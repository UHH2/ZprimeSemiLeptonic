{
  TString input_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/TOP-20-001/output_diffxsec/";
  TString save_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/TOP-20-001/plots_diffxsec/";

  vector<TString> v_hists = {
    "pt_thad",
    "pt_tlep",
    "ST",
    "absy_thad",
    "absy_tlep",
    "deltaabsy_ttbar",
    "absdeltay_ttbar",
    "mtt",
    "pt_ttbar",
    "absy_ttbar",
    "phi_ttbar",
    "cts",
    "cts_mtt250To420",
    "cts_mtt420To520",
    "cts_mtt520To620",
    "cts_mtt620To800",
    "cts_mtt800To1000",
    "cts_mtt1000To3500",
  };
  vector<TString> v_xlabel = {
    "p_{T}(t_{h}) [GeV]",
    "p_{T}(t_{l}) [GeV]",
    "S_{T} [GeV]",
    "|y(t_{h})|",
    "|y(t_{l})|",
    "#Delta|y_{t/#bar{t}}|",
    "|#Deltay_{t/#bar{t}}|",
    "m(t#bar{t}) [GeV]",
    "p_{T}(t#bar{t}) [GeV]",
    "|y(t#bar{t})|",
    "#phi_{t/#bar{t}}",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
  };
  vector<TString> v_ylabel = {
    "#frac{d#sigma}{dp_{T}(t_{h})} [pb GeV^{-1}]",
    "#frac{d#sigma}{dp_{T}(t_{l})} [pb GeV^{-1}]",
    "#frac{d#sigma}{dS_{T}} [pb GeV^{-1}]",
    "#frac{d#sigma}{d|y(t_{h})|} [pb]",
    "#frac{d#sigma}{d|y(t_{l})|} [pb]",
    "#frac{d#sigma}{d#Delta|y_{t/#bar{t}}|} [pb]",
    "#frac{d#sigma}{d|#Deltay_{t/#bar{t}}|} [pb]",
    "#frac{d#sigma}{dm(t#bar{t})} [pb GeV^{-1}]",
    "#frac{d#sigma}{dp_{T}(t#bar{t})} [pb GeV^{-1}]",
    "#frac{d#sigma}{d|y(t#bar{t})|)} [pb]",
    "#frac{d#sigma}{d#phi_{t/#bar{t}}} [pb]",
    "#frac{d#sigma}{dcos(#theta*)} [pb]",
    "#frac{d#sigma}{dm(t#bar{t}) dcos(#theta*)} [pb GeV^{-1}]",
    "#frac{d#sigma}{dm(t#bar{t}) dcos(#theta*)} [pb GeV^{-1}]",
    "#frac{d#sigma}{dm(t#bar{t}) dcos(#theta*)} [pb GeV^{-1}]",
    "#frac{d#sigma}{dm(t#bar{t}) dcos(#theta*)} [pb GeV^{-1}]",
    "#frac{d#sigma}{dm(t#bar{t}) dcos(#theta*)} [pb GeV^{-1}]",
    "#frac{d#sigma}{dm(t#bar{t}) dcos(#theta*)} [pb GeV^{-1}]",
  };
  vector<TString> v_binlabel = {
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "",
    "250 < m_{t#bar{t}} < 420 GeV",
    "420 < m_{t#bar{t}} < 520 GeV",
    "520 < m_{t#bar{t}} < 620 GeV",
    "620 < m_{t#bar{t}} < 800 GeV",
    "800 < m_{t#bar{t}} < 1000 GeV",
    "1000 < m_{t#bar{t}} < 3500 GeV",
  };
  vector<double> v_ylow = {
    5E-08,
    5E-08,
    2E-07,
    0.01,
    0.01,
    0.01,
    0.01,
    3E-07,
    3E-05,
    0.01,
    0.05,
    51,
    0.01,
    0.01,
    0.01,
    0.001,
    0.001,
    1E-04,
  };
  vector<double> v_yhigh = {
    50,
    50,
    5,
    199.9,
    199.9,
    199.9,
    199.9,
    9,
    9,
    199.9,
    200,
    299,
    0.499,
    1.199,
    0.599,
    0.299,
    0.099,
    4.99E-03,
  };

  for(int i=0; i<v_hists.size(); i++){

    TFile *file_ttbar = TFile::Open(input_dir + "uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic.root");
    TH1F *h_ttbar = (TH1F*) gDirectory->Get(v_hists.at(i));

    TFile *file_signal = TFile::Open(input_dir + "uhh2.AnalysisModuleRunner.MC.ALP_ttbar_signal.root");
    TH1F *h_signal = (TH1F*) gDirectory->Get(v_hists.at(i));

    TFile *file_interference = TFile::Open(input_dir + "uhh2.AnalysisModuleRunner.MC.ALP_ttbar_interference.root");
    TH1F *h_interference = (TH1F*) gDirectory->Get(v_hists.at(i));

    TFile *file_data = TFile::Open(input_dir + "uhh2.AnalysisModuleRunner.DATA.data_obs.root");
    TH1F *h_data = (TH1F*) gDirectory->Get(v_hists.at(i));
    for(int i=0; i<h_data->GetNbinsX(); ++i){
      h_data->SetBinError(i+1, 0.);
    }
    TH1F *h_data_errStat = (TH1F*) gDirectory->Get(v_hists.at(i) + "_errStat");
    TH1F *h_data_errSyst = (TH1F*) gDirectory->Get(v_hists.at(i) + "_errSyst");
    TH1F *h_data_plot_errStat = (TH1F*) h_data_errStat->Clone();
    TH1F *h_data_plot_errTotal = (TH1F*) h_data_errSyst->Clone();

    for(int j=0; j<h_data_plot_errStat->GetNbinsX(); ++j){
      h_data_plot_errStat->SetBinContent(j+1, h_data->GetBinContent(j+1));
      h_data_plot_errStat->SetBinError(j+1, h_data_errStat->GetBinContent(j+1));
    }
    for(int j=0; j<h_data_plot_errTotal->GetNbinsX(); ++j){
      h_data_plot_errTotal->SetBinContent(j+1, h_data->GetBinContent(j+1));
      h_data_plot_errTotal->SetBinError(j+1, sqrt(pow(h_data_errStat->GetBinContent(j+1), 2) + pow(h_data_errSyst->GetBinContent(j+1), 2)));
    }

    double upperpad_titlesize    = 0.04;
    double upperpad_topmargin    = 0.05;
    double upperpad_leftmargin   = 0.20;
    double upperpad_rightmargin  = 0.05;
    double upperpad_bottommargin = 0.25;
    double upperpad_width  = 1 - upperpad_leftmargin - upperpad_rightmargin;
    double upperpad_height = 1 - upperpad_topmargin - upperpad_bottommargin;

    auto c1 = new TCanvas("c1","c1",0,0,800,800);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    c1->Draw();
    c1->SetTopMargin(upperpad_topmargin);
    c1->SetBottomMargin(upperpad_bottommargin);
    c1->SetLeftMargin(upperpad_leftmargin);
    c1->SetRightMargin(upperpad_rightmargin);
    c1->SetTicks();
    if(i==0 || i==1 || i==2 || i==7 || i==8 || i==10) c1->SetLogy();
    c1->cd();

    // plotting options
    h_ttbar->SetLineColor(kBlue);
    h_ttbar->SetLineWidth(2);
    h_ttbar->SetMarkerColor(kBlue);
    h_ttbar->SetMarkerStyle(1); // 24
    h_signal->SetLineColor(kBlack);
    h_signal->SetLineWidth(2);
    h_signal->SetLineStyle(7);
    h_interference->SetLineColor(kGray);
    h_interference->SetLineWidth(2);
    h_interference->SetLineStyle(7);
    h_data->SetMarkerStyle(20);
    h_data->SetMarkerColor(kBlack);
    // h_data->SetLineColor(kBlack);

    // y axis
    h_data_plot_errTotal->GetYaxis()->SetTitle(v_ylabel.at(i));
    h_data_plot_errTotal->GetYaxis()->SetTitleOffset(2.8);
    h_data_plot_errTotal->GetYaxis()->SetRangeUser(v_ylow.at(i),v_yhigh.at(i));

    // legend
    double x_pos  = 0.52;
    double y_pos  = 0.72;
    double x_width =  0.25;
    double y_width =  0.2;
    TLegend *legend;
    legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
    legend->SetBorderSize(1);
    legend->SetTextSize(0.025);
    legend->SetLineWidth(0);
    legend->SetFillColor(0);
    legend->SetFillStyle(1001);
    legend->SetNColumns(1);
    legend->AddEntry(h_data, "Data (Phys. Rev. D 104, 092013)", "p");
    legend->AddEntry(h_data_plot_errTotal, "Syst. #oplus Stat.", "f");
    legend->AddEntry(h_data_plot_errStat, "Stat.", "f");
    legend->AddEntry(h_ttbar, "POWHEG P8 (CP5)", "ep");
    legend->AddEntry(h_signal, "ALP signal", "l");
    legend->AddEntry(h_interference, "ALP-SM interference", "l");

    // lumi tag
    x_pos = 0.95;
    y_pos = 0.957;
    auto *lumitag = new TLatex(3.5, 24, "137 fb^{-1} (13 TeV)");
    lumitag->SetNDC();
    lumitag->SetTextAlign(31);
    lumitag->SetX(x_pos);
    lumitag->SetY(y_pos);
    lumitag->SetTextFont(42);
    lumitag->SetTextSize(0.032);

    // channel tag
    x_pos = 0.24;
    y_pos = 0.895;
    auto *channel_tag = new TLatex(3.5, 24, "e/#mu+jets, parton level");
    channel_tag->SetNDC();
    channel_tag->SetTextAlign(11);
    channel_tag->SetX(x_pos);
    channel_tag->SetY(y_pos);
    channel_tag->SetTextFont(42);
    channel_tag->SetTextSize(0.025);

    // bin tag
    x_pos = 0.24;
    y_pos = 0.86;
    auto *bin_tag = new TLatex(3.5, 24, v_binlabel.at(i));
    bin_tag->SetNDC();
    bin_tag->SetTextAlign(11);
    bin_tag->SetX(x_pos);
    bin_tag->SetY(y_pos);
    bin_tag->SetTextFont(62);
    bin_tag->SetTextSize(0.025);

    // CMS tag
    x_pos = 0.20;
    y_pos = 0.957;
    auto *cms_tag = new TLatex(3.5, 24, "CMS Simulation (Private Work)");
    cms_tag->SetNDC();
    cms_tag->SetTextAlign(11);
    cms_tag->SetX(x_pos);
    cms_tag->SetY(y_pos);
    cms_tag->SetTextFont(62);
    cms_tag->SetTextSize(0.032);



    // draw
    h_data_plot_errTotal->SetFillColor(kGray+2);
    h_data_plot_errTotal->SetLineWidth(0);
    h_data_plot_errTotal->SetFillStyle(1001);
    h_data_plot_errStat->SetFillColor(kGray);
    h_data_plot_errStat->SetLineWidth(0);
    h_data_plot_errStat->SetFillStyle(1001);

    h_data_plot_errTotal->Draw("e2");
    h_data_plot_errStat->Draw("e2 same");
    h_data->Draw("p same");
    h_ttbar->Draw("ep same");
    h_signal->Draw("hist same");
    h_interference->Draw("hist same");
    legend->Draw("same");
    cms_tag->Draw("same");
    channel_tag->Draw("same");
    bin_tag->Draw("same");
    lumitag->Draw("same");
    gPad->RedrawAxis();


    // lower pad
    TPad *lowerPad = new TPad ("lowerPad","lowerPad",0.,0.,1,0.24);
    gStyle->SetOptStat(0);
    gStyle->SetOptTitle(kFALSE);
    lowerPad->Draw();
    lowerPad->SetTitle("lowerPad");
    lowerPad->SetTopMargin(0.05);
    lowerPad->SetLeftMargin(upperpad_leftmargin);
    lowerPad->SetRightMargin(upperpad_rightmargin);
    lowerPad->SetBottomMargin(0.35);
    lowerPad->SetTicks();
    lowerPad->cd();

    // hist at 1
    TH1F *hist_ratio_errStat = (TH1F*) h_data_errStat->Clone();
    for(int j=0; j<hist_ratio_errStat->GetNbinsX(); ++j){
      hist_ratio_errStat->SetBinError(j+1, (h_data_errStat->GetBinContent(j+1) / h_data->GetBinContent(j+1)));
      hist_ratio_errStat->SetBinContent(j+1, 1.);
    }

    TH1F *hist_ratio_errTot = (TH1F*) h_data_errStat->Clone();
    for(int j=0; j<hist_ratio_errTot->GetNbinsX(); ++j){
      hist_ratio_errTot->SetBinError(j+1, (sqrt(pow(h_data_errStat->GetBinContent(j+1), 2) + pow(h_data_errSyst->GetBinContent(j+1), 2)) / h_data->GetBinContent(j+1)));
      hist_ratio_errTot->SetBinContent(j+1, 1.);
    }



    // x-axis
    hist_ratio_errTot->GetXaxis()->SetTitle(v_xlabel.at(i));
    hist_ratio_errTot->GetXaxis()->SetTitleSize(upperpad_titlesize * 10/3);
    hist_ratio_errTot->GetXaxis()->SetTitleOffset(1.2);
    hist_ratio_errTot->GetXaxis()->SetLabelSize(upperpad_titlesize * 10/3);
    hist_ratio_errTot->GetXaxis()->SetTickLength(0.1);
    // y-axis
    hist_ratio_errTot->GetYaxis()->SetTitle("#frac{Pred.}{Data}");
    hist_ratio_errTot->GetYaxis()->CenterTitle(true);
    hist_ratio_errTot->GetYaxis()->SetTitleSize(upperpad_titlesize * 10/3);
    hist_ratio_errTot->GetYaxis()->SetTitleOffset(0.75);
    hist_ratio_errTot->GetYaxis()->SetLabelSize(upperpad_titlesize * 10/3);
    hist_ratio_errTot->GetYaxis()->SetNdivisions(-502);
    hist_ratio_errTot->SetMinimum(0.5);
    hist_ratio_errTot->SetMaximum(1.5);


    hist_ratio_errTot->DrawCopy();
    hist_ratio_errTot->SetFillColor(kGray+2);
    hist_ratio_errTot->SetFillStyle(1001);
    hist_ratio_errTot->Draw("E2 same");

    hist_ratio_errStat->DrawCopy("hist same");
    hist_ratio_errStat->SetFillColor(kGray);
    hist_ratio_errStat->SetFillStyle(1001);
    hist_ratio_errStat->Draw("e2 same");

    // line at ratio = 1
    TLine *line1;
    double line_xlow = h_ttbar->GetBinLowEdge(1);
    double line_xhigh = h_ttbar->GetBinLowEdge(h_ttbar->GetNbinsX()+1);
    line1 = new TLine (line_xlow,1,line_xhigh,1);
    line1->SetLineColor(kBlack);
    line1->SetLineWidth(1);
    line1->Draw();

    TH1F *h_ratio_ttbar = (TH1F*) h_ttbar->Clone();
    h_ratio_ttbar->Divide(h_data);
    h_ratio_ttbar->Draw("ep same");

    gPad->RedrawAxis();
    c1->Modified();
    c1->SaveAs(save_dir + v_hists.at(i) + ".pdf");
    c1->Close();
  }
}
