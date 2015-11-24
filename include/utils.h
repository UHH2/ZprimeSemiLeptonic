#pragma once

#include <string>
#include <vector>
#include <stdexcept>

#include <UHH2/core/include/NtupleObjects.h>

namespace util {

  std::vector<std::string> string_tokens(const std::string&, const std::string&);

  template<typename LEP> float pfMINIIso(const LEP&, const std::string&);

}

template<typename LEP>
float util::pfMINIIso(const LEP& lep, const std::string& iso_key_){

  float iso(-1.);

  if(!lep.pt()) throw std::runtime_error("EffyLeptonISOHists::pfMINIIso -- null muon transverse momentum: failed to calculate relative MINI-Isolation");

  if     (iso_key_ == "uncorrected") iso = (lep.pfMINIIso_CH() + lep.pfMINIIso_NH() + lep.pfMINIIso_Ph())/lep.pt();
  else if(iso_key_ == "delta-beta")  iso = (lep.pfMINIIso_CH() + std::max(0., lep.pfMINIIso_NH() + lep.pfMINIIso_Ph() - .5*lep.pfMINIIso_PU()))/lep.pt();
  else if(iso_key_ == "pf-weight")   iso = (lep.pfMINIIso_CH() + lep.pfMINIIso_NH_pfwgt() + lep.pfMINIIso_Ph_pfwgt())/lep.pt();
  else throw std::runtime_error("EffyLeptonISOHists::pfMINIIso -- invalid key for MINI-Isolation pileup correction: "+iso_key_);

  return iso;
}
