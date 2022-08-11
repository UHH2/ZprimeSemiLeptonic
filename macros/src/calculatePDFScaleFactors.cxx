void calculatePDFScaleFactors(){

  TString input_dir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/UL18/muon/AnalysisDNN_withSyst/";
  TString output_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/";
  TString root_dir = "Zprime_PDFVariations_DNN_output0/";
  TString hist_name = "M_Zprime";

  vector<TString> v_samples = {
    "TTbar",
  };

  // loop over all samples
  for(int i=0; i<v_samples.size(); i++){

    TString sample = v_samples.at(i);
    TFile *input_file = new TFile(input_dir + "uhh2.AnalysisModuleRunner.MC." + sample + ".root", "READ");

    // handle normalization for signal samples later
    

    TH1F *h_nominal = (TH1F*) input_file->Get("DNN_output0_General/M_Zprime_rebin4");
    TH1F *h_up = (TH1F*) h_nominal->Clone();
    TH1F *h_down = (TH1F*) h_nominal->Clone();

    int Nbins = h_nominal->GetNbinsX();
    float sum_bins = 0;

    for(int j=1; j<Nbins+1; j++){ // bin 0 is underflow -> 1...Nbins+1

      float value_nominal = h_nominal->GetBinContent(j);
      float sum_bins = 0;

      for(int k=1; k<101; k++){
        TH1F *h_variation = (TH1F*) input_file->Get(root_dir + hist_name + "_PDF_" + to_string(k));
        float value_variation = h_variation->GetBinContent(j);
        sum_bins += pow(value_variation - value_nominal,2);
      }

      float rms = sqrt(sum_bins/100);
      h_up->SetBinContent(j,value_nominal+rms);
      h_down->SetBinContent(j,value_nominal-rms);
    }

    TFile *output_file = new TFile(output_dir + "uhh2.AnalysisModuleRunner.MC." + sample + ".root", "RECREATE");
    output_file->mkdir("Zprime_SystVariations_DNN_output0");
    output_file->cd("Zprime_SystVariations_DNN_output0");
    h_nominal->SetName(hist_name);
    h_up->SetName(hist_name + "_PDF_up");
    h_down->SetName(hist_name + "_PDF_down");
    h_nominal->Write();
    h_up->Write();
    h_down->Write();
    delete output_file;
  }
}
