#pragma once

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/NtupleObjects.h>

class JetLeptonDeltaRCleaner : public uhh2::AnalysisModule {

 public:
  explicit JetLeptonDeltaRCleaner(float mindr=0.8): minDR_(mindr) {}
  virtual bool process(uhh2::Event&) override;

 private:
  float minDR_;
};

class TopJetLeptonDeltaRCleaner : public uhh2::AnalysisModule {

 public:
  explicit TopJetLeptonDeltaRCleaner(float mindr=0.8): minDR_(mindr) {}
  virtual bool process(uhh2::Event&) override;

 private:
  float minDR_;
};

const Particle* leading_lepton(const uhh2::Event&);

float HTlep (const uhh2::Event&);
float HTlep1(const uhh2::Event&);

float Muon_pfMINIIso    (const Muon&    , const uhh2::Event&, const std::string&);
float Electron_pfMINIIso(const Electron&, const uhh2::Event&, const std::string&);
bool trigger_bit(const uhh2::Event&, const std::string&);

class TopTagID_NO {

 public:
  explicit TopTagID_NO() {}

  bool operator()(const TopJet&, const uhh2::Event&) const { return false; }
};

class TopTagID_SoftDrop {

 public:
  explicit TopTagID_SoftDrop(const std::string&);
  virtual ~TopTagID_SoftDrop() {}

  bool operator()(const TopJet&, const uhh2::Event&) const;

  void cut_mass      (const bool c){ cut_mass_       = c; }
  void cut_tau32     (const bool c){ cut_tau32_      = c; }
  void cut_subjetbtag(const bool c){ cut_subjetbtag_ = c; }

 protected:
  bool cut_mass_;     
  bool cut_tau32_;    
  bool cut_subjetbtag_;

  float   mass_min_;
  float   mass_max_;
  float  tau32_max_;
  float sjbtag_min_;
};
