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

BlindDataSelection::BlindDataSelection(Context& ctx, float mtt_max) : mtt_max_(mtt_max){
  h_BestZprimeCandidate_chi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  string dataset_type = ctx.get("dataset_type");
  isMC = dataset_type == "MC";
}
bool BlindDataSelection::passes(const Event & event){

  if(isMC) return true;
  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
  if(!is_zprime_reconstructed_chi2) throw runtime_error("In ZprimeSemiLeptonicSelections.cxx:BlindDataSelection::passes(): The Zprime was never reconstructed via the chi2 method. This must be done before looking for the way it was reconstructed.");

  ZprimeCandidate* cand = event.get(h_BestZprimeCandidate_chi2);
  return cand->Zprime_v4().M() <= mtt_max_;
}

ZprimeTopTagSelection::ZprimeTopTagSelection(Context& ctx){
  h_BestZprimeCandidate_chi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
}
bool ZprimeTopTagSelection::passes(const Event & event){

  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
  if(!is_zprime_reconstructed_chi2) return false;
  //if(!is_zprime_reconstructed_chi2) throw runtime_error("In ZprimeSemiLeptonicSelections.cxx:ZprimeTopTagSelection::passes(): The Zprime was never reconstructed via the chi2 method. This must be done before looking for the way it was reconstructed.");

  ZprimeCandidate* cand = event.get(h_BestZprimeCandidate_chi2);

  return cand->is_toptag_reconstruction();

}

// ZprimeBTagFatSubJetSelection::ZprimeBTagFatSubJetSelection(Context& ctx){
//
//   DeepJetBTag::wp btag_wp = DeepJetBTag::WP_TIGHT; // b-tag workingpoint
//   JetId id_btag = DeepJetBTag(btag_wp);
//
//   sel_1btag.reset(new NJetSelection(1, 1, id_btag));
//   //  cout<<" init ZprimeBTagFatSubJetSelection"<<endl;
// }
// bool ZprimeBTagFatSubJetSelection::passes(const Event & event){
//   int btag_subjet=0;
//   for(auto & topjet : *event.topjets){
//     auto subjets = topjet.subjets();
//     for (auto & subjet : subjets) {
//       if(sel_1btag->passes(event)) btag_subjet++;
//     }
//   }
//   //  cout<<"btag_subjet = "<<btag_subjet<<endl;
//   if(btag_subjet>0)  return true;
//   return false;
// }

TopTag_VetoSelection::TopTag_VetoSelection(Context& ctx, TString mode) : mode_(mode){

  if(mode_ == "deepAK8"){
  h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("DeepAK8TopTags");
  }else if(mode_ == "hotvr"){
  h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("HOTVRTopTags");
  }
}

bool TopTag_VetoSelection::passes(const Event & event){

    vector<TopJet> TopTags = event.get(h_AK8TopTags);

    if(TopTags.size() <= 1) return true;
    return false;
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

TTbarSemiLepMatchableSelection::TTbarSemiLepMatchableSelection(){
  Wlep = GenParticle(); Whad = GenParticle();
  blep =  GenParticle(); bhad = GenParticle();
  thad =  GenParticle(); tlep =  GenParticle();
  lepton =  GenParticle(); neutrino =  GenParticle();
  Whadd1 =  GenParticle(); Whadd2 =  GenParticle();
}
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

      //To identify decay type, check ID of W daughters
      auto Wd1 = W->daughter(event.genparticles,1);
      auto Wd2 = W->daughter(event.genparticles,2);
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

      //hadronic
      if(fabs(Wd1->pdgId()) < 7 && fabs(Wd2->pdgId()) < 7){
        if(found_had) return false;
        found_had = true;
        Whad = *W;
        bhad = *b;
        thad = gp;
        Whadd1 = *Wd1;
        Whadd2 = *Wd2;
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

              // check if end of particle list is reached
              if(abs(idx+1) == event.genparticles->size()){
                // cout << "reached end of particle list" << endl;
               break;
              }

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
        Wlep = *W;
        blep = *b;
        tlep = gp;
        lepton = *lep;
        neutrino = *nu;

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

std::pair<bool,double> TTbarSemiLepMatchableSelection::check_reco(const ReconstructionHypothesis hyp){

  //Following check with matching to GEN particles as described in AN2015-107 (Z' with 2015 data)
  //Hadronic top
  bool tophad_match = false;
  double dR_Wd1_min = 1e6;
  double dR_Wd2_min = 1e6;
  double dR_bhad_min = 1e6;
  if(!hyp.tophad_topjet_ptr()){//hadronic top reconstructed as set of AK4 jets
    //    cout<<"Check AK4 jets for hadronic top"<<endl;
    for (uint i = 0; i < hyp.tophad_jets().size(); i++){
      double dR_Wd1 = deltaR(hyp.tophad_jets().at(i).v4(), Whadd1.v4());
      double dR_Wd2 = deltaR(hyp.tophad_jets().at(i).v4(), Whadd2.v4());
      double dR_bhad = deltaR(hyp.tophad_jets().at(i).v4(), bhad.v4());
      if(dR_Wd1_min>dR_Wd1) dR_Wd1_min = dR_Wd1;
      if(dR_Wd2_min>dR_Wd2) dR_Wd2_min = dR_Wd2;
      if(dR_bhad_min>dR_bhad) dR_bhad_min = dR_bhad;
    }
    if(dR_Wd1_min<0.4 && dR_Wd2_min<0.4 && dR_bhad_min<0.4) tophad_match = true;
  }
  else{//hadronic top reconstructed as AK8 jet
    dR_Wd1_min = deltaR(hyp.tophad_topjet_ptr()->v4(), Whadd1.v4());
    dR_Wd2_min = deltaR(hyp.tophad_topjet_ptr()->v4(), Whadd2.v4());
    dR_bhad_min = deltaR(hyp.tophad_topjet_ptr()->v4(), bhad.v4());
    if(dR_Wd1_min<0.8 && dR_Wd2_min<0.8 && dR_bhad_min<0.8) tophad_match = true;
  }

  //Leptonic top
  bool toplep_match = false;
  double dR_lep = deltaR(lepton.v4(),hyp.lepton().v4());
  // double dR_neutrino = deltaR(neutrino.v4(),hyp.neutrino_v4());
  double dPhi_neutrino = deltaPhi(neutrino.v4(),hyp.neutrino_v4());
  double dR_blep_min = 1e6;
  for (uint i = 0; i < hyp.toplep_jets().size(); i++){
    double dR_blep = deltaR(hyp.toplep_jets().at(i).v4(), blep.v4());
    if(dR_blep_min>dR_blep) dR_blep_min=dR_blep;
  }

  if(dR_blep_min<0.4 && dR_lep<0.1 && dPhi_neutrino<0.3) toplep_match = true;

  // double deltaM_lep = fabs(hyp.toplep_v4().M()-tlep.v4().M())/tlep.v4().M();
  // double deltaM_had = fabs(hyp.tophad_v4().M()-thad.v4().M())/thad.v4().M();
  // cout<<"GEN: tlep.v4().M() = "<<tlep.v4().M()<<" thad.v4().M() = "<<thad.v4().M()<<endl;
  // cout<<"RECO: hyp.toplep_v4().M() = "<<hyp.toplep_v4().M()<<" hyp.tophad_v4().M() = "<<hyp.tophad_v4().M()<<endl;
  // cout<<"DELTA: "<<deltaM_lep<<" "<<deltaM_had<<endl;
  // cout<<" toplep_match, tophad_match :"<<toplep_match<<", "<<tophad_match<<endl;
  // cout<<" dR_neutrino = "<<dR_neutrino<<" dPhi_neutrino = "<<dPhi_neutrino<<" dRlep = "<<dR_lep<<" dR_blep_min = "<<dR_blep_min<<endl;
  // cout<<" dR_Wd1 = "<<dR_Wd1_min<<" dR_Wd2 = "<<dR_Wd2_min<<" dR_bhad = "<<dR_bhad_min<<endl;
  // vector<double> dR;//dRWd1had,dRWd2had,dRbhad,dRlep,dPhineutrino,dRblep
  // dR.push_back(dR_Wd1_min);
  // dR.push_back(dR_Wd2_min);
  // dR.push_back(dR_bhad_min);
  // dR.push_back(dR_lep);
  // dR.push_back(dPhi_neutrino);
  // dR.push_back(dRblep);

  double dR_sum = dR_Wd1_min; dR_sum+=dR_Wd2_min;  dR_sum+=dR_bhad_min; dR_sum+=dR_lep; dR_sum+=dPhi_neutrino; dR_sum+=dR_blep_min;
  pair<bool,double> result;
  result.second = dR_sum;
  if(!toplep_match || !tophad_match){
    result.first = false;
  }
  else{
    result.first = true;
  }
  //  cout<<"### WE FOUND MATCH! ###"<<endl;
  //  return true;
  return result;
  // double dR_top_lep_reco_gen = deltaR( tlep.v4(), hyp.toplep_v4());
  // double dR_top_had_reco_gen = deltaR( thad.v4(), hyp.tophad_v4());
  // //  double dR_lep_reco_gen = deltaR(lepton.v4(),hyp.lepton().v4());
  // //  cout<<"Hi from TTbarSemiLepMatchableSelection::check_reco!"<<endl;
  // //  cout<<"dR_top_lep_reco_gen ="<<dR_top_lep_reco_gen<<" dR_top_had_reco_gen = "<<dR_top_had_reco_gen<<endl;
  // //  cout<<" dR_lep_reco_gen = "<<dR_lep_reco_gen<<endl;
  // if(dR_top_lep_reco_gen>0.4 || dR_top_had_reco_gen>0.4) return false;


  // if(deltaM_lep>1 || deltaM_had>1) return false;
  // return true;
}

////////////////////////////////////////////////////////////////

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
    if(chi2 >= min_ && (chi2 < max_ || max_ < 0)) pass = true;
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

uhh2::HTlepCut::HTlepCut(float min_htlep, float max_htlep):
  min_htlep_(min_htlep), max_htlep_(max_htlep) {}


bool uhh2::HTlepCut::passes(const uhh2::Event& event){
  float lep_pt = 0;
  if(event.muons) lep_pt = event.muons->at(0).pt(); //FixMe: find leading lepton first
  float htlep =  event.met->pt() + lep_pt;

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

// bool uhh2::TwoDCut1::passes(const uhh2::Event& event){
//
//   // assert((event.muons || event.electrons) && event.jets);
//   assert(event.muons || event.electrons);
//
//   const Particle* lepton = leading_lepton(event);
//
//   float drmin, ptrel;
//   bool pass = false;
//   // std::tie(drmin, ptrel) = drmin_pTrel(*lepton, *event.jets);
//   if(event.muons){
//     drmin = lepton->get_tag(Muon::twodcut_dRmin);
//     ptrel = lepton->get_tag(Muon::twodcut_pTrel);
//     if((drmin > min_deltaR_) || (ptrel > min_pTrel_)) pass = true;
//   }
//   if(event.electrons){
//     drmin = lepton->get_tag(Electron::twodcut_dRmin);
//     ptrel = lepton->get_tag(Electron::twodcut_pTrel);
//     if((drmin > min_deltaR_) || (ptrel > min_pTrel_)) pass = true;
//   }
//
//   // return (drmin > min_deltaR_) || (ptrel > min_pTrel_);
//   return pass;
// }
////////////////////////////////////////////////////////

bool uhh2::TwoDCut::passes(const uhh2::Event& event){

  assert(event.muons || event.electrons);
  //if((event.muons->size()+event.electrons->size()) != 1) throw runtime_error("In TwoDCut: Event does not have exactly one muon and electron.");

  bool pass = false;
  if(event.muons->size()){
    float drmin, ptrel;
    drmin = event.muons->at(0).get_tag(Muon::twodcut_dRmin);
    ptrel = event.muons->at(0).get_tag(Muon::twodcut_pTrel);
    if((drmin > min_deltaR_) || (ptrel > min_pTrel_)) pass = true;
  }
  if(event.electrons->size()){
    float drmin, ptrel;
    drmin = event.electrons->at(0).get_tag(Electron::twodcut_dRmin);
    ptrel = event.electrons->at(0).get_tag(Electron::twodcut_pTrel);
    if((drmin > min_deltaR_) || (ptrel > min_pTrel_)) pass = true;
  }

  return pass;
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

HEMSelection::HEMSelection(Context& ctx){
year = extract_year(ctx);
}
bool HEMSelection::passes(const Event & event){

if(year != Year::isUL18) return true;
if( (event.isRealData && event.run >= min_runnum) || (!event.isRealData) ){

   for(const Electron & ele : *event.electrons){
      if ( ele.eta() < eta_up && ele.eta() > eta_down && ele.phi() < phi_up && ele.phi() > phi_down) return false;
   }

   for(const Muon & muo : *event.muons){
      if ( muo.eta() < eta_up && muo.eta() > eta_down && muo.phi() < phi_up && muo.phi() > phi_down) return false;
   }

   for(const auto & jet : *event.jets){
      if ( jet.eta() < eta_up && jet.eta() > eta_down && jet.phi() < phi_up && jet.phi() > phi_down) return false;
   }

   for(const auto & topjet : *event.topjets){
      if ( topjet.eta() < eta_up && topjet.eta() > eta_down && topjet.phi() < phi_up && topjet.phi() > phi_down) return false;
   }

   for(const auto & toppuppijet : *event.toppuppijets){
      if ( toppuppijet.eta() < eta_up && toppuppijet.eta() > eta_down && toppuppijet.phi() < phi_up && toppuppijet.phi() > phi_down) return false;
   }
}
return true;
}

/////////////////////////////////////////////////////

ThetaStarSelection::ThetaStarSelection(Context& ctx, float theta_cut) : theta_cut_(theta_cut){
  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
}
bool ThetaStarSelection::passes(const Event & event){

 bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
 ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);

 if(!is_zprime_reconstructed_chi2) return false;

 bool pass = false;

 float ang_leptop_thetastar;
 float cos_ang_leptop_thetastar;

 LorentzVector had_top = BestZprimeCandidate->top_hadronic_v4();
 LorentzVector lep_top = BestZprimeCandidate->top_leptonic_v4();

 TLorentzVector lep_top_frame(0,0,0,0);
 lep_top_frame.SetPtEtaPhiE(lep_top.pt(), lep_top.eta(), lep_top.phi(), lep_top.E());
 TLorentzVector ttbar(0,0,0,0);
 ttbar.SetPtEtaPhiE((had_top+lep_top).pt(), (had_top+lep_top).eta(), (had_top+lep_top).phi(), (had_top+lep_top).E());

 lep_top_frame.Boost(-ttbar.BoostVector());

 ang_leptop_thetastar = lep_top_frame.Theta();
 cos_ang_leptop_thetastar = TMath::Cos(ang_leptop_thetastar);

 if( (cos_ang_leptop_thetastar > -theta_cut_) && (cos_ang_leptop_thetastar < theta_cut_) ) pass = true;

return pass;

}

/////////////////////////////////////////////////////


PuppiCHS_BTagging::PuppiCHS_BTagging(Context& ctx){

  h_CHSjets_matched = ctx.get_handle<std::vector<Jet>>("CHS_matched");

  BTag::algo btag_algo = BTag::DEEPJET;
  BTag::wp btag_wp = BTag::WP_MEDIUM;
  JetId id_btag = BTag(btag_algo, btag_wp);

  sel_1btag.reset(new NJetSelection(1, -1, id_btag));
}
bool PuppiCHS_BTagging::passes(const Event & event){

  vector<Jet> CHSjets = event.get(h_CHSjets_matched);

  bool btagged = false;
  for(const Jet & jet : *event.jets){
     double deltaR_min = 99;
     for(const Jet & CHSjet : CHSjets){
        double deltaR_CHS = deltaR(jet,CHSjet);
        if(deltaR_CHS<deltaR_min) deltaR_min = deltaR_CHS;
     }
     if(deltaR_min>0.2) continue;
     for(const Jet & CHSjet : CHSjets){
     if(deltaR(jet,CHSjet)!=deltaR_min) continue;
     else{
        if(sel_1btag->passes(event)) {
        btagged = true;
        }
     }
     }
  }
  if(!(btagged)) return false;


return true;
}
