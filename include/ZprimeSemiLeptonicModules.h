#pragma once

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/NtupleObjects.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>
#include <UHH2/core/include/LorentzVector.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/NSelections.h>
#include "UHH2/common/include/BTagCalibrationStandalone.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/Utils.h"

#include <UHH2/HOTVR/include/HOTVRIds.h>

#include <UHH2/ZprimeSemiLeptonic/include/constants.hpp>

#include "TH1.h"

float inv_mass(const LorentzVector&);

class ZprimeCandidateBuilder : uhh2::AnalysisModule{

public:
  explicit ZprimeCandidateBuilder(uhh2::Context&, TString mode, float minDR = 1.2);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< std::vector<ZprimeCandidate> > h_ZprimeCandidates_;
  uhh2::Event::Handle< std::vector<TopJet> > h_AK8TopTags;
  uhh2::Event::Handle< std::vector<const TopJet*> > h_AK8TopTagsPtr;

  float minDR_;
  TString mode_;

};

class ZprimeChi2Discriminator : uhh2::AnalysisModule{

public:
  explicit ZprimeChi2Discriminator(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< std::vector<ZprimeCandidate> > h_ZprimeCandidates_;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestCandidate_;
  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_;
  float mtoplep_, mtoplep_ttag_;
  float sigmatoplep_, sigmatoplep_ttag_;
  float mtophad_, mtophad_ttag_;
  float sigmatophad_, sigmatophad_ttag_;

};

class ZprimeCorrectMatchDiscriminator : uhh2::AnalysisModule{

public:
  explicit ZprimeCorrectMatchDiscriminator(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< std::vector<ZprimeCandidate> > h_ZprimeCandidates_;
  uhh2::Event::Handle<TTbarGen> h_ttbargen_;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestCandidate_;
  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_;

  bool is_mc;
  std::unique_ptr<TTbarGenProducer> ttgenprod;

};

class AK8PuppiTopTagger : public uhh2::AnalysisModule {

public:
  explicit AK8PuppiTopTagger(uhh2::Context&, int min_num_daughters = 2, float max_dR = 1., float min_mass = 105., float max_mass = 210., float max_tau32 = 0.65);
  virtual bool process(uhh2::Event&) override;

private:
  int min_num_daughters_ = 2;
  float max_dR_;
  float min_mass_;
  float max_mass_;
  float max_tau32_;
  uhh2::Event::Handle< std::vector<TopJet> > h_AK8PuppiTopTags_;
  uhh2::Event::Handle< std::vector<const TopJet*> > h_AK8PuppiTopTagsPtr_;
};



class HOTVRTopTagger : public uhh2::AnalysisModule {

public:
  explicit HOTVRTopTagger(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< std::vector<TopJet> > h_HOTVRTopTags_;
  uhh2::Event::Handle< std::vector<const TopJet*> > h_HOTVRTopTagsPtr_;

  TopJetId toptag_id = AndId<TopJet>(HOTVRTopTag(0.8, 140.0, 220.0, 50.0), Tau32Groomed(0.56));

};


class DeepAK8TopTagger : public uhh2::AnalysisModule {

public:
  explicit DeepAK8TopTagger(uhh2::Context&, float min_mSD = 105., float max_mSD = 210., float max_score = 0.685, float pt_min = 400); // WP from https://indico.cern.ch/event/877167/contributions/3744193/attachments/1989744/3379280/DeepAK8_Top_W_SFs_V2.pdf
  virtual bool process(uhh2::Event&) override;

private:
  float min_mSD_;
  float max_mSD_;
  float max_score_;
  float pt_min_;
  uhh2::Event::Handle< std::vector<TopJet> > h_DeepAK8TopTags_;
  uhh2::Event::Handle< std::vector<const TopJet*> > h_DeepAK8TopTagsPtr_;
};



class JetLeptonDeltaRCleaner : public uhh2::AnalysisModule {

public:
  explicit JetLeptonDeltaRCleaner(float mindr=0.8): minDR_(mindr) {}
  virtual bool process(uhh2::Event&) override;

private:
  float minDR_;
};
////

class TopJetLeptonDeltaRCleaner : public uhh2::AnalysisModule {

public:
  explicit TopJetLeptonDeltaRCleaner(float mindr=0.8): minDR_(mindr) {}
  virtual bool process(uhh2::Event&) override;

private:
  float minDR_;
};
////

const Particle* leading_lepton(const uhh2::Event&);

float STlep(const uhh2::Event&);

float Muon_pfMINIIso    (const Muon&    , const uhh2::Event&, const std::string&);
float Electron_pfMINIIso(const Electron&, const uhh2::Event&, const std::string&);
////

bool trigger_bit(const uhh2::Event&, const std::string&);
////

class GENWToLNuFinder : public uhh2::AnalysisModule {

public:
  explicit GENWToLNuFinder(uhh2::Context&, const std::string&);
  virtual ~GENWToLNuFinder() {}

  virtual bool process(uhh2::Event&) override;

protected:
  uhh2::Event::Handle<GenParticle> h_genWln_W_;
  uhh2::Event::Handle<GenParticle> h_genWln_l_;
  uhh2::Event::Handle<GenParticle> h_genWln_n_;
};

class MEPartonFinder : public uhh2::AnalysisModule {

public:
  explicit MEPartonFinder(uhh2::Context&, const std::string&);
  virtual ~MEPartonFinder() {}

  virtual bool process(uhh2::Event&) override;

protected:
  uhh2::Event::Handle<std::vector<GenParticle> > h_meps_;
};


////////////////////////    NN vars
class Variables_NN : uhh2::AnalysisModule{

public:
  explicit Variables_NN(uhh2::Context&, TString mode);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;
  uhh2::Event::Handle< std::vector<Jet> > h_CHSjets_matched;
  uhh2::Event::Handle< float > h_eventweight;
  uhh2::Event::Handle< float > h_Mu_pt, h_Mu_eta, h_Mu_phi, h_Mu_E;
  uhh2::Event::Handle< float > h_Ele_pt, h_Ele_eta, h_Ele_phi, h_Ele_E;
  uhh2::Event::Handle< float > h_MET_pt, h_MET_phi;
  uhh2::Event::Handle< float > h_N_HOTVR;
  uhh2::Event::Handle< float > h_HOTVR_j1_pt, h_HOTVR_j1_eta, h_HOTVR_j1_phi, h_HOTVR_j1_E, h_HOTVR_j1_mSD, h_HOTVR_j1_tau21, h_HOTVR_j1_tau32;
  uhh2::Event::Handle< float > h_HOTVR_j2_pt, h_HOTVR_j2_eta, h_HOTVR_j2_phi, h_HOTVR_j2_E, h_HOTVR_j2_mSD, h_HOTVR_j2_tau21, h_HOTVR_j2_tau32;
  uhh2::Event::Handle< float > h_HOTVR_j3_pt, h_HOTVR_j3_eta, h_HOTVR_j3_phi, h_HOTVR_j3_E, h_HOTVR_j3_mSD, h_HOTVR_j3_tau21, h_HOTVR_j3_tau32;
  uhh2::Event::Handle< float > h_N_Ak8;
  uhh2::Event::Handle< float > h_Ak8_j1_pt, h_Ak8_j1_eta, h_Ak8_j1_phi, h_Ak8_j1_E, h_Ak8_j1_mSD, h_Ak8_j1_tau21, h_Ak8_j1_tau32;
  uhh2::Event::Handle< float > h_Ak8_j2_pt, h_Ak8_j2_eta, h_Ak8_j2_phi, h_Ak8_j2_E, h_Ak8_j2_mSD, h_Ak8_j2_tau21, h_Ak8_j2_tau32;
  uhh2::Event::Handle< float > h_Ak8_j3_pt, h_Ak8_j3_eta, h_Ak8_j3_phi, h_Ak8_j3_E, h_Ak8_j3_mSD, h_Ak8_j3_tau21, h_Ak8_j3_tau32;
  uhh2::Event::Handle< float > h_N_Ak4;
  uhh2::Event::Handle< float > h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_m, h_Ak4_j1_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_m, h_Ak4_j2_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j3_pt, h_Ak4_j3_eta, h_Ak4_j3_phi, h_Ak4_j3_E, h_Ak4_j3_m, h_Ak4_j3_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j4_pt, h_Ak4_j4_eta, h_Ak4_j4_phi, h_Ak4_j4_E, h_Ak4_j4_m, h_Ak4_j4_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j5_pt, h_Ak4_j5_eta, h_Ak4_j5_phi, h_Ak4_j5_E, h_Ak4_j5_m, h_Ak4_j5_deepjetbscore;
  uhh2::Event::Handle< float > h_Ak4_j6_pt, h_Ak4_j6_eta, h_Ak4_j6_phi, h_Ak4_j6_E, h_Ak4_j6_m, h_Ak4_j6_deepjetbscore;
  uhh2::Event::Handle< float > h_M_tt;

  TString mode_;

};

////

// Generic Class for Applying SFs - from Andrea
class ScaleFactorsFromHistos : public uhh2::AnalysisModule {

public:
  void LoadHisto(TFile* file, std::string name, std::string hname);
  double Evaluator(std::string hname, double var);

protected:
  std::unordered_map<std::string, std::unique_ptr<TH1F> > histos;

};

// Apply Corrections V+jets
class NLOCorrections : public ScaleFactorsFromHistos {

public:
  explicit NLOCorrections(uhh2::Context& ctx);
  virtual bool process(uhh2::Event&) override;
  double GetPartonObjectPt(uhh2::Event& event, ParticleID objID);

private:
  bool is_Wjets, is_Zjets, is_DY, is_Znn, is2016;

};

////

// Top pT Reweighting extended - from Alex F.
class TopPtReweighting : public uhh2::AnalysisModule {
 public:
  explicit TopPtReweighting(uhh2::Context& ctx,
			 float a, float b,
			 const std::string& syst_a,
			 const std::string& syst_b,
			 const std::string& ttgen_name ="");


  virtual bool process(uhh2::Event& event) override;
 private:
  uhh2::Event::Handle<TTbarGen> h_ttbargen_;
  float a_, b_;
  std::string version_;
  std::string ttgen_name_;
  uhh2::Event::Handle< float > h_weight_toppt_nominal;
  uhh2::Event::Handle< float > h_weight_toppt_a_up;
  uhh2::Event::Handle< float > h_weight_toppt_b_up;
  uhh2::Event::Handle< float > h_weight_toppt_a_down;
  uhh2::Event::Handle< float > h_weight_toppt_b_down;
};


class PuppiCHS_matching : public uhh2::AnalysisModule {

public:
  explicit PuppiCHS_matching(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< std::vector<Jet> > h_CHSjets;
  uhh2::Event::Handle< std::vector<Jet> > h_CHS_matched_;
};

////

// Muon RECO SF (from https://twiki.cern.ch/twiki/bin/view/CMS/MuonUL2016#RECO_efficiency)
// Add handles with nominal values and up/down variations and apply nominal sf to event.weight

class MuonRecoSF : public uhh2::AnalysisModule {

public:
  explicit MuonRecoSF(uhh2::Context &ctx);
  virtual bool process(uhh2::Event &event) override;

private:
  Year year;
  bool is_mc, is_Muon;
  uhh2::Event::Handle< float > h_muonrecSF_nominal;
  uhh2::Event::Handle< float > h_muonrecSF_up;
  uhh2::Event::Handle< float > h_muonrecSF_down;
};

////
