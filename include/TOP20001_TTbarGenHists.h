#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/Hists.h"

#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_TTbarGen.h"

/** \brief Histograms for ttbar quantities on generator (parton) level
*
* TOP20001_TTbarGen container has to be filled before calling this histogram class
*/
class TOP20001_TTbarGenHists: public uhh2::Hists{
public:
  TOP20001_TTbarGenHists(uhh2::Context & ctx, const std::string & dirname);

  virtual void fill(const uhh2::Event & ev) override;

protected:
  uhh2::Event::Handle<TOP20001_TTbarGen> h_ttbargen;
  TH1F *pt_thad;
  TH1F *pt_tlep;
  TH1F *ST;
  TH1F *absy_thad;
  TH1F *absy_tlep;
  TH1F *deltaabsy_ttbar;
  TH1F *absdeltay_ttbar;
  TH1F *m_ttbar;
  TH1F *pt_ttbar;
  TH1F *absy_ttbar;
  TH1F *phi_ttbar;
  TH1F *cts;
  TH1F *cts_mtt250To420;
  TH1F *cts_mtt420To520;
  TH1F *cts_mtt520To620;
  TH1F *cts_mtt620To800;
  TH1F *cts_mtt800To1000;
  TH1F *cts_mtt1000To3500;
};
