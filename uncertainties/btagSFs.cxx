{
  TString input_directory = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/UL18/muon/AnalysisDNN_withSyst/";
  TString root_directory = "Zprime_SystVariations_DNN_output0"; // SR (TTbar node of DNN)
  TString save_directory = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/plots/";
  TString hist_name = "M_Zprime";

  TString systematic = "btagSFs";
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

  for(int i=0; i<v_samples.size(); i++){

    TString sample = v_samples.at(i);

    // nominal
    TFile *file = TFile::Open(input_directory + "uhh2.AnalysisModuleRunner.MC." + sample + ".root");
    file->cd(root_directory);
    TH1F *h_nominal = (TH1F*) gDirectory->Get(hist_name);

    TH1F *h_cferr1_up = (TH1F*) gDirectory->Get(hist_name + "_btag_cferr1_up");
    TH1F *h_cferr1_down = (TH1F*) gDirectory->Get(hist_name + "_btag_cferr1_down");
    TH1F *h_cferr2_up = (TH1F*) gDirectory->Get(hist_name + "_btag_cferr2_up");
    TH1F *h_cferr2_down = (TH1F*) gDirectory->Get(hist_name + "_btag_cferr2_down");
    TH1F *h_hf_up = (TH1F*) gDirectory->Get(hist_name + "_btag_hf_up");
    TH1F *h_hf_down = (TH1F*) gDirectory->Get(hist_name + "_btag_hf_down");
    TH1F *h_hfstats1_up = (TH1F*) gDirectory->Get(hist_name + "_btag_hfstats1_up");
    TH1F *h_hfstats1_down = (TH1F*) gDirectory->Get(hist_name + "_btag_hfstats1_down");
    TH1F *h_hfstats2_up = (TH1F*) gDirectory->Get(hist_name + "_btag_hfstats2_up");
    TH1F *h_hfstats2_down = (TH1F*) gDirectory->Get(hist_name + "_btag_hfstats2_down");
    TH1F *h_lf_up = (TH1F*) gDirectory->Get(hist_name + "_btag_lf_up");
    TH1F *h_lf_down = (TH1F*) gDirectory->Get(hist_name + "_btag_lf_down");
    TH1F *h_lfstats1_up = (TH1F*) gDirectory->Get(hist_name + "_btag_lfstats1_up");
    TH1F *h_lfstats1_down = (TH1F*) gDirectory->Get(hist_name + "_btag_lfstats1_down");
    TH1F *h_lfstats2_up = (TH1F*) gDirectory->Get(hist_name + "_btag_lfstats2_up");
    TH1F *h_lfstats2_down = (TH1F*) gDirectory->Get(hist_name + "_btag_lfstats2_down");

    h_cferr1_up->Divide(h_nominal);
    h_cferr1_down->Divide(h_nominal);
    h_cferr2_up->Divide(h_nominal);
    h_cferr2_down->Divide(h_nominal);
    h_hf_up->Divide(h_nominal);
    h_hf_down->Divide(h_nominal);
    h_hfstats1_up->Divide(h_nominal);
    h_hfstats1_down->Divide(h_nominal);
    h_hfstats2_up->Divide(h_nominal);
    h_hfstats2_down->Divide(h_nominal);
    h_lf_up->Divide(h_nominal);
    h_lf_down->Divide(h_nominal);
    h_lfstats1_up->Divide(h_nominal);
    h_lfstats1_down->Divide(h_nominal);
    h_lfstats2_up->Divide(h_nominal);
    h_lfstats2_down->Divide(h_nominal);

    h_cferr1_up->SetLineColor(kRed);
    h_cferr1_down->SetLineColor(kRed);
    h_cferr2_up->SetLineColor(kBlue);
    h_cferr2_down->SetLineColor(kBlue);
    h_hf_up->SetLineColor(kGreen);
    h_hf_down->SetLineColor(kGreen);
    h_hfstats1_up->SetLineColor(kCyan);
    h_hfstats1_down->SetLineColor(kCyan);
    h_hfstats2_up->SetLineColor(kMagenta);
    h_hfstats2_down->SetLineColor(kMagenta);
    h_lf_up->SetLineColor(kOrange);
    h_lf_down->SetLineColor(kOrange);
    h_lfstats1_up->SetLineColor(kGray);
    h_lfstats1_down->SetLineColor(kGray);
    h_lfstats2_up->SetLineColor(kYellow);
    h_lfstats2_down->SetLineColor(kYellow);

    h_cferr1_up->SetLineWidth(2);
    h_cferr1_down->SetLineWidth(2);
    h_cferr2_up->SetLineWidth(2);
    h_cferr2_down->SetLineWidth(2);
    h_hf_up->SetLineWidth(2);
    h_hf_down->SetLineWidth(2);
    h_hfstats1_up->SetLineWidth(2);
    h_hfstats1_down->SetLineWidth(2);
    h_hfstats2_up->SetLineWidth(2);
    h_hfstats2_down->SetLineWidth(2);
    h_lf_up->SetLineWidth(2);
    h_lf_down->SetLineWidth(2);
    h_lfstats1_up->SetLineWidth(2);
    h_lfstats1_down->SetLineWidth(2);
    h_lfstats2_up->SetLineWidth(2);
    h_lfstats2_down->SetLineWidth(2);

    h_cferr1_up->SetLineStyle(7);
    h_cferr1_down->SetLineStyle(3);
    h_cferr2_up->SetLineStyle(7);
    h_cferr2_down->SetLineStyle(3);
    h_hf_up->SetLineStyle(7);
    h_hf_down->SetLineStyle(3);
    h_hfstats1_up->SetLineStyle(7);
    h_hfstats1_down->SetLineStyle(3);
    h_hfstats2_up->SetLineStyle(7);
    h_hfstats2_down->SetLineStyle(3);
    h_lf_up->SetLineStyle(7);
    h_lf_down->SetLineStyle(3);
    h_lfstats1_up->SetLineStyle(7);
    h_lfstats1_down->SetLineStyle(3);
    h_lfstats2_up->SetLineStyle(7);
    h_lfstats2_down->SetLineStyle(3);


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
    double y_pos  = 0.6;
    double x_width = 0.2;
    double y_width = 0.3;
    TLegend *legend;
    legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
    legend->SetTextSize(0.025);
    legend->SetLineWidth(0);
    legend->SetNColumns(1);
    legend->AddEntry(h_cferr1_up,"cferr1_up","l");
    legend->AddEntry(h_cferr1_down,"cferr1_down","l");
    legend->AddEntry(h_cferr2_up,"cferr2_up","l");
    legend->AddEntry(h_cferr2_down,"cferr2_down","l");
    legend->AddEntry(h_hf_up,"hf_up","l");
    legend->AddEntry(h_hf_down,"hf_down","l");
    legend->AddEntry(h_hfstats1_up,"hfstats1_up","l");
    legend->AddEntry(h_hfstats1_down,"hfstats1_down","l");
    legend->AddEntry(h_hfstats2_up,"hfstats2_up","l");
    legend->AddEntry(h_hfstats2_down,"hfstats2_down","l");
    legend->AddEntry(h_lf_up,"lf_up","l");
    legend->AddEntry(h_lf_down,"lf_down","l");
    legend->AddEntry(h_lfstats1_up,"lfstats1_up","l");
    legend->AddEntry(h_lfstats1_down,"lfstats1_down","l");
    legend->AddEntry(h_lfstats2_up,"lfstats2_up","l");
    legend->AddEntry(h_lfstats2_down,"lfstats2_down","l");

    // draw
    h_cferr1_up->Draw("hist");
    h_cferr1_down->Draw("hist same");
    h_cferr2_up->Draw("hist same");
    h_cferr2_down->Draw("hist same");
    h_hf_up->Draw("hist same");
    h_hf_down->Draw("hist same");
    h_hfstats1_up->Draw("hist same");
    h_hfstats1_down->Draw("hist same");
    h_hfstats2_up->Draw("hist same");
    h_hfstats2_down->Draw("hist same");
    h_lf_up->Draw("hist same");
    h_lf_down->Draw("hist same");
    h_lfstats1_up->Draw("hist same");
    h_lfstats1_down->Draw("hist same");
    h_lfstats2_up->Draw("hist same");
    h_lfstats2_down->Draw("hist same");
    legend->Draw();

    // x axis
    h_cferr1_up->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
    h_cferr1_up->GetXaxis()->SetTitleOffset(1.3);
    h_cferr1_up->GetXaxis()->SetLimits(0,6000);
    // y axis
    h_cferr1_up->GetYaxis()->SetTitle("variation/nominal");
    h_cferr1_up->GetYaxis()->SetTitleOffset(1.7);
    h_cferr1_up->GetYaxis()->SetRangeUser(0.5,1.5);

    c1->Modified();

    plot_nominalLine();
    plot_lumiTag();
    plot_systTag(sample);

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
