#pragma once

#include <vector>

#include "UHH2/core/include/AnalysisModule.h"
#include "UHH2/core/include/Event.h"
#include "UHH2/core/include/GenParticle.h"

class TOP20001_TTbarGen {

public:
  explicit TOP20001_TTbarGen(const std::vector<GenParticle> & genparts, bool throw_on_failure = true);

  enum E_DecayChannel{
    e_had,
    e_ehad,
    e_muhad,
    e_tauhad,
    e_ee,
    e_mumu,
    e_tautau,
    e_emu,
    e_etau,
    e_mutau,
    e_notfound
  };

  GenParticle Top() const;
  GenParticle Antitop() const;
  GenParticle WTop() const;
  GenParticle WAntitop() const;
  GenParticle bTop() const;
  GenParticle bAntitop() const;
  GenParticle Wdecay1() const;
  GenParticle Wdecay2() const;
  GenParticle WMinusdecay1() const;
  GenParticle WMinusdecay2() const;
  E_DecayChannel DecayChannel() const;

  bool IsTopHadronicDecay() const;
  bool IsAntiTopHadronicDecay() const;
  bool IsSemiLeptonicDecay() const;

  //only for l+jets decays
  GenParticle TopLep() const;
  GenParticle TopHad() const;
  GenParticle BLep() const;
  GenParticle BHad() const;
  GenParticle WLep() const;
  GenParticle WHad() const;
  GenParticle ChargedLepton() const;
  GenParticle Neutrino() const;
  GenParticle Q1() const;
  GenParticle Q2() const;


private:
  GenParticle m_Top;
  GenParticle m_Antitop;
  GenParticle m_WTop;
  GenParticle m_WAntitop;
  GenParticle m_bTop;
  GenParticle m_bAntitop;
  GenParticle m_Wdecay1;
  GenParticle m_Wdecay2;
  GenParticle m_WMinusdecay1;
  GenParticle m_WMinusdecay2;

  E_DecayChannel m_type;
};


class TOP20001_TTbarGenProducer: public uhh2::AnalysisModule{
public:
  explicit TOP20001_TTbarGenProducer(uhh2::Context & ctx, const std::string & name = "ttbargen", bool throw_on_failure = true);
  virtual bool process(uhh2::Event & event) override;

private:
  uhh2::Event::Handle<TOP20001_TTbarGen> h_ttbargen;
  bool throw_on_failure;
};
