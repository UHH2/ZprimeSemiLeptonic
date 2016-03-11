#include <UHH2/ZprimeSemiLeptonic/include/SF_topptREWGT.h>

#include <cmath>

weightcalc_topptREWGT::weightcalc_topptREWGT(uhh2::Context& ctx, const std::string& ttgen_name, const float a, const float b):
  h_ttbargen_(ctx.get_handle<TTbarGen>(ttgen_name)), a_(a), b_(b) {}

float weightcalc_topptREWGT::weight(const uhh2::Event& evt_, const std::string& sys_) const {

  if(evt_.isRealData) return 1.;

  const TTbarGen& ttbargen = evt_.get(h_ttbargen_);

  float wgt(1.);

  if(ttbargen.DecayChannel() != TTbarGen::e_notfound){

    float tpt1 = ttbargen.Top()    .v4().Pt();
    float tpt2 = ttbargen.Antitop().v4().Pt();

    tpt1 = std::min(tpt1, float(400.));
    tpt2 = std::min(tpt2, float(400.));

    wgt = sqrt(exp(a_+b_*tpt1)*exp(a_+b_*tpt2));
  }
  else wgt = 1.;

  if     (sys_ == "ct") wgt = wgt;
  else if(sys_ == "up") wgt = 1.;
  else if(sys_ == "dn") wgt = wgt * wgt;
  else throw std::runtime_error("weightcalc_topptREWGT::weight -- undefined key for systematic variation: "+sys_);

  return wgt;
}
