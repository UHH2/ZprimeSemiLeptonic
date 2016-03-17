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
////

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
////

const Particle* leading_lepton(const uhh2::Event& event){

  const Particle* lep(0);

  float ptL_max(0.);
  if(event.muons)    { for(const auto& mu : *event.muons)    { if(mu.pt() > ptL_max){ ptL_max = mu.pt(); lep = &mu; } } }
  if(event.electrons){ for(const auto& el : *event.electrons){ if(el.pt() > ptL_max){ ptL_max = el.pt(); lep = &el; } } }

  if(!lep) throw std::runtime_error("leading_lepton -- pt-leading lepton not found");

  return lep;
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
////

bool trigger_bit(const uhh2::Event& evt_, const std::string& hlt_key_){

  uhh2::Event::TriggerIndex trg_index = evt_.get_trigger_index(hlt_key_);

  return bool(evt_.passes_trigger(trg_index));
}
////

GENWToLNuFinder::GENWToLNuFinder(uhh2::Context& ctx, const std::string& label){

  h_genWln_W_ = ctx.declare_event_output<GenParticle>(label+"_W");
  h_genWln_l_ = ctx.declare_event_output<GenParticle>(label+"_l");
  h_genWln_n_ = ctx.declare_event_output<GenParticle>(label+"_n");
}

bool GENWToLNuFinder::process(uhh2::Event& evt){

  const GenParticle *genW(0), *genW_lep(0), *genW_neu(0); {

    int genwN(0);

    assert(evt.genparticles);
    for(const auto& genp : *evt.genparticles){

      if(genwN > 1) throw std::runtime_error("GENWToLNuFinder::process -- logic error: more than 1 W->lnu decay found at GEN level");

      // gen-W
      const bool is_me = (20 <= genp.status() && genp.status() <= 30);
      if(!is_me) continue;

      const int is_w = (std::abs(genp.pdgId()) == 24);
      if(!is_w) continue;

      genW = &genp;

      // gen-W daughters
      const GenParticle* dau1 = genp.daughter(evt.genparticles, 1);
      const GenParticle* dau2 = genp.daughter(evt.genparticles, 2);

      if(dau1 && dau2){

        const int id1 = std::abs(dau1->pdgId());
        const int id2 = std::abs(dau2->pdgId());

        if((id1 == 11 || id1 == 13 || id1 == 15) &&
           (id2 == 12 || id2 == 14 || id2 == 16) ){ genW_lep = dau1; genW_neu = dau2; ++genwN; }

        if((id2 == 11 || id2 == 13 || id2 == 15) &&
           (id1 == 12 || id1 == 14 || id1 == 16) ){ genW_lep = dau2; genW_neu = dau1; ++genwN; }
      }
    }
  }

//  if(!genW || !genW_lep || !genW_neu){
//
//    std::cout << std::endl;
//    for(const auto& p : *evt.genparticles){
//
//      std::cout <<  " i=" << p.index()    ;
//      std::cout << " m1=" << p.mother1()  ;
//      std::cout << " m2=" << p.mother2()  ;
//      std::cout << " d1=" << p.daughter1();
//      std::cout << " d2=" << p.daughter2();
//      std::cout << " ID=" << p.pdgId()    ;
//      std::cout << " px=" << p.v4().Px()  ;
//      std::cout << " py=" << p.v4().Py()  ;
//      std::cout << " pz=" << p.v4().Pz()  ;
//      std::cout << std::endl;
//    }
//  }

  evt.set(h_genWln_W_, genW     ? GenParticle(*genW)     : GenParticle());
  evt.set(h_genWln_l_, genW_lep ? GenParticle(*genW_lep) : GenParticle());
  evt.set(h_genWln_n_, genW_neu ? GenParticle(*genW_neu) : GenParticle());

  return true;
}
////

MEPartonFinder::MEPartonFinder(uhh2::Context& ctx, const std::string& label){

  h_meps_ = ctx.declare_event_output<std::vector<GenParticle> >(label);
}

bool MEPartonFinder::process(uhh2::Event& evt){

  std::vector<GenParticle> mep_refs;

  assert(evt.genparticles);
  for(const auto& genp : *evt.genparticles){

    const bool is_me = (20 <= genp.status() && genp.status() <= 30);
    if(!is_me) continue;

    const bool has_mo1 = (genp.mother1() != (unsigned short)(-1));
    if(!has_mo1) continue;

    const bool has_mo2 = (genp.mother2() != (unsigned short)(-1));
    if(!has_mo2) continue;

    const int abs_id = std::abs(genp.pdgId());
    const bool is_parton = (((1<=abs_id) && (abs_id<=5)) || (abs_id == 21));
    if(!is_parton) continue;

    mep_refs.push_back(genp);
  }

  evt.set(h_meps_, std::move(mep_refs));

  return true;
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
////
