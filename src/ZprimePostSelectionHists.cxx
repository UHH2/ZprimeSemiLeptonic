#include "UHH2/ZprimeSemiLeptonic/include/ZprimePostSelectionHists.h"
#include "UHH2/core/include/Utils.h"
#include "UHH2/common/include/Utils.h"

ZprimePostSelectionHists::ZprimePostSelectionHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname){

  wgt = book<TH1F>("weight", ";event weight", 120, 0, 12);

  // PV
  pvN = book<TH1F>("pvN", ";# of primary vertices", 60, 0, 60);

  // MUON
  muoN = book<TH1F>("muoN", ";# of muons", 20, 0, 20);
  muo1__pt = book<TH1F>("muo1__pt", ";muon p_{T} [GeV]", 240, 0, 1200);
  muo1__eta = book<TH1F>("muo1__eta", ";muon #eta", 60, -3, 3);
  muo1__minDR_jet = book<TH1F>("muo1__minDR_jet", ";#DeltaR_{min}(#mu, jet)", 60, 0, 6);
  muo1__pTrel_jet = book<TH1F>("muo1__pTrel_jet", ";p_{T, rel}(#mu, jet)", 180, 0, 180);
  muo1__minDR_topjet = book<TH1F>("muo1__minDR_topjet", ";#DeltaR_{min}(#mu, topjet)", 60, 0, 6);

  // ELECTRON
  eleN = book<TH1F>("eleN", ";# of electrons", 20, 0, 20);
  ele1__pt = book<TH1F>("ele1__pt", ";electron p_{T} [GeV]", 240, 0, 1200);
  ele1__eta = book<TH1F>("ele1__eta", ";electron #eta", 60, -3, 3);
  ele1__minDR_jet = book<TH1F>("ele1__minDR_jet", ";#DeltaR_{min}(e, jet)", 60, 0, 6);
  ele1__pTrel_jet = book<TH1F>("ele1__pTrel_jet", ";p_{T, rel}(e, jet)", 180, 0, 180);
  ele1__minDR_topjet = book<TH1F>("ele1__minDR_topjet", ";#DeltaR_{min}(e, topjet)", 60, 0, 6);

  // JET
  jetN = book<TH1F>("jetN", ";# of jets", 20, 0, 20);
  jet1__pt = book<TH1F>("jet1__pt", ";jet p_{T} [GeV]", 180, 0, 1800);
  jet1__eta = book<TH1F>("jet1__eta", ";jet #eta", 60, -3, 3);
  jet2__pt = book<TH1F>("jet2__pt", ";jet p_{T} [GeV]", 180, 0, 1800);
  jet2__eta = book<TH1F>("jet2__eta", ";jet #eta", 60, -3, 3);
  jet3__pt = book<TH1F>("jet3__pt", ";jet p_{T} [GeV]", 180, 0, 1800);
  jet3__eta = book<TH1F>("jet3__eta", ";jet #eta", 60, -3, 3);

  // TOPJET
  topjetN = book<TH1F>("topjetN", ";# of topjets", 20, 0, 20);
  topjet1__pt = book<TH1F>("topjet1__pt", ";topjet p_{T} [GeV]", 180, 0, 1800);
  topjet1__eta = book<TH1F>("topjet1__eta", ";topjet #eta", 60, -3, 3);
  topjet2__pt = book<TH1F>("topjet2__pt", ";topjet p_{T} [GeV]", 180, 0, 1800);
  topjet2__eta = book<TH1F>("topjet2__eta", ";topjet #eta", 60, -3, 3);

  // MET
  met__pt = book<TH1F>("met__pt", ";MET [GeV]", 180, 0, 1800);
  met__phi = book<TH1F>("met__phi", ";MET #phi", 72, -3.6, 3.6);
  htlep__pt = book<TH1F>("htlep__pt", ";H_{T}^{lep} [GeV]", 180, 0, 1800);
  met_VS_dphi_lep1 = book<TH2F>("met_VS_dphi_lep1", ";MET [GeV];#Delta#phi(MET, l1)", 180, 0, 1800, 60, 0, 3.6);
  met_VS_dphi_jet1 = book<TH2F>("met_VS_dphi_jet1", ";MET [GeV];#Delta#phi(MET, l1)", 180, 0, 1800, 60, 0, 3.6);
}

void ZprimePostSelectionHists::fill(const uhh2::Event& event){

  assert(event.pvs && event.muons && event.electrons);
  assert(event.jets && event.topjets && event.met);

  const double weight = event.weight;
  wgt->Fill(weight);

  // PV
  pvN->Fill(event.pvs->size(), weight);

  // MUON
  int muo_n(event.muons->size());
  muoN->Fill(muo_n, weight);

  if(muo_n){
    const Particle& p = event.muons->at(0);

    float minDR_jet(-1.), pTrel_jet(-1.);
    std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    float minDR_topjet(uhh2::infinity);
    for(const auto& tj: *event.topjets)
      if(uhh2::deltaR(p, tj) < minDR_topjet) minDR_topjet = uhh2::deltaR(p, tj);

    muo1__pt->Fill(p.pt(), weight);
    muo1__eta->Fill(p.eta(), weight);
    muo1__minDR_jet->Fill(minDR_jet, weight);
    muo1__pTrel_jet->Fill(pTrel_jet, weight);
    muo1__minDR_topjet->Fill(minDR_topjet, weight);
  }

  // ELECTRON
  int ele_n(event.electrons->size());
  eleN->Fill(ele_n, weight);

  if(ele_n){
    const Particle& p = event.electrons->at(0);

    float minDR_jet(-1.), pTrel_jet(-1.);
    std::tie(minDR_jet, pTrel_jet) = drmin_pTrel(p, *event.jets);

    float minDR_topjet(uhh2::infinity);
    for(const auto& tj: *event.topjets)
      if(uhh2::deltaR(p, tj) < minDR_topjet) minDR_topjet = uhh2::deltaR(p, tj);

    ele1__pt->Fill(p.pt(), weight);
    ele1__eta->Fill(p.eta(), weight);
    ele1__minDR_jet->Fill(minDR_jet, weight);
    ele1__pTrel_jet->Fill(pTrel_jet, weight);
    ele1__minDR_topjet->Fill(minDR_topjet, weight);
  }

  // JET
  int jet_n(event.jets->size());
  jetN->Fill(jet_n, weight);

  for(int i=0; i<std::min(3, jet_n); ++i){
    const Particle& p = event.jets->at(i);

    if(i == 0){
      jet1__pt->Fill(p.pt(), weight);
      jet1__eta->Fill(p.eta(), weight);
    }
    else if(i == 1){
      jet2__pt->Fill(p.pt(), weight);
      jet2__eta->Fill(p.eta(), weight);
    }
    else if(i == 2){
      jet3__pt->Fill(p.pt(), weight);
      jet3__eta->Fill(p.eta(), weight);
    }
  }

  // TOPJET
  int topjet_n(event.topjets->size());
  topjetN->Fill(topjet_n, weight);

  for(int i=0; i<std::min(2, topjet_n); ++i){
    const Particle& p = event.topjets->at(i);

    if(i == 0){
      topjet1__pt->Fill(p.pt(), weight);
      topjet1__eta->Fill(p.eta(), weight);
    }
    else if(i == 1){
      topjet2__pt->Fill(p.pt(), weight);
      topjet2__eta->Fill(p.eta(), weight);
    }
  }

  // MET
  met__pt->Fill(event.met->pt(), weight);
  met__phi->Fill(event.met->phi(), weight);

  const Particle* lep1(0);
  float max_lep_pt(0.);
  for(const auto& l : *event.muons)     if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }
  for(const auto& l : *event.electrons) if(l.pt() > max_lep_pt){ lep1 = &l; max_lep_pt = l.pt(); }
  if(lep1) htlep__pt->Fill(event.met->pt()+lep1->pt(), weight);

  /* triangular cuts vars */
  if(lep1) met_VS_dphi_lep1->Fill(event.met->pt(), fabs(uhh2::deltaPhi(*event.met, *lep1)), weight);
  if(event.jets->size()) met_VS_dphi_jet1->Fill(event.met->pt(), fabs(uhh2::deltaPhi(*event.met, event.jets->at(0))), weight);

  return;
}
