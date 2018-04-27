#pragma once

//#include <UHH2/ZprimeSemiLeptonic/include/HistsBASE.h>
#include <UHH2/core/include/Hists.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/common/include/TopJetIds.h>

#include <string>

//class TTbarLJHists : public HistsBASE {
class TTbarLJHists : public uhh2::Hists {

 public:
  explicit TTbarLJHists(uhh2::Context&, const std::string&);
  explicit TTbarLJHists(uhh2::Context&, const std::string&, const TopJetId&, const float);

  virtual void fill(const uhh2::Event&) override;

 protected:
  TopJetId tjet_ID_;
  float    tjet_minDR_jet_;
  TH1F *wgt, *pvN, *rho, *muoN, *eleN, *jetN, *topjetN, *toptagN, *toppuppijetN;
  TH1F *muo1__charge,*muo1__pt,*muo1__eta,*muo1__phi;
  TH1F *muo1__minDR_jet,*muo1__pTrel_jet;
  TH1F *muo2__charge,*muo2__pt,*muo2__eta,*muo2__phi;
  TH1F *muo2__minDR_jet,*muo2__pTrel_jet;
  TH1F *muo2__DPhi_met,*muo1__DPhi_met;
  TH2F *muo1__triangle;
  TH1F *ele1__class,*ele1__charge,*ele1__pt,*ele1__ptError;
  TH1F *ele1__eta,*ele1__etaError,*ele1__phi,*ele1__phiError;
  TH1F *ele2__DPhi_met,*ele1__DPhi_met;
  TH1F *ele1__minDR_jet,*ele1__pTrel_jet;
  TH1F *ele1__eta_SC, *ele1__Deta_trk_SC;
  TH2F *ele1__triangle;

  TH1F *ele2__class,*ele2__charge,*ele2__pt,*ele2__ptError;
  TH1F *ele2__eta,*ele2__etaError,*ele2__phi,*ele2__phiError;
  TH1F *ele2__minDR_jet,*ele2__pTrel_jet;
  TH1F *jetN__CSVL,*jetN__CSVM,*jetN__CSVT;
  TH1F *jet1__pt,*jet1__eta,*jet1__phi,*jet1__M,*jet1__CSV,*jet1__MVAbtag,*jet2__MVAbtag,*jet3__MVAbtag;
  TH1F *jet2__pt,*jet2__eta,*jet2__phi,*jet2__M,*jet2__CSV;
  TH1F *jet3__pt,*jet3__eta,*jet3__phi,*jet3__M,*jet3__CSV;
  TH1F *jet1__EMfrac,*jet1__HADfrac,*jet1__PHfrac;
  TH1F *jet2__EMfrac,*jet2__HADfrac,*jet2__PHfrac;
  TH1F *jet3__EMfrac,*jet3__HADfrac,*jet3__PHfrac;
  TH1F *jet1__DPhi_met,*jet2__DPhi_met;
  TH2F *jet1__triangle, *jet2__triangle;
  TH1F *under_jets__pt;
  TH1F *jet1__NDaughters,*jet2__NDaughters,*jet3__NDaughters;
  TH1F *topjet1__pt,*topjet1__eta,*topjet1__phi,*topjet1__CSV,*topjet1__Msdp,*topjet1__tau32,*topjet1__NumSubjets,*topjet1__dR;
  TH1F *topjet2__pt,*topjet2__eta,*topjet2__phi,*topjet2__CSV,*topjet2__Msdp,*topjet2__tau32,*topjet2__NumSubjets,*topjet2__dR;
  TH1F *toppuppijet1__pt,*toppuppijet1__eta,*toppuppijet1__phi,*toppuppijet1__CSV,*toppuppijet1__Msdp,*toppuppijet1__tau32,*toppuppijet1__NumSubjets;
  TH1F *toppuppijet2__pt,*toppuppijet2__eta,*toppuppijet2__phi,*toppuppijet2__CSV,*toppuppijet2__Msdp,*toppuppijet2__tau32,*toppuppijet2__NumSubjets;
  TH1F *toppuppijet__pt_matched,*toppuppijet__eta_matched,*toppuppijet__phi_matched,*toppuppijet__CSV_matched,*toppuppijet__Msdp_matched,*toppuppijet__tau32_matched,*toppuppijet__NumSubjets_matched,*toppuppijet__jetID_matched,*toppuppijetN_matched,*toppuppijet__Msdp_matched_Nminus1,*toppuppijet__tau32_matched_Nminus1;
  TH1F *toppuppijet__pt_matched_ttag,*toppuppijet__eta_matched_ttag,*toppuppijet__phi_matched_ttag,*toppuppijet__CSV_matched_ttag,*toppuppijet__Msdp_matched_ttag,*toppuppijet__tau32_matched_ttag,*toppuppijet__NumSubjets_matched_ttag,*toppuppijet__jetID_matched_ttag;
  TH1F *toptag1__pt,*toptag1__eta,*toptag1__phi,*toptag1__M;
  TH1F *toptag1__Mgro,*toptag1__Mpru,*toptag1__Msdp;
  TH1F *toptag1__tau32,*toptag1__CSV,*toptag1__subjN;
  TH1F *toptag2__pt,*toptag2__eta,*toptag2__phi,*toptag2__M;
  TH1F *toptag2__Mgro,*toptag2__Mpru,*toptag2__Msdp;
  TH1F *toptag2__tau32,*toptag2__CSV,*toptag2__subjN;
  TH1F *topjet1__dRlep, *topjet2__dRlep;
  TH1F *met__pt,*met__phi,*wlep__ht,*wlep__pt,*wlep__Mt,*wlep__pt__jet1__pt;
  TH1F* TMVA_response;
  TH1F* WJets_TMVA_response;
  TH1F *jet1_m, *jet2_m, *jet1_csv, *jet2_csv, *DRpt, *ht_met_lep_norm, *s33, *lep1__minDR_norm, *lep1__pTrel_jet_norm;
  //  virtual void init() override;
  void init();

 private:
  uhh2::Event::Handle<float> tt_tmva_response;
  uhh2::Event::Handle<float> wjets_tmva_response;
  uhh2::Event::Handle<float> h_DRpt;
  uhh2::Event::Handle<float> h_jet1_m;
  uhh2::Event::Handle<float> h_jet1_csv;
  uhh2::Event::Handle<float> h_jet2_m;

  uhh2::Event::Handle<float> h_jet2_csv;
  uhh2::Event::Handle<float> h_njets;
  uhh2::Event::Handle<float> h_ht_met_lep_norm;
  uhh2::Event::Handle<float> h_s33;
  uhh2::Event::Handle<float> h_lep1__minDR_norm;
  uhh2::Event::Handle<float> h_lep1__pTrel_jet_norm;

};
