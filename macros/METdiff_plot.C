//---------------------------------------------------------------
// this macro reads hists for MET pT 
// and create plot to show difference between slMETsCHS and slimmedMETs
//
// 02.08.2016
//---------------------------------------------------------------

void METdiff_plot(){
  TString path1 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJSkimming/Selas2015_13fb_20160801_v02_METcorrTEST_slimmedMETsCHS/";
  TString path2 = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJSkimming/Selas2015_13fb_20160801_v02_METcorrTEST_slimmedMETs/";
  TString file = "uhh2.AnalysisModuleRunner.DATA.SingleEG.root";

  TString fname1 = path1+file;
  TString fname2 = path2+file;
  TFile *input1 = TFile::Open(fname1);
  TH1F *met_pt1 = (TH1F*)input1->Get("twodcut/met__pt");
  TH1F *met_phi1 = (TH1F*)input1->Get("twodcut/met__phi");
  met_pt1->SetMarkerStyle(20);
  met_pt1->SetMarkerColor(1);
  met_phi1->SetMarkerStyle(20);
  met_phi1->SetMarkerColor(1);
  TFile *input2 = TFile::Open(fname2);
  TH1F *met_pt2 = (TH1F*)input2->Get("twodcut/met__pt");
  TH1F *met_phi2 = (TH1F*)input2->Get("twodcut/met__phi");
  met_pt2->SetMarkerStyle(24);
  met_pt2->SetMarkerColor(2);
  met_phi2->SetMarkerStyle(24);
  met_phi2->SetMarkerColor(2);
  TLegend *leg = new TLegend(0.57,0.68,0.85,0.88);
  leg->SetFillColor(0);
  leg->SetTextFont(42);
  leg->SetTextSize(0.05);
  leg->AddEntry(met_pt1,"slMETsCHS","lep");
  leg->AddEntry(met_pt2,"slimmedMETs","lep");

  Double_t w = 600;
  Double_t h = 800;
  TCanvas *c1 = new TCanvas("c1", "MET", w, h);
  c1->Divide(1,2);
  c1->cd(1);
  met_pt1->GetXaxis()->SetTitle("MET [GeV]");
  met_pt1->Draw();
  met_pt2->Draw("same");
  leg->Draw();
  c1->cd(2);
  met_phi1->GetXaxis()->SetTitle("MET #phi [rad]");
  met_phi1->Draw();
  met_phi2->Draw("same");
  c1->SaveAs(path1+"METdiff_plot.root");
  //  c1.SaveAs(path1+"METdiff_plot.pdf");
}
