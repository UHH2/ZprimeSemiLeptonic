#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSystematicsHists.h"
#include "UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h"
#include "UHH2/core/include/Event.h"
#include <UHH2/core/include/Utils.h>
#include <UHH2/common/include/Utils.h>
#include "UHH2/common/include/JetIds.h"
#include <math.h>

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <UHH2/core/include/LorentzVector.h>

#include "TH1F.h"
#include "TH2D.h"
#include <iostream>
#include <string>

using namespace std;
using namespace uhh2;

ZprimeSemiLeptonicSystematicsHists::ZprimeSemiLeptonicSystematicsHists(uhh2::Context& ctx, const std::string& dirname):
Hists(ctx, dirname) {

  is_mc = ctx.get("dataset_type") == "MC";
  is_Muon = ctx.get("channel") == "muon";

  h_ele_reco           = ctx.get_handle<float>("weight_sfelec_reco");
  h_ele_reco_up        = ctx.get_handle<float>("weight_sfelec_reco_up");
  h_ele_reco_down      = ctx.get_handle<float>("weight_sfelec_reco_down");
  h_ele_id             = ctx.get_handle<float>("weight_sfelec_id");
  h_ele_id_up          = ctx.get_handle<float>("weight_sfelec_id_up");
  h_ele_id_down        = ctx.get_handle<float>("weight_sfelec_id_down");
  h_mu_reco            = ctx.get_handle<float>("muonrecSF_nominal");
  h_mu_reco_up         = ctx.get_handle<float>("muonrecSF_up");
  h_mu_reco_down       = ctx.get_handle<float>("muonrecSF_down");
  h_mu_iso             = ctx.get_handle<float>("weight_sfmu_iso");
  h_mu_iso_up          = ctx.get_handle<float>("weight_sfmu_iso_up");
  h_mu_iso_down        = ctx.get_handle<float>("weight_sfmu_iso_down");
  h_mu_id              = ctx.get_handle<float>("weight_sfmu_id");
  h_mu_id_up           = ctx.get_handle<float>("weight_sfmu_id_up");
  h_mu_id_down         = ctx.get_handle<float>("weight_sfmu_id_down");
  h_mu_trigger         = ctx.get_handle<float>("weight_sfmu_trigger");
  h_mu_trigger_up      = ctx.get_handle<float>("weight_sfmu_trigger_up");
  h_mu_trigger_down    = ctx.get_handle<float>("weight_sfmu_trigger_down");
  h_pu                 = ctx.get_handle<float>("weight_pu");
  h_pu_up              = ctx.get_handle<float>("weight_pu_up");
  h_pu_down            = ctx.get_handle<float>("weight_pu_down");
  h_prefiring          = ctx.get_handle<float>("prefiringWeight");
  h_prefiring_up       = ctx.get_handle<float>("prefiringWeightUp");
  h_prefiring_down     = ctx.get_handle<float>("prefiringWeightDown");
  h_toppt              = ctx.get_handle<float>("weight_toppt_nominal");
  h_toppt_a_up         = ctx.get_handle<float>("weight_toppt_a_up");
  h_toppt_a_down       = ctx.get_handle<float>("weight_toppt_a_down");
  h_toppt_b_up         = ctx.get_handle<float>("weight_toppt_b_up");
  h_toppt_b_down       = ctx.get_handle<float>("weight_toppt_b_down");
  h_murmuf_upup        = ctx.get_handle<float>("weight_murmuf_upup");
  h_murmuf_upnone      = ctx.get_handle<float>("weight_murmuf_upnone");
  h_murmuf_noneup      = ctx.get_handle<float>("weight_murmuf_noneup");
  h_murmuf_nonedown    = ctx.get_handle<float>("weight_murmuf_nonedown");
  h_murmuf_downnone    = ctx.get_handle<float>("weight_murmuf_downnone");
  h_murmuf_downdown    = ctx.get_handle<float>("weight_murmuf_downdown");
  h_isr_up             = ctx.get_handle<float>("weight_isr_20_05_up");
  h_isr_down           = ctx.get_handle<float>("weight_isr_20_05_down");
  h_fsr_up             = ctx.get_handle<float>("weight_fsr_20_05_up");
  h_fsr_down           = ctx.get_handle<float>("weight_fsr_20_05_down");
  h_btag               = ctx.get_handle<float>("weight_btagdisc_central");
  h_btag_cferr1_up     = ctx.get_handle<float>("weight_btagdisc_cferr1_up");
  h_btag_cferr1_down   = ctx.get_handle<float>("weight_btagdisc_cferr1_down");
  h_btag_cferr2_up     = ctx.get_handle<float>("weight_btagdisc_cferr2_up");
  h_btag_cferr2_down   = ctx.get_handle<float>("weight_btagdisc_cferr2_down");
  h_btag_hf_up         = ctx.get_handle<float>("weight_btagdisc_hf_up");
  h_btag_hf_down       = ctx.get_handle<float>("weight_btagdisc_hf_down");
  h_btag_hfstats1_up   = ctx.get_handle<float>("weight_btagdisc_hfstats1_up");
  h_btag_hfstats1_down = ctx.get_handle<float>("weight_btagdisc_hfstats1_down");
  h_btag_hfstats2_up   = ctx.get_handle<float>("weight_btagdisc_hfstats2_up");
  h_btag_hfstats2_down = ctx.get_handle<float>("weight_btagdisc_hfstats2_down");
  h_btag_lf_up         = ctx.get_handle<float>("weight_btagdisc_lf_up");
  h_btag_lf_down       = ctx.get_handle<float>("weight_btagdisc_lf_down");
  h_btag_lfstats1_up   = ctx.get_handle<float>("weight_btagdisc_lfstats1_up");
  h_btag_lfstats1_down = ctx.get_handle<float>("weight_btagdisc_lfstats1_down");
  h_btag_lfstats2_up   = ctx.get_handle<float>("weight_btagdisc_lfstats2_up");
  h_btag_lfstats2_down = ctx.get_handle<float>("weight_btagdisc_lfstats2_down");

  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  init();

}

void ZprimeSemiLeptonicSystematicsHists::init(){

  // Zprime reconstruction
  vector<float> bins_Zprime = {0,400,600,800,1000,1200,1400,1600,1800,2000,2200,2400,2600,2800,3000,3200,3400,3600,3800,4000,4400,4800,5200,5600,6000,6100};

  M_Zprime                    = book<TH1F>("M_Zprime", "M_{t#bar{t}} [GeV]",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_mu_reco_up         = book<TH1F>("M_Zprime_mu_reco_up",   "M_{t#bar{t}} [GeV] mu_reco_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_mu_reco_down       = book<TH1F>("M_Zprime_mu_reco_down", "M_{t#bar{t}} [GeV] mu_reco_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_pu_up              = book<TH1F>("M_Zprime_pu_up",   "M_{t#bar{t}} [GeV] pu_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_pu_down            = book<TH1F>("M_Zprime_pu_down", "M_{t#bar{t}} [GeV] pu_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_prefiring_up       = book<TH1F>("M_Zprime_prefiring_up",   "M_{t#bar{t}} [GeV] prefiring_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_prefiring_down     = book<TH1F>("M_Zprime_prefiring_down", "M_{t#bar{t}} [GeV] prefiring_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_mu_id_up           = book<TH1F>("M_Zprime_mu_id_up",   "M_{t#bar{t}} [GeV] mu_id_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_mu_id_down         = book<TH1F>("M_Zprime_mu_id_down", "M_{t#bar{t}} [GeV] mu_id_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_mu_iso_up          = book<TH1F>("M_Zprime_mu_iso_up",   "M_{t#bar{t}} [GeV] mu_iso_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_mu_iso_down        = book<TH1F>("M_Zprime_mu_iso_down", "M_{t#bar{t}} [GeV] mu_iso_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_mu_trigger_up      = book<TH1F>("M_Zprime_mu_trigger_up",   "M_{t#bar{t}} [GeV] mu_trigger_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_mu_trigger_down    = book<TH1F>("M_Zprime_mu_trigger_down", "M_{t#bar{t}} [GeV] mu_trigger_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_ele_id_up          = book<TH1F>("M_Zprime_ele_id_up",   "M_{t#bar{t}} [GeV] ele_id_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_ele_id_down        = book<TH1F>("M_Zprime_ele_id_down", "M_{t#bar{t}} [GeV] ele_id_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_ele_reco_up        = book<TH1F>("M_Zprime_ele_reco_up",   "M_{t#bar{t}} [GeV] ele_reco_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_ele_reco_down      = book<TH1F>("M_Zprime_ele_reco_down", "M_{t#bar{t}} [GeV] ele_reco_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_toppt_a_up         = book<TH1F>("M_Zprime_toppt_a_up",   "M_{t#bar{t}} [GeV] toppt_a_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_toppt_a_down       = book<TH1F>("M_Zprime_toppt_a_down", "M_{t#bar{t}} [GeV] toppt_a_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_toppt_b_up         = book<TH1F>("M_Zprime_toppt_b_up",   "M_{t#bar{t}} [GeV] toppt_b_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_toppt_b_down       = book<TH1F>("M_Zprime_toppt_b_down", "M_{t#bar{t}} [GeV] toppt_b_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_murmuf_upup        = book<TH1F>("M_Zprime_murmuf_upup", "M_{t#bar{t}} [GeV] murmuf_upup",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_murmuf_upnone      = book<TH1F>("M_Zprime_murmuf_upnone", "M_{t#bar{t}} [GeV] murmuf_upnone",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_murmuf_noneup      = book<TH1F>("M_Zprime_murmuf_noneup", "M_{t#bar{t}} [GeV] murmuf_noneup",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_murmuf_nonedown    = book<TH1F>("M_Zprime_murmuf_nonedown", "M_{t#bar{t}} [GeV] murmuf_nonedown",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_murmuf_downnone    = book<TH1F>("M_Zprime_murmuf_downnone", "M_{t#bar{t}} [GeV] murmuf_downnone",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_murmuf_downdown    = book<TH1F>("M_Zprime_murmuf_downdown", "M_{t#bar{t}} [GeV] murmuf_downdown",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_isr_up             = book<TH1F>("M_Zprime_isr_up", "M_{t#bar{t}} [GeV] isr_up", bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_isr_down           = book<TH1F>("M_Zprime_isr_down", "M_{t#bar{t}} [GeV] isr_down", bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_fsr_up             = book<TH1F>("M_Zprime_fsr_up", "M_{t#bar{t}} [GeV] fsr_up", bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_fsr_down           = book<TH1F>("M_Zprime_fsr_down", "M_{t#bar{t}} [GeV] fsr_down", bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_cferr1_up     = book<TH1F>("M_Zprime_btag_cferr1_up", "M_{t#bar{t}} [GeV] btag_cferr1_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_cferr1_down   = book<TH1F>("M_Zprime_btag_cferr1_down", "M_{t#bar{t}} [GeV] btag_cferr1_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_cferr2_up     = book<TH1F>("M_Zprime_btag_cferr2_up", "M_{t#bar{t}} [GeV] btag_cferr2_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_cferr2_down   = book<TH1F>("M_Zprime_btag_cferr2_down", "M_{t#bar{t}} [GeV] btag_cferr2_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_hf_up         = book<TH1F>("M_Zprime_btag_hf_up", "M_{t#bar{t}} [GeV] btag_hf_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_hf_down       = book<TH1F>("M_Zprime_btag_hf_down", "M_{t#bar{t}} [GeV] btag_hf_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_hfstats1_up   = book<TH1F>("M_Zprime_btag_hfstats1_up", "M_{t#bar{t}} [GeV] btag_hfstats1_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_hfstats1_down = book<TH1F>("M_Zprime_btag_hfstats1_down", "M_{t#bar{t}} [GeV] btag_hfstats1_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_hfstats2_up   = book<TH1F>("M_Zprime_btag_hfstats2_up", "M_{t#bar{t}} [GeV] btag_hfstats2_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_hfstats2_down = book<TH1F>("M_Zprime_btag_hfstats2_down", "M_{t#bar{t}} [GeV] btag_hfstats2_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_lf_up         = book<TH1F>("M_Zprime_btag_lf_up", "M_{t#bar{t}} [GeV] btag_lf_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_lf_down       = book<TH1F>("M_Zprime_btag_lf_down", "M_{t#bar{t}} [GeV] btag_lf_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_lfstats1_up   = book<TH1F>("M_Zprime_btag_lfstats1_up", "M_{t#bar{t}} [GeV] btag_lfstats1_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_lfstats1_down = book<TH1F>("M_Zprime_btag_lfstats1_down", "M_{t#bar{t}} [GeV] btag_lfstats1_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_lfstats2_up   = book<TH1F>("M_Zprime_btag_lfstats2_up", "M_{t#bar{t}} [GeV] btag_lfstats2_up",  bins_Zprime.size()-1, &bins_Zprime[0]);
  M_Zprime_btag_lfstats2_down = book<TH1F>("M_Zprime_btag_lfstats2_down", "M_{t#bar{t}} [GeV] btag_lfstats2_down",  bins_Zprime.size()-1, &bins_Zprime[0]);
}


void ZprimeSemiLeptonicSystematicsHists::fill(const Event & event){

  double weight = event.weight;
  float ele_reco_nominal   = event.get(h_ele_reco);
  float ele_reco_up        = event.get(h_ele_reco_up);
  float ele_reco_down      = event.get(h_ele_reco_down);
  float ele_id_nominal     = event.get(h_ele_id);
  float ele_id_up          = event.get(h_ele_id_up);
  float ele_id_down        = event.get(h_ele_id_down);
  float mu_reco_nominal    = event.get(h_mu_reco);
  float mu_reco_up         = event.get(h_mu_reco_up);
  float mu_reco_down       = event.get(h_mu_reco_down);
  float mu_iso_nominal     = event.get(h_mu_iso);
  float mu_iso_up          = event.get(h_mu_iso_up);
  float mu_iso_down        = event.get(h_mu_iso_down);
  float mu_id_nominal      = event.get(h_mu_id);
  float mu_id_up           = event.get(h_mu_id_up);
  float mu_id_down         = event.get(h_mu_id_down);
  float mu_trigger_nominal = event.get(h_mu_trigger);
  float mu_trigger_up      = event.get(h_mu_trigger_up);
  float mu_trigger_down    = event.get(h_mu_trigger_down);
  float pu_nominal         = event.get(h_pu);
  float pu_up              = event.get(h_pu_up);
  float pu_down            = event.get(h_pu_down);
  float prefiring_nominal  = event.get(h_prefiring);
  float prefiring_up       = event.get(h_prefiring_up);
  float prefiring_down     = event.get(h_prefiring_down);
  float toppt_nominal      = event.get(h_toppt);
  float toppt_a_up         = event.get(h_toppt_a_up);
  float toppt_a_down       = event.get(h_toppt_a_down);
  float toppt_b_up         = event.get(h_toppt_b_up);
  float toppt_b_down       = event.get(h_toppt_b_down);
  float murmuf_upup        = event.get(h_murmuf_upup);
  float murmuf_upnone      = event.get(h_murmuf_upnone);
  float murmuf_noneup      = event.get(h_murmuf_noneup);
  float murmuf_nonedown    = event.get(h_murmuf_nonedown);
  float murmuf_downnone    = event.get(h_murmuf_downnone);
  float murmuf_downdown    = event.get(h_murmuf_downdown);
  float isr_up             = event.get(h_isr_up);
  float isr_down           = event.get(h_isr_down);
  float fsr_up             = event.get(h_fsr_up);
  float fsr_down           = event.get(h_fsr_down);
  float btag_nominal       = event.get(h_btag);
  float btag_cferr1_up     = event.get(h_btag_cferr1_up);
  float btag_cferr1_down   = event.get(h_btag_cferr1_down);
  float btag_cferr2_up     = event.get(h_btag_cferr2_up);
  float btag_cferr2_down   = event.get(h_btag_cferr2_down);
  float btag_hf_up         = event.get(h_btag_hf_up);
  float btag_hf_down       = event.get(h_btag_hf_down);
  float btag_hfstats1_up   = event.get(h_btag_hfstats1_up);
  float btag_hfstats1_down = event.get(h_btag_hfstats1_down);
  float btag_hfstats2_up   = event.get(h_btag_hfstats2_up);
  float btag_hfstats2_down = event.get(h_btag_hfstats2_down);
  float btag_lf_up         = event.get(h_btag_lf_up);
  float btag_lf_down       = event.get(h_btag_lf_down);
  float btag_lfstats1_up   = event.get(h_btag_lfstats1_up);
  float btag_lfstats1_down = event.get(h_btag_lfstats1_down);
  float btag_lfstats2_up   = event.get(h_btag_lfstats2_up);
  float btag_lfstats2_down = event.get(h_btag_lfstats2_down);

  // only up/down variations
  vector<string> names       = {"ele_reco", "ele_id", "mu_reco", "mu_iso", "mu_id", "mu_trigger", "pu", "prefiring", "toppt_a", "toppt_b"};
  vector<float> syst_nominal = {ele_reco_nominal, ele_id_nominal, mu_reco_nominal, mu_iso_nominal, mu_id_nominal, mu_trigger_nominal, pu_nominal, prefiring_nominal, toppt_nominal, toppt_nominal};
  vector<float> syst_up      = {ele_reco_up, ele_id_up, mu_reco_up, mu_iso_up, mu_id_up, mu_trigger_up, pu_up, prefiring_up, toppt_a_up, toppt_b_up};
  vector<float> syst_down    = {ele_reco_down, ele_id_down, mu_reco_down, mu_iso_down, mu_id_down, mu_trigger_down, pu_down, prefiring_down, toppt_a_down, toppt_b_down};
  vector<TH1F*> hists_up     = {M_Zprime_ele_reco_up, M_Zprime_ele_id_up, M_Zprime_mu_reco_up, M_Zprime_mu_iso_up, M_Zprime_mu_id_up, M_Zprime_mu_trigger_up, M_Zprime_pu_up, M_Zprime_prefiring_up, M_Zprime_toppt_a_up, M_Zprime_toppt_b_up};
  vector<TH1F*> hists_down   = {M_Zprime_ele_reco_down, M_Zprime_ele_id_down, M_Zprime_mu_reco_down, M_Zprime_mu_iso_down, M_Zprime_mu_id_down, M_Zprime_mu_trigger_down, M_Zprime_pu_down, M_Zprime_prefiring_down, M_Zprime_toppt_a_down, M_Zprime_toppt_b_down};

  // scale variations need special treatment
  vector<float> syst_scale  = {murmuf_upup, murmuf_upnone, murmuf_noneup, murmuf_nonedown, murmuf_downnone, murmuf_downdown};
  vector<TH1F*> hists_scale = {M_Zprime_murmuf_upup, M_Zprime_murmuf_upnone, M_Zprime_murmuf_noneup, M_Zprime_murmuf_nonedown, M_Zprime_murmuf_downnone, M_Zprime_murmuf_downdown};

  // btag variations need special treatment
  vector<float> syst_btag  = {btag_cferr1_up, btag_cferr1_down, btag_cferr2_up, btag_cferr2_down, btag_hf_up, btag_hf_down, btag_hfstats1_up, btag_hfstats1_down, btag_hfstats2_up, btag_hfstats2_down, btag_lf_up, btag_lf_down, btag_lfstats1_up, btag_lfstats1_down, btag_lfstats2_up, btag_lfstats2_down};
  vector<TH1F*> hists_btag  = {M_Zprime_btag_cferr1_up, M_Zprime_btag_cferr1_down, M_Zprime_btag_cferr2_up, M_Zprime_btag_cferr2_down, M_Zprime_btag_hf_up, M_Zprime_btag_hf_down, M_Zprime_btag_hfstats1_up, M_Zprime_btag_hfstats1_down, M_Zprime_btag_hfstats2_up, M_Zprime_btag_hfstats2_down, M_Zprime_btag_lf_up, M_Zprime_btag_lf_down, M_Zprime_btag_lfstats1_up, M_Zprime_btag_lfstats1_down, M_Zprime_btag_lfstats2_up, M_Zprime_btag_lfstats2_down};

  // parton shower variations (ISR, FSR) need special treatment
  vector<float> syst_ps = {isr_up, isr_down, fsr_up, fsr_down};
  vector<TH1F*> hists_ps = {M_Zprime_isr_up, M_Zprime_isr_down, M_Zprime_fsr_up, M_Zprime_fsr_down};

  // Zprime reco
  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2);
  if(is_zprime_reconstructed_chi2 && is_mc){
    ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);
    float Mreco = BestZprimeCandidate->Zprime_v4().M();

    M_Zprime->Fill(Mreco, weight);

    // up/down variations
    for(unsigned int i=0; i<names.size(); i++){
      hists_up.at(i)->Fill(Mreco, weight * syst_up.at(i)/syst_nominal.at(i));
      hists_down.at(i)->Fill(Mreco, weight * syst_down.at(i)/syst_nominal.at(i));
    }
    // scale variations
    for(unsigned int i=0; i<hists_scale.size(); i++){
      hists_scale.at(i)->Fill(Mreco, weight * syst_scale.at(i));
    }
    // btag variations
    for(unsigned int i=0; i<hists_btag.size(); i++){
      hists_btag.at(i)->Fill(Mreco, weight * syst_btag.at(i)/btag_nominal);
    }
    // ps variations
    for(unsigned int i=0; i<hists_ps.size(); i++){
      hists_ps.at(i)->Fill(Mreco, weight * syst_ps.at(i));
    }
  }

} //Method



ZprimeSemiLeptonicSystematicsHists::~ZprimeSemiLeptonicSystematicsHists(){}
