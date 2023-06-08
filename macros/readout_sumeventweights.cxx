{

  TString input_basedir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/02_baseline/UL16postVFP_jetvetomaps/";
  // TString input_basedir = "/nfs/dust/cms/group/zprime-uhh/Analysis_UL16postVFP/";

  vector<TString> v_channel = {
    "electron",
    "muon"
  };

  vector<TString> v_samples = {
    "DATA.DATA",
    "MC.TTbar",
    "MC.WJets",
    "MC.ST",
    "MC.DY",
    "MC.QCD",
    "MC.Diboson"
  };


  for(unsigned int i=0; i<v_channel.size(); ++i){
    TString channel = v_channel.at(i);
    cout << "channel: " << channel << endl;

    double sum_event_weights_allSM = 0.0;

    for(unsigned int j=0; j<v_samples.size(); ++j){
      TString sample = v_samples.at(j);
      cout << "sample: " << sample << endl;

      TString filename_in = input_basedir + "/" + channel + "/uhh2.AnalysisModuleRunner." + sample + ".root";
      TFile* file_in = new TFile(filename_in, "READ");
      TH1F *hist = (TH1F*) file_in->Get("nominal/sum_event_weights");
      double sum_event_weights = (double) hist->GetBinContent(1);
      cout << "sum_event_weights: " << sum_event_weights << endl;

      if(sample.BeginsWith("MC.")) sum_event_weights_allSM += sum_event_weights;
    }
    cout << "sum_event_weights (all SM): " << sum_event_weights_allSM << endl;
  }
}
