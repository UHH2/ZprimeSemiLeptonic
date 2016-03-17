#pragma once

#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Selection.h>
#include <UHH2/core/include/Utils.h>

#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/ReconstructionHypothesis.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>

#include <string>
#include <vector>
#include <unordered_map>

namespace uhh2 {

  class HTlepCut : public Selection {

   public:
    explicit HTlepCut(float, float max_htlep=infinity);
    virtual bool passes(const Event&) override;

   private:
    float min_htlep_, max_htlep_;
  };
  ////

  class METCut : public Selection {

   public:
    explicit METCut(float, float max_met=infinity);
    virtual bool passes(const Event&) override;

   private:
    float min_met_, max_met_;
  };
  ////

  class TwoDCut : public Selection {

   public:
    explicit TwoDCut(float min_deltaR, float min_pTrel): min_deltaR_(min_deltaR), min_pTrel_(min_pTrel) {}
    virtual bool passes(const Event&) override;

   private:
    float min_deltaR_, min_pTrel_;
  };
  ////

  class TwoDCut1 : public Selection {

   public:
    explicit TwoDCut1(float min_deltaR, float min_pTrel): min_deltaR_(min_deltaR), min_pTrel_(min_pTrel) {}
    virtual bool passes(const Event&) override;

   private:
    float min_deltaR_, min_pTrel_;
  };
  ////

  class TwoDCutALL : public Selection {

   public:
    explicit TwoDCutALL(float min_deltaR, float min_pTrel): min_deltaR_(min_deltaR), min_pTrel_(min_pTrel) {}
    virtual bool passes(const Event&) override;

   private:
    float min_deltaR_, min_pTrel_;
  };
  ////

  class TriangularCuts : public Selection {

   public:
    explicit TriangularCuts(const float a, const float b): a_(a), b_(b) {}
    virtual bool passes(const Event&) override;

   private:
    float a_, b_;
  };
  ////

  class TriangularCutsELE : public Selection {

   public:
    explicit TriangularCutsELE(const float a, const float b): a_(a), b_(b) {}
    virtual bool passes(const Event&) override;

   private:
    float a_, b_;
  };
  ////

  class DiLeptonSelection: public Selection {

   public:
    explicit DiLeptonSelection(const std::string&, const bool, const bool);
    virtual bool passes(const Event&) override;

   private:
    std::string channel_;
    bool opposite_charge_;
    bool veto_other_flavor_;
  };
  ////

  class TopJetPlusJetEventSelection: public Selection {

   public:
    explicit TopJetPlusJetEventSelection(const float, const float);
    virtual bool passes(const Event&) override;

   private:
    float topjet_minDR_jet_;
    float jet_min_pt_;
  };
  ////

  class TopTagEventSelection: public Selection {

   public:
    explicit TopTagEventSelection(const TopJetId& tjet_id=CMSTopTag(), const float minDR_jet_ttag=1.2);
    virtual bool passes(const Event&) override;

   private:
    std::unique_ptr<Selection> topjet1_sel_;
    TopJetId topjetID_;
    float minDR_jet_toptag_;
  };
  ////

  class LeptonicTopPtCut: public Selection {

   public:
    explicit LeptonicTopPtCut(Context&, float, float, const std::string& hyps="TTbarReconstruction", const std::string& disc="Chi2");
    virtual bool passes(const Event&) override;

   private:
    float tlep_pt_min_, tlep_pt_max_;
    Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps_;
    std::string disc_name_;
  };
  ////

  class HypothesisDiscriminatorCut: public Selection {

   public:
    explicit HypothesisDiscriminatorCut(Context&, float, float, const std::string& hyps="TTbarReconstruction", const std::string& disc_bhyp="Chi2", const std::string& disc_cut="Chi2");
    virtual bool passes(const Event&) override;

   private:
    float disc_min_, disc_max_;
    Event::Handle<std::vector<ReconstructionHypothesis>> h_hyps_;
    std::string disc_bhyp_;
    std::string disc_cut_;
  };
  ////

  class GenFlavorSelection: public Selection {

   public:
    explicit GenFlavorSelection(const std::string&);
    virtual bool passes(const Event&) override;

   private:
    std::string flavor_key_;
  };
  ////

  class JetFlavorSelection: public Selection {

   public:
    explicit JetFlavorSelection(const std::string&);
    virtual bool passes(const Event&) override;

   private:
    std::string flavor_key_;
  };
  ////

  class GenHTCut : public Selection {

   public:
    explicit GenHTCut(Context&, const float, const float, const std::string&);
    virtual bool passes(const Event&) override;

  protected:
    float genHT_min_, genHT_max_;
    Event::Handle<std::vector<GenParticle> > h_meps_;
  };
  ////

  class RunLumiEventSelection : public Selection {

   public:
    explicit RunLumiEventSelection(const std::string&, const std::string& sep=":");
    virtual ~RunLumiEventSelection() {}

    virtual bool passes(const Event&) override;
    virtual bool found (const Event&);

   protected:
    std::unordered_map<unsigned long int, std::unordered_map<unsigned long int, std::vector<unsigned long int> > > rle_map_;
  };
  ////

}
