#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <TLorentzVector.h>
#include <string>

class ZprimeSemiLeptonicSystematicsHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicSystematicsHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();
  bool is_mc, is_Muon;

  uhh2::Event::Handle<float> h_ele_reco;
  uhh2::Event::Handle<float> h_ele_reco_up;
  uhh2::Event::Handle<float> h_ele_reco_down;
  uhh2::Event::Handle<float> h_ele_id;
  uhh2::Event::Handle<float> h_ele_id_up;
  uhh2::Event::Handle<float> h_ele_id_down;
  uhh2::Event::Handle<float> h_mu_reco;
  uhh2::Event::Handle<float> h_mu_reco_up;
  uhh2::Event::Handle<float> h_mu_reco_down;
  uhh2::Event::Handle<float> h_mu_iso;
  uhh2::Event::Handle<float> h_mu_iso_up;
  uhh2::Event::Handle<float> h_mu_iso_down;
  uhh2::Event::Handle<float> h_mu_id;
  uhh2::Event::Handle<float> h_mu_id_up;
  uhh2::Event::Handle<float> h_mu_id_down;
  uhh2::Event::Handle<float> h_mu_trigger;
  uhh2::Event::Handle<float> h_mu_trigger_up;
  uhh2::Event::Handle<float> h_mu_trigger_down;
  uhh2::Event::Handle<float> h_pu;
  uhh2::Event::Handle<float> h_pu_up;
  uhh2::Event::Handle<float> h_pu_down;
  uhh2::Event::Handle<float> h_prefiring;
  uhh2::Event::Handle<float> h_prefiring_up;
  uhh2::Event::Handle<float> h_prefiring_down;
  uhh2::Event::Handle<float> h_toppt;
  uhh2::Event::Handle<float> h_toppt_a_up;
  uhh2::Event::Handle<float> h_toppt_a_down;
  uhh2::Event::Handle<float> h_toppt_b_up;
  uhh2::Event::Handle<float> h_toppt_b_down;
  uhh2::Event::Handle<float> h_murmuf_upup;
  uhh2::Event::Handle<float> h_murmuf_upnone;
  uhh2::Event::Handle<float> h_murmuf_noneup;
  uhh2::Event::Handle<float> h_murmuf_nonedown;
  uhh2::Event::Handle<float> h_murmuf_downnone;
  uhh2::Event::Handle<float> h_murmuf_downdown;
  uhh2::Event::Handle<float> h_isr_up;
  uhh2::Event::Handle<float> h_isr_down;
  uhh2::Event::Handle<float> h_fsr_up;
  uhh2::Event::Handle<float> h_fsr_down;
  uhh2::Event::Handle<float> h_btag;
  uhh2::Event::Handle<float> h_btag_cferr1_up;
  uhh2::Event::Handle<float> h_btag_cferr1_down;
  uhh2::Event::Handle<float> h_btag_cferr2_up;
  uhh2::Event::Handle<float> h_btag_cferr2_down;
  uhh2::Event::Handle<float> h_btag_hf_up;
  uhh2::Event::Handle<float> h_btag_hf_down;
  uhh2::Event::Handle<float> h_btag_hfstats1_up;
  uhh2::Event::Handle<float> h_btag_hfstats1_down;
  uhh2::Event::Handle<float> h_btag_hfstats2_up;
  uhh2::Event::Handle<float> h_btag_hfstats2_down;
  uhh2::Event::Handle<float> h_btag_lf_up;
  uhh2::Event::Handle<float> h_btag_lf_down;
  uhh2::Event::Handle<float> h_btag_lfstats1_up;
  uhh2::Event::Handle<float> h_btag_lfstats1_down;
  uhh2::Event::Handle<float> h_btag_lfstats2_up;
  uhh2::Event::Handle<float> h_btag_lfstats2_down;

  TH1F *M_Zprime;
  TH1F *M_Zprime_mu_reco_up;
  TH1F *M_Zprime_mu_reco_down;
  TH1F *M_Zprime_pu_up;
  TH1F *M_Zprime_pu_down;
  TH1F *M_Zprime_prefiring_up;
  TH1F *M_Zprime_prefiring_down;
  TH1F *M_Zprime_mu_id_up;
  TH1F *M_Zprime_mu_id_down;
  TH1F *M_Zprime_mu_iso_up;
  TH1F *M_Zprime_mu_iso_down;
  TH1F *M_Zprime_mu_trigger_up;
  TH1F *M_Zprime_mu_trigger_down;
  TH1F *M_Zprime_ele_id_up;
  TH1F *M_Zprime_ele_id_down;
  TH1F *M_Zprime_ele_reco_up;
  TH1F *M_Zprime_ele_reco_down;
  TH1F *M_Zprime_toppt_a_up;
  TH1F *M_Zprime_toppt_a_down;
  TH1F *M_Zprime_toppt_b_up;
  TH1F *M_Zprime_toppt_b_down;
  TH1F *M_Zprime_murmuf_upup;
  TH1F *M_Zprime_murmuf_upnone;
  TH1F *M_Zprime_murmuf_noneup;
  TH1F *M_Zprime_murmuf_nonedown;
  TH1F *M_Zprime_murmuf_downnone;
  TH1F *M_Zprime_murmuf_downdown;
  TH1F *M_Zprime_isr_up;
  TH1F *M_Zprime_isr_down;
  TH1F *M_Zprime_fsr_up;
  TH1F *M_Zprime_fsr_down;
  TH1F *M_Zprime_btag_cferr1_up;
  TH1F *M_Zprime_btag_cferr1_down;
  TH1F *M_Zprime_btag_cferr2_up;
  TH1F *M_Zprime_btag_cferr2_down;
  TH1F *M_Zprime_btag_hf_up;
  TH1F *M_Zprime_btag_hf_down;
  TH1F *M_Zprime_btag_hfstats1_up;
  TH1F *M_Zprime_btag_hfstats1_down;
  TH1F *M_Zprime_btag_hfstats2_up;
  TH1F *M_Zprime_btag_hfstats2_down;
  TH1F *M_Zprime_btag_lf_up;
  TH1F *M_Zprime_btag_lf_down;
  TH1F *M_Zprime_btag_lfstats1_up;
  TH1F *M_Zprime_btag_lfstats1_down;
  TH1F *M_Zprime_btag_lfstats2_up;
  TH1F *M_Zprime_btag_lfstats2_down;


  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;
  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;
  virtual ~ZprimeSemiLeptonicSystematicsHists();
};
