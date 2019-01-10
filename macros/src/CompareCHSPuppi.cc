#include "../include/cosmetics.h"
#include "../include/Tools.h"
#include <TString.h>
#include <iostream>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH1D.h>
#include <TCanvas.h>
#include <TText.h>
#include <TPaveText.h>
#include <TGaxis.h>
#include <TGraph.h>
#include <TStyle.h>
#include <TGraphAsymmErrors.h>
#include <TLegend.h>
#include <TLegendEntry.h>
#include <TROOT.h>
#include <TKey.h>
#include <TLatex.h>
#include <TClass.h>
#include <fstream>

using namespace std;

void DoComparison(TString chsdir, TString puppidir, TString outdir, map<TString, TString> samplemap, TString sample);

void AnalysisTool::CompareCHSPuppi(){

  map<TString, TString> samplemap;
  samplemap["Data"] = "uhh2.AnalysisModuleRunner.DATA.DATA_blinded.root";
  samplemap["TTbar"] = "uhh2.AnalysisModuleRunner.MC.TTbar.root";
  samplemap["WJets"] = "uhh2.AnalysisModuleRunner.MC.WJets.root";
  samplemap["DYJets"] = "uhh2.AnalysisModuleRunner.MC.DYJets.root";
  samplemap["SingleTop"] = "uhh2.AnalysisModuleRunner.MC.ST.root";
  samplemap["QCD"] = "uhh2.AnalysisModuleRunner.MC.QCD_Mu.root";

  TString chsdir = AnalysisTool::base_path_chs + "/NOMINAL/";
  TString puppidir = AnalysisTool::base_path_puppi + "/NOMINAL/";
  TString outdir = puppidir + "Plots/SingleEPS/";

  DoComparison(chsdir, puppidir, outdir, samplemap, "Data");
  DoComparison(chsdir, puppidir, outdir, samplemap, "TTbar");
  DoComparison(chsdir, puppidir, outdir, samplemap, "WJets");
  DoComparison(chsdir, puppidir, outdir, samplemap, "DYJets");
  DoComparison(chsdir, puppidir, outdir, samplemap, "SingleTop");
  DoComparison(chsdir, puppidir, outdir, samplemap, "QCD");

}


void DoComparison(TString chsdir, TString puppidir, TString outdir, map<TString, TString> samplemap, TString sample){
  gStyle->SetOptStat(0);
  gErrorIgnoreLevel = 2002;

  // Open Files
  // ==========
  TString samplename = samplemap[sample];
  TString infilename_chs = chsdir + samplename;
  TString infilename_puppi = puppidir + samplename;
  TFile* infile_chs = new TFile(infilename_chs, "READ");
  TFile* infile_puppi = new TFile(infilename_puppi, "READ");

  // Get list of folders
  // Files must have exact same content histogram-wise
  // =================================================

  infile_chs->cd();
  vector<TString> foldernames;
  TDirectory* dir = gDirectory;
  TIter iter(dir->GetListOfKeys());
  TKey *key;
  while ((key = (TKey*)iter())) {
    TClass *cl = gROOT->GetClass(key->GetClassName());
    if(cl->InheritsFrom("TDirectoryFile")){
      TString name = key->ReadObj()->GetName();
      if(name != "SFrame") foldernames.emplace_back(name);
    }
  }

  for(unsigned int i=0; i<foldernames.size(); i++){
    TString foldername = foldernames.at(i);
    if(!foldername.Contains("_General")) continue;
    cout << foldername << endl;
    infile_chs->cd(foldername);

    // Get histograms (only TH1), get corresponding histogram from infile_puppi, plot comparison and ratio, both normalized and un-normalized
    // ======================================================================================================================================

    infile_chs->cd(foldername);
    dir = gDirectory;
    iter = dir->GetListOfKeys();

    // Loop over all objects in this dir
    while ((key = (TKey*)iter())) {
      TString myclass = "TH1F";

      // Consider only TH1F objects
      if(key->GetClassName() == myclass){
        TString histname = key->ReadObj()->GetName();

        TString readoutname = foldername + "/" + histname;
        TH1F* h_chs = (TH1F*)infile_chs->Get(readoutname);
        if(h_chs->Integral() == 0.) continue;
        TH1F* h_puppi = (TH1F*)infile_puppi->Get(readoutname);
        TH1F* h_chs_norm = (TH1F*)h_chs->Clone();
        TH1F* h_puppi_norm = (TH1F*)h_puppi->Clone();
        h_chs_norm->Scale(1./h_chs_norm->Integral());
        h_puppi_norm->Scale(1./h_puppi_norm->Integral());

        // Now that we have both histograms: Compute ratio, normalized and also un-normalized
        // ==================================================================================

        TGraphAsymmErrors* g_ratio = new TGraphAsymmErrors(h_puppi, h_chs, "pois");
        TGraphAsymmErrors* g_ratio_norm = new TGraphAsymmErrors(h_puppi_norm, h_chs_norm, "pois");


        // Do cosmetics and plot!
        // =====================

        float maximum = 0.;
        for(int i=1; i<h_chs->GetNbinsX()+1; i++){
          if(maximum < h_chs->GetBinContent(i)) maximum = h_chs->GetBinContent(i);
          if(maximum < h_puppi->GetBinContent(i)) maximum = h_puppi->GetBinContent(i);
        }

        Int_t col_puppi = kRed+1;
        Int_t col_chs = kBlack;
        h_chs->SetLineColor(col_chs);
        h_chs_norm->SetLineColor(col_chs);
        h_puppi->SetLineColor(col_puppi);
        h_puppi_norm->SetLineColor(col_puppi);
        g_ratio->SetLineColor(col_puppi);
        g_ratio_norm->SetLineColor(col_puppi);
        h_chs->GetYaxis()->SetRangeUser(5E-2, maximum*10);
        h_chs->GetYaxis()->SetTitle("Events / bin");
        h_chs_norm->GetYaxis()->SetRangeUser(5E-8, 5E+0);
        h_chs_norm->GetYaxis()->SetTitle("normalized entries");

        TH1F* h_axis = (TH1F*)h_chs->Clone();
        // h_axis->GetYaxis()->SetRangeUser(0.3, 1.7);
        h_axis->GetYaxis()->SetTitle("Puppi / CHS");
        h_axis->GetYaxis()->SetLabelSize(12);
        h_axis->GetXaxis()->SetTitle(h_chs->GetTitle());
        HistCosmetics(h_axis, true);


        // First for un-normalized histograms
        // ==================================

        TCanvas* c_out = new TCanvas("c_out", "Comparison of CHS and PUPPI", 400, 400);
        TPad* pad_top = SetupRatioPadTop();
        TPad* pad_bot = SetupRatioPad();
        pad_top->Draw();
        pad_bot->Draw();
        pad_top->cd();
        HistCosmetics(h_chs, false);
        HistCosmetics(h_puppi, false);
        h_chs->Draw("E");
        h_puppi->Draw("E SAME");

        TLegend* leg1 = new TLegend(0.60, 0.65, 0.90, 0.90);
        leg1->SetFillStyle(0);
        leg1->SetLineWidth(0);
        leg1->AddEntry(h_chs, "CHS objects", "l");
        leg1->AddEntry(h_puppi, "Puppi objects", "l");
        leg1->Draw("SAME");
        pad_top->SetLogy();

        pad_bot->cd();
        h_axis->Draw("AXIS");
        HistCosmetics(g_ratio, true);
        g_ratio->Draw("EP SAME");

        TLine* line1 = new TLine(h_axis->GetBinLowEdge(1), 1, h_axis->GetBinLowEdge(h_axis->GetNbinsX()+1), 1);
        line1->SetLineWidth(2);
        line1->SetLineColor(kBlack);
        line1->SetLineStyle(2);
        line1->Draw("SAME");

        pad_top->cd();
        TString infotext = "41.5 fb^{-1} (13 TeV)";
        TLatex *text1 = new TLatex(3.5, 24, infotext);
        text1->SetNDC();
        text1->SetTextAlign(33);
        text1->SetX(0.94);
        text1->SetTextFont(43);
        text1->SetTextSize(16);
        text1->SetY(0.995);
        text1->Draw("SAME");

        TString sampletext = sample;
        TLatex *text2 = new TLatex(3.5, 24, sampletext);
        text2->SetNDC();
        text2->SetTextAlign(33);
        text2->SetX(0.3);
        text2->SetTextFont(43);
        text2->SetTextSize(16);
        text2->SetY(0.98);
        text2->Draw("SAME");

        c_out->SaveAs(outdir + "CHSPuppi_" + sample + "_" + foldername + "_" + histname + ".eps");
        c_out->SaveAs("Plots/CHSPuppiComparison/CHSPuppi_" + sample + "_" + foldername + "_" + histname + ".eps");
        delete c_out;


        // Normalized histograms
        // =====================

        TCanvas* c_out2 = new TCanvas("c_out2", "Comparison of CHS and PUPPI", 400, 400);
        pad_top = SetupRatioPadTop();
        pad_bot = SetupRatioPad();
        pad_top->Draw();
        pad_bot->Draw();
        pad_top->cd();
        HistCosmetics(h_chs_norm, false);
        HistCosmetics(h_puppi_norm, false);
        h_chs_norm->Draw("E");
        h_puppi_norm->Draw("E SAME");

        TLegend* leg2 = new TLegend(0.60, 0.65, 0.90, 0.90);
        leg2->SetFillStyle(0);
        leg2->SetLineWidth(0);
        leg2->AddEntry(h_chs_norm, "CHS objects", "l");
        leg2->AddEntry(h_puppi_norm, "Puppi objects", "l");
        leg2->Draw("SAME");
        pad_top->SetLogy();

        pad_bot->cd();
        h_axis->Draw("AXIS");
        HistCosmetics(g_ratio_norm, true);
        g_ratio_norm->Draw("EP SAME");

        line1->Draw("SAME");

        pad_top->cd();
        text1->Draw("SAME");
        text2->Draw("SAME");



        c_out2->SaveAs(outdir + "CHSPuppi_" + sample + "_" + foldername + "_" + histname + "_norm.eps");
        c_out2->SaveAs("Plots/CHSPuppiComparison/CHSPuppi_" + sample + "_" + foldername + "_" + histname + "_norm.eps");
        delete c_out2;


      }
    }

  }



  delete infile_chs;
  delete infile_puppi;
}
