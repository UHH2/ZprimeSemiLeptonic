#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h"
#include "UHH2/core/include/LorentzVector.h"

bool TopJetLeptonDeltaRCleaner::process(uhh2::Event & event){

  assert(event.topjets);
  std::vector<TopJet> cleaned_topjets;

  for(const auto & tjet : *event.topjets){
    bool skip_tjet(false);

    if(event.muons){
      for(const auto & muo : *event.muons)
        if(uhh2::deltaR(tjet, muo) < minDR_) skip_tjet = true;
    }

    if(skip_tjet) continue;

    if(event.electrons){
      for(const auto & ele : *event.electrons)
        if(uhh2::deltaR(tjet, ele) < minDR_) skip_tjet = true;
    }

    if(!skip_tjet) cleaned_topjets.push_back(tjet);
  }

  event.topjets->clear();
  event.topjets->reserve(cleaned_topjets.size());
  for(auto & j : cleaned_topjets) event.topjets->push_back(j);

  return true;
}

const Particle* leading_lepton(const uhh2::Event& event){

  const Particle* lep(0);

  float ptL_max(0.);
  if(event.muons)    { for(const auto& mu : *event.muons)    { if(mu.pt() > ptL_max){ ptL_max = mu.pt(); lep = &mu; } } }
  if(event.electrons){ for(const auto& el : *event.electrons){ if(el.pt() > ptL_max){ ptL_max = el.pt(); lep = &el; } } }

  if(!lep) throw std::runtime_error("leading_lepton -- pt-leading lepton not found");

  return lep;
}

float HTlep(const uhh2::Event& event){

  float htlep(0.);

  assert((event.muons || event.electrons) && event.met);

  if(event.muons)    { for(const auto& mu : *event.muons)     htlep += mu.pt(); }
  if(event.electrons){ for(const auto& el : *event.electrons) htlep += el.pt(); }

  htlep += event.met->pt();

  return htlep;
}

float HTlep1(const uhh2::Event& event){

  assert((event.muons || event.electrons) && event.met);

  return (leading_lepton(event)->pt() + event.met->pt());
}
