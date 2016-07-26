//---------------------------------------------------------------
// this macro reads number of events with top jets 
//(tagged and not tagged) and calculates the top-tag efficiency
// in muon and electron channels separetly
//
// 11.07.2016
//---------------------------------------------------------------

void TopTagEff(){
  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJAnalysis/Selas2015_4fb_TopTag/T1_v01/";
  const int nch = 1;
  //  TString channels[nch] = {"muon","elec"};
  TString channels[nch] = {"muon"};
  //  TString channels[nch] = {"elec"};
  for(int chI = 0; chI <nch; chI++){
    //DATA
    TString fname_data = path+channels[chI]+"/uhh2.AnalysisModuleRunner.DATA.DATA.root";
    TFile *input_data = TFile::Open(fname_data);
    TH1I *htopjets_data = (TH1I*)input_data->Get("chi2/topjetN");
    TH1I *htoptags_data = (TH1I*)input_data->Get("chi2/toptagN");
    double err_nevt_topjets_data, err_nevt_toptags_data;
    int nevt_topjets_data = htopjets_data->IntegralAndError(2,htopjets_data->GetNbinsX(),err_nevt_topjets_data);
    int nevt_toptags_data = htoptags_data->IntegralAndError(2,htoptags_data->GetNbinsX(),err_nevt_toptags_data);
    // cout<<"DATA: "<<endl;
    // cout<<"nevt_topjets = "<<nevt_topjets_data<<" +/- "<<err_nevt_topjets_data<<endl;
    // cout<<"nevt_toptags = "<<nevt_toptags_data<<" +/- "<<err_nevt_toptags_data<<endl;
    // cout<<"-------"<<endl;
    //MC
    //WJets (light)
    TString fname_wjetsL = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.WJets_LNu__L.root";
    TFile *input_wjetsL = TFile::Open(fname_wjetsL);
    TH1I *htopjets_wjetsL = (TH1I*)input_wjetsL->Get("chi2/topjetN");
    TH1I *htoptags_wjetsL = (TH1I*)input_wjetsL->Get("chi2/toptagN");
    double err_nevt_topjets_wjetsL, err_nevt_toptags_wjetsL;
    int nevt_topjets_wjetsL = htopjets_wjetsL->IntegralAndError(2,htopjets_wjetsL->GetNbinsX(),err_nevt_topjets_wjetsL);
    int nevt_toptags_wjetsL = htoptags_wjetsL->IntegralAndError(2,htoptags_wjetsL->GetNbinsX(),err_nevt_toptags_wjetsL);
    // cout<<"W+JETS (Light): "<<endl;
    // cout<<"nevt_topjets = "<<nevt_topjets_wjetsL<<" +/- "<<err_nevt_topjets_wjetsL<<endl;
    // cout<<"nevt_toptags = "<<nevt_toptags_wjetsL<<" +/- "<<err_nevt_toptags_wjetsL<<endl;
    // cout<<"-------"<<endl;
    //WJets (b)
    TString fname_wjetsB = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.WJets_LNu__B.root";
    TFile *input_wjetsB = TFile::Open(fname_wjetsB);
    TH1I *htopjets_wjetsB = (TH1I*)input_wjetsB->Get("chi2/topjetN");
    TH1I *htoptags_wjetsB = (TH1I*)input_wjetsB->Get("chi2/toptagN");
    double err_nevt_topjets_wjetsB, err_nevt_toptags_wjetsB;
    int nevt_topjets_wjetsB = htopjets_wjetsB->IntegralAndError(2,htopjets_wjetsB->GetNbinsX(),err_nevt_topjets_wjetsB);
    int nevt_toptags_wjetsB = htoptags_wjetsB->IntegralAndError(2,htoptags_wjetsB->GetNbinsX(),err_nevt_toptags_wjetsB);
    // cout<<"W+JETS (b): "<<endl;
    // cout<<"nevt_topjets = "<<nevt_topjets_wjetsB<<" +/- "<<err_nevt_topjets_wjetsB<<endl;
    // cout<<"nevt_toptags = "<<nevt_toptags_wjetsB<<" +/- "<<err_nevt_toptags_wjetsB<<endl;
    // cout<<"-------"<<endl;
    //WJets (c)
    TString fname_wjetsC = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.WJets_LNu__C.root";
    TFile *input_wjetsC = TFile::Open(fname_wjetsC);
    TH1I *htopjets_wjetsC = (TH1I*)input_wjetsC->Get("chi2/topjetN");
    TH1I *htoptags_wjetsC = (TH1I*)input_wjetsC->Get("chi2/toptagN");
    double err_nevt_topjets_wjetsC, err_nevt_toptags_wjetsC;
    int nevt_topjets_wjetsC = htopjets_wjetsC->IntegralAndError(2,htopjets_wjetsC->GetNbinsX(),err_nevt_topjets_wjetsC);
    int nevt_toptags_wjetsC = htoptags_wjetsC->IntegralAndError(2,htoptags_wjetsC->GetNbinsX(),err_nevt_toptags_wjetsC);
    // cout<<"W+JETS (c): "<<endl;
    // cout<<"nevt_topjets = "<<nevt_topjets_wjetsC<<" +/- "<<err_nevt_topjets_wjetsC<<endl;
    // cout<<"nevt_toptags = "<<nevt_toptags_wjetsC<<" +/- "<<err_nevt_toptags_wjetsC<<endl;
    // cout<<"-------"<<endl;
    // cout<<"-------"<<endl;
    // //TTbar
    // TString fname_ttbar = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.TTbar.root";
    // TFile *input_ttbar = TFile::Open(fname_ttbar);
    // TH1I *htopjets_ttbar = (TH1I*)input_ttbar->Get("chi2/topjetN");
    // TH1I *htoptags_ttbar = (TH1I*)input_ttbar->Get("chi2/toptagN");
    // double err_nevt_topjets_ttbar, err_nevt_toptags_ttbar;
    // int nevt_topjets_ttbar = htopjets_ttbar->IntegralAndError(2,htopjets_ttbar->GetNbinsX(),err_nevt_topjets_ttbar);
    // int nevt_toptags_ttbar = htoptags_ttbar->IntegralAndError(2,htoptags_ttbar->GetNbinsX(),err_nevt_toptags_ttbar);
    // // cout<<"TTBAR: "<<endl;
    // // cout<<"nevt_topjets = "<<nevt_topjets_ttbar<<" +/- "<<err_nevt_topjets_ttbar<<endl;
    // // cout<<"nevt_toptags = "<<nevt_toptags_ttbar<<" +/- "<<err_nevt_toptags_ttbar<<endl;
    // // cout<<"-------"<<endl;

    //TTbar
    TString fname_ttbar = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.TTbar.root";
    TFile *input_ttbar = TFile::Open(fname_ttbar);
    TH1I *htopjets_ttbar = (TH1I*)input_ttbar->Get("chi2__TTAG/TAG____t");
    TH1I *htoptags_ttbar = (TH1I*)input_ttbar->Get("chi2__t1__TTAG/TAG____t");
    double err_nevt_topjets_ttbar, err_nevt_toptags_ttbar;
    int nevt_topjets_ttbar = htopjets_ttbar->IntegralAndError(0,htopjets_ttbar->GetNbinsX(),err_nevt_topjets_ttbar);
    int nevt_toptags_ttbar = htoptags_ttbar->IntegralAndError(0,htoptags_ttbar->GetNbinsX(),err_nevt_toptags_ttbar);
    cout<<"TTBAR (heavy): "<<endl;
    cout<<"nevt_topjets = "<<nevt_topjets_ttbar<<" +/- "<<err_nevt_topjets_ttbar<<endl;
    cout<<"nevt_toptags = "<<nevt_toptags_ttbar<<" +/- "<<err_nevt_toptags_ttbar<<endl;
    cout<<"-------"<<endl;

    TH1I *htopjets_ttbar_l = (TH1I*)input_ttbar->Get("chi2__TTAG/TAG____l");
    TH1I *htoptags_ttbar_l = (TH1I*)input_ttbar->Get("chi2__t1__TTAG/TAG____l");
    double err_nevt_topjets_ttbar_l, err_nevt_toptags_ttbar_l;
    int nevt_topjets_ttbar_l = htopjets_ttbar_l->IntegralAndError(0,htopjets_ttbar_l->GetNbinsX(),err_nevt_topjets_ttbar_l);
    int nevt_toptags_ttbar_l = htoptags_ttbar_l->IntegralAndError(0,htoptags_ttbar_l->GetNbinsX(),err_nevt_toptags_ttbar_l);
    cout<<"TTBAR (light): "<<endl;
    cout<<"nevt_topjets = "<<nevt_topjets_ttbar_l<<" +/- "<<err_nevt_topjets_ttbar_l<<endl;
    cout<<"nevt_toptags = "<<nevt_toptags_ttbar_l<<" +/- "<<err_nevt_toptags_ttbar_l<<endl;
    cout<<"-------"<<endl;

    //QCD
    TString fname_qcd = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.QCD_HT.root";
    TFile *input_qcd = TFile::Open(fname_qcd);
    TH1I *htopjets_qcd = (TH1I*)input_qcd->Get("chi2/topjetN");
    TH1I *htoptags_qcd = (TH1I*)input_qcd->Get("chi2/toptagN");
    double err_nevt_topjets_qcd, err_nevt_toptags_qcd;
    int nevt_topjets_qcd = htopjets_qcd->IntegralAndError(2,htopjets_qcd->GetNbinsX(),err_nevt_topjets_qcd);
    int nevt_toptags_qcd = htoptags_qcd->IntegralAndError(2,htoptags_qcd->GetNbinsX(),err_nevt_toptags_qcd);
    // cout<<"QCD: "<<endl;
    // cout<<"nevt_topjets = "<<nevt_topjets_qcd<<" +/- "<<err_nevt_topjets_qcd<<endl;
    // cout<<"nevt_toptags = "<<nevt_toptags_qcd<<" +/- "<<err_nevt_toptags_qcd<<endl;
    // cout<<"-------"<<endl;
    //DY
    TString fname_dy = path+channels[chI]+"/uhh2.AnalysisModuleRunner.MC.DYJetsToLL_NLO.root";
    TFile *input_dy = TFile::Open(fname_dy);
    TH1I *htopjets_dy = (TH1I*)input_dy->Get("chi2/topjetN");
    TH1I *htoptags_dy = (TH1I*)input_dy->Get("chi2/toptagN");
    double err_nevt_topjets_dy, err_nevt_toptags_dy;
    int nevt_topjets_dy = htopjets_dy->IntegralAndError(2,htopjets_dy->GetNbinsX(),err_nevt_topjets_dy);
    int nevt_toptags_dy = htoptags_dy->IntegralAndError(2,htoptags_dy->GetNbinsX(),err_nevt_toptags_dy);
    // cout<<"DY: "<<endl;
    // cout<<"nevt_topjets = "<<nevt_topjets_dy<<" +/- "<<err_nevt_topjets_dy<<endl;
    // cout<<"nevt_toptags = "<<nevt_toptags_dy<<" +/- "<<err_nevt_toptags_dy<<endl;
    // cout<<"-------"<<endl;
    cout<<"Channel: "<<channels[chI]<<endl;
    cout<<" Source & N$_{events}$ (AK8 jets) & N$_{events}$ (top-tagged jets) \\\\ \\hline"<<endl;
    cout<<" DATA & "<<nevt_topjets_data<<" $\\pm$ "<<Form("%.2f", err_nevt_topjets_data)<<" & "<<nevt_toptags_data<<" $\\pm$ "<<Form("%.2f", err_nevt_toptags_data)<<" \\\\ \\hline"<<endl;
    cout<<" W+Jets (light) & "<<nevt_topjets_wjetsL<<" $\\pm$ "<<Form("%.2f",err_nevt_topjets_wjetsL)<<" & "<<nevt_toptags_wjetsL<<" $\\pm$ "<<Form("%.2f",err_nevt_toptags_wjetsL)<<" \\\\ \\hline"<<endl;
    cout<<" W+Jets (b) & "<<nevt_topjets_wjetsB<<" $\\pm$ "<<Form("%.2f",err_nevt_topjets_wjetsB)<<" & "<<nevt_toptags_wjetsB<<" $\\pm$ "<<Form("%.2f",err_nevt_toptags_wjetsB)<<" \\\\ \\hline"<<endl;
    cout<<" W+Jets (c) & "<<nevt_topjets_wjetsC<<" $\\pm$ "<<Form("%.2f",err_nevt_topjets_wjetsC)<<" & "<<nevt_toptags_wjetsC<<" $\\pm$ "<<Form("%.2f",err_nevt_toptags_wjetsC)<<" \\\\ \\hline \\hline"<<endl;
    cout<<"TTbar (t) & "<<nevt_topjets_ttbar<<" $\\pm$ "<<Form("%.2f",err_nevt_topjets_ttbar)<<" & "<<nevt_toptags_ttbar<<" $\\pm$ "<<Form("%.2f",err_nevt_toptags_ttbar)<<" \\\\ \\hline"<<endl;
    cout<<"TTbar (light) & "<<nevt_topjets_ttbar_l<<" $\\pm$ "<<Form("%.2f",err_nevt_topjets_ttbar_l)<<" & "<<nevt_toptags_ttbar_l<<" $\\pm$ "<<Form("%.2f",err_nevt_toptags_ttbar_l)<<" \\\\ \\hline"<<endl;
    cout<<"QCD & "<<nevt_topjets_qcd<<" $\\pm$ "<<Form("%.2f",err_nevt_topjets_qcd)<<" & "<<nevt_toptags_qcd<<" $\\pm$ "<<Form("%.2f",err_nevt_toptags_qcd)<<" \\\\ \\hline"<<endl;
    cout<<"DY &  "<<nevt_topjets_dy<<" $\\pm$ "<<Form("%.2f",err_nevt_topjets_dy)<<" & "<<nevt_toptags_dy<<" $\\pm$ "<<Form("%.2f",err_nevt_toptags_dy)<<" \\\\ \\hline"<<endl;

    /* double MC_yeild_topjets = nevt_topjets_wjetsL+nevt_topjets_wjetsB+nevt_topjets_wjetsC;
    double err_MC_yeild_topjets = sqrt(TMath::Power(err_nevt_topjets_wjetsL,2)+TMath::Power(err_nevt_topjets_wjetsB,2)+TMath::Power(err_nevt_topjets_wjetsC,2));
    double MC_yeild_toptags = nevt_toptags_wjetsL+nevt_toptags_wjetsB+nevt_toptags_wjetsC;
    double err_MC_yeild_toptags = sqrt(err_nevt_toptags_wjetsL*err_nevt_toptags_wjetsL+err_nevt_toptags_wjetsB*err_nevt_toptags_wjetsB+err_nevt_toptags_wjetsC*err_nevt_toptags_wjetsC);*/
    double MC_yeild_topjets = nevt_topjets_wjetsL+nevt_topjets_wjetsB+nevt_topjets_wjetsC+nevt_topjets_qcd+nevt_topjets_dy+nevt_topjets_ttbar_l;
    double err_MC_yeild_topjets = sqrt(TMath::Power(err_nevt_topjets_wjetsL,2)+TMath::Power(err_nevt_topjets_wjetsB,2)+TMath::Power(err_nevt_topjets_wjetsC,2)
				       +TMath::Power(err_nevt_topjets_ttbar,2)+TMath::Power(err_nevt_topjets_dy,2)+TMath::Power(err_nevt_topjets_ttbar_l,2));
    double MC_yeild_toptags = nevt_toptags_wjetsL+nevt_toptags_wjetsB+nevt_toptags_wjetsC+nevt_toptags_qcd+nevt_toptags_dy+nevt_toptags_ttbar_l;
    double err_MC_yeild_toptags = sqrt(TMath::Power(err_nevt_toptags_wjetsL,2)+TMath::Power(err_nevt_toptags_wjetsB,2)+TMath::Power(err_nevt_toptags_wjetsC,2)
				       +TMath::Power(err_nevt_toptags_qcd,2)+TMath::Power(err_nevt_toptags_dy,2)+TMath::Power(err_nevt_toptags_ttbar_l,2));

    double eff_MC = MC_yeild_toptags/MC_yeild_topjets;
    //    double err_eff_MC = sqrt(TMath::Power(MC_yeild_toptags,2)*(MC_yeild_topjets+MC_yeild_toptags)/TMath::Power(MC_yeild_topjets,3));
    double err_eff_MC = eff_MC*sqrt(TMath::Power(err_MC_yeild_toptags/MC_yeild_toptags,2)+TMath::Power(err_MC_yeild_topjets/MC_yeild_topjets,2));
    // cout<<"MC: topjets = "<<MC_yeild_topjets<<" +/- "<<err_MC_yeild_topjets<<" top-tag = "<<MC_yeild_toptags<<" +/- "<<err_MC_yeild_toptags<<endl;
    // cout<<"Eff MC = "<<eff_MC<<" +/- "<<err_eff_MC<<endl;

    /*    double DATA_yeild_topjets = nevt_topjets_data - nevt_topjets_ttbar;
    double err_DATA_yeild_topjets = sqrt(TMath::Power(err_nevt_topjets_data,2)+TMath::Power(err_nevt_topjets_ttbar,2));
    double DATA_yeild_toptags = nevt_toptags_data - nevt_toptags_ttbar;
    double err_DATA_yeild_toptags = sqrt(TMath::Power(err_nevt_toptags_data,2)+TMath::Power(err_nevt_toptags_ttbar,2));
    double eff_DATA = DATA_yeild_toptags/DATA_yeild_topjets;
    double err_eff_DATA = eff_DATA*sqrt(TMath::Power(err_DATA_yeild_toptags/DATA_yeild_toptags,2)+TMath::Power(err_DATA_yeild_topjets/DATA_yeild_topjets,2)); */

    double DATA_yeild_topjets = nevt_topjets_data - nevt_topjets_ttbar - nevt_topjets_qcd - nevt_topjets_dy;
    double err_DATA_yeild_topjets = sqrt(TMath::Power(err_nevt_topjets_data,2)+TMath::Power(err_nevt_topjets_ttbar,2)+TMath::Power(err_nevt_topjets_qcd,2)+TMath::Power(err_nevt_topjets_dy,2));
    double DATA_yeild_toptags = nevt_toptags_data - nevt_toptags_ttbar - nevt_toptags_qcd - nevt_toptags_dy;
    double err_DATA_yeild_toptags = sqrt(TMath::Power(err_nevt_toptags_data,2)+TMath::Power(err_nevt_toptags_ttbar,2)+TMath::Power(err_nevt_toptags_qcd,2)+TMath::Power(err_nevt_toptags_dy,2));

    double eff_DATA = DATA_yeild_toptags/DATA_yeild_topjets;
    double err_eff_DATA = eff_DATA*sqrt(TMath::Power(err_DATA_yeild_toptags/DATA_yeild_toptags,2)+TMath::Power(err_DATA_yeild_topjets/DATA_yeild_topjets,2)); 

    double SF = eff_DATA/eff_MC;
    double err_SF = SF*sqrt(TMath::Power(err_eff_MC/eff_MC,2)+TMath::Power(err_eff_DATA/eff_DATA,2));
    // cout<<"DATA: topjets = "<<DATA_yeild_topjets<<" +/- "<<err_DATA_yeild_topjets<<" top-tag = "<<DATA_yeild_toptags<<" +/- "<<err_DATA_yeild_toptags<<endl;
    // cout<<"Eff DATA = "<<eff_DATA<<" +/- "<<err_eff_DATA<<endl;
    cout<<"CR & $\\varepsilon_{DATA}$ & $\\varepsilon_{MC}$ & DATA/MC SF "<<endl;
    // cout<<"$\\mu$+jets & "
    if(channels[chI]=="elec")    cout<<"$e$+jets & ";
    if(channels[chI]=="muon")  cout<<"$\\mu$+jets & ";
     cout<<Form("%.3f",eff_DATA)<<" $\\pm$ "<<Form("%.3f",err_eff_DATA)<<" & "<<Form("%.3f",eff_MC)<<" $\\pm$ "<<Form("%.3f",err_eff_MC)
	 <<" & "<<Form("%.2f",SF)<<" $\\pm$ "<<Form("%.2f",err_SF)<<endl;
  }
}
