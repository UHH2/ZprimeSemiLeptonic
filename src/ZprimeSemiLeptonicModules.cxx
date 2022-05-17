#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/core/include/LorentzVector.h>
#include <UHH2/core/include/Utils.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>
#include "UHH2/core/include/Event.h"
#include <UHH2/common/include/NSelections.h>
#include "UHH2/common/include/BTagCalibrationStandalone.h"
#include "UHH2/common/include/MCWeight.h"

#include "boost/algorithm/string.hpp"

#include "Riostream.h"
#include "TFile.h"
#include "TH1F.h"

using namespace std;
using namespace uhh2;




float inv_mass(const LorentzVector& p4){ return p4.isTimelike() ? p4.mass() : -sqrt(-p4.mass2()); }

FlavorParticle find_primary_lepton(uhh2::Event & event) {
  assert(event.muons || event.electrons);
  FlavorParticle primlep;
  float ptmax = 0.;
  if(event.electrons) {
    for(const auto & ele : *event.electrons) {
      if(ele.pt() > ptmax) {
        ptmax = ele.pt();
        primlep = ele;
      }
    }
  }
  if(event.muons) {
    for(const auto & mu : *event.muons) {
      if(mu.pt() > ptmax) {
        ptmax = mu.pt();
        primlep = mu;
      }
    }
  }
  return primlep;
}

vector<LorentzVector> reconstruct_neutrino(const LorentzVector & lepton, const LorentzVector & met) {
  TVector3 lepton_pT = toVector(lepton);
  lepton_pT.SetZ(0);
  TVector3 neutrino_pT = toVector(met);
  neutrino_pT.SetZ(0);
  constexpr float mass_w = 80.399f;
  float mu = mass_w * mass_w / 2 + lepton_pT * neutrino_pT;
  float A = - (lepton_pT * lepton_pT);
  float B = mu * lepton.pz();
  float C = mu * mu - lepton.e() * lepton.e() * (neutrino_pT * neutrino_pT);
  float discriminant = B * B - A * C;
  std::vector<LorentzVector> solutions;
  if (0 >= discriminant) {
    // Take only real part of the solution for pz:
    LorentzVectorXYZE solution (met.Px(),met.Py(),-B / A,0);
    solution.SetE(solution.P());
    solutions.emplace_back(toPtEtaPhi(solution));
  }
  else {
    discriminant = sqrt(discriminant);
    LorentzVectorXYZE solution (met.Px(),met.Py(),(-B - discriminant) / A,0);
    solution.SetE(solution.P());
    solutions.emplace_back(toPtEtaPhi(solution));

    LorentzVectorXYZE solution2 (met.Px(),met.Py(),(-B + discriminant) / A,0);
    solution2.SetE(solution2.P());
    solutions.emplace_back(toPtEtaPhi(solution2));
  }
  return solutions;
}


ZprimeCandidateBuilder::ZprimeCandidateBuilder(uhh2::Context& ctx, TString mode, float minDR) : minDR_(minDR), mode_(mode){

  h_ZprimeCandidates_ = ctx.get_handle< vector<ZprimeCandidate> >("ZprimeCandidates");

  if(mode_ == "deepAK8"){
  h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("DeepAK8TopTags");
  h_AK8TopTagsPtr = ctx.get_handle<std::vector<const TopJet*>>("DeepAK8TopTagsPtr");
  }else if(mode_ == "hotvr"){
  h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("HOTVRTopTags");
  h_AK8TopTagsPtr = ctx.get_handle<std::vector<const TopJet*>>("HOTVRTopTagsPtr");
  }

  if(mode_ != "hotvr" && mode_ != "deepAK8") throw runtime_error("In ZprimeCandidateBuilder::ZprimeCandidateBuilder(): 'mode' must be 'hotvr' or 'deepAK8'");

}

bool ZprimeCandidateBuilder::process(uhh2::Event& event){
  assert(event.jets);
  assert(event.muons || event.electrons);
  assert(event.met);

  // Declare output
  vector<ZprimeCandidate> candidates;

  // Find primary lepton
  FlavorParticle lepton = find_primary_lepton(event);

  // Reconstruct neutrino
  vector<LorentzVector> neutrinos = reconstruct_neutrino(lepton.v4(), event.met->v4());
  unsigned int neutrinoidx = 0;

  // Build all necessary loops
  vector<TopJet> TopTags = event.get(h_AK8TopTags);
  vector<const TopJet*> TopTagsPtr = event.get(h_AK8TopTagsPtr);

  if((event.muons->size() < 1 && event.electrons->size() < 1)) throw runtime_error("Event content did not allow reconstructing the Zprime: Leptons");
  if((event.jets->size() < 2 && TopTags.size() == 0)) throw runtime_error("Event content did not allow reconstructing the Zprime: AK4");
  if((event.jets->size() < 1 && TopTags.size() >= 1)) throw runtime_error("Event content did not allow reconstructing the Zprime: Top-tag");

  // Must have at least one AK4 jet with dR > 1.2
  vector<bool> has_separated_jet;
  for(unsigned int i=0; i<TopTags.size(); i++){
    bool is_sep = false;
    for(unsigned int k = 0; k < event.jets->size(); k++){
      if(deltaR(event.jets->at(k), TopTags[i]) > 1.2) is_sep = true;
    }
    has_separated_jet.emplace_back(is_sep);
  }

  vector<bool> overlap_with_lepton;
  double maxDeltaR = -1;
  if(mode_ == "deepAK8"){
    for(const TopJet & toptag : TopTags){
      bool overlap = true;
      if(deltaR(lepton, toptag) > 0.8) overlap = false;
      overlap_with_lepton.emplace_back(overlap);
    }
  } else if(mode_ == "hotvr"){
    for(const TopJet & toptag : TopTags){
      if(deltaR(lepton, toptag)>maxDeltaR) maxDeltaR = deltaR(lepton, toptag);
      bool overlap = true;
      if(deltaR(lepton, toptag) > 1.5) overlap = false;
      overlap_with_lepton.emplace_back(overlap);
    }
  }

  bool do_toptag_reco = false;
  if(TopTags.size() >= 1){
    for(unsigned int i=0; i<TopTags.size(); i++){
     //cout << "Number of toptags: " << TopTags.size() << endl;
     //cout << "At " << i << " of " << has_separated_jet.size() << " and " << overlap_with_lepton.size() << endl;
    if(has_separated_jet[i] &&  !overlap_with_lepton[i]) do_toptag_reco = true;
    }
  }

  if(!do_toptag_reco){ // AK4 reconstruction

    unsigned int njets = event.jets->size();
    if(njets > 10) njets = 10;

    unsigned int jetiters = pow(3, njets);
    for(const auto & neutrino_v4 : neutrinos) {
      for (unsigned int j=0; j < jetiters; j++) {

        LorentzVector tophadv4;
        vector<Particle> tophadjets;
        LorentzVector toplepv4 = lepton.v4() + neutrino_v4;
        vector<Particle> toplepjets;
        int num = j;
        ZprimeCandidate candidate;
        candidate.set_is_toptag_reconstruction(false);
        candidate.set_is_puppi_reconstruction(false);

        for (unsigned int k=0; k<njets; k++) {
          if(num%3==0){
            tophadv4 = tophadv4 + event.jets->at(k).v4();
            tophadjets.emplace_back(event.jets->at(k));
          }
          if(num%3==1){
            toplepv4 = toplepv4 + event.jets->at(k).v4();
            toplepjets.emplace_back(event.jets->at(k));
          }
          num /= 3;
        }

        if(tophadjets.size() < 1 || toplepjets.size() < 1) continue;

        // Set all member variables of the candidate
        candidate.set_Zprime_v4(tophadv4 + toplepv4);
        candidate.set_top_hadronic_v4(tophadv4);
        candidate.set_top_leptonic_v4(toplepv4);
        candidate.set_jets_hadronic(tophadjets);
        candidate.set_jets_leptonic(toplepjets);
        candidate.set_lepton(lepton);
        candidate.set_neutrino_v4(neutrino_v4);
        candidate.set_neutrinoindex(neutrinoidx);
        candidates.emplace_back(move(candidate));
      }
      neutrinoidx++;
    }
  }
  else{ // TopTag reconstruction
    for(const auto & neutrino_v4 : neutrinos) {
      for (unsigned int j=0; j < TopTags.size(); j++) {
        if(!(has_separated_jet[j] &&  !overlap_with_lepton[j])) continue;

        TopJet toptag = TopTags.at(j);
        const TopJet* toptag_ptr = TopTagsPtr.at(j);

        if(mode_ == "hotvr"){
          // Only HOTVR jet farest from lepton
          if(deltaR(lepton,toptag)<maxDeltaR) continue;
        }

        // Only consider well-separated AK4 jets
        vector<Jet> separated_jets;
        for(unsigned int k = 0; k < event.jets->size(); k++){
          if(deltaR(event.jets->at(k), toptag) > minDR_) separated_jets.emplace_back(event.jets->at(k));
        }
        unsigned int njets = separated_jets.size();
        if(njets < 1) throw runtime_error("In TopTagReco (PUPPI): This toptag does not have >= 1 well-separated AK4 jet. This should have been caught by earlier messages. There is a logic error.");
        if(njets > 10) njets = 10;

        unsigned int jetiters = pow(2, njets);
        for (unsigned int k=0; k < jetiters; k++) {

          LorentzVector tophadv4 = toptag.v4();
          vector<Particle> tophadjets;
          tophadjets.emplace_back(toptag);
          LorentzVector toplepv4 = lepton.v4() + neutrino_v4;
          vector<Particle> toplepjets;
          int num = k;
          ZprimeCandidate candidate;
          candidate.set_is_toptag_reconstruction(true);
          candidate.set_is_puppi_reconstruction(true);

          for (unsigned int l=0; l<njets; l++) {
            if(num%2==0){
              toplepv4 = toplepv4 + separated_jets.at(l).v4();
              toplepjets.emplace_back(separated_jets.at(l));
            }
            num /= 2;
          }

          if(tophadjets.size() < 1 || toplepjets.size() < 1 || separated_jets.size() < 1) continue;

          // Set all member variables of the candidate
          candidate.set_Zprime_v4(tophadv4 + toplepv4);
          candidate.set_top_hadronic_v4(tophadv4);
          candidate.set_top_leptonic_v4(toplepv4);
          candidate.set_jets_hadronic(tophadjets);
          candidate.set_jets_leptonic(toplepjets);
          candidate.set_tophad_topjet_ptr(toptag_ptr);
          candidate.set_lepton(lepton);
          candidate.set_neutrinoindex(neutrinoidx);
          candidate.set_neutrino_v4(neutrino_v4);
          candidates.emplace_back(candidate);

        }
      }
      neutrinoidx++;
    }
  }
  // Set the handle with all candidates
  event.set(h_ZprimeCandidates_, candidates);

  return true;
}


ZprimeChi2Discriminator::ZprimeChi2Discriminator(uhh2::Context& ctx){

  h_ZprimeCandidates_ = ctx.get_handle< std::vector<ZprimeCandidate> >("ZprimeCandidates");
  h_is_zprime_reconstructed_ = ctx.get_handle< bool >("is_zprime_reconstructed_chi2");
  h_BestCandidate_ = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");

  // mtophad_ = 175.;
  // mtophad_ttag_ = 177.;
  // sigmatophad_ = 20.;
  // sigmatophad_ttag_ = 17.;
  // mtoplep_ = 173.;
  // mtoplep_ttag_ = 173.;
  // sigmatoplep_ = 29.;
  // sigmatoplep_ttag_ = 29.;

  // values used in 102
  //mtoplep_ = 175.;
  //sigmatoplep_ = 19.;
  //mtophad_ = 177.;
  //sigmatophad_ = 16.;
  //mtoplep_ttag_ = 175.;
  //sigmatoplep_ttag_ = 19.;
  //mtophad_ttag_ = 173.;
  //sigmatophad_ttag_ = 15.;

  // New fit 2017 MC
  //mtoplep_ = 164.;
  //sigmatoplep_ = 22.;
  //mtophad_ = 166.;
  //sigmatophad_ = 16.;

  //mtoplep_ttag_ = 164.;
  //sigmatoplep_ttag_ = 22.;
  //mtophad_ttag_ = 166.;
  //sigmatophad_ttag_ = 16.;

  mtoplep_ = 173.;
  sigmatoplep_ = 15.;
  mtophad_ = 173.;
  sigmatophad_ = 15.;

  mtoplep_ttag_ = 173.;
  sigmatoplep_ttag_ = 15.;
  mtophad_ttag_ = 173.;
  sigmatophad_ttag_ = 15.;

}

bool ZprimeChi2Discriminator::process(uhh2::Event& event){

  vector<ZprimeCandidate>& candidates = event.get(h_ZprimeCandidates_);
  if(candidates.size() < 1) return false;

  float chi2_best = 99999999;
  ZprimeCandidate* bestCand = &candidates.at(0);
  for(unsigned int i=0; i<candidates.size(); i++){
    bool is_toptag_reconstruction = candidates.at(i).is_toptag_reconstruction();

    float chi2_had = 0.;
    float chi2_lep = 0.;
    float mhad = 0.;
    float mlep = 0.;
    if(is_toptag_reconstruction){

      if(!candidates.at(i).is_puppi_reconstruction()) mhad = candidates.at(i).tophad_topjet_ptr()->softdropmass();
      else{
        LorentzVector SumSubjets(0.,0.,0.,0.);
        for(unsigned int k=0; k<candidates.at(i).tophad_topjet_ptr()->subjets().size(); k++) SumSubjets = SumSubjets + candidates.at(i).tophad_topjet_ptr()->subjets().at(k).v4();
        mhad = inv_mass(SumSubjets);
      }
      mlep = inv_mass(candidates.at(i).top_leptonic_v4());
      chi2_had = pow((mhad - mtophad_ttag_) / sigmatophad_ttag_,2);
      chi2_lep = pow((mlep - mtoplep_ttag_) / sigmatoplep_ttag_,2);
    }
    else{
      mhad = inv_mass(candidates.at(i).top_hadronic_v4());
      mlep = inv_mass(candidates.at(i).top_leptonic_v4());
      chi2_had = pow((mhad - mtophad_) / sigmatophad_,2);
      chi2_lep = pow((mlep - mtoplep_) / sigmatoplep_,2);
    }


    float chi2 = chi2_had + chi2_lep;

    candidates.at(i).set_discriminators("chi2_hadronic", chi2_had);
    candidates.at(i).set_discriminators("chi2_leptonic", chi2_lep);
    candidates.at(i).set_discriminators("chi2_total", chi2);

    if(chi2 < chi2_best){
      chi2_best = chi2;
      bestCand = &candidates.at(i);
    }
  }
  event.set(h_BestCandidate_, bestCand);
  event.set(h_is_zprime_reconstructed_, true);
  return true;
}

// match particle p to one of the jets (Delta R < 0.3); return the deltaR
// of the match.
template<typename T> // T should inherit from Particle
float match_dr(const Particle & p, const std::vector<T> & jets, int& index){
  float mindr = 999999;
  index = -1;
  for(unsigned int i=0; i<jets.size(); ++i){
    float dR = deltaR(p, jets.at(i));
    if( dR <0.3 && dR<mindr) {
      mindr=dR;
      index=i;
    }
  }
  return mindr;
}

ZprimeCorrectMatchDiscriminator::ZprimeCorrectMatchDiscriminator(uhh2::Context& ctx){

  h_ZprimeCandidates_ = ctx.get_handle< std::vector<ZprimeCandidate> >("ZprimeCandidates");
  h_ttbargen_ = ctx.get_handle<TTbarGen>("ttbargen");
  h_is_zprime_reconstructed_ = ctx.get_handle< bool >("is_zprime_reconstructed_correctmatch");
  h_BestCandidate_ = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestCorrectMatch");

  is_mc = ctx.get("dataset_type") == "MC";
  if(is_mc) ttgenprod.reset(new TTbarGenProducer(ctx));
}

bool ZprimeCorrectMatchDiscriminator::process(uhh2::Event& event){

  if(!is_mc) return false;

  // Check if event contains == 2 top quarks
  assert(event.genparticles);
  int n_top = 0, n_antitop = 0;
  for(const auto & gp : *event.genparticles){
    if(gp.pdgId() == 6) n_top++;
    else if(gp.pdgId() == -6) n_antitop++;
  }
  if(n_top != 1 || n_antitop != 1) return false;
  bool check_decay = ttgenprod->process(event);
  if(!check_decay) return false; //FixME: sometimes decay prodcts of ttbar are not Wb+Wb. Why?

  vector<ZprimeCandidate>& candidates = event.get(h_ZprimeCandidates_);
  if(candidates.size() < 1) return false;

  float dr_best = 99999999; // This number should be larger than the largest possible value from above, just so there is always a 'bestCand' set
  ZprimeCandidate* bestCand = &candidates.at(0);
  TTbarGen ttbargen = event.get(h_ttbargen_);
  for(unsigned int i=0; i<candidates.size(); i++){

    bool is_toptag_reconstruction = candidates.at(i).is_toptag_reconstruction();

    // Gen-Lvl ttbar has to decay semileptonically
    if(ttbargen.DecayChannel() != TTbarGen::e_muhad && ttbargen.DecayChannel() != TTbarGen::e_ehad){
      candidates.at(i).set_discriminators("correct_match", 9999999);
      // cout << "Not semileptonic decay" << endl;
      continue;
    }

    vector<Particle> jets_had = candidates.at(i).jets_hadronic();
    vector<Particle> jets_lep = candidates.at(i).jets_leptonic();

    if(jets_lep.size() != 1){
      candidates.at(i).set_discriminators("correct_match", 9999999);
      // cout << "Not ==1 leptonic jet" << endl;
      continue;
    }

    if((!is_toptag_reconstruction && jets_had.size() > 3) || (is_toptag_reconstruction && jets_had.size() != 1)){
      candidates.at(i).set_discriminators("correct_match", 9999999);
      // cout << "Not right amount of hadronic jets" << endl;
      continue;
    }

    float correct_dr = 0.;
    int idx;

    // Match leptonic b-quark
    float dr = match_dr(ttbargen.BLep(), jets_lep, idx);
    if(dr > 0.3){
      candidates.at(i).set_discriminators("correct_match", 9999999);
      // cout << "Not leptonic b-quark matched" << endl;
      continue;
    }
    correct_dr += dr;

    if(!is_toptag_reconstruction){

      unsigned int n_matched = 0;

      // Match hadronic b-quark
      dr = match_dr(ttbargen.BHad(), jets_had, idx);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not hadronic b-quark matched (AK4)" << endl;
        continue;
      }
      correct_dr += dr;
      if(idx >= 0) n_matched++;

      //match quarks from W decays to jets
      // First
      dr = match_dr(ttbargen.Q1(), jets_had, idx);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not had Q1 matched (AK4)" << endl;
        continue;
      }
      correct_dr += dr;
      if(idx >= 0) n_matched++;

      // Second
      dr = match_dr(ttbargen.Q2(), jets_had, idx);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not had Q2 matched (AK4)" << endl;
        continue;
      }
      correct_dr += dr;
      if(idx >= 0) n_matched++;

      if(n_matched != jets_had.size()){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not number of jets and matched equal" << endl;
        continue;
      }
    }
    else{
      const TopJet* topjet = candidates.at(i).tophad_topjet_ptr();

      // Match b-quark
      float dr = deltaR(ttbargen.BHad(), *topjet);
      if(dr > 0.8){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not hadronic b-quark matched (TTAG)" << endl;
        continue;
      }
      correct_dr += dr;

      //match quarks from W decays to jets
      // First
      dr = deltaR(ttbargen.Q1(), *topjet);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not hadronic Q1 matched (TTAG)" << endl;
        continue;
      }
      correct_dr += dr;

      // Second
      dr = deltaR(ttbargen.Q2(), *topjet);
      if(dr > 0.3){
        candidates.at(i).set_discriminators("correct_match", 9999999);
        // cout << "Not hadronic Q2 matched (TTAG)" << endl;
        continue;
      }
      correct_dr += dr;
    }

    correct_dr += deltaR(ttbargen.Neutrino(), candidates.at(i).neutrino_v4());
    candidates.at(i).set_discriminators("correct_match", correct_dr);

    if(correct_dr < dr_best){
      dr_best = correct_dr;
      bestCand = &candidates.at(i);
    }
  }

  if(dr_best > 10.) return false;
  event.set(h_BestCandidate_, bestCand);
  event.set(h_is_zprime_reconstructed_, true);
  return true;
}

AK8PuppiTopTagger::AK8PuppiTopTagger(uhh2::Context& ctx, int min_num_daughters, float max_dR, float min_mass, float max_mass, float max_tau32) : min_num_daughters_(min_num_daughters), max_dR_(max_dR), min_mass_(min_mass), max_mass_(max_mass), max_tau32_(max_tau32) {

  h_AK8PuppiTopTags_ = ctx.get_handle< std::vector<TopJet> >("AK8PuppiTopTags");
  h_AK8PuppiTopTagsPtr_ = ctx.get_handle< std::vector<const TopJet*> >("AK8PuppiTopTagsPtr");

}

bool AK8PuppiTopTagger::process(uhh2::Event& event){

  std::vector<TopJet> toptags;
  vector<const TopJet*> toptags_ptr;
  for(const TopJet & puppijet : *event.toppuppijets){

    // 1) Jet should have at least two daughters
    int n_constit = 0;
    // Loop over subjets' constituents
    for(unsigned int i=0; i<puppijet.subjets().size(); i++){
      n_constit += puppijet.subjets().at(i).numberOfDaughters();
    }
    if(puppijet.numberOfDaughters() > (int)puppijet.subjets().size()){
      n_constit += (puppijet.numberOfDaughters() - puppijet.subjets().size());
    }

    if(n_constit<min_num_daughters_){
      continue;
    }

    // 3) Cut on SD mass
    LorentzVector SumSubjets(0.,0.,0.,0.);
    for(unsigned int k=0; k<puppijet.subjets().size(); k++) SumSubjets = SumSubjets + puppijet.subjets().at(k).v4();
    float mSD = SumSubjets.M();
    if(!(min_mass_ < mSD && mSD < max_mass_)) continue;

    // 4) Cut on tau 3/2
    if(!((puppijet.tau3() / puppijet.tau2()) < max_tau32_)) continue;

    // All jets at this point are top-tagged
    toptags.emplace_back(puppijet);
    toptags_ptr.emplace_back(&puppijet);
  }
  event.set(h_AK8PuppiTopTags_, toptags);
  event.set(h_AK8PuppiTopTagsPtr_, toptags_ptr);
  return (toptags.size() >= 1);
}



HOTVRTopTagger::HOTVRTopTagger(uhh2::Context& ctx) {

  h_HOTVRTopTags_ = ctx.get_handle< std::vector<TopJet> >("HOTVRTopTags");
  h_HOTVRTopTagsPtr_ = ctx.get_handle< std::vector<const TopJet*> >("HOTVRTopTagsPtr");

}

bool HOTVRTopTagger::process(uhh2::Event& event){

  std::vector<TopJet> toptags;
  vector<const TopJet*> toptags_ptr;
  for(const TopJet & topjet : *event.topjets){

    if (toptag_id(topjet, event)){
       toptags.emplace_back(topjet);
       toptags_ptr.emplace_back(&topjet);
    }
  }
  event.set(h_HOTVRTopTags_, toptags);
  event.set(h_HOTVRTopTagsPtr_, toptags_ptr);
  return (toptags.size() >= 1);
}


DeepAK8TopTagger::DeepAK8TopTagger(uhh2::Context& ctx, float min_mSD, float max_mSD, float max_score, float pt_min) : min_mSD_(min_mSD), max_mSD_(max_mSD), max_score_(max_score), pt_min_(pt_min) {

  h_DeepAK8TopTags_ = ctx.get_handle< std::vector<TopJet> >("DeepAK8TopTags");
  h_DeepAK8TopTagsPtr_ = ctx.get_handle< std::vector<const TopJet*> >("DeepAK8TopTagsPtr");

}

bool DeepAK8TopTagger::process(uhh2::Event& event){

  std::vector<TopJet> toptags;
  vector<const TopJet*> toptags_ptr;
  for(const TopJet & puppijet : *event.toppuppijets){

     // pT threshold
     if(!( puppijet.pt() > pt_min_ )) continue;

     // cut on SD mass
     LorentzVector SumSubjets(0.,0.,0.,0.);
     for(unsigned int k=0; k<puppijet.subjets().size(); k++) SumSubjets = SumSubjets + puppijet.subjets().at(k).v4();
     float mSD = SumSubjets.M();
     if(!(min_mSD_ < mSD && mSD < max_mSD_)) continue;

     // cut on score
     if(!( puppijet.btag_MassDecorrelatedDeepBoosted_TvsQCD() > max_score_ )) continue;

     toptags.emplace_back(puppijet);
     toptags_ptr.emplace_back(&puppijet);

  }

  event.set(h_DeepAK8TopTags_, toptags);
  event.set(h_DeepAK8TopTagsPtr_, toptags_ptr);
  return (toptags.size() >= 1);

}

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

float STlep(const uhh2::Event& event){

  assert((event.muons || event.electrons));

  double stlep = 0.;
  for(const Electron & ele : *event.electrons) stlep += ele.pt();
  for(const Muon & mu : *event.muons)          stlep += mu.pt();

  return stlep;
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

//////////////////////////////////////////////////////////////
/////////////// Variables for NN
//////////////////////////////////////////////////////////////

Variables_NN::Variables_NN(uhh2::Context& ctx, TString mode): mode_(mode){
  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  h_CHSjets_matched = ctx.get_handle<std::vector<Jet>>("CHS_matched");
  h_eventweight = ctx.declare_event_output<float> ("eventweight");

///  MUONS
  h_Mu_pt = ctx.declare_event_output<float> ("Mu_pt");
  h_Mu_eta = ctx.declare_event_output<float> ("Mu_eta");
  h_Mu_phi = ctx.declare_event_output<float> ("Mu_phi");
  h_Mu_E = ctx.declare_event_output<float> ("Mu_E");

///  ELECTRONS
  h_Ele_pt = ctx.declare_event_output<float> ("Ele_pt");
  h_Ele_eta = ctx.declare_event_output<float> ("Ele_eta");
  h_Ele_phi = ctx.declare_event_output<float> ("Ele_phi");
  h_Ele_E = ctx.declare_event_output<float> ("Ele_E");

///  MET
  h_MET_pt = ctx.declare_event_output<float> ("MET_pt");
  h_MET_phi = ctx.declare_event_output<float> ("MET_phi");

///  AK4 JETS
  h_N_Ak4 = ctx.declare_event_output<float> ("N_Ak4");

  h_Ak4_j1_pt = ctx.declare_event_output<float> ("Ak4_j1_pt");
  h_Ak4_j1_eta = ctx.declare_event_output<float>("Ak4_j1_eta");
  h_Ak4_j1_phi = ctx.declare_event_output<float>("Ak4_j1_phi");
  h_Ak4_j1_E = ctx.declare_event_output<float>  ("Ak4_j1_E");
  h_Ak4_j1_m = ctx.declare_event_output<float>  ("Ak4_j1_m");
  h_Ak4_j1_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j1_deepjetbscore");

  h_Ak4_j2_pt = ctx.declare_event_output<float> ("Ak4_j2_pt");
  h_Ak4_j2_eta = ctx.declare_event_output<float>("Ak4_j2_eta");
  h_Ak4_j2_phi = ctx.declare_event_output<float>("Ak4_j2_phi");
  h_Ak4_j2_E = ctx.declare_event_output<float>  ("Ak4_j2_E");
  h_Ak4_j2_m = ctx.declare_event_output<float>  ("Ak4_j2_m");
  h_Ak4_j2_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j2_deepjetbscore");

  h_Ak4_j3_pt = ctx.declare_event_output<float> ("Ak4_j3_pt");
  h_Ak4_j3_eta = ctx.declare_event_output<float>("Ak4_j3_eta");
  h_Ak4_j3_phi = ctx.declare_event_output<float>("Ak4_j3_phi");
  h_Ak4_j3_E = ctx.declare_event_output<float>  ("Ak4_j3_E");
  h_Ak4_j3_m = ctx.declare_event_output<float>  ("Ak4_j3_m");
  h_Ak4_j3_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j3_deepjetbscore");

  h_Ak4_j4_pt = ctx.declare_event_output<float> ("Ak4_j4_pt");
  h_Ak4_j4_eta = ctx.declare_event_output<float>("Ak4_j4_eta");
  h_Ak4_j4_phi = ctx.declare_event_output<float>("Ak4_j4_phi");
  h_Ak4_j4_E = ctx.declare_event_output<float>  ("Ak4_j4_E");
  h_Ak4_j4_m = ctx.declare_event_output<float>  ("Ak4_j4_m");
  h_Ak4_j4_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j4_deepjetbscore");

  h_Ak4_j5_pt = ctx.declare_event_output<float> ("Ak4_j5_pt");
  h_Ak4_j5_eta = ctx.declare_event_output<float>("Ak4_j5_eta");
  h_Ak4_j5_phi = ctx.declare_event_output<float>("Ak4_j5_phi");
  h_Ak4_j5_E = ctx.declare_event_output<float>  ("Ak4_j5_E");
  h_Ak4_j5_m = ctx.declare_event_output<float>  ("Ak4_j5_m");
  h_Ak4_j5_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j5_deepjetbscore");

  h_Ak4_j6_pt = ctx.declare_event_output<float> ("Ak4_j6_pt");
  h_Ak4_j6_eta = ctx.declare_event_output<float>("Ak4_j6_eta");
  h_Ak4_j6_phi = ctx.declare_event_output<float>("Ak4_j6_phi");
  h_Ak4_j6_E = ctx.declare_event_output<float>  ("Ak4_j6_E");
  h_Ak4_j6_m = ctx.declare_event_output<float>  ("Ak4_j6_m");
  h_Ak4_j6_deepjetbscore = ctx.declare_event_output<float>  ("Ak4_j6_deepjetbscore");

/// AK8 JETS
  if(mode_ == "deepAK8"){
  h_N_Ak8 = ctx.declare_event_output<float> ("N_Ak8");

  h_Ak8_j1_pt = ctx.declare_event_output<float> ("Ak8_j1_pt");
  h_Ak8_j1_eta = ctx.declare_event_output<float>("Ak8_j1_eta");
  h_Ak8_j1_phi = ctx.declare_event_output<float>("Ak8_j1_phi");
  h_Ak8_j1_E = ctx.declare_event_output<float>  ("Ak8_j1_E");
  h_Ak8_j1_mSD = ctx.declare_event_output<float>("Ak8_j1_mSD");
  h_Ak8_j1_tau21 = ctx.declare_event_output<float>("Ak8_j1_tau21");
  h_Ak8_j1_tau32 = ctx.declare_event_output<float>("Ak8_j1_tau32");

  h_Ak8_j2_pt = ctx.declare_event_output<float> ("Ak8_j2_pt");
  h_Ak8_j2_eta = ctx.declare_event_output<float>("Ak8_j2_eta");
  h_Ak8_j2_phi = ctx.declare_event_output<float>("Ak8_j2_phi");
  h_Ak8_j2_E = ctx.declare_event_output<float>  ("Ak8_j2_E");
  h_Ak8_j2_mSD = ctx.declare_event_output<float>("Ak8_j2_mSD");
  h_Ak8_j2_tau21 = ctx.declare_event_output<float>("Ak8_j2_tau21");
  h_Ak8_j2_tau32 = ctx.declare_event_output<float>("Ak8_j2_tau32");

  h_Ak8_j3_pt = ctx.declare_event_output<float> ("Ak8_j3_pt");
  h_Ak8_j3_eta = ctx.declare_event_output<float>("Ak8_j3_eta");
  h_Ak8_j3_phi = ctx.declare_event_output<float>("Ak8_j3_phi");
  h_Ak8_j3_E = ctx.declare_event_output<float>  ("Ak8_j3_E");
  h_Ak8_j3_mSD = ctx.declare_event_output<float>("Ak8_j3_mSD");
  h_Ak8_j3_tau21 = ctx.declare_event_output<float>("Ak8_j3_tau21");
  h_Ak8_j3_tau32 = ctx.declare_event_output<float>("Ak8_j3_tau32");
  }else if(mode_ == "hotvr"){
///  HOTVR JETS
  h_N_HOTVR = ctx.declare_event_output<float> ("N_HOTVR");

  h_HOTVR_j1_pt = ctx.declare_event_output<float> ("HOTVR_j1_pt");
  h_HOTVR_j1_eta = ctx.declare_event_output<float>("HOTVR_j1_eta");
  h_HOTVR_j1_phi = ctx.declare_event_output<float>("HOTVR_j1_phi");
  h_HOTVR_j1_E = ctx.declare_event_output<float>  ("HOTVR_j1_E");
  h_HOTVR_j1_mSD = ctx.declare_event_output<float>("HOTVR_j1_mSD");
  h_HOTVR_j1_tau21 = ctx.declare_event_output<float>("HOTVR_j1_tau21");
  h_HOTVR_j1_tau32 = ctx.declare_event_output<float>("HOTVR_j1_tau32");

  h_HOTVR_j2_pt = ctx.declare_event_output<float> ("HOTVR_j2_pt");
  h_HOTVR_j2_eta = ctx.declare_event_output<float>("HOTVR_j2_eta");
  h_HOTVR_j2_phi = ctx.declare_event_output<float>("HOTVR_j2_phi");
  h_HOTVR_j2_E = ctx.declare_event_output<float>  ("HOTVR_j2_E");
  h_HOTVR_j2_mSD = ctx.declare_event_output<float>("HOTVR_j2_mSD");
  h_HOTVR_j2_tau21 = ctx.declare_event_output<float>("HOTVR_j2_tau21");
  h_HOTVR_j2_tau32 = ctx.declare_event_output<float>("HOTVR_j2_tau32");

  h_HOTVR_j3_pt = ctx.declare_event_output<float> ("HOTVR_j3_pt");
  h_HOTVR_j3_eta = ctx.declare_event_output<float>("HOTVR_j3_eta");
  h_HOTVR_j3_phi = ctx.declare_event_output<float>("HOTVR_j3_phi");
  h_HOTVR_j3_E = ctx.declare_event_output<float>  ("HOTVR_j3_E");
  h_HOTVR_j3_mSD = ctx.declare_event_output<float>("HOTVR_j3_mSD");
  h_HOTVR_j3_tau21 = ctx.declare_event_output<float>("HOTVR_j3_tau21");
  h_HOTVR_j3_tau32 = ctx.declare_event_output<float>("HOTVR_j3_tau32");
  }

///  M ttbar
  h_M_tt = ctx.declare_event_output<float> ("M_tt");

}

bool Variables_NN::process(uhh2::Event& evt){

  double weight = evt.weight;
  evt.set(h_eventweight, -10);
  evt.set(h_eventweight, weight);

/////////   MUONS
  evt.set(h_Mu_pt, -10);
  evt.set(h_Mu_eta,-10);
  evt.set(h_Mu_phi, -10);
  evt.set(h_Mu_E, -10);

  vector<Muon>* muons = evt.muons;
  int Nmuons = muons->size();

  for(int i=0; i<Nmuons; i++){
      evt.set(h_Mu_pt, muons->at(i).pt());
      evt.set(h_Mu_eta, muons->at(i).eta());
      evt.set(h_Mu_phi, muons->at(i).phi());
      evt.set(h_Mu_E, muons->at(i).energy());
  }


/////////   ELECTRONS
  evt.set(h_Ele_pt, -10);
  evt.set(h_Ele_eta, -10);
  evt.set(h_Ele_phi, -10);
  evt.set(h_Ele_E, -10);

  vector<Electron>* electrons = evt.electrons;
  int Nelectrons = electrons->size();

  for(int i=0; i<Nelectrons; i++){
      evt.set(h_Ele_pt, electrons->at(i).pt());
      evt.set(h_Ele_eta, electrons->at(i).eta());
      evt.set(h_Ele_phi, electrons->at(i).phi());
      evt.set(h_Ele_E, electrons->at(i).energy());
  }

/////////   MET
  evt.set(h_MET_pt, -10);
  evt.set(h_MET_phi, -10);

  evt.set(h_MET_pt, evt.met->pt());
  evt.set(h_MET_phi, evt.met->phi());


///////// AK4 JETS
  evt.set(h_N_Ak4, -10);

  evt.set(h_Ak4_j1_pt, -10);
  evt.set(h_Ak4_j1_eta, -10);
  evt.set(h_Ak4_j1_phi, -10);
  evt.set(h_Ak4_j1_E, -10);
  evt.set(h_Ak4_j1_m, -10);
  evt.set(h_Ak4_j1_deepjetbscore, -10);

  evt.set(h_Ak4_j2_pt, -10);
  evt.set(h_Ak4_j2_eta, -10);
  evt.set(h_Ak4_j2_phi, -10);
  evt.set(h_Ak4_j2_E, -10);
  evt.set(h_Ak4_j2_m, -10);
  evt.set(h_Ak4_j2_deepjetbscore, -10);

  evt.set(h_Ak4_j3_pt, -10);
  evt.set(h_Ak4_j3_eta, -10);
  evt.set(h_Ak4_j3_phi, -10);
  evt.set(h_Ak4_j3_E, -10);
  evt.set(h_Ak4_j3_m, -10);
  evt.set(h_Ak4_j3_deepjetbscore, -10);

  evt.set(h_Ak4_j4_pt, -10);
  evt.set(h_Ak4_j4_eta, -10);
  evt.set(h_Ak4_j4_phi, -10);
  evt.set(h_Ak4_j4_E, -10);
  evt.set(h_Ak4_j4_m, -10);
  evt.set(h_Ak4_j4_deepjetbscore, -10);

  evt.set(h_Ak4_j5_pt, -10);
  evt.set(h_Ak4_j5_eta, -10);
  evt.set(h_Ak4_j5_phi, -10);
  evt.set(h_Ak4_j5_E, -10);
  evt.set(h_Ak4_j5_m, -10);
  evt.set(h_Ak4_j5_deepjetbscore, -10);

  evt.set(h_Ak4_j6_pt, -10);
  evt.set(h_Ak4_j6_eta, -10);
  evt.set(h_Ak4_j6_phi, -10);
  evt.set(h_Ak4_j6_E, -10);
  evt.set(h_Ak4_j6_m, -10);
  evt.set(h_Ak4_j6_deepjetbscore, -10);


  vector<Jet>* Ak4jets = evt.jets;
  int NAk4jets = Ak4jets->size();
  evt.set(h_N_Ak4, NAk4jets);

  for(int i=0; i<NAk4jets; i++){
      if(i==0){
      evt.set(h_Ak4_j1_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j1_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j1_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j1_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j1_m, Ak4jets->at(i).v4().M());
      //evt.set(h_Ak4_j1_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==1){
      evt.set(h_Ak4_j2_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j2_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j2_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j2_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j2_m, Ak4jets->at(i).v4().M());
      //evt.set(h_Ak4_j2_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==2){
      evt.set(h_Ak4_j3_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j3_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j3_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j3_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j3_m, Ak4jets->at(i).v4().M());
      //evt.set(h_Ak4_j3_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==3){
      evt.set(h_Ak4_j4_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j4_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j4_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j4_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j4_m, Ak4jets->at(i).v4().M());
      //evt.set(h_Ak4_j4_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==4){
      evt.set(h_Ak4_j5_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j5_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j5_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j5_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j5_m, Ak4jets->at(i).v4().M());
      //evt.set(h_Ak4_j5_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
      if(i==5){
      evt.set(h_Ak4_j6_pt, Ak4jets->at(i).pt());
      evt.set(h_Ak4_j6_eta, Ak4jets->at(i).eta());
      evt.set(h_Ak4_j6_phi, Ak4jets->at(i).phi());
      evt.set(h_Ak4_j6_E, Ak4jets->at(i).energy());
      evt.set(h_Ak4_j6_m, Ak4jets->at(i).v4().M());
      //evt.set(h_Ak4_j6_deepjetbscore, Ak4jets->at(i).btag_DeepJet());
      }
  }

  // save b-tag score of matched CHS jet
  vector<Jet> AK4CHSjets_matched = evt.get(h_CHSjets_matched);
  for(unsigned int i=0; i<AK4CHSjets_matched.size(); i++){
      if(i==0){
      evt.set(h_Ak4_j1_deepjetbscore, AK4CHSjets_matched.at(i).btag_DeepJet());
      }
      if(i==1){
      evt.set(h_Ak4_j2_deepjetbscore, AK4CHSjets_matched.at(i).btag_DeepJet());
      }
      if(i==2){
      evt.set(h_Ak4_j3_deepjetbscore, AK4CHSjets_matched.at(i).btag_DeepJet());
      }
      if(i==3){
      evt.set(h_Ak4_j4_deepjetbscore, AK4CHSjets_matched.at(i).btag_DeepJet());
      }
      if(i==4){
      evt.set(h_Ak4_j5_deepjetbscore, AK4CHSjets_matched.at(i).btag_DeepJet());
      }
      if(i==5){
      evt.set(h_Ak4_j6_deepjetbscore, AK4CHSjets_matched.at(i).btag_DeepJet());
      }
  }

/////////   AK8 JETS
  if(mode_ == "deepAK8"){
  evt.set(h_N_Ak8, -10);

  evt.set(h_Ak8_j1_pt, -10);
  evt.set(h_Ak8_j1_eta, -10);
  evt.set(h_Ak8_j1_phi, -10);
  evt.set(h_Ak8_j1_E, -10);
  evt.set(h_Ak8_j1_mSD, -10);
  evt.set(h_Ak8_j1_tau21, -10);
  evt.set(h_Ak8_j1_tau32, -10);

  evt.set(h_Ak8_j2_pt, -10);
  evt.set(h_Ak8_j2_eta, -10);
  evt.set(h_Ak8_j2_phi, -10);
  evt.set(h_Ak8_j2_E, -10);
  evt.set(h_Ak8_j2_mSD, -10);
  evt.set(h_Ak8_j2_tau21, -10);
  evt.set(h_Ak8_j2_tau32, -10);

  evt.set(h_Ak8_j3_pt, -10);
  evt.set(h_Ak8_j3_eta, -10);
  evt.set(h_Ak8_j3_phi, -10);
  evt.set(h_Ak8_j3_E, -10);
  evt.set(h_Ak8_j3_mSD, -10);
  evt.set(h_Ak8_j3_tau21, -10);
  evt.set(h_Ak8_j3_tau32, -10);

  vector<TopJet>* Ak8jets = evt.toppuppijets;
  int NAk8jets = Ak8jets->size();
  evt.set(h_N_Ak8, NAk8jets);

  for(int i=0; i<NAk8jets; i++){
      if(i==0){
      evt.set(h_Ak8_j1_pt, Ak8jets->at(i).pt());
      evt.set(h_Ak8_j1_eta, Ak8jets->at(i).eta());
      evt.set(h_Ak8_j1_phi, Ak8jets->at(i).phi());
      evt.set(h_Ak8_j1_E, Ak8jets->at(i).energy());
      evt.set(h_Ak8_j1_mSD, Ak8jets->at(i).softdropmass());
      evt.set(h_Ak8_j1_tau21, Ak8jets->at(i).tau2()/Ak8jets->at(i).tau1());
      evt.set(h_Ak8_j1_tau32, Ak8jets->at(i).tau3()/Ak8jets->at(i).tau2());
      }
      if(i==1){
      evt.set(h_Ak8_j2_pt, Ak8jets->at(i).pt());
      evt.set(h_Ak8_j2_eta, Ak8jets->at(i).eta());
      evt.set(h_Ak8_j2_phi, Ak8jets->at(i).phi());
      evt.set(h_Ak8_j2_E, Ak8jets->at(i).energy());
      evt.set(h_Ak8_j2_mSD, Ak8jets->at(i).softdropmass());
      evt.set(h_Ak8_j2_tau21, Ak8jets->at(i).tau2()/Ak8jets->at(i).tau1());
      evt.set(h_Ak8_j2_tau32, Ak8jets->at(i).tau3()/Ak8jets->at(i).tau2());
      }
      if(i==2){
      evt.set(h_Ak8_j3_pt, Ak8jets->at(i).pt());
      evt.set(h_Ak8_j3_eta, Ak8jets->at(i).eta());
      evt.set(h_Ak8_j3_phi, Ak8jets->at(i).phi());
      evt.set(h_Ak8_j3_E, Ak8jets->at(i).energy());
      evt.set(h_Ak8_j3_mSD, Ak8jets->at(i).softdropmass());
      evt.set(h_Ak8_j3_tau21, Ak8jets->at(i).tau2()/Ak8jets->at(i).tau1());
      evt.set(h_Ak8_j3_tau32, Ak8jets->at(i).tau3()/Ak8jets->at(i).tau2());
      }
  }
  }// end deepAK8 mode

/////////   HOTVR JETS
  if(mode_ == "hotvr"){
  evt.set(h_N_HOTVR, -10);

  evt.set(h_HOTVR_j1_pt, -10);
  evt.set(h_HOTVR_j1_eta, -10);
  evt.set(h_HOTVR_j1_phi, -10);
  evt.set(h_HOTVR_j1_E, -10);
  evt.set(h_HOTVR_j1_mSD, -10);
  evt.set(h_HOTVR_j1_tau21, -10);
  evt.set(h_HOTVR_j1_tau32, -10);

  evt.set(h_HOTVR_j2_pt, -10);
  evt.set(h_HOTVR_j2_eta, -10);
  evt.set(h_HOTVR_j2_phi, -10);
  evt.set(h_HOTVR_j2_E, -10);
  evt.set(h_HOTVR_j2_mSD, -10);
  evt.set(h_HOTVR_j2_tau21, -10);
  evt.set(h_HOTVR_j2_tau32, -10);

  evt.set(h_HOTVR_j3_pt, -10);
  evt.set(h_HOTVR_j3_eta, -10);
  evt.set(h_HOTVR_j3_phi, -10);
  evt.set(h_HOTVR_j3_E, -10);
  evt.set(h_HOTVR_j3_mSD, -10);
  evt.set(h_HOTVR_j3_tau21, -10);
  evt.set(h_HOTVR_j3_tau32, -10);


  vector<TopJet>* HOTVRjets = evt.topjets;
  int NHOTVRjets = HOTVRjets->size();
  evt.set(h_N_HOTVR, NHOTVRjets);

  for(int i=0; i<NHOTVRjets; i++){
      if(i==0){
      evt.set(h_HOTVR_j1_pt, HOTVRjets->at(i).pt());
      evt.set(h_HOTVR_j1_eta, HOTVRjets->at(i).eta());
      evt.set(h_HOTVR_j1_phi, HOTVRjets->at(i).phi());
      evt.set(h_HOTVR_j1_E, HOTVRjets->at(i).energy());
      evt.set(h_HOTVR_j1_mSD, HOTVRjets->at(i).v4().M());
      evt.set(h_HOTVR_j1_tau21, HOTVRjets->at(i).tau2_groomed()/HOTVRjets->at(i).tau1_groomed());
      evt.set(h_HOTVR_j1_tau32, HOTVRjets->at(i).tau3_groomed()/HOTVRjets->at(i).tau2_groomed());
      }
      if(i==1){
      evt.set(h_HOTVR_j2_pt, HOTVRjets->at(i).pt());
      evt.set(h_HOTVR_j2_eta, HOTVRjets->at(i).eta());
      evt.set(h_HOTVR_j2_phi, HOTVRjets->at(i).phi());
      evt.set(h_HOTVR_j2_E, HOTVRjets->at(i).energy());
      evt.set(h_HOTVR_j2_mSD, HOTVRjets->at(i).v4().M());
      evt.set(h_HOTVR_j2_tau21, HOTVRjets->at(i).tau2_groomed()/HOTVRjets->at(i).tau1_groomed());
      evt.set(h_HOTVR_j2_tau32, HOTVRjets->at(i).tau3_groomed()/HOTVRjets->at(i).tau2_groomed());
      }
      if(i==2){
      evt.set(h_HOTVR_j3_pt, HOTVRjets->at(i).pt());
      evt.set(h_HOTVR_j3_eta, HOTVRjets->at(i).eta());
      evt.set(h_HOTVR_j3_phi, HOTVRjets->at(i).phi());
      evt.set(h_HOTVR_j3_E, HOTVRjets->at(i).energy());
      evt.set(h_HOTVR_j3_mSD, HOTVRjets->at(i).v4().M());
      evt.set(h_HOTVR_j3_tau21, HOTVRjets->at(i).tau2_groomed()/HOTVRjets->at(i).tau1_groomed());
      evt.set(h_HOTVR_j3_tau32, HOTVRjets->at(i).tau3_groomed()/HOTVRjets->at(i).tau2_groomed());
      }
  }
  } // end hotvr mode

  // ttbar mass
  evt.set(h_M_tt, -10);
  bool is_zprime_reconstructed_chi2 = evt.get(h_is_zprime_reconstructed_chi2);
  if(is_zprime_reconstructed_chi2){
    ZprimeCandidate* BestZprimeCandidate = evt.get(h_BestZprimeCandidateChi2);
    float Mass_tt = BestZprimeCandidate->Zprime_v4().M();
  evt.set(h_M_tt, Mass_tt);
  }



  return true;
}

//////////////////////////////////
//  EWK corrections
//////////////////////////////////
// Generic Class for Applying SFs
void ScaleFactorsFromHistos::LoadHisto(TFile* file, std::string name, std::string hname) {
  histos[name].reset((TH1F*)file->Get(hname.c_str()));
  histos[name]->SetDirectory(0);
};

double ScaleFactorsFromHistos::Evaluator(std::string hname, double var) {
  // invalid cases
  if (var == uhh2::infinity) return 1.0;

  int firstBin = 1;
  int lastBin  = histos[hname]->GetNbinsX();
  double h_min = histos[hname]->GetBinCenter(firstBin)-histos[hname]->GetBinError(firstBin);
  double h_max = histos[hname]->GetBinCenter(lastBin)+histos[hname]->GetBinError(lastBin);
  double var_for_eval = var;
  var_for_eval = (var_for_eval > h_min) ? var_for_eval : h_min+0.001;
  var_for_eval = (var_for_eval < h_max) ? var_for_eval : h_max-0.001;
  return histos[hname]->GetBinContent(histos[hname]->FindBin(var_for_eval));
};



NLOCorrections::NLOCorrections(uhh2::Context& ctx) {

 // Corrections for 2017 and 2018 are the same. 2016 is different
 is2016 = (ctx.get("dataset_version").find("2016") != std::string::npos);

 is_Wjets  = (ctx.get("dataset_version").find("WJets") != std::string::npos);
 is_Znn  = (ctx.get("dataset_version").find("DY_inv") != std::string::npos);
 is_DY  = (ctx.get("dataset_version").find("DY") != std::string::npos) && !is_Znn;
 is_Zjets  = is_DY || is_Znn;


 std::string folder_ = ctx.get("NLOCorrections");
 for (const std::string& proc: {"w","z"}) {
    TFile* file_ = new TFile((folder_+"merged_kfactors_"+proc+"jets.root").c_str());
    for (const std::string& corr: {"ewk","qcd","qcd_ewk"}) LoadHisto(file_, proc+"_"+corr, "kfactor_monojet_"+corr);
    file_->Close();
  }
  for (const std::string& proc: {"dy","znn"}) {
    TFile* file_ = new TFile((folder_+"kfac_"+proc+"_filter.root").c_str());
    LoadHisto(file_, proc+"_qcd_2017", "kfac_"+proc+"_filter");
    file_->Close();
  }
  TFile* file_ = new TFile((folder_+"2017_gen_v_pt_qcd_sf.root").c_str());
  LoadHisto(file_, "w_qcd_2017", "wjet_dress_inclusive");
  file_->Close();
  file_ = new TFile((folder_+"lindert_qcd_nnlo_sf.root").c_str());
  for (const std::string& proc: {"eej", "evj", "vvj"}) LoadHisto(file_, proc+"_qcd_nnlo", proc);
  file_->Close();

}


double NLOCorrections::GetPartonObjectPt(uhh2::Event& event, ParticleID objID) {
  for(const auto & gp : *event.genparticles) {if (gp.pdgId()==objID) return gp.pt(); }
  return uhh2::infinity;
};




bool NLOCorrections::process(uhh2::Event& event){
 // Sample dependant corrections
 if ((!is_Wjets && !is_Zjets) || event.isRealData) return true;
 double objpt = uhh2::infinity, theory_weight = 1.0;
 std::string process = "";

 const bool do_EWK = true;
 const bool do_QCD_EWK = false;
 const bool do_QCD_NLO  = true;
 const bool do_QCD_NNLO = false;


  if (is_Zjets) objpt = GetPartonObjectPt(event,ParticleID::Z);
  if (is_Wjets) objpt = GetPartonObjectPt(event,ParticleID::W);

  if (is_Zjets) process = "z";
  if (is_Wjets) process = "w";

  if (do_QCD_EWK) theory_weight *= Evaluator(process+"_qcd_ewk",objpt);
  else {
    if (do_EWK) theory_weight *= Evaluator(process+"_ewk",objpt);
    if (do_QCD_NLO) {
      if (!is2016) {
        if (is_DY)  process = "dy";
        if (is_Znn) process = "znn";
      }
      theory_weight *= Evaluator(process+"_qcd"+(is2016?"":"_2017"),objpt);
    }
  }

  if (do_QCD_NNLO) {
    if (is_DY)    process = "eej";
    if (is_Znn)   process = "vvj";
    if (is_Wjets) process = "evj";
    theory_weight *= Evaluator(process+"_qcd_nnlo",objpt);
  }

  event.weight *= theory_weight;
  return true;
}


// Top pT Reweight extended - from Alex F.

TopPtReweighting::TopPtReweighting(uhh2::Context& ctx,
				   float a, float b,
				   const std::string& syst_a,
				   const std::string& syst_b,
				   const std::string& ttgen_name,
				   const std::string& weight_name):
  a_(a), b_(b),
  ttgen_name_(ttgen_name){

  weight_name_ = weight_name;
  if(!weight_name_.empty())
    h_weight_= ctx.get_handle<float>(weight_name);
  version_ = ctx.get("dataset_version", "");
  boost::algorithm::to_lower(version_);
  if(!ttgen_name_.empty()){
    h_ttbargen_ = ctx.get_handle<TTbarGen>(ttgen_name);
  }

  if (syst_a == "up")
    a_ *= 1.5;
  else if (syst_a == "down")
    a_ *= 0.5;

  if (syst_b == "up")
    b_ *= 1.5;
  else if (syst_b == "down")
    b_ *= 0.5;
}

bool TopPtReweighting::process(uhh2::Event& event){
  if (event.isRealData || (!boost::algorithm::contains(version_,"ttbar") && !boost::algorithm::contains(version_,"ttjets") && !boost::algorithm::starts_with(version_,"tt")) ) {
    return true;
  }
  const TTbarGen& ttbargen = !ttgen_name_.empty() ? event.get(h_ttbargen_) : TTbarGen(*event.genparticles,false);
  float wgt = 1.;
  if (ttbargen.DecayChannel() != TTbarGen::e_notfound) {
    float tpt1 = ttbargen.Top().v4().Pt();
    float tpt2 = ttbargen.Antitop().v4().Pt();
    wgt = sqrt(exp(a_+b_*tpt1)*exp(a_+b_*tpt2));
  }

  if(!weight_name_.empty())
    event.set(h_weight_, wgt);

  event.weight *= wgt;
  return true;
}


////

PuppiCHS_matching::PuppiCHS_matching(uhh2::Context& ctx){

  h_CHSjets = ctx.get_handle< std::vector<Jet> >("jetsAk4CHS");
  h_CHS_matched_ = ctx.declare_event_output<vector<Jet>>("CHS_matched");

}

bool PuppiCHS_matching::process(uhh2::Event& event){

  vector<Jet> CHSjets = event.get(h_CHSjets);
  std::vector<Jet> matched_jets;
  std::vector<Jet> matched_jets_PUPPI;

  for(const Jet & jet : *event.jets){ // PUPPI jets
     double deltaR_min = 99;

     for(const Jet & CHSjet : CHSjets){ // CHS jets
        double deltaR_CHS = deltaR(jet,CHSjet);
        if(deltaR_CHS<deltaR_min) deltaR_min = deltaR_CHS;
     } // end CHS loop

     if(deltaR_min>0.2) continue;

     for(const Jet & CHSjet : CHSjets){
     if(deltaR(jet,CHSjet)!=deltaR_min) continue;
     else{
      matched_jets.emplace_back(CHSjet);
      matched_jets_PUPPI.emplace_back(jet);
     }
     }

  } // end PUPPI loop
  std::swap(matched_jets_PUPPI, *event.jets);
  event.set(h_CHS_matched_, matched_jets);
  if(event.jets->size()==0) return false;
  return true;
}

////

MuonRecoSF::MuonRecoSF(uhh2::Context& ctx){
  
  year = extract_year(ctx);
  is_mc = ctx.get("dataset_type") == "MC";
  is_Muon = ctx.get("channel") == "muon";

  h_muonrecSF_nominal = ctx.declare_event_output<float> ("muonrecSF_nominal");
  h_muonrecSF_up      = ctx.declare_event_output<float> ("muonrecSF_up");
  h_muonrecSF_down    = ctx.declare_event_output<float> ("muonrecSF_down");

}

bool MuonRecoSF::process(uhh2::Event& event){

  event.set(h_muonrecSF_nominal, 1.0);
  event.set(h_muonrecSF_up, 1.0);
  event.set(h_muonrecSF_down, 1.0);

  if(is_mc && is_Muon){ 
  float Tot_P = event.muons->at(0).pt()*cosh(event.muons->at(0).eta());
    if(year == Year::isUL16preVFP || year == Year::isUL16postVFP){
        if( abs(event.muons->at(0).eta()) <= 1.6){ 
            if( 50 < Tot_P && Tot_P <= 100)   { event.set(h_muonrecSF_nominal, 0.9914); event.set(h_muonrecSF_up, 0.9914+0.0008); event.set(h_muonrecSF_down, 0.9914-0.0008); event.weight *= 0.9914; }
            if( 100 < Tot_P && Tot_P <= 150)  { event.set(h_muonrecSF_nominal, 0.9936); event.set(h_muonrecSF_up, 0.9936+0.0009); event.set(h_muonrecSF_down, 0.9936-0.0009); event.weight *= 0.9936; }
            if( 150 < Tot_P && Tot_P <= 200)  { event.set(h_muonrecSF_nominal, 0.993); event.set(h_muonrecSF_up, 0.993+0.001); event.set(h_muonrecSF_down, 0.993-0.001); event.weight *= 0.993; }
            if( 200 < Tot_P && Tot_P <= 300)  { event.set(h_muonrecSF_nominal, 0.993); event.set(h_muonrecSF_up, 0.993+0.002); event.set(h_muonrecSF_down, 0.993-0.002); event.weight *= 0.993; }
            if( 300 < Tot_P && Tot_P <= 400)  { event.set(h_muonrecSF_nominal, 0.990); event.set(h_muonrecSF_up, 0.990+0.004); event.set(h_muonrecSF_down, 0.990-0.004); event.weight *= 0.990; }
            if( 400 < Tot_P && Tot_P <= 600)  { event.set(h_muonrecSF_nominal, 0.990); event.set(h_muonrecSF_up, 0.990+0.003); event.set(h_muonrecSF_down, 0.990-0.003); event.weight *= 0.990; }
            if( 600 < Tot_P && Tot_P <= 1500) { event.set(h_muonrecSF_nominal, 0.989); event.set(h_muonrecSF_up, 0.989+0.004); event.set(h_muonrecSF_down, 0.989-0.004); event.weight *= 0.989; }
            if( 1500 < Tot_P && Tot_P <= 3500){ event.set(h_muonrecSF_nominal, 0.8); event.set(h_muonrecSF_up, 0.8+0.3); event.set(h_muonrecSF_down, 0.8-0.3); event.weight *= 0.8; }
        }
        if(abs(event.muons->at(0).eta()) > 1.6 && abs(event.muons->at(0).eta()) < 2.4){ 
            if( 50 < Tot_P && Tot_P <= 100)   { event.set(h_muonrecSF_nominal, 1.0); event.set(h_muonrecSF_up, 1.0); event.set(h_muonrecSF_down, 1.0); event.weight *= 1.0; }
            if( 100 < Tot_P && Tot_P <= 150)  { event.set(h_muonrecSF_nominal, 0.993); event.set(h_muonrecSF_up, 0.993+0.001); event.set(h_muonrecSF_down, 0.993-0.001); event.weight *= 0.993; }
            if( 150 < Tot_P && Tot_P <= 200)  { event.set(h_muonrecSF_nominal, 0.991); event.set(h_muonrecSF_up, 0.991+0.001); event.set(h_muonrecSF_down, 0.991-0.001); event.weight *= 0.991; }
            if( 200 < Tot_P && Tot_P <= 300)  { event.set(h_muonrecSF_nominal, 0.985); event.set(h_muonrecSF_up, 0.985+0.001); event.set(h_muonrecSF_down, 0.985-0.001); event.weight *= 0.985; }
            if( 300 < Tot_P && Tot_P <= 400)  { event.set(h_muonrecSF_nominal, 0.981); event.set(h_muonrecSF_up, 0.981+0.002); event.set(h_muonrecSF_down, 0.981-0.002); event.weight *= 0.981; }
            if( 400 < Tot_P && Tot_P <= 600)  { event.set(h_muonrecSF_nominal, 0.979); event.set(h_muonrecSF_up, 0.979+0.004); event.set(h_muonrecSF_down, 0.979-0.004); event.weight *= 0.979; }
            if( 600 < Tot_P && Tot_P <= 1500) { event.set(h_muonrecSF_nominal, 0.978); event.set(h_muonrecSF_up, 0.978+0.005); event.set(h_muonrecSF_down, 0.978-0.005); event.weight *= 0.978; }
            if( 1500 < Tot_P && Tot_P <= 3500){ event.set(h_muonrecSF_nominal, 0.9); event.set(h_muonrecSF_up, 0.9+0.2); event.set(h_muonrecSF_down, 0.9-0.2); event.weight *= 0.9; }
        }
    }
    if(year == Year::isUL17){
        if( abs(event.muons->at(0).eta()) <= 1.6){ 
            if( 50 < Tot_P && Tot_P <= 100)   { event.set(h_muonrecSF_nominal, 0.9938); event.set(h_muonrecSF_up, 0.9938+0.0006); event.set(h_muonrecSF_down, 0.9938-0.0006); event.weight *= 0.9938; }
            if( 100 < Tot_P && Tot_P <= 150)  { event.set(h_muonrecSF_nominal, 0.9950); event.set(h_muonrecSF_up, 0.9950+0.0007); event.set(h_muonrecSF_down, 0.9950-0.0007); event.weight *= 0.9950; }
            if( 150 < Tot_P && Tot_P <= 200)  { event.set(h_muonrecSF_nominal, 0.996); event.set(h_muonrecSF_up, 0.996+0.001); event.set(h_muonrecSF_down, 0.996-0.001); event.weight *= 0.996; }
            if( 200 < Tot_P && Tot_P <= 300)  { event.set(h_muonrecSF_nominal, 0.996); event.set(h_muonrecSF_up, 0.996+0.001); event.set(h_muonrecSF_down, 0.996-0.001); event.weight *= 0.996; }
            if( 300 < Tot_P && Tot_P <= 400)  { event.set(h_muonrecSF_nominal, 0.994); event.set(h_muonrecSF_up, 0.994+0.001); event.set(h_muonrecSF_down, 0.994-0.001); event.weight *= 0.994; }
            if( 400 < Tot_P && Tot_P <= 600)  { event.set(h_muonrecSF_nominal, 1.003); event.set(h_muonrecSF_up, 1.003+0.006); event.set(h_muonrecSF_down, 1.003-0.006); event.weight *= 1.003; }
            if( 600 < Tot_P && Tot_P <= 1500) { event.set(h_muonrecSF_nominal, 0.987); event.set(h_muonrecSF_up, 0.987+0.003); event.set(h_muonrecSF_down, 0.987-0.003); event.weight *= 0.987; }
            if( 1500 < Tot_P && Tot_P <= 3500){ event.set(h_muonrecSF_nominal, 0.9); event.set(h_muonrecSF_up, 0.9+0.1); event.set(h_muonrecSF_down, 0.9-0.1); event.weight *= 0.9; }
        }
        if(abs(event.muons->at(0).eta()) > 1.6 && abs(event.muons->at(0).eta()) < 2.4){ 
            if( 50 < Tot_P && Tot_P <= 100)   { event.set(h_muonrecSF_nominal, 1.0); event.set(h_muonrecSF_up, 1.0); event.set(h_muonrecSF_down, 1.0); event.weight *= 1.0; }
            if( 100 < Tot_P && Tot_P <= 150)  { event.set(h_muonrecSF_nominal, 0.993); event.set(h_muonrecSF_up, 0.993+0.001); event.set(h_muonrecSF_down, 0.993-0.001); event.weight *= 0.993; }
            if( 150 < Tot_P && Tot_P <= 200)  { event.set(h_muonrecSF_nominal, 0.989); event.set(h_muonrecSF_up, 0.989+0.001); event.set(h_muonrecSF_down, 0.989-0.001); event.weight *= 0.989; }
            if( 200 < Tot_P && Tot_P <= 300)  { event.set(h_muonrecSF_nominal, 0.986); event.set(h_muonrecSF_up, 0.986+0.001); event.set(h_muonrecSF_down, 0.986-0.001); event.weight *= 0.986; }
            if( 300 < Tot_P && Tot_P <= 400)  { event.set(h_muonrecSF_nominal, 0.989); event.set(h_muonrecSF_up, 0.989+0.001); event.set(h_muonrecSF_down, 0.989-0.001); event.weight *= 0.989; }
            if( 400 < Tot_P && Tot_P <= 600)  { event.set(h_muonrecSF_nominal, 0.983); event.set(h_muonrecSF_up, 0.983+0.003); event.set(h_muonrecSF_down, 0.983-0.003); event.weight *= 0.983; }
            if( 600 < Tot_P && Tot_P <= 1500) { event.set(h_muonrecSF_nominal, 0.986); event.set(h_muonrecSF_up, 0.986+0.006); event.set(h_muonrecSF_down, 0.986-0.006); event.weight *= 0.986; }
            if( 1500 < Tot_P && Tot_P <= 3500){ event.set(h_muonrecSF_nominal, 1.01); event.set(h_muonrecSF_up, 1.01+0.01); event.set(h_muonrecSF_down, 1.01-0.01); event.weight *= 1.01; }
        }
    }
    if(year == Year::isUL18){
        if( abs(event.muons->at(0).eta()) <= 1.6){ 
            if( 50 < Tot_P && Tot_P <= 100)   { event.set(h_muonrecSF_nominal, 0.9943); event.set(h_muonrecSF_up, 0.9943+0.0007); event.set(h_muonrecSF_down, 0.9943-0.0007); event.weight *= 0.9943; }
            if( 100 < Tot_P && Tot_P <= 150)  { event.set(h_muonrecSF_nominal, 0.9948); event.set(h_muonrecSF_up, 0.9948+0.0007); event.set(h_muonrecSF_down, 0.9948-0.0007); event.weight *= 0.9948; }
            if( 150 < Tot_P && Tot_P <= 200)  { event.set(h_muonrecSF_nominal, 0.9950); event.set(h_muonrecSF_up, 0.9950+0.0009); event.set(h_muonrecSF_down, 0.9950-0.0009); event.weight *= 0.9950; }
            if( 200 < Tot_P && Tot_P <= 300)  { event.set(h_muonrecSF_nominal, 0.994); event.set(h_muonrecSF_up, 0.994+0.001); event.set(h_muonrecSF_down, 0.994-0.001); event.weight *= 0.994; }
            if( 300 < Tot_P && Tot_P <= 400)  { event.set(h_muonrecSF_nominal, 0.9914); event.set(h_muonrecSF_up, 0.9914+0.0009); event.set(h_muonrecSF_down, 0.9914-0.0009); event.weight *= 0.9914; }
            if( 400 < Tot_P && Tot_P <= 600)  { event.set(h_muonrecSF_nominal, 0.993); event.set(h_muonrecSF_up, 0.993+0.002); event.set(h_muonrecSF_down, 0.993-0.002); event.weight *= 0.993; }
            if( 600 < Tot_P && Tot_P <= 1500) { event.set(h_muonrecSF_nominal, 0.991); event.set(h_muonrecSF_up, 0.991+0.004); event.set(h_muonrecSF_down, 0.991-0.004); event.weight *= 0.991; }
            if( 1500 < Tot_P && Tot_P <= 3500){ event.set(h_muonrecSF_nominal, 1.0); event.set(h_muonrecSF_up, 1.0+0.1); event.set(h_muonrecSF_down, 1.0-0.1); event.weight *= 1.0; }
        }
        if(abs(event.muons->at(0).eta()) > 1.6 && abs(event.muons->at(0).eta()) < 2.4){ 
            if( 50 < Tot_P && Tot_P <= 100)   { event.set(h_muonrecSF_nominal, 1.0); event.set(h_muonrecSF_up, 1.0); event.set(h_muonrecSF_down, 1.0); event.weight *= 1.0; }
            if( 100 < Tot_P && Tot_P <= 150)  { event.set(h_muonrecSF_nominal, 0.993); event.set(h_muonrecSF_up, 0.993+0.001); event.set(h_muonrecSF_down, 0.993-0.001); event.weight *= 0.993; }
            if( 150 < Tot_P && Tot_P <= 200)  { event.set(h_muonrecSF_nominal, 0.990); event.set(h_muonrecSF_up, 0.990+0.001); event.set(h_muonrecSF_down, 0.990-0.001); event.weight *= 0.990; }
            if( 200 < Tot_P && Tot_P <= 300)  { event.set(h_muonrecSF_nominal, 0.988); event.set(h_muonrecSF_up, 0.988+0.001); event.set(h_muonrecSF_down, 0.988-0.001); event.weight *= 0.988; }
            if( 300 < Tot_P && Tot_P <= 400)  { event.set(h_muonrecSF_nominal, 0.981); event.set(h_muonrecSF_up, 0.981+0.002); event.set(h_muonrecSF_down, 0.981-0.002); event.weight *= 0.981; }
            if( 400 < Tot_P && Tot_P <= 600)  { event.set(h_muonrecSF_nominal, 0.983); event.set(h_muonrecSF_up, 0.983+0.003); event.set(h_muonrecSF_down, 0.983-0.003); event.weight *= 0.983; }
            if( 600 < Tot_P && Tot_P <= 1500) { event.set(h_muonrecSF_nominal, 0.978); event.set(h_muonrecSF_up, 0.978+0.006); event.set(h_muonrecSF_down, 0.978-0.006); event.weight *= 0.978; }
            if( 1500 < Tot_P && Tot_P <= 3500){ event.set(h_muonrecSF_nominal, 0.98); event.set(h_muonrecSF_up, 0.98+0.03); event.set(h_muonrecSF_down, 0.98-0.03); event.weight *= 0.98; }
        }
    }
  }


  return true;
}

