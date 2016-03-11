#pragma once

#include <string>
#include <vector>

#include <TFile.h>
#include <TH2F.h>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Muon.h>

class weightcalc_muonID {

 public:
  explicit weightcalc_muonID(uhh2::Context&, const std::string&, const std::string&, const std::string&, const float);
  virtual ~weightcalc_muonID();

  virtual float muon_SFac(const Muon&, const std::string&) const;
  virtual float weight(const uhh2::Event&, const std::string&) const;

  virtual void set_verbose(const bool v){ verbose_ = v; }

 protected:
  bool verbose_;

  uhh2::Event::Handle<std::vector<Muon>> h_objs_;
  std::string sfac__input_;
  TFile* sfac__tfile_;
  TH2F*  sfac__thist_;
  float sys_pct_;
};

class weightcalc_muonHLT : public weightcalc_muonID {

 public:
  explicit weightcalc_muonHLT(uhh2::Context& ctx, const std::string& objs, const std::string& sfac_file, const std::string& sfac_hist, const float sys_pct) :
    weightcalc_muonID(ctx, objs, sfac_file, sfac_hist, sys_pct) {}
};
