#pragma once
#include "UHH2/core/include/Event.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/core/include/Jet.h"
#include "UHH2/core/include/TopJet.h"
#include "UHH2/core/include/AnalysisModule.h"

#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <math.h>
#include <TH1F.h>
#include <TGraph.h>
#include <TGraphAsymmErrors.h>
#include <TFile.h>

using namespace std;

namespace uhh2 {

  class ElecTriggerSF: public uhh2::AnalysisModule{
  public:

    explicit ElecTriggerSF(uhh2::Context & ctx, std::string var_, TString pe, TString year);
    virtual bool process(uhh2::Event & ) override;

  private:
    TH1F *h_sf_lo, *h_sf_me, *h_sf_hi;
    TH1F *h_sf_lo_up, *h_sf_me_up, *h_sf_hi_up;
    TH1F *h_sf_lo_down, *h_sf_me_down, *h_sf_hi_down;
    bool isMC, is_Muon;
    TString pteta, var;
    uhh2::Event::Handle<float> h_ele_weight, h_ele_weight_up, h_ele_weight_down;

  };

}
