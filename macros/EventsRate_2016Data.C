//---------------------------------------------------------------
// this macro reads number of events/lumi in the data file
// and put some run info on the plot
// 23.11.2016
//---------------------------------------------------------------

//#include "tdrstyle_mod15.C"

void EventsRate_2016Data(){
  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_271036_284044_JSON_Mtt_shrink_Leppt60_Jetpt180/elec/";
  //  TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJAnalysis/Selas2015_36fb_271036_284044_JSON_Mtt_shrink/elec/";
  TString fname_data = path+"uhh2.AnalysisModuleRunner.DATA.DATA.root";
  TFile *input_data = TFile::Open(fname_data);
  TH1 *rate_data = (TH1*)input_data->Get("lumi/luminosity");
  //  TH1D *rate_data = (TH1D*)input_data->Get("chi2/pvN");
  rate_data->SetMarkerStyle(20);
  rate_data->SetMarkerSize(1.5);
  rate_data->GetXaxis()->SetTitle("luminosity, pb^{-1}");
  rate_data->GetYaxis()->SetTitle("Events/250 pb^{-1}");
  rate_data->GetYaxis()->SetRangeUser(500,1500);
  rate_data->SetTitle("");
  rate_data->Draw("");
  TLine *RunB = new TLine (5892,500,5892,1500);
  RunB->SetLineWidth(2);
  RunB->SetLineStyle(2);
  RunB->Draw("same");
  TLine *RunC = new TLine (8538,500,8538,1500);
  RunC->SetLineWidth(2);
  RunC->SetLineStyle(2);
  RunC->Draw("same");
  TLine *RunD = new TLine (12891,500,12891,1500);
  RunD->SetLineWidth(2);
  RunD->SetLineStyle(2);
  RunD->Draw("same");
  TLine *RunE = new TLine (16941,500,16941,1500);
  RunE->SetLineWidth(2);
  RunE->SetLineStyle(2);
  RunE->Draw("same");
  TLine *RunF = new TLine (20101,500,20101,1500);
  RunF->SetLineWidth(2);
  RunF->SetLineStyle(2);
  RunF->Draw("same");
  TLine *RunG = new TLine (27655,500,27655,1500);
  RunG->SetLineWidth(2);
  RunG->SetLineStyle(2);
  RunG->Draw("same");
}
