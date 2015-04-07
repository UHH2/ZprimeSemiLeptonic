#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

#include <string>
#include <TH1F.h>
#include <TH2F.h>

class ZprimeSelectionHists : public uhh2::Hists {
 public:
  ZprimeSelectionHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

 private:
  TH1F* wgt;

  // PV 
  TH1F* pvN;

  // MUON
  TH1F* muoN;
  TH1F* muo1__pt;
  TH1F* muo1__eta;
  TH1F* muo1__minDR_jet;
  TH1F* muo1__pTrel_jet;
  TH1F* muo1__minDR_topjet;
  TH1F* muo2__pt;
  TH1F* muo2__eta;
  TH1F* muo2__minDR_jet;
  TH1F* muo2__pTrel_jet;
  TH1F* muo2__minDR_topjet;

  // ELECTRON
  TH1F* eleN;
  TH1F* ele1__pt;
  TH1F* ele1__eta;
  TH1F* ele1__minDR_jet;
  TH1F* ele1__pTrel_jet;
  TH1F* ele1__minDR_topjet;
  TH1F* ele2__pt;
  TH1F* ele2__eta;
  TH1F* ele2__minDR_jet;
  TH1F* ele2__pTrel_jet;
  TH1F* ele2__minDR_topjet;

  // JET
  TH1F* jetN;
  TH1F* jet1__pt;
  TH1F* jet1__eta;
  TH1F* jet2__pt;
  TH1F* jet2__eta;
  TH1F* jet3__pt;
  TH1F* jet3__eta;

  // TOPJET
  TH1F* topjetN;
  TH1F* topjet1__pt;
  TH1F* topjet1__eta;
  TH1F* topjet2__pt;
  TH1F* topjet2__eta;

  // MET
  TH1F* met__pt;
  TH1F* met__phi;
  TH1F* htlep__pt;
  TH2F* met_VS_dphi_lep1;
  TH2F* met_VS_dphi_jet1;
};
