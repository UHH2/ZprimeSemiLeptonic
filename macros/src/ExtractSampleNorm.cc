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

void ExtractSampleNorm(){

  TString file_dir = "/nfs/dust/cms/group/zprime-uhh/Presel_";
  vector<TString> year = {
    "UL16preVFP",
    "UL16postVFP",
    "UL17",
    "UL18"
  };

  vector<TString> sample_names = {
    "TTbar",
    "WJets",
    "ST",
    "QCD",
    "DY",
    // "Diboson",
    // "others",
    "ALP_ttbar_signal",
    "ALP_ttbar_interference",
    "HscalarToTTTo1L1Nu2J_m365_w36p5_res",
    "HscalarToTTTo1L1Nu2J_m400_w40p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w50p0_res",
    "HscalarToTTTo1L1Nu2J_m600_w60p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w80p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w100p0_res",
    "HscalarToTTTo1L1Nu2J_m365_w36p5_int",
    "HscalarToTTTo1L1Nu2J_m400_w40p0_int",
    "HscalarToTTTo1L1Nu2J_m500_w50p0_int",
    "HscalarToTTTo1L1Nu2J_m600_w60p0_int",
    "HscalarToTTTo1L1Nu2J_m800_w80p0_int",
    "HscalarToTTTo1L1Nu2J_m1000_w100p0_int",
    "HpseudoToTTTo1L1Nu2J_m365_w36p5_res",
    "HpseudoToTTTo1L1Nu2J_m400_w40p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w50p0_res",
    "HpseudoToTTTo1L1Nu2J_m600_w60p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w80p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_w36p5_int",
    "HpseudoToTTTo1L1Nu2J_m400_w40p0_int",
    "HpseudoToTTTo1L1Nu2J_m500_w50p0_int",
    "HpseudoToTTTo1L1Nu2J_m600_w60p0_int",
    "HpseudoToTTTo1L1Nu2J_m800_w80p0_int",
    "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int",
    "HscalarToTTTo1L1Nu2J_m365_w91p25_res",
    "HscalarToTTTo1L1Nu2J_m400_w100p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w125p0_res",
    "HscalarToTTTo1L1Nu2J_m600_w150p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w200p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w250p0_res",
    "HscalarToTTTo1L1Nu2J_m365_w91p25_int",
    "HscalarToTTTo1L1Nu2J_m400_w100p0_int",
    "HscalarToTTTo1L1Nu2J_m500_w125p0_int",
    "HscalarToTTTo1L1Nu2J_m600_w150p0_int",
    "HscalarToTTTo1L1Nu2J_m800_w200p0_int",
    "HscalarToTTTo1L1Nu2J_m1000_w250p0_int",
    "HpseudoToTTTo1L1Nu2J_m365_w91p25_res",
    "HpseudoToTTTo1L1Nu2J_m400_w100p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w125p0_res",
    "HpseudoToTTTo1L1Nu2J_m600_w150p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w200p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_w91p25_int",
    "HpseudoToTTTo1L1Nu2J_m400_w100p0_int",
    "HpseudoToTTTo1L1Nu2J_m500_w125p0_int",
    "HpseudoToTTTo1L1Nu2J_m600_w150p0_int",
    "HpseudoToTTTo1L1Nu2J_m800_w200p0_int",
    "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int",
    "HscalarToTTTo1L1Nu2J_m365_w9p125_res",
    "HscalarToTTTo1L1Nu2J_m400_w10p0_res",
    "HscalarToTTTo1L1Nu2J_m500_w12p5_res",
    "HscalarToTTTo1L1Nu2J_m600_w15p0_res",
    "HscalarToTTTo1L1Nu2J_m800_w20p0_res",
    "HscalarToTTTo1L1Nu2J_m1000_w25p0_res",
    "HscalarToTTTo1L1Nu2J_m365_w9p125_int",
    "HscalarToTTTo1L1Nu2J_m400_w10p0_int",
    "HscalarToTTTo1L1Nu2J_m500_w12p5_int",
    "HscalarToTTTo1L1Nu2J_m600_w15p0_int",
    "HscalarToTTTo1L1Nu2J_m800_w20p0_int",
    "HscalarToTTTo1L1Nu2J_m1000_w25p0_int",
    "HpseudoToTTTo1L1Nu2J_m365_w9p125_res",
    "HpseudoToTTTo1L1Nu2J_m400_w10p0_res",
    "HpseudoToTTTo1L1Nu2J_m500_w12p5_res",
    "HpseudoToTTTo1L1Nu2J_m600_w15p0_res",
    "HpseudoToTTTo1L1Nu2J_m800_w20p0_res",
    "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res",
    "HpseudoToTTTo1L1Nu2J_m365_w9p125_int",
    "HpseudoToTTTo1L1Nu2J_m400_w10p0_int",
    "HpseudoToTTTo1L1Nu2J_m500_w12p5_int",
    "HpseudoToTTTo1L1Nu2J_m600_w15p0_int",
    "HpseudoToTTTo1L1Nu2J_m800_w20p0_int",
    "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int",
    "ZPrimeToTT_M400_W40",
    "ZPrimeToTT_M500_W50",
    "ZPrimeToTT_M600_W60",
    "ZPrimeToTT_M700_W70",
    "ZPrimeToTT_M800_W80",
    "ZPrimeToTT_M900_W90",
    "ZPrimeToTT_M1000_W100",
    "ZPrimeToTT_M1200_W120",
    "ZPrimeToTT_M1400_W140",
    "ZPrimeToTT_M1600_W160",
    "ZPrimeToTT_M1800_W180",
    "ZPrimeToTT_M2000_W200",
    "ZPrimeToTT_M2500_W250",
    "ZPrimeToTT_M3000_W300",
    "ZPrimeToTT_M3500_W350",
    "ZPrimeToTT_M4000_W400",
    "ZPrimeToTT_M4500_W450",
    "ZPrimeToTT_M5000_W500",
    "ZPrimeToTT_M6000_W600",
    "ZPrimeToTT_M7000_W700",
    "ZPrimeToTT_M8000_W800",
    "ZPrimeToTT_M9000_W900",
    "ZPrimeToTT_M400_W120",
    "ZPrimeToTT_M500_W150",
    "ZPrimeToTT_M600_W180",
    "ZPrimeToTT_M700_W210",
    "ZPrimeToTT_M800_W240",
    "ZPrimeToTT_M900_W270",
    "ZPrimeToTT_M1000_W300",
    "ZPrimeToTT_M1200_W360",
    "ZPrimeToTT_M1400_W420",
    "ZPrimeToTT_M1600_W480",
    "ZPrimeToTT_M1800_W540",
    "ZPrimeToTT_M2000_W600",
    "ZPrimeToTT_M2500_W750",
    "ZPrimeToTT_M3000_W900",
    "ZPrimeToTT_M3500_W1050",
    "ZPrimeToTT_M4000_W1200",
    "ZPrimeToTT_M4500_W1350",
    "ZPrimeToTT_M5000_W1500",
    "ZPrimeToTT_M6000_W1800",
    "ZPrimeToTT_M7000_W2100",
    "ZPrimeToTT_M8000_W2400",
    "ZPrimeToTT_M9000_W2700",
    "ZPrimeToTT_M400_W4",
    "ZPrimeToTT_M500_W5",
    "ZPrimeToTT_M600_W6",
    "ZPrimeToTT_M700_W7",
    "ZPrimeToTT_M800_W8",
    "ZPrimeToTT_M900_W9",
    "ZPrimeToTT_M1000_W10",
    "ZPrimeToTT_M1200_W12",
    "ZPrimeToTT_M1400_W14",
    "ZPrimeToTT_M1600_W16",
    "ZPrimeToTT_M1800_W18",
    "ZPrimeToTT_M2000_W20",
    "ZPrimeToTT_M2500_W25",
    "ZPrimeToTT_M3000_W30",
    "ZPrimeToTT_M3500_W35",
    "ZPrimeToTT_M4000_W40",
    "ZPrimeToTT_M4500_W45",
    "ZPrimeToTT_M5000_W50",
    "ZPrimeToTT_M6000_W60",
    "ZPrimeToTT_M7000_W70",
    "ZPrimeToTT_M8000_W80",
    "ZPrimeToTT_M9000_W90",
  };
  // vector<TString> sample_names = {"ALP_ttbar_signal", "ALP_ttbar_interference", "HscalarToTTTo1L1Nu2J_m365_w36p5_res", "HscalarToTTTo1L1Nu2J_m400_w40p0_res", "HscalarToTTTo1L1Nu2J_m500_w50p0_res", "HscalarToTTTo1L1Nu2J_m600_w60p0_res", "HscalarToTTTo1L1Nu2J_m800_w80p0_res", "HscalarToTTTo1L1Nu2J_m1000_w100p0_res", "HscalarToTTTo1L1Nu2J_m365_w36p5_int", "HscalarToTTTo1L1Nu2J_m400_w40p0_int", "HscalarToTTTo1L1Nu2J_m500_w50p0_int", "HscalarToTTTo1L1Nu2J_m600_w60p0_int", "HscalarToTTTo1L1Nu2J_m800_w80p0_int", "HscalarToTTTo1L1Nu2J_m1000_w100p0_int", "HpseudoToTTTo1L1Nu2J_m365_w36p5_res", "HpseudoToTTTo1L1Nu2J_m400_w40p0_res", "HpseudoToTTTo1L1Nu2J_m500_w50p0_res", "HpseudoToTTTo1L1Nu2J_m600_w60p0_res", "HpseudoToTTTo1L1Nu2J_m800_w80p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res", "HpseudoToTTTo1L1Nu2J_m365_w36p5_int", "HpseudoToTTTo1L1Nu2J_m400_w40p0_int", "HpseudoToTTTo1L1Nu2J_m500_w50p0_int", "HpseudoToTTTo1L1Nu2J_m600_w60p0_int", "HpseudoToTTTo1L1Nu2J_m800_w80p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int", "HscalarToTTTo1L1Nu2J_m365_w91p25_res", "HscalarToTTTo1L1Nu2J_m400_w100p0_res", "HscalarToTTTo1L1Nu2J_m500_w125p0_res", "HscalarToTTTo1L1Nu2J_m600_w150p0_res", "HscalarToTTTo1L1Nu2J_m800_w200p0_res", "HscalarToTTTo1L1Nu2J_m1000_w250p0_res", "HscalarToTTTo1L1Nu2J_m365_w91p25_int", "HscalarToTTTo1L1Nu2J_m400_w100p0_int", "HscalarToTTTo1L1Nu2J_m500_w125p0_int", "HscalarToTTTo1L1Nu2J_m600_w150p0_int", "HscalarToTTTo1L1Nu2J_m800_w200p0_int", "HscalarToTTTo1L1Nu2J_m1000_w250p0_int", "HpseudoToTTTo1L1Nu2J_m365_w91p25_res", "HpseudoToTTTo1L1Nu2J_m400_w100p0_res", "HpseudoToTTTo1L1Nu2J_m500_w125p0_res", "HpseudoToTTTo1L1Nu2J_m600_w150p0_res", "HpseudoToTTTo1L1Nu2J_m800_w200p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res", "HpseudoToTTTo1L1Nu2J_m365_w91p25_int", "HpseudoToTTTo1L1Nu2J_m400_w100p0_int", "HpseudoToTTTo1L1Nu2J_m500_w125p0_int", "HpseudoToTTTo1L1Nu2J_m600_w150p0_int", "HpseudoToTTTo1L1Nu2J_m800_w200p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int", "HscalarToTTTo1L1Nu2J_m365_w9p125_res", "HscalarToTTTo1L1Nu2J_m400_w10p0_res", "HscalarToTTTo1L1Nu2J_m500_w12p5_res", "HscalarToTTTo1L1Nu2J_m600_w15p0_res", "HscalarToTTTo1L1Nu2J_m800_w20p0_res", "HscalarToTTTo1L1Nu2J_m1000_w25p0_res", "HscalarToTTTo1L1Nu2J_m365_w9p125_int", "HscalarToTTTo1L1Nu2J_m400_w10p0_int", "HscalarToTTTo1L1Nu2J_m500_w12p5_int", "HscalarToTTTo1L1Nu2J_m600_w15p0_int", "HscalarToTTTo1L1Nu2J_m800_w20p0_int", "HscalarToTTTo1L1Nu2J_m1000_w25p0_int", "HpseudoToTTTo1L1Nu2J_m365_w9p125_res", "HpseudoToTTTo1L1Nu2J_m400_w10p0_res", "HpseudoToTTTo1L1Nu2J_m500_w12p5_res", "HpseudoToTTTo1L1Nu2J_m600_w15p0_res", "HpseudoToTTTo1L1Nu2J_m800_w20p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res", "HpseudoToTTTo1L1Nu2J_m365_w9p125_int", "HpseudoToTTTo1L1Nu2J_m400_w10p0_int", "HpseudoToTTTo1L1Nu2J_m500_w12p5_int", "HpseudoToTTTo1L1Nu2J_m600_w15p0_int", "HpseudoToTTTo1L1Nu2J_m800_w20p0_int", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int", "ZPrimeToTT_M400_W40", "ZPrimeToTT_M500_W50", "ZPrimeToTT_M600_W60", "ZPrimeToTT_M700_W70", "ZPrimeToTT_M800_W80", "ZPrimeToTT_M900_W90", "ZPrimeToTT_M1000_W100", "ZPrimeToTT_M1200_W120", "ZPrimeToTT_M1400_W140", "ZPrimeToTT_M1600_W160", "ZPrimeToTT_M1800_W180", "ZPrimeToTT_M2000_W200", "ZPrimeToTT_M2500_W250", "ZPrimeToTT_M3000_W300", "ZPrimeToTT_M3500_W350", "ZPrimeToTT_M4000_W400", "ZPrimeToTT_M4500_W450", "ZPrimeToTT_M5000_W500", "ZPrimeToTT_M6000_W600", "ZPrimeToTT_M7000_W700", "ZPrimeToTT_M8000_W800", "ZPrimeToTT_M9000_W900", "ZPrimeToTT_M400_W120", "ZPrimeToTT_M500_W150", "ZPrimeToTT_M600_W180", "ZPrimeToTT_M700_W210", "ZPrimeToTT_M800_W240", "ZPrimeToTT_M900_W270", "ZPrimeToTT_M1000_W300", "ZPrimeToTT_M1200_W360", "ZPrimeToTT_M1400_W420", "ZPrimeToTT_M1600_W480", "ZPrimeToTT_M1800_W540", "ZPrimeToTT_M2000_W600", "ZPrimeToTT_M2500_W750", "ZPrimeToTT_M3000_W900", "ZPrimeToTT_M3500_W1050", "ZPrimeToTT_M4000_W1200", "ZPrimeToTT_M4500_W1350", "ZPrimeToTT_M5000_W1500", "ZPrimeToTT_M6000_W1800", "ZPrimeToTT_M7000_W2100", "ZPrimeToTT_M8000_W2400", "ZPrimeToTT_M9000_W2700", "ZPrimeToTT_M400_W4", "ZPrimeToTT_M500_W5", "ZPrimeToTT_M600_W6", "ZPrimeToTT_M700_W7", "ZPrimeToTT_M800_W8", "ZPrimeToTT_M900_W9", "ZPrimeToTT_M1000_W10", "ZPrimeToTT_M1200_W12", "ZPrimeToTT_M1400_W14", "ZPrimeToTT_M1600_W16", "ZPrimeToTT_M1800_W18", "ZPrimeToTT_M2000_W20", "ZPrimeToTT_M2500_W25", "ZPrimeToTT_M3000_W30", "ZPrimeToTT_M3500_W35", "ZPrimeToTT_M4000_W40", "ZPrimeToTT_M4500_W45", "ZPrimeToTT_M5000_W50", "ZPrimeToTT_M6000_W60", "ZPrimeToTT_M7000_W70", "ZPrimeToTT_M8000_W80", "ZPrimeToTT_M9000_W90"};

  vector<bool> isSignalInt (sample_names.size(), false);

  for(unsigned int j=0; j<year.size(); j++){
    cout << "year: " << year.at(j) << endl;

    for(unsigned int i=0; i<sample_names.size(); i++){
      cout << sample_names.at(i) << endl;

      TString filename;
      filename = file_dir  + year.at(j) + "/uhh2.AnalysisModuleRunner.MC." + sample_names.at(i) + ".root";
      //cout << "filename : " << filename << endl;

      TFile* file_in = new TFile(filename, "READ");

      isSignalInt.at(i) = ( (sample_names.at(i).Index("Hpseudo") == 0 && sample_names.at(i).Index("_int") != -1 ) || (sample_names.at(i).Index("Hscalar") == 0 && sample_names.at(i).Index("_int") != -1 ) );

      float nominal = ((TH1F*)(file_in->Get("Input_General/sum_event_weights")))->GetBinContent(1);
      std::ofstream file_out;
      std::ofstream file_out_copy;
      if(!isSignalInt.at(i)) file_out.open("SamplePDFNorm/" + year.at(j) +  "/SampleNorm_" + sample_names.at(i) + ".txt");
      else{
        file_out.open("SamplePDFNorm/" + year.at(j) +  "/SampleNorm_" + sample_names.at(i) + "_pos.txt");
        file_out_copy.open("SamplePDFNorm/" + year.at(j) +  "/SampleNorm_" + sample_names.at(i) + "_neg.txt");
      }

      //cout << "nominal = " << nominal << endl;

      for(int i = 1; i<101; i++){
        stringstream ss_name;
        ss_name << "Input_General/sum_event_weights_PDF_" << i;
        string s_name = ss_name.str();
        const char* char_name = s_name.c_str();
        float sum_pdf =  ((TH1F*)(file_in->Get(char_name)))->GetBinContent(1);
        //cout << "sum event weights pdf no " << i << "= " << sum_pdf << endl;
        float norm_pdf = nominal / sum_pdf;
        file_out << "pdf" << i << " " << norm_pdf << std::endl;
        file_out_copy << "pdf" << i << " " << norm_pdf << std::endl;
      }

      delete file_in;

    }
  }

}
