#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHistsSkimming.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/utils.h>

#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/TopJetIds.h>

#include "TH1F.h"
#include "TH2F.h"

using namespace uhh2;
using namespace std;

TTbarLJHistsSkimming::TTbarLJHistsSkimming(uhh2::Context& ctx, const std::string& dirname):
  Hists(ctx, dirname), tjet_ID_(TopTagID_NO()), tjet_minDR_jet_(0.) {

  init();
}

TTbarLJHistsSkimming::TTbarLJHistsSkimming(uhh2::Context& ctx, const std::string& dirname, const TopJetId& ttag_id, const float dr__ttag_jet):
  Hists(ctx, dirname), tjet_ID_(ttag_id), tjet_minDR_jet_(dr__ttag_jet) {

  init();
}

void TTbarLJHistsSkimming::init(){

  wgt = book<TH1F>("wgt","weight",120, -6, 6);

  // PV
  pvN = book<TH1F>("pvN","N_{PV}", 60, 0, 60);

  // MUON
  muoN = book<TH1F>("muoN", "N mouns"               , 20, 0, 20);
  muo1__charge = book<TH1F>("muo1__charge","muon charge"        , 5, -2, 3);
  muo1__pt = book<TH1F>("muo1__pt","muon p_{T} [GeV]"            , 90, 0, 900);
  muo1__eta = book<TH1F>("muo1__eta","muon #eta"            ,60,-3,3);
  muo1__phi = book<TH1F>("muo1__phi","muon #phi"           , 60, -3.15, 3.15);
  muo1__minDR_jet = book<TH1F>("muo1__minDR_jet", "#Delta R_{min}(#mu,jet)"     , 60, 0, 6);
  muo1__pTrel_jet = book<TH1F>("muo1__pTrel_jet", "p_{T,rel}(#mu,jet) [GeV]"    , 100, 0, 500);

  muo2__charge = book<TH1F>("muo2__charge","muon charge"         , 5, -2, 3);
  muo2__pt = book<TH1F>("muo2__pt","muon p_{T}[GeV]"             , 90, 0, 900);
  muo2__eta = book<TH1F>("muo2__eta","muon #eta"            ,60,-3,3);
  muo2__phi = book<TH1F>("muo2__phi","muon #phi"            , 60, -3.15, 3.15);
  muo2__minDR_jet = book<TH1F>("muo2__minDR_jet", "#Delta R_{min}(#mu,jet)"      , 60, 0, 6);
  muo2__pTrel_jet = book<TH1F>("muo2__pTrel_jet", "p_{T,rel}(#mu,jet) [GeV]"      , 100, 0, 500);

  // ELECTRON
  eleN = book<TH1F>("eleN", "N electrons"               , 20, 0, 20);
  ele1__class = book<TH1F>("ele1__class", "electron class" , 6, -0.5, 5.5);
  ele1__charge = book<TH1F>("ele1__charge", "electron charge"         , 5, -2, 3);
  ele1__pt = book<TH1F>("ele1__pt", "electron p_{T} [GeV]"             , 90, 0, 900);
  ele1__ptError = book<TH1F>("ele1__ptError","electron #sigma(p_{T}) [GeV]"         , 36, 0, 720);
  ele1__eta = book<TH1F>("ele1__eta","electron #eta"            ,60,-3,3);
  ele1__etaError = book<TH1F>("ele1__etaError","electron #sigma(#eta)"        , 60, 0, 1.);
  ele1__phi = book<TH1F>("ele1__phi", "electron #phi"            , 60, -3.15, 3.15);
  ele1__phiError = book<TH1F>("ele1__phiError", "electron #sigma(#phi)"            , 60, 0, 1.);
  ele1__minDR_jet = book<TH1F>("ele1__minDR_jet","#Delta R_{min}(e,jet)"      , 60, 0, 6);
  ele1__pTrel_jet = book<TH1F>("ele1__pTrel_jet", "p_{T,rel}(e,jet)[GeV]"     , 100, 0, 500);

  ele2__class = book<TH1F>("ele2__class", "electron class" , 6, -0.5, 5.5);
  ele2__charge = book<TH1F>("ele2__charge", "electron charge"         , 5, -2, 3);
  ele2__pt = book<TH1F>("ele2__pt", "electron p_{T} [GeV]"             , 240, 0, 1200);
  ele2__ptError = book<TH1F>("ele2__ptError","electron #sigma(p_{T}) [GeV]"  , 36, 0, 720);
  ele2__eta = book<TH1F>("ele2__eta", "electron #eta"            ,60,-3,3);
  ele2__etaError = book<TH1F>("ele2__etaError","electron #sigma(#eta)" , 60, 0, 1);
  ele2__phi = book<TH1F>("ele2__phi", "electron #phi"           , 60, -3.15, 3.15);
  ele2__phiError = book<TH1F>("ele2__phiError", "electron #sigma(#phi)" , 60, 0, 1.);
  ele2__minDR_jet = book<TH1F>("ele2__minDR_jet","#Delta R_{min}(e,jet)"      , 60, 0, 6);
  ele2__pTrel_jet = book<TH1F>("ele2__pTrel_jet", "p_{T,rel}(e,jet)[GeV]"      , 100, 0, 500);

  // JET
  jetN = book<TH1F>("jetN", "N jets"              , 20, 0, 20);
  jetN__CSVL = book<TH1F>("jetN__CSVL","N jets with Loose CSV"        , 10, 0, 10);
  jetN__CSVM = book<TH1F>("jetN__CSVM","N jets with Medium CSV"        , 10, 0, 10);
  jetN__CSVT = book<TH1F>("jetN__CSVT", "N jets with Tight CSV"        , 10, 0, 10);

  jet1__pt = book<TH1F>("jet1__pt", "jet p_{T} [GeV]" , 100, 0, 1500);
  jet1__eta = book<TH1F>("jet1__eta", "jet #eta",60,-3,3);
  jet1__phi = book<TH1F>("jet1__phi", "jet #phi", 60, -3.15, 3.15);
  jet1__M = book<TH1F>("jet1__M", "jet mass"  , 360, 0, 360);
  jet1__CSV = book<TH1F>("jet1__CSV","CSV", 60, 0, 1.2);

  jet2__pt = book<TH1F>("jet2__pt", "jet p_{T} [GeV]" , 100, 0, 1500);
  jet2__eta = book<TH1F>("jet2__eta", "jet #eta",60,-3,3);
  jet2__phi = book<TH1F>("jet2__phi", "jet #phi", 60, -3.15, 3.15);
  jet2__M = book<TH1F>("jet2__M", "jet mass [GeV]"  , 360, 0, 360);
  jet2__CSV = book<TH1F>("jet2__CSV","CSV", 60, 0, 1.2);

  jet3__pt = book<TH1F>("jet3__pt", "jet p_{T}[GeV]" , 50, 200, 1700);
  jet3__eta = book<TH1F>("jet3__eta", "jet #eta",60,-3,3);
  jet3__phi = book<TH1F>("jet3__phi", "jet #phi", 60, -3.15, 3.15);
  jet3__M = book<TH1F>("jet3__M", "jet mass"  , 360, 0, 360);
  jet3__CSV = book<TH1F>("jet3__CSV","CSV", 60, 0, 1.2);

  // TOPJET
  topjetN = book<TH1F>("topjetN","N topjets", 10, 0, 10);

  topjet1__pt = book<TH1F>("topjet1__pt","topjet p_{T} [GeV]" , 50, 200, 1700);
  topjet1__eta = book<TH1F>("topjet1__eta","topjet #eta", 30, -3, 3);
  topjet1__phi = book<TH1F>("topjet1__phi","topjet #phi", 30, -3.15, 3.15);
  topjet1__CSV = book<TH1F>("topjet1__CSV", "topjet CSV", 30, 0, 1.2);
  topjet1__Msdp = book<TH1F>("topjet1__Msdp","topjet softdrop mass [GeV]", 35, 0, 350);
  topjet1__tau32 = book<TH1F>("topjet1__tau32","jet #tau_{32}", 24, 0, 1.2);
  topjet2__pt = book<TH1F>("topjet2__pt","topjet p_{T} [GeV]" , 50, 200, 1700);
  topjet2__eta = book<TH1F>("topjet2__eta","topjet #eta", 30, -3, 3);
  topjet2__phi = book<TH1F>("topjet2__phi","topjet #phi", 30, -3.15, 3.15);
  topjet2__CSV = book<TH1F>("topjet2__CSV", "topjet CSV", 30, 0, 1.2);
  topjet2__Msdp = book<TH1F>("topjet2__Msdp","topjet softdrop mass [GeV]", 35, 0, 350);
  topjet2__tau32 = book<TH1F>("topjet2__tau32","topjet #tau_{32}", 24, 0, 1.2);



  // TOPTAG
  toptagN = book<TH1F>("toptagN","N top-tagged jets"              , 10, 0, 10);

 
  toptag1__pt = book<TH1F>("toptag1__pt","top-tag jet p_{T} [GeV]"          , 50, 200, 1700);
  toptag1__eta = book<TH1F>("toptag1__eta", "top-tag jet #eta"         , 30, -3, 3);
  toptag1__phi = book<TH1F>("toptag1__phi","top-tag jet #phi"         , 30, -3.15, 3.15);
  toptag1__M  = book<TH1F>("toptag1__M", "top-tag jet mass [GeV]"           , 360, 90, 450);
  toptag1__Mgro = book<TH1F>("toptag1__Mgro", "top-tag jet groomed mass [GeV]"        , 35, 0, 350);
  toptag1__Mpru  = book<TH1F>("toptag1__Mpru", "top-tag jet pruned mass [GeV]"        , 35, 0, 350);
  toptag1__Msdp  = book<TH1F>("toptag1__Msdp", "top-tag jet softdrop mass [GeV]"        , 35, 0, 350);
  toptag1__tau32  = book<TH1F>("toptag1__tau32", "top-tag jet #tau_{32}"       , 24, 0, 1.2);
  toptag1__CSV  = book<TH1F>("toptag1__CSV","top-tag jet CSV"        , 60, 0, 1.2);
  toptag1__subjN  = book<TH1F>("toptag1__subjN", "top-tag jet N subjettiness"       , 4, 2, 6);

   toptag2__pt = book<TH1F>("toptag2__pt","top-tag jet p_{T} [GeV]"          , 50, 200, 1700);
  toptag2__eta = book<TH1F>("toptag2__eta", "top-tag jet #eta"         , 30, -3, 3);
  toptag2__phi = book<TH1F>("toptag2__phi","top-tag jet #phi"         , 30, -3.15, 3.15);
  toptag2__M  = book<TH1F>("toptag2__M", "top-tag jet mass [GeV]"           , 360, 90, 450);
  toptag2__Mgro = book<TH1F>("toptag2__Mgro", "top-tag jet groomed mass [GeV]"        , 35, 0, 350);
  toptag2__Mpru  = book<TH1F>("toptag2__Mpru", "top-tag jet pruned mass [GeV]"        , 35, 0, 350);
  toptag2__Msdp  = book<TH1F>("toptag2__Msdp", "top-tag jet softdrop mass [GeV]"        , 35, 0, 350);
  toptag2__tau32  = book<TH1F>("toptag2__tau32", "top-tag jet #tau_{32}"       , 24, 0, 1.2);
  toptag2__CSV  = book<TH1F>("toptag2__CSV","top-tag jet CSV"        , 60, 0, 1.2);
  toptag2__subjN  = book<TH1F>("toptag2__subjN", "top-tag jet N subjettiness"       , 4, 2, 6);

  // MET
  met__pt = book<TH1F>("met__pt", "MET [GeV]" , 60, 0, 800);
  met__phi = book<TH1F>("met__phi", "MET #phi", 60, -3.15, 3.15);
  wlep__ht = book<TH1F>("wlep__ht","W_{leptonic} H_{T} [GeV]", 90, 0, 900);
  wlep__pt = book<TH1F>("wlep__pt","W_{leptonic} p_{T} [GeV]", 90, 0, 900);
  wlep__Mt = book<TH1F>("wlep__Mt","W_{leptonic} M_{T} [GeV]", 360, 0,  360);
  return ; 
}

void TTbarLJHistsSkimming::fill(const uhh2::Event& event){

  assert(event.pvs && event.muons && event.electrons);
  assert(event.jets && event.topjets && event.met);

  const float weight(event.weight);
  wgt->Fill(weight);

  // PV
  pvN->Fill(event.pvs->size(), weight);

  // MUON
  const int muoN_(event.muons->size());
  muoN->Fill(muoN_, weight);

  for(int i=0; i<std::min(2, muoN_); ++i){

    const Muon& p = event.muons->at(i);
    float minDR_jet(-1.), pTrel_jet(-1.);
    if(p.has_tag(Muon::twodcut_dRmin) && p.has_tag(Muon::twodcut_pTrel)){
      minDR_jet = p.get_tag(Muon::twodcut_dRmin);
      pTrel_jet = p.get_tag(Muon::twodcut_pTrel);
    }
    else std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    if(i==0){
      muo1__charge->Fill(p.charge(), weight);
      muo1__pt->Fill(p.pt()    , weight);
      muo1__eta->Fill(p.eta()   , weight);
      muo1__phi   ->Fill(p.phi()   , weight);
      muo1__minDR_jet->Fill(minDR_jet, weight);
      muo1__pTrel_jet->Fill(pTrel_jet, weight);
    }
    if(i==1){
      muo2__charge->Fill(p.charge(), weight);
      muo2__pt->Fill(p.pt()    , weight);
      muo2__eta->Fill(p.eta()   , weight);
      muo2__phi   ->Fill(p.phi()   , weight);
      muo2__minDR_jet->Fill(minDR_jet, weight);
      muo2__pTrel_jet->Fill(pTrel_jet, weight);
    }
  }

  // ELECTRON
  const int eleN_(event.electrons->size());
  eleN->Fill(eleN_, weight);

  for(int i=0; i<std::min(2, eleN_); ++i){
    const Electron& p = event.electrons->at(i);
    float minDR_jet(-1.), pTrel_jet(-1.);
    if(p.has_tag(Electron::twodcut_dRmin) && p.has_tag(Electron::twodcut_pTrel)){
      minDR_jet = p.get_tag(Electron::twodcut_dRmin);
      pTrel_jet = p.get_tag(Electron::twodcut_pTrel);
    }
    else std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);
    if(i==0){
      ele1__charge->Fill(p.charge()          , weight);
      ele1__pt    ->Fill(p.pt()              , weight);
      ele1__ptError ->Fill(p.ptError() , weight);
      ele1__eta   ->Fill(p.eta()             , weight);
      ele1__etaError ->Fill(p.etaError() , weight);
      ele1__phi   ->Fill(p.phi()             , weight);
      ele1__phiError ->Fill(p.phiError() , weight);
      int EMclass= p.Class();
      ele1__class->Fill(EMclass, weight);
      ele1__minDR_jet->Fill(minDR_jet, weight);
      ele1__pTrel_jet->Fill(pTrel_jet, weight);
    }
    if(i==1){
      ele2__charge->Fill(p.charge()          , weight);
      ele2__pt    ->Fill(p.pt()              , weight);
      ele2__ptError ->Fill(p.ptError() , weight);
      ele2__eta   ->Fill(p.eta()             , weight);
      ele2__etaError ->Fill(p.etaError() , weight);
      ele2__phi   ->Fill(p.phi()             , weight);
      ele2__phiError ->Fill(p.phiError() , weight);
      int EMclass= p.Class();
      ele2__class->Fill(EMclass, weight);
      ele2__minDR_jet->Fill(minDR_jet, weight);
      ele2__pTrel_jet->Fill(pTrel_jet, weight);
    }
 
  }

  // JET
  int jetN_(event.jets->size());

  for(int i=0; i<jetN_; ++i){

    const Jet& p = event.jets->at(i);
    if(i==0){
      jet1__pt ->Fill(p.pt()                          , weight);
      jet1__eta->Fill(p.eta()                         , weight);
      jet1__phi->Fill(p.phi()                         , weight);
      jet1__M  ->Fill(p.v4().M()                      , weight);
      jet1__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    }
    if(i==1){
      jet2__pt ->Fill(p.pt()                          , weight);
      jet2__eta->Fill(p.eta()                         , weight);
      jet2__phi->Fill(p.phi()                         , weight);
      jet2__M  ->Fill(p.v4().M()                      , weight);
      jet2__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    }
    if(i==2){
      jet3__pt ->Fill(p.pt()                          , weight);
      jet3__eta->Fill(p.eta()                         , weight);
      jet3__phi->Fill(p.phi()                         , weight);
      jet3__M  ->Fill(p.v4().M()                      , weight);
      jet3__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    }
  }

  jetN             ->Fill(jetN_              , weight);

  std::vector<float> jets_CSV;
  jets_CSV.reserve(event.jets->size());
  for(const auto& j : *event.jets) jets_CSV.push_back(j.btag_combinedSecondaryVertex());
  std::sort(jets_CSV.begin(), jets_CSV.end(), [](const float s1, const float s2){return s1 > s2;});

  int jetN__CSVL_(0), jetN__CSVM_(0), jetN__CSVT_(0);
  for(unsigned int i=0; i<jets_CSV.size(); ++i){

    const float& csv = jets_CSV.at(i);

    if(csv > 0.605) ++jetN__CSVL_;
    if(csv > 0.890) ++jetN__CSVM_;
    if(csv > 0.970) ++jetN__CSVT_;
  }

  jetN__CSVL->Fill(jetN__CSVL_, weight);
  jetN__CSVM->Fill(jetN__CSVM_, weight);
  jetN__CSVT->Fill(jetN__CSVT_, weight);
  //

  // TOPJET
  const int topjetN_(event.topjets->size());
  topjetN->Fill(topjetN_, weight);

  for(int i=0; i<std::min(2, topjetN_); ++i){

    //    const Jet& p = event.topjets->at(i);
    const TopJet& p = event.topjets->at(i);
    if(i==0){
    topjet1__pt ->Fill(p.pt()                          , weight);
    topjet1__eta->Fill(p.eta()                         , weight);
    topjet1__phi->Fill(p.phi()                         , weight);
    topjet1__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    topjet1__Msdp->Fill(p.softdropmass() , weight);
    topjet1__tau32->Fill(p.tau3()/p.tau2() , weight);
    }
    if(i==1){
    topjet2__pt ->Fill(p.pt()                          , weight);
    topjet2__eta->Fill(p.eta()                         , weight);
    topjet2__phi->Fill(p.phi()                         , weight);
    topjet2__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    topjet2__Msdp->Fill(p.softdropmass() , weight);
    topjet2__tau32->Fill(p.tau3()/p.tau2() , weight);
    }
  }

  // TOPTAG
  std::vector<TopJet> toptags;
  for(unsigned int i=0; i<event.topjets->size(); ++i){

    const TopJet& tjet = event.topjets->at(i);
    if(tjet_ID_(tjet, event)) toptags.push_back(tjet);
  }

  const int toptagN_(toptags.size());
  toptagN->Fill(toptagN_, weight);

  sort_by_pt<TopJet>(toptags);
  for(int i=0; i<std::min(2, toptagN_); ++i){

    const TopJet& tj = toptags.at(i);
    if(i==0){
      toptag1__pt ->Fill(tj.pt()                          , weight);
      toptag1__eta->Fill(tj.eta()                         , weight);
      toptag1__phi->Fill(tj.phi()                         , weight);
      toptag1__M  ->Fill(tj.v4().M()                      , weight);
      toptag1__CSV->Fill(tj.btag_combinedSecondaryVertex(), weight);

      toptag1__Mpru->Fill(tj.prunedmass()   , weight);
      toptag1__Msdp->Fill(tj.softdropmass() , weight);
      if(tj.tau2()) toptag1__tau32->Fill(tj.tau3()/tj.tau2(), weight);
      std::vector<Jet> subjets = tj.subjets();
      const int subjN(subjets.size());
      toptag1__subjN->Fill(subjN, weight);

      float subj_minDR(-1.);
      LorentzVector sum_subj(0, 0, 0, 0);
      for  (int sj1=0    ; sj1<subjN; ++sj1){
        for(int sj2=sj1+1; sj2<subjN; ++sj2){

          const float dR = uhh2::deltaR(subjets.at(sj1), subjets.at(sj2));
          if(dR < subj_minDR || (sj1+sj2==1)) subj_minDR = dR;
        }
        sum_subj += subjets.at(sj1).v4();
      }
      toptag1__Mgro      ->Fill(sum_subj.M(), weight);
    }
    if(i==1){
      toptag2__pt ->Fill(tj.pt()                          , weight);
      toptag2__eta->Fill(tj.eta()                         , weight);
      toptag2__phi->Fill(tj.phi()                         , weight);
      toptag2__M  ->Fill(tj.v4().M()                      , weight);
      toptag2__CSV->Fill(tj.btag_combinedSecondaryVertex(), weight);

      toptag2__Mpru->Fill(tj.prunedmass()   , weight);
      toptag2__Msdp->Fill(tj.softdropmass() , weight);
      if(tj.tau2()) toptag2__tau32->Fill(tj.tau3()/tj.tau2(), weight);
      std::vector<Jet> subjets = tj.subjets();
      const int subjN(subjets.size());
      toptag2__subjN->Fill(subjN, weight);

      float subj_minDR(-1.);
      LorentzVector sum_subj(0, 0, 0, 0);
      for  (int sj1=0    ; sj1<subjN; ++sj1){
        for(int sj2=sj1+1; sj2<subjN; ++sj2){

          const float dR = uhh2::deltaR(subjets.at(sj1), subjets.at(sj2));
          if(dR < subj_minDR || (sj1+sj2==1)) subj_minDR = dR;
        }
        sum_subj += subjets.at(sj1).v4();
      }
      toptag2__Mgro      ->Fill(sum_subj.M(), weight);
    }

  }
      

  // MET
  met__pt->Fill(event.met->pt() , weight);
  met__phi->Fill(event.met->phi(), weight);

  const Particle* lep1(0);
  float max_lep_pt(0.);
  for(const auto& l : *event.muons)     if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }
  for(const auto& l : *event.electrons) if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }

  if(lep1){

    wlep__ht->Fill( event.met->pt()+lep1->pt()      , weight);
    wlep__pt->Fill((event.met->v4()+lep1->v4()).Pt(), weight);
    wlep__Mt->Fill(sqrt(2*event.met->pt()*lep1->pt()*(1.-cos(uhh2::deltaPhi(*event.met, *lep1)))), weight);
  }

  return;
}
