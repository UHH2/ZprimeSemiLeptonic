#pragma once

#include <string>
#include <vector>

#include <TFile.h>
#include <TH2F.h>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Electron.h>

class weightcalc_elecID {

 public:
  explicit weightcalc_elecID(uhh2::Context&, const std::string&, const std::string&, const std::string&, const float);
  virtual ~weightcalc_elecID();

  virtual float elec_SFac(const Electron&, const std::string&) const;
  virtual float weight(const uhh2::Event&, const std::string&) const;

  virtual void set_verbose(const bool v){ verbose_ = v; }

 protected:
  bool verbose_;

  uhh2::Event::Handle<std::vector<Electron>> h_objs_;
  std::string sfac__input_;
  TFile* sfac__tfile_;
  TH2F*  sfac__thist_;
  float sys_pct_;
};

class weightcalc_elecHLT : public weightcalc_elecID {

 public:
  explicit weightcalc_elecHLT(uhh2::Context& ctx, const std::string& objs, const std::string& sfac_file, const std::string& sfac_hist, const float sys_pct) :
    weightcalc_elecID(ctx, objs, sfac_file, sfac_hist, sys_pct) {}
};
