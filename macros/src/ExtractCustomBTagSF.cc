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

  vector<TString> channel = {"muon", "electron"};
  vector<TString> year = {"UL16preVFP","UL16postVFP", "UL17", "UL18"};
  TString file_dir = "/nfs/dust/cms/group/zprime-uhh/";

  vector<TString> sample_names = {"TTbar", "ST", "WJets", "DY", "Diboson", "QCD", "ALP_ttbar_signal", "ALP_ttbar_interference", "HscalarToTTTo1L1Nu2J_m365_w36p5_res", "HscalarToTTTo1L1Nu2J_m400_w40p0_res", "HscalarToTTTo1L1Nu2J_m500_w50p0_res", "HscalarToTTTo1L1Nu2J_m600_w60p0_res", "HscalarToTTTo1L1Nu2J_m800_w80p0_res", "HscalarToTTTo1L1Nu2J_m1000_w100p0_res", "HscalarToTTTo1L1Nu2J_m365_w36p5_int", "HscalarToTTTo1L1Nu2J_m400_w40p0_int", "HscalarToTTTo1L1Nu2J_m500_w50p0_int", "HscalarToTTTo1L1Nu2J_m600_w60p0_int", "HscalarToTTTo1L1Nu2J_m800_w80p0_int", "HscalarToTTTo1L1Nu2J_m1000_w100p0_int", "HpseudoToTTTo1L1Nu2J_m365_w36p5_res", "HpseudoToTTTo1L1Nu2J_m400_w40p0_res", "HpseudoToTTTo1L1Nu2J_m500_w50p0_res", "HpseudoToTTTo1L1Nu2J_m600_w60p0_res", "HpseudoToTTTo1L1Nu2J_m800_w80p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res", "HpseudoToTTTo1L1Nu2J_m365_w36p5_int", "HpseudoToTTTo1L1Nu2J_m400_w40p0_int", "HpseudoToTTTo1L1Nu2J_m500_w50p0_int", "HpseudoToTTTo1L1Nu2J_m600_w60p0_int", "HpseudoToTTTo1L1Nu2J_m800_w80p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int", "HscalarToTTTo1L1Nu2J_m365_w91p25_res", "HscalarToTTTo1L1Nu2J_m400_w100p0_res", "HscalarToTTTo1L1Nu2J_m500_w125p0_res", "HscalarToTTTo1L1Nu2J_m600_w150p0_res", "HscalarToTTTo1L1Nu2J_m800_w200p0_res", "HscalarToTTTo1L1Nu2J_m1000_w250p0_res", "HscalarToTTTo1L1Nu2J_m365_w91p25_int", "HscalarToTTTo1L1Nu2J_m400_w100p0_int", "HscalarToTTTo1L1Nu2J_m500_w125p0_int", "HscalarToTTTo1L1Nu2J_m600_w150p0_int", "HscalarToTTTo1L1Nu2J_m800_w200p0_int", "HscalarToTTTo1L1Nu2J_m1000_w250p0_int", "HpseudoToTTTo1L1Nu2J_m365_w91p25_res", "HpseudoToTTTo1L1Nu2J_m400_w100p0_res", "HpseudoToTTTo1L1Nu2J_m500_w125p0_res", "HpseudoToTTTo1L1Nu2J_m600_w150p0_res", "HpseudoToTTTo1L1Nu2J_m800_w200p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res", "HpseudoToTTTo1L1Nu2J_m365_w91p25_int", "HpseudoToTTTo1L1Nu2J_m400_w100p0_int", "HpseudoToTTTo1L1Nu2J_m500_w125p0_int", "HpseudoToTTTo1L1Nu2J_m600_w150p0_int", "HpseudoToTTTo1L1Nu2J_m800_w200p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int", "HscalarToTTTo1L1Nu2J_m365_w9p125_res", "HscalarToTTTo1L1Nu2J_m400_w10p0_res", "HscalarToTTTo1L1Nu2J_m500_w12p5_res", "HscalarToTTTo1L1Nu2J_m600_w15p0_res", "HscalarToTTTo1L1Nu2J_m800_w20p0_res", "HscalarToTTTo1L1Nu2J_m1000_w25p0_res", "HscalarToTTTo1L1Nu2J_m365_w9p125_int", "HscalarToTTTo1L1Nu2J_m400_w10p0_int", "HscalarToTTTo1L1Nu2J_m500_w12p5_int", "HscalarToTTTo1L1Nu2J_m600_w15p0_int", "HscalarToTTTo1L1Nu2J_m800_w20p0_int", "HscalarToTTTo1L1Nu2J_m1000_w25p0_int", "HpseudoToTTTo1L1Nu2J_m365_w9p125_res", "HpseudoToTTTo1L1Nu2J_m400_w10p0_res", "HpseudoToTTTo1L1Nu2J_m500_w12p5_res", "HpseudoToTTTo1L1Nu2J_m600_w15p0_res", "HpseudoToTTTo1L1Nu2J_m800_w20p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res", "HpseudoToTTTo1L1Nu2J_m365_w9p125_int", "HpseudoToTTTo1L1Nu2J_m400_w10p0_int", "HpseudoToTTTo1L1Nu2J_m500_w12p5_int", "HpseudoToTTTo1L1Nu2J_m600_w15p0_int", "HpseudoToTTTo1L1Nu2J_m800_w20p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int", "RSGluonToTT_M-500", "RSGluonToTT_M-1000", "RSGluonToTT_M-1500", "RSGluonToTT_M-2000", "RSGluonToTT_M-2500", "RSGluonToTT_M-3000", "RSGluonToTT_M-3500", "RSGluonToTT_M-4000", "RSGluonToTT_M-4500", "RSGluonToTT_M-5000", "RSGluonToTT_M-5500", "RSGluonToTT_M-6000", "ZPrimeToTT_M400_W40", "ZPrimeToTT_M500_W50", "ZPrimeToTT_M600_W60", "ZPrimeToTT_M700_W70", "ZPrimeToTT_M800_W80", "ZPrimeToTT_M900_W90", "ZPrimeToTT_M1000_W100", "ZPrimeToTT_M1200_W120", "ZPrimeToTT_M1400_W140", "ZPrimeToTT_M1600_W160", "ZPrimeToTT_M1800_W180", "ZPrimeToTT_M2000_W200", "ZPrimeToTT_M2500_W250", "ZPrimeToTT_M3000_W300", "ZPrimeToTT_M3500_W350", "ZPrimeToTT_M4000_W400", "ZPrimeToTT_M4500_W450", "ZPrimeToTT_M5000_W500", "ZPrimeToTT_M6000_W600",  "ZPrimeToTT_M7000_W700", "ZPrimeToTT_M8000_W800", "ZPrimeToTT_M9000_W900", "ZPrimeToTT_M400_W120", "ZPrimeToTT_M500_W150", "ZPrimeToTT_M600_W180", "ZPrimeToTT_M700_W210", "ZPrimeToTT_M800_W240", "ZPrimeToTT_M900_W270", "ZPrimeToTT_M1000_W300", "ZPrimeToTT_M1200_W360", "ZPrimeToTT_M1400_W420", "ZPrimeToTT_M1600_W480", "ZPrimeToTT_M1800_W540", "ZPrimeToTT_M2000_W600", "ZPrimeToTT_M2500_W750", "ZPrimeToTT_M3000_W900", "ZPrimeToTT_M3500_W1050", "ZPrimeToTT_M4000_W1200", "ZPrimeToTT_M4500_W1350", "ZPrimeToTT_M5000_W1500", "ZPrimeToTT_M6000_W1800", "ZPrimeToTT_M7000_W2100", "ZPrimeToTT_M8000_W2400", "ZPrimeToTT_M9000_W2700", "ZPrimeToTT_M400_W4", "ZPrimeToTT_M500_W5", "ZPrimeToTT_M600_W6", "ZPrimeToTT_M700_W7", "ZPrimeToTT_M800_W8", "ZPrimeToTT_M900_W9", "ZPrimeToTT_M1000_W10", "ZPrimeToTT_M1200_W12", "ZPrimeToTT_M1400_W14", "ZPrimeToTT_M1600_W16", "ZPrimeToTT_M1800_W18", "ZPrimeToTT_M2000_W20", "ZPrimeToTT_M2500_W25", "ZPrimeToTT_M3000_W30", "ZPrimeToTT_M3500_W35", "ZPrimeToTT_M4000_W40", "ZPrimeToTT_M4500_W45", "ZPrimeToTT_M5000_W50", "ZPrimeToTT_M6000_W60", "ZPrimeToTT_M7000_W70", "ZPrimeToTT_M8000_W80", "ZPrimeToTT_M9000_W90"};


for(unsigned int k=0; k<year.size(); k++){
  for(unsigned int j=0; j<channel.size(); j++){
    for(unsigned int i=0; i<sample_names.size(); i++){
      TString filename;
      filename = file_dir + "Analysis_" + year.at(k) +"_2DSF/" + channel.at(j) + "/uhh2.AnalysisModuleRunner.MC." + sample_names.at(i) + ".root";

      TFile* file_in = new TFile(filename, "READ");
  
      TH2F *h_NJets_HT_beforeSF = (TH2F*)file_in->Get("BeforeBtagSF_General/N_Jets_vs_HT");
      TH2F *h_NJets_HT_afterSF  = (TH2F*)file_in->Get("AfterBtagSF_General/N_Jets_vs_HT");
  
      TH2F *h_ratio = (TH2F*)h_NJets_HT_beforeSF->Clone(); 
      h_ratio->Divide(h_NJets_HT_afterSF);
      h_ratio->SetName("N_Jets_vs_HT_"+sample_names.at(i));
  
      TFile* f = new TFile("files_BTagSF/customBtagSF_" + channel.at(j) +"_" + year.at(k) + ".root", "UPDATE");
      h_ratio->Write();
      delete f;
 
      // Save plot with SF
      if(year.at(k)=="UL18" && channel.at(j)=="muon" && sample_names.at(i)=="TTbar"){ 
         TCanvas* c = new TCanvas("c", "c", 1200, 800);
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
      } 
      delete file_in;
  
    }
  }
}

}
