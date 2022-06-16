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
#include <sstream>
#include <iostream>

using namespace std;

void ExtractSignalNorm(){

  TString file_dir = "/nfs/dust/cms/user/deleokse/RunII_106_v2/Preselection_UL18_TEST_PDF/workdir_Preselection_UL18/";
  vector<TString> year = {"UL16preVFP", "UL16postVFP", "UL17", "UL18"};
  vector<TString> sample_names = {"ZPrimeToTT_M1000_W100_UL18_6"};

//  vector<TString> sample_names = {"ALP_ttbar_signal_UL18", "ALP_ttbar_interference_UL18", "HscalarToTTTo1L1Nu2J_m365_w36p5_res_UL18", "HscalarToTTTo1L1Nu2J_m400_w40p0_res_UL18", "HscalarToTTTo1L1Nu2J_m500_w50p0_res_UL18", "HscalarToTTTo1L1Nu2J_m600_w60p0_res_UL18", "HscalarToTTTo1L1Nu2J_m800_w80p0_res_UL18", "HscalarToTTTo1L1Nu2J_m1000_w100p0_res_UL18", "HscalarToTTTo1L1Nu2J_m365_w36p5_int_UL18", "HscalarToTTTo1L1Nu2J_m400_w40p0_int_UL18", "HscalarToTTTo1L1Nu2J_m500_w50p0_int_UL18", "HscalarToTTTo1L1Nu2J_m600_w60p0_int_UL18", "HscalarToTTTo1L1Nu2J_m800_w80p0_int_UL18", "HscalarToTTTo1L1Nu2J_m1000_w100p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m365_w36p5_res_UL18", "HpseudoToTTTo1L1Nu2J_m400_w40p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m500_w50p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m600_w60p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m800_w80p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m365_w36p5_int_UL18", "HpseudoToTTTo1L1Nu2J_m400_w40p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m500_w50p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m600_w60p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m800_w80p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_UL18", "HscalarToTTTo1L1Nu2J_m365_w91p25_res_UL18", "HscalarToTTTo1L1Nu2J_m400_w100p0_res_UL18", "HscalarToTTTo1L1Nu2J_m500_w125p0_res_UL18", "HscalarToTTTo1L1Nu2J_m600_w150p0_res_UL18", "HscalarToTTTo1L1Nu2J_m800_w200p0_res_UL18", "HscalarToTTTo1L1Nu2J_m1000_w250p0_res_UL18", "HscalarToTTTo1L1Nu2J_m365_w91p25_int_UL18", "HscalarToTTTo1L1Nu2J_m400_w100p0_int_UL18", "HscalarToTTTo1L1Nu2J_m500_w125p0_int_UL18", "HscalarToTTTo1L1Nu2J_m600_w150p0_int_UL18", "HscalarToTTTo1L1Nu2J_m800_w200p0_int_UL18", "HscalarToTTTo1L1Nu2J_m1000_w250p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m365_w91p25_res_UL18", "HpseudoToTTTo1L1Nu2J_m400_w100p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m500_w125p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m600_w150p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m800_w200p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m365_w91p25_int_UL18", "HpseudoToTTTo1L1Nu2J_m400_w100p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m500_w125p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m600_w150p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m800_w200p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_UL18", "HscalarToTTTo1L1Nu2J_m365_w9p125_res_UL18", "HscalarToTTTo1L1Nu2J_m400_w10p0_res_UL18", "HscalarToTTTo1L1Nu2J_m500_w12p5_res_UL18", "HscalarToTTTo1L1Nu2J_m600_w15p0_res_UL18", "HscalarToTTTo1L1Nu2J_m800_w20p0_res_UL18", "HscalarToTTTo1L1Nu2J_m1000_w25p0_res_UL18", "HscalarToTTTo1L1Nu2J_m365_w9p125_int_UL18", "HscalarToTTTo1L1Nu2J_m400_w10p0_int_UL18", "HscalarToTTTo1L1Nu2J_m500_w12p5_int_UL18", "HscalarToTTTo1L1Nu2J_m600_w15p0_int_UL18", "HscalarToTTTo1L1Nu2J_m800_w20p0_int_UL18", "HscalarToTTTo1L1Nu2J_m1000_w25p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m365_w9p125_res_UL18", "HpseudoToTTTo1L1Nu2J_m400_w10p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m500_w12p5_res_UL18", "HpseudoToTTTo1L1Nu2J_m600_w15p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m800_w20p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_UL18", "HpseudoToTTTo1L1Nu2J_m365_w9p125_int_UL18", "HpseudoToTTTo1L1Nu2J_m400_w10p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m500_w12p5_int_UL18", "HpseudoToTTTo1L1Nu2J_m600_w15p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m800_w20p0_int_UL18", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_UL18", "ZPrimeToTT_M400_W40_UL18", "ZPrimeToTT_M500_W50_UL18", "ZPrimeToTT_M600_W60_UL18", "ZPrimeToTT_M700_W70_UL18", "ZPrimeToTT_M800_W80_UL18", "ZPrimeToTT_M900_W90_UL18", "ZPrimeToTT_M1000_W100_UL18", "ZPrimeToTT_M1200_W120_UL18", "ZPrimeToTT_M1400_W140_UL18", "ZPrimeToTT_M1600_W160_UL18", "ZPrimeToTT_M1800_W180_UL18", "ZPrimeToTT_M2000_W200_UL18", "ZPrimeToTT_M2500_W250_UL18", "ZPrimeToTT_M3000_W300_UL18", "ZPrimeToTT_M3500_W350_UL18", "ZPrimeToTT_M4000_W400_UL18", "ZPrimeToTT_M4500_W450_UL18", "ZPrimeToTT_M5000_W500_UL18", "ZPrimeToTT_M6000_W600_UL18", "ZPrimeToTT_M7000_W700_UL18", "ZPrimeToTT_M8000_W800_UL18", "ZPrimeToTT_M9000_W900_UL18", "ZPrimeToTT_M400_W120_UL18", "ZPrimeToTT_M500_W150_UL18", "ZPrimeToTT_M600_W180_UL18", "ZPrimeToTT_M700_W210_UL18", "ZPrimeToTT_M800_W240_UL18", "ZPrimeToTT_M900_W270_UL18", "ZPrimeToTT_M1000_W300_UL18", "ZPrimeToTT_M1200_W360_UL18", "ZPrimeToTT_M1400_W420_UL18", "ZPrimeToTT_M1600_W480_UL18", "ZPrimeToTT_M1800_W540_UL18", "ZPrimeToTT_M2000_W600_UL18", "ZPrimeToTT_M2500_W750_UL18", "ZPrimeToTT_M3000_W900_UL18", "ZPrimeToTT_M3500_W1050_UL18", "ZPrimeToTT_M4000_W1200_UL18", "ZPrimeToTT_M4500_W1350_UL18", "ZPrimeToTT_M5000_W1500_UL18", "ZPrimeToTT_M6000_W1800_UL18", "ZPrimeToTT_M7000_W2100_UL18", "ZPrimeToTT_M8000_W2400_UL18", "ZPrimeToTT_M9000_W2700_UL18", "ZPrimeToTT_M400_W4_UL18", "ZPrimeToTT_M500_W5_UL18", "ZPrimeToTT_M600_W6_UL18", "ZPrimeToTT_M700_W7_UL18", "ZPrimeToTT_M800_W8_UL18", "ZPrimeToTT_M900_W9_UL18", "ZPrimeToTT_M1000_W10_UL18", "ZPrimeToTT_M1200_W12_UL18", "ZPrimeToTT_M1400_W14_UL18", "ZPrimeToTT_M1600_W16_UL18", "ZPrimeToTT_M1800_W18_UL18", "ZPrimeToTT_M2000_W20_UL18", "ZPrimeToTT_M2500_W25_UL18", "ZPrimeToTT_M3000_W30_UL18", "ZPrimeToTT_M3500_W35_UL18", "ZPrimeToTT_M4000_W40_UL18", "ZPrimeToTT_M4500_W45_UL18", "ZPrimeToTT_M5000_W50_UL18", "ZPrimeToTT_M7000_W70_UL18", "ZPrimeToTT_M8000_W80_UL18"};
// ZPrimeToTT_M6000_W60_UL18, ZPrimeToTT_M9000_W90_UL18 missing samples


    for(unsigned int i=0; i<sample_names.size(); i++){
      TString filename;
      filename = file_dir + "/uhh2.AnalysisModuleRunner.MC." + sample_names.at(i) + ".root";
   
      TFile* file_in = new TFile(filename, "READ");
 
      float nominal = ((TH1F*)(file_in->Get("Input_General/sum_event_weights")))->GetBinContent(1); 
      std::ofstream file_out;
      file_out.open("SignalPDFNorm/SignalNorm_"+sample_names.at(i) +".txt");
      //cout << "nominal = " << nominal << endl;

      for(int i = 1; i<101; i++){
         stringstream ss_name;
         ss_name << "Input_General/sum_event_weights_PDF_" << i;
         string s_name = ss_name.str();
         const char* char_name = s_name.c_str();
         float sum_pdf =  ((TH1F*)(file_in->Get(char_name)))->GetBinContent(1);
         //cout << "sum event weights pdf no " << i << "= " << sum_pdf << endl;
         float norm_pdf = nominal / sum_pdf;
         file_out << "pdf" << i << " " << norm_pdf << std::endl;;
      }

      delete file_in;
   
  }

}
