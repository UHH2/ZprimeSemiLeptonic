#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/utils.h>

#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/TopJetIds.h>

TTbarLJHists::TTbarLJHists(uhh2::Context& ctx, const std::string& dirname):
  HistsBASE(ctx, dirname), tjet_ID_(TopTagID_NO()), tjet_minDR_jet_(0.) {

  init();
  tt_tmva_response = ctx.get_handle<float>("TMVA_response");
}

TTbarLJHists::TTbarLJHists(uhh2::Context& ctx, const std::string& dirname, const TopJetId& ttag_id, const float dr__ttag_jet):
  HistsBASE(ctx, dirname), tjet_ID_(ttag_id), tjet_minDR_jet_(dr__ttag_jet) {

  init();
  tt_tmva_response = ctx.get_handle<float>("TMVA_response");
}

void TTbarLJHists::init(){

  book_TH1F("wgt", 120, -6, 6);

  // PV
  book_TH1F("pvN", 120, 0, 120);

  // MUON
  book_TH1F("muoN"                 , 20, 0, 20);

  book_TH1F("muo1__charge"         , 5, -2, 3);
  book_TH1F("muo1__pt"             , 360, 0, 1800);
  book_TH1F("muo1__eta"            , 60, -3, 3);
  book_TH1F("muo1__phi"            , 60, -3.15, 3.15);
  book_TH1F("muo1__pfIso_dbeta"    , 60, 0, 3);
  book_TH1F("muo1__pfMINIIso_dbeta", 60, 0, 3);
  book_TH1F("muo1__pfMINIIso_pfwgt", 60, 0, 3);
  book_TH1F("muo1__minDR_jet"      , 60, 0, 6);
  book_TH1F("muo1__pTrel_jet"      , 100, 0, 500);
  book_TH1F("muo1__minDR_topjet"   , 60, 0, 6);
  book_TH2F("muo1__minDR_jet__vs__muo1__pTrel_jet", 60, 0, 6, 100, 0, 500);
  book_TH2F("muo1__pt__vs__met__pt", 360, 0, 1800, 180, 0, 1800);
  book_TH2F("muo1__pTrel_jet__vs__met__pt", 100, 0, 500, 180, 0, 1800);

  book_TH1F("muo2__charge"         , 5, -2, 3);
  book_TH1F("muo2__pt"             , 240, 0, 1200);
  book_TH1F("muo2__eta"            , 60, -3, 3);
  book_TH1F("muo2__phi"            , 60, -3.15, 3.15);
  book_TH1F("muo2__pfIso_dbeta"    , 60, 0, 3);
  book_TH1F("muo2__pfMINIIso_dbeta", 60, 0, 3);
  book_TH1F("muo2__pfMINIIso_pfwgt", 60, 0, 3);
  book_TH1F("muo2__minDR_jet"      , 60, 0, 6);
  book_TH1F("muo2__pTrel_jet"      , 100, 0, 500);
  book_TH1F("muo2__minDR_topjet"   , 60, 0, 6);
  book_TH2F("muo2__minDR_jet__vs__muo2__pTrel_jet", 60, 0, 6, 100, 0, 500);
  book_TH2F("muo2__pt__vs__met__pt", 360, 0, 1800, 180, 0, 1800);
  book_TH2F("muo2__pTrel_jet__vs__met__pt", 100, 0, 500, 180, 0, 1800);

  // ELECTRON
  book_TH1F("eleN"                 , 20, 0, 20);
  book_TH1F("ele1__etaSC"          , 60, -3, 3);
  book_TH1F("ele1__class" , 6, -0.5, 5.5);
  book_TH1F("ele1__charge"         , 5, -2, 3);
  book_TH1F("ele1__pt"             , 360, 0, 1800);
  book_TH1F("ele1__ptError"         , 36, 0, 720);
  book_TH1F("ele1__eta"            , 60, -3, 3);
  book_TH1F("ele1__etaError"        , 60, 0, 1.);
  book_TH1F("ele1__phi"            , 60, -3.15, 3.15);
  book_TH1F("ele1__phiError"            , 60, 0, 1.);
  book_TH1F("ele1__pfIso_dbeta"    , 60, 0, 3);
  book_TH1F("ele1__pfMINIIso_dbeta", 60, 0, 3);
  book_TH1F("ele1__pfMINIIso_pfwgt", 60, 0, 3);
  book_TH1F("ele1__minDR_jet"      , 60, 0, 6);
  book_TH1F("ele1__pTrel_jet"      , 100, 0, 500);
  book_TH1F("ele1__minDR_topjet"   , 60, 0, 6);
  book_TH2F("ele1__minDR_jet__vs__ele1__pTrel_jet", 60, 0, 6, 100, 0, 500);
  book_TH2F("ele1__pt__vs__met__pt", 360, 0, 1800, 180, 0, 1800);
  book_TH2F("ele1__pTrel_jet__vs__met__pt", 100, 0, 500, 180, 0, 1800);
  

  book_TH1F("ele2__class" , 6, -0.5, 5.5);
  book_TH1F("ele2__etaSC"          , 60, -3, 3);
  book_TH1F("ele2__charge"         , 5, -2, 3);
  book_TH1F("ele2__pt"             , 240, 0, 1200);
  book_TH1F("ele2__ptError" , 36, 0, 720);
  book_TH1F("ele2__eta"            , 60, -3, 3);
  book_TH1F("ele2__etaError" , 60, 0, 1);
  book_TH1F("ele2__phi"            , 60, -3.15, 3.15);
  book_TH1F("ele2__phiError" , 60, 0, 1.);
  book_TH1F("ele2__pfIso_dbeta"    , 60, 0, 3);
  book_TH1F("ele2__pfMINIIso_dbeta", 60, 0, 3);
  book_TH1F("ele2__pfMINIIso_pfwgt", 60, 0, 3);
  book_TH1F("ele2__minDR_jet"      , 60, 0, 6);
  book_TH1F("ele2__pTrel_jet"      , 100, 0, 500);
  book_TH1F("ele2__minDR_topjet"   , 60, 0, 6);
  book_TH2F("ele2__minDR_jet__vs__ele2__pTrel_jet", 60, 0, 6, 100, 0, 500);
  book_TH2F("ele2__pt__vs__met__pt", 360, 0, 1800, 180, 0, 1800);
  book_TH2F("ele2__pTrel_jet__vs__met__pt", 100, 0, 500, 180, 0, 1800);

  // JET
  book_TH1F("jetN"              , 20, 0, 20);
  book_TH1F("jetN__pt030_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt050_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt100_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt150_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt200_eta2p4", 20, 0, 20);
  book_TH1F("jetN__pt250_eta2p4", 20, 0, 20);
  book_TH1F("jetN__CSVL"        , 10, 0, 10);
  book_TH1F("jetN__CSVM"        , 10, 0, 10);
  book_TH1F("jetN__CSVT"        , 10, 0, 10);

  book_TH1F("jetA__maxCSV1", 120, 0, 1.2);
  book_TH1F("jetA__maxCSV2", 120, 0, 1.2);
  book_TH1F("jetA__maxCSV3", 120, 0, 1.2);

  book_TH1F("jet1__pt" , 180, 0, 1800);
  book_TH1F("jet1__eta", 60, -3, 3);
  book_TH1F("jet1__phi", 60, -3.15, 3.15);
  book_TH1F("jet1__M"  , 360, 0, 360);
  book_TH1F("jet1__CSV", 120, 0, 1.2);

  book_TH1F("jet2__pt" , 180, 0, 1800);
  book_TH1F("jet2__eta", 60, -3, 3);
  book_TH1F("jet2__phi", 60, -3.15, 3.15);
  book_TH1F("jet2__M"  , 360, 0, 360);
  book_TH1F("jet2__CSV", 120, 0, 1.2);

  book_TH1F("jet3__pt" , 180,  0, 1800);
  book_TH1F("jet3__eta", 60, -3, 3);
  book_TH1F("jet3__phi", 60, -3.15, 3.15);
  book_TH1F("jet3__M"  , 360, 0, 360);
  book_TH1F("jet3__CSV", 120, 0, 1.2);

  // TOPJET
  book_TH1F("topjetN", 20, 0, 20);

  book_TH1F("topjet1__pt" , 180,  0, 1800);
  book_TH1F("topjet1__eta", 60, -3, 3);
  book_TH1F("topjet1__phi", 60, -3.15, 3.15);
  book_TH1F("topjet1__CSV", 120, 0, 1.2);
  book_TH1F("topjet2__pt" , 180,  0, 1800);
  book_TH1F("topjet2__eta", 60, -3, 3);
  book_TH1F("topjet2__phi", 60, -3.15, 3.15);
  book_TH1F("topjet2__CSV", 120, 0, 1.2);

  // TOPTAG
  book_TH1F("toptagN"              , 20, 0, 20);

  const std::vector<std::string> htags_ETA({"", "_etaLO", "_etaHI"});

  for(const auto& eta : htags_ETA){

    book_TH1F("toptag1"+eta+"__pt"          , 180, 0, 1800);
    book_TH1F("toptag1"+eta+"__eta"         , 60, -3, 3);
    book_TH1F("toptag1"+eta+"__phi"         , 60, -3.15, 3.15);
    book_TH1F("toptag1"+eta+"__M"           , 360, 90, 450);
    book_TH1F("toptag1"+eta+"__Mgro"        , 360, 90, 450);
    book_TH1F("toptag1"+eta+"__Mpru"        , 360, 90, 450);
    book_TH1F("toptag1"+eta+"__Msdp"        , 360, 90, 450);
    book_TH1F("toptag1"+eta+"__mmin"        , 40, 0, 200);
    book_TH1F("toptag1"+eta+"__tau2"        , 24, 0, 1.2);
    book_TH1F("toptag1"+eta+"__tau3"        , 24, 0, 1.2);
    book_TH1F("toptag1"+eta+"__tau32"       , 24, 0, 1.2);
    book_TH1F("toptag1"+eta+"__CSV"         , 120, 0, 1.2);
    book_TH1F("toptag1"+eta+"__subjN"       , 4, 2, 6);
    book_TH1F("toptag1"+eta+"__subj1__pt"   , 180, 0, 1800);
    book_TH1F("toptag1"+eta+"__subj1__eta"  , 60, -3, 3);
    book_TH1F("toptag1"+eta+"__subj2__pt"   , 180, 0, 900);
    book_TH1F("toptag1"+eta+"__subj2__eta"  , 60, -3, 3);
    book_TH1F("toptag1"+eta+"__subj3__pt"   , 180, 0, 900);
    book_TH1F("toptag1"+eta+"__subj3__eta"  , 60, -3, 3);
    book_TH1F("toptag1"+eta+"__subj_minDR"  , 20, 0, 2);
    book_TH1F("toptag1"+eta+"__subj_maxCSV1", 120, 0, 1.2);
    book_TH1F("toptag1"+eta+"__subj_maxCSV2", 120, 0, 1.2);
    book_TH1F("toptag1"+eta+"__subj_maxCSV3", 120, 0, 1.2);
  }

  book_TH1F("toptag2__pt"          , 180, 0, 1800);
  book_TH1F("toptag2__eta"         , 60, -3, 3);
  book_TH1F("toptag2__phi"         , 60, -3.15, 3.15);
  book_TH1F("toptag2__M"           , 360, 90, 450);
  book_TH1F("toptag2__CSV"         , 120, 0, 1.2);

  // MET
  book_TH1F("met__pt" , 180, 0, 1800);
  book_TH1F("met__phi", 60, -3.15, 3.15);
  book_TH1F("wlep__ht", 180, 0, 1800);
  book_TH1F("wlep__pt", 180, 0, 1800);
  book_TH1F("wlep__Mt", 360, 0,  360);
  book_TH2F("met__pt__vs__dphi_met_lep1", 180, 0, 1800, 60, 0, 3.15);
  book_TH2F("met__pt__vs__dphi_met_jet1", 180, 0, 1800, 60, 0, 3.15);

  TMVA_response = book<TH1F>("TMVA_response", "TMVA response", 50,-1.2,1.8);

  return;
}

void TTbarLJHists::fill(const uhh2::Event& event){

  assert(event.pvs && event.muons && event.electrons);
  assert(event.jets && event.topjets && event.met);

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

    H2("muo"+std::to_string(i+1)+"__pt__vs__met__pt")->Fill(p.pt(), event.met->pt(), weight);

    const float pfR040Iso_dbeta = p.relIso();
    const float pfMINIIso_dbeta = util::pfMINIIso(p, "delta-beta");
    const float pfMINIIso_pfwgt = util::pfMINIIso(p, "pf-weight");

    H1("muo"+std::to_string(i+1)+"__pfIso_dbeta")    ->Fill(pfR040Iso_dbeta, weight);
    H1("muo"+std::to_string(i+1)+"__pfMINIIso_dbeta")->Fill(pfMINIIso_dbeta, weight);
    H1("muo"+std::to_string(i+1)+"__pfMINIIso_pfwgt")->Fill(pfMINIIso_pfwgt, weight);

    float minDR_jet(-1.), pTrel_jet(-1.);
    if(p.has_tag(Muon::twodcut_dRmin) && p.has_tag(Muon::twodcut_pTrel)){

      minDR_jet = p.get_tag(Muon::twodcut_dRmin);
      pTrel_jet = p.get_tag(Muon::twodcut_pTrel);
    }
    else std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    H1("muo"+std::to_string(i+1)+"__minDR_jet")->Fill(minDR_jet, weight);
    H1("muo"+std::to_string(i+1)+"__pTrel_jet")->Fill(pTrel_jet, weight);
    H2("muo"+std::to_string(i+1)+"__minDR_jet__vs__muo"+std::to_string(i+1)+"__pTrel_jet")->Fill(minDR_jet, pTrel_jet, weight);
    H2("muo"+std::to_string(i+1)+"__pTrel_jet__vs__met__pt")->Fill(pTrel_jet, event.met->pt(), weight);

    float minDR_topjet(uhh2::infinity);
    for(const auto& tj: *event.topjets){
      if(uhh2::deltaR(p, tj) < minDR_topjet) minDR_topjet = uhh2::deltaR(p, tj);
    }

    H1("muo"+std::to_string(i+1)+"__minDR_topjet")->Fill(minDR_topjet, weight);
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
    H1("ele"+std::to_string(i+1)+"__etaSC") ->Fill(p.supercluster_eta(), weight);
    H1("ele"+std::to_string(i+1)+"__phi")   ->Fill(p.phi()             , weight);
    H1("ele"+std::to_string(i+1)+"__phiError") ->Fill(p.phiError() , weight);
    H2("ele"+std::to_string(i+1)+"__pt__vs__met__pt")->Fill(p.pt(), event.met->pt(), weight);
    int EMclass= p.Class();
    H1("ele"+std::to_string(i+1)+"__class")->Fill(EMclass, weight);

    const float pfR030Iso_dbeta = p.relIsodb();
    const float pfMINIIso_dbeta = util::pfMINIIso(p, "delta-beta");
    const float pfMINIIso_pfwgt = util::pfMINIIso(p, "pf-weight");

    H1("ele"+std::to_string(i+1)+"__pfIso_dbeta")    ->Fill(pfR030Iso_dbeta, weight);
    H1("ele"+std::to_string(i+1)+"__pfMINIIso_dbeta")->Fill(pfMINIIso_dbeta, weight);
    H1("ele"+std::to_string(i+1)+"__pfMINIIso_pfwgt")->Fill(pfMINIIso_pfwgt, weight);

    float minDR_jet(-1.), pTrel_jet(-1.);
    if(p.has_tag(Electron::twodcut_dRmin) && p.has_tag(Electron::twodcut_pTrel)){

      minDR_jet = p.get_tag(Electron::twodcut_dRmin);
      pTrel_jet = p.get_tag(Electron::twodcut_pTrel);
    }
    else std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    H1("ele"+std::to_string(i+1)+"__minDR_jet")->Fill(minDR_jet, weight);
    H1("ele"+std::to_string(i+1)+"__pTrel_jet")->Fill(pTrel_jet, weight);
    H2("ele"+std::to_string(i+1)+"__minDR_jet__vs__ele"+std::to_string(i+1)+"__pTrel_jet")->Fill(minDR_jet, pTrel_jet, weight);
    H2("ele"+std::to_string(i+1)+"__pTrel_jet__vs__met__pt")->Fill(pTrel_jet, event.met->pt(), weight);

    float minDR_topjet(uhh2::infinity);
    for(const auto& tj: *event.topjets){
      if(uhh2::deltaR(p, tj) < minDR_topjet) minDR_topjet = uhh2::deltaR(p, tj);
    }

    H1("ele"+std::to_string(i+1)+"__minDR_topjet")->Fill(minDR_topjet, weight);
  }

  // JET
  int jetN(event.jets->size());
  int jetN__pt030_eta2p4(0);
  int jetN__pt050_eta2p4(0);
  int jetN__pt100_eta2p4(0);
  int jetN__pt150_eta2p4(0);
  int jetN__pt200_eta2p4(0);
  int jetN__pt250_eta2p4(0);

  for(int i=0; i<jetN; ++i){

    const Jet& p = event.jets->at(i);

    if(p.pt() >  30. && fabs(p.eta()) < 2.4) ++jetN__pt030_eta2p4;
    if(p.pt() >  50. && fabs(p.eta()) < 2.4) ++jetN__pt050_eta2p4;
    if(p.pt() > 100. && fabs(p.eta()) < 2.4) ++jetN__pt100_eta2p4;
    if(p.pt() > 150. && fabs(p.eta()) < 2.4) ++jetN__pt150_eta2p4;
    if(p.pt() > 200. && fabs(p.eta()) < 2.4) ++jetN__pt200_eta2p4;
    if(p.pt() > 250. && fabs(p.eta()) < 2.4) ++jetN__pt250_eta2p4;

    if(i > 2) continue;

    H1("jet"+std::to_string(i+1)+"__pt") ->Fill(p.pt()                          , weight);
    H1("jet"+std::to_string(i+1)+"__eta")->Fill(p.eta()                         , weight);
    H1("jet"+std::to_string(i+1)+"__phi")->Fill(p.phi()                         , weight);
    H1("jet"+std::to_string(i+1)+"__M")  ->Fill(p.v4().M()                      , weight);
    H1("jet"+std::to_string(i+1)+"__CSV")->Fill(p.btag_combinedSecondaryVertex(), weight);
  }

  H1("jetN")              ->Fill(jetN              , weight);
  H1("jetN__pt030_eta2p4")->Fill(jetN__pt030_eta2p4, weight);
  H1("jetN__pt050_eta2p4")->Fill(jetN__pt050_eta2p4, weight);
  H1("jetN__pt100_eta2p4")->Fill(jetN__pt100_eta2p4, weight);
  H1("jetN__pt150_eta2p4")->Fill(jetN__pt150_eta2p4, weight);
  H1("jetN__pt200_eta2p4")->Fill(jetN__pt200_eta2p4, weight);
  H1("jetN__pt250_eta2p4")->Fill(jetN__pt250_eta2p4, weight);

  std::vector<float> jets_CSV;
  jets_CSV.reserve(event.jets->size());
  for(const auto& j : *event.jets) jets_CSV.push_back(j.btag_combinedSecondaryVertex());
  std::sort(jets_CSV.begin(), jets_CSV.end(), [](const float s1, const float s2){return s1 > s2;});

  int jetN__CSVL(0), jetN__CSVM(0), jetN__CSVT(0);
  for(unsigned int i=0; i<jets_CSV.size(); ++i){

    const float& csv = jets_CSV.at(i);

    if(csv > 0.605) ++jetN__CSVL;
    if(csv > 0.890) ++jetN__CSVM;
    if(csv > 0.970) ++jetN__CSVT;

    if(i > 2) continue;

    H1("jetA__maxCSV"+std::to_string(i+1))->Fill(jets_CSV.at(i), weight);
  }

  H1("jetN__CSVL")->Fill(jetN__CSVL, weight);
  H1("jetN__CSVM")->Fill(jetN__CSVM, weight);
  H1("jetN__CSVT")->Fill(jetN__CSVT, weight);
  //

  // TOPJET
  const int topjetN(event.topjets->size());
  H1("topjetN")->Fill(topjetN, weight);

  for(int i=0; i<std::min(2, topjetN); ++i){

    const Jet& p = event.topjets->at(i);

    H1("topjet"+std::to_string(i+1)+"__pt") ->Fill(p.pt()                          , weight);
    H1("topjet"+std::to_string(i+1)+"__eta")->Fill(p.eta()                         , weight);
    H1("topjet"+std::to_string(i+1)+"__phi")->Fill(p.phi()                         , weight);
    H1("topjet"+std::to_string(i+1)+"__CSV")->Fill(p.btag_combinedSecondaryVertex(), weight);
  }

  // TOPTAG
  std::vector<TopJet> toptags;
  for(unsigned int i=0; i<event.topjets->size(); ++i){

    const TopJet& tjet = event.topjets->at(i);
    if(tjet_ID_(tjet, event)) toptags.push_back(tjet);
  }

  const int toptagN(toptags.size());
  H1("toptagN")->Fill(toptagN, weight);

  sort_by_pt<TopJet>(toptags);
  for(int i=0; i<std::min(2, toptagN); ++i){

    const TopJet& tj = toptags.at(i);

    std::vector<std::string> htags_ETA({""});
    if(i == 0){
      if(fabs(tj.eta()) < 1.0) htags_ETA.push_back("_etaLO");
      else                     htags_ETA.push_back("_etaHI");
    }

    for(const auto& eta : htags_ETA){

      H1("toptag"+std::to_string(i+1)+eta+"__pt") ->Fill(tj.pt()                          , weight);
      H1("toptag"+std::to_string(i+1)+eta+"__eta")->Fill(tj.eta()                         , weight);
      H1("toptag"+std::to_string(i+1)+eta+"__phi")->Fill(tj.phi()                         , weight);
      H1("toptag"+std::to_string(i+1)+eta+"__M")  ->Fill(tj.v4().M()                      , weight);
      H1("toptag"+std::to_string(i+1)+eta+"__CSV")->Fill(tj.btag_combinedSecondaryVertex(), weight);

      // substructure
      if(i > 0) continue;

      H1("toptag"+std::to_string(i+1)+eta+"__Mpru")->Fill(tj.prunedmass()   , weight);
      H1("toptag"+std::to_string(i+1)+eta+"__Msdp")->Fill(tj.softdropmass() , weight);
      H1("toptag"+std::to_string(i+1)+eta+"__mmin")->Fill(m_disubjet_min(tj), weight);
      H1("toptag"+std::to_string(i+1)+eta+"__tau2")->Fill(tj.tau2()         , weight);
      H1("toptag"+std::to_string(i+1)+eta+"__tau3")->Fill(tj.tau3()         , weight);
      if(tj.tau2()) H1("toptag"+std::to_string(i+1)+eta+"__tau32")->Fill(tj.tau3()/tj.tau2(), weight);

      std::vector<Jet> subjets = tj.subjets();

      const int subjN(subjets.size());

      H1("toptag"+std::to_string(i+1)+eta+"__subjN")->Fill(subjN, weight);

      float subj_minDR(-1.);
      LorentzVector sum_subj(0, 0, 0, 0);
      for  (int sj1=0    ; sj1<subjN; ++sj1){
        for(int sj2=sj1+1; sj2<subjN; ++sj2){

          const float dR = uhh2::deltaR(subjets.at(sj1), subjets.at(sj2));
          if(dR < subj_minDR || (sj1+sj2==1)) subj_minDR = dR;
        }

        sum_subj += subjets.at(sj1).v4();
      }
      H1("toptag"+std::to_string(i+1)+eta+"__Mgro")      ->Fill(sum_subj.M(), weight);
      H1("toptag"+std::to_string(i+1)+eta+"__subj_minDR")->Fill(subj_minDR  , weight);

      sort_by_pt<Jet>(subjets);
      for(int sj=0; sj<std::min(3, subjN); ++sj){

        const Jet& sjet = subjets.at(sj);

        H1("toptag"+std::to_string(i+1)+eta+"__subj"+std::to_string(sj+1)+"__pt") ->Fill(sjet.pt() , weight);
        H1("toptag"+std::to_string(i+1)+eta+"__subj"+std::to_string(sj+1)+"__eta")->Fill(sjet.eta(), weight);
      }

      std::sort(subjets.begin(), subjets.end(), [](const Jet& j1, const Jet& j2){return j1.btag_combinedSecondaryVertex() > j2.btag_combinedSecondaryVertex();});
      for(int sj=0; sj<std::min(3, subjN); ++sj){

        const Jet& sjet = subjets.at(sj);

        H1("toptag"+std::to_string(i+1)+eta+"__subj_maxCSV"+std::to_string(sj+1))->Fill(sjet.btag_combinedSecondaryVertex(), weight);
      }
    }
  }

  // MET
  H1("met__pt") ->Fill(event.met->pt() , weight);
  H1("met__phi")->Fill(event.met->phi(), weight);

  const Particle* lep1(0);
  float max_lep_pt(0.);
  for(const auto& l : *event.muons)     if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }
  for(const auto& l : *event.electrons) if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }

  if(lep1){

    H1("wlep__ht")->Fill( event.met->pt()+lep1->pt()      , weight);
    H1("wlep__pt")->Fill((event.met->v4()+lep1->v4()).Pt(), weight);
    H1("wlep__Mt")->Fill(sqrt(2*event.met->pt()*lep1->pt()*(1.-cos(uhh2::deltaPhi(*event.met, *lep1)))), weight);
  }

  /* triangular cuts vars */
  if(lep1)               H2("met__pt__vs__dphi_met_lep1")->Fill(event.met->pt(), fabs(uhh2::deltaPhi(*event.met, *lep1))            , weight);
  if(event.jets->size()) H2("met__pt__vs__dphi_met_jet1")->Fill(event.met->pt(), fabs(uhh2::deltaPhi(*event.met, event.jets->at(0))), weight);

  TMVA_response->Fill(event.get(tt_tmva_response), weight);
  return;
}
