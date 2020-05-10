#pragma once

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/NtupleObjects.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>
#include <UHH2/core/include/LorentzVector.h>
#include <UHH2/common/include/TTbarGen.h>

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
  explicit Variables_NN(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;

private:
  uhh2::Event::Handle< float > h_Mu_pt, h_Mu_eta, h_Mu_phi, h_Mu_E, h_Mu_px, h_Mu_py, h_Mu_pz;
  uhh2::Event::Handle< float > h_Ele_pt, h_Ele_eta, h_Ele_phi, h_Ele_E, h_Ele_px, h_Ele_py, h_Ele_pz;
  uhh2::Event::Handle< float > h_MET_pt, h_MET_px, h_MET_py;
  uhh2::Event::Handle< float > h_N_Ak8;
  uhh2::Event::Handle< float > h_Ak8_j1_pt, h_Ak8_j1_eta, h_Ak8_j1_phi, h_Ak8_j1_E, h_Ak8_j1_px, h_Ak8_j1_py, h_Ak8_j1_pz, h_Ak8_j1_mSD, h_Ak8_j1_tau21, h_Ak8_j1_tau32;
  uhh2::Event::Handle< float > h_Ak8_j2_pt, h_Ak8_j2_eta, h_Ak8_j2_phi, h_Ak8_j2_E, h_Ak8_j2_px, h_Ak8_j2_py, h_Ak8_j2_pz, h_Ak8_j2_mSD, h_Ak8_j2_tau21, h_Ak8_j2_tau32;
  uhh2::Event::Handle< float > h_Ak8_j3_pt, h_Ak8_j3_eta, h_Ak8_j3_phi, h_Ak8_j3_E, h_Ak8_j3_px, h_Ak8_j3_py, h_Ak8_j3_pz, h_Ak8_j3_mSD, h_Ak8_j3_tau21, h_Ak8_j3_tau32;
  uhh2::Event::Handle< float > h_Ak8_j4_pt, h_Ak8_j4_eta, h_Ak8_j4_phi, h_Ak8_j4_E, h_Ak8_j4_px, h_Ak8_j4_py, h_Ak8_j4_pz, h_Ak8_j4_mSD, h_Ak8_j4_tau21, h_Ak8_j4_tau32;
  uhh2::Event::Handle< float > h_Ak8_j5_pt, h_Ak8_j5_eta, h_Ak8_j5_phi, h_Ak8_j5_E, h_Ak8_j5_px, h_Ak8_j5_py, h_Ak8_j5_pz, h_Ak8_j5_mSD, h_Ak8_j5_tau21, h_Ak8_j5_tau32;
  uhh2::Event::Handle< float > h_N_Ak4;
  uhh2::Event::Handle< float > h_Ak4_j1_pt, h_Ak4_j1_eta, h_Ak4_j1_phi, h_Ak4_j1_E, h_Ak4_j1_px, h_Ak4_j1_py, h_Ak4_j1_pz, h_Ak4_j1_m;
  uhh2::Event::Handle< float > h_Ak4_j2_pt, h_Ak4_j2_eta, h_Ak4_j2_phi, h_Ak4_j2_E, h_Ak4_j2_px, h_Ak4_j2_py, h_Ak4_j2_pz, h_Ak4_j2_m;
  uhh2::Event::Handle< float > h_Ak4_j3_pt, h_Ak4_j3_eta, h_Ak4_j3_phi, h_Ak4_j3_E, h_Ak4_j3_px, h_Ak4_j3_py, h_Ak4_j3_pz, h_Ak4_j3_m;
  uhh2::Event::Handle< float > h_Ak4_j4_pt, h_Ak4_j4_eta, h_Ak4_j4_phi, h_Ak4_j4_E, h_Ak4_j4_px, h_Ak4_j4_py, h_Ak4_j4_pz, h_Ak4_j4_m;
  uhh2::Event::Handle< float > h_Ak4_j5_pt, h_Ak4_j5_eta, h_Ak4_j5_phi, h_Ak4_j5_E, h_Ak4_j5_px, h_Ak4_j5_py, h_Ak4_j5_pz, h_Ak4_j5_m;
  uhh2::Event::Handle< float > h_Ak4_j6_pt, h_Ak4_j6_eta, h_Ak4_j6_phi, h_Ak4_j6_E, h_Ak4_j6_px, h_Ak4_j6_py, h_Ak4_j6_pz, h_Ak4_j6_m;
  uhh2::Event::Handle< float > h_Ak4_j7_pt, h_Ak4_j7_eta, h_Ak4_j7_phi, h_Ak4_j7_E, h_Ak4_j7_px, h_Ak4_j7_py, h_Ak4_j7_pz, h_Ak4_j7_m;
  uhh2::Event::Handle< float > h_Ak4_j8_pt, h_Ak4_j8_eta, h_Ak4_j8_phi, h_Ak4_j8_E, h_Ak4_j8_px, h_Ak4_j8_py, h_Ak4_j8_pz, h_Ak4_j8_m;
  uhh2::Event::Handle< float > h_Ak4_j9_pt, h_Ak4_j9_eta, h_Ak4_j9_phi, h_Ak4_j9_E, h_Ak4_j9_px, h_Ak4_j9_py, h_Ak4_j9_pz, h_Ak4_j9_m;
  uhh2::Event::Handle< float > h_Ak4_j10_pt, h_Ak4_j10_eta, h_Ak4_j10_phi, h_Ak4_j10_E, h_Ak4_j10_px, h_Ak4_j10_py, h_Ak4_j10_pz, h_Ak4_j10_m;

};

////
