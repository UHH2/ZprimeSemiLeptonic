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
  uhh2::Event::Handle< float > h_Mu_pt, h_Mu_eta, h_Mu_phi, h_Mu_E;
  uhh2::Event::Handle< float > h_Ele_pt, h_Ele_eta, h_Ele_phi, h_Ele_E;
  uhh2::Event::Handle< float > h_MET_pt;
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

};

////
