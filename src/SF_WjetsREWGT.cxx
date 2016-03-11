#include <UHH2/ZprimeSemiLeptonic/include/SF_WjetsREWGT.h>

weightcalc_WjetsREWGT::weightcalc_WjetsREWGT() {}

float weightcalc_WjetsREWGT::weight(const uhh2::Event& evt_) const {

  if(evt_.isRealData) return 1.;

  float wgt(1.);

  assert(evt_.genparticles);

  const GenParticle* genW_ptr = genW(*evt_.genparticles);

  if(genW_ptr){

    const auto& gen_W = *genW_ptr;

    wgt  = weightcalc_WjetsREWGT::kfactor_QCD(gen_W);
    wgt *= weightcalc_WjetsREWGT::kfactor_EWK(gen_W);
  }
  else wgt = 1.;

  return wgt;
}

float weightcalc_WjetsREWGT::kfactor_QCD(const GenParticle& genw) const {

  float K(1.);

  const float wpt = genw.pt();

  if     (wpt < 150.) K = 1.89123;// 1.685005;
  else if(wpt < 200.) K = 1.70414;// 1.552560;
  else if(wpt < 250.) K = 1.60726;// 1.522595;
  else if(wpt < 300.) K = 1.57206;// 1.520624;
  else if(wpt < 350.) K = 1.51689;// 1.432282;
  else if(wpt < 400.) K = 1.41090;// 1.457417;
  else if(wpt < 500.) K = 1.30758;// 1.368499;
  else if(wpt < 600.) K = 1.32046;// 1.358024;
  else                K = 1.26853;// 1.164847;

  return K;
}

float weightcalc_WjetsREWGT::kfactor_EWK(const GenParticle& genw) const {

  float K(1.);

  const float wpt = genw.pt();

  if     (wpt < 150.) K = 0.980859;// 0.984525;
  else if(wpt < 200.) K = 0.962119;// 0.969079;
  else if(wpt < 250.) K = 0.944429;// 0.954627;
  else if(wpt < 300.) K = 0.927686;// 0.941059;
  else if(wpt < 350.) K = 0.911802;// 0.928284;
  else if(wpt < 400.) K = 0.896700;// 0.916220;
  else if(wpt < 500.) K = 0.875368;// 0.899312;
  else if(wpt < 600.) K = 0.849097;// 0.878693;
  else                K = 0.792159;// 0.834718;

  return K;
}

const GenParticle* weightcalc_WjetsREWGT::genW(const std::vector<GenParticle>& genps) const {

  const GenParticle* p(0);

  unsigned int W_N(0);
  for(const auto& genp : genps){

    const bool is_me = (20 <= genp.status() && genp.status() <= 30);
    if(!is_me) continue;

    const bool has_mo1 = (genp.mother1() != (unsigned short)(-1));
    if(!has_mo1) continue;

    const bool has_mo2 = (genp.mother2() != (unsigned short)(-1));
    if(!has_mo2) continue;

    const bool is_W = (std::abs(genp.pdgId()) == 24);
    if(!is_W) continue;

    if(is_W){

      if(W_N > 0){ p = 0; break; }

      p = &genp;
      ++W_N;
    }
  }

  return p;
}
