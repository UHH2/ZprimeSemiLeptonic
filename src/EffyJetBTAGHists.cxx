#include <UHH2/ZprimeSemiLeptonic/include/EffyJetBTAGHists.h>

#include <UHH2/core/include/Utils.h>
#include <UHH2/core/include/LorentzVector.h>

#include <UHH2/common/include/Utils.h>

EffyJetBTAGHists::EffyJetBTAGHists(uhh2::Context& ctx, const std::string& dirname, const TopJetId& ttag_id, const float min_dr): HistsBASE(ctx, dirname){

  // t-tagger
  ttagID_ = ttag_id;
  minDR_ttag_jet_ = min_dr;
  check_subjets_ = true;

  init();
}

void EffyJetBTAGHists::init(){

  // histograms
  book_TH1F("wgt", 120, -6, 6);
  book_TH1F("pvN", 60, 0, 60);

  std::vector<std::string> posx_fla({"", "__b", "__c", "__l"});

  for(const auto& fla: posx_fla){

    book_TH2F("CSV__vs__jetA__pt" +fla, 1000, 0, 1, 360, 0, 1800);
    book_TH2F("CSV__vs__jetA__eta"+fla, 1000, 0, 1,  60, -3, 3);
    book_TH2F("CSV__vs__jetA__phi"+fla, 1000, 0, 1,  60, -3.15, 3.15);
  }

  if(check_subjets_){

    for(const auto& fla: posx_fla){

      book_TH2F("CSV__vs__SUBjetA__pt" +fla, 1000, 0, 1, 360, 0, 1800);
      book_TH2F("CSV__vs__SUBjetA__eta"+fla, 1000, 0, 1,  60, -3, 3);
      book_TH2F("CSV__vs__SUBjetA__phi"+fla, 1000, 0, 1,  60, -3.15, 3.15);
    }

    for(const auto& fla: posx_fla){

      book_TH2F("CSV__vs__OUTjetA__pt" +fla, 1000, 0, 1, 360, 0, 1800);
      book_TH2F("CSV__vs__OUTjetA__eta"+fla, 1000, 0, 1,  60, -3, 3);
      book_TH2F("CSV__vs__OUTjetA__phi"+fla, 1000, 0, 1,  60, -3.15, 3.15);
    }
  }

  return;
}

void EffyJetBTAGHists::fill(const uhh2::Event& event){

  assert(event.pvs && event.jets);
  if(check_subjets_) assert(event.topjets);

  const float weight = event.weight;
  H1("wgt")->Fill(weight);

  // PV
  H1("pvN")->Fill(event.pvs->size(), weight);

  // JET
  for(const auto& jet : *event.jets){

    const int   jfla = std::abs(jet.hadronFlavor());
    const float jCSV = jet.btag_combinedSecondaryVertex();

    std::vector<std::string> fla_strs;
    fla_strs.reserve(2);
    fla_strs.push_back("");

    if     (jfla ==  5) fla_strs.push_back("__b");
    else if(jfla ==  4) fla_strs.push_back("__c");
    else                fla_strs.push_back("__l");

    for(const auto& fla : fla_strs){

      H2("CSV__vs__jetA__pt" +fla)->Fill(jCSV, jet.pt() , weight);
      H2("CSV__vs__jetA__eta"+fla)->Fill(jCSV, jet.eta(), weight);
      H2("CSV__vs__jetA__phi"+fla)->Fill(jCSV, jet.phi(), weight);
    }
  }

  // TOPJET (subjet b-tagging)
  if(check_subjets_){

    const TopJet* ttagjet(0);
    for(const auto& tjet : *event.topjets){

      bool ttag = ttagID_(tjet, event);
      bool ttag_update = ttag && (!ttagjet || (ttagjet->pt() < tjet.pt()));

      if(ttag_update) ttagjet = &tjet;
    }

    if(ttagjet){

      // ttag subjets
      for(const auto& subjet : ttagjet->subjets()){

        const int   jfla = std::abs(subjet.hadronFlavor());
        const float jCSV = subjet.btag_combinedSecondaryVertex();

        std::vector<std::string> fla_strs;
        fla_strs.reserve(2);
        fla_strs.push_back("");

        if     (jfla ==  5) fla_strs.push_back("__b");
        else if(jfla ==  4) fla_strs.push_back("__c");
        else                fla_strs.push_back("__l");

        for(const auto& fla : fla_strs){

          H2("CSV__vs__SUBjetA__pt" +fla)->Fill(jCSV, subjet.pt() , weight);
          H2("CSV__vs__SUBjetA__eta"+fla)->Fill(jCSV, subjet.eta(), weight);
          H2("CSV__vs__SUBjetA__phi"+fla)->Fill(jCSV, subjet.phi(), weight);
        }
      }

      // outside jets
      for(const auto& jet : *event.jets){

        if(!(uhh2::deltaR(*ttagjet, jet) > minDR_ttag_jet_)) continue;

        const int   jfla = std::abs(jet.hadronFlavor());
        const float jCSV = jet.btag_combinedSecondaryVertex();

        std::vector<std::string> fla_strs;
        fla_strs.reserve(2);
        fla_strs.push_back("");

        if     (jfla ==  5) fla_strs.push_back("__b");
        else if(jfla ==  4) fla_strs.push_back("__c");
        else                fla_strs.push_back("__l");

        for(const auto& fla : fla_strs){

          H2("CSV__vs__OUTjetA__pt" +fla)->Fill(jCSV, jet.pt() , weight);
          H2("CSV__vs__OUTjetA__eta"+fla)->Fill(jCSV, jet.eta(), weight);
          H2("CSV__vs__OUTjetA__phi"+fla)->Fill(jCSV, jet.phi(), weight);
        }
      }
    }
  }

  return;
}
