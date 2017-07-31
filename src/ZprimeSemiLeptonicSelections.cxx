#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/utils.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>

#include <UHH2/core/include/LorentzVector.h>

#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/Utils.h>

uhh2::HTlepCut::HTlepCut(float min_htlep, float max_htlep):
  min_htlep_(min_htlep), max_htlep_(max_htlep) {}

bool uhh2::HTlepCut::passes(const uhh2::Event& event){

  float htlep = HTlep1(event);

  return (htlep > min_htlep_) && (htlep < max_htlep_);
}
////////////////////////////////////////////////////////

uhh2::METCut::METCut(float min_met, float max_met):
  min_met_(min_met), max_met_(max_met) {}

bool uhh2::METCut::passes(const uhh2::Event& event){

  assert(event.met);

  float MET = event.met->pt();
  return (MET > min_met_) && (MET < max_met_);
}
////////////////////////////////////////////////////////

//!! uhh2::TTbarNJetSelection::TTbarNJetSelection(const float jet1_pt, const float jet2_pt, const float tjet1_pt):
//!!   jet1_pt_(jet1_pt), jet2_pt_(jet2_pt), tjet1_pt_(tjet1_pt) {
//!! 
//!!   h_jets_    = ctx.get_handle<std::vector<Jet>   >("jets");
//!!   h_topjets_ = ctx.get_handle<std::vector<TopJet>>("topjets");
//!! 
//!! }
//!! 
//!! bool uhh2::TTbarNJetSelection::passes(const uhh2::Event& event){
//!! 
//!!   const std::vector<Jet>&       jets = event.get(h_jets_);
//!!   const std::vector<TopJet>& topjets = event.get(h_topjets_);
//!! 
//!!   int jetN_1(0), jetN_2(0);
//!!   for(const auto& j : jets){
//!! 
//!!     if(j.pt() > jet1_pt_) ++jetN_1;
//!!     if(j.pt() > jet2_pt_) ++jetN_2;
//!!   }
//!! 
//!!   int tjetN_1(0);
//!!   for(const auto& tj : topjets){
//!! 
//!!     if(tj.pt() > tjet1_pt_) ++tjetN_1;
//!!   }
//!! 
//!!   return (njet >= nmin) && (njet <= nmax);
//!! }
//!! ////////////////////////////////////////////////////////

bool uhh2::TwoDCut1::passes(const uhh2::Event& event){

  assert(event.muons && event.electrons && event.jets);

  const Particle* lepton = leading_lepton(event);

  float drmin, ptrel;
  std::tie(drmin, ptrel) = drmin_pTrel(*lepton, *event.jets);

  return (drmin > min_deltaR_) || (ptrel > min_pTrel_);
}
////////////////////////////////////////////////////////

bool uhh2::TwoDCutALL::passes(const uhh2::Event& event){

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

bool uhh2::TwoDCut::passes(const uhh2::Event& event){

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

bool uhh2::TriangularCuts::passes(const uhh2::Event& event){

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
  bool pass_tc_lep = fabs(fabs(deltaPhi(*event.met, *lep1)) - a_) < b_ * event.met->pt();

  // MET-jet triangular cut
  bool pass_tc_jet = fabs(fabs(deltaPhi(*event.met, *jet1)) - a_) < b_ * event.met->pt();

  return pass_tc_lep && pass_tc_jet;
}
////////////////////////////////////////////////////////

bool uhh2::TriangularCutsELE::passes(const uhh2::Event& event){

  assert(event.electrons);
  assert(event.jets && event.met);

  if(event.electrons->size() != 1) std::runtime_error("TriangularCutsELE::passes -- unexpected number of electrons in the event (!=1)");
  if(event.jets     ->size() == 0) std::runtime_error("TriangularCutsELE::passes -- unexpected number of jets in the event (==0)");

  // pt-leading charged lepton
  const Particle* lep1 = &event.electrons->at(0);

  // 1st entry in jet collection (should be the pt-leading jet)
  const Particle* jet1 = &event.jets->at(0);

  // MET-lepton triangular cut
  bool pass_tc_lep = fabs(fabs(deltaPhi(*event.met, *lep1)) - a_) < b_ * event.met->pt();

  // MET-jet triangular cut
  bool pass_tc_jet = fabs(fabs(deltaPhi(*event.met, *jet1)) - a_) < b_ * event.met->pt();

  return pass_tc_lep && pass_tc_jet;
}
////////////////////////////////////////////////////////

uhh2::DiLeptonSelection::DiLeptonSelection(const std::string& channel, const bool opposite_charge, const bool veto_other_flavor):
  channel_(channel), opposite_charge_(opposite_charge), veto_other_flavor_(veto_other_flavor) {}

bool uhh2::DiLeptonSelection::passes(const uhh2::Event& event){ 

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
  else throw std::runtime_error("DiLeptonSelection::passes -- undefined key for lepton channel: "+channel_);

  return pass;
}
////////////////////////////////////////////////////////

uhh2::TopJetPlusJetEventSelection::TopJetPlusJetEventSelection(const float topjet_minDR_jet, const float jet_min_pt):
  topjet_minDR_jet_(topjet_minDR_jet), jet_min_pt_(jet_min_pt) {}

bool uhh2::TopJetPlusJetEventSelection::passes(const uhh2::Event& event){ 

  if(event.topjets->size() != 1) return false;

  for(const auto& topjet : *event.topjets){

    for(const auto& jet : *event.jets){
      if(uhh2::deltaR(topjet, jet) > topjet_minDR_jet_ && jet.pt() > jet_min_pt_) return true;
    }
  }

  return false;
}
////////////////////////////////////////////////////////

uhh2::TopTagEventSelection::TopTagEventSelection(const TopJetId& tjetID, const float minDR_jet_ttag):
  topjetID_(tjetID), minDR_jet_toptag_(minDR_jet_ttag) {

  topjet1_sel_.reset(new NTopJetSelection(1, -1, topjetID_));
}

bool uhh2::TopTagEventSelection::passes(const uhh2::Event& event){ 

  if(!topjet1_sel_->passes(event)) return false;

  for(const auto& topjet : *event.topjets){

    if(!topjetID_(topjet, event)) continue;

    for(const auto& jet : *event.jets){
      if(deltaR(jet, topjet) > minDR_jet_toptag_) return true;
    }
  }

  return false;
}
////////////////////////////////////////////////////////

uhh2::LeptonicTopPtCut::LeptonicTopPtCut(uhh2::Context& ctx, float pt_min, float pt_max, const std::string& hyps_name, const std::string& disc_name):
  tlep_pt_min_(pt_min), tlep_pt_max_(pt_max), h_hyps_(ctx.get_handle<std::vector<ReconstructionHypothesis>>(hyps_name)), disc_name_(disc_name) {}

bool uhh2::LeptonicTopPtCut::passes(const uhh2::Event& event){

  const std::vector<ReconstructionHypothesis>& hyps = event.get(h_hyps_);

  const ReconstructionHypothesis* hyp = get_best_hypothesis(hyps, disc_name_);
  if(!hyp) std::runtime_error("LeptonicTopPtCut -- best hypothesis not found (discriminator="+disc_name_+")");

  const float tlep_pt = hyp->toplep_v4().Pt();

  return (tlep_pt > tlep_pt_min_) && (tlep_pt < tlep_pt_max_);
}
////////////////////////////////////////////////////////

uhh2::HypothesisDiscriminatorCut::HypothesisDiscriminatorCut(uhh2::Context& ctx, float disc_min, float disc_max, const std::string& hyps_name, const std::string& disc_bhyp, const std::string& disc_cut):
  disc_min_(disc_min), disc_max_(disc_max), h_hyps_(ctx.get_handle<std::vector<ReconstructionHypothesis>>(hyps_name)), disc_bhyp_(disc_bhyp), disc_cut_(disc_cut) {}

bool uhh2::HypothesisDiscriminatorCut::passes(const uhh2::Event& event){

  const std::vector<ReconstructionHypothesis>& hyps = event.get(h_hyps_);

  const ReconstructionHypothesis* hyp = get_best_hypothesis(hyps, disc_bhyp_);
  if(!hyp) std::runtime_error("HypothesisDiscriminatorCut -- best hypothesis not found (discriminator="+disc_bhyp_+")");

  const float disc_val = hyp->discriminator(disc_cut_);

  return (disc_val > disc_min_) && (disc_val < disc_max_);
}
////////////////////////////////////////////////////////

uhh2::GenFlavorSelection::GenFlavorSelection(const std::string& flav_key){

  flavor_key_ = flav_key;

  if(flavor_key_ != "l" && flavor_key_ != "c" && flavor_key_ != "b")
    throw std::runtime_error("GenFlavorSelection::GenFlavorSelection -- undefined key for parton flavor (must be 'l', 'c' or 'b'): "+flavor_key_);
}

bool uhh2::GenFlavorSelection::passes(const uhh2::Event& event){ 

  bool pass(false);

  assert(event.genparticles);

  int bottomN(0), charmN(0);
  for(const auto& genp : *event.genparticles){

    if(!(20 <= genp.status() && genp.status() <= 30)) continue;
    if(genp.mother1() == (unsigned short)(-1)) continue;
    if(genp.mother2() == (unsigned short)(-1)) continue;

    const int id = genp.pdgId();

    if(std::abs(id) == 5) ++bottomN;
    if(std::abs(id) == 4) ++charmN;
  }

  if     (flavor_key_ == "b") pass = (bottomN >= 1);
  else if(flavor_key_ == "c") pass = (bottomN == 0 && charmN >= 1);
  else if(flavor_key_ == "l") pass = (bottomN == 0 && charmN == 0);
  else throw std::runtime_error("GenFlavorSelection::GenFlavorSelection -- undefined key for parton flavor (must be 'l', 'c' or 'b'): "+flavor_key_);
  //  std::cout<<"bottomN = "<<bottomN<<" charmN = "<<charmN<<std::endl;

  return pass;
}
////////////////////////////////////////////////////////

uhh2::JetFlavorSelection::JetFlavorSelection(const std::string& flav_key){

  flavor_key_ = flav_key;

  if(flavor_key_ != "l" && flavor_key_ != "c" && flavor_key_ != "b")
    throw std::runtime_error("JetFlavorSelection::JetFlavorSelection -- undefined key for jet flavor (must be 'l', 'c' or 'b'): "+flavor_key_);
}

bool uhh2::JetFlavorSelection::passes(const uhh2::Event& event){ 

  bool pass(false);

  assert(event.jets);

  int bottomN(0), charmN(0);
  for(const auto& j : *event.jets){

    const int id = j.hadronFlavor();

    if(std::abs(id) == 5) ++bottomN;
    if(std::abs(id) == 4) ++charmN;
  }

  if     (flavor_key_ == "b") pass = (bottomN >= 1);
  else if(flavor_key_ == "c") pass = (bottomN == 0 && charmN >= 1);
  else if(flavor_key_ == "l") pass = (bottomN == 0 && charmN == 0);
  else throw std::runtime_error("JetFlavorSelection::JetFlavorSelection -- undefined key for jet flavor (must be 'l', 'c' or 'b'): "+flavor_key_);

  return pass;
}
////////////////////////////////////////////////////////

uhh2::GenHTCut::GenHTCut(uhh2::Context& ctx, const float min, const float max, const std::string& meps_name):
  genHT_min_(min), genHT_max_(max), h_meps_(ctx.get_handle<std::vector<GenParticle> >(meps_name)) {}

bool uhh2::GenHTCut::passes(const uhh2::Event& event){

  const std::vector<GenParticle>& me_partons = event.get(h_meps_);

  float genHT(0.);
  for(const auto& p : me_partons) genHT += p.pt();

  return (genHT_min_ <= genHT) && (genHT < genHT_max_);
}
////////////////////////////////////////////////////////

uhh2::RunLumiEventSelection::RunLumiEventSelection(const std::string& input_file, const std::string& separator){

  std::ifstream ifstr;
  ifstr.open(input_file.c_str());
  if(!ifstr.fail()){

    std::string line;
    while(std::getline(ifstr, line)){

      const std::vector<std::string> line_tags(util::string_tokens(line, separator));
      if(line_tags.size() != 3) std::runtime_error("RunLumiEventSelection::RunLumiEventSelection -- unexpected number of tags (separator="+separator+"): "+line);

      const unsigned long int run = atoi(line_tags.at(0).c_str());
      const unsigned long int lum = atoi(line_tags.at(1).c_str());
      const unsigned long int evt = atoi(line_tags.at(2).c_str());

      rle_map_[run][lum].push_back(evt);
    }
  }
  else throw std::runtime_error("RunLumiEventSelection::RunLumiEventSelection -- failed reading input file: "+input_file);

  ifstr.close();
}

bool uhh2::RunLumiEventSelection::found(const uhh2::Event& event){

  bool is_found(false);

  const unsigned long int RUN = ((unsigned int) event.run);
  const unsigned long int LUM = ((unsigned int) event.luminosityBlock);
  const unsigned long int EVT = ((unsigned int) event.event);

  for(const auto& r : rle_map_){
    if(is_found) break;

    if(r.first == RUN){

      for(const auto& l : r.second){
	if(is_found) break;

        if(l.first == LUM){

          for(const auto& e : l.second){
            if(is_found) break;

            if(e == EVT) is_found = true;
          }
        }
      }
    }
  }

  return is_found;
}

bool uhh2::RunLumiEventSelection::passes(const uhh2::Event& event){

  return found(event);
}
////////////////////////////////////////////////////////
