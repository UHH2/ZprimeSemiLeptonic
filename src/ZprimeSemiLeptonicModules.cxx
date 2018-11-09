#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/core/include/LorentzVector.h>
#include <UHH2/core/include/Utils.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

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

ZprimeCandidateBuilder::ZprimeCandidateBuilder(uhh2::Context& ctx, float minDR) : minDR_(minDR){

  h_ZprimeCandidates_ = ctx.declare_event_output< vector<ZprimeCandidate> >("ZprimeCandidates");
  h_AK8TopTags = ctx.get_handle<std::vector<TopJet>>("AK8PuppiTopTags");

}

bool ZprimeCandidateBuilder::process(uhh2::Event& event){
  assert(event.jets);
  assert(event.met);


  // Declare output
  vector<ZprimeCandidate> candidates;

  // Find primary lepton
  FlavorParticle lepton = find_primary_lepton(event);

  // Reconstruct neutrino
  vector<LorentzVector> neutrinos = reconstruct_neutrino(lepton.v4(), event.met->v4());

  // Build all necessary loops
  vector<TopJet> TopTags = event.get(h_AK8TopTags);
  if(TopTags.size() < 1){ // AK4 reconstruction

    unsigned int njets = event.jets->size();
    if(njets > 7) njets = 7;

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
        candidates.emplace_back(move(candidate));
      }
    }
  }
  else{ // TopTag reconstruction
    for(const auto & neutrino_v4 : neutrinos) {
      for (unsigned int j=0; j < TopTags.size(); j++) {

        // Find matched AK8CHS jet
        TopJet chsjet_matched;
        const TopJet* chsjet_matched_ptr;
        for(const TopJet & chsjet : *event.topjets){
          double dR = uhh2::deltaR(chsjet, TopTags.at(j));
          chsjet_matched = chsjet;
          chsjet_matched_ptr = &chsjet;
          if(!(dR < 1.0)) continue;

          //only consider CHS jets not overlapping with the primary lepton
          if(!(deltaR(lepton, chsjet) > 0.8)) continue;

          // Only consider well-separated AK4 jets
          vector<Jet> separated_jets;
          for(unsigned int k = 0; k < event.jets->size(); k++){
            if(deltaR(event.jets->at(k), chsjet_matched) > minDR_) separated_jets.emplace_back(event.jets->at(k));
          }
          unsigned int njets = separated_jets.size();
          if(njets > 7) njets = 7;

          unsigned int jetiters = pow(2, njets);
          for (unsigned int k=0; k < jetiters; k++) {

            LorentzVector tophadv4 = chsjet_matched.v4();
            vector<Particle> tophadjets;
            tophadjets.emplace_back(chsjet_matched);
            LorentzVector toplepv4 = lepton.v4() + neutrino_v4;
            vector<Particle> toplepjets;
            int num = k;
            ZprimeCandidate candidate;
            candidate.set_is_toptag_reconstruction(true);

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
            candidate.set_tophad_topjet_ptr(chsjet_matched_ptr);
            candidate.set_lepton(lepton);
            candidates.emplace_back(candidate);

          }
        }
      }
    }
  }
  // Set the handle with all candidates
  event.set(h_ZprimeCandidates_, candidates);

  return true;
}

ZprimeChi2Discriminator::ZprimeChi2Discriminator(uhh2::Context& ctx){

  h_ZprimeCandidates_ = ctx.get_handle< std::vector<ZprimeCandidate> >("ZprimeCandidates");
  h_is_zprime_reconstructed_ = ctx.get_handle< bool >("is_zprime_reconstructed");
  h_BestCandidate_ = ctx.get_handle<ZprimeCandidate>("ZprimeCandidateBestChi2");

  mtophad_ = 177.;
  mtophad_ttag_ = 173.;
  sigmatophad_ = 16.;
  sigmatophad_ttag_ = 15.;
  mtoplep_ = 175.;
  mtoplep_ttag_ = 175.;
  sigmatoplep_ = 19.;
  sigmatoplep_ttag_ = 19.;
}

bool ZprimeChi2Discriminator::process(uhh2::Event& event){

  vector<ZprimeCandidate>& candidates = event.get(h_ZprimeCandidates_);
  if(candidates.size() < 1) return false;
  // for(unsigned int i=0; i<event.topjets->size(); i++) cout << "Zprime: This topjet has mass: " << event.topjets->at(i).softdropmass() << endl;

  float chi2_best = 99999999;
  ZprimeCandidate bestCand;
  for(unsigned int i=0; i<candidates.size(); i++){
    bool is_toptag_reconstruction = candidates.at(i).is_toptag_reconstruction();

    float chi2_had = 0.;
    float chi2_lep = 0.;
    float mhad = 0.;
    float mlep = 0.;
    if(is_toptag_reconstruction){

      mhad = candidates.at(i).tophad_topjet_ptr()->softdropmass();
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
      bestCand = candidates.at(i);
    }
  }
  event.set(h_BestCandidate_, bestCand);
  event.set(h_is_zprime_reconstructed_, true);
  return true;
}

AK8PuppiTopTagger::AK8PuppiTopTagger(uhh2::Context& ctx, int min_num_daughters, float max_dR, float min_mass, float max_mass, float max_tau32) : min_num_daughters_(min_num_daughters), max_dR_(max_dR), min_mass_(min_mass), max_mass_(max_mass), max_tau32_(max_tau32) {

  h_AK8PuppiTopTags_ = ctx.declare_event_output< std::vector<TopJet> >("AK8PuppiTopTags");

}

bool AK8PuppiTopTagger::process(uhh2::Event& event){

  std::vector<TopJet> toptags;
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

    // 2) Jet should be matched to AK8CHS jet
    double dRmin_CHS = 99999;
    for(const TopJet & chsjet : *event.topjets){
      double dR = uhh2::deltaR(chsjet, puppijet);
      if(dR < dRmin_CHS) dRmin_CHS = dR;
    }
    if(!(dRmin_CHS < max_dR_)) continue;



    // Must have at least one AK4 jet with dR > 1.2
    bool has_separated_jet = false;
    float max_dr = 0.;
    for(unsigned int k = 0; k < event.jets->size(); k++){
      if(deltaR(event.jets->at(k), puppijet) > 1.2){
        has_separated_jet = true;
      }
      if(deltaR(event.jets->at(k), puppijet) > max_dr) max_dr = deltaR(event.jets->at(k), puppijet);
    }
    if(!has_separated_jet) continue;

    // 3) Cut on SD mass
    LorentzVector SumSubjets(0.,0.,0.,0.);
    for(unsigned int k=0; k<puppijet.subjets().size(); k++) SumSubjets = SumSubjets + puppijet.subjets().at(k).v4();
    float mSD = SumSubjets.M();
    if(!(min_mass_ < mSD && mSD < max_mass_)) continue;

    // 4) Cut on tau 3/2
    if(!((puppijet.tau3() / puppijet.tau2()) < max_tau32_)) continue;

    // All jets at this point are top-tagged
    toptags.emplace_back(puppijet);
  }
  event.set(h_AK8PuppiTopTags_, toptags);
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
////

TopTagID_SoftDrop::TopTagID_SoftDrop(const std::string& wp_key){

  if     (wp_key == "mr001_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .44; sjbtag_min_ = -1.; }
  else if(wp_key == "mr001_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .54; sjbtag_min_ = .79; }
  else if(wp_key == "mr003_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .50; sjbtag_min_ = -1.; }
  else if(wp_key == "mr003_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .61; sjbtag_min_ = .76; }
  //else if(wp_key == "mr010_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .59; sjbtag_min_ = -1.; }
  else if(wp_key == "mr010_wp1"){ mass_min_ = 105.; mass_max_ = 210.; tau32_max_ = .65; sjbtag_min_ = -1.; }
  else if(wp_key == "mr030_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .69; sjbtag_min_ = -1.; }
  else if(wp_key == "mr010_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .69; sjbtag_min_ = .66; }
  else if(wp_key == "mr030_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .75; sjbtag_min_ = .39; }
  else if(wp_key == "mr100_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .86; sjbtag_min_ = -1.; }
  else if(wp_key == "mr100_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .87; sjbtag_min_ =.089; }

  else throw std::runtime_error("TopTagID_SoftDrop -- undefined key for working-point: "+wp_key);

  cut_mass_       = true;
  cut_tau32_      = true;
  cut_subjetbtag_ = true;
  // verbose_        = false;
  verbose_        = false;
}

bool TopTagID_SoftDrop::operator()(const TopJet& tj, const uhh2::Event& event) const {


  // float mindR = 9999.0;
  TopJet MatchedPuppiJet;
  TLorentzVector PuppiJetv4;
  TLorentzVector TopJetv4;
  TopJetv4.SetPtEtaPhiE(tj.pt(),tj.eta(),tj.phi(),tj.energy());
  for(const auto & pjet : *event.toppuppijets) {
    int n_constit = 0;
    // Loop over subjets' constituents
    for(unsigned int i=0; i<pjet.subjets().size(); i++){
      n_constit += pjet.subjets().at(i).numberOfDaughters();
    }
    if(pjet.numberOfDaughters() > (int)pjet.subjets().size()){
      n_constit += (pjet.numberOfDaughters() - pjet.subjets().size());
    }

    if(n_constit<2){
      continue;   //TEST: skip PUPPI jet if it contains only one daughter
    }
    PuppiJetv4.SetPtEtaPhiE(pjet.pt(),pjet.eta(),pjet.phi(),pjet.energy());
    float dR = TopJetv4.DeltaR(PuppiJetv4);
    if(dR > 1.0){
      continue;
    }

    TLorentzVector SoftDropv4(0,0,0,0);
    for(const auto & subjet : pjet.subjets()) {
      TLorentzVector SubJetv4;
      SubJetv4.SetPtEtaPhiE(subjet.pt(),subjet.eta(),subjet.phi(),subjet.energy());
      SoftDropv4 = SoftDropv4 + SubJetv4;
    }


    const bool pass_mass = (mass_min_ < SoftDropv4.M()) && (SoftDropv4.M() < mass_max_);
    if(cut_mass_ && !pass_mass){
      continue;
    }

    const bool pass_tau32 = (pjet.tau2()>0) && (pjet.tau3() < tau32_max_*pjet.tau2());
    if(cut_tau32_ && !pass_tau32){
      continue;
    }

    // All puppijets at this point are top-tagged, so the matching CHS jet is top-tagged as well
    return true;
  }
  return false;

}
////
///SoftDrop CHS
TopTagID_SoftDropCHS::TopTagID_SoftDropCHS(const std::string& wp_key){

  if     (wp_key == "mr001_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .44; sjbtag_min_ = -1.; }
  else if(wp_key == "mr001_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .54; sjbtag_min_ = .79; }
  else if(wp_key == "mr003_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .50; sjbtag_min_ = -1.; }
  else if(wp_key == "mr003_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .61; sjbtag_min_ = .76; }
  //else if(wp_key == "mr010_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .59; sjbtag_min_ = -1.; }
  else if(wp_key == "mr010_wp1"){ mass_min_ = 105.; mass_max_ = 210.; tau32_max_ = .65; sjbtag_min_ = -1.; }
  else if(wp_key == "mr030_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .69; sjbtag_min_ = -1.; }
  else if(wp_key == "mr010_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .69; sjbtag_min_ = .66; }
  else if(wp_key == "mr030_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .75; sjbtag_min_ = .39; }
  else if(wp_key == "mr100_wp1"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .86; sjbtag_min_ = -1.; }
  else if(wp_key == "mr100_wp2"){ mass_min_ = 110.; mass_max_ = 210.; tau32_max_ = .87; sjbtag_min_ =.089; }

  else throw std::runtime_error("TopTagID_SoftDrop -- undefined key for working-point: "+wp_key);

  cut_mass_       = true;
  cut_tau32_      = true;
  cut_subjetbtag_ = true;
  verbose_        = false;
  //  verbose_        = true;
}

bool TopTagID_SoftDropCHS::operator()(const TopJet& tj, const uhh2::Event& event) const {

  float mindR = 9999.0;
  TopJet MatchedPuppiJet;
  TLorentzVector PuppiJetv4;
  TLorentzVector TopJetv4;
  TopJetv4.SetPtEtaPhiE(tj.pt(),tj.eta(),tj.phi(),tj.energy());
  if (verbose_) {
    std::cout<<"Top jet SoftDropCHS with pt = "<<tj.pt()<<" eta = "<<tj.eta()<<std::endl;
  }
  for(const auto & pjet : *event.topjets) {
    //    if(pjet.numberOfDaughters()<2) continue;   //TEST: skip PUPPI jet if it contains only one daughter
    PuppiJetv4.SetPtEtaPhiE(pjet.pt(),pjet.eta(),pjet.phi(),pjet.energy());
    if (verbose_) {
      std::cout << "pt: " << pjet.pt()<<" eta: "<<pjet.eta() << std::endl;
    }
    float dR = TopJetv4.DeltaR(PuppiJetv4);
    if (dR < mindR) {
      MatchedPuppiJet = pjet;
      mindR = dR;
    }
  }

  if (verbose_) {
    std::cout << "DeltaR Min: " << mindR << std::endl;
    std::cout << "pt: " << MatchedPuppiJet.pt()<<" eta: "<<MatchedPuppiJet.eta() << std::endl;
    std::cout << "Tau2: " << MatchedPuppiJet.tau2() << std::endl;
    std::cout << "Tau3: " << MatchedPuppiJet.tau3() << std::endl;
    std::cout << "Tau3/2: " << MatchedPuppiJet.tau3()/MatchedPuppiJet.tau2() << std::endl;
    std::cout << "Num Subjets: " << MatchedPuppiJet.numberOfDaughters() << std::endl;
    std::cout << "tau32_max_: " << tau32_max_ << std::endl;
  }

  //  if (mindR > 0.8) return false;
  if (mindR > 1.0) return false; //sync with all had
  //  if (MatchedPuppiJet.numberOfDaughters() != 2) return false;

  TLorentzVector SoftDropv4(0,0,0,0);
  for(const auto & subjet : MatchedPuppiJet.subjets()) {
    TLorentzVector SubJetv4;
    SubJetv4.SetPtEtaPhiE(subjet.pt(),subjet.eta(),subjet.phi(),subjet.energy());
    SoftDropv4 = SoftDropv4 + SubJetv4;
  }

  if (verbose_) std::cout << "SoftDropMass: " << SoftDropv4.M() << std::endl;

  const bool pass_mass = (mass_min_ < SoftDropv4.M()) && (SoftDropv4.M() < mass_max_);
  if(cut_mass_ && !pass_mass) return false;

  const bool pass_tau32 = (MatchedPuppiJet.tau2()>0) && (MatchedPuppiJet.tau3() < tau32_max_*MatchedPuppiJet.tau2());
  if(cut_tau32_ && !pass_tau32) return false;

  bool pass_sjbtag(false);
  if(sjbtag_min_ == -1.) pass_sjbtag = true;
  else {

    std::vector<Jet> subjets = MatchedPuppiJet.subjets();

    if(!subjets.size()) pass_sjbtag = false;
    else{

      std::sort(subjets.begin(), subjets.end(), [](const Jet& j1, const Jet& j2){return j1.btag_combinedSecondaryVertex() > j2.btag_combinedSecondaryVertex();});
      pass_sjbtag = (subjets.at(0).btag_combinedSecondaryVertex() > sjbtag_min_);
    }
  }
  if(cut_subjetbtag_ && !pass_sjbtag) return false;
  if (verbose_) std::cout << "TopJet passed Top Tagging Criteria" << std::endl;
  if (verbose_) std::cout << " " << std::endl;
  return true;
}
////
