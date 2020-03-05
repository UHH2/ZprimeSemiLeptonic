#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>


class ZprimeSemiLeptonicHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();
  bool is_mc;

TH1F *N_jets, *pt_jet, *pt_jet1, *pt_jet2, *pt_jet3, *eta_jet, *eta_jet1, *eta_jet2, *eta_jet3, *phi_jet, *phi_jet1, *phi_jet2, *phi_jet3, *m_jet, *m_jet1, *m_jet2, *m_jet3, *csv_jet, *csv_jet1, *csv_jet2, *csv_jet3, *N_bJets_loose, *N_bJets_med, *N_bJets_tight;

TH1F *N_mu, *pt_mu, *pt_mu1, *pt_mu2, *eta_mu, *eta_mu1, *eta_mu2, *phi_mu, *phi_mu1, *phi_mu2, *reliso_mu, *reliso_mu1, *reliso_mu2, *reliso_mu_rebin, *reliso_mu1_rebin, *reliso_mu2_rebin;

TH1F *N_ele, *pt_ele, *pt_ele1, *pt_ele2, *eta_ele, *eta_ele1, *eta_ele2, *phi_ele, *phi_ele1, *phi_ele2, *reliso_ele, *reliso_ele1, *reliso_ele2, *reliso_ele_rebin, *reliso_ele1_rebin, *reliso_ele2_rebin;

TH1F *M_mumu, *M_ee, *dRmin_mu_jet, *dRmin_mu_jet_scaled, *dRmin_ele_jet, *dRmin_ele_jet_scaled, *ptrel_mu_jet, *ptrel_ele_jet, *dRmin_mu1_jet, *dRmin_mu1_jet_scaled, *dRmin_ele1_jet, *dRmin_ele1_jet_scaled, *ptrel_mu1_jet, *ptrel_ele1_jet;

TH1F *N_AK8CHSjets, *pt_AK8CHSjet, *pt_AK8CHSjet1, *pt_AK8CHSjet2, *pt_AK8CHSjet3, *eta_AK8CHSjet, *eta_AK8CHSjet1, *eta_AK8CHSjet2, *eta_AK8CHSjet3, *phi_AK8CHSjet, *phi_AK8CHSjet1, *phi_AK8CHSjet2, *phi_AK8CHSjet3, *mSD_AK8CHSjet, *mSD_AK8CHSjet1, *mSD_AK8CHSjet2, *mSD_AK8CHSjet3, *N_subjets_AK8CHSjet, *N_subjets_AK8CHSjet1, *N_subjets_AK8CHSjet2, *N_subjets_AK8CHSjet3, *N_daughters_AK8CHSjet, *N_daughters_AK8CHSjet1, *N_daughters_AK8CHSjet2, *N_daughters_AK8CHSjet3, *dRmin_AK8Puppi_AK8CHSjet, *dRmin_AK8Puppi_AK8CHSjet1, *dRmin_AK8Puppi_AK8CHSjet2, *dRmin_AK8Puppi_AK8CHSjet3, *dRmin_mu_AK8CHSjet, *dRmin_mu_AK8CHSjet1, *dRmin_mu_AK8CHSjet2, *dRmin_mu_AK8CHSjet3, *tau1_AK8CHSjet, *tau1_AK8CHSjet1, *tau1_AK8CHSjet2, *tau1_AK8CHSjet3, *tau2_AK8CHSjet, *tau2_AK8CHSjet1, *tau2_AK8CHSjet2, *tau2_AK8CHSjet3, *tau3_AK8CHSjet, *tau3_AK8CHSjet1, *tau3_AK8CHSjet2, *tau3_AK8CHSjet3, *tau21_AK8CHSjet, *tau21_AK8CHSjet1, *tau21_AK8CHSjet2, *tau21_AK8CHSjet3, *tau32_AK8CHSjet, *tau32_AK8CHSjet1, *tau32_AK8CHSjet2, *tau32_AK8CHSjet3;

TH1F *N_AK8Puppijets, *pt_AK8Puppijet, *pt_AK8Puppijet1, *pt_AK8Puppijet2, *pt_AK8Puppijet3, *eta_AK8Puppijet, *eta_AK8Puppijet1, *eta_AK8Puppijet2, *eta_AK8Puppijet3, *phi_AK8Puppijet, *phi_AK8Puppijet1, *phi_AK8Puppijet2, *phi_AK8Puppijet3, *mSD_AK8Puppijet, *mSD_AK8Puppijet1, *mSD_AK8Puppijet2, *mSD_AK8Puppijet3, *N_subjets_AK8Puppijet, *N_subjets_AK8Puppijet1, *N_subjets_AK8Puppijet2, *N_subjets_AK8Puppijet3, *N_daughters_AK8Puppijet, *N_daughters_AK8Puppijet1, *N_daughters_AK8Puppijet2, *N_daughters_AK8Puppijet3, *dRmin_AK8CHS_AK8Puppijet, *dRmin_AK8CHS_AK8Puppijet1, *dRmin_AK8CHS_AK8Puppijet2, *dRmin_AK8CHS_AK8Puppijet3, *dRmin_mu_AK8Puppijet, *dRmin_mu_AK8Puppijet1, *dRmin_mu_AK8Puppijet2, *dRmin_mu_AK8Puppijet3, *tau1_AK8Puppijet, *tau1_AK8Puppijet1, *tau1_AK8Puppijet2, *tau1_AK8Puppijet3, *tau2_AK8Puppijet, *tau2_AK8Puppijet1, *tau2_AK8Puppijet2, *tau2_AK8Puppijet3, *tau3_AK8Puppijet, *tau3_AK8Puppijet1, *tau3_AK8Puppijet2, *tau3_AK8Puppijet3, *tau21_AK8Puppijet, *tau21_AK8Puppijet1, *tau21_AK8Puppijet2, *tau21_AK8Puppijet3, *tau32_AK8Puppijet, *tau32_AK8Puppijet1, *tau32_AK8Puppijet2, *tau32_AK8Puppijet3;

TH1F *N_AK8PuppiTaggedjets, *pt_AK8PuppiTaggedjet, *pt_AK8PuppiTaggedjet1, *pt_AK8PuppiTaggedjet2, *pt_AK8PuppiTaggedjet3, *eta_AK8PuppiTaggedjet, *eta_AK8PuppiTaggedjet1, *eta_AK8PuppiTaggedjet2, *eta_AK8PuppiTaggedjet3, *phi_AK8PuppiTaggedjet, *phi_AK8PuppiTaggedjet1, *phi_AK8PuppiTaggedjet2, *phi_AK8PuppiTaggedjet3, *mSD_AK8PuppiTaggedjet, *mSD_AK8PuppiTaggedjet1, *mSD_AK8PuppiTaggedjet2, *mSD_AK8PuppiTaggedjet3, *N_subjets_AK8PuppiTaggedjet, *N_subjets_AK8PuppiTaggedjet1, *N_subjets_AK8PuppiTaggedjet2, *N_subjets_AK8PuppiTaggedjet3, *N_daughters_AK8PuppiTaggedjet, *N_daughters_AK8PuppiTaggedjet1, *N_daughters_AK8PuppiTaggedjet2, *N_daughters_AK8PuppiTaggedjet3, *dRmin_AK8CHS_AK8PuppiTaggedjet, *dRmin_AK8CHS_AK8PuppiTaggedjet1, *dRmin_AK8CHS_AK8PuppiTaggedjet2, *dRmin_AK8CHS_AK8PuppiTaggedjet3, *dRmin_mu_AK8PuppiTaggedjet, *dRmin_mu_AK8PuppiTaggedjet1, *dRmin_mu_AK8PuppiTaggedjet2, *dRmin_mu_AK8PuppiTaggedjet3, *tau1_AK8PuppiTaggedjet, *tau1_AK8PuppiTaggedjet1, *tau1_AK8PuppiTaggedjet2, *tau1_AK8PuppiTaggedjet3, *tau2_AK8PuppiTaggedjet, *tau2_AK8PuppiTaggedjet1, *tau2_AK8PuppiTaggedjet2, *tau2_AK8PuppiTaggedjet3, *tau3_AK8PuppiTaggedjet, *tau3_AK8PuppiTaggedjet1, *tau3_AK8PuppiTaggedjet2, *tau3_AK8PuppiTaggedjet3, *tau21_AK8PuppiTaggedjet, *tau21_AK8PuppiTaggedjet1, *tau21_AK8PuppiTaggedjet2, *tau21_AK8PuppiTaggedjet3, *tau32_AK8PuppiTaggedjet, *tau32_AK8PuppiTaggedjet1, *tau32_AK8PuppiTaggedjet2, *tau32_AK8PuppiTaggedjet3;

TH1F *NPV, *MET, *MET_rebin, *MET_rebin2, *MET_rebin3, *ST, *ST_rebin, *ST_rebin2, *ST_rebin3, *STjets, *STjets_rebin, *STjets_rebin2, *STjets_rebin3, *STlep, *STlep_rebin, *STlep_rebin2, *STlep_rebin3, *M_Zprime,*out0, *out1, *out2,*M_out, *Lep_pt, *Lep_eta, *Lep_phi, *Nu_pt, *Nu_eta, *Nu_phi, *JetLep_pt, *JetLep_eta, *JetLep_phi, *JetHadAK8_pt, *JetHadAK8_eta, *JetHadAK8_phi, *JetHadAK4_1j_pt, *JetHadAK4_1j_eta, *JetHadAK4_1j_phi, *N_AK4_HadJets, *N_AK8_Jets, *N_AK4_LepJets, *JetHadAK4_2j_pt, *JetHadAK4_2j_eta, *JetHadAK4_2j_phi, *TopLep_pt,*TopLep_m, *TopLep_eta, *TopLep_phi,*TopHad_pt, *TopHad_m,*TopHad_eta, *TopHad_phi, *TopHadOverLep_pt, *DeltaR_j1j2_had, *DeltaR_j1lep_j1had, *DeltaR_j1_lep, *DeltaR_j1_nu, *DeltaR_tlep_thad, *M_Zprime_rebin, *M_Zprime_rebin2, *M_Zprime_rebin3, *M_Zprime_rebin4, *M_Zprime_rebin5, *chi2_Zprime, *chi2_Zprime_rebin, *chi2_Zprime_rebin2, *M_tophad, *M_toplep, *M_Zprime_ak4, *M_Zprime_ak4_rebin, *M_Zprime_ak4_rebin2, *M_Zprime_ak4_rebin3, *M_Zprime_ak4_rebin4, *M_Zprime_ak4_rebin5, *chi2_Zprime_ak4, *chi2_Zprime_ak4_rebin, *chi2_Zprime_ak4_rebin2, *M_tophad_ak4, *M_toplep_ak4, *M_Zprime_ttag, *M_Zprime_ttag_rebin, *M_Zprime_ttag_rebin2, *M_Zprime_ttag_rebin3, *M_Zprime_ttag_rebin4, *M_Zprime_ttag_rebin5, *chi2_Zprime_ttag, *chi2_Zprime_ttag_rebin, *chi2_Zprime_ttag_rebin2, *M_tophad_ttag, *M_toplep_ttag, *M_tophad_dr_ak4, *M_toplep_dr_ak4, *M_tophad_dr_ttag, *M_toplep_dr_ttag, *dr_discr_Zprime, *M_Zprime_dr, *M_Zprime_dr_rebin, *M_Zprime_dr_rebin2, *M_Zprime_dr_rebin3, *S11, *S12, *S13, *S22, *S23, *S33, *sum_event_weights;

TH2F *dRmin_ptrel_mu, *dRmin_ptrel_mu1, *dRmin_ptrel_ele, *dRmin_ptrel_ele1;

 TH1F *deepjetbscore_jet,*deepjetbscore_jet1,*deepjetbscore_jet2,*deepjetbscore_jet3;

 TH1F *deepjet_topscore_jet,*deepjet_topscore_jet1,*deepjet_topscore_jet2;
 TH1F *deepjet_wscore_jet,*deepjet_wscore_jet1,*deepjet_wscore_jet2;
 TH1F *deepjet_zscore_jet,*deepjet_zscore_jet1,*deepjet_zscore_jet2;
 TH1F *deepjet_higgsscore_jet,*deepjet_higgsscore_jet1,*deepjet_higgsscore_jet2;
 TH1F *deepjet_qcdscore_jet,*deepjet_qcdscore_jet1,*deepjet_qcdscore_jet2;

 TH1F *massdecordeepjet_topscore_jet,*massdecordeepjet_topscore_jet1,*massdecordeepjet_topscore_jet2;
 TH1F *massdecordeepjet_wscore_jet,*massdecordeepjet_wscore_jet1,*massdecordeepjet_wscore_jet2;
 TH1F *massdecordeepjet_zscore_jet,*massdecordeepjet_zscore_jet1,*massdecordeepjet_zscore_jet2;
 TH1F *massdecordeepjet_higgsscore_jet,*massdecordeepjet_higgsscore_jet1,*massdecordeepjet_higgsscore_jet2;
 TH1F *massdecordeepjet_qcdscore_jet,*massdecordeepjet_qcdscore_jet1,*massdecordeepjet_qcdscore_jet2;

uhh2::Event::Handle< std::vector<TopJet> > h_AK8PuppiTopTags;
uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
uhh2::Event::Handle<bool> h_is_zprime_reconstructed_correctmatch;
uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;
uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateCorrectMatch;
uhh2::Event::Handle<std::vector<ReconstructionHypothesis>> h_ttbar_hyps;
//uhh2::Event::Handle<float> h_chi2;
uhh2::Event::Handle<std::vector<double>> h_dnnoutput;

  virtual ~ZprimeSemiLeptonicHists();
};
