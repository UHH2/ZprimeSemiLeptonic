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

  int nparticle(0);
  for(auto & jet : *event.jets){
    if(jet.pt() > ptmin && fabs(jet.eta()) < etamax) ++nparticle;
  }

  return (nparticle >= nmin);
}
////////////////////////////////////////////////////////

bool TwoDCut::passes(const Event & event){
  // make sure that you have cleaned the electron and muon collections
  // event should content only one charged lepton
  // clean jets for pt>25 GeV before calling this routine 

  for(auto & ele : *event.electrons) {
    float drmin, ptrel;
    std::tie(drmin, ptrel) = drmin_pTrel(ele, *event.jets);
    if(ptrel < 25. && drmin < 0.5) return false;
  }

  for(auto & mu : *event.muons) {
    float drmin, ptrel;
    std::tie(drmin, ptrel) = drmin_pTrel(mu, *event.jets);
    if(ptrel < 25. && drmin < 0.5) return false;
  }

  return true;
}
////////////////////////////////////////////////////////

TopJetOverlapSelection::TopJetOverlapSelection(float delR_Lep_TopJet_, float delR_Jet_TopJet_):
  delR_Lep_TopJet(delR_Lep_TopJet_), delR_Jet_TopJet(delR_Jet_TopJet_), topjetid(CMSTopTag()) {

  ntopjet_sel.reset(new NTopJetSelection(1, -1, topjetid));
}

bool TopJetOverlapSelection::passes(const Event & event){ 

  bool ntopjet_selection = ntopjet_sel->passes(event);

  if(event.electrons->size() > 0){
    const auto & ele = (*event.electrons)[0];

    for(auto & topjet : * event.topjets){
      if(ntopjet_selection && delR_Lep_TopJet < deltaR(ele, topjet)){
        for(auto & jet : * event.jets){
          if(deltaR(jet, topjet) > delR_Jet_TopJet) return true;
        }
      }
    }
  }

  if(event.muons->size() > 0){
    const auto & mu = (*event.muons)[0];

    for(auto & topjet : * event.topjets){
      if(ntopjet_selection && delR_Lep_TopJet < deltaR(mu, topjet)){
        for(auto & jet : * event.jets){
          if(deltaR(jet, topjet) > delR_Jet_TopJet) return true;
        }
      }
    }
  }

  return false;
}
////////////////////////////////////////////////////////
