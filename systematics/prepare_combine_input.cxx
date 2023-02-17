#include <iostream>
using namespace std;

// choose: after_preselection, after_baseline_selection, after_dnn
TString analysis_step = "after_baseline_selection";

// input base dir: the folder structure is exected like this: *year/channel/
TString input_base_dir = "/nfs/dust/cms/group/zprime-uhh/";

// years
vector<TString> v_years = {
  // "UL16preVFP",
  // "UL16postVFP",
  "UL17",
  // "UL18"
};

// channels
vector<TString> v_channels = {
  "electron",
  "muon"
};

// samples
vector<TString> v_samples = {
  "DATA",
  "TTbar",
  "WJets",
  "ST",
  "DY",
  "Diboson",
  "QCD",
  "ALP_ttbar_signal",
  "ALP_ttbar_interference",
  // "HpseudoToTTTo1L1Nu2J_m365_w91p25_res",
  // "HpseudoToTTTo1L1Nu2J_m400_w100p0_res",
  "HpseudoToTTTo1L1Nu2J_m500_w125p0_res",
  // "HpseudoToTTTo1L1Nu2J_m600_w150p0_res",
  // "HpseudoToTTTo1L1Nu2J_m800_w200p0_res",
  "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res",
  // "HpseudoToTTTo1L1Nu2J_m365_w36p5_res",
  // "HpseudoToTTTo1L1Nu2J_m400_w40p0_res",
  // "HpseudoToTTTo1L1Nu2J_m500_w50p0_res",
  // "HpseudoToTTTo1L1Nu2J_m600_w60p0_res",
  // "HpseudoToTTTo1L1Nu2J_m800_w80p0_res",
  // "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res",
  // "HpseudoToTTTo1L1Nu2J_m365_w9p125_res",
  // "HpseudoToTTTo1L1Nu2J_m400_w10p0_res",
  // "HpseudoToTTTo1L1Nu2J_m500_w12p5_res",
  // "HpseudoToTTTo1L1Nu2J_m600_w15p0_res",
  // "HpseudoToTTTo1L1Nu2J_m800_w20p0_res",
  // "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res",
  // "HpseudoToTTTo1L1Nu2J_m365_w91p25_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m400_w100p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m500_w125p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m600_w150p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m800_w200p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m365_w91p25_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m400_w100p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m500_w125p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m600_w150p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m800_w200p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m365_w36p5_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m400_w40p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m500_w50p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m600_w60p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m800_w80p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m365_w36p5_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m400_w40p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m500_w50p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m600_w60p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m800_w80p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m365_w9p125_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m400_w10p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m500_w12p5_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m600_w15p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m800_w20p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_pos",
  // "HpseudoToTTTo1L1Nu2J_m365_w9p125_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m400_w10p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m500_w12p5_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m600_w15p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m800_w20p0_int_neg",
  // "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m365_w91p25_res",
  // "HscalarToTTTo1L1Nu2J_m400_w100p0_res",
  "HscalarToTTTo1L1Nu2J_m500_w125p0_res",
  // "HscalarToTTTo1L1Nu2J_m600_w150p0_res",
  // "HscalarToTTTo1L1Nu2J_m800_w200p0_res",
  "HscalarToTTTo1L1Nu2J_m1000_w250p0_res",
  // "HscalarToTTTo1L1Nu2J_m365_w36p5_res",
  // "HscalarToTTTo1L1Nu2J_m400_w40p0_res",
  // "HscalarToTTTo1L1Nu2J_m500_w50p0_res",
  // "HscalarToTTTo1L1Nu2J_m600_w60p0_res",
  // "HscalarToTTTo1L1Nu2J_m800_w80p0_res",
  // "HscalarToTTTo1L1Nu2J_m1000_w100p0_res",
  // "HscalarToTTTo1L1Nu2J_m365_w9p125_res",
  // "HscalarToTTTo1L1Nu2J_m400_w10p0_res",
  // "HscalarToTTTo1L1Nu2J_m500_w12p5_res",
  // "HscalarToTTTo1L1Nu2J_m600_w15p0_res",
  // "HscalarToTTTo1L1Nu2J_m800_w20p0_res",
  // "HscalarToTTTo1L1Nu2J_m1000_w25p0_res",
  // "HscalarToTTTo1L1Nu2J_m365_w91p25_int_pos",
  // "HscalarToTTTo1L1Nu2J_m400_w100p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m500_w125p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m600_w150p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m800_w200p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m1000_w250p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m365_w91p25_int_neg",
  // "HscalarToTTTo1L1Nu2J_m400_w100p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m500_w125p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m600_w150p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m800_w200p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m1000_w250p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m365_w36p5_int_pos",
  // "HscalarToTTTo1L1Nu2J_m400_w40p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m500_w50p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m600_w60p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m800_w80p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m1000_w100p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m365_w36p5_int_neg",
  // "HscalarToTTTo1L1Nu2J_m400_w40p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m500_w50p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m600_w60p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m800_w80p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m1000_w100p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m365_w9p125_int_pos",
  // "HscalarToTTTo1L1Nu2J_m400_w10p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m500_w12p5_int_pos",
  // "HscalarToTTTo1L1Nu2J_m600_w15p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m800_w20p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m1000_w25p0_int_pos",
  // "HscalarToTTTo1L1Nu2J_m365_w9p125_int_neg",
  // "HscalarToTTTo1L1Nu2J_m400_w10p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m500_w12p5_int_neg",
  // "HscalarToTTTo1L1Nu2J_m600_w15p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m800_w20p0_int_neg",
  // "HscalarToTTTo1L1Nu2J_m1000_w25p0_int_neg",
  "RSGluonToTT_M-500",
  "RSGluonToTT_M-1000",
  // "RSGluonToTT_M-1500",
  // "RSGluonToTT_M-2000",
  // "RSGluonToTT_M-2500",
  // "RSGluonToTT_M-3000",
  // "RSGluonToTT_M-3500",
  // "RSGluonToTT_M-4000",
  // "RSGluonToTT_M-4500",
  // "RSGluonToTT_M-5000",
  // "RSGluonToTT_M-5500",
  // "RSGluonToTT_M-6000",
  // "ZPrimeToTT_M400_W40",
  "ZPrimeToTT_M500_W50",
  // "ZPrimeToTT_M600_W60",
  // "ZPrimeToTT_M700_W70",
  // "ZPrimeToTT_M800_W80",
  // "ZPrimeToTT_M900_W90",
  "ZPrimeToTT_M1000_W100",
  // "ZPrimeToTT_M1200_W120",
  // "ZPrimeToTT_M1400_W140",
  // "ZPrimeToTT_M1600_W160",
  // "ZPrimeToTT_M1800_W180",
  // "ZPrimeToTT_M2000_W200",
  // "ZPrimeToTT_M2500_W250",
  // "ZPrimeToTT_M3000_W300",
  // "ZPrimeToTT_M3500_W350",
  // "ZPrimeToTT_M4000_W400",
  // "ZPrimeToTT_M4500_W450",
  // "ZPrimeToTT_M5000_W500",
  // "ZPrimeToTT_M6000_W600",
  // "ZPrimeToTT_M7000_W700",
  // "ZPrimeToTT_M8000_W800",
  // "ZPrimeToTT_M9000_W900",
  // "ZPrimeToTT_M400_W120",
  // "ZPrimeToTT_M500_W150",
  // "ZPrimeToTT_M600_W180",
  // "ZPrimeToTT_M700_W210",
  // "ZPrimeToTT_M800_W240",
  // "ZPrimeToTT_M900_W270",
  // "ZPrimeToTT_M1000_W300",
  // "ZPrimeToTT_M1200_W360",
  // "ZPrimeToTT_M1400_W420",
  // "ZPrimeToTT_M1600_W480",
  // "ZPrimeToTT_M1800_W540",
  // "ZPrimeToTT_M2000_W600",
  // "ZPrimeToTT_M2500_W750",
  // "ZPrimeToTT_M3000_W900",
  // "ZPrimeToTT_M3500_W1050",
  // "ZPrimeToTT_M4000_W1200",
  // "ZPrimeToTT_M4500_W1350",
  // "ZPrimeToTT_M5000_W1500",
  // "ZPrimeToTT_M6000_W1800",
  // "ZPrimeToTT_M7000_W2100",
  // "ZPrimeToTT_M8000_W2400",
  // "ZPrimeToTT_M9000_W2700",
  // "ZPrimeToTT_M400_W4",
  // "ZPrimeToTT_M500_W5",
  // "ZPrimeToTT_M600_W6",
  // "ZPrimeToTT_M700_W7",
  // "ZPrimeToTT_M800_W8",
  // "ZPrimeToTT_M900_W9",
  // "ZPrimeToTT_M1000_W10",
  // "ZPrimeToTT_M1200_W12",
  // "ZPrimeToTT_M1400_W14",
  // "ZPrimeToTT_M1600_W16",
  // "ZPrimeToTT_M1800_W18",
  // "ZPrimeToTT_M2000_W20",
  // "ZPrimeToTT_M2500_W25",
  // "ZPrimeToTT_M3000_W30",
  // "ZPrimeToTT_M3500_W35",
  // "ZPrimeToTT_M4000_W40",
  // "ZPrimeToTT_M4500_W45",
  // "ZPrimeToTT_M5000_W50",
  // "ZPrimeToTT_M6000_W60",
  // "ZPrimeToTT_M7000_W70",
  // "ZPrimeToTT_M8000_W80",
  // "ZPrimeToTT_M9000_W90",
};

// systematics
void prepare_combine_input(){
  cout << "starting..." << endl;

  if(analysis_step == "after_preselection") input_base_dir += "Presel_";
  else if(analysis_step == "after_baseline_selection") input_base_dir += "Analysis_";
  else if(analysis_step == "after_dnn") input_base_dir += "AnalysisDNN_";
  else throw runtime_error("no allowed analysis step");

  for(unsigned int a=0; a<v_years.size(); ++a){ // year loop
    TString year = v_years.at(a);
    cout << "year: " << year << endl;

    for(unsigned int b=0; b<v_channels.size(); ++b){ // channel loop
      TString channel = v_channels.at(b);
      cout << "channel: " << channel << endl;

      TFile *output_file;
      output_file = new TFile(year + "/" + channel + "/combine_input_" + analysis_step + ".root", "RECREATE");

      for(unsigned int c=0; c<v_samples.size(); ++c){ // sample loop
        vector<TH1F*> v_hists;
        TString sample = v_samples.at(c);
        cout << sample << endl;

        TString file_prefix = "uhh2.AnalysisModuleRunner.";
        if(sample == "DATA") file_prefix += "DATA.";
        else file_prefix += "MC.";

        TFile *input_file = TFile::Open(input_base_dir + year + "/" + channel + "/" + file_prefix + sample + ".root");

        vector<TH1F*> v_nominal;
        vector<TH1F*> v_murmuf_upup, v_murmuf_upnone, v_murmuf_noneup, v_murmuf_nonedown, v_murmuf_downnone, v_murmuf_downdown;
        vector<TH1F*> v_pdf;

        TObject *dir;
        TKey *dir_key;
        TIter next_dir(input_file->GetListOfKeys());
        while((dir_key = (TKey *) next_dir())){ // root subdir loop
          dir = input_file->Get(dir_key->GetName());
          TString dir_name = dir->GetName();

          bool is_nominal = false;
          bool is_multiclass_nn = false;
          bool is_up_variation = false;
          bool is_down_variation = false;
          bool is_murmuf_upup = false;
          bool is_murmuf_upnone = false;
          bool is_murmuf_noneup = false;
          bool is_murmuf_nonedown = false;
          bool is_murmuf_downnone = false;
          bool is_murmuf_downdown = false;
          bool is_pdf = false;

          if(dir_name == "nominal") is_nominal = true;
          else if(dir_name == "MulticlassNN") is_multiclass_nn = true;
          else if(dir_name.EndsWith("_up")) is_up_variation = true;
          else if(dir_name.EndsWith("_down")) is_down_variation = true;
          else if(dir_name == "murmuf_upup") is_murmuf_upup = true;
          else if(dir_name == "murmuf_upnone") is_murmuf_upnone = true;
          else if(dir_name == "murmuf_noneup") is_murmuf_noneup = true;
          else if(dir_name == "murmuf_nonedown") is_murmuf_nonedown = true;
          else if(dir_name == "murmuf_downnone") is_murmuf_downnone = true;
          else if(dir_name == "murmuf_downdown") is_murmuf_downdown = true;
          else if(dir_name.BeginsWith("pdf")) is_pdf = true;
          else if(dir_name == "uhh2_meta" || dir_name == "AnalysisTree") continue; // skip if in case hadded files have tree

          input_file->cd(dir_name);

          TH1F *hist;
          TKey *hist_key;
          TIter next_hist(gDirectory->GetListOfKeys());

          if(is_nominal || is_multiclass_nn){
            // cout << "nominal" << endl;
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              TString hist_name = hist->GetName();
              hist->SetName(hist_name + "_" + sample);
              v_nominal.push_back(hist);
              v_hists.push_back(hist);
            }
          }
          else if(is_up_variation){ // simple up variation
            // cout << "up variations" << endl;
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              TString hist_name = hist->GetName();
              hist->SetName(hist_name + "_" + sample + "_" + dir_name.ReplaceAll("_up", "Up"));
              v_hists.push_back(hist);
            }
          }
          else if(is_down_variation){ // simple down variation
            // cout << "down variations" << endl;
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              TString hist_name = hist->GetName();
              hist->SetName(hist_name + "_" + sample + "_" + dir_name.ReplaceAll("_down", "Down"));
              v_hists.push_back(hist);
            }
          }
          else if(is_murmuf_upup){
            // cout << "mcscale" << endl;
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              v_murmuf_upup.push_back(hist);
            }
          }
          else if(is_murmuf_upnone){
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              v_murmuf_upnone.push_back(hist);
            }
          }
          else if(is_murmuf_noneup){
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              v_murmuf_noneup.push_back(hist);
            }
          }
          else if(is_murmuf_nonedown){
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              v_murmuf_nonedown.push_back(hist);
            }
          }
          else if(is_murmuf_downnone){
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              v_murmuf_downnone.push_back(hist);
            }
          }
          else if(is_murmuf_downdown){
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              v_murmuf_downdown.push_back(hist);
            }
          }
          else if(is_pdf){
            // cout << "pdf" << endl;
            while((hist_key = (TKey *) next_hist())){ // hist loop
              hist = (TH1F*) gDirectory->Get(hist_key->GetName());
              v_pdf.push_back(hist);
            }
          }
          else {
            continue;
          }
        }

        // mscale: envelope (to do: later factor out normalization)
        for(unsigned int i=0; i<v_murmuf_upup.size(); ++i){ // hist loop
          vector<TH1F*> v_murmuf_variations;
          v_murmuf_variations.push_back(v_murmuf_upup.at(i));
          v_murmuf_variations.push_back(v_murmuf_upnone.at(i));
          v_murmuf_variations.push_back(v_murmuf_noneup.at(i));
          v_murmuf_variations.push_back(v_murmuf_nonedown.at(i));
          v_murmuf_variations.push_back(v_murmuf_downnone.at(i));
          v_murmuf_variations.push_back(v_murmuf_downdown.at(i));

          TH1F *hist_mcscaleUp = (TH1F*) v_murmuf_variations.at(0)->Clone();
          TH1F *hist_mcscaleDown = (TH1F*) v_murmuf_variations.at(0)->Clone();
          for(unsigned int j=0; j<hist_mcscaleUp->GetNbinsX()+2; ++j){ // bin loop
            float max = 0.;
            float min = 10000000000.;
            for(unsigned int k=0; k<v_murmuf_variations.size(); ++k){ // variation loop
              float bin_content = v_murmuf_variations.at(k)->GetBinContent(j);
              if(bin_content > max) max = bin_content;
              if(bin_content < min) min = bin_content;
            }
            hist_mcscaleUp->SetBinContent(j, max);
            hist_mcscaleDown->SetBinContent(j, min);
          }
          TString hist_name = hist_mcscaleUp->GetName();
          hist_mcscaleUp->SetName(hist_name + "_" + sample + "_mcscaleUp");
          hist_mcscaleDown->SetName(hist_name + "_" + sample + "_mcscaleDown");
          v_hists.push_back(hist_mcscaleUp);
          v_hists.push_back(hist_mcscaleDown);
        }

        // pdf: root mean square of all 100 variations (to do: add normalization)
        int n_hists = v_pdf.size()/100; // = 546
        for(unsigned int i=0; i<n_hists; ++i){ // hist loop
          TH1F *hist_pdfUp = (TH1F*) v_pdf.at(i)->Clone();
          TH1F *hist_pdfDown = (TH1F*) v_pdf.at(i)->Clone();

          for(unsigned int j=0; j<hist_pdfUp->GetNbinsX()+2; ++j){ // bin loop
            float nominal_bin_content = v_nominal.at(i)->GetBinContent(j);
            float sum_bins = 0.;

            for(unsigned int k=0; k<100; ++k){ // variation loop
              float bin_content = v_pdf.at(k * n_hists + i)->GetBinContent(j);
              // to do: multiply with normalization factor here
              sum_bins += pow(bin_content - nominal_bin_content, 2);
            }
            float rms = sqrt(sum_bins / 100);
            hist_pdfUp->SetBinContent(j, nominal_bin_content + rms);
            hist_pdfDown->SetBinContent(j, nominal_bin_content - rms);
          }
          TString hist_name = hist_pdfUp->GetName();
          hist_pdfUp->SetName(hist_name + "_" + sample + "_pdfUp");
          hist_pdfDown->SetName(hist_name + "_" + sample + "_pdfDown");
          v_hists.push_back(hist_pdfUp);
          v_hists.push_back(hist_pdfDown);
        }

        output_file->cd();
        for(unsigned int i=0; i<v_hists.size(); ++i) v_hists.at(i)->Write();
      } // end sample loop
      output_file->Close();
    } // end channel loop
  } // end year loop
  cout << "done!" << endl;
  cout << "if root does not manage to end this script properly (might happen after writing lots of histograms) simply end it manually via: control + Z" << endl;
  return;
}
