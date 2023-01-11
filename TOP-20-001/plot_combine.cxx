{
  TString input_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/TOP-20-001/output_combine/";
  TString save_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/TOP-20-001/plots_combine/";

  vector<TString> v_hists = {
    // "pt_thad",
    // "pt_tlep",
    // "ST",
    // "absy_thad",
    // "absy_tlep",
    // "deltaabsy_ttbar",
    // "absdeltay_ttbar",
    "mtt",
    // "pt_ttbar",
    // "absy_ttbar",
    // "phi_ttbar",
    // "cts",
    "cts_mtt250To420",
    "cts_mtt420To520",
    "cts_mtt520To620",
    "cts_mtt620To800",
    "cts_mtt800To1000",
    "cts_mtt1000To3500",
  };
  vector<TString> v_xlabel = {
    // "p_{T}(t_{h}) [GeV]",
    // "p_{T}(t_{l}) [GeV]",
    // "S_{T} [GeV]",
    // "|y(t_{h})|",
    // "|y(t_{l})|",
    // "#Delta|y_{t/#bar{t}}|",
    // "|#Deltay_{t/#bar{t}}|",
    "m(t#bar{t}) [GeV]",
    // "p_{T}(t#bar{t}) [GeV]",
    // "|y(t#bar{t})|",
    // "#phi_{t/#bar{t}}",
    // "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
    "cos(#theta*)",
  };

  vector<TString> v_binlabel = {
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    // "",
    "",
    // "",
    // "",
    // "",
    // "",
    "250 < m(t#bar{t}) < 420 GeV",
    "420 < m(t#bar{t}) < 520 GeV",
    "520 < m(t#bar{t}) < 620 GeV",
    "620 < m(t#bar{t}) < 800 GeV",
    "800 < m(t#bar{t}) < 1000 GeV",
    "1000 < m(t#bar{t}) < 3500 GeV",
  };
  vector<double> v_ylow = {
    // 2,
    // 2,
    // 2E+01,
    // 6E+03,
    // 6E+03,
    // 2E+03,
    // 6E+02,
    6E+01,
    // 6E+01,
    // 6E+03,
    // 2E+05,
    // 7E+02,
    7E+02,
    7E+02,
    7E+02,
    7E+02,
    7E+02,
    7E+02,
  };
  vector<double> v_yhigh = {
    // 9E+08,
    // 9E+08,
    // 9E+07,
    // 9E+07,
    // 9E+07,
    // 9E+08,
    // 9E+08,
    9E+07,
    // 9E+07,
    // 9E+07,
    // 9E+07,
    // 2E+08,
    2E+08,
    2E+08,
    2E+08,
    2E+08,
    2E+08,
    2E+08,
  };

  vector<TString> v_sample = {
    "TTToSemiLeptonic",
    "ALP_ttbar_signal",
    "ALP_ttbar_interference"
  };
  vector<int> v_color = {
    kBlue,
    kBlack,
    kGray
  };

  vector<TString> v_syst = {
    "datasyst",
    "pu",
    "isr",
    "fsr",
    "mcscale",
    "pdf"
  };
  vector<double> v_ratio_range = {
    0.5,
    0.05,
    0.05,
    0.05,
    0.5,
    0.05
  };


  for(int i=0; i<v_hists.size(); i++){ // hist loop
    for(int j=0; j<v_sample.size(); ++j){ // sample loop
      for(int k=0; k<v_syst.size(); ++k){ // syst loop
        if(j != 0 && k == 0) continue; // datasyst for TTToSemiLeptonic only

        TFile *file = TFile::Open(input_dir + "uhh2.AnalysisModuleRunner.MC." + v_sample.at(j) + ".root");
        TH1F *h = (TH1F*) gDirectory->Get(v_hists.at(i));
        TH1F *h_up = (TH1F*) gDirectory->Get(v_hists.at(i) + "_" + v_syst.at(k) + "_up");
        TH1F *h_down = (TH1F*) gDirectory->Get(v_hists.at(i) + "_" + v_syst.at(k) + "_down");

        TFile *file_data = TFile::Open(input_dir + "uhh2.AnalysisModuleRunner.DATA.data_obs.root");
        TH1F *h_data = (TH1F*) gDirectory->Get(v_hists.at(i));

        double upperpad_titlesize    = 0.04;
        double upperpad_topmargin    = 0.05;
        double upperpad_leftmargin   = 0.15;
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
        c1->SetLogy();
        c1->cd();

        // plotting options
        h->SetLineColor(v_color.at(j));
        h->SetLineWidth(2);
        h_up->SetLineColor(kGray);
        h_up->SetLineWidth(2);
        h_up->SetLineStyle(2);
        h_down->SetLineColor(kGray);
        h_down->SetLineWidth(2);
        h_down->SetLineStyle(9);

        h_data->SetMarkerStyle(20);
        h_data->SetMarkerColor(kBlack);
        h_data->SetLineColor(kBlack);

        // y axis
        h->GetYaxis()->SetTitle("Events");
        h->GetYaxis()->SetTitleOffset(2.1);
        h->GetYaxis()->SetRangeUser(v_ylow.at(i),v_yhigh.at(i));

        // legend
        double x_pos  = 0.52;
        double y_pos  = 0.77;
        double x_width =  0.25;
        double y_width =  0.15;
        TLegend *legend;
        legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
        legend->SetBorderSize(1);
        legend->SetTextSize(0.025);
        legend->SetLineWidth(0);
        legend->SetFillColor(0);
        legend->SetFillStyle(1001);
        legend->SetNColumns(1);
        legend->AddEntry(h, v_sample.at(j), "l");
        legend->AddEntry(h_up, v_syst.at(k) + " up", "l");
        legend->AddEntry(h_down, v_syst.at(k) + " down", "l");
        if(j == 0) legend->AddEntry(h_data, "Data (Phys. Rev. D 104, 092013)", "ep");

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
        x_pos = 0.19;
        y_pos = 0.895;
        auto *channel_tag = new TLatex(3.5, 24, "e/#mu+jets, parton level");
        channel_tag->SetNDC();
        channel_tag->SetTextAlign(11);
        channel_tag->SetX(x_pos);
        channel_tag->SetY(y_pos);
        channel_tag->SetTextFont(42);
        channel_tag->SetTextSize(0.025);

        // bin tag
        x_pos = 0.19;
        y_pos = 0.86;
        auto *bin_tag = new TLatex(3.5, 24, v_binlabel.at(i));
        bin_tag->SetNDC();
        bin_tag->SetTextAlign(11);
        bin_tag->SetX(x_pos);
        bin_tag->SetY(y_pos);
        bin_tag->SetTextFont(62);
        bin_tag->SetTextSize(0.025);

        // CMS tag
        x_pos = 0.15;
        y_pos = 0.957;
        auto *cms_tag = new TLatex(3.5, 24, "CMS Simulation (Private Work)");
        cms_tag->SetNDC();
        cms_tag->SetTextAlign(11);
        cms_tag->SetX(x_pos);
        cms_tag->SetY(y_pos);
        cms_tag->SetTextFont(62);
        cms_tag->SetTextSize(0.032);

        h->Draw("hist");
        h_up->Draw("hist same");
        h_down->Draw("hist same");
        h->Draw("hist same");
        if(j == 0) h_data->Draw("ep same");
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

        TH1F *h_ttbar_ratio = (TH1F*) h->Clone();
        TH1F *h_ttbar_up_ratio = (TH1F*) h_up->Clone();
        TH1F *h_ttbar_down_ratio = (TH1F*) h_down->Clone();
        TH1F *h_data_ratio = (TH1F*) h_data->Clone();
        h_ttbar_ratio->Divide(h);
        h_ttbar_up_ratio->Divide(h);
        h_ttbar_down_ratio->Divide(h);
        h_data_ratio->Divide(h);

        // x-axis
        h_ttbar_ratio->GetXaxis()->SetTitle(v_xlabel.at(i));
        h_ttbar_ratio->GetXaxis()->SetTitleSize(upperpad_titlesize * 10/3);
        h_ttbar_ratio->GetXaxis()->SetTitleOffset(1.2);
        h_ttbar_ratio->GetXaxis()->SetLabelSize(upperpad_titlesize * 10/3);
        h_ttbar_ratio->GetXaxis()->SetTickLength(0.1);
        // y-axis
        h_ttbar_ratio->GetYaxis()->SetTitle("#frac{Variation}{Pred.}");
        h_ttbar_ratio->GetYaxis()->CenterTitle(true);
        h_ttbar_ratio->GetYaxis()->SetTitleSize(upperpad_titlesize * 10/3);
        h_ttbar_ratio->GetYaxis()->SetTitleOffset(0.5);
        h_ttbar_ratio->GetYaxis()->SetLabelSize(upperpad_titlesize * 10/3);
        h_ttbar_ratio->GetYaxis()->SetNdivisions(-502);
        h_ttbar_ratio->SetMinimum(1. - v_ratio_range.at(k));
        h_ttbar_ratio->SetMaximum(1. + v_ratio_range.at(k));

        h_ttbar_ratio->Draw("hist");
        h_ttbar_up_ratio->Draw("hist same");
        h_ttbar_down_ratio->Draw("hist same");
        h_ttbar_ratio->Draw("hist same");
        if(j == 0) h_data_ratio->Draw("ep same");

        gPad->RedrawAxis();
        c1->Modified();
        c1->SaveAs(save_dir + v_hists.at(i) + "/" + v_hists.at(i) + "_" + v_sample.at(j) + "_" + v_syst.at(k) + ".pdf");
        c1->Close();
      } // syst loop
    } // sample loop
  } // hist loop
}
