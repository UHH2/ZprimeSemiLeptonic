#include <iostream>
using namespace std;

// input base dir
// the folder structure is exected like this: *_year/channel/
TString input_base_dir = "/nfs/dust/cms/group/zprime-uhh/Analysis_";

// years
vector<TString> v_years = {
  // "UL16preVFP",
  // "UL16postVFP",
  "UL17",
  // "UL18"
};

// channels
vector<TString> v_channels = {
  // "electron",
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
};

// systematics

void prepare_combine_input(){
  cout << "starting..." << endl;

  for(unsigned int a=0; a<v_years.size(); ++a){ // year loop
    TString year = v_years.at(a);
    cout << "year: " << year << endl;

    for(unsigned int b=0; b<v_channels.size(); ++b){ // channel loop
      TString channel = v_channels.at(b);
      cout << "channel: " << channel << endl;

      TFile *output_file;
      output_file = new TFile(year + "/" + channel + "/input_histograms_combine.root", "RECREATE");

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
          else if(dir_name.EndsWith("_up")) is_up_variation = true;
          else if(dir_name.EndsWith("_down")) is_down_variation = true;
          else if(dir_name == "murmuf_upup") is_murmuf_upup = true;
          else if(dir_name == "murmuf_upnone") is_murmuf_upnone = true;
          else if(dir_name == "murmuf_noneup") is_murmuf_noneup = true;
          else if(dir_name == "murmuf_nonedown") is_murmuf_nonedown = true;
          else if(dir_name == "murmuf_downnone") is_murmuf_downnone = true;
          else if(dir_name == "murmuf_downdown") is_murmuf_downdown = true;
          else if(dir_name.BeginsWith("pdf")) is_pdf = true;

          input_file->cd(dir_name);

          TH1F *hist;
          TKey *hist_key;
          TIter next_hist(gDirectory->GetListOfKeys());

          if(is_nominal){
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

        // output_file = TFile::Open(year + "/" + channel + "/input_histograms_combine.root", "UPDATE");
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
