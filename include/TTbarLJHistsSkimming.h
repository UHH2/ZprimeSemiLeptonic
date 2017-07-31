#pragma once

//#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>
#include <UHH2/core/include/Hists.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/common/include/TopJetIds.h>

#include <string>

//class TTbarLJHists : public HistsBASE {
class TTbarLJHistsSkimming : public uhh2::Hists {

 public:
  explicit TTbarLJHistsSkimming(uhh2::Context&, const std::string&);
  explicit TTbarLJHistsSkimming(uhh2::Context&, const std::string&, const TopJetId&, const float);

  virtual void fill(const uhh2::Event&) override;

 protected:
  TopJetId tjet_ID_;
  float    tjet_minDR_jet_;
  TH1F *wgt, *pvN, *muoN, *eleN, *jetN, *topjetN, *toptagN;
  TH1F *muo1__charge,*muo1__pt,*muo1__eta,*muo1__phi;
  TH1F *muo1__minDR_jet,*muo1__pTrel_jet;
  TH1F *muo2__charge,*muo2__pt,*muo2__eta,*muo2__phi;
  TH1F *muo2__minDR_jet,*muo2__pTrel_jet;
  TH1F *ele1__class,*ele1__charge,*ele1__pt,*ele1__ptError;
  TH1F *ele1__eta,*ele1__etaError,*ele1__phi,*ele1__phiError;
  TH1F *ele1__minDR_jet,*ele1__pTrel_jet;
  TH1F *ele2__class,*ele2__charge,*ele2__pt,*ele2__ptError;
  TH1F *ele2__eta,*ele2__etaError,*ele2__phi,*ele2__phiError;
  TH1F *ele2__minDR_jet,*ele2__pTrel_jet;
  TH1F *jetN__CSVL,*jetN__CSVM,*jetN__CSVT;
  TH1F *jet1__pt,*jet1__eta,*jet1__phi,*jet1__M,*jet1__CSV;
  TH1F *jet2__pt,*jet2__eta,*jet2__phi,*jet2__M,*jet2__CSV;
  TH1F *jet3__pt,*jet3__eta,*jet3__phi,*jet3__M,*jet3__CSV;
  TH1F *topjet1__pt,*topjet1__eta,*topjet1__phi,*topjet1__CSV,*topjet1__Msdp,*topjet1__tau32;
  TH1F *topjet2__pt,*topjet2__eta,*topjet2__phi,*topjet2__CSV,*topjet2__Msdp,*topjet2__tau32;
  TH1F *toptag1__pt,*toptag1__eta,*toptag1__phi,*toptag1__M;
  TH1F *toptag1__Mgro,*toptag1__Mpru,*toptag1__Msdp;
  TH1F *toptag1__tau32,*toptag1__CSV,*toptag1__subjN;
  TH1F *toptag2__pt,*toptag2__eta,*toptag2__phi,*toptag2__M;
  TH1F *toptag2__Mgro,*toptag2__Mpru,*toptag2__Msdp;
  TH1F *toptag2__tau32,*toptag2__CSV,*toptag2__subjN;
  TH1F *met__pt,*met__phi,*wlep__ht,*wlep__pt,*wlep__Mt;
  //TH1F* TMVA_response;
  //TH1F *lep_eta_err;
  //TH1F *lep_pt;
  //*lep_eta,
  //TH1F *lep_pt_err;
  //TH1F *lep_full5x5_e5x5;
  //TH1F *lep_dB; 
  //TH1F *lep_dPhiIn,*lep_dEtaInSeed,*lep_hcalOverEcal,*lep_dr03TkSumPt,*lep_effArea, *ljet_eta,*ljet_CSV,*fjet2_eta,*fjet2_pt,*jet2_CSV,*met_pT;
  // TH1F* WJets_TMVA_response;
  // TH1F *jet1_m, *jet2_pt, *jet1_csv, *jet2_csv, *DRpt, *ht_met_lep_norm, *s33, *lep1__minDR_norm, *lep1__pTrel_jet_norm, *njets;
  // uhh2::Event::Handle<float> wjets_tmva_response;
  //TH1F *lep_eta_err,*lep_pt, *lep_eta, *lep_pt_err, *lep_full5x5_e5x5, *lep_dB, *lep_dPhiIn, *lep_dEtaInSeed, *lep_hcalOverEcal, *lep_dr03TkSumPt, *lep_effArea, *ljet_eta, *ljet_CSV, *fjet2_eta, *fjet2_pt, *jet2_CSV, *met_pT; 
  //  virtual void init() override;
  void init();

/* private:
  uhh2::Event::Handle<float> tt_tmva_response;
  uhh2::Event::Handle<float> wjets_tmva_response;
  uhh2::Event::Handle<float> h_DRpt;
  uhh2::Event::Handle<float> h_jet1_m;
  uhh2::Event::Handle<float> h_jet1_csv;
  uhh2::Event::Handle<float> h_jet2_pt;
  uhh2::Event::Handle<float> h_jet2_csv;
  uhh2::Event::Handle<float> h_njets;
  uhh2::Event::Handle<float> h_ht_met_lep_norm;
  uhh2::Event::Handle<float> h_s33;
  uhh2::Event::Handle<float> h_lep1__minDR_norm;
  uhh2::Event::Handle<float> h_lep1__pTrel_jet_norm;
  //uhh2::Event::Handle<float> h_lep_eta_err;
  //uhh2::Event::Handle<float> h_lep_pt;
  //uhh2::Event::Handle<float> h_lep_eta;
  //uhh2::Event::Handle<float> h_lep_pt_err;
  //uhh2::Event::Handle<float> h_lep_full5x5_e5x5;
  //uhh2::Event::Handle<float> h_lep_dB;
  //uhh2::Event::Handle<float> h_lep_dPhiIn;
  //uhh2::Event::Handle<float> h_lep_dEtaInSeed;
  //uhh2::Event::Handle<float> h_lep_hcalOverEcal;
  //uhh2::Event::Handle<float> h_lep_dr03TkSumPt;
  //uhh2::Event::Handle<float> h_lep_effArea;
  //uhh2::Event::Handle<float> h_ljet_eta;
  //uhh2::Event::Handle<float> h_ljet_CSV;
  //uhh2::Event::Handle<float> h_fjet2_eta;
  //uhh2::Event::Handle<float> h_fjet2_pt;
  //uhh2::Event::Handle<float> h_jet2_CSV;
  //uhh2::Event::Handle<float> h_met_pt;
  */
};
