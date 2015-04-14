#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

#include <string>

class ZprimePreSelectionHists : public uhh2::Hists {
 public:
  ZprimePreSelectionHists(uhh2::Context&, const std::string&);

  virtual void fill(const uhh2::Event&) override;
};
