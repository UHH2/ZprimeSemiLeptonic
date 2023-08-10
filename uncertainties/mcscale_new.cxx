{
  TString input_directory = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/Scale_hists/UL18/muon/";
  TString input_directory_nominal = "/nfs/dust/cms/group/zprime-uhh/AnalysisDNN_UL18/muon/";
  TString root_directory = "Zprime_SystVariations_DNN_output0"; // SR (TTbar node of DNN)
  TString save_directory = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/uncertainties/plots/";
  TString hist_name = "M_Zprime";

  TString systematic = "mcscale";
  vector<TString> v_samples = {
    // "TTbar",
    // "ST",
    // "WJets",
    "Diboson",
    // "DY",
    // "QCD",
    // "others", // DY + Diboson + QCD
    // "ZPrimeToTT_M500_W50",
    // "ZPrimeToTT_M1000_W100",
    // "ZPrimeToTT_M1400_W140",
    // "ZPrimeToTT_M2000_W200",
    // "ZPrimeToTT_M2500_W250",
    // "ZPrimeToTT_M3000_W300",
    // "ZPrimeToTT_M3500_W350",
    // "ZPrimeToTT_M4000_W400",
    // "ZPrimeToTT_M4500_W450",
    // "ZPrimeToTT_M5000_W500",
    // "ZPrimeToTT_M6000_W600",
    // "HscalarToTTTo1L1Nu2J_m400_w10p0_res",
    // "HscalarToTTTo1L1Nu2J_m400_w10p0_int_pos",
    // "HscalarToTTTo1L1Nu2J_m400_w10p0_int_neg",
    // "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res",
    // "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_pos",
    // "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_neg",
    // "ALP_ttbar_signal",
    // "ALP_ttbar_interference",
    "RSGluonToTT_M-500",
    "RSGluonToTT_M-1000",
    "RSGluonToTT_M-1500",
    "RSGluonToTT_M-2000",
    "RSGluonToTT_M-2500",
    "RSGluonToTT_M-3000",
    "RSGluonToTT_M-3500",
    "RSGluonToTT_M-4000",
    "RSGluonToTT_M-4500",
    "RSGluonToTT_M-5000",
    "RSGluonToTT_M-5500",
    "RSGluonToTT_M-6000",
    // "ZprimeDMToTTbarResoIncl_MZp1000_Mchi10_V1",
    // "ZprimeDMToTTbarResoIncl_MZp3000_Mchi10_V1",
    // "ZprimeDMToTTbarResoIncl_MZp5000_Mchi10_V1",
  };

  for(int i=0; i<v_samples.size(); i++){

    TString sample = v_samples.at(i);

    // nominal
    TFile *file = TFile::Open(input_directory + "uhh2.AnalysisModuleRunner.MC." + sample + ".root");
    file->cd(root_directory);
    TH1F *h_mcscale_up = (TH1F*) gDirectory->Get(hist_name + "_mcscale_up");
    TH1F *h_mcscale_down = (TH1F*) gDirectory->Get(hist_name + "_mcscale_down");

    TFile *file_nominal = TFile::Open(input_directory_nominal + "uhh2.AnalysisModuleRunner.MC." + sample + ".root");
    file_nominal->cd(root_directory);
    TH1F *h_nominal = (TH1F*) gDirectory->Get(hist_name);
    h_nominal->SetLineColor(kBlack);
    h_nominal->SetLineWidth(2);

    h_nominal->Rebin(10);
    h_mcscale_up->Rebin(10);
    h_mcscale_down->Rebin(10);

    h_mcscale_up->Divide(h_nominal);
    h_mcscale_down->Divide(h_nominal);

    h_mcscale_up->SetLineColor(kRed);
    h_mcscale_down->SetLineColor(kRed);

    h_mcscale_up->SetLineWidth(2);
    h_mcscale_down->SetLineWidth(2);

    h_mcscale_up->SetLineStyle(7);
    h_mcscale_down->SetLineStyle(3);


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
    double x_pos  = 0.7;
    double y_pos  = 0.7;
    double x_width = 0.2;
    double y_width = 0.1;
    TLegend *legend;
    legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
    legend->SetTextSize(0.025);
    legend->SetLineWidth(0);
    legend->SetNColumns(1);
    legend->AddEntry(h_mcscale_up,"mcscale_up","le");
    legend->AddEntry(h_mcscale_down,"mcscale_down","le");

    // draw
    h_mcscale_up->Draw("hist");
    h_mcscale_down->Draw("hist same");
    legend->Draw();

    // x axis
    h_mcscale_up->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
    h_mcscale_up->GetXaxis()->SetTitleOffset(1.3);
    h_mcscale_up->GetXaxis()->SetRangeUser(100,10000);
    // y axis
    h_mcscale_up->GetYaxis()->SetTitle("variation/nominal");
    h_mcscale_up->GetYaxis()->SetTitleOffset(1.7);
    h_mcscale_up->GetYaxis()->SetRangeUser(0.,2.);

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
  line1 = new TLine (0,1,10000,1);
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
  double x_pos = 0.17;
  double y_pos = 0.88;
  auto *systTag = new TLatex(3.5, 24, "#splitline{UL18 muon channel (SR):}{" + sample + "}");
  systTag->SetNDC();
  systTag->SetTextAlign(11);
  systTag->SetX(x_pos);
  systTag->SetY(y_pos);
  systTag->SetTextFont(62);
  systTag->SetTextSize(0.028);
  systTag->Draw();
}
