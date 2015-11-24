#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/core/include/LorentzVector.h>

bool JetLeptonDeltaRCleaner::process(uhh2::Event& event){

  assert(event.jets);
  std::vector<Jet> cleaned_jets;

  for(const auto & tjet : *event.jets){
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

    if(!skip_tjet) cleaned_jets.push_back(tjet);
  }

  event.jets->clear();
  event.jets->reserve(cleaned_jets.size());
  for(const auto& j : cleaned_jets) event.jets->push_back(j);

  return true;
}

bool TopJetLeptonDeltaRCleaner::process(uhh2::Event& event){

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
  for(const auto& j : cleaned_topjets) event.topjets->push_back(j);

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

float Muon_pfMINIIso(const Muon& muo, const uhh2::Event&, const std::string& iso_key_){

  float iso(-1.);

  if(!muo.pt()) throw std::runtime_error("Muon_pfMINIIso -- null muon transverse momentum: failed to calculate relative MINI-Isolation");

  if     (iso_key_ == "uncorrected") iso = (muo.pfMINIIso_CH() + muo.pfMINIIso_NH() + muo.pfMINIIso_Ph())/muo.pt();
  else if(iso_key_ == "delta-beta")  iso = (muo.pfMINIIso_CH() + std::max(0., muo.pfMINIIso_NH() + muo.pfMINIIso_Ph() - .5*muo.pfMINIIso_PU()))/muo.pt();
  else if(iso_key_ == "pf-weight")   iso = (muo.pfMINIIso_CH() + muo.pfMINIIso_NH_pfwgt() + muo.pfMINIIso_Ph_pfwgt())/muo.pt();
  else throw std::runtime_error("Muon_pfMINIIso -- invalid key for MINI-Isolation pileup correction: "+iso_key_);

  return iso;
}

float Electron_pfMINIIso(const Electron& ele, const uhh2::Event&, const std::string& iso_key_){

  float iso(-1.);

  if(!ele.pt()) throw std::runtime_error("Electron_pfMINIIso -- null muon transverse momentum: failed to calculate relative MINI-Isolation");

  if     (iso_key_ == "uncorrected") iso = (ele.pfMINIIso_CH() + ele.pfMINIIso_NH() + ele.pfMINIIso_Ph())/ele.pt();
  else if(iso_key_ == "delta-beta")  iso = (ele.pfMINIIso_CH() + std::max(0., ele.pfMINIIso_NH() + ele.pfMINIIso_Ph() - .5*ele.pfMINIIso_PU()))/ele.pt();
  else if(iso_key_ == "pf-weight")   iso = (ele.pfMINIIso_CH() + ele.pfMINIIso_NH_pfwgt() + ele.pfMINIIso_Ph_pfwgt())/ele.pt();
  else throw std::runtime_error("Electron_pfMINIIso -- invalid key for MINI-Isolation pileup correction: "+iso_key_);

  return iso;
}

bool trigger_bit(const uhh2::Event& evt_, const std::string& hlt_key_){

  uhh2::Event::TriggerIndex trg_index = evt_.get_trigger_index(hlt_key_);

  return bool(evt_.passes_trigger(trg_index));
}
////

TopTagID_SoftDrop::TopTagID_SoftDrop(const std::string& wp_key){

  if     (wp_key == "mr001_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .44; sjbtag_min_ = -1.; }
  else if(wp_key == "mr001_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .54; sjbtag_min_ = .79; }
  else if(wp_key == "mr003_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .50; sjbtag_min_ = -1.; }
  else if(wp_key == "mr003_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .61; sjbtag_min_ = .76; }
  else if(wp_key == "mr010_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .59; sjbtag_min_ = -1.; }
  else if(wp_key == "mr010_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .69; sjbtag_min_ = .66; }
  else if(wp_key == "mr030_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .69; sjbtag_min_ = -1.; }
  else if(wp_key == "mr030_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .75; sjbtag_min_ = .39; }
  else if(wp_key == "mr100_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .86; sjbtag_min_ = -1.; }
  else if(wp_key == "mr100_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .87; sjbtag_min_ =.089; }

  else throw std::runtime_error("TopTagID_SoftDrop -- undefined key for working-point: "+wp_key);

  cut_mass_       = true;
  cut_tau32_      = true;
  cut_subjetbtag_ = true;
}

bool TopTagID_SoftDrop::operator()(const TopJet& tj, const uhh2::Event&) const {

  const bool pass_mass = (mass_min_ < tj.softdropmass()) && (tj.softdropmass() < mass_max_);
  if(cut_mass_ && !pass_mass) return false;

  const bool pass_tau32 = (tj.tau2()>0) && (tj.tau3() < tau32_max_*tj.tau2());
  if(cut_tau32_ && !pass_tau32) return false;

  bool pass_sjbtag(false);
  if(sjbtag_min_ == -1.) pass_sjbtag = true;
  else {

    std::vector<Jet> subjets = tj.subjets();

    if(!subjets.size()) pass_sjbtag = false;
    else{

      std::sort(subjets.begin(), subjets.end(), [](const Jet& j1, const Jet& j2){return j1.btag_combinedSecondaryVertex() > j2.btag_combinedSecondaryVertex();});
      pass_sjbtag = (subjets.at(0).btag_combinedSecondaryVertex() > sjbtag_min_);
    }
  }
  if(cut_subjetbtag_ && !pass_sjbtag) return false;

  return true;
}
