#pragma once

#include <string>
#include <TLorentzVector.h>

#include "UHH2/core/include/Hists.h"
#include "UHH2/core/include/Event.h"

#include "UHH2/ZprimeSemiLeptonic/include/TOP20001_TTbarGen.h"


namespace uhh2 {
  class TOP20001_SystematicsHists: public uhh2::Hists{
  public:
    explicit TOP20001_SystematicsHists(uhh2::Context&, const std::string&);
    virtual void fill(const uhh2::Event&) override;

  protected:
    void init();
    bool is_mc;
    uhh2::Event::Handle<float> h_pu, h_pu_up, h_pu_down, h_murmuf_upup, h_murmuf_upnone, h_murmuf_noneup, h_murmuf_nonedown, h_murmuf_downnone, h_murmuf_downdown, h_isr_up, h_isr_down, h_fsr_up, h_fsr_down;
    TH1F *mtt, *mtt_pu_up, *mtt_pu_down, *mtt_murmuf_upup, *mtt_murmuf_upnone, *mtt_murmuf_noneup, *mtt_murmuf_nonedown, *mtt_murmuf_downnone, *mtt_murmuf_downdown, *mtt_isr_up, *mtt_isr_down, *mtt_fsr_up, *mtt_fsr_down;
    TH1F *cts_mtt250To420, *cts_mtt250To420_pu_up, *cts_mtt250To420_pu_down, *cts_mtt250To420_murmuf_upup, *cts_mtt250To420_murmuf_upnone, *cts_mtt250To420_murmuf_noneup, *cts_mtt250To420_murmuf_nonedown, *cts_mtt250To420_murmuf_downnone, *cts_mtt250To420_murmuf_downdown, *cts_mtt250To420_isr_up, *cts_mtt250To420_isr_down, *cts_mtt250To420_fsr_up, *cts_mtt250To420_fsr_down;
    TH1F *cts_mtt420To520, *cts_mtt420To520_pu_up, *cts_mtt420To520_pu_down, *cts_mtt420To520_murmuf_upup, *cts_mtt420To520_murmuf_upnone, *cts_mtt420To520_murmuf_noneup, *cts_mtt420To520_murmuf_nonedown, *cts_mtt420To520_murmuf_downnone, *cts_mtt420To520_murmuf_downdown, *cts_mtt420To520_isr_up, *cts_mtt420To520_isr_down, *cts_mtt420To520_fsr_up, *cts_mtt420To520_fsr_down;
    TH1F *cts_mtt520To620, *cts_mtt520To620_pu_up, *cts_mtt520To620_pu_down, *cts_mtt520To620_murmuf_upup, *cts_mtt520To620_murmuf_upnone, *cts_mtt520To620_murmuf_noneup, *cts_mtt520To620_murmuf_nonedown, *cts_mtt520To620_murmuf_downnone, *cts_mtt520To620_murmuf_downdown, *cts_mtt520To620_isr_up, *cts_mtt520To620_isr_down, *cts_mtt520To620_fsr_up, *cts_mtt520To620_fsr_down;
    TH1F *cts_mtt620To800, *cts_mtt620To800_pu_up, *cts_mtt620To800_pu_down, *cts_mtt620To800_murmuf_upup, *cts_mtt620To800_murmuf_upnone, *cts_mtt620To800_murmuf_noneup, *cts_mtt620To800_murmuf_nonedown, *cts_mtt620To800_murmuf_downnone, *cts_mtt620To800_murmuf_downdown, *cts_mtt620To800_isr_up, *cts_mtt620To800_isr_down, *cts_mtt620To800_fsr_up, *cts_mtt620To800_fsr_down;
    TH1F *cts_mtt800To1000, *cts_mtt800To1000_pu_up, *cts_mtt800To1000_pu_down, *cts_mtt800To1000_murmuf_upup, *cts_mtt800To1000_murmuf_upnone, *cts_mtt800To1000_murmuf_noneup, *cts_mtt800To1000_murmuf_nonedown, *cts_mtt800To1000_murmuf_downnone, *cts_mtt800To1000_murmuf_downdown, *cts_mtt800To1000_isr_up, *cts_mtt800To1000_isr_down, *cts_mtt800To1000_fsr_up, *cts_mtt800To1000_fsr_down;
    TH1F *cts_mtt1000To3500, *cts_mtt1000To3500_pu_up, *cts_mtt1000To3500_pu_down, *cts_mtt1000To3500_murmuf_upup, *cts_mtt1000To3500_murmuf_upnone, *cts_mtt1000To3500_murmuf_noneup, *cts_mtt1000To3500_murmuf_nonedown, *cts_mtt1000To3500_murmuf_downnone, *cts_mtt1000To3500_murmuf_downdown, *cts_mtt1000To3500_isr_up, *cts_mtt1000To3500_isr_down, *cts_mtt1000To3500_fsr_up, *cts_mtt1000To3500_fsr_down;

    uhh2::Event::Handle<TOP20001_TTbarGen> h_ttbargen;
    virtual ~TOP20001_SystematicsHists();
  };
}
