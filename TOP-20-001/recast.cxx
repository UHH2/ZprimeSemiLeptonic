{
  cout << "starting..." << endl;

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

  double binwidth_mtt250To420 = 420 - 250;
  double binwidth_mtt420To520 = 520 - 420;
  double binwidth_mtt520To620 = 620 - 520;
  double binwidth_mtt620To800 = 800 - 620;
  double binwidth_mtt800To1000 = 1000 - 800;
  double binwidth_mtt1000To3500 = 3500 - 1000;

  vector<TString> v_HEPDatanames = {
    "parton_abs_ttm",
    "parton_abs_ttm+cts_1",
    "parton_abs_ttm+cts_2",
    "parton_abs_ttm+cts_3",
    "parton_abs_ttm+cts_4",
    "parton_abs_ttm+cts_5",
    "parton_abs_ttm+cts_6",
    "parton_abs_cts",
    "parton_abs_thadpth",
    "parton_abs_tleppt",
    "parton_abs_st",
    "parton_abs_thady",
    "parton_abs_tlepy",
    "parton_abs_dy",
    "parton_abs_ady",
    "parton_abs_ttpt",
    "parton_abs_tty",
    "parton_abs_ttphi",
  };
  vector<TString> v_inputnames = {
    "m_ttbar",
    "cts_mtt250To420",
    "cts_mtt420To520",
    "cts_mtt520To620",
    "cts_mtt620To800",
    "cts_mtt800To1000",
    "cts_mtt1000To3500",
    "cts",
    "pt_thad",
    "pt_tlep",
    "ST",
    "absy_thad",
    "absy_tlep",
    "deltaabsy_ttbar",
    "absdeltay_ttbar",
    "pt_ttbar",
    "absy_ttbar",
    "phi_ttbar",
  };
  vector<TString> v_outputnames = {
    "mtt",
    "cts_mtt250To420",
    "cts_mtt420To520",
    "cts_mtt520To620",
    "cts_mtt620To800",
    "cts_mtt800To1000",
    "cts_mtt1000To3500",
    "cts",
    "pt_thad",
    "pt_tlep",
    "ST",
    "absy_thad",
    "absy_tlep",
    "deltaabsy_ttbar",
    "absdeltay_ttbar",
    "pt_ttbar",
    "absy_ttbar",
    "phi_ttbar",
  };


  for(int a=0; a<v_HEPDatanames.size(); ++a){
    cout << "----- " << v_HEPDatanames.at(a) << " -----" << endl;
    TFile *outputfile;

    // DATA
    // diff xsec
    cout << "DATA" << endl;
    vector<TString> v_histnames_data = {"Hist1D_y1", "Hist1D_y1_e1", "Hist1D_y1_e2"};
    vector<TH1D*> v_datahists;
    TFile *inputfile_data = TFile::Open("HEPData/HEPData-ins1901295-v1-" + v_HEPDatanames.at(a) + ".root");
    inputfile_data->cd(v_HEPDatanames.at(a));
    for(int i=0; i<v_histnames_data.size(); ++i){
      TH1D *datahist = (TH1D*) gDirectory->Get(v_histnames_data.at(i));
      if(v_histnames_data.at(i).Contains("e1")) datahist->SetName(v_outputnames.at(a) + "_errStat"); // stat. error
      else if(v_histnames_data.at(i).Contains("e2")) datahist->SetName(v_outputnames.at(a) + "_errSyst"); // syst. error
      else datahist->SetName(v_outputnames.at(a)); // nominal
      v_datahists.push_back(datahist);
    }
    if(a == 0) outputfile = new TFile(outputdir_diffxsec + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "RECREATE");
    else outputfile = TFile::Open(outputdir_diffxsec + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "UPDATE");
    outputfile->cd();
    for(int i=0; i<v_datahists.size(); ++i) v_datahists.at(i)->Write();
    outputfile->Close();

    // scaled to Nevents
    vector<TH1D*> v_datahists_Nevents;
    for(int i=0; i<v_datahists.size(); ++i){
      TH1D *datahist_Nevents = (TH1D*) v_datahists.at(i)->Clone();
      datahist_Nevents->Scale(target_lumi);
      for(int i=0; i<datahist_Nevents->GetNbinsX(); ++i) datahist_Nevents->SetBinContent(i+1, (int) (datahist_Nevents->GetBinContent(i+1) * datahist_Nevents->GetXaxis()->GetBinWidth(i+1)));
      if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_1") datahist_Nevents->Scale(binwidth_mtt250To420);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_2") datahist_Nevents->Scale(binwidth_mtt420To520);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_3") datahist_Nevents->Scale(binwidth_mtt520To620);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_4") datahist_Nevents->Scale(binwidth_mtt620To800);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_5") datahist_Nevents->Scale(binwidth_mtt800To1000);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_6") datahist_Nevents->Scale(binwidth_mtt1000To3500);
      datahist_Nevents->GetYaxis()->SetTitle("Nevents");
      v_datahists_Nevents.push_back(datahist_Nevents);
    }
    if(a == 0) outputfile = new TFile(outputdir_Nevents + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "RECREATE");
    else outputfile = TFile::Open(outputdir_Nevents + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "UPDATE");
    outputfile->cd();
    for(int i=0; i<v_datahists_Nevents.size(); ++i) v_datahists_Nevents.at(i)->Write();
    outputfile->Close();

    // prepare for combine
    TH1D *datahist_combine = (TH1D*) v_datahists_Nevents.at(0)->Clone();
    for(int i=0; i<datahist_combine->GetNbinsX(); ++i){
      double statError = v_datahists_Nevents.at(1)->GetBinContent(i+1);
      // double systError = v_datahists_Nevents.at(2)->GetBinContent(i+1);
      // double totalError = sqrt(pow(statError, 2) + pow(systError, 2));
      datahist_combine->SetBinError(i+1, statError);
    }
    if(a == 0) outputfile = new TFile(outputdir_combine + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "RECREATE");
    else outputfile = TFile::Open(outputdir_combine + "uhh2.AnalysisModuleRunner.DATA.data_obs.root", "UPDATE");
    outputfile->cd();
    datahist_combine->Write();
    outputfile->Close();


    // MC
    for(int j=0; j<v_samplenames.size(); ++j){
      cout << v_samplenames.at(j) << endl;
      // diff xsec
      TFile *inputfile = TFile::Open(inputdir + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root");
      TH1D *hist = (TH1D*) gDirectory->Get(rootdir_hist + v_inputnames.at(a));
      hist->Scale(v_scales.at(j), "width");
      if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_1") hist->Scale(1. / binwidth_mtt250To420);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_2") hist->Scale(1. / binwidth_mtt420To520);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_3") hist->Scale(1. / binwidth_mtt520To620);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_4") hist->Scale(1. / binwidth_mtt620To800);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_5") hist->Scale(1. / binwidth_mtt800To1000);
      else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_6") hist->Scale(1. / binwidth_mtt1000To3500);


      hist->SetName(v_outputnames.at(a));
      double Nbins = hist->GetNbinsX();
      vector<TH1D*> v_hists;

      // for TTbar: take statistical error from DATA + apply systematics from DATA
      if(j==0){
        for(int i=0; i<Nbins; ++i) hist->SetBinError(i+1, v_datahists.at(1)->GetBinError(i+1)); // for TTbar: take statistical error from DATA
        TH1D *hist_dataSystUp = (TH1D*) hist->Clone();
        TH1D *hist_dataSystDown = (TH1D*) hist->Clone();
        hist_dataSystUp->SetName(v_outputnames.at(a) + "_datasyst_up");
        hist_dataSystDown->SetName(v_outputnames.at(a) + "_datasyst_down");
        for(int i=0; i<Nbins; ++i){
          hist_dataSystUp->SetBinContent(i+1, hist_dataSystUp->GetBinContent(i+1) + v_datahists.at(2)->GetBinContent(i+1));
          hist_dataSystDown->SetBinContent(i+1, hist_dataSystDown->GetBinContent(i+1) - v_datahists.at(2)->GetBinContent(i+1));
        }
        v_hists.push_back(hist);
        v_hists.push_back(hist_dataSystUp);
        v_hists.push_back(hist_dataSystDown);
      }
      else{
        v_hists.push_back(hist);
      }

      // systematics
      if(v_HEPDatanames.at(a).Contains("ttm")){
        for(int i=0; i<v_systnames.size(); ++i){
          TH1D *syst = (TH1D*) gDirectory->Get(rootdir_syst + v_outputnames.at(a) + "_" + v_systnames.at(i));
          syst->Scale(v_scales.at(j), "width");
          if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_1") syst->Scale(1. / binwidth_mtt250To420);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_2") syst->Scale(1. / binwidth_mtt420To520);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_3") syst->Scale(1. / binwidth_mtt520To620);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_4") syst->Scale(1. / binwidth_mtt620To800);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_5") syst->Scale(1. / binwidth_mtt800To1000);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_6") syst->Scale(1. / binwidth_mtt1000To3500);
          v_hists.push_back(syst);
        }
        // PDFs
        for(int i=1; i<101; ++i){
          TH1D *pdf = (TH1D*) gDirectory->Get(rootdir_pdf + v_outputnames.at(a) + "_PDF_" + i);
          pdf->Scale(v_scales.at(j), "width");
          if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_1") pdf->Scale(1. / binwidth_mtt250To420);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_2") pdf->Scale(1. / binwidth_mtt420To520);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_3") pdf->Scale(1. / binwidth_mtt520To620);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_4") pdf->Scale(1. / binwidth_mtt620To800);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_5") pdf->Scale(1. / binwidth_mtt800To1000);
          else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_6") pdf->Scale(1. / binwidth_mtt1000To3500);
          v_hists.push_back(pdf);
        }
      }

      if(a == 0) outputfile = new TFile(outputdir_diffxsec + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "RECREATE");
      else outputfile = TFile::Open(outputdir_diffxsec + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "UPDATE");
      outputfile->cd();
      for(int i=0; i<v_hists.size(); ++i) v_hists.at(i)->Write();
      outputfile->Close();

      // scaled to Nevents
      vector<TH1D*> v_hists_Nevents;
      for(int i=0; i<v_hists.size(); ++i){
        TH1D *hist_Nevents = (TH1D*) v_hists.at(i)->Clone();
        hist_Nevents->Scale(target_lumi);
        if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_1") hist_Nevents->Scale(binwidth_mtt250To420);
        else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_2") hist_Nevents->Scale(binwidth_mtt420To520);
        else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_3") hist_Nevents->Scale(binwidth_mtt520To620);
        else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_4") hist_Nevents->Scale(binwidth_mtt620To800);
        else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_5") hist_Nevents->Scale(binwidth_mtt800To1000);
        else if(v_HEPDatanames.at(a) == "parton_abs_ttm+cts_6") hist_Nevents->Scale(binwidth_mtt1000To3500);
        for(int h=0; h<hist_Nevents->GetNbinsX(); ++h){
          hist_Nevents->SetBinContent(h+1, hist_Nevents->GetBinContent(h+1) * hist_Nevents->GetXaxis()->GetBinWidth(h+1));
          hist_Nevents->SetBinError(h+1, hist_Nevents->GetBinError(h+1) * hist_Nevents->GetXaxis()->GetBinWidth(h+1));
        }
        v_hists_Nevents.push_back(hist_Nevents);
      }
      if(a == 0) outputfile = new TFile(outputdir_Nevents + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "RECREATE");
      else outputfile = TFile::Open(outputdir_Nevents + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "UPDATE");
      outputfile->cd();
      for(int i=0; i<v_hists_Nevents.size(); ++i) v_hists_Nevents.at(i)->Write();
      outputfile->Close();

      // prepare for combine
      vector<TH1D*> v_hists_combine, v_hists_murmuf_combine, v_hists_pdf_combine;
      for(int i=0; i<v_hists_Nevents.size(); ++i){
        TH1D *hist_combine = (TH1D*) v_hists_Nevents.at(i)->Clone();
        TString histname = (TString) hist_combine->GetName();
        if(histname == v_outputnames.at(a) || histname.Contains("_datasyst_") || histname.Contains("_pu_") || histname.Contains("_isr_") || histname.Contains("_fsr_")) v_hists_combine.push_back(hist_combine);
        else if(histname.Contains("_murmuf_")) v_hists_murmuf_combine.push_back(hist_combine);
        else if(histname.Contains("_PDF_")) v_hists_pdf_combine.push_back(hist_combine);
      }
      if(v_HEPDatanames.at(a).Contains("ttm")){ // only for m(tt) and cos(theta*) in m(tt) bins for now
        // handle mur, muf: take envelope = min/max per bin
        TH1D *hist_mcscale_up = (TH1D*) v_hists_combine.at(0)->Clone();
        TH1D *hist_mcscale_down = (TH1D*) v_hists_combine.at(0)->Clone();
        hist_mcscale_up->SetName(v_outputnames.at(a) + "_mcscale_up");
        hist_mcscale_down->SetName(v_outputnames.at(a) + "_mcscale_down");
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
        hist_pdf_up->SetName(v_outputnames.at(a) + "_pdf_up");
        hist_pdf_down->SetName(v_outputnames.at(a) + "_pdf_down");
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
      }

      if(a == 0) outputfile = new TFile(outputdir_combine + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "RECREATE");
      else outputfile = TFile::Open(outputdir_combine + "uhh2.AnalysisModuleRunner.MC." + v_samplenames.at(j) + ".root", "UPDATE");
      outputfile->cd();
      for(int i=0; i<v_hists_combine.size(); ++i) v_hists_combine.at(i)->Write();
      outputfile->Close();
    }
  }
  cout << "done!" << endl;
}
