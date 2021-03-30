#pragma once

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

class ZprimeSemiLeptonicMulticlassNNHists: public uhh2::Hists {
public:
  explicit ZprimeSemiLeptonicMulticlassNNHists(uhh2::Context&, const std::string&);
  virtual void fill(const uhh2::Event&) override;

protected:
  void init();

TH1F *NN_out0, *NN_out1, *NN_out2;
uhh2::Event::Handle<double> h_NNoutput0;
uhh2::Event::Handle<double> h_NNoutput1;
uhh2::Event::Handle<double> h_NNoutput2;

  virtual ~ZprimeSemiLeptonicMulticlassNNHists();
};
      
