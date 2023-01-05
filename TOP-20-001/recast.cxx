{

  // TODO: adapt for more observables
  // vector<TString> v_HEPDatas = {
  //   "parton_abs_ttm",
  // };
  // vector<TString> v_inputnames = {
  //   "m_ttbar",
  // };
  // vector<TString> v_outputnames = {
  //   "mtt",
  // };


  // MC
  TString inputdir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/fullRun2/TOP-20-001/";
  TString outputdir_diffxsec = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/TOP-20-001/output_diffxsec/";
  TString outputdir_Nevents = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/TOP-20-001/output_Nevents/";
  TString outputdir_combine = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/TOP-20-001/output_combine/";
  TString rootdir_hist = "ttgenhists/";
  TString rootdir_syst = "SystematicsHists/";
  TString rootdir_pdf = "PDFHists/";
  vector<TString> v_systnames = {
    "pu_up",
    "pu_down",
    "murmuf_upup",
    "murmuf_upnone",
    "murmuf_noneup",
    "murmuf_nonedown",
    "murmuf_downnone",
    "murmuf_downdown",
    "isr_up",
    "isr_down",
    "fsr_up",
    "fsr_down"
  };
  vector<TString> v_samplenames = {
    "TTToSemiLeptonic",
    "ALP_ttbar_signal",
    "ALP_ttbar_interference"
  };
  vector<double> v_scales = { // xsec / # weighted events
    831.76 * 0.438 / (39046225860.2 + 42833982385.9 + 1.04665737783e+11 + 1.40602835351e+11),
    7.048 / (5308000.0 + 4528000.0 + 9802000.0 + 9493000.0),
    -28.248020 / (5398990.0 + 4540996.0 + 9831978.0 + 9617976.0) // (-1) makes interference positive here -> easier to treat
  };

  double target_lumi = 137620;

  TString HEPDataname = "parton_abs_ttm";
  TString inputname = "m_ttbar";
  TString outputname = "mtt";

  // DATA
  // diff xsec
  vector<TString> v_histnames_data = {"Hist1D_y1", "Hist1D_y1_e1", "Hist1D_y1_e2"};
  vector<TH1D*> v_datahists;
  TFile *inputfile_data = TFile::Open("HEPData/HEPData-ins1901295-v1-" + HEPDataname + ".root");
  inputfile_data->cd(HEPDataname);
  for(int i=0; i<v_histnames_data.size(); ++i){
    TH1D *datahist = (TH1D*) gDirectory->Get(v_histnames_data.at(i));
    if(v_histnames_data.at(i).Contains("e1")) datahist->SetName(outputname + "_errStat");
    else if(v_histnames_data.at(i).Contains("e2")) datahist->SetName(outputname + "_errSyst");
    else datahist->SetName(outputname);
    v_datahists.push_back(datahist);
  }
  TFile *outputfile_data_diffxsec = new TFile(outputdir_diffxsec + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "RECREATE");
  outputfile_data_diffxsec->cd();
  for(int i=0; i<v_datahists.size(); ++i) v_datahists.at(i)->Write();
  outputfile_data_diffxsec->Close();

  // scaled to Nevents
  vector<TH1D*> v_datahists_Nevents;
  for(int i=0; i<v_datahists.size(); ++i){
    TH1D *datahist_Nevents = (TH1D*) v_datahists.at(i)->Clone();
    datahist_Nevents->Scale(target_lumi);
    for(int i=0; i<datahist_Nevents->GetNbinsX(); ++i) datahist_Nevents->SetBinContent(i+1, datahist_Nevents->GetBinContent(i+1) * datahist_Nevents->GetXaxis()->GetBinWidth(i+1));
    datahist_Nevents->GetYaxis()->SetTitle("Nevents");
    v_datahists_Nevents.push_back(datahist_Nevents);
  }
  TFile *outputfile_data_Nevents = new TFile(outputdir_Nevents + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "RECREATE");
  outputfile_data_Nevents->cd();
  for(int i=0; i<v_datahists_Nevents.size(); ++i) v_datahists_Nevents.at(i)->Write();
  outputfile_data_Nevents->Close();

  // prepare for combine
  TH1D *datahist_combine = (TH1D*) v_datahists_Nevents.at(0)->Clone();
  for(int i=0; i<datahist_combine->GetNbinsX(); ++i){
    double statError = v_datahists_Nevents.at(1)->GetBinContent(i+1);
    double systError = v_datahists_Nevents.at(2)->GetBinContent(i+1);
    double totalError = sqrt(pow(statError, 2) + pow(systError, 2));
    datahist_combine->SetBinError(i+1, totalError);
  }
  TFile * outputfile_data_combine = new TFile(outputdir_combine + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "RECREATE");
  outputfile_data_combine->cd();
  datahist_combine->Write();
  outputfile_data_combine->Close();



  // MC
  for(int j=0; j<v_samplenames.size(); ++j){
    // diff xsec
    TFile *inputfile = TFile::Open(inputdir + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root");
    TH1D *hist = (TH1D*) gDirectory->Get(rootdir_hist + inputname);
    hist->Scale(v_scales.at(j), "width");
    hist->SetName(outputname);
    double Nbins = hist->GetNbinsX();
    vector<TH1D*> v_hists;

    // for TTbar: take statistical error from DATA + apply systematics from DATA
    if(j==0){
      for(int i=0; i<Nbins; ++i) hist->SetBinError(i+1, v_datahists.at(1)->GetBinError(i+1)); // for TTbar: take statistical error from DATA
      TH1D *hist_dataSystUp = (TH1D*) hist->Clone();
      TH1D *hist_dataSystDown = (TH1D*) hist->Clone();
      hist_dataSystUp->SetName(outputname + "_datasyst_up");
      hist_dataSystDown->SetName(outputname + "_datasyst_down");
      hist_dataSystUp->Add(v_datahists.at(1), +1);
      hist_dataSystDown->Add(v_datahists.at(1), -1);
      v_hists.push_back(hist);
      v_hists.push_back(hist_dataSystUp);
      v_hists.push_back(hist_dataSystDown);
    }
    else{
      v_hists.push_back(hist);
    }

    // systematics
    for(int i=0; i<v_systnames.size(); ++i){
      TH1D *syst = (TH1D*) gDirectory->Get(rootdir_syst + outputname + "_" + v_systnames.at(i));
      syst->Scale(v_scales.at(j), "width");
      v_hists.push_back(syst);
    }

    // PDFs
    for(int i=1; i<101; ++i){
      TH1D *pdf = (TH1D*) gDirectory->Get(rootdir_pdf + outputname + "_PDF_" + i);
      pdf->Scale(v_scales.at(j), "width");
      v_hists.push_back(pdf);
    }

    TFile *outputfile_diffxsec = TFile::Open(outputdir_diffxsec + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "RECREATE");
    outputfile_diffxsec->cd();
    for(int i=0; i<v_hists.size(); ++i) v_hists.at(i)->Write();
    outputfile_diffxsec->Close();

    // scaled to Nevents
    vector<TH1D*> v_hists_Nevents;
    for(int i=0; i<v_hists.size(); ++i){
      TH1D *hist_Nevents = (TH1D*) v_hists.at(i)->Clone();
      hist_Nevents->Scale(target_lumi);
      for(int h=0; h<hist_Nevents->GetNbinsX(); ++h){
        hist_Nevents->SetBinContent(h+1, hist_Nevents->GetBinContent(h+1) * hist_Nevents->GetXaxis()->GetBinWidth(h+1));
        hist_Nevents->SetBinError(h+1, hist_Nevents->GetBinError(h+1) * hist_Nevents->GetXaxis()->GetBinWidth(h+1));
      }
      v_hists_Nevents.push_back(hist_Nevents);
    }
    TFile *outputfile_Nevents = TFile::Open(outputdir_Nevents + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "RECREATE");
    outputfile_Nevents->cd();
    for(int i=0; i<v_hists_Nevents.size(); ++i) v_hists_Nevents.at(i)->Write();
    outputfile_Nevents->Close();

    // prepare for combine
    vector<TH1D*> v_hists_combine, v_hists_murmuf_combine, v_hists_pdf_combine;
    for(int i=0; i<v_hists_Nevents.size(); ++i){
      TH1D *hist_combine = (TH1D*) v_hists_Nevents.at(i)->Clone();
      TString histname = (TString) hist_combine->GetName();
      if(histname == "mtt" || histname.Contains("_datasyst_") || histname.Contains("_pu_") || histname.Contains("_isr_") || histname.Contains("_fsr_")) v_hists_combine.push_back(hist_combine);
      else if(histname.Contains("_murmuf_")) v_hists_murmuf_combine.push_back(hist_combine);
      else if(histname.Contains("_PDF_")) v_hists_pdf_combine.push_back(hist_combine);
    }
    // handle mur, muf: take envelope = min/max per bin
    TH1D *hist_mcscale_up = (TH1D*) v_hists_combine.at(0)->Clone();
    TH1D *hist_mcscale_down = (TH1D*) v_hists_combine.at(0)->Clone();
    hist_mcscale_up->SetName(outputname + "_mcscale_up");
    hist_mcscale_down->SetName(outputname + "_mcscale_down");
    for(int h=0; h<Nbins; ++h){
      double max = 0;
      double min = 9999999999;
      for(int g=0; g<v_hists_murmuf_combine.size(); ++g){
        double bincontent = v_hists_murmuf_combine.at(g)->GetBinContent(h+1);
        if(bincontent > max) max = bincontent;
        if(bincontent < min) min = bincontent;
      }
      hist_mcscale_up->SetBinContent(h+1, max);
      hist_mcscale_down->SetBinContent(h+1, min);
    }
    v_hists_combine.push_back(hist_mcscale_up);
    v_hists_combine.push_back(hist_mcscale_down);


    // handle pdfs: take rms per bin
    TH1D *hist_pdf_nominal = (TH1D*) v_hists_combine.at(0)->Clone();
    TH1D *hist_pdf_up = (TH1D*) hist_pdf_nominal->Clone();
    TH1D *hist_pdf_down = (TH1D*) hist_pdf_nominal->Clone();
    hist_pdf_up->SetName(outputname + "_pdf_up");
    hist_pdf_down->SetName(outputname + "_pdf_down");
    for(int h=0; h<Nbins; ++h){
      double nominal = hist_pdf_nominal->GetBinContent(h+1);
      double bin_sum = 0;
      for(int g=0; g<v_hists_pdf_combine.size(); ++g){
        double bincontent = v_hists_pdf_combine.at(g)->GetBinContent(h+1);
        bin_sum += pow(nominal - bincontent, 2);
      }
      double rms = sqrt(bin_sum/v_hists_pdf_combine.size());
      hist_pdf_up->SetBinContent(h+1, nominal + rms);
      hist_pdf_down->SetBinContent(h+1, max(0., nominal - rms));
    }
    v_hists_combine.push_back(hist_pdf_up);
    v_hists_combine.push_back(hist_pdf_down);

    TFile *outputfile_combine = TFile::Open(outputdir_combine + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "RECREATE");
    outputfile_combine->cd();
    for(int i=0; i<v_hists_combine.size(); ++i) v_hists_combine.at(i)->Write();
    outputfile_combine->Close();
  }
}
