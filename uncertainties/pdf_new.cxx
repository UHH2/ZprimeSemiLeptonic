{
  TString input_directory = "/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/UL18/muon/";
  TString input_directory_nominal = "/nfs/dust/cms/user/deleokse/RunII_106_v2/DNN_UL18_muon/";
  TString root_directory = "Zprime_SystVariations_DNN_output0"; // SR (TTbar node of DNN)
  TString save_directory = "/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/plots_new/";
  TString hist_name = "M_Zprime";

  TString systematic = "pdf";
  vector<TString> v_samples = {
    //"TTbar",
    //"ST",
    //"WJets",
    //"others", // DY + Diboson + QCD
    //"DY",
    //"QCD",
    //"ZPrimeToTT_M500_W50",
    //"ZPrimeToTT_M1000_W100",
    //"ZPrimeToTT_M1400_W140",
    //"ZPrimeToTT_M2000_W200",
    //"ZPrimeToTT_M2500_W250",
    //"ZPrimeToTT_M3000_W300",
    //"ZPrimeToTT_M3500_W350",
    //"ZPrimeToTT_M4000_W400",
    //"ZPrimeToTT_M4500_W450",
    "ZPrimeToTT_M5000_W500",
    "ZPrimeToTT_M6000_W600",
    "ZPrimeToTT_M7000_W700",
    "ZPrimeToTT_M8000_W800",
    "ZPrimeToTT_M9000_W900",
    //"HscalarToTTTo1L1Nu2J_m400_w10p0_res",
    //"HscalarToTTTo1L1Nu2J_m400_w10p0_int_pos",
    //"HscalarToTTTo1L1Nu2J_m400_w10p0_int_neg",
    //"HpseudoToTTTo1L1Nu2J_m1000_w250p0_res",
    //"HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_pos",
    //"HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_neg",
    //"ALP_ttbar_signal",
    //"ALP_ttbar_interference",
    //"Diboson",
    //"RSGluonToTT_M-500",
    //"RSGluonToTT_M-1000",
    //"RSGluonToTT_M-1500",
    //"RSGluonToTT_M-2000",
    //"RSGluonToTT_M-2500",
    //"RSGluonToTT_M-3000",
    //"RSGluonToTT_M-3500",
    //"RSGluonToTT_M-4000",
    //"RSGluonToTT_M-4500",
    //"RSGluonToTT_M-5000",
    //"RSGluonToTT_M-5500",
    //"RSGluonToTT_M-6000"
    "ZPrimeToTT_M3000_W30",
    "ZPrimeToTT_M4000_W40",
    "ZPrimeToTT_M5000_W50",
    "ZPrimeToTT_M6000_W60",
    "ZPrimeToTT_M7000_W70",
    "ZPrimeToTT_M8000_W80",
    "ZPrimeToTT_M9000_W90",
  };

  for(int i=0; i<v_samples.size(); i++){

    TString sample = v_samples.at(i);

    // nominal
    TFile *file = TFile::Open(input_directory + "uhh2.AnalysisModuleRunner.MC." + sample + ".root");
    file->cd(root_directory);
    TH1F *h_pdf_up = (TH1F*) gDirectory->Get(hist_name + "_pdf_up");
    TH1F *h_pdf_down = (TH1F*) gDirectory->Get(hist_name + "_pdf_down");

    TFile *file_nominal = TFile::Open(input_directory_nominal + "uhh2.AnalysisModuleRunner.MC." + sample + ".root");
    file_nominal->cd(root_directory);
    TH1F *h_nominal = (TH1F*) gDirectory->Get(hist_name);
    h_nominal->SetLineColor(kBlack);
    h_nominal->SetLineWidth(2);

    h_pdf_up->Divide(h_nominal);
    h_pdf_down->Divide(h_nominal);

    h_pdf_up->SetLineColor(kRed);
    h_pdf_down->SetLineColor(kRed);

    h_pdf_up->SetLineWidth(2);
    h_pdf_down->SetLineWidth(2);

    h_pdf_up->SetLineStyle(7);
    h_pdf_down->SetLineStyle(3);


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
    double y_pos  = 0.7;
    double x_width = 0.2;
    double y_width = 0.2;
    TLegend *legend;
    legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
    legend->SetTextSize(0.025);
    legend->SetLineWidth(0);
    legend->SetNColumns(1);
    legend->AddEntry(h_pdf_up,"pdf_up","le");
    legend->AddEntry(h_pdf_down,"pdf_down","le");

    // draw
    h_pdf_up->Draw("hist");
    h_pdf_down->Draw("hist same");
    legend->Draw();

    // x axis
    h_pdf_up->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
    h_pdf_up->GetXaxis()->SetTitleOffset(1.3);
    h_pdf_up->GetXaxis()->SetRangeUser(100,6000);
    // y axis
    h_pdf_up->GetYaxis()->SetTitle("variation/nominal");
    h_pdf_up->GetYaxis()->SetTitleOffset(1.7);
    h_pdf_up->GetYaxis()->SetRangeUser(-2.,3.);

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
