#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/utils.h>

#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/TopJetIds.h>

#include "TH1F.h"
#include "TH2F.h"

using namespace uhh2;
using namespace std;

TTbarLJHists::TTbarLJHists(uhh2::Context& ctx, const std::string& dirname):
  Hists(ctx, dirname), tjet_ID_(TopTagID_NO()), tjet_minDR_jet_(0.) {

  init();

  tt_tmva_response = ctx.get_handle<float>("TMVA_response");
  //mask them all for preselection
  wjets_tmva_response = ctx.get_handle<float>("WJets_TMVA_response"); 
  h_s33 = ctx.get_handle<float>("s33");
  //  h_njets = ctx.get_handle<float>("njets");
  h_jet1_csv = ctx.get_handle<float>("jet1_csv"); 
  h_jet2_csv = ctx.get_handle<float>("jet2_csv"); 
  h_DRpt = ctx.get_handle<float>("DRpt");
  h_lep1__pTrel_jet_norm = ctx.get_handle<float>("lep1__pTrel_jet_norm");
  h_lep1__minDR_norm = ctx.get_handle<float>("lep1__minDR_norm");
  h_jet1_m = ctx.get_handle<float>("jet1_m");
  h_jet2_m = ctx.get_handle<float>("jet2_m");
  h_ht_met_lep_norm = ctx.get_handle<float>("ht_met_lep_norm");

}

TTbarLJHists::TTbarLJHists(uhh2::Context& ctx, const std::string& dirname, const TopJetId& ttag_id, const float dr__ttag_jet):
  Hists(ctx, dirname), tjet_ID_(ttag_id), tjet_minDR_jet_(dr__ttag_jet) {

  init();

  tt_tmva_response = ctx.get_handle<float>("TMVA_response");
  wjets_tmva_response = ctx.get_handle<float>("WJets_TMVA_response");
  h_s33 = ctx.get_handle<float>("s33");
  //  h_njets = ctx.get_handle<float>("njets");
  h_jet1_csv = ctx.get_handle<float>("jet1_csv");
  h_jet2_csv = ctx.get_handle<float>("jet2_csv");
  h_DRpt = ctx.get_handle<float>("DRpt");

  h_lep1__pTrel_jet_norm = ctx.get_handle<float>("lep1__pTrel_jet_norm");
  h_lep1__minDR_norm = ctx.get_handle<float>("lep1__minDR_jet");
  h_ht_met_lep_norm = ctx.get_handle<float>("ht_met_lep_norm");
  h_jet1_m = ctx.get_handle<float>("jet1_m");
  h_jet2_m = ctx.get_handle<float>("jet2_m");
}

void TTbarLJHists::init(){
  // const int nptAxis = 13;
  // //  Float_t ptAxis[nptAxis] ={0., 40., 60., 80., 100., 120., 140., 160., 180., 200., 220., 240., 300., 450., 600., 750., 900., 1500.};
  // Float_t ptAxis[nptAxis] ={0., 50., 90., 130., 170., 210., 250., 300., 450., 600., 750., 900., 1500.};
  // const int nptAxis = 41;
  // Float_t ptAxis[nptAxis] = {0, 20, 30, 40, 45, 50, 55, 60, 65, 70, 
  // 			     80, 90, 100, 110, 120, 130, 140, 150, 160, 170, 
  // 			     180, 190, 200, 210, 230, 250, 270, 290, 310, 330, 
  // 			     350, 370, 390, 410, 460, 510, 560, 610, 660, 710, 810}; 

  wgt = book<TH1F>("wgt","weight",120, -6, 6);

  // PV
  pvN = book<TH1F>("pvN","N_{PV}", 60, 0, 60);
  rho = book<TH1F>("rho","#rho [GeV]", 60, 0, 60);

  // MUON
  muoN = book<TH1F>("muoN", "N mouns"               , 10, 0, 10);
  muo1__charge = book<TH1F>("muo1__charge","muon charge"        , 5, -2, 3);
  muo1__pt = book<TH1F>("muo1__pt","muon p_{T} [GeV]"            , 45, 0, 900);
  //  muo1__pt = book<TH1F>("muo1__pt","muon p_{T} [GeV]", nptAxis-1, ptAxis);
  muo1__eta = book<TH1F>("muo1__eta","muon #eta"            ,30,-3,3);

  muo1__phi = book<TH1F>("muo1__phi","muon #phi"           , 60, -3.15, 3.15);
  muo1__minDR_jet = book<TH1F>("muo1__minDR_jet", "#Delta R_{min}(#mu,jet)"     , 30, 0, 3.2);
  muo1__pTrel_jet = book<TH1F>("muo1__pTrel_jet", "p_{T,rel}(#mu,jet) [GeV]"    , 25, 0, 500);


  muo2__charge = book<TH1F>("muo2__charge","muon_{2} charge"         , 5, -2, 3);
  muo2__pt = book<TH1F>("muo2__pt","muon_{2} p_{T}[GeV]"             , 45, 0, 900);
  //  muo2__pt = book<TH1F>("muo2__pt","muon p_{T}[GeV]", nptAxis-1, ptAxis);
  muo2__eta = book<TH1F>("muo2__eta","muon_{2} #eta"            ,30,-3,3);
  muo2__phi = book<TH1F>("muo2__phi","muon_{2} #phi"            , 60, -3.15, 3.15);
  muo2__minDR_jet = book<TH1F>("muo2__minDR_jet", "#Delta R_{min}(#mu_{2},jet)"      , 60, 0, 6);
  muo2__pTrel_jet = book<TH1F>("muo2__pTrel_jet", "p_{T,rel}(#mu_{2},jet) [GeV]"      , 100, 0, 500);

  // ELECTRON
  eleN = book<TH1F>("eleN", "N electrons"               , 20, 0, 20);
  ele1__class = book<TH1F>("ele1__class", "electron class" , 6, -0.5, 5.5);
  ele1__charge = book<TH1F>("ele1__charge", "electron charge"         , 5, -2, 3);
  //ele1__pt = book<TH1F>("ele1__pt", "electron p_{T} [GeV]"             , 45, 0, 900);

  ele1__pt = book<TH1F>("ele1__pt", "electron p_{T} [GeV]"             , 45, 0, 900);
  //  ele1__pt = book<TH1F>("ele1__pt", "electron p_{T} [GeV]", nptAxis-1, ptAxis);

  ele1__ptError = book<TH1F>("ele1__ptError","electron #sigma(p_{T}) [GeV]"         , 36, 0, 720);
  ele1__eta = book<TH1F>("ele1__eta","electron #eta"            ,30,-3,3);
  ele1__etaError = book<TH1F>("ele1__etaError","electron #sigma(#eta)"        , 100, 0, 0.01);
  ele1__phi = book<TH1F>("ele1__phi", "electron #phi"            , 60, -3.15, 3.15);
  ele1__phiError = book<TH1F>("ele1__phiError", "electron #sigma(#phi)"            , 60, 0, 1.);
  ele1__minDR_jet = book<TH1F>("ele1__minDR_jet","#Delta R_{min}(e,jet)"      , 60, 0, 6);
  ele1__pTrel_jet = book<TH1F>("ele1__pTrel_jet", "p_{T,rel}(e,jet)[GeV]"     , 100, 0, 500);
  ele1__DPhi_met = book<TH1F>("ele1__DPhi_met","#Delta #phi(e,MET)", 40, 0, 4);
  ele1__eta_SC = book<TH1F>("ele1__eta_SC","electron SC #eta" ,30,-3,3);
  ele1__Deta_trk_SC = book<TH1F>("ele1__Deta_trk_SC","electron #eta_{trk} -#eta_{SC}",150,-2.5,2.5);

  ele2__class = book<TH1F>("ele2__class", "electron_{2} class" , 6, -0.5, 5.5);
  ele2__charge = book<TH1F>("ele2__charge", "electron_{2} charge"         , 5, -2, 3);
  ele2__pt = book<TH1F>("ele2__pt", "electron p_{T} [GeV]"             , 45, 0, 900);
  //  ele2__pt = book<TH1F>("ele2__pt", "electron_{2} p_{T} [GeV]", nptAxis-1, ptAxis);
  ele2__ptError = book<TH1F>("ele2__ptError","electron_{2} #sigma(p_{T}) [GeV]"  , 36, 0, 720);
  ele2__eta = book<TH1F>("ele2__eta", "electron_{2} #eta"            ,30,-3,3);
  ele2__etaError = book<TH1F>("ele2__etaError","electron_{2} #sigma(#eta)" , 100, 0, 0.01);
  ele2__phi = book<TH1F>("ele2__phi", "electron_{2} #phi"           , 60, -3.15, 3.15);
  ele2__phiError = book<TH1F>("ele2__phiError", "electron_{2} #sigma(#phi)" , 60, 0, 1.);
  ele2__minDR_jet = book<TH1F>("ele2__minDR_jet","#Delta R_{min}(e_{2},jet)"      , 60, 0, 6);
  ele2__pTrel_jet = book<TH1F>("ele2__pTrel_jet", "p_{T,rel}(e_{2},jet)[GeV]"      , 100, 0, 500);
  ele2__DPhi_met = book<TH1F>("ele2__DPhi_met","#Delta #phi(e,MET)", 40, 0, 4);

  // JET
  jetN = book<TH1F>("jetN", "N jets"              , 20, 0, 20);
  jetN__CSVL = book<TH1F>("jetN__CSVL","N jets with Loose CSV"        , 10, 0, 10);
  jetN__CSVM = book<TH1F>("jetN__CSVM","N jets with Medium CSV"        , 10, 0, 10);
  jetN__CSVT = book<TH1F>("jetN__CSVT", "N jets with Tight CSV"        , 10, 0, 10);

  jet1__pt = book<TH1F>("jet1__pt", "jet p_{T} [GeV]" , 45, 0, 900);
  //  jet1__pt = book<TH1F>("jet1__pt", "jet p_{T} [GeV]", nptAxis-1, ptAxis);
  jet1__eta = book<TH1F>("jet1__eta", "jet #eta",30,-3,3);
  jet1__phi = book<TH1F>("jet1__phi", "jet #phi", 60, -3.15, 3.15);
  jet1__M = book<TH1F>("jet1__M", "jet mass"  , 360, 0, 360);
  jet1__CSV = book<TH1F>("jet1__CSV","CSV", 60, 0, 1.2);
  jet1__NDaughters = book<TH1F>("jet1__NDaughters","NDaughters", 100, 0, 100);
  jet1__MVAbtag = book<TH1F>("jet1__MVAbtag","MVA b-tag", 60, -1.2, 1.2);
  jet1__EMfrac = book<TH1F>("jet1__EMfrac", "jet EM fraction" , 22, 0, 1.1);
  jet1__HADfrac = book<TH1F>("jet1__HADfrac", "jet HAD fraction" , 22, 0, 1.1);
  jet1__PHfrac = book<TH1F>("jet1__PHfrac", "jet photon fraction" , 22, 0, 1.1);

  jet2__pt = book<TH1F>("jet2__pt", "jet_{2} p_{T} [GeV]" , 45, 0, 900);
  //  jet2__pt = book<TH1F>("jet2__pt", "jet p_{T} [GeV]", nptAxis-1, ptAxis);
  jet2__eta = book<TH1F>("jet2__eta", "jet_{2} #eta",30,-3,3);
  jet2__phi = book<TH1F>("jet2__phi", "jet_{2} #phi", 60, -3.15, 3.15);
  jet2__M = book<TH1F>("jet2__M", "jet_{2} mass [GeV]"  , 360, 0, 360);
  jet2__NDaughters = book<TH1F>("jet2__NDaughters","jet_{2} NDaughters", 100, 0, 100);
  jet2__CSV = book<TH1F>("jet2__CSV","jet_{2} CSV", 60, 0, 1.2);
  jet2__MVAbtag = book<TH1F>("jet2__MVAbtag","jet_{2} MVA b-tag", 60, -1.2, 1.2);
  jet2__EMfrac = book<TH1F>("jet2__EMfrac", "jet_{2} EM fraction" , 22, 0, 1.1);
  jet2__HADfrac = book<TH1F>("jet2__HADfrac", "jet_{2} HAD fraction" , 22, 0, 1.1);
  jet2__PHfrac = book<TH1F>("jet2__PHfrac", "jet_{2} photon fraction" , 22, 0, 1.1);

  jet3__pt = book<TH1F>("jet3__pt", "jet_{3} p_{T}[GeV]" , 50, 200, 1700);
  //  jet3__pt = book<TH1F>("jet3__pt", "jet_{3} p_{T}[GeV]", nptAxis-1, ptAxis);
  jet3__eta = book<TH1F>("jet3__eta", "jet_{3} #eta",30,-3,3);
  jet3__phi = book<TH1F>("jet3__phi", "jet_{3} #phi", 60, -3.15, 3.15);
  jet3__M = book<TH1F>("jet3__M", "jet_{3} mass"  , 360, 0, 360);
  jet3__NDaughters = book<TH1F>("jet3__NDaughters","jet_{3} NDaughters", 100, 0, 100);
  jet3__CSV = book<TH1F>("jet3__CSV","jet_{3} CSV", 60, 0, 1.2);
  jet3__MVAbtag = book<TH1F>("jet3__MVAbtag","jet_{3} MVA b-tag", 60, -1.2, 1.2);
  jet3__EMfrac = book<TH1F>("jet3__EMfrac", "jet_{3} EM fraction" , 22, 0, 1.1);
  jet3__HADfrac = book<TH1F>("jet3__HADfrac", "jet_{3} HAD fraction" , 22, 0, 1.1);
  jet3__PHfrac = book<TH1F>("jet3__PHfrac", "jet_{3} photon fraction" , 22, 0, 1.1);

  //  under_jets__pt = book<TH1F>("under_jets__pt", "#sum_{i}{jet_{i} p_{T}} - jet1 [GeV]", nptAxis-1, ptAxis);
  under_jets__pt = book<TH1F>("under_jets__pt", "#sum_{i}{jet_{i} p_{T}} - jet1 [GeV]", 45, 0, 900);
 
  // TOPJET
  topjetN = book<TH1F>("topjetN","N topjets", 10, 0, 10);

  topjet1__pt = book<TH1F>("topjet1__pt","topjet p_{T} [GeV]" , 80, 100, 1700);
  //  topjet1__pt = book<TH1F>("topjet1__pt","topjet p_{T} [GeV]", nptAxis-1, ptAxis);

  topjet1__eta = book<TH1F>("topjet1__eta","topjet #eta", 30, -3, 3);
  topjet1__phi = book<TH1F>("topjet1__phi","topjet #phi", 30, -3.15, 3.15);
  topjet1__CSV = book<TH1F>("topjet1__CSV", "topjet CSV", 30, 0, 1.2);
  topjet1__Msdp = book<TH1F>("topjet1__Msdp","topjet softdrop mass [GeV]", 50, 0, 500);
  topjet1__tau32 = book<TH1F>("topjet1__tau32","topjet #tau_{32}", 24, 0, 1.2);
  topjet1__NumSubjets = book<TH1F>("topjet1__subjN", "topjet N sub-jets"       , 6, 0, 6);
  topjet1__dR = book<TH1F>("topjet1__dR","#DeltaR(topjet_{1}, toppuppijet)" , 50, 0, 5);
  topjet2__pt = book<TH1F>("topjet2__pt","topjet_{2} p_{T} [GeV]" , 80, 100, 1700);
  //  topjet2__pt = book<TH1F>("topjet2__pt","topjet p_{T} [GeV]", nptAxis-1, ptAxis);
  topjet2__eta = book<TH1F>("topjet2__eta","topjet_{2} #eta", 30, -3, 3);
  topjet2__phi = book<TH1F>("topjet2__phi","topjet_{2} #phi", 30, -3.15, 3.15);
  topjet2__CSV = book<TH1F>("topjet2__CSV", "topjet_{2} CSV", 30, 0, 1.2);
  topjet2__Msdp = book<TH1F>("topjet2__Msdp","topjet_{2} softdrop mass [GeV]", 50, 0, 500);
  topjet2__tau32 = book<TH1F>("topjet2__tau32","topjet_{2} #tau_{32}", 24, 0, 1.2);
  topjet2__NumSubjets = book<TH1F>("topjet2__subjN", "topjet_{2} N sub-jets" , 6, 0, 6);
  topjet2__dR = book<TH1F>("topjet2__dR","#DeltaR(topjet_{2}, toppuppijet)" , 50, 0, 5);

 // TOPPUPPIJET
  toppuppijetN = book<TH1F>("toppuppijetN","N toppuppijets", 10, 0, 10);

  toppuppijet1__pt = book<TH1F>("toppuppijet1__pt","toppuppijet p_{T} [GeV]" , 80, 100, 1700);
  //  toppuppijet1__pt = book<TH1F>("toppuppijet1__pt","toppuppijet p_{T} [GeV]", nptAxis-1, ptAxis);

  toppuppijet1__eta = book<TH1F>("toppuppijet1__eta","toppuppijet #eta", 30, -3, 3);
  toppuppijet1__phi = book<TH1F>("toppuppijet1__phi","toppuppijet #phi", 30, -3.15, 3.15);
  toppuppijet1__CSV = book<TH1F>("toppuppijet1__CSV", "toppuppijet CSV", 30, 0, 1.2);
  toppuppijet1__Msdp = book<TH1F>("toppuppijet1__Msdp","toppuppijet softdrop mass [GeV]", 50, 0, 500);
  toppuppijet1__tau32 = book<TH1F>("toppuppijet1__tau32","toppuppijet #tau_{32}", 24, 0, 1.2);
  toppuppijet1__NumSubjets = book<TH1F>("toppuppijet1__subjN", "toppuppijet N sub-jets"       , 6, 0, 6);
  toppuppijet2__pt = book<TH1F>("toppuppijet2__pt","toppuppijet_{2} p_{T} [GeV]" , 80, 100, 1700);
  //  toppuppijet2__pt = book<TH1F>("toppuppijet2__pt","toppuppijet p_{T} [GeV]", nptAxis-1, ptAxis);
  toppuppijet2__eta = book<TH1F>("toppuppijet2__eta","toppuppijet_{2} #eta", 30, -3, 3);
  toppuppijet2__phi = book<TH1F>("toppuppijet2__phi","toppuppijet_{2} #phi", 30, -3.15, 3.15);
  toppuppijet2__CSV = book<TH1F>("toppuppijet2__CSV", "toppuppijet_{2} CSV", 30, 0, 1.2);
  toppuppijet2__Msdp = book<TH1F>("toppuppijet2__Msdp","toppuppijet_{2} softdrop mass [GeV]", 50, 0, 500);
  toppuppijet2__tau32 = book<TH1F>("toppuppijet2__tau32","toppuppijet_{2} #tau_{32}", 24, 0, 1.2);
  toppuppijet2__NumSubjets = book<TH1F>("toppuppijet2__subjN", "toppuppijet_{2} N sub-jets"       , 6, 0, 6);

 // TOPPUPPIJET matched
  toppuppijetN_matched = book<TH1F>("toppuppijetN_matched","N toppuppijets matched", 10, 0, 10);
  toppuppijet__pt_matched = book<TH1F>("toppuppijet__pt_matched","matched toppuppijet p_{T} [GeV]" , 80, 100, 1700);
  toppuppijet__eta_matched = book<TH1F>("toppuppijet__eta_matched","matched toppuppijet #eta", 30, -3, 3);
  toppuppijet__phi_matched = book<TH1F>("toppuppijet__phi_matched","matched toppuppijet #phi", 30, -3.15, 3.15);
  toppuppijet__CSV_matched = book<TH1F>("toppuppijet__CSV_matched", "matched toppuppijet CSV", 30, 0, 1.2);
  toppuppijet__Msdp_matched = book<TH1F>("toppuppijet__Msdp_matched","matched toppuppijet softdrop mass [GeV]", 50, 0, 500);
  toppuppijet__tau32_matched = book<TH1F>("toppuppijet__tau32_matched","matched toppuppijet #tau_{32}", 24, 0, 1.2);
  toppuppijet__NumSubjets_matched = book<TH1F>("toppuppijet__subjN_matched", "matched toppuppijet N sub-jets"       , 6, 0, 6);
  toppuppijet__jetID_matched = book<TH1F>("toppuppijet__jetID_matched", "matched toppuppijet  jetID"       , 6, 1, 7);


  toppuppijet__pt_matched_ttag = book<TH1F>("toppuppijet__pt_matched_ttag","matched to ttag toppuppijet p_{T} [GeV]" , 80, 100, 1700);
  toppuppijet__eta_matched_ttag = book<TH1F>("toppuppijet__eta_matched_ttag","matched to ttag toppuppijet #eta", 30, -3, 3);
  toppuppijet__phi_matched_ttag = book<TH1F>("toppuppijet__phi_matched_ttag","matched to ttag toppuppijet #phi", 30, -3.15, 3.15);
  toppuppijet__CSV_matched_ttag = book<TH1F>("toppuppijet__CSV_matched_ttag", "matched to ttag toppuppijet CSV", 30, 0, 1.2);
  toppuppijet__Msdp_matched_ttag = book<TH1F>("toppuppijet__Msdp_matched_ttag","matched to ttag toppuppijet softdrop mass [GeV]", 50, 0, 500);
  toppuppijet__tau32_matched_ttag = book<TH1F>("toppuppijet__tau32_matched_ttag","matched to ttag toppuppijet #tau_{32}", 24, 0, 1.2);
  toppuppijet__NumSubjets_matched_ttag = book<TH1F>("toppuppijet__subjN_matched_ttag", "matched to ttag toppuppijet N sub-jets"       , 6, 0, 6);
  toppuppijet__jetID_matched_ttag = book<TH1F>("toppuppijet__jetID_matched_ttag", "matched to ttag toppuppijet  jetID"       , 6, 1, 7);
  toppuppijet__Msdp_matched_Nminus1 = book<TH1F>("toppuppijet__Msdp_matched_Nminus1","AK8PUPPI softdrop mass [GeV]", 50, 0, 500);
  toppuppijet__tau32_matched_Nminus1 = book<TH1F>("toppuppijet__tau32_matched_Nminus1","AK8PUPPI #tau_{32}", 24, 0, 1.2);



  // TOPTAG
  toptagN = book<TH1F>("toptagN","N top-tagged jets"              , 10, 0, 10);
  toptag1__pt = book<TH1F>("toptag1__pt","top-tag jet p_{T} [GeV]"          , 80, 100, 1700);
  toptag1__eta = book<TH1F>("toptag1__eta", "top-tag jet #eta"         , 30, -3, 3);
  toptag1__phi = book<TH1F>("toptag1__phi","top-tag jet #phi"         , 30, -3.15, 3.15);
  toptag1__M  = book<TH1F>("toptag1__M", "top-tag jet mass [GeV]"           , 50, 0, 500);
  toptag1__Mgro = book<TH1F>("toptag1__Mgro", "top-tag jet groomed mass [GeV]"        , 50, 0, 500);
  toptag1__Mpru  = book<TH1F>("toptag1__Mpru", "top-tag jet pruned mass [GeV]"        , 50, 0, 500);
  toptag1__Msdp  = book<TH1F>("toptag1__Msdp", "top-tag jet softdrop mass [GeV]"        , 50, 0, 500);
  toptag1__tau32  = book<TH1F>("toptag1__tau32", "top-tag jet #tau_{32}"       , 24, 0, 1.2);
  toptag1__CSV  = book<TH1F>("toptag1__CSV","top-tag jet CSV"        , 60, 0, 1.2);
  toptag1__subjN  = book<TH1F>("toptag1__subjN", "top-tag jet N subjettiness"       , 6, 0, 6);

  toptag2__pt = book<TH1F>("toptag2__pt","top-tag jet_{2} p_{T} [GeV]"          , 80, 100, 1700);
  toptag2__eta = book<TH1F>("toptag2__eta", "top-tag jet_{2} #eta"         , 30, -3, 3);
  toptag2__phi = book<TH1F>("toptag2__phi","top-tag jet_{2} #phi"         , 30, -3.15, 3.15);
  toptag2__M  = book<TH1F>("toptag2__M", "top-tag jet_{2} mass [GeV]"           , 50, 0, 500);
  toptag2__Mgro = book<TH1F>("toptag2__Mgro", "top-tag jet_{2} groomed mass [GeV]"        , 50, 0, 500);
  toptag2__Mpru  = book<TH1F>("toptag2__Mpru", "top-tag jet_{2} pruned mass [GeV]"        , 50, 0, 500);
  toptag2__Msdp  = book<TH1F>("toptag2__Msdp", "top-tag jet_{2} softdrop mass [GeV]"        , 50, 0, 500);
  toptag2__tau32  = book<TH1F>("toptag2__tau32", "top-tag jet_{2} #tau_{32}"       , 24, 0, 1.2);
  toptag2__CSV  = book<TH1F>("toptag2__CSV","top-tag jet_{2} CSV"        , 60, 0, 1.2);
  toptag2__subjN  = book<TH1F>("toptag2__subjN", "top-tag jet_{2} N subjettiness"       , 6, 0, 6);

  // MET
  met__pt = book<TH1F>("met__pt", "MET [GeV]" , 45, 0, 900);
  //  met__pt = book<TH1F>("met__pt", "MET [GeV]", nptAxis-1, ptAxis);

  met__phi = book<TH1F>("met__phi", "MET #phi", 60, -3.15, 3.15);
  wlep__ht = book<TH1F>("wlep__ht","W_{leptonic} H_{T} [GeV]", 45, 0, 900);
  wlep__pt = book<TH1F>("wlep__pt","W_{leptonic} p_{T} [GeV]", 45, 0, 900);
  wlep__pt__jet1__pt = book<TH1F>("wlep__pt__jet1__pt","W_{leptonic} p_{T}/leading jet p_{T}", 100, 0, 10);
  //  wlep__pt = book<TH1F>("wlep__pt","W_{leptonic} p_{T} [GeV]", nptAxis-1, ptAxis);
  wlep__Mt = book<TH1F>("wlep__Mt","W_{leptonic} M_{T} [GeV]", 360, 0,  360);
  TMVA_response = book<TH1F>("TMVA_response", "QCD TMVA response", 50,-1.2,1.8);


   WJets_TMVA_response = book<TH1F>("WJets_TMVA_response", "WJets TMVA response", 50,-1.2,1.8);
   s33 = book<TH1F>("s33", "s33", 50, 0, 1);
   DRpt= book<TH1F>("DRpt", "DRpt", 50, 0, 1.5);
   jet1_csv = book<TH1F>("jet1_csv", "jet1_csv", 50, 0, 1);
   jet2_csv = book<TH1F>("jet2_csv", "jet2_csv", 50, 0, 1);
   //   njets  = book<TH1F>("njets", "njets", 12, 0, 12);
   jet1_m = book<TH1F>("jet1_m","jet1_m",50,0,0.1);
   jet2_m = book<TH1F>("jet2_m","jet2_m",50,0,0.1);
   ht_met_lep_norm = book<TH1F>("ht_met_lep_norm","ht_met_lep_norm",50,0,3);
   lep1__minDR_norm = book<TH1F>("lep1__minDR_jet","lep1__minDR_jet",50,0,3);
   lep1__pTrel_jet_norm = book<TH1F>("lep1__pTrel_jet_norm", "lep1__pTrel_jet_norm",50,0,0.5);
 
  return;

}

void TTbarLJHists::fill(const uhh2::Event& event){

  assert(event.pvs && event.muons && event.electrons);
  assert(event.jets && event.topjets && event.met);
  assert(event.toppuppijets);

  const float weight(event.weight);
  wgt->Fill(weight);

  // PV
  pvN->Fill(event.pvs->size(), weight);
  rho->Fill(event.rho, weight);

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
      ele1__DPhi_met->Fill(uhh2::deltaPhi(*event.met,p), weight);
      ele1__eta_SC->Fill(p.supercluster_eta(), weight);
      ele1__Deta_trk_SC->Fill(p.eta()-p.supercluster_eta(), weight);
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
      ele2__DPhi_met->Fill(uhh2::deltaPhi(*event.met,p), weight);
    }
 
  }

  // JET
  int jetN_(event.jets->size());
  double jets_pt = 0;
  for(int i=0; i<jetN_; ++i){
    const Jet& p = event.jets->at(i);
    if(i>0) jets_pt+=p.pt();//skip leading jet
    if(i==0){
      jet1__pt ->Fill(p.pt()                          , weight);
      jet1__eta->Fill(p.eta()                         , weight);
      jet1__phi->Fill(p.phi()                         , weight);
      jet1__M  ->Fill(p.v4().M()                      , weight);
      jet1__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
      jet1__MVAbtag->Fill(p.btag_combinedSecondaryVertexMVA(), weight);
      jet1__NDaughters->Fill(p.numberOfDaughters(), weight);
      jet1__EMfrac->Fill(p.neutralEmEnergyFraction()+p.chargedEmEnergyFraction(), weight);
      jet1__HADfrac->Fill(p.neutralHadronEnergyFraction()+p.chargedHadronEnergyFraction(), weight);
      jet1__PHfrac->Fill(p.photonEnergyFraction(), weight);
    }
    if(i==1){
      jet2__pt ->Fill(p.pt()                          , weight);
      jet2__eta->Fill(p.eta()                         , weight);
      jet2__phi->Fill(p.phi()                         , weight);
      jet2__M  ->Fill(p.v4().M()                      , weight);
      jet2__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
      jet2__MVAbtag->Fill(p.btag_combinedSecondaryVertexMVA(), weight);
      jet2__NDaughters->Fill(p.numberOfDaughters(), weight);
      jet2__EMfrac->Fill(p.neutralEmEnergyFraction()+p.chargedEmEnergyFraction(), weight);
      jet2__HADfrac->Fill(p.neutralHadronEnergyFraction()+p.chargedHadronEnergyFraction(), weight);
      jet2__PHfrac->Fill(p.photonEnergyFraction(), weight);
    }
    if(i==2){
      jet3__pt ->Fill(p.pt()                          , weight);
      jet3__eta->Fill(p.eta()                         , weight);
      jet3__phi->Fill(p.phi()                         , weight);
      jet3__M  ->Fill(p.v4().M()                      , weight);
      jet3__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
      jet3__MVAbtag->Fill(p.btag_combinedSecondaryVertexMVA(), weight);
      jet3__NDaughters->Fill(p.numberOfDaughters(), weight);
      jet3__EMfrac->Fill(p.neutralEmEnergyFraction()+p.chargedEmEnergyFraction(), weight);
      jet3__HADfrac->Fill(p.neutralHadronEnergyFraction()+p.chargedHadronEnergyFraction(), weight);
      jet3__PHfrac->Fill(p.photonEnergyFraction(), weight);
    }
  }

  jetN             ->Fill(jetN_              , weight);
  under_jets__pt->Fill(jets_pt,weight);
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
  int topjetN_matched = 0;
  for(int i=0; i<std::min(2, topjetN_); ++i){

    //    const Jet& p = event.topjets->at(i);
    const TopJet& p = event.topjets->at(i);
    float mindR = 9999.0;
    TopJet MatchedPuppiJet;
    TLorentzVector PuppiJetv4;
    TLorentzVector TopJetv4;
    TopJetv4.SetPtEtaPhiE(p.pt(),p.eta(),p.phi(),p.energy());
    for(const auto & pjet : *event.toppuppijets) {
      if(pjet.numberOfDaughters()<2) continue;
      PuppiJetv4.SetPtEtaPhiE(pjet.pt(),pjet.eta(),pjet.phi(),pjet.energy());
      float dR = TopJetv4.DeltaR(PuppiJetv4);
      if (dR < mindR) {
	MatchedPuppiJet = pjet;
	mindR = dR;
      }
    }

    //    if(mindR<0.8) topjetN_matched++;
    if(mindR<1.0) topjetN_matched++;//sync with all had
    if(i==0){
    topjet1__pt ->Fill(p.pt()                          , weight);
    topjet1__eta->Fill(p.eta()                         , weight);
    topjet1__phi->Fill(p.phi()                         , weight);
    topjet1__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    topjet1__Msdp->Fill(p.softdropmass() , weight);
    topjet1__tau32->Fill(p.tau3()/p.tau2() , weight);
    topjet1__NumSubjets->Fill(p.numberOfDaughters() , weight);
    topjet1__dR->Fill(mindR, weight);
    }
    if(i==1){
    topjet2__pt ->Fill(p.pt()                          , weight);
    topjet2__eta->Fill(p.eta()                         , weight);
    topjet2__phi->Fill(p.phi()                         , weight);
    topjet2__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    topjet2__Msdp->Fill(p.softdropmass() , weight);
    topjet2__tau32->Fill(p.tau3()/p.tau2() , weight);
    topjet2__NumSubjets->Fill(p.numberOfDaughters() , weight);
    topjet2__dR->Fill(mindR, weight);
    }
  }

 // TOPPUPPIJET
  const int toppuppijetN_(event.toppuppijets->size());
  int toppuppiN_tmp = 0;
  for(const auto & pjet : *event.toppuppijets) {                                                                                                                      
    if(pjet.numberOfDaughters()<2) continue;   //TEST: skip PUPPI jet if it contains only one daughter  
    toppuppiN_tmp ++;
  }
  //  const int toppuppijetN_(toppuppiN_tmp);
  toppuppijetN->Fill(toppuppiN_tmp , weight);


  for(int i=0; i<std::min(2, toppuppijetN_); ++i){
    const TopJet& p = event.toppuppijets->at(i);
    //if(p.numberOfDaughters()<2) continue;
    float mindR = 9999.0;
    TopJet MatchedPuppiJet;
    TLorentzVector PuppiJetv4;
    TLorentzVector TopJetv4;
    PuppiJetv4.SetPtEtaPhiE(p.pt(),p.eta(),p.phi(),p.energy());
    for(const auto & pjet : *event.topjets) {
      TopJetv4.SetPtEtaPhiE(pjet.pt(),pjet.eta(),pjet.phi(),pjet.energy());
      float dR = TopJetv4.DeltaR(PuppiJetv4);
      if (dR < mindR) {
	MatchedPuppiJet = pjet;
	mindR = dR;
      }
    }

    //    if(mindR<0.8 && p.numberOfDaughters()>1) topjetN_matched++;
    if(mindR<1.0 && p.numberOfDaughters()>1) topjetN_matched++;

    if(i==0 && p.numberOfDaughters()>1){
    toppuppijet1__pt ->Fill(p.pt()                          , weight);
    toppuppijet1__eta->Fill(p.eta()                         , weight);
    toppuppijet1__phi->Fill(p.phi()                         , weight);
    toppuppijet1__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    //Calculate SoftDrop on fly
    TLorentzVector SoftDropv4(0,0,0,0);
    for(const auto & subjet : p.subjets()) {
      TLorentzVector SubJetv4;
      SubJetv4.SetPtEtaPhiE(subjet.pt(),subjet.eta(),subjet.phi(),subjet.energy());
      SoftDropv4 = SoftDropv4 + SubJetv4;
    }

    toppuppijet1__Msdp->Fill(SoftDropv4.M(), weight);
    toppuppijet1__tau32->Fill(p.tau3()/p.tau2() , weight);
    toppuppijet1__NumSubjets->Fill(p.numberOfDaughters() , weight);
    }
    if(i==1 && p.numberOfDaughters()>1){
    toppuppijet2__pt ->Fill(p.pt()                          , weight);
    toppuppijet2__eta->Fill(p.eta()                         , weight);
    toppuppijet2__phi->Fill(p.phi()                         , weight);
    toppuppijet2__CSV->Fill(p.btag_combinedSecondaryVertex(), weight);
    //Calculate SoftDrop on fly
    TLorentzVector SoftDropv4(0,0,0,0);
    for(const auto & subjet : p.subjets()) {
      TLorentzVector SubJetv4;
      SubJetv4.SetPtEtaPhiE(subjet.pt(),subjet.eta(),subjet.phi(),subjet.energy());
      SoftDropv4 = SoftDropv4 + SubJetv4;
    }
    toppuppijet2__Msdp->Fill(SoftDropv4.M() , weight);
    toppuppijet2__tau32->Fill(p.tau3()/p.tau2() , weight);
    toppuppijet2__NumSubjets->Fill(p.numberOfDaughters() , weight);
    }
  }


 // TOPPUPPIJET matched to AK8CHS
  toppuppijetN_matched->Fill(topjetN_matched, weight);

  for(int i=0; i<std::min(2, toppuppijetN_); ++i){
    const TopJet& p = event.toppuppijets->at(i);
    if(p.numberOfDaughters()<2) continue;
    float mindR = 9999.0;
    //    TopJet MatchedPuppiJet;
    TLorentzVector PuppiJetv4;TLorentzVector TopJetv4;
    PuppiJetv4.SetPtEtaPhiE(p.pt(),p.eta(),p.phi(),p.energy());
    for(const auto & pjet : *event.topjets) {  
      TopJetv4.SetPtEtaPhiE(pjet.pt(),pjet.eta(),pjet.phi(),pjet.energy());
      float dR = TopJetv4.DeltaR(PuppiJetv4);
      if (dR < mindR) {  
	//	MatchedPuppiJet = pjet;
        mindR = dR;                                                                                                                                                   
      }                                                                                                                                                               
    }            
    //    if(mindR<0.8 && p.numberOfDaughters()>1){ 
    if(mindR<1.0 && p.numberOfDaughters()>1){ 
      toppuppijet__pt_matched ->Fill(p.pt()                          , weight);
      toppuppijet__eta_matched->Fill(p.eta()                         , weight);
      toppuppijet__phi_matched->Fill(p.phi()                         , weight);
      toppuppijet__CSV_matched->Fill(p.btag_combinedSecondaryVertex(), weight);
      //Calculate SoftDrop on fly
      TLorentzVector SoftDropv4(0,0,0,0);
      for(const auto & subjet : p.subjets()) {
	TLorentzVector SubJetv4;
	SubJetv4.SetPtEtaPhiE(subjet.pt(),subjet.eta(),subjet.phi(),subjet.energy());
	SoftDropv4 = SoftDropv4 + SubJetv4;
      }
      toppuppijet__Msdp_matched->Fill(SoftDropv4.M(), weight);
      toppuppijet__tau32_matched->Fill(p.tau3()/p.tau2() , weight);
      toppuppijet__NumSubjets_matched->Fill(p.numberOfDaughters() , weight);
      toppuppijet__jetID_matched->Fill(i, weight);
      if((p.tau3()/p.tau2())<0.65)
	toppuppijet__Msdp_matched_Nminus1->Fill(SoftDropv4.M(),weight);
      if(SoftDropv4.M()>105 && SoftDropv4.M()<210)
	toppuppijet__tau32_matched_Nminus1->Fill(p.tau3()/p.tau2(),weight); 

      //      if((p.tau3()/p.tau2())>0.65)      std::cout<<"TTbarLJHists: LOOK toppuppijet_matched tau32 = "<<p.tau3()/p.tau2()<<std::endl;
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

  //Top-tag jets matched to toppuppi jets
  for(int i=0; i<std::min(2, toppuppijetN_); ++i){
    const TopJet& p = event.toppuppijets->at(i);
    if(p.numberOfDaughters()<2) continue;
    float mindR = 9999.0;
    //    TopJet MatchedPuppiJet;
    TLorentzVector PuppiJetv4;TLorentzVector TopJetv4;
    PuppiJetv4.SetPtEtaPhiE(p.pt(),p.eta(),p.phi(),p.energy());
    for(int i=0; i<std::min(2, toptagN_); ++i){
      const TopJet& pjet = toptags.at(i);
  
      TopJetv4.SetPtEtaPhiE(pjet.pt(),pjet.eta(),pjet.phi(),pjet.energy());
      float dR = TopJetv4.DeltaR(PuppiJetv4);
      if (dR < mindR && p.numberOfDaughters()>1) {  
	//	MatchedPuppiJet = pjet;
        mindR = dR;                                                                                                                                                   
      }                                                                                                                                                               
    }            
    //    if(mindR<0.8 && p.numberOfDaughters()>1){ 
    if(mindR<1.0 && p.numberOfDaughters()>1){ 
      toppuppijet__pt_matched_ttag ->Fill(p.pt()                          , weight);
      toppuppijet__eta_matched_ttag->Fill(p.eta()                         , weight);
      toppuppijet__phi_matched_ttag->Fill(p.phi()                         , weight);
      toppuppijet__CSV_matched_ttag->Fill(p.btag_combinedSecondaryVertex(), weight);
      //Calculate SoftDrop on fly
      TLorentzVector SoftDropv4(0,0,0,0);
      for(const auto & subjet : p.subjets()) {
	TLorentzVector SubJetv4;
	SubJetv4.SetPtEtaPhiE(subjet.pt(),subjet.eta(),subjet.phi(),subjet.energy());
	SoftDropv4 = SoftDropv4 + SubJetv4;
      }
      toppuppijet__Msdp_matched_ttag->Fill(SoftDropv4.M(), weight);
      toppuppijet__tau32_matched_ttag->Fill(p.tau3()/p.tau2() , weight);
      toppuppijet__NumSubjets_matched_ttag->Fill(p.numberOfDaughters() , weight);
      toppuppijet__jetID_matched_ttag->Fill(i, weight);
      //      if((p.tau3()/p.tau2())>0.65)      std::cout<<"TTbarLJHists: LOOK toppuppijet_matched tau32 = "<<p.tau3()/p.tau2()<<std::endl;
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
    wlep__pt__jet1__pt->Fill((event.met->v4()+lep1->v4()).Pt()/event.jets->at(0).pt(), weight);
    wlep__Mt->Fill(sqrt(2*event.met->pt()*lep1->pt()*(1.-cos(uhh2::deltaPhi(*event.met, *lep1)))), weight);
  }

  TMVA_response->Fill(event.get(tt_tmva_response), weight);
  WJets_TMVA_response->Fill(event.get(wjets_tmva_response), weight);
  jet1_m->Fill(event.get(h_jet1_m),weight);
  jet1_csv->Fill(event.get(h_jet1_csv),weight);
  jet2_csv->Fill(event.get(h_jet2_csv),weight);
  jet2_m->Fill(event.get(h_jet2_m),weight);

  DRpt->Fill(event.get(h_DRpt),weight);
  ht_met_lep_norm->Fill(event.get(h_ht_met_lep_norm),weight);
  lep1__minDR_norm->Fill(event.get(h_lep1__minDR_norm),weight);
  lep1__pTrel_jet_norm->Fill(event.get(h_lep1__pTrel_jet_norm),weight);
  s33->Fill(event.get(h_s33),weight);
  //  njets->Fill(event.get(h_njets),weight);

  // // jet flavor for top tagged jet                                                                                                                                    
  // std::vector<std::string> fla_strs;                                                                                                                                 
  // fla_strs.reserve(2);                                                                                                                                               
  // fla_strs.push_back("");                         
  // int jfla(21);                                                                                                                                            
  // float tgen_pt(-1.);                                          
  // if(!event.isRealData){
  //   const TopJet& tjet = toptags.at(0);  //only one top-tag jet is expected in the semileptonic channel
  //   for(const auto& genp : *event.genparticles){
  //     if(std::abs(genp.pdgId()) != 6) continue;
  //     if(uhh2::deltaR(tjet, genp) < 0.4 ){ 
  // 	jfla = 6; tgen_pt = genp.pt(); 
  // 	break; 
  //     } 
  //   }
  //   if  (jfla == 6) fla_strs.push_back("__t");
  //   else            fla_strs.push_back("__l");                                                                                                                       
  //   //std::cout<<"jfla = "<<jfla<<std::endl;                                                                                                                         
  // }                                                                                                                                                                 
  // for(const auto& fla : fla_strs){
  // }
  return;
}
