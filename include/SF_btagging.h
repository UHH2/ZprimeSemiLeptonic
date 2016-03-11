#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TF2.h>

#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Jet.h>

#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/JetIds.h>

class weightcalc_btagging {

 public:
  explicit weightcalc_btagging(const std::string&, const std::string&,
                               const std::string&, const std::string&, const std::string&,
                               const std::string&, const std::string&, const std::string&,
                               const std::string&, const std::string&, const std::string&, const std::string&, const bool v=false);
  virtual ~weightcalc_btagging();

  virtual void load_SFac(const std::string&, const std::string&);

  virtual float jet_effy(const Jet& jet_) const;
  virtual float jet_SFac(const Jet& jet_) const;

  virtual float weight(const uhh2::Event&) const;

  void set_verbose(const bool v=true){ verbose_ = v; }
  void set_abseta (const bool e=true){ abs_eta_ = e; }

 protected:
  bool verbose_;
  bool abs_eta_;

  JetId btagWP_;

  std::string sys_key__jetL_;
  std::string sys_key__jetC_;
  std::string sys_key__jetB_;

  std::string measurement_type__jetL_;
  std::string measurement_type__jetC_;
  std::string measurement_type__jetB_;

  TFile            * effy__tfile_;
  TGraphAsymmErrors* effy__graph__jet_l_;
  TGraphAsymmErrors* effy__graph__jet_c_;
  TGraphAsymmErrors* effy__graph__jet_b_;

  void import_entry(std::stringstream&, const char, int&)         const;
  void import_entry(std::stringstream&, const char, float&)       const;
  void import_entry(std::stringstream&, const char, std::string&) const;

  struct btagSF {

    int OperatingPoint;
    std::string measurementType;
    std::string sysType;
    int   jetFlavor;
    float etaMin;
    float etaMax;
    float ptMin;
    float ptMax;
    float discrMin;
    float discrMax;
    TF2   function;
  };

  std::vector<btagSF> btagSF_vec_;
};
