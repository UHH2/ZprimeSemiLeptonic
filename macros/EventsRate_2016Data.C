//---------------------------------------------------------------
// this macro reads number of events/lumi in the data file
// and put some run info on the plot
// 23.11.2016
//---------------------------------------------------------------

//#include "tdrstyle_mod15.C"

void EventsRate_2016Data(){
  int miny = 0;
  int maxy = 1500;
  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/ElecID_MVA_loose_PartI_CutBased_03FebDATA_NOelecHLTSF_btagSFsMoriond_23fb_EGReg_looseJetID_slimmedMETsMuEGClean/T1_v06/";
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_271036_284044_JSON_Mtt_shrink_Leppt60_Jetpt180/elec/";
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_271036_284044_JSON_Mtt_shrink/elec/";
  TString fname_data = path+"uhh2.AnalysisModuleRunner.DATA.DATA.root";
  TFile *input_data = TFile::Open(fname_data);
  TH1 *rate_data = (TH1*)input_data->Get("lumi/luminosity");
  //  TH1D *rate_data = (TH1D*)input_data->Get("chi2/pvN");
  rate_data->SetMarkerStyle(20);
  rate_data->SetMarkerSize(2.5);
  rate_data->GetXaxis()->SetTitle("luminosity, pb^{-1}");
  rate_data->GetYaxis()->SetTitle("Events/250 pb^{-1}");
  rate_data->GetYaxis()->SetRangeUser(miny,maxy);
  //  rate_data->GetYaxis()->SetRangeUser(0,1100);
  rate_data->SetTitle("");
  rate_data->Draw("");


  TString path2 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/ElecID_MVA_loose_PartI_CutBased_03FebDATA_NOelecHLTSF_btagSFsMoriond_23fb/T1_v06/";
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_271036_284044_JSON_Mtt_shrink_Leppt60_Jetpt180/elec/";
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_271036_284044_JSON_Mtt_shrink/elec/";
  TString fname_data2 = path2+"uhh2.AnalysisModuleRunner.DATA.DATA.root";
  TFile *input_data2 = TFile::Open(fname_data2);
  TH1 *rate_data2 = (TH1*)input_data2->Get("lumi/luminosity");
  //  TH1D *rate_data = (TH1D*)input_data->Get("chi2/pvN");
  rate_data2->SetMarkerStyle(24);
  rate_data2->SetMarkerSize(2.5);
  rate_data2->GetXaxis()->SetTitle("luminosity, pb^{-1}");
  rate_data2->GetYaxis()->SetTitle("Events/250 pb^{-1}");
  //  rate_data2->GetYaxis()->SetRangeUser(miny,maxy);
  rate_data2->SetTitle("");
  rate_data2->Draw("same");

 TString path3 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/ElecID_MVA_loose_PartI_CutBased_elecPt65_jet1Pt185_jet2Pt50_elecHLTSF/T1_v06/";
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_271036_284044_JSON_Mtt_shrink_Leppt60_Jetpt180/elec/";
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_271036_284044_JSON_Mtt_shrink/elec/";
  TString fname_data3 = path3+"uhh2.AnalysisModuleRunner.DATA.DATA.root";
  TFile *input_data3 = TFile::Open(fname_data3);
  TH1 *rate_data3 = (TH1*)input_data3->Get("lumi/luminosity");
  //  TH1D *rate_data = (TH1D*)input_data->Get("chi2/pvN");
  rate_data3->SetMarkerStyle(31);
  rate_data3->SetMarkerColor(2);
  rate_data3->SetMarkerSize(2.5);
  //  rate_data3->GetXaxis()->SetTitle("luminosity, pb^{-1}");
  //  rate_data3->GetYaxis()->SetTitle("Events/250 pb^{-1}");
  //  rate_data2->GetYaxis()->SetRangeUser(miny,maxy);
  rate_data3->SetTitle("");
  rate_data3->Draw("same");

  TLine *RunB = new TLine (5892,miny,5892,maxy);
  RunB->SetLineWidth(2);
  RunB->SetLineStyle(2);
  RunB->Draw("same");
  TLine *RunC = new TLine (8538,miny,8538,maxy);
  RunC->SetLineWidth(2);
  RunC->SetLineStyle(2);
  RunC->Draw("same");
  TLine *RunD = new TLine (12891,miny,12891,maxy);
  RunD->SetLineWidth(2);
  RunD->SetLineStyle(2);
  RunD->Draw("same");
  TLine *RunE = new TLine (16941,miny,16941,maxy);
  RunE->SetLineWidth(2);
  RunE->SetLineStyle(2);
  RunE->Draw("same");
  TLine *RunF = new TLine (20101,miny,20101,maxy);
  RunF->SetLineWidth(2);
  RunF->SetLineStyle(2);
  RunF->Draw("same");
  TLine *RunG = new TLine (27655,miny,27655,maxy);
  RunG->SetLineWidth(2);
  RunG->SetLineStyle(2);
  RunG->Draw("same");

   auto legend = new TLegend(0.7,0.7,0.98,0.95);
   //   legend->SetHeader("The Legend Title","C"); // option "C" allows to center the header
   legend->AddEntry(rate_data,"03Feb NEW","p");
   legend->AddEntry(rate_data2,"03Feb OLD","p");
   legend->AddEntry(rate_data3,"23Sep OLD","p");
   //   legend->AddEntry("f1","Function abs(#frac{sin(x)}{x})","l");
   //   legend->AddEntry("gr","Graph with error bars","lep");
   legend->Draw();
}
