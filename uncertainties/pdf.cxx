{
  TString year = "UL18";
  TString channel = "muon";

  TString input_directory = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/" + year + "/" + channel + "/AnalysisDNN_withSyst/";
  TString input_directory_signal_norm = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/UL18/preselection/";
  TString output_directory = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/hists_pdf/";
  TString save_plots_directory = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/plots/";

  vector<TString> v_root_directories = {
    "Zprime_PDFVariations_DNN_output0",
    "Zprime_PDFVariations_DNN_output1",
    "Zprime_PDFVariations_DNN_output2",
    "Zprime_PDFVariations_DNN_output0_TopTag",
    "Zprime_PDFVariations_DNN_output1_TopTag",
    "Zprime_PDFVariations_DNN_output2_TopTag",
    "Zprime_PDFVariations_DNN_output0_NoTopTag",
    "Zprime_PDFVariations_DNN_output1_NoTopTag",
    "Zprime_PDFVariations_DNN_output2_NoTopTag",
    "Zprime_PDFVariations_DNN_output0_thetastar_bin1",
    "Zprime_PDFVariations_DNN_output0_thetastar_bin2",
    "Zprime_PDFVariations_DNN_output0_thetastar_bin3",
    "Zprime_PDFVariations_DNN_output0_thetastar_bin4",
    "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin1",
    "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin2",
    "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin3",
    "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin4",
    "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin1",
    "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin2",
    "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin3",
    "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin4"
  };

  TString hist_name = "M_Zprime";

  TString systematic = "pdf";

  vector<TString> v_samples = {
    "TTbar",
    "ST",
    "WJets",
    "others", // DY + Diboson + QCD
    "DY",
    "Diboson",
    "QCD",
    "ALP_ttbar_signal",
    "ALP_ttbar_interference",
  };

  // loop over all samples
  for(int i=0; i<v_samples.size(); i++){

    std::string sample = (std::string) v_samples.at(i);
    // TString input
    TFile *input_file = new TFile(input_directory + "uhh2.AnalysisModuleRunner.MC." + sample + ".root", "READ");

    TH1F *h_nominal = (TH1F*) input_file->Get("DNN_output0_General/M_Zprime_rebin4");
    TH1F *h_up = (TH1F*) h_nominal->Clone();
    TH1F *h_down = (TH1F*) h_nominal->Clone();

    float sum_bins = 0;

    TFile *output_file = new TFile(output_directory + year + "/" + channel + "/" + "uhh2.AnalysisModuleRunner.MC." + sample + ".root", "RECREATE");

    for(int l=0; l<v_root_directories.size(); l++){

      std::string root_directory = (std::string) v_root_directories.at(l);
      TString output_root_directory = (TString) root_directory;
      output_root_directory.ReplaceAll("PDF", "Syst");

      int Nbins = h_nominal->GetNbinsX();
      for(int j=1; j<Nbins+1; j++){ // bin 0 is underflow -> 1...Nbins+1

        float value_nominal = h_nominal->GetBinContent(j);
        float sum_bins = 0;

        for(int k=1; k<101; k++){
          TString hist_name_pdf = root_directory + "/" + hist_name + "_PDF_" + to_string(k);
          TH1F *h_variation = (TH1F*) input_file->Get(hist_name_pdf);
          float value_variation = h_variation->GetBinContent(j);

          sum_bins += pow(value_variation - value_nominal,2);
        }

        float rms = sqrt(sum_bins/100);
        h_up->SetBinContent(j,value_nominal+rms);
        h_down->SetBinContent(j,value_nominal-rms);
      }

      // TODO: fix signal normalization
      // // normalization for signal samples
      // if(sample.find("ALP") != string::npos || sample.find("Hscalar") != string::npos || sample.find("Hpseudo") != string::npos || sample.find("RSGluon") != string::npos || sample.find("ZPrime") != string::npos){
      //   double integral_nominal = h_nominal->Integral();
      //   double integral_up = h_up->Integral();
      //   double integral_down = h_down->Integral();
      //   h_up->Scale(integral_nominal/integral_up);
      //   h_down->Scale(integral_nominal/integral_down);
      // }

      // cout << "h_nominal->Integral(): " << h_nominal->Integral() << endl;
      // cout << "     h_up->Integral(): " << h_up->Integral() << endl;
      // cout << "   h_down->Integral(): " << h_down->Integral() << endl;



      output_file->mkdir(output_root_directory);
      output_file->cd(output_root_directory);
      h_nominal->SetName(hist_name);
      h_up->SetName(hist_name + "_" + systematic + "_up");
      h_down->SetName(hist_name + "_" + systematic + "_down");
      // h_nominal->Write(); // not needed -> up/down variations are enough
      h_up->Write();
      h_down->Write();



      if(l == 0){ // plots only for SR = Zprime_SystVariations_DNN_output0
        TH1F *h_ratio_up = (TH1F*) h_up->Clone();
        TH1F *h_ratio_down = (TH1F*) h_down->Clone();

        h_ratio_up->Divide(h_nominal);
        h_ratio_down->Divide(h_nominal);

        h_ratio_up->SetLineColor(kRed);
        h_ratio_down->SetLineColor(kRed);

        h_ratio_up->SetLineWidth(2);
        h_ratio_down->SetLineWidth(2);

        h_ratio_up->SetLineStyle(7);
        h_ratio_down->SetLineStyle(3);

        // plotting
        TCanvas *c1 = new TCanvas("c1","c1",0,0,800,800);
        // upper pad
        double upperpad_titlesize = 0.04;
        double upperpad_topmargin = 0.05;
        double upperpad_leftmargin = 0.12;
        double upperpad_rightmargin = 0.05;
        double upperpad_bottommargin = 0.10;
        double upperpad_width = 1 - upperpad_leftmargin - upperpad_rightmargin;
        double upperpad_height = 1 - upperpad_topmargin - upperpad_bottommargin;

        TPad *upperPad = new TPad("upperPad","upperPad",0,0,1,1);
        gStyle->SetOptStat(0);
        gStyle->SetOptTitle(kFALSE);
        upperPad->Draw();
        upperPad->SetTitle("upperPad");
        upperPad->SetTopMargin(upperpad_topmargin);
        upperPad->SetLeftMargin(upperpad_leftmargin);
        upperPad->SetRightMargin(upperpad_rightmargin);
        upperPad->SetBottomMargin(upperpad_bottommargin);
        upperPad->SetTicks();
        upperPad->cd();

        // legend
        double x_pos  = 0.17;
        double y_pos  = 0.8;
        double x_width = 0.2;
        double y_width = 0.1;
        TLegend *legend;
        legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
        legend->SetTextSize(0.025);
        legend->SetLineWidth(0);
        legend->SetNColumns(1);
        legend->AddEntry(h_ratio_up, systematic + "_up","le");
        legend->AddEntry(h_ratio_down, systematic + "_down","le");

        // draw
        h_ratio_up->Draw("hist e");
        h_ratio_down->Draw("hist e same");
        legend->Draw();

        // x axis
        h_ratio_up->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
        h_ratio_up->GetXaxis()->SetTitleOffset(1.3);
        h_ratio_up->GetXaxis()->SetRangeUser(0,6000);
        // y axis
        h_ratio_up->GetYaxis()->SetTitle("variation/nominal");
        h_ratio_up->GetYaxis()->SetTitleOffset(1.7);
        h_ratio_up->GetYaxis()->SetRangeUser(0.5,1.5);

        c1->Modified();

        plot_nominalLine();
        plot_lumiTag();
        plot_systTag(sample);


        c1->SaveAs(save_plots_directory + systematic + "_" + sample + ".pdf");
        c1->Close();
      }

    }
    delete output_file;
  }
}


void plot_nominalLine(){
  TLine *line1;
  line1 = new TLine (0,1,6000,1);
  line1->SetLineColor(kBlack);
  line1->SetLineWidth(1);
  line1->SetLineStyle(2);
  line1->Draw();
}

void plot_lumiTag(){
  double x_pos = 0.95;
  double y_pos = 0.957;
  TLatex *lumiTag = new TLatex(3.5,24,"59.8 fb^{-1} (13 TeV)");
  lumiTag->SetNDC();
  lumiTag->SetTextAlign(31);
  lumiTag->SetX(x_pos);
  lumiTag->SetY(y_pos);
  lumiTag->SetTextFont(42);
  lumiTag->SetTextSize(0.032);
  lumiTag->Draw();
}

void plot_systTag(TString sample){
  double x_pos = 0.125;
  double y_pos = 0.957;
  auto *systTag = new TLatex(3.5, 24, "UL18 muon channel (SR): " + sample);
  systTag->SetNDC();
  systTag->SetTextAlign(11);
  systTag->SetX(x_pos);
  systTag->SetY(y_pos);
  systTag->SetTextFont(62);
  systTag->SetTextSize(0.028);
  systTag->Draw();
}
