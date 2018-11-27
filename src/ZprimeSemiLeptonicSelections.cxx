#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/utils.h>

#include <iostream>
#include <fstream>
#include <cstdlib>
#include <memory>

#include <UHH2/core/include/LorentzVector.h>

#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/Utils.h>

using namespace std;


ZprimeTopTagSelection::ZprimeTopTagSelection(Context& ctx){
  h_BestZprimeCandidate_chi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
}
bool ZprimeTopTagSelection::passes(const Event & event){

  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
  if(!is_zprime_reconstructed_chi2) throw runtime_error("In ZprimeSemiLeptonicSelections.cxx:ZprimeTopTagSelection::passes(): The Zprime was never reconstructed via the chi2 method. This must be done before looking for the way it was reconstructed.");

  ZprimeCandidate* cand = event.get(h_BestZprimeCandidate_chi2);

  return cand->is_toptag_reconstruction();

}

Chi2CandidateMatchedSelection::Chi2CandidateMatchedSelection(Context& ctx){
  h_BestZprimeCandidate_chi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  h_is_zprime_reconstructed_correctmatch = ctx.get_handle<bool>("is_zprime_reconstructed_correctmatch");
}
bool Chi2CandidateMatchedSelection::passes(const Event & event){

  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
  bool is_zprime_reconstructed_correctmatch = event.get(h_is_zprime_reconstructed_correctmatch);

  if(!(is_zprime_reconstructed_chi2 && is_zprime_reconstructed_correctmatch)) return false;
  ZprimeCandidate* cand_chi2 = event.get(h_BestZprimeCandidate_chi2);
  float dr_chi2 = cand_chi2->discriminator("correct_match");
  return dr_chi2 < 10.;

}

TTbarSemiLepMatchableSelection::TTbarSemiLepMatchableSelection(){}
bool TTbarSemiLepMatchableSelection::passes(const Event & event){
  if(event.isRealData) return false;
  assert(event.genparticles);

  //check, if one top decays had and one decays lep
  bool found_had = false, found_lep = false;

  //Loop over genparticles
  for(const auto & gp : *event.genparticles){

    //Get tops
    if(fabs(gp.pdgId()) == 6){

      //Get b and W
      auto b = gp.daughter(event.genparticles,1);
      auto W = gp.daughter(event.genparticles,2);
      if(fabs(W->pdgId()) == 5 && fabs(b->pdgId()) == 24){
        b = gp.daughter(event.genparticles,2);
        W = gp.daughter(event.genparticles,1);
      }
      if(abs(W->pdgId()) != 24) {
        for(unsigned int j = 0; j < event.genparticles->size(); ++j) {
          const GenParticle & genp = event.genparticles->at(j);
          auto m1 = genp.mother(event.genparticles, 1);
          auto m2 = genp.mother(event.genparticles, 2);
          bool has_top_mother = ((m1 && m1->index() == gp.index()) || (m2 && m2->index() == gp.index()));
          if(has_top_mother && (abs(genp.pdgId()) == 24)) {
            W = &genp;
            break;
          }
        }
      }
      if(abs(b->pdgId()) != 5 && abs(b->pdgId()) != 3 && abs(b->pdgId()) != 1) {
        for(unsigned int j = 0; j < event.genparticles->size(); ++j) {
          const GenParticle & genp = event.genparticles->at(j);
          auto m1 = genp.mother(event.genparticles, 1);
          auto m2 = genp.mother(event.genparticles, 2);
          bool has_top_mother = ((m1 && m1->index() == gp.index()) || (m2 && m2->index() == gp.index()));
          if(has_top_mother && (abs(genp.pdgId()) == 5 || abs(genp.pdgId()) == 3 || abs(genp.pdgId()) == 1)) {
            b = &genp;
            break;
          }
        }
      }
      if(!((fabs(b->pdgId()) == 5 || fabs(b->pdgId()) == 3 || fabs(b->pdgId()) == 1) && fabs(W->pdgId()) == 24)) return false;

      //try to match the b quarks
      bool matched_b_ak4 = false;

      // Consider AK4 jets first
      for(const auto & jet : *event.jets){
        if(deltaR(*b,jet) <= 0.4) matched_b_ak4 = true;
      }

      bool matched_b_ak8 = false;
      // Now consider AK8 jets
      int idx_matched_topjet = -1;
      int idx = 0;
      for(const auto & jet : *event.topjets){
        if(deltaR(*b,jet) <= 0.8){
          matched_b_ak8 = true;
          idx_matched_topjet = idx;
        }
        idx++;
      }

      if(!matched_b_ak4 && !matched_b_ak8) return false;

      //Check decaymodes of W
      auto Wd1 = W->daughter(event.genparticles,1);
      auto Wd2 = W->daughter(event.genparticles,2);

      //hadronic
      if(fabs(Wd1->pdgId()) < 7 && fabs(Wd2->pdgId()) < 7){
        if(found_had) return false;
        found_had = true;

        //check if both daughters can be matched by jets
        bool matched_d1_ak4 = false, matched_d2_ak4 = false;
        bool matched_d1_ak8 = false, matched_d2_ak8 = false;
        // Consider AK4 jets first
        for(const auto & jet : *event.jets){
          if(deltaR(*Wd1, jet) <= 0.4) matched_d1_ak4 = true;
          if(deltaR(*Wd2, jet) <= 0.4) matched_d2_ak4 = true;
        }

        // Now consider the one AK8 jet also used for the b-jet
        if(!matched_b_ak8){
          matched_d1_ak8 = false;
          matched_d2_ak8 = false;
        }
        else{
          if(deltaR(*Wd1, event.topjets->at(idx_matched_topjet)) <= 0.8) matched_d1_ak8 = true;
          if(deltaR(*Wd2, event.topjets->at(idx_matched_topjet)) <= 0.8) matched_d2_ak8 = true;
        }

        // if(!(matched_d1 && matched_d2)) return false;
        if(!(matched_b_ak4 && matched_d1_ak4 && matched_d2_ak4) && !(matched_b_ak8 && matched_d1_ak8 && matched_d2_ak8)) return false;
      }

      //leptonic
      else if((abs(Wd1->pdgId()) == 11 || abs(Wd1->pdgId()) == 13) || (abs(Wd2->pdgId()) == 11 || abs(Wd2->pdgId()) == 13)){
        if(found_lep) return false;

        // Escape cases where the W radiates an intermediate photon, that splits into llbar
        if(Wd1->pdgId() == -Wd2->pdgId()){
          // cout << "Entered the escape-part" << endl;
          // Find 2 genparts with 11,12,13,14 that follow each other in the list and don't have the same fabs
          int idx = 0;
          for(const auto & genp : *event.genparticles){
            if(found_lep) break;
            if(abs(genp.pdgId()) >= 11 && abs(genp.pdgId()) <= 14){
              bool is_charged = (abs(genp.pdgId()) == 11 || abs(genp.pdgId()) == 13);
              // cout << "Found a genpart at index " << idx << " with id " << genp.pdgId() << ", is_charged: " << is_charged << endl;

              // if the first one is charged, the second one has to have pdgId of +1 wrt. this genpart
              if(is_charged){
                // cout << "(charged) Going to check for next particle in list" << endl;
                if(abs(event.genparticles->at(idx+1).pdgId()) == abs(genp.pdgId()) + 1){
                  Wd1 = &genp;
                  Wd2 = &event.genparticles->at(idx+1);
                  found_lep = true;
                }
              }
              else{
                // cout << "(neutral) Going to check for next particle in list" << endl;
                if(abs(event.genparticles->at(idx+1).pdgId()) == abs(genp.pdgId()) - 1){
                  Wd2 = &genp;
                  Wd1 = &event.genparticles->at(idx+1);
                  found_lep = true;
                }
              }
            }
            idx++;
          }
          if(!found_lep) return false;
        }

        found_lep = true;

        //Find charged lepton
        auto lep = Wd1;
        auto nu = Wd2;
        if(fabs(Wd2->pdgId()) == 11 || fabs(Wd2->pdgId()) == 13){
          lep = Wd2;
          nu = Wd1;
        }
        if(!(abs(lep->pdgId()) == 11 && abs(nu->pdgId()) == 12) && !(abs(lep->pdgId()) == 13 && abs(nu->pdgId()) == 14)) throw runtime_error("In TTbarSemiLepMatchable: The leptonic W does not decay into a lepton and its neutrino.");

        //check, if lepton can be matched
        bool matched_lep = false;
        if(fabs(lep->pdgId()) == 11){
          for(const auto & ele : *event.electrons){
            if(deltaR(*lep,ele) <= 0.1) matched_lep = true;
          }
        }
        else if(fabs(lep->pdgId()) == 13){
          for(const auto & mu : *event.muons){
            if(deltaR(mu,*lep) <= 0.1) matched_lep = true;
          }
        }
        else throw runtime_error("In TTbarSemiLepMatchable: Lepton from W decay is neither e nor mu.");
        if(!matched_lep) return false;
      }
      //tau-decays
      else return false;
    }
  }

  if(!(found_had && found_lep)) return false;

  return true;
}

uhh2::Chi2Cut::Chi2Cut(Context& ctx, float min, float max): min_(min), max_(max){
  h_BestZprimeCandidate = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
}

bool uhh2::Chi2Cut::passes(const uhh2::Event& event){

  bool is_zprime_reconstructed = event.get(h_is_zprime_reconstructed);
  // if(!is_zprime_reconstructed) throw runtime_error("In ZprimeSemiLeptonicSelections.cxx: Chi2Cut::passes: The Zprime was never reconstructed. Do this before trying to cut on its chi2.");
  bool pass = false;
  if(is_zprime_reconstructed){
    ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidate);
    double chi2 = BestZprimeCandidate->discriminator("chi2_total");
    if(chi2 >= min_ && (chi2 <= max_ || max_ < 0)) pass = true;
  }

  return pass;
}

uhh2::STlepPlusMetCut::STlepPlusMetCut(float min, float max):
min_(min), max_(max) {}

bool uhh2::STlepPlusMetCut::passes(const uhh2::Event& event){

  float stlep = STlep(event);
  float met = event.met->pt();
  float sum = stlep + met;

  return (sum > min_) && (sum < max_ || max_ < 0.);
}
////////////////////////////////////////////////////////

uhh2::METCut::METCut(float min_met, float max_met):
min_met_(min_met), max_met_(max_met) {}

bool uhh2::METCut::passes(const uhh2::Event& event){

  assert(event.met);

  float MET = event.met->pt();
  return (MET > min_met_) && (MET < max_met_);
}

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
    // cout << "TTbar: TopJet has been tagged" << endl;
    float max_dr = 0.;
    for(const auto& jet : *event.jets){
      if(deltaR(jet, topjet) > minDR_jet_toptag_){
        return true;
      }
      if(deltaR(jet, topjet) > max_dr) max_dr = deltaR(jet, topjet);
    }
    // cout << "TTbar: Apparently there is no AK4 jet well-separated from this top jet. Maximum dR = " << max_dr << endl;
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
