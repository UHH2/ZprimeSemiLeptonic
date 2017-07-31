#pragma once

#include <string>
#include <vector>
#include <sstream>
#include <cstdlib>

#include <TFile.h>
#include <TGraphAsymmErrors.h>
#include <TF2.h>

#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/TopJet.h>

#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/TopJetIds.h>

class weightcalc_ttagging {

 public:
  explicit weightcalc_ttagging(const std::string&, const std::string&,
                                                   const std::string&, const std::string&,
                                                   const std::string&, const std::string&,
                               const std::string&, const std::string&, const std::string&, const bool v=false);
  virtual ~weightcalc_ttagging();

  virtual void load_SFac(const std::string&, const std::string&);

  virtual int   jet_flavor(const TopJet&, const uhh2::Event&) const;
  virtual float jet_effy  (const TopJet&, const uhh2::Event&) const;
  virtual float jet_SFac  (const TopJet&, const uhh2::Event&) const;

  virtual float weight(const uhh2::Event&) const;

  void set_verbose(const bool v=true){ verbose_ = v; }

 protected:
  bool verbose_;

  TopJetId ttagWP_;

  float tjet_maxDR_gentop_;

  std::string sys_key__jetL_;
  std::string sys_key__jetT_;

  std::string measurement_type__jetL_;
  std::string measurement_type__jetT_;

  TFile            * effy__tfile_;
  TGraphAsymmErrors* effy__graph__jet_l_;
  TGraphAsymmErrors* effy__graph__jet_t_;

  void import_entry(std::stringstream&, const char, int&)         const;
  void import_entry(std::stringstream&, const char, float&)       const;
  void import_entry(std::stringstream&, const char, std::string&) const;

  struct ttagSF {

    std::string OperatingPoint;
    std::string measurementType;
    std::string sysType;
    int   jetFlavor;
    float etaMin;
    float etaMax;
    float ptMin;
    float ptMax;
    TF2   function;
  };

  std::vector<ttagSF> ttagSF_vec_;
};
