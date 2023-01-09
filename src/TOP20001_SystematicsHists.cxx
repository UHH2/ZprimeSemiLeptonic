#include <iostream>
#include <math.h>
#include <string>

#include "TH1F.h"
#include "TH2D.h"

#include "UHH2/core/include/Event.h"
#include <UHH2/core/include/LorentzVector.h>

#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_SystematicsHists.h"

using namespace std;
using namespace uhh2;

TOP20001_SystematicsHists::TOP20001_SystematicsHists(uhh2::Context& ctx, const std::string& dirname): Hists(ctx, dirname) {
  is_mc = ctx.get("dataset_type") == "MC";

  h_pu = ctx.get_handle<float>("weight_pu");
  h_pu_up = ctx.get_handle<float>("weight_pu_up");
  h_pu_down = ctx.get_handle<float>("weight_pu_down");
  h_murmuf_upup = ctx.get_handle<float>("weight_murmuf_upup");
  h_murmuf_upnone = ctx.get_handle<float>("weight_murmuf_upnone");
  h_murmuf_noneup = ctx.get_handle<float>("weight_murmuf_noneup");
  h_murmuf_nonedown = ctx.get_handle<float>("weight_murmuf_nonedown");
  h_murmuf_downnone = ctx.get_handle<float>("weight_murmuf_downnone");
  h_murmuf_downdown = ctx.get_handle<float>("weight_murmuf_downdown");
  h_isr_up = ctx.get_handle<float>("weight_isr_2_up");
  h_isr_down = ctx.get_handle<float>("weight_isr_2_down");
  h_fsr_up = ctx.get_handle<float>("weight_fsr_2_up");
  h_fsr_down = ctx.get_handle<float>("weight_fsr_2_down");

  h_ttbargen = ctx.get_handle<TOP20001_TTbarGen>("ttbargen");
  init();
}

void TOP20001_SystematicsHists::init(){
  // m(tt)
  vector<float> bins_mtt = {250,400,480,560,640,720,800,900,1000,1150,1300,1500,1700,2000,2300,3500};
  mtt = book<TH1F>("mtt", "M_{t#bar{t}} [GeV]",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_pu_up = book<TH1F>("mtt_pu_up", "M_{t#bar{t}} [GeV] pu_up",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_pu_down = book<TH1F>("mtt_pu_down", "M_{t#bar{t}} [GeV] pu_down",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_murmuf_upup = book<TH1F>("mtt_murmuf_upup", "M_{t#bar{t}} [GeV] murmuf_upup",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_murmuf_upnone = book<TH1F>("mtt_murmuf_upnone", "M_{t#bar{t}} [GeV] murmuf_upnone",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_murmuf_noneup = book<TH1F>("mtt_murmuf_noneup", "M_{t#bar{t}} [GeV] murmuf_noneup",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_murmuf_nonedown = book<TH1F>("mtt_murmuf_nonedown", "M_{t#bar{t}} [GeV] murmuf_nonedown",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_murmuf_downnone = book<TH1F>("mtt_murmuf_downnone", "M_{t#bar{t}} [GeV] murmuf_downnone",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_murmuf_downdown = book<TH1F>("mtt_murmuf_downdown", "M_{t#bar{t}} [GeV] murmuf_downdown",  bins_mtt.size()-1, &bins_mtt[0]);
  mtt_isr_up = book<TH1F>("mtt_isr_up", "M_{t#bar{t}} [GeV] isr_up", bins_mtt.size()-1, &bins_mtt[0]);
  mtt_isr_down = book<TH1F>("mtt_isr_down", "M_{t#bar{t}} [GeV] isr_down", bins_mtt.size()-1, &bins_mtt[0]);
  mtt_fsr_up = book<TH1F>("mtt_fsr_up", "M_{t#bar{t}} [GeV] fsr_up", bins_mtt.size()-1, &bins_mtt[0]);
  mtt_fsr_down = book<TH1F>("mtt_fsr_down", "M_{t#bar{t}} [GeV] fsr_down", bins_mtt.size()-1, &bins_mtt[0]);
  // cos(theta*) in bins of m(tt)
  vector<float> bins_cts = {-1,-0.65,-0.3,0.0,0.3,0.65,1.0};
  cts_mtt250To420 = book<TH1F>("cts_mtt250To420", "cos(#theta*) bin 1", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_pu_up = book<TH1F>("cts_mtt250To420_pu_up", "cos(#theta*) bin 1 pu_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_pu_down = book<TH1F>("cts_mtt250To420_pu_down", "cos(#theta*) bin 1 pu_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_murmuf_upup = book<TH1F>("cts_mtt250To420_murmuf_upup", "cos(#theta*) bin 1 murmuf_upup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_murmuf_upnone = book<TH1F>("cts_mtt250To420_murmuf_upnone", "cos(#theta*) bin 1 murmuf_upnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_murmuf_noneup = book<TH1F>("cts_mtt250To420_murmuf_noneup", "cos(#theta*) bin 1 murmuf_noneup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_murmuf_nonedown = book<TH1F>("cts_mtt250To420_murmuf_nonedown", "cos(#theta*) bin 1 murmuf_nonedown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_murmuf_downnone = book<TH1F>("cts_mtt250To420_murmuf_downnone", "cos(#theta*) bin 1 murmuf_downnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_murmuf_downdown = book<TH1F>("cts_mtt250To420_murmuf_downdown", "cos(#theta*) bin 1 murmuf_downdown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_isr_up = book<TH1F>("cts_mtt250To420_isr_up", "cos(#theta*) bin 1 isr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_isr_down = book<TH1F>("cts_mtt250To420_isr_down", "cos(#theta*) bin 1 isr_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_fsr_up = book<TH1F>("cts_mtt250To420_fsr_up", "cos(#theta*) bin 1 fsr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt250To420_fsr_down = book<TH1F>("cts_mtt250To420_fsr_down", "cos(#theta*) bin 1 fsr_down", bins_cts.size()-1, &bins_cts[0]);

  cts_mtt420To520 = book<TH1F>("cts_mtt420To520", "cos(#theta*) bin 2", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_pu_up = book<TH1F>("cts_mtt420To520_pu_up", "cos(#theta*) bin 2 pu_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_pu_down = book<TH1F>("cts_mtt420To520_pu_down", "cos(#theta*) bin 2 pu_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_murmuf_upup = book<TH1F>("cts_mtt420To520_murmuf_upup", "cos(#theta*) bin 2 murmuf_upup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_murmuf_upnone = book<TH1F>("cts_mtt420To520_murmuf_upnone", "cos(#theta*) bin 2 murmuf_upnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_murmuf_noneup = book<TH1F>("cts_mtt420To520_murmuf_noneup", "cos(#theta*) bin 2 murmuf_noneup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_murmuf_nonedown = book<TH1F>("cts_mtt420To520_murmuf_nonedown", "cos(#theta*) bin 2 murmuf_nonedown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_murmuf_downnone = book<TH1F>("cts_mtt420To520_murmuf_downnone", "cos(#theta*) bin 2 murmuf_downnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_murmuf_downdown = book<TH1F>("cts_mtt420To520_murmuf_downdown", "cos(#theta*) bin 2 murmuf_downdown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_isr_up = book<TH1F>("cts_mtt420To520_isr_up", "cos(#theta*) bin 2 isr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_isr_down = book<TH1F>("cts_mtt420To520_isr_down", "cos(#theta*) bin 2 isr_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_fsr_up = book<TH1F>("cts_mtt420To520_fsr_up", "cos(#theta*) bin 2 fsr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt420To520_fsr_down = book<TH1F>("cts_mtt420To520_fsr_down", "cos(#theta*) bin 2 fsr_down", bins_cts.size()-1, &bins_cts[0]);

  cts_mtt520To620 = book<TH1F>("cts_mtt520To620", "cos(#theta*) bin 3", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_pu_up = book<TH1F>("cts_mtt520To620_pu_up", "cos(#theta*) bin 3 pu_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_pu_down = book<TH1F>("cts_mtt520To620_pu_down", "cos(#theta*) bin 3 pu_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_murmuf_upup = book<TH1F>("cts_mtt520To620_murmuf_upup", "cos(#theta*) bin 3 murmuf_upup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_murmuf_upnone = book<TH1F>("cts_mtt520To620_murmuf_upnone", "cos(#theta*) bin 3 murmuf_upnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_murmuf_noneup = book<TH1F>("cts_mtt520To620_murmuf_noneup", "cos(#theta*) bin 3 murmuf_noneup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_murmuf_nonedown = book<TH1F>("cts_mtt520To620_murmuf_nonedown", "cos(#theta*) bin 3 murmuf_nonedown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_murmuf_downnone = book<TH1F>("cts_mtt520To620_murmuf_downnone", "cos(#theta*) bin 3 murmuf_downnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_murmuf_downdown = book<TH1F>("cts_mtt520To620_murmuf_downdown", "cos(#theta*) bin 3 murmuf_downdown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_isr_up = book<TH1F>("cts_mtt520To620_isr_up", "cos(#theta*) bin 3 isr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_isr_down = book<TH1F>("cts_mtt520To620_isr_down", "cos(#theta*) bin 3 isr_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_fsr_up = book<TH1F>("cts_mtt520To620_fsr_up", "cos(#theta*) bin 3 fsr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt520To620_fsr_down = book<TH1F>("cts_mtt520To620_fsr_down", "cos(#theta*) bin 3 fsr_down", bins_cts.size()-1, &bins_cts[0]);

  cts_mtt620To800 = book<TH1F>("cts_mtt620To800", "cos(#theta*) bin 4", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_pu_up = book<TH1F>("cts_mtt620To800_pu_up", "cos(#theta*) bin 4 pu_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_pu_down = book<TH1F>("cts_mtt620To800_pu_down", "cos(#theta*) bin 4 pu_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_murmuf_upup = book<TH1F>("cts_mtt620To800_murmuf_upup", "cos(#theta*) bin 4 murmuf_upup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_murmuf_upnone = book<TH1F>("cts_mtt620To800_murmuf_upnone", "cos(#theta*) bin 4 murmuf_upnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_murmuf_noneup = book<TH1F>("cts_mtt620To800_murmuf_noneup", "cos(#theta*) bin 4 murmuf_noneup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_murmuf_nonedown = book<TH1F>("cts_mtt620To800_murmuf_nonedown", "cos(#theta*) bin 4 murmuf_nonedown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_murmuf_downnone = book<TH1F>("cts_mtt620To800_murmuf_downnone", "cos(#theta*) bin 4 murmuf_downnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_murmuf_downdown = book<TH1F>("cts_mtt620To800_murmuf_downdown", "cos(#theta*) bin 4 murmuf_downdown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_isr_up = book<TH1F>("cts_mtt620To800_isr_up", "cos(#theta*) bin 4 isr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_isr_down = book<TH1F>("cts_mtt620To800_isr_down", "cos(#theta*) bin 4 isr_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_fsr_up = book<TH1F>("cts_mtt620To800_fsr_up", "cos(#theta*) bin 4 fsr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt620To800_fsr_down = book<TH1F>("cts_mtt620To800_fsr_down", "cos(#theta*) bin 4 fsr_down", bins_cts.size()-1, &bins_cts[0]);

  cts_mtt800To1000 = book<TH1F>("cts_mtt800To1000", "cos(#theta*) bin 5", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_pu_up = book<TH1F>("cts_mtt800To1000_pu_up", "cos(#theta*) bin 5 pu_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_pu_down = book<TH1F>("cts_mtt800To1000_pu_down", "cos(#theta*) bin 5 pu_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_murmuf_upup = book<TH1F>("cts_mtt800To1000_murmuf_upup", "cos(#theta*) bin 5 murmuf_upup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_murmuf_upnone = book<TH1F>("cts_mtt800To1000_murmuf_upnone", "cos(#theta*) bin 5 murmuf_upnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_murmuf_noneup = book<TH1F>("cts_mtt800To1000_murmuf_noneup", "cos(#theta*) bin 5 murmuf_noneup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_murmuf_nonedown = book<TH1F>("cts_mtt800To1000_murmuf_nonedown", "cos(#theta*) bin 5 murmuf_nonedown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_murmuf_downnone = book<TH1F>("cts_mtt800To1000_murmuf_downnone", "cos(#theta*) bin 5 murmuf_downnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_murmuf_downdown = book<TH1F>("cts_mtt800To1000_murmuf_downdown", "cos(#theta*) bin 5 murmuf_downdown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_isr_up = book<TH1F>("cts_mtt800To1000_isr_up", "cos(#theta*) bin 5 isr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_isr_down = book<TH1F>("cts_mtt800To1000_isr_down", "cos(#theta*) bin 5 isr_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_fsr_up = book<TH1F>("cts_mtt800To1000_fsr_up", "cos(#theta*) bin 5 fsr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt800To1000_fsr_down = book<TH1F>("cts_mtt800To1000_fsr_down", "cos(#theta*) bin 5 fsr_down", bins_cts.size()-1, &bins_cts[0]);

  cts_mtt1000To3500 = book<TH1F>("cts_mtt1000To3500", "cos(#theta*) bin 6", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_pu_up = book<TH1F>("cts_mtt1000To3500_pu_up", "cos(#theta*) bin 6 pu_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_pu_down = book<TH1F>("cts_mtt1000To3500_pu_down", "cos(#theta*) bin 6 pu_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_murmuf_upup = book<TH1F>("cts_mtt1000To3500_murmuf_upup", "cos(#theta*) bin 6 murmuf_upup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_murmuf_upnone = book<TH1F>("cts_mtt1000To3500_murmuf_upnone", "cos(#theta*) bin 6 murmuf_upnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_murmuf_noneup = book<TH1F>("cts_mtt1000To3500_murmuf_noneup", "cos(#theta*) bin 6 murmuf_noneup", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_murmuf_nonedown = book<TH1F>("cts_mtt1000To3500_murmuf_nonedown", "cos(#theta*) bin 6 murmuf_nonedown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_murmuf_downnone = book<TH1F>("cts_mtt1000To3500_murmuf_downnone", "cos(#theta*) bin 6 murmuf_downnone", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_murmuf_downdown = book<TH1F>("cts_mtt1000To3500_murmuf_downdown", "cos(#theta*) bin 6 murmuf_downdown", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_isr_up = book<TH1F>("cts_mtt1000To3500_isr_up", "cos(#theta*) bin 6 isr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_isr_down = book<TH1F>("cts_mtt1000To3500_isr_down", "cos(#theta*) bin 6 isr_down", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_fsr_up = book<TH1F>("cts_mtt1000To3500_fsr_up", "cos(#theta*) bin 6 fsr_up", bins_cts.size()-1, &bins_cts[0]);
  cts_mtt1000To3500_fsr_down = book<TH1F>("cts_mtt1000To3500_fsr_down", "cos(#theta*) bin 6 fsr_down", bins_cts.size()-1, &bins_cts[0]);
}

void TOP20001_SystematicsHists::fill(const Event & event){
  float weight = event.weight;
  float pu_nominal = event.get(h_pu);
  float pu_up = event.get(h_pu_up);
  float pu_down = event.get(h_pu_down);
  float murmuf_upup = event.get(h_murmuf_upup);
  float murmuf_upnone = event.get(h_murmuf_upnone);
  float murmuf_noneup = event.get(h_murmuf_noneup);
  float murmuf_nonedown = event.get(h_murmuf_nonedown);
  float murmuf_downnone = event.get(h_murmuf_downnone);
  float murmuf_downdown = event.get(h_murmuf_downdown);
  float isr_up = event.get(h_isr_up);
  float isr_down = event.get(h_isr_down);
  float fsr_up = event.get(h_fsr_up);
  float fsr_down = event.get(h_fsr_down);

  // only up/down variations
  vector<string> names = {"pu"};
  vector<float> syst_nominal = {pu_nominal};
  vector<float> syst_up = {pu_up};
  vector<float> syst_down = {pu_down};
  vector<TH1F*> hists_mtt_up = {mtt_pu_up};
  vector<TH1F*> hists_mtt_down = {mtt_pu_down};
  vector<TH1F*> hists_cts_bin1_up = {cts_mtt250To420_pu_up};
  vector<TH1F*> hists_cts_bin1_down = {cts_mtt250To420_pu_down};
  vector<TH1F*> hists_cts_bin2_up = {cts_mtt420To520_pu_up};
  vector<TH1F*> hists_cts_bin2_down = {cts_mtt420To520_pu_down};
  vector<TH1F*> hists_cts_bin3_up = {cts_mtt520To620_pu_up};
  vector<TH1F*> hists_cts_bin3_down = {cts_mtt520To620_pu_down};
  vector<TH1F*> hists_cts_bin4_up = {cts_mtt620To800_pu_up};
  vector<TH1F*> hists_cts_bin4_down = {cts_mtt620To800_pu_down};
  vector<TH1F*> hists_cts_bin5_up = {cts_mtt800To1000_pu_up};
  vector<TH1F*> hists_cts_bin5_down = {cts_mtt800To1000_pu_down};
  vector<TH1F*> hists_cts_bin6_up = {cts_mtt1000To3500_pu_up};
  vector<TH1F*> hists_cts_bin6_down = {cts_mtt1000To3500_pu_down};

  // scale variations need special treatment
  vector<float> syst_scale  = {murmuf_upup, murmuf_upnone, murmuf_noneup, murmuf_nonedown, murmuf_downnone, murmuf_downdown};
  vector<TH1F*> hists_mtt_scale = {mtt_murmuf_upup, mtt_murmuf_upnone, mtt_murmuf_noneup, mtt_murmuf_nonedown, mtt_murmuf_downnone, mtt_murmuf_downdown};
  vector<TH1F*> hists_cts_bin1_scale = {cts_mtt250To420_murmuf_upup, cts_mtt250To420_murmuf_upnone, cts_mtt250To420_murmuf_noneup, cts_mtt250To420_murmuf_nonedown, cts_mtt250To420_murmuf_downnone, cts_mtt250To420_murmuf_downdown};
  vector<TH1F*> hists_cts_bin2_scale = {cts_mtt420To520_murmuf_upup, cts_mtt420To520_murmuf_upnone, cts_mtt420To520_murmuf_noneup, cts_mtt420To520_murmuf_nonedown, cts_mtt420To520_murmuf_downnone, cts_mtt420To520_murmuf_downdown};
  vector<TH1F*> hists_cts_bin3_scale = {cts_mtt520To620_murmuf_upup, cts_mtt520To620_murmuf_upnone, cts_mtt520To620_murmuf_noneup, cts_mtt520To620_murmuf_nonedown, cts_mtt520To620_murmuf_downnone, cts_mtt520To620_murmuf_downdown};
  vector<TH1F*> hists_cts_bin4_scale = {cts_mtt620To800_murmuf_upup, cts_mtt620To800_murmuf_upnone, cts_mtt620To800_murmuf_noneup, cts_mtt620To800_murmuf_nonedown, cts_mtt620To800_murmuf_downnone, cts_mtt620To800_murmuf_downdown};
  vector<TH1F*> hists_cts_bin5_scale = {cts_mtt800To1000_murmuf_upup, cts_mtt800To1000_murmuf_upnone, cts_mtt800To1000_murmuf_noneup, cts_mtt800To1000_murmuf_nonedown, cts_mtt800To1000_murmuf_downnone, cts_mtt800To1000_murmuf_downdown};
  vector<TH1F*> hists_cts_bin6_scale = {cts_mtt1000To3500_murmuf_upup, cts_mtt1000To3500_murmuf_upnone, cts_mtt1000To3500_murmuf_noneup, cts_mtt1000To3500_murmuf_nonedown, cts_mtt1000To3500_murmuf_downnone, cts_mtt1000To3500_murmuf_downdown};

  // parton shower variations (ISR, FSR) need special treatment
  vector<float> syst_ps = {isr_up, isr_down, fsr_up, fsr_down};
  vector<TH1F*> hists_mtt_ps = {mtt_isr_up, mtt_isr_down, mtt_fsr_up, mtt_fsr_down};
  vector<TH1F*> hists_cts_bin1_ps = {cts_mtt250To420_isr_up, cts_mtt250To420_isr_down, cts_mtt250To420_fsr_up, cts_mtt250To420_fsr_down};
  vector<TH1F*> hists_cts_bin2_ps = {cts_mtt420To520_isr_up, cts_mtt420To520_isr_down, cts_mtt420To520_fsr_up, cts_mtt420To520_fsr_down};
  vector<TH1F*> hists_cts_bin3_ps = {cts_mtt520To620_isr_up, cts_mtt520To620_isr_down, cts_mtt520To620_fsr_up, cts_mtt520To620_fsr_down};
  vector<TH1F*> hists_cts_bin4_ps = {cts_mtt620To800_isr_up, cts_mtt620To800_isr_down, cts_mtt620To800_fsr_up, cts_mtt620To800_fsr_down};
  vector<TH1F*> hists_cts_bin5_ps = {cts_mtt800To1000_isr_up, cts_mtt800To1000_isr_down, cts_mtt800To1000_fsr_up, cts_mtt800To1000_fsr_down};
  vector<TH1F*> hists_cts_bin6_ps = {cts_mtt1000To3500_isr_up, cts_mtt1000To3500_isr_down, cts_mtt1000To3500_fsr_up, cts_mtt1000To3500_fsr_down};

  // Zprime reco
  TOP20001_TTbarGen TOP20001_TTbarGen = event.get(h_ttbargen);

  if(is_mc && TOP20001_TTbarGen.IsSemiLeptonicDecay()){
    LorentzVector top = TOP20001_TTbarGen.Top().v4();
    LorentzVector antitop = TOP20001_TTbarGen.Antitop().v4();

    float mttbar = (top + antitop).M();

    const TLorentzVector Top(top.px(), top.py(), top.pz(), top.E());
    const TLorentzVector Antitop(antitop.px(), antitop.py(), antitop.pz(), antitop.E());
    const TLorentzVector TTbar = Top + Antitop;
    TLorentzVector Topcms = Top;
    Topcms.Boost(-1.*TTbar.BoostVector());
    float cts = TTbar.Vect().Dot(Topcms.Vect())/TTbar.P()/Topcms.P();

    mtt->Fill(mttbar, weight);

    // up/down variations
    for(unsigned int i=0; i<names.size(); i++){
      hists_mtt_up.at(i)->Fill(mttbar, weight * syst_up.at(i)/syst_nominal.at(i));
      hists_mtt_down.at(i)->Fill(mttbar, weight * syst_down.at(i)/syst_nominal.at(i));

      if(mttbar < 250.){} // do nothing: underflow bin
      else if(mttbar < 420.){
        cts_mtt250To420->Fill(cts, weight);
        hists_cts_bin1_up.at(i)->Fill(cts, weight * syst_up.at(i)/syst_nominal.at(i));
        hists_cts_bin1_down.at(i)->Fill(cts, weight * syst_down.at(i)/syst_nominal.at(i));
      }
      else if(mttbar < 520.){
        cts_mtt420To520->Fill(cts, weight);
        hists_cts_bin2_up.at(i)->Fill(cts, weight * syst_up.at(i)/syst_nominal.at(i));
        hists_cts_bin2_down.at(i)->Fill(cts, weight * syst_down.at(i)/syst_nominal.at(i));
      }
      else if(mttbar < 620.){
        cts_mtt520To620->Fill(cts, weight);
        hists_cts_bin3_up.at(i)->Fill(cts, weight * syst_up.at(i)/syst_nominal.at(i));
        hists_cts_bin3_down.at(i)->Fill(cts, weight * syst_down.at(i)/syst_nominal.at(i));
      }
      else if(mttbar < 800.){
        cts_mtt620To800->Fill(cts, weight);
        hists_cts_bin4_up.at(i)->Fill(cts, weight * syst_up.at(i)/syst_nominal.at(i));
        hists_cts_bin4_down.at(i)->Fill(cts, weight * syst_down.at(i)/syst_nominal.at(i));
      }
      else if(mttbar < 1000.){
        cts_mtt800To1000->Fill(cts, weight);
        hists_cts_bin5_up.at(i)->Fill(cts, weight * syst_up.at(i)/syst_nominal.at(i));
        hists_cts_bin5_down.at(i)->Fill(cts, weight * syst_down.at(i)/syst_nominal.at(i));
      }
      else if(mttbar < 3500.){
        cts_mtt1000To3500->Fill(cts, weight);
        hists_cts_bin6_up.at(i)->Fill(cts, weight * syst_up.at(i)/syst_nominal.at(i));
        hists_cts_bin6_down.at(i)->Fill(cts, weight * syst_down.at(i)/syst_nominal.at(i));
      }
      else{} // do nothing: overflow bin
    }
    // scale variations
    for(unsigned int i=0; i<hists_mtt_scale.size(); i++){
      hists_mtt_scale.at(i)->Fill(mttbar, weight * syst_scale.at(i));

      if(mttbar < 250.){} // do nothing: underflow bin
      else if(mttbar < 420.) hists_cts_bin1_scale.at(i)->Fill(cts, weight * syst_scale.at(i));
      else if(mttbar < 520.) hists_cts_bin2_scale.at(i)->Fill(cts, weight * syst_scale.at(i));
      else if(mttbar < 620.) hists_cts_bin3_scale.at(i)->Fill(cts, weight * syst_scale.at(i));
      else if(mttbar < 800.) hists_cts_bin4_scale.at(i)->Fill(cts, weight * syst_scale.at(i));
      else if(mttbar < 1000.) hists_cts_bin5_scale.at(i)->Fill(cts, weight * syst_scale.at(i));
      else if(mttbar < 3500.) hists_cts_bin6_scale.at(i)->Fill(cts, weight * syst_scale.at(i));
      else{} // do nothing: overflow bin
    }
    // ps variations
    for(unsigned int i=0; i<hists_mtt_ps.size(); i++){
      hists_mtt_ps.at(i)->Fill(mttbar, weight * syst_ps.at(i));

      if(mttbar < 250.){} // do nothing: underflow bin
      else if(mttbar < 420.) hists_cts_bin1_ps.at(i)->Fill(cts, weight * syst_ps.at(i));
      else if(mttbar < 520.) hists_cts_bin2_ps.at(i)->Fill(cts, weight * syst_ps.at(i));
      else if(mttbar < 620.) hists_cts_bin3_ps.at(i)->Fill(cts, weight * syst_ps.at(i));
      else if(mttbar < 800.) hists_cts_bin4_ps.at(i)->Fill(cts, weight * syst_ps.at(i));
      else if(mttbar < 1000.) hists_cts_bin5_ps.at(i)->Fill(cts, weight * syst_ps.at(i));
      else if(mttbar < 3500.) hists_cts_bin6_ps.at(i)->Fill(cts, weight * syst_ps.at(i));
      else{} // do nothing: overflow bin
    }
  }
}

TOP20001_SystematicsHists::~TOP20001_SystematicsHists(){}
