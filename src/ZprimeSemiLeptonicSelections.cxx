#include <stdexcept>
#include <iostream>
#include <memory>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/ElectronHists.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimePreSelectionHists.h"
#include "UHH2/common/include/TTbarGen.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/LorentzVector.h"
#include "UHH2/common/include/TopJetIds.h"
#include "UHH2/core/include/Selection.h"
#include "UHH2/common/include/ObjectIdUtils.h"
#include "UHH2/common/include/JetIds.h"
#include "UHH2/common/include/NSelections.h"

using namespace uhh2;

HTlepCut::HTlepCut(float min_htlep, float max_htlep):
  min_htlep_(min_htlep), max_htlep_(max_htlep) {}

bool HTlepCut::passes(const Event & event){

  assert(event.muons || event.electrons);
  assert(event.met);

  float plep_pt(0.);

  if(event.electrons){
    for(const auto & ele : *event.electrons){
      if(ele.pt() > plep_pt) plep_pt = ele.pt();
    }
  }

  if(event.muons) {
    for(const auto & mu : *event.muons){
      if(mu.pt() > plep_pt) plep_pt = mu.pt();
    }
  }

  float htlep = plep_pt + event.met->pt();
  return (htlep > min_htlep_) && (htlep < max_htlep_);
}
////////////////////////////////////////////////////////

HypothesisDiscriminatorCut::HypothesisDiscriminatorCut(uhh2::Context& ctx, float min_discr, float max_discr, const std::string& discr_name, const std::string& hyps_name):
  m_min_discr_(min_discr), m_max_discr_(max_discr), m_discriminator_name(discr_name), h_hyps(ctx.get_handle<std::vector<ReconstructionHypothesis>>(hyps_name)) {}

bool HypothesisDiscriminatorCut::passes(const Event & event){

  std::vector<ReconstructionHypothesis> hyps = event.get(h_hyps);
  const ReconstructionHypothesis* hyp = get_best_hypothesis( hyps, m_discriminator_name);

  if(!hyp){
//    std::cout << "WARNING: no hypothesis " << m_discr->GetLabel() << " found, event is rejected.\n";
    return false;
  }

  float discr_value = hyp->discriminator(m_discriminator_name);
  if(discr_value < m_min_discr_ || discr_value > m_max_discr_) return false;

  return true;
}
////////////////////////////////////////////////////////

METCut::METCut(float min_met, float max_met):
  min_met_(min_met), max_met_(max_met) {}

bool METCut::passes(const Event & event){

  float MET = event.met->pt();
  return (MET > min_met_) && (MET < max_met_);
}
////////////////////////////////////////////////////////

NJetCut::NJetCut(int nmin_, int nmax_, float ptmin_, float etamax_):
  nmin(nmin_), nmax(nmax_), ptmin(ptmin_), etamax(etamax_) {}

bool NJetCut::passes(const Event & event){

  int njet(0);
  for(auto & jet : *event.jets){
    if(jet.pt() > ptmin && fabs(jet.eta()) < etamax) ++njet;
  }

  return (njet >= nmin) && (njet <= nmax);
}
////////////////////////////////////////////////////////

bool TwoDCut::passes(const Event & event){

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

TopTagEventSelection::TopTagEventSelection(const TopJetId& tjetID, float minDR_jet_ttag):
  topjetID_(tjetID), minDR_jet_toptag_(minDR_jet_ttag) {

  topjet1_sel_.reset(new NTopJetSelection(1, -1, topjetID_));
}

bool TopTagEventSelection::passes(const Event & event){ 

  if(!topjet1_sel_->passes(event)) return false;

  for(auto & topjet : * event.topjets){
    if(!topjetID_(topjet, event)) continue;

    for(auto & jet : * event.jets)
      if(deltaR(jet, topjet) > minDR_jet_toptag_) return true;
  }

  return false;
}
////////////////////////////////////////////////////////
