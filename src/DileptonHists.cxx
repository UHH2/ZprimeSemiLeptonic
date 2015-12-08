#include <UHH2/ZprimeSemiLeptonic/include/DileptonHists.h>

#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/Utils.h>

DileptonHists::DileptonHists(uhh2::Context& ctx, const std::string& dirname):
  HistsBASE(ctx, dirname) {

  init();
}

void DileptonHists::init(){

  // DI-MUON
  book_TH1F("dimuo1__charge", 5, -2, 3);
  book_TH1F("dimuo1__M"     , 360, 0, 360);
  book_TH1F("dimuo1__pt"    , 180, 0, 1800);
  book_TH1F("dimuo1__eta"   , 60, -3, 3);
  book_TH1F("dimuo1__phi"   , 60, -3.15, 3.15);
  book_TH1F("dimuo1__DR12"  , 60, 0, 6);

  // DI-ELECTRON
  book_TH1F("diele1__charge", 5, -2, 3);
  book_TH1F("diele1__M"     , 360, 0, 360);
  book_TH1F("diele1__pt"    , 180, 0, 1800);
  book_TH1F("diele1__eta"   , 60, -3, 3);
  book_TH1F("diele1__phi"   , 60, -3.15, 3.15);
  book_TH1F("diele1__DR12"  , 60, 0, 6);

  return;
}

void DileptonHists::fill(const uhh2::Event& event){

  const float weight = event.weight;

  if(event.muons->size() == 2){

    const auto& lep1 = event.muons->at(0);
    const auto& lep2 = event.muons->at(1);

    auto dilep = lep1.v4() + lep2.v4();

    H1("dimuo1__charge")->Fill(lep1.charge()+lep2.charge(), weight);
    H1("dimuo1__DR12")  ->Fill(uhh2::deltaR(lep1, lep2)   , weight);

    H1("dimuo1__M")     ->Fill(dilep.M()  , weight);
    H1("dimuo1__pt")    ->Fill(dilep.Pt() , weight);
    H1("dimuo1__eta")   ->Fill(dilep.Eta(), weight);
    H1("dimuo1__phi")   ->Fill(dilep.Phi(), weight);
  }
  else if(event.electrons->size() == 2){

    const auto& lep1 = event.electrons->at(0);
    const auto& lep2 = event.electrons->at(1);

    auto dilep = lep1.v4() + lep2.v4();

    H1("diele1__charge")->Fill(lep1.charge()+lep2.charge(), weight);
    H1("diele1__DR12")  ->Fill(uhh2::deltaR(lep1, lep2)   , weight);

    H1("diele1__M")     ->Fill(dilep.M()  , weight);
    H1("diele1__pt")    ->Fill(dilep.Pt() , weight);
    H1("diele1__eta")   ->Fill(dilep.Eta(), weight);
    H1("diele1__phi")   ->Fill(dilep.Phi(), weight);
  }

  return;
}
