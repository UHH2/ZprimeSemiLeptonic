{

  // TFile* infile = new TFile("/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/2017_Initial/NOMINAL/uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root", "READ");
  TFile* infile = new TFile("/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/2017_Initial/NOMINAL/uhh2.AnalysisModuleRunner.MC.TTbar_SemiLep.root", "READ");

  TH1F* h_had_ak4  = (TH1F*)infile->Get("STlepPlusMet_General/M_tophad_dr_ak4");
  TH1F* h_lep_ak4  = (TH1F*)infile->Get("STlepPlusMet_General/M_toplep_dr_ak4");
  TH1F* h_had_ttag = (TH1F*)infile->Get("STlepPlusMet_General/M_tophad_dr_ttag");
  TH1F* h_lep_ttag = (TH1F*)infile->Get("STlepPlusMet_General/M_toplep_dr_ttag");

  vector<TH1F*> hists = {h_had_ak4, h_lep_ak4, h_had_ttag, h_lep_ttag};
  vector<TString> names = {"Mtop_hadronic_AK4", "Mtop_leptonic_AK4", "Mtop_hadronic_TTag", "Mtop_leptonic_TTag"};

  for(unsigned int i=0; i<hists.size(); i++){
    TCanvas* c = new TCanvas("c", "c", 600, 600);
    hists.at(i)->GetXaxis()->SetTitle(hists.at(i)->GetTitle());
    hists.at(i)->SetTitle("");

    hists.at(i)->Fit("gaus", "", "", 130, 210);
    gStyle->SetOptFit(1);

    c->SaveAs("Plots/" + names.at(i) + ".eps");
    c->SaveAs("Plots/" + names.at(i) + ".pdf");
  }










}
