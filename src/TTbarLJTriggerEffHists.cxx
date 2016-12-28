#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJTriggerEffHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/utils.h>

#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/TopJetIds.h>

TTbarLJTriggerEffHists::TTbarLJTriggerEffHists(uhh2::Context& ctx, const std::string& dirname):
  HistsBASE(ctx, dirname){
  init();
}

TTbarLJTriggerEffHists::TTbarLJTriggerEffHists(uhh2::Context& ctx, const std::string& dirname, const TopJetId& ttag_id, const float dr__ttag_jet):
  HistsBASE(ctx, dirname){
  init();
}

void TTbarLJTriggerEffHists::init(){

  book_TH1F("wgt", 120, -6, 6);

  // PV
  book_TH1F("pvN", 60, 0, 60);

  // MUON
  book_TH1F("muoN"                 , 20, 0, 20);

  book_TH1F("muo1__charge"         , 5, -2, 3);
  book_TH1F("muo1__pt"             , 90, 0, 900);
  book_TH1F("muo1__eta"            , 60, -3, 3);
  book_TH1F("muo1__phi"            , 60, -3.15, 3.15);

  book_TH1F("muo2__charge"         , 5, -2, 3);
  book_TH1F("muo2__pt"             , 240, 0, 1200);
  book_TH1F("muo2__eta"            , 60, -3, 3);
  book_TH1F("muo2__phi"            , 60, -3.15, 3.15);
 

  // ELECTRON
  book_TH1F("eleN"                 , 20, 0, 20);
  book_TH1F("ele1__class" , 6, -0.5, 5.5);
  book_TH1F("ele1__charge"         , 5, -2, 3);
  book_TH1F("ele1__pt"             , 90, 0, 900);
  book_TH1F("ele1__ptError"         , 36, 0, 720);
  book_TH1F("ele1__eta"            , 60, -3, 3);
  book_TH1F("ele1__etaError"        , 60, 0, 1.);
  book_TH1F("ele1__phi"            , 60, -3.15, 3.15);
  book_TH1F("ele1__phiError"            , 60, 0, 1.);

  book_TH1F("ele2__class" , 6, -0.5, 5.5);
  book_TH1F("ele2__charge"         , 5, -2, 3);
  book_TH1F("ele2__pt"             , 240, 0, 1200);
  book_TH1F("ele2__ptError" , 36, 0, 720);
  book_TH1F("ele2__eta"            , 60, -3, 3);
  book_TH1F("ele2__etaError" , 60, 0, 1);
  book_TH1F("ele2__phi"            , 60, -3.15, 3.15);
  book_TH1F("ele2__phiError" , 60, 0, 1.);
 
  Double_t xAxis1[11] = {-2.5, -2, -1.566, -1.444, -0.8, 0, 0.8, 1.444, 1.566, 2, 2.5}; 
  Double_t yAxis1[8] = {40, 60, 80, 100, 200, 300, 400, 1000};
  book_TH2F("ele1__eta__pt", 10, xAxis1, 7, yAxis1);
  book_TH2F("ele2__eta__pt", 10, xAxis1, 7, yAxis1);

  Double_t xAxis2[8] = {40, 60, 80, 100, 200, 300, 400, 1000};
  Double_t yAxis2[8] = {40, 60, 80, 100, 200, 300, 400, 1000};
  book_TH2F("jet__jet1pt__jet2pt", 7, xAxis2, 7, yAxis2);
  book_TH2F("jet__ele1pt__jet1pt", 7, yAxis1, 7, xAxis2);
  book_TH2F("jet__jet1eta__jet2eta", 10, xAxis1, 10, xAxis1);



  // JET
  book_TH1F("jetN"              , 20, 0, 20);
 
  book_TH1F("jet1__pt" , 90, 0, 900);
  book_TH1F("jet1__eta", 60, -3, 3);
  book_TH1F("jet1__phi", 60, -3.15, 3.15);
  book_TH1F("jet1__M"  , 360, 0, 360);
  book_TH1F("jet1__CSV", 120, 0, 1.2);

  book_TH1F("jet2__pt" , 90, 0, 900);
  book_TH1F("jet2__eta", 60, -3, 3);
  book_TH1F("jet2__phi", 60, -3.15, 3.15);
  book_TH1F("jet2__M"  , 360, 0, 360);
  book_TH1F("jet2__CSV", 120, 0, 1.2);

  book_TH1F("jet3__pt" , 180,  0, 1800);
  book_TH1F("jet3__eta", 60, -3, 3);
  book_TH1F("jet3__phi", 60, -3.15, 3.15);
  book_TH1F("jet3__M"  , 360, 0, 360);
  book_TH1F("jet3__CSV", 120, 0, 1.2);

  // MET
  book_TH1F("met__pt" , 90, 0, 900);
  book_TH1F("met__phi", 60, -3.15, 3.15);

  return;
}

void TTbarLJTriggerEffHists::fill(const uhh2::Event& event){

  assert(event.pvs && event.muons && event.electrons);
  assert(event.jets && event.met);

  const float weight(event.weight);
  H1("wgt")->Fill(weight);

  // PV
  H1("pvN")->Fill(event.pvs->size(), weight);

  // MUON
  const int muoN(event.muons->size());
  H1("muoN")->Fill(muoN, weight);

  for(int i=0; i<std::min(2, muoN); ++i){

    const Muon& p = event.muons->at(i);

    H1("muo"+std::to_string(i+1)+"__charge")->Fill(p.charge(), weight);
    H1("muo"+std::to_string(i+1)+"__pt")    ->Fill(p.pt()    , weight);
    H1("muo"+std::to_string(i+1)+"__eta")   ->Fill(p.eta()   , weight);
    H1("muo"+std::to_string(i+1)+"__phi")   ->Fill(p.phi()   , weight);

  }

  // ELECTRON
  const int eleN(event.electrons->size());
  H1("eleN")->Fill(eleN, weight);

  for(int i=0; i<std::min(2, eleN); ++i){

    const Electron& p = event.electrons->at(i);

    H1("ele"+std::to_string(i+1)+"__charge")->Fill(p.charge()          , weight);
    H1("ele"+std::to_string(i+1)+"__pt")    ->Fill(p.pt()              , weight);
    H1("ele"+std::to_string(i+1)+"__ptError") ->Fill(p.ptError() , weight);
    H1("ele"+std::to_string(i+1)+"__eta")   ->Fill(p.eta()             , weight);
    H1("ele"+std::to_string(i+1)+"__etaError") ->Fill(p.etaError() , weight);
    H1("ele"+std::to_string(i+1)+"__phi")   ->Fill(p.phi()             , weight);
    H1("ele"+std::to_string(i+1)+"__phiError") ->Fill(p.phiError() , weight);
    H2("ele"+std::to_string(i+1)+"__eta__pt") ->Fill(p.eta(),p.pt(), weight);

    int EMclass= p.Class();
    H1("ele"+std::to_string(i+1)+"__class")->Fill(EMclass, weight);

  }

  // JET
  int jetN(event.jets->size());
 
  for(int i=0; i<jetN; ++i){
    if(i > 2) continue;
    const Jet& p = event.jets->at(i);
    H1("jet"+std::to_string(i+1)+"__pt") ->Fill(p.pt()                          , weight);
    H1("jet"+std::to_string(i+1)+"__eta")->Fill(p.eta()                         , weight);
    H1("jet"+std::to_string(i+1)+"__phi")->Fill(p.phi()                         , weight);
    H1("jet"+std::to_string(i+1)+"__M")  ->Fill(p.v4().M()                      , weight);
    H1("jet"+std::to_string(i+1)+"__CSV")->Fill(p.btag_combinedSecondaryVertex(), weight);
  }

  H1("jetN")              ->Fill(jetN              , weight);
 
  const Jet& p1 = event.jets->at(0); 
  const Jet& p2 = event.jets->at(1);
  H2("jet__jet1pt__jet2pt")->Fill(p1.pt(),p2.pt(),weight);
  H2("jet__jet1eta__jet2eta")->Fill(p1.eta(),p2.eta(),weight);
  if(eleN>0){
    const Electron& plep = event.electrons->at(0);
    H2("jet__ele1pt__jet1pt")->Fill(plep.pt(),p1.pt(),weight);
  }
  // MET
  H1("met__pt") ->Fill(event.met->pt() , weight);
  H1("met__phi")->Fill(event.met->phi(), weight);

  return;
}
