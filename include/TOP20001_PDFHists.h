#pragma once

#include <string>
#include <math.h>
#include <sstream>
#include <iostream>

#include "TH1F.h"
#include <TLorentzVector.h>

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_TTbarGen.h"

namespace uhh2 {
  class TOP20001_PDFHists: public uhh2::Hists {
  public:
    explicit TOP20001_PDFHists(uhh2::Context&, const std::string&);
    virtual void fill(const uhh2::Event&) override;
    std::string mtt_hist_names[100];
    std::string cts_bin1_hist_names[100];
    std::string cts_bin2_hist_names[100];
    std::string cts_bin3_hist_names[100];
    std::string cts_bin4_hist_names[100];
    std::string cts_bin5_hist_names[100];
    std::string cts_bin6_hist_names[100];

  protected:
    bool is_mc;
    bool is_alps;
    uhh2::Event::Handle<TOP20001_TTbarGen> h_ttbargen;
    virtual ~TOP20001_PDFHists();
  };
}
