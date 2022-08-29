{
  TString input_directory = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/UL18/muon/AnalysisDNN_withSyst/";
  TString save_directory = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/plots/";
  TString root_directory = "Zprime_SystVariations_DNN_output0/";
  TString hist_name = "M_Zprime";

  TString systematic = "MCScale";

  vector<TString> v_samples = {
    "TTbar",
    "ST",
    "WJets",
    "others", // DY + Diboson + QCD
    "DY",
    "Diboson",
    "QCD",
    "ALP_ttbar_signal",
    "ALP_ttbar_interference"
  };

  // loop over all samples
  for(int i=0; i<v_samples.size(); i++){

    std::string sample = (std::string) v_samples.at(i);
    TFile *input_file = new TFile(input_directory + "uhh2.AnalysisModuleRunner.MC." + sample + ".root", "READ");

    TH1F *h_nominal = (TH1F*) input_file->Get(root_directory + hist_name);
    TH1F *h_up = (TH1F*) h_nominal->Clone();
    TH1F *h_down = (TH1F*) h_nominal->Clone();

    TH1F *h_upup     = (TH1F*) input_file->Get(root_directory + hist_name + "_murmuf_upup");
    TH1F *h_upnone   = (TH1F*) input_file->Get(root_directory + hist_name + "_murmuf_upnone");
    TH1F *h_noneup   = (TH1F*) input_file->Get(root_directory + hist_name + "_murmuf_noneup");
    TH1F *h_nonedown = (TH1F*) input_file->Get(root_directory + hist_name + "_murmuf_nonedown");
    TH1F *h_downnone = (TH1F*) input_file->Get(root_directory + hist_name + "_murmuf_downnone");
    TH1F *h_downdown = (TH1F*) input_file->Get(root_directory + hist_name + "_murmuf_downdown");


    int Nbins = h_nominal->GetNbinsX();
    for(int j=1; j<Nbins+1; j++){ // bin 0 is underflow -> 1...Nbins+1

      // normalization for signal samples
      if(sample.find("ALP") != string::npos || sample.find("Hscalar") != string::npos || sample.find("Hpseudo") != string::npos || sample.find("RSGluon") != string::npos || sample.find("ZPrime") != string::npos){
        double integral_nominal = h_nominal->Integral();
        double integral_upup = h_upup->Integral();
        double integral_upnone = h_upnone->Integral();
        double integral_noneup = h_noneup->Integral();
        double integral_nonedown = h_nonedown->Integral();
        double integral_downnone = h_downnone->Integral();
        double integral_downdown = h_downdown->Integral();

        h_upup->Scale(integral_nominal/integral_upup);
        h_upnone->Scale(integral_nominal/integral_upnone);
        h_noneup->Scale(integral_nominal/integral_noneup);
        h_nonedown->Scale(integral_nominal/integral_nonedown);
        h_downnone->Scale(integral_nominal/integral_downnone);
        h_downdown->Scale(integral_nominal/integral_downdown);
      }

      vector<TH1F*> v_hists = {h_upup,h_upnone,h_noneup,h_nonedown,h_downnone,h_downdown};

      float value_up = -999999;
      float value_down = 999999;

      for(int k=0; k<v_hists.size(); k++){
        float value = v_hists.at(k)->GetBinContent(j);
        if(value > value_up) value_up = value;
        if(value < value_down) value_down = value;
      }

      h_up->SetBinContent(j, value_up);
      h_down->SetBinContent(j, value_down);
    }


    TH1F *h_ratio_up = (TH1F*) h_up->Clone();
    TH1F *h_ratio_down = (TH1F*) h_down->Clone();
    TH1F *h_ratio_upup = (TH1F*) h_upup->Clone();
    TH1F *h_ratio_upnone = (TH1F*) h_upnone->Clone();
    TH1F *h_ratio_noneup = (TH1F*) h_noneup->Clone();
    TH1F *h_ratio_nonedown = (TH1F*) h_nonedown->Clone();
    TH1F *h_ratio_downnone = (TH1F*) h_downnone->Clone();
    TH1F *h_ratio_downdown = (TH1F*) h_downdown->Clone();

    h_ratio_up->Divide(h_nominal);
    h_ratio_down->Divide(h_nominal);
    h_ratio_upup->Divide(h_nominal);
    h_ratio_upnone->Divide(h_nominal);
    h_ratio_noneup->Divide(h_nominal);
    h_ratio_nonedown->Divide(h_nominal);
    h_ratio_downnone->Divide(h_nominal);
    h_ratio_downdown->Divide(h_nominal);

    h_ratio_up->SetLineColor(kBlack);
    h_ratio_down->SetLineColor(kBlack);
    h_ratio_upup->SetLineColor(kRed);
    h_ratio_upnone->SetLineColor(kGreen);
    h_ratio_noneup->SetLineColor(kBlue);
    h_ratio_nonedown->SetLineColor(kCyan);
    h_ratio_downnone->SetLineColor(kMagenta);
    h_ratio_downdown->SetLineColor(kOrange);

    h_ratio_up->SetLineWidth(2);
    h_ratio_down->SetLineWidth(2);
    h_ratio_upup->SetLineWidth(2);
    h_ratio_upnone->SetLineWidth(2);
    h_ratio_noneup->SetLineWidth(2);
    h_ratio_nonedown->SetLineWidth(2);
    h_ratio_downnone->SetLineWidth(2);
    h_ratio_downdown->SetLineWidth(2);

    h_ratio_up->SetLineStyle(2);
    h_ratio_down->SetLineStyle(2);


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
    double y_pos  = 0.66;
    double x_width = 0.2;
    double y_width = 0.25;
    TLegend *legend;
    legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
    legend->SetTextSize(0.025);
    legend->SetLineWidth(0);
    legend->SetNColumns(1);
    legend->SetHeader("MC scale (#mu_{R}, #mu_{F})");
    legend->AddEntry(h_ratio_up,"envelope","l");
    legend->AddEntry(h_ratio_upup,"upup","l");
    legend->AddEntry(h_ratio_upnone,"upnone","l");
    legend->AddEntry(h_ratio_noneup,"noneup","l");
    legend->AddEntry(h_ratio_nonedown,"nonedown","l");
    legend->AddEntry(h_ratio_downnone,"downnone","l");
    legend->AddEntry(h_ratio_downdown,"downdown","l");

    // draw
    h_ratio_upup->Draw("hist");
    h_ratio_upnone->Draw("hist same");
    h_ratio_noneup->Draw("hist same");
    h_ratio_nonedown->Draw("hist same");
    h_ratio_downnone->Draw("hist same");
    h_ratio_downdown->Draw("hist same");
    h_ratio_up->Draw("hist same");
    h_ratio_down->Draw("hist same");
    legend->Draw();

    // x axis
    h_ratio_upup->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
    h_ratio_upup->GetXaxis()->SetTitleOffset(1.3);
    h_ratio_upup->GetXaxis()->SetRangeUser(0,6000);
    // y axis
    h_ratio_upup->GetYaxis()->SetTitle("variation/nominal");
    h_ratio_upup->GetYaxis()->SetTitleOffset(1.7);
    h_ratio_upup->GetYaxis()->SetRangeUser(0.1, 1.9);

    plot_nominalLine();
    plot_lumiTag();
    plot_systTag(sample);

    c1->Modified();

    c1->SaveAs(save_directory + systematic + "_" + sample + ".pdf");
    c1->Close();
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
