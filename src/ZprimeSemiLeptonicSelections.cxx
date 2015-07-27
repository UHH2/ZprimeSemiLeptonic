#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h"

#include <iostream>
#include <memory>

#include "UHH2/core/include/LorentzVector.h"
#include "UHH2/common/include/ReconstructionHypothesisDiscriminators.h"
#include "UHH2/common/include/Utils.h"

uhh2::HTlepCut::HTlepCut(float min_htlep, float max_htlep):
  min_htlep_(min_htlep), max_htlep_(max_htlep) {}

bool uhh2::HTlepCut::passes(const uhh2::Event & event){

  float htlep = HTlep1(event);

  return (htlep > min_htlep_) && (htlep < max_htlep_);
}
////////////////////////////////////////////////////////

uhh2::METCut::METCut(float min_met, float max_met):
  min_met_(min_met), max_met_(max_met) {}

bool uhh2::METCut::passes(const uhh2::Event & event){

  assert(event.met);

  float MET = event.met->pt();
  return (MET > min_met_) && (MET < max_met_);
}
////////////////////////////////////////////////////////

uhh2::NJetCut::NJetCut(int nmin_, int nmax_, float ptmin_, float etamax_):
  nmin(nmin_), nmax(nmax_), ptmin(ptmin_), etamax(etamax_) {}

bool uhh2::NJetCut::passes(const uhh2::Event & event){

  int njet(0);
  for(auto & jet : *event.jets){
    if(jet.pt() > ptmin && fabs(jet.eta()) < etamax) ++njet;
  }

  return (njet >= nmin) && (njet <= nmax);
}
////////////////////////////////////////////////////////

bool uhh2::TwoDCut1::passes(const uhh2::Event& event){

  assert(event.muons && event.electrons && event.jets);

  const Particle* lepton = leading_lepton(event);

  float drmin, ptrel;
  std::tie(drmin, ptrel) = drmin_pTrel(*lepton, *event.jets);

  return (drmin > min_deltaR_) || (ptrel > min_pTrel_);
}
////////////////////////////////////////////////////////

bool uhh2::TwoDCutALL::passes(const uhh2::Event & event){

  assert(event.muons && event.electrons && event.jets);

  for(const auto& muo : *event.muons){

    float drmin, ptrel;
    std::tie(drmin, ptrel) = drmin_pTrel(muo, *event.jets);

    const bool pass = (drmin > min_deltaR_) || (ptrel > min_pTrel_);
    if(!pass) return false;
  }

  for(const auto& ele : *event.electrons){

    float drmin, ptrel;
    std::tie(drmin, ptrel) = drmin_pTrel(ele, *event.jets);

    const bool pass = (drmin > min_deltaR_) || (ptrel > min_pTrel_);
    if(!pass) return false;
  }

  return true;
}
////////////////////////////////////////////////////////

bool uhh2::TwoDCut::passes(const uhh2::Event & event){

  assert(event.muons && event.electrons && event.jets);
  if((event.muons->size()+event.electrons->size()) != 1){
    std::cout << "\n @@@ WARNING -- TwoDCut::passes -- unexpected number of muons+electrons in the event (!=1). returning 'false'\n";
    return false;
  }

  float drmin, ptrel;  
  if(event.muons->size()) std::tie(drmin, ptrel) = drmin_pTrel(event.muons->at(0), *event.jets);
  else std::tie(drmin, ptrel) = drmin_pTrel(event.electrons->at(0), *event.jets);

  return (drmin > min_deltaR_) || (ptrel > min_pTrel_);
}
////////////////////////////////////////////////////////

uhh2::TriangularCuts::TriangularCuts(float a, float b): a_(a), b_(b) {

  if(!b_) std::runtime_error("TriangularCuts -- incorrect initialization (parameter 'b' is null)");
}

bool uhh2::TriangularCuts::passes(const uhh2::Event & event){

  assert(event.muons || event.electrons);
  assert(event.jets && event.met);

  if((event.muons->size()+event.electrons->size()) != 1){
    std::cout << "\n @@@ WARNING -- TriangularCuts::passes -- unexpected number of muons+electrons in the event (!=1). returning 'false'\n";
    return false;
  }

  if(!event.jets->size()){
    std::cout << "\n @@@ WARNING -- TriangularCuts::passes -- unexpected number of jets in the event (==0). returning 'false'\n";
    return false;
  }

  // pt-leading charged lepton
  const Particle* lep1 = leading_lepton(event);

  // 1st entry in jet collection (should be the pt-leading jet)
  const Particle* jet1 = &event.jets->at(0);

  // MET-lepton triangular cut
  bool pass_tc_lep = fabs(fabs(deltaPhi(*event.met, *lep1)) - a_) < a_/b_ * event.met->pt();

  // MET-jet triangular cut
  bool pass_tc_jet = fabs(fabs(deltaPhi(*event.met, *jet1)) - a_) < a_/b_ * event.met->pt();

  return pass_tc_lep && pass_tc_jet;
}
////////////////////////////////////////////////////////

uhh2::TriangularCutsELE::TriangularCutsELE(float a, float b): a_(a), b_(b) {

  if(!b_) std::runtime_error("TriangularCuts -- incorrect initialization (parameter 'b' is null)");
}

bool uhh2::TriangularCutsELE::passes(const uhh2::Event & event){

  assert(event.electrons);
  assert(event.jets && event.met);

  if(event.electrons->size() != 1) std::runtime_error("TriangularCutsELE::passes -- unexpected number of electrons in the event (!=1)");
  if(event.jets     ->size() == 0) std::runtime_error("TriangularCutsELE::passes -- unexpected number of jets in the event (==0)");

  // pt-leading charged lepton
  const Particle* lep1 = &event.electrons->at(0);

  // 1st entry in jet collection (should be the pt-leading jet)
  const Particle* jet1 = &event.jets->at(0);

  // MET-lepton triangular cut
  bool pass_tc_lep = fabs(fabs(deltaPhi(*event.met, *lep1)) - a_) < a_/b_ * event.met->pt();

  // MET-jet triangular cut
  bool pass_tc_jet = fabs(fabs(deltaPhi(*event.met, *jet1)) - a_) < a_/b_ * event.met->pt();

  return pass_tc_lep && pass_tc_jet;
}
////////////////////////////////////////////////////////

uhh2::DiLeptonSelection::DiLeptonSelection(const std::string& channel, const bool opposite_charge, const bool veto_other_flavor):
  channel_(channel), opposite_charge_(opposite_charge), veto_other_flavor_(veto_other_flavor) {}

bool uhh2::DiLeptonSelection::passes(const uhh2::Event & event){ 

  bool pass(false);

  assert(event.muons && event.electrons);

  if(channel_ == "muon"){

    pass = (event.muons->size() == 2);

    if(pass && opposite_charge_)   pass &= ((event.muons->at(0).charge() * event.muons->at(1).charge()) == -1);
    if(pass && veto_other_flavor_) pass &= (event.electrons->size() == 0);
  }
  else if(channel_ == "elec"){

    pass = (event.electrons->size() == 2);

    if(pass && opposite_charge_)   pass &= ((event.electrons->at(0).charge() * event.electrons->at(1).charge()) == -1);
    if(pass && veto_other_flavor_) pass &= (event.muons->size() == 0);
  }
  else std::runtime_error("DiLeptonSelection::passes -- undefined key for lepton channel: "+channel_);

  return pass;
}
////////////////////////////////////////////////////////

uhh2::TopTagEventSelection::TopTagEventSelection(const TopJetId& tjetID, float minDR_jet_ttag):
  topjetID_(tjetID), minDR_jet_toptag_(minDR_jet_ttag) {

  topjet1_sel_.reset(new NTopJetSelection(1, -1, topjetID_));
}

bool uhh2::TopTagEventSelection::passes(const uhh2::Event & event){ 

  if(!topjet1_sel_->passes(event)) return false;

  for(auto & topjet : * event.topjets){
    if(!topjetID_(topjet, event)) continue;

    for(auto & jet : * event.jets)
      if(deltaR(jet, topjet) > minDR_jet_toptag_) return true;
  }

  return false;
}
////////////////////////////////////////////////////////

uhh2::LeptonicTopPtCut::LeptonicTopPtCut(uhh2::Context& ctx, float pt_min, float pt_max, const std::string& hyps_name, const std::string& disc_name):
  tlep_pt_min_(pt_min), tlep_pt_max_(pt_max), h_hyps_(ctx.get_handle<std::vector<ReconstructionHypothesis>>(hyps_name)), disc_name_(disc_name) {}

bool uhh2::LeptonicTopPtCut::passes(const uhh2::Event& event){

  std::vector<ReconstructionHypothesis> hyps = event.get(h_hyps_);
  const ReconstructionHypothesis* hyp = get_best_hypothesis(hyps, disc_name_);
  if(!hyp) std::runtime_error("LeptonicTopPtCut -- best hypothesis not found (discriminator="+disc_name_+")");

  float tlep_pt = hyp->toplep_v4().Pt();

  return (tlep_pt > tlep_pt_min_) && (tlep_pt < tlep_pt_max_);
}
////////////////////////////////////////////////////////

uhh2::HypothesisDiscriminatorCut::HypothesisDiscriminatorCut(uhh2::Context& ctx, float disc_min, float disc_max, const std::string& hyps_name, const std::string& disc_bhyp, const std::string& disc_cut):
  disc_min_(disc_min), disc_max_(disc_max), h_hyps_(ctx.get_handle<std::vector<ReconstructionHypothesis>>(hyps_name)), disc_bhyp_(disc_bhyp), disc_cut_(disc_cut) {}

bool uhh2::HypothesisDiscriminatorCut::passes(const uhh2::Event & event){

  std::vector<ReconstructionHypothesis> hyps = event.get(h_hyps_);
  const ReconstructionHypothesis* hyp = get_best_hypothesis(hyps, disc_bhyp_);
  if(!hyp) std::runtime_error("HypothesisDiscriminatorCut -- best hypothesis not found (discriminator="+disc_bhyp_+")");

  float disc_val = hyp->discriminator(disc_cut_);

  return (disc_val > disc_min_) && (disc_val < disc_max_);
}
////////////////////////////////////////////////////////
