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
#include <UHH2/common/include/Utils.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

#include <string>
#include <vector>
#include <unordered_map>
#include <TLorentzVector.h>

namespace uhh2 {

  class BlindDataSelection : public Selection{
  public:
    explicit BlindDataSelection(uhh2::Context&, float mtt_max);
    virtual bool passes(const Event&) override;

  private:
    uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidate_chi2;
    uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
    bool isMC;
    float mtt_max_;
  };

  class ZprimeTopTagSelection : public Selection{
  public:
    explicit ZprimeTopTagSelection(uhh2::Context&);
    virtual bool passes(const Event&) override;

  private:
    uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidate_chi2;
    uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
  };

  class TopTag_VetoSelection : public Selection{
  public:
    explicit TopTag_VetoSelection(uhh2::Context&, TString mode);
    virtual bool passes(const Event&) override;

  private:
  uhh2::Event::Handle< std::vector<TopJet> > h_AK8TopTags;
  TString mode_;
  };

  class Chi2CandidateMatchedSelection : public Selection{
  public:
    explicit Chi2CandidateMatchedSelection(uhh2::Context&);
    virtual bool passes(const Event&) override;

  private:
    uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidate_chi2;
    uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
    uhh2::Event::Handle<bool> h_is_zprime_reconstructed_correctmatch;
  };

  class TTbarSemiLepMatchableSelection: public uhh2::Selection{
  public:
    TTbarSemiLepMatchableSelection();
    ~TTbarSemiLepMatchableSelection(){};
    virtual bool passes(const uhh2::Event & event);
    std::pair<bool,double> check_reco(const ReconstructionHypothesis hyp);//compares match between reconstructed hypothesis vs gen tops and products of their decays filled in passes()
  private:
    GenParticle Wlep, Whad, blep, bhad, thad, tlep, lepton, neutrino, Whadd1,Whadd2;
  };



  class Chi2Cut : public Selection{
  public:
    explicit Chi2Cut(uhh2::Context&, float, float max=-1);
    virtual bool passes(const Event&) override;

  private:
    float min_, max_;
    uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidate;
    uhh2::Event::Handle<bool> h_is_zprime_reconstructed;
  };

  class STlepPlusMetCut : public Selection {

  public:
    explicit STlepPlusMetCut(float, float max=-1);
    virtual bool passes(const Event&) override;

  private:
    float min_, max_;
  };

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

  // class ZprimeBTagFatSubJetSelection: public Selection {
  // public:
  //   explicit ZprimeBTagFatSubJetSelection(;
  //   virtual bool passes(const Event&) override;
  //
  // private:
  //   std::unique_ptr<Selection> sel_1btag;
  // };
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



  class HEMSelection : public Selection{
  public:
    explicit HEMSelection(uhh2::Context&);
    virtual bool passes(const Event&) override;

  private:
  Year year;
  int min_runnum = 319077;
  double eta_up = -1.3;
  double eta_down = -3.0;
  double phi_up = -0.87;
  double phi_down = -1.57;
  };
  ////

  class ThetaStarSelection : public Selection{
  public:
    explicit ThetaStarSelection(uhh2::Context&, float theta_cut_low, float theta_cut_high);
    virtual bool passes(const Event&) override;
  private:
    uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;
    uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
    float theta_cut_low_;
    float theta_cut_high_;
  };
  ////


  class AbsThetaStarSelection : public Selection{
  public:
    explicit AbsThetaStarSelection(uhh2::Context&, float abs_theta_cut_low, float abs_theta_cut_high);
    virtual bool passes(const Event&) override;
  private:
    uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;
    uhh2::Event::Handle<bool> h_is_zprime_reconstructed_chi2;
    float abs_theta_cut_low_;
    float abs_theta_cut_high_;
  };
  ////


  class PuppiCHS_BTagging : public Selection{
  public:
    explicit PuppiCHS_BTagging(uhh2::Context&);
    virtual bool passes(const Event&) override;

  private:
  uhh2::Event::Handle< std::vector<Jet> > h_CHSjets_matched;
  std::unique_ptr<Selection> sel_1btag;
  };
  ////

  class SignSelection: public Selection {

  public:
    explicit SignSelection(const std::string&);
    virtual bool passes(const Event&) override;

  private:
    std::string weight_sign_;
  };

}
