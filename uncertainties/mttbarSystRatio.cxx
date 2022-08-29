{
  TString input_dir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/UL18/muon/AnalysisDNN_withSyst/";
  TString root_dir = "Zprime_SystVariations_DNN_output0"; // SR (TTbar node of DNN)
  TString save_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/plots/mttbarSystRatio/";
  TString histname = "M_Zprime";
  TString sample = "ALP_ttbar_signal"; // TTbar, data_obs, ALP_ttbar_signal

  vector<TString> v_systs = {
    "pu",
    "prefiring",
    "mu_reco",
    "mu_id",
    "mu_iso",
    "mu_trigger",
    "toppt_a",
    "toppt_b",
    "btag_cferr1",
    "btag_cferr2",
    "btag_hf",
    "btag_hfstats1",
    "btag_hfstats2",
    "btag_lf",
    "btag_lfstats1",
    "btag_lfstats2",
    "PDF",
  };

  vector<double> v_yRange = {
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
    0.2,
  };

  if(v_systs.size() != v_yRange.size()) throw runtime_error("different number of entries in vectors!");








  // TODO: add loop over all samples
  for(int i=0; i<v_systs.size(); i++){

    TString syst = v_systs.at(i);
    if(syst == "PDF") input_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/";

    // nominal sample
    TFile *file = TFile::Open(input_dir + "uhh2.AnalysisModuleRunner.MC." + sample + ".root");
    file->cd(root_dir);
    TH1F *h_nominal = (TH1F*) gDirectory->Get(histname);
    h_nominal->SetLineColor(kBlack);
    h_nominal->SetLineWidth(2);


    TH1F *h_up = (TH1F*) gDirectory->Get(histname + "_" + syst + "_up");
    TH1F *h_down = (TH1F*) gDirectory->Get(histname + "_" + syst + "_down");

    TH1F *h_ratio_up = (TH1F*) h_up->Clone();
    h_ratio_up->Divide(h_nominal);
    h_ratio_up->SetLineColor(kRed);
    h_ratio_up->SetLineWidth(2);

    TH1F *h_ratio_down = (TH1F*) h_down->Clone();
    h_ratio_down->Divide(h_nominal);
    h_ratio_down->SetLineColor(kBlue);
    h_ratio_down->SetLineWidth(2);

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
    double y_pos  = 0.83;
    double x_width =  0.1;
    double y_width =  0.07;
    TLegend *legend;
    legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
    legend->SetTextSize(0.025);
    legend->SetLineWidth(0);
    legend->SetNColumns(1);
    legend->SetHeader(syst);
    legend->AddEntry(h_ratio_up,"up","l");
    legend->AddEntry(h_ratio_down,"down","l");

    // draw
    h_ratio_up->Draw("hist");
    h_ratio_down->Draw("hist same");

    // x axis
    h_ratio_up->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
    h_ratio_up->GetXaxis()->SetTitleOffset(1.3);
    h_ratio_up->GetXaxis()->SetRangeUser(100,6000);
    // y axis
    h_ratio_up->GetYaxis()->SetTitle("variation/nominal");
    h_ratio_up->GetYaxis()->SetTitleOffset(1.7);
    h_ratio_up->GetYaxis()->SetRangeUser(1-v_yRange.at(i), 1+v_yRange.at(i));

    c1->Modified();

    plot_nominalLine();
    plot_lumiTag();
    plot_systTag(sample);

    // redraw lines
    h_ratio_up->Draw("hist same");
    h_ratio_down->Draw("hist same");
    legend->Draw();

    c1->SaveAs(save_dir + "mttbarSystRatio_" + sample + "_" + syst + ".pdf");
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
