//---------------------------------------------------------------
// this macro reads hists for trigger efficiency plots
// and creates file with 2D efficincy histogramm
// 11.12.2016
//---------------------------------------------------------------

void TriggerEff_hists(){
  gStyle->SetOptStat(0);
  gStyle->SetTitleSize(0.06,"x");  
  gStyle->SetTitleSize(0.06,"y");
  
TString path = "/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v2/ttbarLJTriggerStudyLite_2Dhists/elec/";
// TString prefix = "BCDEFGH";
// TString prefix = "BCD";
// TString prefix = "EF";
  TString prefix = "GH";
  TString file_HLTsel = path+"uhh2.AnalysisModuleRunner.DATA.SingleMUON_Run"+prefix+"_ID_HLT.root";
  TFile *input_HLTsel = TFile::Open(file_HLTsel); 


  TH1F *h_ele_pt = (TH1F*)input_HLTsel->Get("trigger/ele1__pt"); 
  //  h_ele_pt->Print();    
  TH1F *h_ele_pt_norm = (TH1F*)input_HLTsel->Get("jet1/ele1__pt"); //jet1 selection is the last one before trigger selection     
  h_ele_pt->Divide(h_ele_pt_norm);
  //  h_ele_pt_norm->Print();    

  TH1F *h_ele_eta = (TH1F*)input_HLTsel->Get("trigger/ele1__eta");     
  TH1F *h_ele_eta_norm = (TH1F*)input_HLTsel->Get("jet1/ele1__eta");     
  h_ele_eta->Divide(h_ele_eta_norm);

  TH2F *h_ele_eta_pt = (TH2F*)input_HLTsel->Get("trigger/ele1__eta__pt");     
  TH2F *h_ele_eta_pt_norm = (TH2F*)input_HLTsel->Get("jet1/ele1__eta__pt");     
  h_ele_eta_pt->Divide(h_ele_eta_pt_norm);

  TH2F *h_jet_jet12_pt = (TH2F*)input_HLTsel->Get("trigger/jet__jet1pt__jet2pt");     
  TH2F *h_jet_jet12_pt_norm = (TH2F*)input_HLTsel->Get("jet1/jet__jet1pt__jet2pt");     
  h_jet_jet12_pt->Divide(h_jet_jet12_pt_norm);

  TH2F *h_jet_jet12_eta = (TH2F*)input_HLTsel->Get("trigger/jet__jet1eta__jet2eta");     
  TH2F *h_jet_jet12_eta_norm = (TH2F*)input_HLTsel->Get("jet1/jet__jet1eta__jet2eta");     
  h_jet_jet12_eta->Divide(h_jet_jet12_eta_norm);

  TH2F *h_jet_ele1_jet1_pt = (TH2F*)input_HLTsel->Get("trigger/jet__ele1pt__jet1pt");     
  TH2F *h_jet_ele1_jet1_pt_norm = (TH2F*)input_HLTsel->Get("jet1/jet__ele1pt__jet1pt");     
  h_jet_ele1_jet1_pt->Divide(h_jet_ele1_jet1_pt_norm);

  Double_t w = 600;
  Double_t h = 800;
  TCanvas * c1 = new TCanvas("Trigger_Eff", "Trigger_Eff", w, h);
  c1->Divide(1,2);
  c1->cd(1);
  h_ele_pt->GetYaxis()->SetTitle("efficiency");
  h_ele_pt->GetXaxis()->SetTitle("ele pt, GeV");
  h_ele_pt->Draw();
  c1->cd(2);
  h_ele_eta->GetYaxis()->SetTitle("efficiency");
  h_ele_eta->GetXaxis()->SetTitle("ele #eta");
  h_ele_eta->Draw();
  c1->SaveAs(path+"TriggerEff_1D_Run2016.pdf");
  TCanvas * c2 = new TCanvas("Trigger_Eff2D", "Trigger_Eff2D", h, w);
  h_ele_eta_pt->GetYaxis()->SetTitle("ele pt, GeV");
  h_ele_eta_pt->GetXaxis()->SetTitle("ele #eta");
  h_ele_eta_pt->SetTitle("");
  h_ele_eta_pt->GetZaxis()->SetRangeUser(0.0,1.0);
  h_ele_eta_pt->Draw("colz");
  c2->SaveAs(path+"TriggerEff_2D_Run2016"+prefix+".pdf");

  TCanvas * c3 = new TCanvas("Trigger_Eff2Djetspt", "Trigger_Eff2Djetspt", h, w);
  h_jet_jet12_pt->GetXaxis()->SetTitle("jet1 pt, GeV");
  h_jet_jet12_pt->GetYaxis()->SetTitle("jet2 pt, GeV");
  h_jet_jet12_pt->SetTitle("");
  h_jet_jet12_pt->GetZaxis()->SetRangeUser(0.0,1.0);
  h_jet_jet12_pt->Draw("colz");
  c3->SaveAs(path+"TriggerEff_2Djetspt_Run2016"+prefix+".pdf");
  TCanvas * c4 = new TCanvas("Trigger_Eff2Djetseta", "Trigger_Eff2Djetseta", h, w);
  h_jet_jet12_eta->GetXaxis()->SetTitle("jet1 #eta");
  h_jet_jet12_eta->GetYaxis()->SetTitle("jet2 #eta");
  h_jet_jet12_eta->SetTitle("");
  h_jet_jet12_eta->GetZaxis()->SetRangeUser(0.0,1.0);
  h_jet_jet12_eta->Draw("colz");
  c4->SaveAs(path+"TriggerEff_2Djetseta_Run2016"+prefix+".pdf");
  TCanvas * c5 = new TCanvas("Trigger_Eff2Delejetpt", "Trigger_Eff2Delejetpt", h, w);
  h_jet_ele1_jet1_pt->GetXaxis()->SetTitle("ele1 pt, GeV");   
  h_jet_ele1_jet1_pt->GetYaxis()->SetTitle("jet1 pt, GeV");   
  h_jet_ele1_jet1_pt->SetTitle("");   
  h_jet_ele1_jet1_pt->GetZaxis()->SetRangeUser(0.0,1.0);
  h_jet_ele1_jet1_pt->Draw("colz");   
  c5->SaveAs(path+"TriggerEff_2Delejetpt_Run2016"+prefix+".pdf");

  //  h_ele_pt_norm->Draw();
  TFile fout(path+"TriggerEff_Run2016"+prefix+".root","RECREATE");
  h_ele_eta_pt->Write();
  fout.Write();
  fout.Close();
}
