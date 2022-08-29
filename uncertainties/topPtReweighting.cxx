{
  TString input_directory = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/UL18/muon/AnalysisDNN_withSyst/";
  TString root_directory = "Zprime_SystVariations_DNN_output0"; // SR (TTbar node of DNN)
  TString save_directory = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/plots/";
  TString hist_name = "M_Zprime";

  TString systematic = "topPtReweighting";
  TString sample = "TTbar"; // top pt reweighting for TTbar only


  // nominal
  TFile *file = TFile::Open(input_directory + "uhh2.AnalysisModuleRunner.MC." + sample + ".root");
  file->cd(root_directory);
  TH1F *h_nominal = (TH1F*) gDirectory->Get(hist_name);
  h_nominal->SetLineColor(kBlack);
  h_nominal->SetLineWidth(2);

  TH1F *h_toppt_a_up = (TH1F*) gDirectory->Get(hist_name + "_toppt_a_up");
  TH1F *h_toppt_a_down = (TH1F*) gDirectory->Get(hist_name + "_toppt_a_down");

  TH1F *h_toppt_b_up = (TH1F*) gDirectory->Get(hist_name + "_toppt_b_up");
  TH1F *h_toppt_b_down = (TH1F*) gDirectory->Get(hist_name + "_toppt_b_down");

  TH1F *h_ratio_toppt_a_up = (TH1F*) h_toppt_a_up->Clone();
  TH1F *h_ratio_toppt_a_down = (TH1F*) h_toppt_a_down->Clone();
  TH1F *h_ratio_toppt_b_up = (TH1F*) h_toppt_b_up->Clone();
  TH1F *h_ratio_toppt_b_down = (TH1F*) h_toppt_b_down->Clone();

  h_ratio_toppt_a_up->Divide(h_nominal);
  h_ratio_toppt_a_down->Divide(h_nominal);
  h_ratio_toppt_b_up->Divide(h_nominal);
  h_ratio_toppt_b_down->Divide(h_nominal);

  h_ratio_toppt_a_up->SetLineColor(kRed);
  h_ratio_toppt_a_down->SetLineColor(kRed);
  h_ratio_toppt_b_up->SetLineColor(kBlue);
  h_ratio_toppt_b_down->SetLineColor(kBlue);

  h_ratio_toppt_a_up->SetLineWidth(2);
  h_ratio_toppt_a_down->SetLineWidth(2);
  h_ratio_toppt_b_up->SetLineWidth(2);
  h_ratio_toppt_b_down->SetLineWidth(2);

  h_ratio_toppt_a_up->SetLineStyle(7);
  h_ratio_toppt_a_down->SetLineStyle(3);
  h_ratio_toppt_b_up->SetLineStyle(7);
  h_ratio_toppt_b_down->SetLineStyle(3);


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
  legend->AddEntry(h_ratio_toppt_a_up,"toppt_a_up","l");
  legend->AddEntry(h_ratio_toppt_a_down,"toppt_a_down","l");
  legend->AddEntry(h_ratio_toppt_b_up,"toppt_b_up","l");
  legend->AddEntry(h_ratio_toppt_b_down,"toppt_b_down","l");

  // draw
  h_ratio_toppt_a_up->Draw("hist");
  h_ratio_toppt_a_down->Draw("hist same");
  h_ratio_toppt_b_up->Draw("hist same");
  h_ratio_toppt_b_down->Draw("hist same");
  legend->Draw();

  // x axis
  h_ratio_toppt_a_up->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
  h_ratio_toppt_a_up->GetXaxis()->SetTitleOffset(1.3);
  h_ratio_toppt_a_up->GetXaxis()->SetRangeUser(100,6000);
  // y axis
  h_ratio_toppt_a_up->GetYaxis()->SetTitle("variation/nominal");
  h_ratio_toppt_a_up->GetYaxis()->SetTitleOffset(1.7);
  h_ratio_toppt_a_up->GetYaxis()->SetRangeUser(0.8,1.2);

  c1->Modified();

  plot_nominalLine();
  plot_lumiTag();
  plot_systTag(sample);

  c1->SaveAs(save_directory + systematic + "_" + sample + ".pdf");
  c1->Close();
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
