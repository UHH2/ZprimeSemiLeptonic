#include "../include/cosmetics.h"
#include "../include/Tools.h"
#include "TString.h"
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

void CalculateChi2Values(){

  vector<TString> channel = {"muon", "electron"};
  //vector<TString> year = {"UL16preVFP","UL16postVFP", "UL17", "UL18"};
  vector<TString> year = {"UL17"};
  TString file_dir = "/nfs/dust/cms/user/deleokse/RunII_106_v2/";

  vector<TString> samples = {"TTbar"};
//  vector<TString> samples = {"ALP_ttbar_signal", "ALP_ttbar_interference", "HscalarToTTTo1L1Nu2J_m365_w36p5_res", "HscalarToTTTo1L1Nu2J_m400_w40p0_res", "HscalarToTTTo1L1Nu2J_m500_w50p0_res", "HscalarToTTTo1L1Nu2J_m600_w60p0_res", "HscalarToTTTo1L1Nu2J_m800_w80p0_res", "HscalarToTTTo1L1Nu2J_m1000_w100p0_res", "HscalarToTTTo1L1Nu2J_m365_w36p5_int", "HscalarToTTTo1L1Nu2J_m400_w40p0_int", "HscalarToTTTo1L1Nu2J_m500_w50p0_int", "HscalarToTTTo1L1Nu2J_m600_w60p0_int", "HscalarToTTTo1L1Nu2J_m800_w80p0_int", "HscalarToTTTo1L1Nu2J_m1000_w100p0_int", "HpseudoToTTTo1L1Nu2J_m365_w36p5_res", "HpseudoToTTTo1L1Nu2J_m400_w40p0_res", "HpseudoToTTTo1L1Nu2J_m500_w50p0_res", "HpseudoToTTTo1L1Nu2J_m600_w60p0_res", "HpseudoToTTTo1L1Nu2J_m800_w80p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res", "HpseudoToTTTo1L1Nu2J_m365_w36p5_int", "HpseudoToTTTo1L1Nu2J_m400_w40p0_int", "HpseudoToTTTo1L1Nu2J_m500_w50p0_int", "HpseudoToTTTo1L1Nu2J_m600_w60p0_int", "HpseudoToTTTo1L1Nu2J_m800_w80p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int", "HscalarToTTTo1L1Nu2J_m365_w91p25_res", "HscalarToTTTo1L1Nu2J_m400_w100p0_res", "HscalarToTTTo1L1Nu2J_m500_w125p0_res", "HscalarToTTTo1L1Nu2J_m600_w150p0_res", "HscalarToTTTo1L1Nu2J_m800_w200p0_res", "HscalarToTTTo1L1Nu2J_m1000_w250p0_res", "HscalarToTTTo1L1Nu2J_m365_w91p25_int", "HscalarToTTTo1L1Nu2J_m400_w100p0_int", "HscalarToTTTo1L1Nu2J_m500_w125p0_int", "HscalarToTTTo1L1Nu2J_m600_w150p0_int", "HscalarToTTTo1L1Nu2J_m800_w200p0_int", "HscalarToTTTo1L1Nu2J_m1000_w250p0_int", "HpseudoToTTTo1L1Nu2J_m365_w91p25_res", "HpseudoToTTTo1L1Nu2J_m400_w100p0_res", "HpseudoToTTTo1L1Nu2J_m500_w125p0_res", "HpseudoToTTTo1L1Nu2J_m600_w150p0_res", "HpseudoToTTTo1L1Nu2J_m800_w200p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res", "HpseudoToTTTo1L1Nu2J_m365_w91p25_int", "HpseudoToTTTo1L1Nu2J_m400_w100p0_int", "HpseudoToTTTo1L1Nu2J_m500_w125p0_int", "HpseudoToTTTo1L1Nu2J_m600_w150p0_int", "HpseudoToTTTo1L1Nu2J_m800_w200p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int", "HscalarToTTTo1L1Nu2J_m365_w9p125_res", "HscalarToTTTo1L1Nu2J_m400_w10p0_res", "HscalarToTTTo1L1Nu2J_m500_w12p5_res", "HscalarToTTTo1L1Nu2J_m600_w15p0_res", "HscalarToTTTo1L1Nu2J_m800_w20p0_res", "HscalarToTTTo1L1Nu2J_m1000_w25p0_res", "HscalarToTTTo1L1Nu2J_m365_w9p125_int", "HscalarToTTTo1L1Nu2J_m400_w10p0_int", "HscalarToTTTo1L1Nu2J_m500_w12p5_int", "HscalarToTTTo1L1Nu2J_m600_w15p0_int", "HscalarToTTTo1L1Nu2J_m800_w20p0_int", "HscalarToTTTo1L1Nu2J_m1000_w25p0_int", "HpseudoToTTTo1L1Nu2J_m365_w9p125_res", "HpseudoToTTTo1L1Nu2J_m400_w10p0_res", "HpseudoToTTTo1L1Nu2J_m500_w12p5_res", "HpseudoToTTTo1L1Nu2J_m600_w15p0_res", "HpseudoToTTTo1L1Nu2J_m800_w20p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res", "HpseudoToTTTo1L1Nu2J_m365_w9p125_int", "HpseudoToTTTo1L1Nu2J_m400_w10p0_int", "HpseudoToTTTo1L1Nu2J_m500_w12p5_int", "HpseudoToTTTo1L1Nu2J_m600_w15p0_int", "HpseudoToTTTo1L1Nu2J_m800_w20p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int", "RSGluonToTT_M-500", "RSGluonToTT_M-1000", "RSGluonToTT_M-1500", "RSGluonToTT_M-2000", "RSGluonToTT_M-2500", "RSGluonToTT_M-3000", "RSGluonToTT_M-3500", "RSGluonToTT_M-4000", "RSGluonToTT_M-4500", "RSGluonToTT_M-5000", "RSGluonToTT_M-5500", "RSGluonToTT_M-6000", "ZPrimeToTT_M400_W40", "ZPrimeToTT_M500_W50", "ZPrimeToTT_M600_W60", "ZPrimeToTT_M700_W70", "ZPrimeToTT_M800_W80", "ZPrimeToTT_M900_W90", "ZPrimeToTT_M1000_W100", "ZPrimeToTT_M1200_W120", "ZPrimeToTT_M1400_W140", "ZPrimeToTT_M1600_W160", "ZPrimeToTT_M1800_W180", "ZPrimeToTT_M2000_W200", "ZPrimeToTT_M2500_W250", "ZPrimeToTT_M3000_W300", "ZPrimeToTT_M3500_W350", "ZPrimeToTT_M4000_W400", "ZPrimeToTT_M4500_W450", "ZPrimeToTT_M5000_W500", "ZPrimeToTT_M6000_W600",  "ZPrimeToTT_M7000_W700", "ZPrimeToTT_M8000_W800", "ZPrimeToTT_M9000_W900", "ZPrimeToTT_M400_W120", "ZPrimeToTT_M500_W150", "ZPrimeToTT_M600_W180", "ZPrimeToTT_M700_W210", "ZPrimeToTT_M800_W240", "ZPrimeToTT_M900_W270", "ZPrimeToTT_M1000_W300", "ZPrimeToTT_M1200_W360", "ZPrimeToTT_M1400_W420", "ZPrimeToTT_M1600_W480", "ZPrimeToTT_M1800_W540", "ZPrimeToTT_M2000_W600", "ZPrimeToTT_M2500_W750", "ZPrimeToTT_M3000_W900", "ZPrimeToTT_M3500_W1050", "ZPrimeToTT_M4000_W1200", "ZPrimeToTT_M4500_W1350", "ZPrimeToTT_M5000_W1500", "ZPrimeToTT_M6000_W1800", "ZPrimeToTT_M7000_W2100", "ZPrimeToTT_M8000_W2400", "ZPrimeToTT_M9000_W2700", "ZPrimeToTT_M400_W4", "ZPrimeToTT_M500_W5", "ZPrimeToTT_M600_W6", "ZPrimeToTT_M700_W7", "ZPrimeToTT_M800_W8", "ZPrimeToTT_M900_W9", "ZPrimeToTT_M1000_W10", "ZPrimeToTT_M1200_W12", "ZPrimeToTT_M1400_W14", "ZPrimeToTT_M1600_W16", "ZPrimeToTT_M1800_W18", "ZPrimeToTT_M2000_W20", "ZPrimeToTT_M2500_W25", "ZPrimeToTT_M3000_W30", "ZPrimeToTT_M3500_W35", "ZPrimeToTT_M4000_W40", "ZPrimeToTT_M4500_W45", "ZPrimeToTT_M5000_W50", "ZPrimeToTT_M6000_W60", "ZPrimeToTT_M7000_W70", "ZPrimeToTT_M8000_W80", "ZPrimeToTT_M9000_W90"};


for(unsigned int k=0; k<year.size(); k++){
  for(unsigned int j=0; j<channel.size(); j++){
    for(unsigned int i=0; i<samples.size(); i++){
      TString filename;
      filename = file_dir + "Chi2_params_" + year.at(k) +"/" + channel.at(j) + "/uhh2.AnalysisModuleRunner.MC." + samples.at(i) + ".root";

      TFile* infile = new TFile(filename, "READ");

      cout << "sample " << samples.at(i) << endl;
   
      TH1F* h_had_ak4  = (TH1F*)infile->Get("CorrectMatchDiscriminator_General/M_tophad_dr_ak4");
      TH1F* h_lep_ak4  = (TH1F*)infile->Get("CorrectMatchDiscriminator_General/M_toplep_dr_ak4");
      TH1F* h_had_ttag = (TH1F*)infile->Get("CorrectMatchDiscriminator_General/M_tophad_dr_ttag");
      TH1F* h_lep_ttag = (TH1F*)infile->Get("CorrectMatchDiscriminator_General/M_toplep_dr_ttag");
   
      vector<TH1F*> hists = {h_had_ak4, h_lep_ak4, h_had_ttag, h_lep_ttag};
      vector<TString> names = {"Mtop_hadronic_AK4", "Mtop_leptonic_AK4", "Mtop_hadronic_TTag", "Mtop_leptonic_TTag"};
      ofstream myfile;
      myfile.open ("files_chi2_parameters/"+year.at(k)+"_"+ channel.at(j) + "_" + samples.at(i) +".txt");
   
      for(unsigned int l=0; l<hists.size(); l++){
        TCanvas* c = new TCanvas("c", "c", 600, 600);
   
        double scale_hist = 1/hists.at(l)->Integral();
        hists.at(l)->Scale(scale_hist);
   
        hists.at(l)->Rebin(4);
   
        hists.at(l)->GetXaxis()->SetRangeUser(100.0,350.0);
        hists.at(l)->GetXaxis()->SetTitle(hists.at(l)->GetTitle());
        hists.at(l)->SetTitle("");
        hists.at(l)->SetMarkerStyle(24);
        hists.at(l)->Draw("P");
   
        TF1 *gaussian_fit = new TF1("gaussian_fit","gaus",150,200);
        hists.at(l)->Fit(gaussian_fit, "R");
        gStyle->SetOptFit(1);

        cout << "histo: " << names.at(l) << " mean " << gaussian_fit->GetParameter(1) << " width " << gaussian_fit->GetParameter(2) << endl; 
        myfile << names.at(l) << " mean " << gaussian_fit->GetParameter(1) << " width " << gaussian_fit->GetParameter(2) << "\n";
   
        c->SaveAs("Plots_chi2/" +  year.at(k) +"_"+ channel.at(j) +"_" +  samples.at(i) +"_"+ names.at(l) + ".pdf");
        delete c;
      }
   
      delete infile;
    }
  }
}

}
