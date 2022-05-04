{
  // options
  bool logyaxis   = true; // true/false
  bool afterDNN   = false; // true/false (false: before DNN, after full selection)
  TString year    = "combination"; // UL18/combination
  TString channel = "combination"; // electron/muon/combination
  TString region  = "SR1T"; // SR0T/SR1T/CR1/CR2

  // colors
  // SM backgrounds: filled histograms
  int color_ttbar   = 810;
  int color_wjets   = 416;
  int color_dy      = 400;
  int color_st      = 860;
  int color_qcd     = 867;
  int color_diboson = 880;
  // signal: line only
  int color_signal  = kBlack;


  // axes
  // x axis range
  double x_axis_lowerBound = 0;
  double x_axis_upperBound = 5E+03;
  // y axis range
  double y_axis_lowerBound = 1;
  double y_axis_upperBound = 5E+08;


  cout << endl;
  cout << "----- plotting options -----" << endl;
  cout << "              region: " + channel << endl;
  cout << "             channel: " + channel << endl;
  if(logyaxis) cout << "log scale for y axis: true" << endl; else cout << "log scale for y axis: false" << endl;
  cout << endl;


  // after full selection
  // TString dir      = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_102X_v2/2018/" + channel + "/ZPrime_lowmass_HOTVR/NOMINAL/";
  // TString histname = "M_Zprime_rebin2";
  // TString root_dir = "Chi2_General";

  // after full selection or DNN
  TString dir;
  if(afterDNN){
    if(year == "UL18"){
      dir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/" + year + "/" + channel + "/ZPrime_DeepAK8_afterDNN/";
    }
    else if (year == "combination"){
      dir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/" + year + "/ZPrime_DeepAK8_afterDNN/";
    }
  }
  else{
    if(year == "UL18"){
      if(channel == "muon")        dir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/" + year + "/" + channel + "/ZPrime_DeepAK8/NOMINAL/";
      if(channel == "electron")    dir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/" + year + "/" + channel + "/ZPrime_DeepAK8/";
      if(channel == "combination") dir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/" + year + "/" + channel + "/ZPrime_DeepAK8/";
    }
    else if(year == "combination"){
      dir = "/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/" + year + "/ZPrime_DeepAK8/";
    }
  }
  TString histname = "M_Zprime_rebin5";

  // select region
  TString root_dir;
  if(afterDNN){
    if (region == "SR0T") {
      root_dir = "DNN_output0_NoTopTag_General";
    } else if (region == "SR1T") {
      root_dir = "DNN_output0_TopTag_General";
    } else if (region == "CR1"){
      root_dir = "DNN_output1_General";
    } else if (region == "CR2"){
      root_dir = "DNN_output2_General";
    }
  }
  else{
    root_dir = "NNInputsBeforeReweight_General";
  }


  // ALP interference
  TFile *file_ALPinterference = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.ALP_ttbar_interference.root");
  file_ALPinterference->cd(root_dir);
  TH1F *h_ALPinterference = (TH1F*) gDirectory->Get(histname);
  h_ALPinterference->SetLineColor(kGray);
  h_ALPinterference->SetLineWidth(2);
  h_ALPinterference->SetLineStyle(2);

  TFile *file_ALPsignal = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.ALP_ttbar_signal.root");
  file_ALPsignal->cd(root_dir);
  TH1F *h_ALPsignal = (TH1F*) gDirectory->Get(histname);
  h_ALPsignal->SetLineColor(kBlack);
  h_ALPsignal->SetLineWidth(2);
  h_ALPsignal->SetLineStyle(2);


  // TTbar
  TFile *file_ttbar = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.TTbar.root");
  file_ttbar->cd(root_dir);
  TH1F *h_ttbar = (TH1F*) gDirectory->Get(histname);
  h_ttbar->SetLineColor(color_ttbar);
  h_ttbar->SetFillColor(color_ttbar);
  // WJets
  TFile *file_wjets = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.WJets.root");
  file_wjets->cd(root_dir);
  TH1F *h_wjets = (TH1F*) gDirectory->Get(histname);
  h_wjets->SetLineColor(color_wjets);
  h_wjets->SetFillColor(color_wjets);
  // DY
  TFile *file_dy = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.DY.root");
  file_dy->cd(root_dir);
  TH1F *h_dy = (TH1F*) gDirectory->Get(histname);
  h_dy->SetLineColor(color_dy);
  h_dy->SetFillColor(color_dy);
  // ST
  TFile *file_st = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.ST.root");
  file_st->cd(root_dir);
  TH1F *h_st = (TH1F*) gDirectory->Get(histname);
  h_st->SetLineColor(color_st);
  h_st->SetFillColor(color_st);
  // QCD
  TFile *file_qcd = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.QCD.root");
  file_qcd->cd(root_dir);
  TH1F *h_qcd = (TH1F*) gDirectory->Get(histname);
  h_qcd->SetLineColor(color_qcd);
  h_qcd->SetFillColor(color_qcd);
  // Diboson
  TFile *file_diboson = TFile::Open(dir + "uhh2.AnalysisModuleRunner.MC.Diboson.root");
  file_diboson->cd(root_dir);
  TH1F *h_diboson = (TH1F*) gDirectory->Get(histname);
  h_diboson->SetLineColor(color_diboson);
  h_diboson->SetFillColor(color_diboson);
  // stack backgrounds
  THStack stack("stack","SM backgrounds");
  stack.Add(h_diboson);
  stack.Add(h_qcd);
  stack.Add(h_st);
  stack.Add(h_dy);
  stack.Add(h_wjets);
  stack.Add(h_ttbar);

  // reversed stacking
  // stack.Add(h_ttbar);
  // stack.Add(h_wjets);
  // stack.Add(h_dy);
  // stack.Add(h_st);
  // stack.Add(h_qcd);
  // stack.Add(h_diboson);


  TH1F *h_bkg = (TH1F*) h_ttbar->Clone();
  h_bkg->Add(h_wjets);
  h_bkg->Add(h_dy);
  h_bkg->Add(h_st);
  h_bkg->Add(h_qcd);
  h_bkg->Add(h_diboson);


  // scaling
  double f_a = 5.0;
  double c_G = 7.5;
  double c_Phi = 7.5;
  double C = abs((c_G * c_Phi));
  double k = C / pow(f_a,2);
  double mu = pow(k,2);
  cout << "         f_a = " <<   f_a << endl;
  cout << "         c_G = " <<   c_G << endl;
  cout << "       c_Phi = " << c_Phi << endl;
  cout << "k = sqrt(mu) = " <<     k << endl;
  cout << "    k^2 = mu = " <<    mu << endl;
  cout << endl;



  TH1F *h_bkgplusALP = (TH1F*) h_ALPinterference->Clone();
  h_bkgplusALP->Scale(sqrt(mu));
  h_bkgplusALP->Add(h_ttbar);
  h_bkgplusALP->Add(h_wjets);
  h_bkgplusALP->Add(h_dy);
  h_bkgplusALP->Add(h_st);
  h_bkgplusALP->Add(h_qcd);
  h_bkgplusALP->Add(h_diboson);
  h_bkgplusALP->Add(h_ALPsignal,mu);
  h_bkgplusALP->SetLineColor(color_signal);
  h_bkgplusALP->SetLineWidth(2);
  h_bkgplusALP->SetLineStyle(2);


  // ratio as hist
  TH1F *h_ratio = (TH1F*) h_bkgplusALP->Clone();
  h_ratio->Divide(h_bkg);
  h_ratio->SetLineColor(kBlack);
  h_ratio->SetLineWidth(2);
  h_ratio->SetLineStyle(1);



  // lumi tag
  double x_pos = 0.95;
  double y_pos = 0.957;
  TLatex *lumitag = new TLatex(3.5,24,"138 fb^{-1} (13 TeV)");
  lumitag->SetNDC();
  lumitag->SetTextAlign(31);
  lumitag->SetX(x_pos);
  lumitag->SetY(y_pos);
  lumitag->SetTextFont(42);
  lumitag->SetTextSize(0.032);
  // channel tag
  x_pos = 0.5;
  y_pos = 0.9;
  TLatex *channeltag = new TLatex(3.5,24, region);
  // TLatex *channeltag = new TLatex(3.5,24, region + " (" + channel + " channel)");
  channeltag->SetNDC();
  channeltag->SetTextAlign(11);
  channeltag->SetX(x_pos);
  channeltag->SetY(y_pos);
  channeltag->SetTextFont(62);
  channeltag->SetTextSize(0.028);
  channeltag->SetLineColor(kBlack);
  channeltag->SetLineWidth(1);
  // legend
  x_pos  = 0.46;
  y_pos  = 0.64;
  double x_width =  0.3;
  double y_width =  0.25;
  TLegend *legend;
  legend = new TLegend(x_pos,y_pos,x_pos+x_width,y_pos+y_width);
  legend->SetBorderSize(1);
  legend->SetTextSize(0.025);
  legend->SetLineColor(0);
  legend->SetFillColor(0);
  legend->SetFillStyle(1001);
  legend->SetNColumns(1);
  legend->AddEntry(h_ttbar          ,"t#bar{t}"                                      ,"f");
  legend->AddEntry(h_wjets          ,"W#plusJets"                                 ,"f");
  legend->AddEntry(h_dy             ,"Drell-Yan"                                         ,"f");
  legend->AddEntry(h_st             ,"Single top"                                         ,"f");
  legend->AddEntry(h_qcd            ,"QCD"                                        ,"f");
  legend->AddEntry(h_diboson        ,"Diboson"                                    ,"f");
  // legend->AddEntry(h_ALPinterference,"ALP pure interference #times (-1)"          ,"l");
  // legend->AddEntry(h_ALPsignal      ,"ALP pure signal"                            ,"l");
  legend->AddEntry(h_bkgplusALP     ,"SM + ALP incl. interference (c_{i}/f_{a}=1.5)","l");

  // CMS logo
  x_pos = 0.18;
  y_pos = 0.915;
  TString cmslogo_text = "CMS";
  TLatex *cmslogo = new TLatex(3.5, 24, cmslogo_text);
  cmslogo->SetX(x_pos);
  cmslogo->SetY(y_pos);
  cmslogo->SetNDC();
  cmslogo->SetTextAlign(13);
  cmslogo->SetTextFont(62);
  cmslogo->SetTextSize(0.05);


  // sub line: simulation
  x_pos = 0.18;
  y_pos = 0.87;
  TString subline_text_sim = "Simulation";
  TLatex *subline_sim = new TLatex(3.5, 24, subline_text_sim);
  subline_sim->SetX(x_pos);
  subline_sim->SetY(y_pos);
  subline_sim->SetNDC();
  subline_sim->SetTextAlign(13);
  subline_sim->SetTextFont(52);
  subline_sim->SetTextSize(0.03);


  // sub line: private work
  x_pos = 0.18;
  y_pos = 0.84;
  TString subline_text_pw = "Work in Progress"; // Private Work or Work in Progress
  TLatex *subline_pw = new TLatex(3.5, 24, subline_text_pw);
  subline_pw->SetX(x_pos);
  subline_pw->SetY(y_pos);
  subline_pw->SetNDC();
  subline_pw->SetTextAlign(13);
  subline_pw->SetTextFont(52);
  subline_pw->SetTextSize(0.03);




  // plotting
  TCanvas *c1 = new TCanvas("c1","c1",0,0,800,800);

  // upper pad
  double upperpad_titlesize    = 0.04;
  double upperpad_topmargin    = 0.05;
  double upperpad_leftmargin   = 0.14;
  double upperpad_rightmargin  = 0.05;
  double upperpad_bottommargin = 0.25;
  double upperpad_width  = 1 - upperpad_leftmargin - upperpad_rightmargin;
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
  if(logyaxis) upperPad->SetLogy();
  upperPad->cd();
  // draw
  stack             .Draw("hist");
  // h_ALPinterference->Draw("hist same");
  // h_ALPsignal      ->Draw("hist same");
  h_bkgplusALP     ->Draw("hist same");
  lumitag          ->Draw("same");
  if(afterDNN) channeltag       ->Draw("same");
  legend           ->Draw("same");
  cmslogo->Draw();
  subline_sim->Draw();
  subline_pw->Draw();

  // x axis
  stack.GetXaxis()->SetRangeUser(x_axis_lowerBound,x_axis_upperBound);
  stack.GetXaxis()->SetNdivisions(50205);
  // y axis
  stack.GetYaxis()->SetTitle("Events");
  stack.GetYaxis()->SetTitleOffset(2.1);
  if(logyaxis){
    stack.SetMinimum(y_axis_lowerBound);
    stack.SetMaximum(y_axis_upperBound);
  }
  else{
    if(region == "SR0T"){
      stack.SetMaximum(1200000);
    }
    else if(region == "SR1T"){
      stack.SetMaximum(4000);
    }
    else if(region == "CR1"){
      stack.SetMaximum(10000);
    }
    else if(region == "CR2"){
      stack.SetMaximum(150000);
    }
  }

  // lower pad
  TPad *lowerPad = new TPad ("lowerPad","lowerPad",0.,0.,1,0.24);
  gStyle->SetOptStat(0);
  gStyle->SetOptTitle(kFALSE);
  lowerPad->Draw();
  lowerPad->SetTitle("lowerPad");
  lowerPad->SetTopMargin(0.0);
  lowerPad->SetLeftMargin(upperpad_leftmargin);
  lowerPad->SetRightMargin(upperpad_rightmargin);
  lowerPad->SetBottomMargin(0.35);
  lowerPad->SetTicks();
  // lowerPad->SetLogy();
  lowerPad->cd();




  // line at ratio = 1
  TLine *line1;
  line1 = new TLine (x_axis_lowerBound,1,x_axis_upperBound,1);
  line1->SetLineColor(kBlack);
  line1->SetLineWidth(1);
  line1->SetLineStyle(2);
  // draw
  h_ratio->Draw("hist");
  line1  ->Draw("same");
  // x axis
  h_ratio->GetXaxis()->SetTitle("m_{t#bar{t}} [GeV]");
  h_ratio->GetXaxis()->SetTitleSize(upperpad_titlesize * 10/3);
  h_ratio->GetXaxis()->SetTitleOffset(1.2);
  h_ratio->GetXaxis()->SetLabelSize(upperpad_titlesize * 10/3);
  h_ratio->GetXaxis()->SetRangeUser(x_axis_lowerBound,x_axis_upperBound);
  h_ratio->GetXaxis()->SetNdivisions(50205);
  h_ratio->GetXaxis()->SetTickLength(0.1);

  // y axis
  // TLatex yaxis_title =
  h_ratio->GetYaxis()->SetTitle("#frac{S+I+B}{B}");
  h_ratio->GetYaxis()->CenterTitle(true);
  h_ratio->GetYaxis()->SetTitleSize(upperpad_titlesize * 10/3);
  h_ratio->GetYaxis()->SetTitleOffset(0.5);
  h_ratio->GetYaxis()->SetLabelSize(upperpad_titlesize * 10/3);
  // h_ratio->GetYaxis()->SetRangeUser(0.5,1.5);
  // h_ratio->GetYaxis()->SetNdivisions(-502);
  h_ratio->SetMinimum(0.71);
  h_ratio->SetMaximum(1.29);

  c1->Modified();

  // saving

  TString save_dir;
  if(afterDNN){
    save_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/plots/";
  }
  else{
    save_dir = "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/plots_fullsel/";
  }



  if(logyaxis){
    if(year == "UL18"){
      if(afterDNN) c1->SaveAs(save_dir + "mttbar_" + region + "_" + year + "_" + channel + "_logscale.pdf");
      else         c1->SaveAs(save_dir + "mttbar_" + year + "_" + channel + "_logscale.pdf");
    }
    else if(year == "combination"){
      c1->SaveAs(save_dir + "mttbar_" + region + "_" + year + "_logscale.pdf");
    }
  }
  else{
    if(year == "UL18"){
      if(afterDNN) c1->SaveAs(save_dir + "mttbar_" + region + "_" + year + "_" + channel + ".pdf");
      else         c1->SaveAs(save_dir + "mttbar" + + year + "_" + channel + ".pdf");
    }
    else if(year == "combination"){
      c1->SaveAs(save_dir + "mttbar_" + region + "_" + year + ".pdf");
    }
  }
  c1->Close();


  // event yields
  double N_ttbar   = h_ttbar          ->Integral();
  double N_wjets   = h_wjets          ->Integral();
  double N_st      = h_st             ->Integral();
  double N_dy      = h_dy             ->Integral();
  double N_qcd     = h_qcd            ->Integral();
  double N_diboson = h_diboson        ->Integral();
  double N_total   = N_ttbar + N_wjets + N_dy + N_st + N_qcd + N_diboson;

  cout << "  relative amount of TTbar [%]: " <<   N_ttbar / N_total * 100. << endl;
  cout << "  relative amount of WJets [%]: " <<   N_wjets / N_total * 100. << endl;
  cout << "     relative amount of ST [%]: " <<      N_st / N_total * 100. << endl;
  cout << "     relative amount of DY [%]: " <<      N_dy / N_total * 100. << endl;
  cout << "    relative amount of QCD [%]: " <<     N_qcd / N_total * 100. << endl;
  cout << "relative amount of Diboson [%]: " << N_diboson / N_total * 100. << endl;
  cout << "        total number of events: " <<                    N_total << endl;

  // double N_alp_s   = h_ALPsignal      ->Integral();
  // double N_alp_i   = h_ALPinterference->Integral();



}
