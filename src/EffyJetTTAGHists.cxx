#include <UHH2/ZprimeSemiLeptonic/include/EffyJetTTAGHists.h>

#include <UHH2/core/include/Utils.h>
#include <UHH2/core/include/LorentzVector.h>

#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/TopJetIds.h>

EffyJetTTAGHists::EffyJetTTAGHists(uhh2::Context& ctx, const std::string& dirname, const TopJetId& ttag_id, const float min_dr): HistsBASE(ctx, dirname){

  // t-tagger
  ttagID_ = ttag_id;
  minDR_ttag_jet_ = min_dr;
  maxDR_tjet_gentop_ = .8;

  init();
}

void EffyJetTTAGHists::init(){

  // histograms
  book_TH1F("wgt", 120, -6, 6);
  book_TH1F("pvN", 60, 0, 60);

  std::vector<std::string> posx_fla({"", "__t", "__l"});

  for(const auto& fla: posx_fla){

    book_TH1F("tjetA__pt"   +fla, 360,  0, 3600);
    book_TH1F("tjetA__eta"  +fla, 60, -3, 3);
    book_TH1F("tjetA__subjN"+fla, 8,  0, 8);
    book_TH1F("tjetA__M"    +fla, 240, 0, 600);
    book_TH1F("tjetA__Mgro" +fla, 240, 0, 600);
    book_TH1F("tjetA__Mpru" +fla, 240, 0, 600);
    book_TH1F("tjetA__Msdp" +fla, 240, 0, 600);
    book_TH1F("tjetA__Mmin" +fla, 180, 0, 180);
    book_TH1F("tjetA__tau32"+fla, 120, 0, 1.2);

    book_TH1F("tjetA__CEF"  +fla, 120, 0, 1.2);
    book_TH1F("tjetA__CHF"  +fla, 120, 0, 1.2);
    book_TH1F("tjetA__NEF"  +fla, 120, 0, 1.2);
    book_TH1F("tjetA__NHF"  +fla, 120, 0, 1.2);
    book_TH1F("tjetA__MuF"  +fla, 120, 0, 1.2);
    book_TH1F("tjetA__PhF"  +fla, 120, 0, 1.2);
    book_TH1F("tjetA__ChN"  +fla, 120, 0, 120);
    book_TH1F("tjetA__CHN"  +fla, 120, 0, 120);
    book_TH1F("tjetA__MuN"  +fla,  12, 0,  12);
    book_TH1F("tjetA__ElN"  +fla,  12, 0,  12);
    book_TH1F("tjetA__NeN"  +fla, 120, 0, 120);
    book_TH1F("tjetA__NHN"  +fla, 120, 0, 120);
    book_TH1F("tjetA__PhN"  +fla, 120, 0, 120);

    book_TH2F("tjetA__pt__vs__tjetA__subjN"  +fla, 360, 0, 3600,   8, 0, 8);
    book_TH2F("tjetA__pt__vs__tjetA__M"      +fla, 360, 0, 3600, 240, 0, 600);
    book_TH2F("tjetA__pt__vs__tjetA__Mgro"   +fla, 360, 0, 3600, 240, 0, 600);
    book_TH2F("tjetA__pt__vs__tjetA__Mpru"   +fla, 360, 0, 3600, 240, 0, 600);
    book_TH2F("tjetA__pt__vs__tjetA__Msdp"   +fla, 360, 0, 3600, 240, 0, 600);
    book_TH2F("tjetA__pt__vs__tjetA__Mmin"   +fla, 360, 0, 3600, 180, 0, 180);
    book_TH2F("tjetA__pt__vs__tjetA__tau32"  +fla, 360, 0, 3600, 120, 0, 1.2);
    book_TH2F("tjetA__M__vs__tjetA__subjN"   +fla, 240, 0, 600,   8,  0, 8);
    book_TH2F("tjetA__M__vs__tjetA__tau32"   +fla, 240, 0, 600, 120,  0, 1.2);
    book_TH2F("tjetA__Mgro__vs__tjetA__subjN"+fla, 240, 0, 600,   8,  0, 8);
    book_TH2F("tjetA__Mgro__vs__tjetA__tau32"+fla, 240, 0, 600, 120,  0, 1.2);
    book_TH2F("tjetA__Mpru__vs__tjetA__subjN"+fla, 240, 0, 600,   8,  0, 8);
    book_TH2F("tjetA__Mpru__vs__tjetA__tau32"+fla, 240, 0, 600, 120,  0, 1.2);
    book_TH2F("tjetA__Msdp__vs__tjetA__subjN"+fla, 240, 0, 600,   8,  0, 8);
    book_TH2F("tjetA__Msdp__vs__tjetA__tau32"+fla, 240, 0, 600, 120,  0, 1.2);

    book_TH2F("TAG__vs__tjetA__pt"     +fla, 2, 0, 2, 360, 0, 3600);
    book_TH2F("TAG__vs__tjetA__eta"    +fla, 2, 0, 2,  60, -3, 3);
    book_TH2F("TAG__vs__tjetA__phi"    +fla, 2, 0, 2,  60, -3.15, 3.15);
    book_TH2F("TAG__vs__tjetA__subjN"  +fla, 2, 0, 2,   8, 0, 8);
    book_TH2F("TAG__vs__tjetA__M"      +fla, 2, 0, 2, 240, 0, 600);
    book_TH2F("TAG__vs__tjetA__Mgro"   +fla, 2, 0, 2, 240, 0, 600);
    book_TH2F("TAG__vs__tjetA__Mpru"   +fla, 2, 0, 2, 240, 0, 600);
    book_TH2F("TAG__vs__tjetA__Msdp"   +fla, 2, 0, 2, 240, 0, 600);
    book_TH2F("TAG__vs__tjetA__Mmin"   +fla, 2, 0, 2, 180, 0, 180);
    book_TH2F("TAG__vs__tjetA__tau2"   +fla, 2, 0, 2, 120, 0, 1.2);
    book_TH2F("TAG__vs__tjetA__tau3"   +fla, 2, 0, 2, 120, 0, 1.2);
    book_TH2F("TAG__vs__tjetA__tau32"  +fla, 2, 0, 2, 120, 0, 1.2);
    book_TH2F("TAG__vs__tjetA__tgen_pt"+fla, 2, 0, 2, 360, 0, 3600);
  }

  return;
}

void EffyJetTTAGHists::fill(const uhh2::Event& event){

  assert(event.pvs && event.topjets);

  const double weight = event.weight;
  H1("wgt")->Fill(weight);

  // PV
  H1("pvN")->Fill(event.pvs->size(), weight);

  // TOPJET
  for(const auto& tjet : *event.topjets){

    // jet vars
    LorentzVector subj_sum_p4;
    for(const auto& subj : tjet.subjets()) subj_sum_p4 += subj.v4();

    const int   tjet_subjN = tjet.subjets().size();
    const float tjet_M     = tjet.v4().M();
    const float tjet_Mgro  = subj_sum_p4.M();
    const float tjet_Mpru  = tjet.prunedmass();
    const float tjet_Msdp  = tjet.softdropmass();
    const float tjet_Mmin  = m_disubjet_min(tjet);
    const float tjet_tau32 = tjet.tau2() ? (tjet.tau3() / tjet.tau2()) : (!tjet.tau3() ? 0. : 100.);

    // jet tag
    const bool jtag = ttagID_(tjet, event);

    // jet flavor
    std::vector<std::string> fla_strs;
    fla_strs.reserve(2);
    fla_strs.push_back("");

    int jfla(21);
    float tgen_pt(-1.);

    if(!event.isRealData){

      for(const auto& genp : *event.genparticles){

        if(std::abs(genp.pdgId()) != 6) continue;
        if(uhh2::deltaR(tjet, genp) < maxDR_tjet_gentop_){ jfla = 6; tgen_pt = genp.pt(); break; }
      }

      if  (jfla == 6) fla_strs.push_back("__t");
      else            fla_strs.push_back("__l");
    }

    for(const auto& fla : fla_strs){

      H1("tjetA__pt"   +fla)->Fill(tjet.pt() , weight);
      H1("tjetA__eta"  +fla)->Fill(tjet.eta(), weight);
      H1("tjetA__subjN"+fla)->Fill(tjet_subjN, weight);
      H1("tjetA__M"    +fla)->Fill(tjet_M    , weight);
      H1("tjetA__Mgro" +fla)->Fill(tjet_Mgro , weight);
      H1("tjetA__Mpru" +fla)->Fill(tjet_Mpru , weight);
      H1("tjetA__Msdp" +fla)->Fill(tjet_Msdp , weight);
      H1("tjetA__Mmin" +fla)->Fill(tjet_Mmin , weight);
      H1("tjetA__tau32"+fla)->Fill(tjet_tau32, weight);

      H1("tjetA__CEF"  +fla)->Fill(tjet.chargedEmEnergyFraction()    , weight);
      H1("tjetA__CHF"  +fla)->Fill(tjet.chargedHadronEnergyFraction(), weight);
      H1("tjetA__NEF"  +fla)->Fill(tjet.neutralEmEnergyFraction()    , weight);
      H1("tjetA__NHF"  +fla)->Fill(tjet.neutralHadronEnergyFraction(), weight);
      H1("tjetA__MuF"  +fla)->Fill(tjet.muonEnergyFraction()         , weight);
      H1("tjetA__PhF"  +fla)->Fill(tjet.photonEnergyFraction()       , weight);
      H1("tjetA__ChN"  +fla)->Fill(tjet.chargedMultiplicity()        , weight);
      H1("tjetA__MuN"  +fla)->Fill(tjet.muonMultiplicity()           , weight);
      H1("tjetA__ElN"  +fla)->Fill(tjet.electronMultiplicity()       , weight);
      H1("tjetA__NeN"  +fla)->Fill(tjet.neutralMultiplicity()        , weight);
      H1("tjetA__PhN"  +fla)->Fill(tjet.photonMultiplicity()         , weight);

      const int tjet_chargedhadronN = tjet.chargedMultiplicity() - tjet.muonMultiplicity() - tjet.electronMultiplicity();
      const int tjet_neutralhadronN = tjet.neutralMultiplicity() - tjet.photonMultiplicity();

      H1("tjetA__CHN"  +fla)->Fill(tjet_chargedhadronN, weight);
      H1("tjetA__NHN"  +fla)->Fill(tjet_neutralhadronN, weight);

      H2("tjetA__pt__vs__tjetA__subjN"  +fla)->Fill(tjet.pt(), tjet_subjN, weight);
      H2("tjetA__pt__vs__tjetA__M"      +fla)->Fill(tjet.pt(), tjet_M    , weight);
      H2("tjetA__pt__vs__tjetA__Mgro"   +fla)->Fill(tjet.pt(), tjet_Mgro , weight);
      H2("tjetA__pt__vs__tjetA__Mpru"   +fla)->Fill(tjet.pt(), tjet_Mpru , weight);
      H2("tjetA__pt__vs__tjetA__Msdp"   +fla)->Fill(tjet.pt(), tjet_Msdp , weight);
      H2("tjetA__pt__vs__tjetA__Mmin"   +fla)->Fill(tjet.pt(), tjet_Mmin , weight);
      H2("tjetA__pt__vs__tjetA__tau32"  +fla)->Fill(tjet.pt(), tjet_tau32, weight);
      H2("tjetA__M__vs__tjetA__subjN"   +fla)->Fill(tjet_M   , tjet_subjN, weight);
      H2("tjetA__M__vs__tjetA__tau32"   +fla)->Fill(tjet_M   , tjet_tau32, weight);
      H2("tjetA__Mgro__vs__tjetA__subjN"+fla)->Fill(tjet_Mgro, tjet_subjN, weight);
      H2("tjetA__Mgro__vs__tjetA__tau32"+fla)->Fill(tjet_Mgro, tjet_tau32, weight);
      H2("tjetA__Mpru__vs__tjetA__subjN"+fla)->Fill(tjet_Mpru, tjet_subjN, weight);
      H2("tjetA__Mpru__vs__tjetA__tau32"+fla)->Fill(tjet_Mpru, tjet_tau32, weight);
      H2("tjetA__Msdp__vs__tjetA__subjN"+fla)->Fill(tjet_Msdp, tjet_subjN, weight);
      H2("tjetA__Msdp__vs__tjetA__tau32"+fla)->Fill(tjet_Msdp, tjet_tau32, weight);

      H2("TAG__vs__tjetA__pt"   +fla)->Fill(float(jtag), tjet.pt()  , weight);
      H2("TAG__vs__tjetA__eta"  +fla)->Fill(float(jtag), tjet.eta() , weight);
      H2("TAG__vs__tjetA__phi"  +fla)->Fill(float(jtag), tjet.phi() , weight);
      H2("TAG__vs__tjetA__subjN"+fla)->Fill(float(jtag), tjet_subjN , weight);
      H2("TAG__vs__tjetA__M"    +fla)->Fill(float(jtag), tjet_M     , weight);
      H2("TAG__vs__tjetA__Mgro" +fla)->Fill(float(jtag), tjet_Mgro  , weight);
      H2("TAG__vs__tjetA__Mpru" +fla)->Fill(float(jtag), tjet_Mpru  , weight);
      H2("TAG__vs__tjetA__Msdp" +fla)->Fill(float(jtag), tjet_Msdp  , weight);
      H2("TAG__vs__tjetA__Mmin" +fla)->Fill(float(jtag), tjet_Mmin  , weight);
      H2("TAG__vs__tjetA__tau2" +fla)->Fill(float(jtag), tjet.tau2(), weight);
      H2("TAG__vs__tjetA__tau3" +fla)->Fill(float(jtag), tjet.tau3(), weight);
      H2("TAG__vs__tjetA__tau32"+fla)->Fill(float(jtag), tjet_tau32 , weight);

      if(jfla == 6) H2("TAG__vs__tjetA__tgen_pt"+fla)->Fill(float(jtag), tgen_pt, weight);
    }
  }

  return;
}
