#include "../include/cosmetics.h"
#include "../include/Tools.h"
#include <TString.h>
#include <iostream>
#include <TStyle.h>
#include <TFile.h>
#include <TH1.h>
#include <TH2F.h>
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

void ExtractCustomBTagSF(){

  TString file_dir = "/nfs/dust/cms/group/zprime-uhh/Analysis_UL18_2DSF/";
  vector<TString> channel = {"muon", "electron"};

  vector<TString> sample_names = {"TTbar", "ST", "WJets", "DY", "Diboson", "QCD", "ALP_ttbar_signal_UL18", "ALP_ttbar_interference_UL18", "HscalarToTTTo1L1Nu2J_m365_w36p5_res_UL18", "HscalarToTTTo1L1Nu2J_m400_w40p0_res_UL18", "HscalarToTTTo1L1Nu2J_m500_w50p0_res_UL18", "HscalarToTTTo1L1Nu2J_m600_w60p0_res_UL18", "HscalarToTTTo1L1Nu2J_m800_w80p0_res_UL18", "HscalarToTTTo1L1Nu2J_m1000_w100p0_res_UL18", "HscalarToTTTo1L1Nu2J_m365_w36p5_int_UL18", "HscalarToTTTo1L1Nu2J_m400_w40p0_int_UL18", "HscalarToTTTo1L1Nu2J_m500_w50p0_int_UL18", "HscalarToTTTo1L1Nu2J_m600_w60p0_int_UL18", "HscalarToTTTo1L1Nu2J_m800_w80p0_int_UL18", "HscalarToTTTo1L1Nu2J_m1000_w100p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m365_w36p5_res_UL18", "HpseudoToTTTo1L1Nu2J_m400_w40p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m500_w50p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m600_w60p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m800_w80p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m365_w36p5_int_UL18", "HpseudoToTTTo1L1Nu2J_m400_w40p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m500_w50p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m600_w60p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m800_w80p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_UL18", "HscalarToTTTo1L1Nu2J_m365_w91p25_res_UL18", "HscalarToTTTo1L1Nu2J_m400_w100p0_res_UL18", "HscalarToTTTo1L1Nu2J_m500_w125p0_res_UL18", "HscalarToTTTo1L1Nu2J_m600_w150p0_res_UL18", "HscalarToTTTo1L1Nu2J_m800_w200p0_res_UL18", "HscalarToTTTo1L1Nu2J_m1000_w250p0_res_UL18", "HscalarToTTTo1L1Nu2J_m365_w91p25_int_UL18", "HscalarToTTTo1L1Nu2J_m400_w100p0_int_UL18", "HscalarToTTTo1L1Nu2J_m500_w125p0_int_UL18", "HscalarToTTTo1L1Nu2J_m600_w150p0_int_UL18", "HscalarToTTTo1L1Nu2J_m800_w200p0_int_UL18", "HscalarToTTTo1L1Nu2J_m1000_w250p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m365_w91p25_res_UL18", "HpseudoToTTTo1L1Nu2J_m400_w100p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m500_w125p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m600_w150p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m800_w200p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m365_w91p25_int_UL18", "HpseudoToTTTo1L1Nu2J_m400_w100p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m500_w125p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m600_w150p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m800_w200p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_UL18", "HscalarToTTTo1L1Nu2J_m365_w9p125_res_UL18", "HscalarToTTTo1L1Nu2J_m400_w10p0_res_UL18", "HscalarToTTTo1L1Nu2J_m500_w12p5_res_UL18", "HscalarToTTTo1L1Nu2J_m600_w15p0_res_UL18", "HscalarToTTTo1L1Nu2J_m800_w20p0_res_UL18", "HscalarToTTTo1L1Nu2J_m1000_w25p0_res_UL18", "HscalarToTTTo1L1Nu2J_m365_w9p125_int_UL18", "HscalarToTTTo1L1Nu2J_m400_w10p0_int_UL18", "HscalarToTTTo1L1Nu2J_m500_w12p5_int_UL18", "HscalarToTTTo1L1Nu2J_m600_w15p0_int_UL18", "HscalarToTTTo1L1Nu2J_m800_w20p0_int_UL18", "HscalarToTTTo1L1Nu2J_m1000_w25p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m365_w9p125_res_UL18", "HpseudoToTTTo1L1Nu2J_m400_w10p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m500_w12p5_res_UL18", "HpseudoToTTTo1L1Nu2J_m600_w15p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m800_w20p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m365_w9p125_int_UL18", "HpseudoToTTTo1L1Nu2J_m400_w10p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m500_w12p5_int_UL18", "HpseudoToTTTo1L1Nu2J_m600_w15p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m800_w20p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_UL18", "RSGluonToTT_M-500_UL18", "RSGluonToTT_M-1000_UL18", "RSGluonToTT_M-1500_UL18", "RSGluonToTT_M-2000_UL18", "RSGluonToTT_M-2500_UL18", "RSGluonToTT_M-3000_UL18", "RSGluonToTT_M-3500_UL18", "RSGluonToTT_M-4000_UL18", "RSGluonToTT_M-4500_UL18", "RSGluonToTT_M-5000_UL18", "RSGluonToTT_M-5500_UL18", "RSGluonToTT_M-6000_UL18", "ZPrimeToTT_M400_W40_UL18", "ZPrimeToTT_M500_W50_UL18", "ZPrimeToTT_M600_W60_UL18", "ZPrimeToTT_M700_W70_UL18", "ZPrimeToTT_M800_W80_UL18", "ZPrimeToTT_M900_W90_UL18", "ZPrimeToTT_M1000_W100_UL18", "ZPrimeToTT_M1200_W120_UL18", "ZPrimeToTT_M1400_W140_UL18", "ZPrimeToTT_M1600_W160_UL18", "ZPrimeToTT_M1800_W180_UL18", "ZPrimeToTT_M2000_W200_UL18", "ZPrimeToTT_M2500_W250_UL18", "ZPrimeToTT_M3000_W300_UL18", "ZPrimeToTT_M3500_W350_UL18", "ZPrimeToTT_M4000_W400_UL18", "ZPrimeToTT_M4500_W450_UL18", "ZPrimeToTT_M5000_W500_UL18", "ZPrimeToTT_M6000_W600_UL18", "ZPrimeToTT_M7000_W700_UL18", "ZPrimeToTT_M8000_W800_UL18", "ZPrimeToTT_M9000_W900_UL18", "ZPrimeToTT_M400_W120_UL18", "ZPrimeToTT_M500_W150_UL18", "ZPrimeToTT_M600_W180_UL18", "ZPrimeToTT_M700_W210_UL18", "ZPrimeToTT_M800_W240_UL18", "ZPrimeToTT_M900_W270_UL18", "ZPrimeToTT_M1000_W300_UL18", "ZPrimeToTT_M1200_W360_UL18", "ZPrimeToTT_M1400_W420_UL18", "ZPrimeToTT_M1600_W480_UL18", "ZPrimeToTT_M1800_W540_UL18", "ZPrimeToTT_M2000_W600_UL18", "ZPrimeToTT_M2500_W750_UL18", "ZPrimeToTT_M3000_W900_UL18", "ZPrimeToTT_M3500_W1050_UL18", "ZPrimeToTT_M4000_W1200_UL18", "ZPrimeToTT_M4500_W1350_UL18", "ZPrimeToTT_M5000_W1500_UL18", "ZPrimeToTT_M6000_W1800_UL18", "ZPrimeToTT_M7000_W2100_UL18", "ZPrimeToTT_M8000_W2400_UL18", "ZPrimeToTT_M9000_W2700_UL18", "ZPrimeToTT_M400_W4_UL18", "ZPrimeToTT_M500_W5_UL18", "ZPrimeToTT_M600_W6_UL18", "ZPrimeToTT_M700_W7_UL18", "ZPrimeToTT_M800_W8_UL18", "ZPrimeToTT_M900_W9_UL18", "ZPrimeToTT_M1000_W10_UL18", "ZPrimeToTT_M1200_W12_UL18", "ZPrimeToTT_M1400_W14_UL18", "ZPrimeToTT_M1600_W16_UL18", "ZPrimeToTT_M1800_W18_UL18", "ZPrimeToTT_M2000_W20_UL18", "ZPrimeToTT_M2500_W25_UL18", "ZPrimeToTT_M3000_W30_UL18", "ZPrimeToTT_M3500_W35_UL18", "ZPrimeToTT_M4000_W40_UL18", "ZPrimeToTT_M4500_W45_UL18", "ZPrimeToTT_M5000_W50_UL18", "ZPrimeToTT_M7000_W70_UL18", "ZPrimeToTT_M8000_W80_UL18"};
// ZPrimeToTT_M6000_W60_UL18, ZPrimeToTT_M9000_W90_UL18 missing samples


  for(unsigned int j=0; j<channel.size(); j++){
    for(unsigned int i=0; i<sample_names.size(); i++){
      TString filename;
      filename = file_dir + channel.at(j) + "/uhh2.AnalysisModuleRunner.MC." + sample_names.at(i) + ".root";
   
      TFile* file_in = new TFile(filename, "READ");
  
      TH2F *h_NJets_HT_beforeSF = (TH2F*)file_in->Get("BeforeBtagSF_General/N_Jets_vs_HT");
      TH2F *h_NJets_HT_afterSF  = (TH2F*)file_in->Get("AfterBtagSF_General/N_Jets_vs_HT");
  
      TH2F *h_ratio = (TH2F*)h_NJets_HT_beforeSF->Clone(); 
      h_ratio->Divide(h_NJets_HT_afterSF);
      h_ratio->SetName("N_Jets_vs_HT_"+sample_names.at(i));
  
      TFile* f = new TFile("customBtagSF_" + channel.at(j) + ".root", "UPDATE");
      h_ratio->Write();
      delete f;
  
      // Save plot with SF
/*      TCanvas* c = new TCanvas("c", "c", 1200, 800);
      c->Divide(1,1);
      c->cd(1);
      gPad->SetTopMargin(0.07);
      gPad->SetBottomMargin(0.17);
      gPad->SetLeftMargin(0.2);
      gPad->SetRightMargin(0.1);
      gPad->SetLogy();
      gStyle->SetOptStat(0);
     
      h_ratio->Draw("colz");
     
      h_ratio->SetTitle("");
      h_ratio->GetXaxis()->SetTitle("NJets");
      h_ratio->SetLineColor(kBlue);
      h_ratio->SetLineWidth(2);
      h_ratio->SetLineStyle(2);
      h_ratio->GetXaxis()->SetTitleSize(0.055);
      h_ratio->GetXaxis()->SetLabelSize(0.05);
      h_ratio->GetYaxis()->SetRangeUser(0.,10000.);
      h_ratio->GetYaxis()->SetTitle("HT [GeV]");
      h_ratio->GetYaxis()->SetTitleSize(0.055);
      h_ratio->GetYaxis()->SetLabelSize(0.05);
      h_ratio->Draw("colz");
     
     
      //auto legend = new TLegend(0.58,0.74,0.86,0.92);
      //legend->SetBorderSize(0);
      //legend->AddEntry(h_ratio,"Zprime","l");
      //legend->Draw("same");
     
     
      TString infotext = "59.8 fb^{-1}(13 TeV)";
      TLatex *text1 = new TLatex(3.5, 24, infotext);
      text1->SetNDC();
      text1->SetTextAlign(31);
      text1->SetX(1.-0.1);
      text1->SetTextFont(42);
      text1->SetTextSize(0.07*0.7);
      text1->SetY(1.-0.07+0.2*0.07);
      text1->Draw();
     
      c->SaveAs("Plots_BTagSF/SF_" + channel.at(j) +"_" + sample_names.at(i) +".pdf");
     
      delete c;
*/  
      delete file_in;
  
    }
  }

}
