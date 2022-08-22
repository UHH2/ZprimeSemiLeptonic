#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <TLorentzVector.h>

class ZprimeSemiLeptonicHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();
  bool is_mc, ishotvr, isdeepAK8;

  TH1F *N_jets, *pt_jet, *pt_jet1, *pt_jet2, *pt_jet3, *eta_jet, *eta_jet1, *eta_jet2, *eta_jet3, *phi_jet, *phi_jet1, *phi_jet2, *phi_jet3, *m_jet, *m_jet1, *m_jet2, *m_jet3, *csv_jet, *csv_jet1, *csv_jet2, *csv_jet3, *N_bJets_loose, *N_bJets_med, *N_bJets_tight;

  TH1F *N_bJetsDeepJet_loose, *N_bJetsDeepJet_med, *N_bJetsDeepJet_tight;

  TH1F *N_mu, *pt_mu, *pt_mu1, *pt_mu2, *eta_mu, *eta_mu1, *eta_mu2, *phi_mu, *phi_mu1, *phi_mu2, *reliso_mu, *reliso_mu1, *reliso_mu2, *reliso_mu_rebin, *reliso_mu1_rebin, *reliso_mu2_rebin;

  TH1F *dR_mu_nearjet, *pt_mu_nearjet;

  TH1F *N_ele, *pt_ele, *pt_ele1, *pt_ele2, *eta_ele, *eta_ele1, *eta_ele2, *phi_ele, *phi_ele1, *phi_ele2, *reliso_ele, *reliso_ele1, *reliso_ele2, *reliso_ele_rebin, *reliso_ele1_rebin, *reliso_ele2_rebin;

  TH1F *pt_ele_lowpt, *pt_ele_midpt, *pt_ele_highpt, *eta_ele_lowpt, *eta_ele_midpt, *eta_ele_highpt, *phi_ele_lowpt, *phi_ele_midpt, *phi_ele_highpt;

  TH1F *dR_ele_nearjet, *pt_ele_nearjet;

  TH1F *M_mumu, *M_ee, *dRmin_mu_jet, *dRmin_mu_jet_scaled, *dRmin_ele_jet, *dRmin_ele_jet_scaled, *ptrel_mu_jet, *ptrel_ele_jet, *dRmin_mu1_jet, *dRmin_mu1_jet_scaled, *dRmin_ele1_jet, *dRmin_ele1_jet_scaled, *ptrel_mu1_jet, *ptrel_ele1_jet;

  TH1F *N_HOTVRjets, *pt_HOTVRjet, *pt_HOTVRjet1, *pt_HOTVRjet2, *pt_HOTVRjet3, *eta_HOTVRjet, *eta_HOTVRjet1, *eta_HOTVRjet2, *eta_HOTVRjet3, *phi_HOTVRjet, *phi_HOTVRjet1, *phi_HOTVRjet2, *phi_HOTVRjet3, *m_HOTVRjet, *m_HOTVRjet1, *m_HOTVRjet2, *m_HOTVRjet3, *N_subjets_HOTVRjet, *N_subjets_HOTVRjet1, *N_subjets_HOTVRjet2, *N_subjets_HOTVRjet3, *N_daughters_HOTVRjet, *N_daughters_HOTVRjet1, *N_daughters_HOTVRjet2, *N_daughters_HOTVRjet3, *dRmin_AK8Puppi_HOTVRjet, *dRmin_AK8Puppi_HOTVRjet1, *dRmin_AK8Puppi_HOTVRjet2, *dRmin_AK8Puppi_HOTVRjet3, *dRmin_mu_HOTVRjet, *dRmin_mu_HOTVRjet1, *dRmin_mu_HOTVRjet2, *dRmin_mu_HOTVRjet3, *tau1_HOTVRjet, *tau1_HOTVRjet1, *tau1_HOTVRjet2, *tau1_HOTVRjet3, *tau2_HOTVRjet, *tau2_HOTVRjet1, *tau2_HOTVRjet2, *tau2_HOTVRjet3, *tau3_HOTVRjet, *tau3_HOTVRjet1, *tau3_HOTVRjet2, *tau3_HOTVRjet3, *tau21_HOTVRjet, *tau21_HOTVRjet1, *tau21_HOTVRjet2, *tau21_HOTVRjet3, *tau32_HOTVRjet, *tau32_HOTVRjet1, *tau32_HOTVRjet2, *tau32_HOTVRjet3;

  TH1F *N_AK8Puppijets, *pt_AK8Puppijet, *pt_AK8Puppijet1, *pt_AK8Puppijet2, *pt_AK8Puppijet3, *eta_AK8Puppijet, *eta_AK8Puppijet1, *eta_AK8Puppijet2, *eta_AK8Puppijet3, *phi_AK8Puppijet, *phi_AK8Puppijet1, *phi_AK8Puppijet2, *phi_AK8Puppijet3, *mSD_AK8Puppijet, *mSD_AK8Puppijet1, *mSD_AK8Puppijet2, *mSD_AK8Puppijet3, *N_subjets_AK8Puppijet, *N_subjets_AK8Puppijet1, *N_subjets_AK8Puppijet2, *N_subjets_AK8Puppijet3, *N_daughters_AK8Puppijet, *N_daughters_AK8Puppijet1, *N_daughters_AK8Puppijet2, *N_daughters_AK8Puppijet3, *dRmin_AK8_AK8Puppijet, *dRmin_AK8_AK8Puppijet1, *dRmin_AK8_AK8Puppijet2, *dRmin_AK8_AK8Puppijet3, *dRmin_mu_AK8Puppijet, *dRmin_mu_AK8Puppijet1, *dRmin_mu_AK8Puppijet2, *dRmin_mu_AK8Puppijet3, *tau1_AK8Puppijet, *tau1_AK8Puppijet1, *tau1_AK8Puppijet2, *tau1_AK8Puppijet3, *tau2_AK8Puppijet, *tau2_AK8Puppijet1, *tau2_AK8Puppijet2, *tau2_AK8Puppijet3, *tau3_AK8Puppijet, *tau3_AK8Puppijet1, *tau3_AK8Puppijet2, *tau3_AK8Puppijet3, *tau21_AK8Puppijet, *tau21_AK8Puppijet1, *tau21_AK8Puppijet2, *tau21_AK8Puppijet3, *tau32_AK8Puppijet, *tau32_AK8Puppijet1, *tau32_AK8Puppijet2, *tau32_AK8Puppijet3;

  TH1F *N_HOTVRTaggedjets, *pt_HOTVRTaggedjet, *pt_HOTVRTaggedjet1, *pt_HOTVRTaggedjet2, *pt_HOTVRTaggedjet3, *eta_HOTVRTaggedjet, *eta_HOTVRTaggedjet1, *eta_HOTVRTaggedjet2, *eta_HOTVRTaggedjet3, *phi_HOTVRTaggedjet, *phi_HOTVRTaggedjet1, *phi_HOTVRTaggedjet2, *phi_HOTVRTaggedjet3, *m_HOTVRTaggedjet, *m_HOTVRTaggedjet1, *m_HOTVRTaggedjet2, *m_HOTVRTaggedjet3, *N_subjets_HOTVRTaggedjet, *N_subjets_HOTVRTaggedjet1, *N_subjets_HOTVRTaggedjet2, *N_subjets_HOTVRTaggedjet3, *N_daughters_HOTVRTaggedjet, *N_daughters_HOTVRTaggedjet1, *N_daughters_HOTVRTaggedjet2, *N_daughters_HOTVRTaggedjet3, *dRmin_AK8_HOTVRTaggedjet, *dRmin_AK8_HOTVRTaggedjet1, *dRmin_AK8_HOTVRTaggedjet2, *dRmin_AK8_HOTVRTaggedjet3, *dRmin_mu_HOTVRTaggedjet, *dRmin_mu_HOTVRTaggedjet1, *dRmin_mu_HOTVRTaggedjet2, *dRmin_mu_HOTVRTaggedjet3, *tau1_HOTVRTaggedjet, *tau1_HOTVRTaggedjet1, *tau1_HOTVRTaggedjet2, *tau1_HOTVRTaggedjet3, *tau2_HOTVRTaggedjet, *tau2_HOTVRTaggedjet1, *tau2_HOTVRTaggedjet2, *tau2_HOTVRTaggedjet3, *tau3_HOTVRTaggedjet, *tau3_HOTVRTaggedjet1, *tau3_HOTVRTaggedjet2, *tau3_HOTVRTaggedjet3, *tau21_HOTVRTaggedjet, *tau21_HOTVRTaggedjet1, *tau21_HOTVRTaggedjet2, *tau21_HOTVRTaggedjet3, *tau32_HOTVRTaggedjet, *tau32_HOTVRTaggedjet1, *tau32_HOTVRTaggedjet2, *tau32_HOTVRTaggedjet3;

  TH1F *N_AK8PuppiTaggedjets, *pt_AK8PuppiTaggedjet, *pt_AK8PuppiTaggedjet1, *pt_AK8PuppiTaggedjet2, *pt_AK8PuppiTaggedjet3, *eta_AK8PuppiTaggedjet, *eta_AK8PuppiTaggedjet1, *eta_AK8PuppiTaggedjet2, *eta_AK8PuppiTaggedjet3, *phi_AK8PuppiTaggedjet, *phi_AK8PuppiTaggedjet1, *phi_AK8PuppiTaggedjet2, *phi_AK8PuppiTaggedjet3, *mSD_AK8PuppiTaggedjet, *mSD_AK8PuppiTaggedjet1, *mSD_AK8PuppiTaggedjet2, *mSD_AK8PuppiTaggedjet3, *N_subjets_AK8PuppiTaggedjet, *N_subjets_AK8PuppiTaggedjet1, *N_subjets_AK8PuppiTaggedjet2, *N_subjets_AK8PuppiTaggedjet3, *N_daughters_AK8PuppiTaggedjet, *N_daughters_AK8PuppiTaggedjet1, *N_daughters_AK8PuppiTaggedjet2, *N_daughters_AK8PuppiTaggedjet3, *dRmin_HOTVR_AK8PuppiTaggedjet, *dRmin_HOTVR_AK8PuppiTaggedjet1, *dRmin_HOTVR_AK8PuppiTaggedjet2, *dRmin_HOTVR_AK8PuppiTaggedjet3, *dRmin_mu_AK8PuppiTaggedjet, *dRmin_mu_AK8PuppiTaggedjet1, *dRmin_mu_AK8PuppiTaggedjet2, *dRmin_mu_AK8PuppiTaggedjet3, *tau1_AK8PuppiTaggedjet, *tau1_AK8PuppiTaggedjet1, *tau1_AK8PuppiTaggedjet2, *tau1_AK8PuppiTaggedjet3, *tau2_AK8PuppiTaggedjet, *tau2_AK8PuppiTaggedjet1, *tau2_AK8PuppiTaggedjet2, *tau2_AK8PuppiTaggedjet3, *tau3_AK8PuppiTaggedjet, *tau3_AK8PuppiTaggedjet1, *tau3_AK8PuppiTaggedjet2, *tau3_AK8PuppiTaggedjet3, *tau21_AK8PuppiTaggedjet, *tau21_AK8PuppiTaggedjet1, *tau21_AK8PuppiTaggedjet2, *tau21_AK8PuppiTaggedjet3, *tau32_AK8PuppiTaggedjet, *tau32_AK8PuppiTaggedjet1, *tau32_AK8PuppiTaggedjet2, *tau32_AK8PuppiTaggedjet3;

  TH1F *NPV, *MET, *MET_rebin, *MET_rebin2, *MET_rebin3, *ST, *ST_rebin, *ST_rebin2, *ST_rebin3, *STjets, *STjets_rebin, *STjets_rebin2, *STjets_rebin3, *STlep, *STlep_rebin, *STlep_rebin2, *STlep_rebin3, *toplep_pt, *toplep_eta, *toplep_phi, *toplep_m, *tophad_pt, *tophad_eta, *tophad_phi, *tophad_m, *ditop_mass, *ditop_absDeltaPhi, *ditop_deltaEta, *ditop_absDeltaEta, *ditop_deltaR, *M_Zprime, *M_Zprime_rebin, *M_Zprime_rebin2, *M_Zprime_rebin3, *M_Zprime_rebin4, *M_Zprime_rebin5, *M_Zprime_rebin6, *M_Zprime_rebin7, *chi2_Zprime, *chi2_Zprime_rebin, *chi2_Zprime_rebin2, *M_tophad, *M_toplep, *M_Zprime_ak4, *M_Zprime_ak4_rebin, *M_Zprime_ak4_rebin2, *M_Zprime_ak4_rebin3, *M_Zprime_ak4_rebin4, *M_Zprime_ak4_rebin5, *M_Zprime_ak4_rebin6, *M_Zprime_ak4_rebin7, *chi2_Zprime_ak4, *chi2_Zprime_ak4_rebin, *chi2_Zprime_ak4_rebin2, *M_tophad_ak4, *M_toplep_ak4, *M_Zprime_ttag, *M_Zprime_ttag_rebin, *M_Zprime_ttag_rebin2, *M_Zprime_ttag_rebin3, *M_Zprime_ttag_rebin4, *M_Zprime_ttag_rebin5, *M_Zprime_ttag_rebin6, *M_Zprime_ttag_rebin7, *chi2_Zprime_ttag, *chi2_Zprime_ttag_rebin, *chi2_Zprime_ttag_rebin2, *M_tophad_ttag, *M_tophad_ttag_M, *M_tophad_ttag_v4, *M_toplep_ttag, *M_tophad_dr_ak4, *M_toplep_dr_ak4, *M_tophad_dr_ttag, *M_toplep_dr_ttag, *dr_discr_Zprime, *M_Zprime_dr, *M_Zprime_dr_rebin, *M_Zprime_dr_rebin2, *M_Zprime_dr_rebin3, *S11, *S12, *S13, *S22, *S23, *S33, *sum_event_weights;


  TH1F *NN_Mu_pt, *NN_Mu_eta, *NN_Mu_phi, *NN_Mu_E, *NN_Ele_pt, *NN_Ele_eta, *NN_Ele_phi, *NN_Ele_E, *NN_MET_pt, *NN_MET_phi, *NN_N_Ak4, *NN_Ak4_j1_pt, *NN_Ak4_j1_eta, *NN_Ak4_j1_phi, *NN_Ak4_j1_E, *NN_Ak4_j1_m, *NN_Ak4_j1_btag, *NN_Ak4_j2_pt, *NN_Ak4_j2_eta, *NN_Ak4_j2_phi, *NN_Ak4_j2_E, *NN_Ak4_j2_m, *NN_Ak4_j2_btag, *NN_Ak4_j3_pt, *NN_Ak4_j3_eta, *NN_Ak4_j3_phi, *NN_Ak4_j3_E, *NN_Ak4_j3_m, *NN_Ak4_j3_btag, *NN_Ak4_j4_pt, *NN_Ak4_j4_eta, *NN_Ak4_j4_phi, *NN_Ak4_j4_E, *NN_Ak4_j4_m, *NN_Ak4_j4_btag, *NN_Ak4_j5_pt, *NN_Ak4_j5_eta, *NN_Ak4_j5_phi, *NN_Ak4_j5_E, *NN_Ak4_j5_m, *NN_Ak4_j5_btag, *NN_Ak4_j6_pt, *NN_Ak4_j6_eta, *NN_Ak4_j6_phi, *NN_Ak4_j6_E, *NN_Ak4_j6_m, *NN_Ak4_j6_btag, *NN_N_HOTVR, *NN_HOTVR_j1_pt, *NN_HOTVR_j1_eta, *NN_HOTVR_j1_phi, *NN_HOTVR_j1_E, *NN_HOTVR_j1_mSD, *NN_HOTVR_j1_tau21, *NN_HOTVR_j1_tau32, *NN_HOTVR_j2_pt, *NN_HOTVR_j2_eta, *NN_HOTVR_j2_phi, *NN_HOTVR_j2_E, *NN_HOTVR_j2_mSD, *NN_HOTVR_j2_tau21, *NN_HOTVR_j2_tau32, *NN_HOTVR_j3_pt, *NN_HOTVR_j3_eta, *NN_HOTVR_j3_phi, *NN_HOTVR_j3_E, *NN_HOTVR_j3_mSD, *NN_HOTVR_j3_tau21, *NN_HOTVR_j3_tau32, *NN_M_tt_weighted, *NN_M_tt_notweighted,*NN_N_Ak8, *NN_Ak8_j1_pt, *NN_Ak8_j1_eta, *NN_Ak8_j1_phi, *NN_Ak8_j1_E, *NN_Ak8_j1_mSD, *NN_Ak8_j1_tau21, *NN_Ak8_j1_tau32, *NN_Ak8_j2_pt, *NN_Ak8_j2_eta, *NN_Ak8_j2_phi, *NN_Ak8_j2_E, *NN_Ak8_j2_mSD, *NN_Ak8_j2_tau21, *NN_Ak8_j2_tau32, *NN_Ak8_j3_pt, *NN_Ak8_j3_eta, *NN_Ak8_j3_phi, *NN_Ak8_j3_E, *NN_Ak8_j3_mSD, *NN_Ak8_j3_tau21, *NN_Ak8_j3_tau32;

  TH2F *dRmin_ptrel_mu, *dRmin_ptrel_mu1, *dRmin_ptrel_ele, *dRmin_ptrel_ele1;

  TH1F *deepjetbscore_jet,*deepjetbscore_jet1,*deepjetbscore_jet2,*deepjetbscore_jet3;

  TH1F *deepjet_topscore_jet,*deepjet_topscore_jet1,*deepjet_topscore_jet2,*deepjet_topscore_jet3;
  TH1F *deepjet_wscore_jet,*deepjet_wscore_jet1,*deepjet_wscore_jet2;
  TH1F *deepjet_zscore_jet,*deepjet_zscore_jet1,*deepjet_zscore_jet2;
  TH1F *deepjet_higgsscore_jet,*deepjet_higgsscore_jet1,*deepjet_higgsscore_jet2;
  TH1F *deepjet_qcdscore_jet,*deepjet_qcdscore_jet1,*deepjet_qcdscore_jet2;

  TH1F *massdecordeepjet_topscore_jet,*massdecordeepjet_topscore_jet1,*massdecordeepjet_topscore_jet2,*massdecordeepjet_topscore_jet3;
  TH1F *massdecordeepjet_wscore_jet,*massdecordeepjet_wscore_jet1,*massdecordeepjet_wscore_jet2;
  TH1F *massdecordeepjet_zscore_jet,*massdecordeepjet_zscore_jet1,*massdecordeepjet_zscore_jet2;
  TH1F *massdecordeepjet_higgsscore_jet,*massdecordeepjet_higgsscore_jet1,*massdecordeepjet_higgsscore_jet2;
  TH1F *massdecordeepjet_qcdscore_jet,*massdecordeepjet_qcdscore_jet1,*massdecordeepjet_qcdscore_jet2;

  TH1F *deepjet_topscore_Taggedjet,*deepjet_topscore_Taggedjet1,*deepjet_topscore_Taggedjet2,*deepjet_topscore_Taggedjet3;
  TH1F *massdecordeepjet_topscore_Taggedjet,*massdecordeepjet_topscore_Taggedjet1,*massdecordeepjet_topscore_Taggedjet2,*massdecordeepjet_topscore_Taggedjet3;

  TH1F *deepjet_TvsQCD_jet,*deepjet_TvsQCD_jet1,*deepjet_TvsQCD_jet2,*deepjet_TvsQCD_jet3;
  TH1F *massdecordeepjet_TvsQCD_jet,*massdecordeepjet_TvsQCD_jet1,*massdecordeepjet_TvsQCD_jet2,*massdecordeepjet_TvsQCD_jet3;
  TH1F *deepjet_TvsQCD_Taggedjet,*deepjet_TvsQCD_Taggedjet1,*deepjet_TvsQCD_Taggedjet2,*deepjet_TvsQCD_Taggedjet3;
  TH1F *massdecordeepjet_TvsQCD_Taggedjet,*massdecordeepjet_TvsQCD_Taggedjet1,*massdecordeepjet_TvsQCD_Taggedjet2,*massdecordeepjet_TvsQCD_Taggedjet3;

  TH1F *hadtop_thetastar, *cos_hadtop_thetastar, *leptop_thetastar, *cos_leptop_thetastar;

  TH2F *N_Jets_vs_HT;

  uhh2::Event::Handle< std::vector<TopJet> > h_AK8TopTags;
  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_correctmatch;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateCorrectMatch;
  uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;
  //uhh2::Event::Handle<float> h_chi2;
  virtual ~ZprimeSemiLeptonicHists();
};
