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
#include <string>

using namespace std;

void getRMS(){

  TString filename_base = "";
  filename_base += "/nfs/dust/cms/user/deleokse/RunII_106_v2/PDF_syst/uhh2.AnalysisModuleRunner.MC.";

  vector<TString> samples = {"ZPrimeToTT_M1000_W100_UL18"};
  vector<bool> isSignal (samples.size(), false);

  for(unsigned int i=0; i<samples.size(); i++){

    cout << "sample " << samples.at(i) << endl;

    // check if the sample is a signal or a background
    isSignal.at(i) = (samples.at(i).Index("ZPrimeToTT") == 0 );

    TString filename = filename_base + samples.at(i) + "_DNNMuon" + ".root";
    TFile* f_in = new TFile(filename, "READ");

    // For each Signal sample read the normalization values - one for each of the 100 PDF replicas
    vector<double> pdf_norm (100, 1.); //For bkgs set normalization value to 1 
    if( isSignal.at(i) ){
       string pdf_numb[100];
       ifstream normfile("/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/SignalPDFNorm/SignalNorm_"+ samples.at(i) +".txt", ios::in);
       if (normfile.is_open()){
         for(int i = 0; i < 100; ++i){
           normfile >> pdf_numb[i] >> pdf_norm[i];
         }
         normfile.close();
       } 
    } 

    TH1F *h_nominal = (TH1F*)f_in->Get("DNN_output0_General/M_Zprime_rebin4");
    TH1F *h_PDF_up = (TH1F*)h_nominal->Clone();
    TH1F *h_PDF_down = (TH1F*)h_nominal->Clone();

    float sum_bins = 0;
    // Loop over each bin of the Mtt histograms
     for(int j=1; j<26; j++){

      float nominal = h_nominal->GetBinContent(j); 
      float sum_bins = 0;

       // Loop over each of the 100 Histogrmas reweighted with the PDF replicas
       for(int i = 1; i<101; i++){
           stringstream ss_name;
           ss_name << "Zprime_PDFVariations_DNN_output0/M_Zprime_PDF_" << i;
           string s_name = ss_name.str();
           const char* char_name = s_name.c_str();

           float bin =  ((TH1F*)(f_in->Get(char_name)))->GetBinContent(j);
           float norm_bin = bin * pdf_norm[i-1];

           sum_bins += pow(norm_bin - nominal,2);
       }
       float rms = sqrt( sum_bins /100  );

       h_PDF_up->SetBinContent(j, nominal+rms);
       h_PDF_down->SetBinContent(j, nominal-rms);

    }

    // Save the histo with the up/down variations in root file
    TFile* f_out = new TFile("/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/" + samples.at(i) + ".root", "RECREATE");
    h_PDF_up->SetName(samples.at(i)+"_PDF_up");
    h_PDF_down->SetName(samples.at(i)+"_PDF_down");
    h_PDF_up->Write();
    h_PDF_down->Write();
    delete f_out;

    // Plots nominal hist + up/down variations
    TCanvas* c = new TCanvas("c", "c", 1200, 800);
    c->Divide(1,1);
    c->cd(1);
    gPad->SetTopMargin(0.07);
    gPad->SetBottomMargin(0.17);
    gPad->SetLeftMargin(0.2);
    gPad->SetRightMargin(0.1);
    //gPad->SetLogy();
    gStyle->SetOptStat(0);
    
    h_nominal->SetLineWidth(1);
    h_nominal->SetLineColor(kBlack);
    h_PDF_up->SetLineWidth(1);
    h_PDF_up->SetLineColor(kRed);
    h_PDF_down->SetLineWidth(1);
    h_PDF_down->SetLineColor(kBlue);

    h_nominal->Draw("HIST");
    h_nominal->SetTitle("");
    h_nominal->GetXaxis()->SetTitle("M_{t#bar{t}} [GeV]");
    h_nominal->GetXaxis()->SetRangeUser(0.,3000.);
    h_nominal->GetXaxis()->SetTitleSize(0.055);
    h_nominal->GetXaxis()->SetLabelSize(0.05);
    h_nominal->GetYaxis()->SetTitle("Events");
    h_nominal->GetYaxis()->SetRangeUser(0.,1500.);
    h_nominal->GetYaxis()->SetTitleSize(0.055);
    h_nominal->GetYaxis()->SetLabelSize(0.05);
    h_nominal->Draw("HIST");
    h_PDF_up->Draw("HIST same");
    h_PDF_down->Draw("HIST same");

    auto legend = new TLegend(0.7,0.67,0.85,0.9);
    legend->SetBorderSize(0);
    legend->SetFillStyle(0);
    legend->SetTextSize(0.035);
    legend->SetTextFont(42);
    legend->AddEntry(h_nominal,"nominal","le");
    legend->AddEntry(h_PDF_up,"PDF up","le");
    legend->AddEntry(h_PDF_down,"PDF down","le");
    legend->Draw();

    TString cmstext = "CMS";
    TLatex *text2 = new TLatex(3.5, 24, cmstext);
    text2->SetNDC();
    text2->SetTextAlign(13);
    text2->SetX(0.24);
    text2->SetTextFont(62);
    text2->SetTextSize(0.06825);
    text2->SetY(0.895);
    text2->Draw();


    TString supptext = "Simulation";
    TLatex *text4 = new TLatex(3.5, 24, supptext);
    text4->SetNDC();
    text4->SetTextAlign(13);
    text4->SetX(0.24);
    text4->SetTextFont(52);
    text4->SetTextSize(0.55*0.06825);
    text4->SetY(0.8312);
    text4->Draw();

    TString supptext2 = "Work in progress";
    TLatex *text5 = new TLatex(3.5, 24, supptext2);
    text5->SetNDC();
    text5->SetTextAlign(13);
    text5->SetX(0.24);
    text5->SetTextFont(52);
    text5->SetTextSize(0.55*0.06825);
    text5->SetY(0.79);
    text5->Draw();

    TString infotext = "59.8 fb^{-1}(13 TeV)";
    TLatex *text1 = new TLatex(3.5, 24, infotext);
    text1->SetNDC();
    text1->SetTextAlign(31);
    text1->SetX(1.-0.1);
    text1->SetTextFont(42);
    text1->SetTextSize(0.07*0.7);
    text1->SetY(1.-0.07+0.2*0.07);
    text1->Draw();


    c->SaveAs("/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/PDF_"+ samples.at(i) +".pdf");
    c->Close();

    delete f_in;
  }
}
