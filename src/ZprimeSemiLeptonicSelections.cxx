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


using namespace std;
using namespace uhh2;

DijetSelection::DijetSelection(float dphi_min_, float third_frac_max_): dphi_min(dphi_min_), third_frac_max(third_frac_max_){}
    
bool DijetSelection::passes(const Event & event){
    assert(event.jets); // if this fails, it probably means jets are not read in
    if(event.jets->size() < 2) return false;
    const auto & jet0 = event.jets->at(0);
    const auto & jet1 = event.jets->at(1);
    auto dphi = deltaPhi(jet0, jet1);
    if(dphi < dphi_min) return false;
    if(event.jets->size() == 2) return true;
    const auto & jet2 = event.jets->at(2);
    auto third_jet_frac = jet2.pt() / (0.5 * (jet0.pt() + jet1.pt()));
    return third_jet_frac < third_frac_max;
}

HTlepCut::HTlepCut(Context & ctx, float min_htlep, float max_htlep) : h_htlep_(ctx.get_handle<double>("HTlep")), min_htlep_(min_htlep), max_htlep_(max_htlep) {} 

bool HTlepCut::passes(const Event & event)
{
    if (event.is_valid(h_htlep_))
    {
        double htlep = event.get(h_htlep_);
        return htlep > min_htlep_ && (max_htlep_ < 0 || htlep < max_htlep_);
    }

    return false;

}

////////////////////////////////////////////////////////

HypothesisDiscriminatorCut::HypothesisDiscriminatorCut(uhh2::Context & ctx, double min_discr, double max_discr, const std::string & discriminator_name, const std::string & hyps_name):
m_min_discr_(min_discr), m_max_discr_(max_discr), m_discriminator_name(discriminator_name), h_hyps(ctx.get_handle<std::vector<ReconstructionHypothesis>>(hyps_name)) {}
bool HypothesisDiscriminatorCut::passes(const Event & event)
{
  std::vector<ReconstructionHypothesis> hyps = event.get(h_hyps);
  const ReconstructionHypothesis* hyp = get_best_hypothesis( hyps, m_discriminator_name);

  if(!hyp) {
        // std::cout << "WARNING: no hypothesis " << m_discr->GetLabel() << " found, event is rejected." <<std::endl;
        return false;
  }

  double discr_value = hyp->discriminator(m_discriminator_name);
  if(discr_value < m_min_discr_ || discr_value > m_max_discr_) return false;
  return true;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////



METCut::METCut(double min_met_, double max_met_): min_met(min_met_), max_met(max_met_){}
bool METCut::passes(const Event & event){
  double MET = event.met->pt();
  if (MET < min_met) return false;
  if (MET > max_met) return false;
  return MET;
}

NJetCut::NJetCut(int nmin_, int nmax_, double ptmin_, double etamax_): nmin(nmin_), nmax(nmax_), ptmin(ptmin_), etamax(etamax_){}
bool NJetCut::passes(const Event & event){
  int nparticle=0;
  for(auto & jet : *event.jets) {
    if (jet.pt() > ptmin && fabs(jet.eta()<etamax)) nparticle++;
  }
  return nparticle >= nmin;
}


bool TwoDCut::passes(const Event & event){
    //make sure that you have cleaned the electron and muon collections: event should content only one charged lepton
    //clean jets for pt>25 GeV before calling this routine    
    for(auto & ele : *event.electrons) {
        double drmin, ptrel;
        tie(drmin, ptrel) = drmin_pTrel(ele, *event.jets);
        if (ptrel < 25) return false;
        if (drmin < 0.5) return false;
    }
    return true;
}


CMSTopTagOverlapSelection::CMSTopTagOverlapSelection(double delR_Lep_TopTag_, double delR_Jet_TopTag_): delR_Lep_TopTag(delR_Lep_TopTag_), delR_Jet_TopTag(delR_Jet_TopTag_){
topjetid = CMSTopTag();
ntopjet_sel.reset(new NTopJetSelection(1,-1,topjetid));

}
bool CMSTopTagOverlapSelection::passes(const Event & event)
{    
    bool ntopjet_selection = ntopjet_sel->passes(event);
if(event.electrons->size() > 0){
    const auto & ele = (*event.electrons)[0];
    for(auto & topjet : * event.topjets){
        if(ntopjet_selection && delR_Lep_TopTag < deltaR(ele,topjet)){
            for(auto & jet : * event.jets){
                if (deltaR(jet,topjet) > delR_Jet_TopTag) return true;
            }
        }
    }
}
if(event.muons->size() > 0){
    const auto & mu = (*event.muons)[0];
    for(auto & topjet : * event.topjets){
        if(ntopjet_selection && delR_Lep_TopTag < deltaR(mu,topjet)){
            for(auto & jet : * event.jets){
                if (deltaR(jet,topjet) > delR_Jet_TopTag) return true;
            }
        }
    }
}
return false;
}















