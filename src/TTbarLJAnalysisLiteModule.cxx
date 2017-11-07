#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>

#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/CleaningModules.h>
#include <UHH2/common/include/NSelections.h>
#include <UHH2/common/include/LumiSelection.h>
#include <UHH2/common/include/TriggerSelection.h>
#include <UHH2/common/include/JetCorrections.h>
#include <UHH2/common/include/ObjectIdUtils.h>
#include <UHH2/common/include/MuonIds.h>
#include <UHH2/common/include/ElectronIds.h>
#include <UHH2/common/include/JetIds.h>
#include <UHH2/common/include/TopJetIds.h>
#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/TopPtReweight.h>
#include "UHH2/common/include/LuminosityHists.h"

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicUtils.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/DileptonHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/EffyTTbarRECOHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/SF_elec.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_ttagging.h>
#include <UHH2/ZprimeSemiLeptonic/include/SF_WjetsREWGT.h>
#include <UHH2/ZprimeSemiLeptonic/include/jacobi_eigenvalue.h>
#include <TMVA/Tools.h>
#include <TMVA/Reader.h>
#include <TMVA/MethodCuts.h>

class TTbarLJAnalysisLiteModule : public ModuleBASE {

public:
  explicit TTbarLJAnalysisLiteModule(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  float delta_phi(const float phi1, const float phi2);

protected:
  enum lepton { muon, elec };
  lepton channel_;
  
  //selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel; 
  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> trigger_sel;
  std::unique_ptr<uhh2::Selection> trigger2_sel;
  std::unique_ptr<uhh2::Selection> trigger3_sel;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<uhh2::Selection> triangc_sel;
  std::unique_ptr<uhh2::Selection> ttagevt_sel;
  std::unique_ptr<uhh2::Selection> topleppt_sel;
  std::unique_ptr<uhh2::Selection> chi2_sel;

  //ttbar reconstruction
  std::unique_ptr<uhh2::AnalysisModule> ttgenprod;
  std::unique_ptr<uhh2::AnalysisModule> reco_primlep;

  std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag0;
  std::unique_ptr<uhh2::AnalysisModule>  ttbar_reco__ttag1;
  std::unique_ptr<Chi2Discriminator>     ttbar_chi2__ttag0;
  std::unique_ptr<Chi2DiscriminatorTTAG> ttbar_chi2__ttag1;

  uhh2::Event::Handle<TTbarGen> h_ttbar_gen;
  uhh2::Event::Handle<std::vector<ReconstructionHypothesis> > h_ttbar_hyps;

  float lep1_pt_;
  float muo1_pt_max_, muo1_eta_max_;
  float chi2_cut_;
  float QCD_BDT_cut;
  JetId btag_ID_;
  CSVBTag::wp b_working_point;
  //   MVABTag::wp b_working_point;

  bool use_ttagging_;
  TopJetId ttag_ID_;
  float    ttag_minDR_jet_;

  bool blind_DATA_;

  bool store_PDF_weights_;

  //  Data/MC scale factors
  // std::unique_ptr<weightcalc_elecID>  elecIDSF;
  std::unique_ptr<uhh2::AnalysisModule> elecID_SF;
  std::unique_ptr<uhh2::AnalysisModule> elecGsf_SF;
  std::unique_ptr<uhh2::AnalysisModule> elecHLT_SF;

  std::unique_ptr<uhh2::AnalysisModule> pileupSF;
  std::unique_ptr<uhh2::AnalysisModule> muonID_SF;
  std::unique_ptr<uhh2::AnalysisModule> muonHLT_SF;
  std::unique_ptr<uhh2::AnalysisModule> muonHLT2_SF;
  std::unique_ptr<uhh2::AnalysisModule> muonTRK_SF;

  //!!  std::unique_ptr<weightcalc_elecHLT> elecHLTSF;

  //  std::unique_ptr<uhh2::AnalysisModule> btagSF;
  //  std::unique_ptr<Hists> h_btagMCeffi;
  std::unique_ptr<uhh2::AnalysisModule> csvSF;

  std::unique_ptr<weightcalc_ttagging> ttagSF_ct;
  std::unique_ptr<weightcalc_ttagging> ttagSF_upL;
  std::unique_ptr<weightcalc_ttagging> ttagSF_dnL;
  std::unique_ptr<weightcalc_ttagging> ttagSF_upT;
  std::unique_ptr<weightcalc_ttagging> ttagSF_dnT;

  //  std::unique_ptr<weightcalc_topptREWGT> topptREWGT;
  //  std::unique_ptr<TopPtReweight> topptREWGT;
  //  std::unique_ptr<weightcalc_WjetsREWGT> wjetsREWGT;
  

  //  VARS

  //  event
  Event::Handle<int>   h_run;
  Event::Handle<int>   h_lumi_block;
  Event::Handle<int>   h_event;
  Event::Handle<int>   h_pvN;
  Event::Handle<int>   h_muoN;
  Event::Handle<int>   h_eleN;
  Event::Handle<int>   h_btagN;
  Event::Handle<int>   h_ttagN;
  Event::Handle<bool>  h_ttagevt;
  Event::Handle<int>   h_ttgen;
  

  //  lepton
  Event::Handle<TLorentzVector> h_lep1;
  Event::Handle<int>            h_lep1__pdgID;
  Event::Handle<int>            h_lep1__charge;
  Event::Handle<float>          h_lep1__minDR_jet;
  Event::Handle<float>          h_lep1__pTrel_jet;
  /*
    Event::Handle<TLorentzVector> h_lep2;
    Event::Handle<int>            h_lep2__pdgID;
    Event::Handle<int>            h_lep2__charge;
    Event::Handle<float>          h_lep2__minDR_jet;
    Event::Handle<float>          h_lep2__pTrel_jet;

  */ 

  //  jet
  Event::Handle<TLorentzVector> h_jet1;
  Event::Handle<TLorentzVector> h_jet2;

  //MET
  Event::Handle<TLorentzVector> h_MET;
  Event::Handle<float>          h_MET__pz;
  

  //  ttbar reco hyp
  Event::Handle<float>          h_rec_chi2;
  Event::Handle<TLorentzVector> h_rec_tlep;
  Event::Handle<TLorentzVector> h_rec_thad;
  

  //  weight
  Event::Handle<float> h_wgtMC__GEN;

  //  Event::Handle<float> h_wgtMC__elecIDSF_ct;
  // Event::Handle<float> h_wgtMC__elecIDSF_up;
  // Event::Handle<float> h_wgtMC__elecIDSF_dn;

   // Event::Handle<float> h_wgtMC__elecHLTSF_ct;
   // Event::Handle<float> h_wgtMC__elecHLTSF_up;
   // Event::Handle<float> h_wgtMC__elecHLTSF_dn;

  Event::Handle<float> h_wgtMC__ttagSF_ct;
  Event::Handle<float> h_wgtMC__ttagSF_upL;
  Event::Handle<float> h_wgtMC__ttagSF_dnL;
  Event::Handle<float> h_wgtMC__ttagSF_upT;
  Event::Handle<float> h_wgtMC__ttagSF_dnT;

  Event::Handle<float> h_wgtMC__muR_ct__muF_up;
  Event::Handle<float> h_wgtMC__muR_ct__muF_dn;
  Event::Handle<float> h_wgtMC__muR_up__muF_ct;
  Event::Handle<float> h_wgtMC__muR_up__muF_up;
  Event::Handle<float> h_wgtMC__muR_dn__muF_ct;
  Event::Handle<float> h_wgtMC__muR_dn__muF_dn;

  Event::Handle<float> h_wgtMC__muRmuF_min; //envelope
  Event::Handle<float> h_wgtMC__muRmuF_max;

  //  Event::Handle<float> h_wgtMC__topptREWGT_ct;
  // Event::Handle<float> h_wgtMC__topptREWGT_up;
  // Event::Handle<float> h_wgtMC__topptREWGT_dn;

  // Event::Handle<float> h_wgtMC__wjetsREWGT_ct;

  Event::Handle<std::vector<float> > h_wgtMC__PDF;
  
  //
  //   __   __   __      __   __  ___               __          __        ___  __
  //  /  \ /  ` |  \    |__) |  \  |     \  /  /\  |__) |  /\  |__) |    |__  /__`
  //  \__X \__, |__/    |__) |__/  |      \/  /~~\ |  \ | /~~\ |__) |___ |___ .__/
  //  vars in TTree for Homemade ttbar MVA
  Event::Handle<float> tt_lep_pt;//lepton pt
  Event::Handle<float> tt_lep_pt_err;//lepton pt error
  Event::Handle<float> tt_lep_eta;//lepton eta
  Event::Handle<float> tt_lep_eta_SC;//lepton eta
  Event::Handle<float> tt_lep_eta_err;//lepton eta error
  Event::Handle<float> tt_lep_phi;//lepton eta
  Event::Handle<float> tt_lep_phi_err;//lepton eta error
  Event::Handle<float> tt_lep_xy;//x^2+y^2 vertex of the lepton 
  Event::Handle<float> tt_MwT;//Transversal mass
  Event::Handle<float> tt_WlepPt;//pt of W leptonic
  Event::Handle<float> tt_lep_fbrem;//fraction of energy loss due to bremsstrahlung. !cation: in 8TeV was well modeled only for |eta|<1.44
  Event::Handle<float> tt_rawmet_pt;//raw MET pt 
  Event::Handle<float> tt_met_pt;//MET pt 
  Event::Handle<float> tt_met_phi;//MET phi
  Event::Handle<float> tt_ljet_pt;//jet pt (for the leading jet)
  Event::Handle<float> tt_cjet_pt;//jet pt (for the close to lepton jet)
  Event::Handle<float> tt_ljet_phi;//jet pt (for the leading jet)
  Event::Handle<float> tt_cjet_phi;//jet pt (for the close to lepton jet)
  Event::Handle<float> tt_ljet_eta;//jet pt (for the leading jet)
  Event::Handle<float> tt_cjet_eta;//jet pt (for the close to lepton jet)
  Event::Handle<float> tt_jet2_pt;
  Event::Handle<float> tt_jet3_pt;
  Event::Handle<float> tt_jet2_phi;
  Event::Handle<float> tt_jet3_phi;
  Event::Handle<float> tt_jet2_eta;
  Event::Handle<float> tt_jet3_eta;
  Event::Handle<float> tt_ljet_M; Event::Handle<float> tt_cjet_M;  Event::Handle<float> tt_jet2_M; Event::Handle<float> tt_jet3_M; //jet mass
  Event::Handle<float> tt_lep_pt_ljet;//lepton Pt to the leading jet axis
  Event::Handle<float> tt_lep_pt_cjet;//lepton Pt to the closest not leading jet axis
  Event::Handle<float> tt_cjet_pt_ljet;//the closest not leading jet Pt to the leading jet axis
  Event::Handle<float> tt_dR_cljet_ljet;//distance in eta-phi between close jet  and leading jet
  Event::Handle<float> tt_dR_lep_cljet;//distance between lepton and the closest not leading jet in eta-phi
  Event::Handle<float> tt_dR_lep_ljet;//distance between lepton and the leading jet in eta-phi
  Event::Handle<float> tt_dPhi_lep_met;//distance in phi for MET to lepton  
  Event::Handle<float> tt_dPhi_ljet_met;//distance in phi for MET to the leading jet
  Event::Handle<float> tt_dPhi_cjet_met;//distance in phi for MET to the closest not leading jet to lepton 
  Event::Handle<int> tt_lep_class;//rec.electron classification
  Event::Handle<float> tt_ljet_CSV;//btagging: CombinedSecondaryVertex
  Event::Handle<float> tt_cjet_CSV;//btagging: CombinedSecondaryVertex
  Event::Handle<float> tt_jet2_CSV; Event::Handle<float> tt_jet3_CSV;
  Event::Handle<float> tt_nJets;//number of jets
  Event::Handle<float> tt_jets_pt;//sum of jets pt
  //   Event::Handle<float> tt_chi2;//chi2 of ttbar decay reconstruction

  //electron related variables (as for HEEP ID)
  Event::Handle<float> tt_Nclusters;
  Event::Handle<float> tt_full5x5_e1x5;
  Event::Handle<float> tt_full5x5_e2x5Max;
  Event::Handle<float> tt_full5x5_e5x5;
  Event::Handle<float> tt_dEtaInSeed;
  //electron related variables
  Event::Handle<float> tt_dB;
  Event::Handle<float> tt_sigmaIEtaIEta;
  Event::Handle<float> tt_HoverE;
  Event::Handle<float> tt_EoverPIn;
  Event::Handle<float> tt_hcalOverEcal;
  Event::Handle<float> tt_dr03TkSumPt;
  Event::Handle<float> tt_effArea;
  //  Event::Handle<float> tt_mvaNonTrigV0;
  Event::Handle<float> tt_dEtaIn;
  Event::Handle<float> tt_dPhiIn;
  // top tagging variables
  Event::Handle<float> tt_qjets_volatility;
  Event::Handle<float> tt_tau1;
  Event::Handle<float> tt_tau2;
  Event::Handle<float> tt_tau3;
  Event::Handle<float> tt_mvahiggsdiscr;
  Event::Handle<float> tt_prunedmass;
  Event::Handle<float> tt_softdropmass;

  Event::Handle<float> tt_ev_weight;//event weight
  Event::Handle<float> tt_mttbar;//ttbar rec inv. mass
  Event::Handle<float> tt_mttbar_gen;//ttbar generated inv. mass

  Event::Handle<float> tt_M12jet;//invariant mass of the first 2 jets
  Event::Handle<float> tt_M123jet;//invariant mass of the first 3 jets

  Event::Handle<int> tt_NDaughters_jet1;//number of constituets in the leading jet
  Event::Handle<int> tt_NDaughters_jet2;//number of constituets in the second jet
  Event::Handle<float> tt_dPhi_reclep_recneu; //distance in phi for reconstructed neu to lepton  
  Event::Handle<float> tt_dPhi_recblep_recneu;//distance in phi for reconstructed neu to b quark from lepton side 
  Event::Handle<float> tt_dR_reclep_recneu;//distance in R for reconstructed neu to lepton  
  Event::Handle<float> tt_dR_recblep_recneu;//distance in R for reconstructed neu to b quark from lepton side 

  float met_pt, met_phi, rawmet_pt;//MET
  float lep_pt, lep_eta, lep_eta_SC, fabs_lep_eta, lep_phi;//lepton
  float lep_pt_err, lep_eta_err, lep_phi_err;//lepton
  float ljet_pt; float ljet_eta; float ljet_phi;//leading jet 
  float cjet_pt; float cjet_eta; float cjet_phi;//close to the lepton jet (not leading)
  float fjet2_pt; float fjet2_eta; float fjet2_phi;//leading jet 
  float fjet3_pt; float fjet3_eta; float fjet3_phi;//leading jet 
  float ljet_M, cjet_M, jet2_M, jet3_M;
  float M12jet, M123jet;//invariant mass
  int NDaughters_jet1, NDaughters_jet2;//number of constituets

  float lep_xy;// x^2+y^2 vertex of the lepton
  float lep_fbrem; 
  float MwT;//Transversal mass
  float WlepPt;//pt of W leptonic
  float lep_pt_ljet;//lepton Pt to the leading jet axis
  float lep_pt_cjet;//lepton Pt to the closest not leading jet axis
  float cjet_pt_ljet;//the leading jet Pt to the closest not leading jet axis
  float dR_cljet_ljet;//distance in eta-phi between the closest jet and the leading jet 
  float dR_lep_cljet;//distance in eta-phi for the closest not leading jet to lepton  
  float dR_lep_ljet;//distance in eta-phi for the leading jet to lepton  
  float dPhi_lep_met;//distance in phi for MET to lepton  
  float dPhi_ljet_met;//distance in phi for MET to the leading jet
  float dPhi_cjet_met;//distance in phi for MET to the closest not leading jet to lepton 

  float dPhi_reclep_recneu;//distance in Phi for reconstructed neu to lepton  
  float dPhi_recblep_recneu;//distance in Phi for reconstructed neu to b quark from lepton side 
  float dR_reclep_recneu;//distance in R for reconstructed neu to lepton  
  float dR_recblep_recneu;//distance in R for reconstructed neu to b quark from lepton side 

  int lep_class;//rec.electron classification
  float ljet_CSV;//btag: combinedSecondaryVertex
  float cjet_CSV;//btag: combinedSecondaryVertex
  float jet2_CSV,jet3_CSV;//btag: combinedSecondaryVertex
  float jets_pt;//sum of jets pt
  float ev_weight;//

  float rec_ttbar_M_; float gen_ttbar_M_;
  float lep_Nclusters,lep_full5x5_e1x5,lep_full5x5_e2x5Max,lep_full5x5_e5x5,lep_dEtaInSeed;
  //  float log_ljet_pt, log_dR_cljet_ljet, log_dR_lep_cljet, log_lep_pt, jets_pt_to_lep_pt, lep_pt_ljet_to_lep_pt, log_met_pt_to_ljet_pt;
  //  float jets_pt_to_ljet_pt,  log_lep_xy_corr, log_ljet_CSV_ljet_pt;
  float lep_dB, lep_sigmaIEtaIEta, lep_HoverE, lep_EoverPIn, lep_hcalOverEcal, lep_dr03TkSumPt, lep_effArea;// lep_mvaNonTrigV0;
  float lep_dEtaIn, lep_dPhiIn;
  float top_qjets_volatility,top_tau1, top_tau2, top_tau3, top_mvahiggsdiscr, top_prunedmass, top_softdropmass;
  float TMVA_response;
  Event::Handle<float> tt_TMVA_response;//response of TMVA method
  std::unique_ptr<TMVA::Reader> reader;
  TString methodName;
  //  float varMVA[20];
  float varMVA[15];

  std::unique_ptr<Hists> lumihists; std::unique_ptr<Hists> lumihists_before;
  
  //W+Jets MVA Related, copied from https://github.com/isando3/ZprimeSemiLeptonic/blob/Summer17/src/TTbarLJAnalysisLiteModule.cxx
  TMVA::Reader *reader_wjets;
  float WJets_TMVA_response;
  Event::Handle<float> H_Rec_chi2;
  Event::Handle<float> wjets_TMVA_response;
  float mva_DRpt_norm;                                //1
  float mva_ht_met_lep_norm;                          //2
  float mva_lep1__minDR_jet;                          //3
  float mva_ptrel_norm;                               //4
  float mva_j1CSV;                                    //5
  float mva_jet1pt_norm;                              //6
  float mva_jet1m_norm;                               //7
  float mva_j2CSV;                                    //8
  float mva_jet2pt_norm;                              //9
  float mva_jet2m_norm;                               //10
  float mva_njets;                                    //11
  float mva_WptResponse;                                    //11
  float mva_s11;                                      //12
  float mva_s12;                                      //13
  float mva_s13;                                      //14
  float mva_s22;                                      //15
  float mva_s23;                                      //16
  float mva_s33;                                      //17
  float mva_sphericity;                               //18
  float mva_aplanarity;                               //19
  int it_num;
  int rot_num;
  Event::Handle<float>    h_jet1_pt;                 //9
  Event::Handle<float>    h_jet2_pt;                 //10

  Event::Handle<float>    h_lep1__pTrel_jet_norm;     //11
  Event::Handle<float>    h_ht_met_lep_norm;          //12
  Event::Handle<float>    h_jet1_csv;                //13
  Event::Handle<float>    h_jet2_csv;                //14
  Event::Handle<float>    h_DRpt;                     //15

  Event::Handle<float>    h_njets;                    //16
  Event::Handle<float>    h_jet1_m;                  //17
  Event::Handle<float>    h_jet2_m;                  //18
  Event::Handle<float>    h_lep1__minDR_norm;   //19
  Event::Handle<float> h_s33; 
  Event::Handle<float> h_jet1pt_chi2;
  Event::Handle<float> h_mttbar_chi2;

};

float TTbarLJAnalysisLiteModule::delta_phi(const float phi1, const float phi2){

  float a_dphi = fabs(phi1-phi2);
  if(a_dphi > M_PI) a_dphi = 2*M_PI - a_dphi;

  return a_dphi;
}

TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule(uhh2::Context& ctx){

  //  CONFIGURATION
  const bool isMC = (ctx.get("dataset_type") == "MC");

  const std::string& channel = ctx.get("channel", "");
  if     (channel == "muon") channel_ = muon;
  else if(channel == "elec") channel_ = elec;
  else {

    std::string log("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- ");
    log += "TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- invalid argument for 'channel' key in xml file (must be 'muon' or 'elec'): \""+channel+"\"";

    throw std::runtime_error(log);
  }

  use_ttagging_ = true;

  //  blind_DATA_ = ((ctx.get("dataset_version").find("BLINDED") != std::string::npos) && (ctx.get("dataset_type") == "DATA") && !isMC);
  //  blind_DATA_ = ((ctx.get("dataset_version").find("BLINDED") != std::string::npos) && (ctx.get("dataset_type") == "DATA") && !isMC);
  //    blind_DATA_ = true;//TEST blind both DATA and MC!
  blind_DATA_ = false;//TEST unblind both DATA and MC!

  const std::string& store_PDF_weights = ctx.get("store_PDF_weights", "");
  if     (store_PDF_weights == "true")  store_PDF_weights_ = true;
  else if(store_PDF_weights == "false") store_PDF_weights_ = false;
  else {

    std::string log("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- ");
    log += "invalid argument for 'store_PDF_weights' key in xml file (must be 'true' or 'false'): \""+store_PDF_weights+"\"";

    throw std::runtime_error(log);
  }
  

  const std::string& keyword = ctx.get("keyword");

  float jet1_pt(-1.), jet2_pt(-1.), MET(-1.), HT_lep(-1.);
  bool triangul_cut(false);
  bool topleppt_cut(false);

  QCD_BDT_cut = -10;

  if(keyword == "T0_v01" || keyword == "T1_v01"){ //Cut-Based analysis

    if     (keyword == "T0_v01") use_ttagging_ = false;
    else if(keyword == "T1_v01") use_ttagging_ = true;

    if(channel_ == muon){

      lep1_pt_ =   55.;
     
      jet1_pt  = 150.;
      jet2_pt  =  50.;

      MET      =  50.;
      HT_lep   = 150.;

      triangul_cut = false;
      topleppt_cut = false;

      // muo1_pt_max_ = 500.;
      // muo1_eta_max_ = 1.2;
      muo1_pt_max_ = 99999.0;
      muo1_eta_max_ = 2.4;
      chi2_cut_ = 30.;
      QCD_BDT_cut = -10;
    }
    else if(channel_ == elec){

      lep1_pt_ =   100.;
      jet1_pt  = 200.;
      jet2_pt  =  100.;
      MET      =  40.;

      HT_lep   =   0.;

      triangul_cut = false;
      topleppt_cut = false;

      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;
      chi2_cut_ = 30.;
      QCD_BDT_cut = -10;
    }
  }
  else if(keyword == "T0_v02" || keyword == "T1_v02"){ //for fast studies (elecID, trigger choise, etc)

    if     (keyword == "T0_v02") use_ttagging_ = false;
    else if(keyword == "T1_v02") use_ttagging_ = true;

    if(channel_ == muon){

      lep1_pt_ =   0.;
      jet1_pt  =   0.;
      jet2_pt  =   0.;

      MET      =   0.;
      HT_lep   =   0.;

      triangul_cut = false;
      topleppt_cut = false;

      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;

    }
    else if(channel_ == elec){

      lep1_pt_ =   0.;
      jet1_pt  =   0.;
      jet2_pt  =   0.;

      //      MET      = 100.;
      MET      =   0.;
      HT_lep   =   0.;

      triangul_cut = false;

      topleppt_cut = false;

      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;

    }
    chi2_cut_ = 30.;
  }
  else if(keyword == "T0_v03" || keyword == "T1_v03"){

    if     (keyword == "T0_v03") use_ttagging_ = false;
    else if(keyword == "T1_v03") use_ttagging_ = true;
    chi2_cut_ = 30.;
    if(channel_ == muon){

      lep1_pt_ =   0.;

      jet1_pt  = 250.;
      jet2_pt  =  70.;

      MET      = 120.;
      HT_lep   =   0.;

      triangul_cut = false;
      topleppt_cut = false;

      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;

    }
    else if(channel_ == elec){

      throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined working-point for \""+keyword+"\" in \"elec\" channel");
    }
  }
  else if(keyword == "T0_v04" || keyword == "T1_v04"){ //for QCD MVA input

    if     (keyword == "T0_v04") use_ttagging_ = false;
    else if(keyword == "T1_v04") use_ttagging_ = true;
    chi2_cut_ = 30.;
    if(channel_ == muon){

      throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined working-point for \""+keyword+"\" in \"muon\" channel");
    }
    else if(channel_ == elec){

      lep1_pt_ =   65.;

      jet1_pt  = 185.;
      jet2_pt  =  50.;

      MET      =  0.;
      HT_lep   =   0.;

      triangul_cut = false;
      topleppt_cut = false;

      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;
      QCD_BDT_cut = -10;
    }
  }
  else if(keyword == "T0_v05" || keyword == "T1_v05"){
    chi2_cut_ = 30.;
    if     (keyword == "T0_v05") use_ttagging_ = false;
    else if(keyword == "T1_v05") use_ttagging_ = true;
    if(channel_ == muon){
      throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined working-point for \""+keyword+"\" in \"muon\" channel");
    }
    else if(channel_ == elec){
      lep1_pt_ =   65.;
      jet1_pt  = 185.;
      jet2_pt  =  50.;
      MET      =  50.;
      HT_lep   =   0.;
      triangul_cut = false;
      topleppt_cut = false;
      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;
      QCD_BDT_cut = -10;
    }
  }
  else if(keyword == "T0_v06" || keyword == "T1_v06"){
    chi2_cut_ = 30.;

    if     (keyword == "T0_v06") use_ttagging_ = false;
    else if(keyword == "T1_v06") use_ttagging_ = true;
    if(channel_ == muon){
      lep1_pt_ =   55.;
      jet1_pt  = 150.;
      jet2_pt  =  50.;
      MET      =  50.;
      HT_lep   = 150.;
      triangul_cut = false;                                                                                                                                           
      topleppt_cut = false;                          
      muo1_pt_max_ = 0.0;
      muo1_eta_max_ = 0.0;
      chi2_cut_ = 30.;
      QCD_BDT_cut = -10;            
      //      throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined working-point for \""+keyword+"\" in \"muon\" channel");
    }
    else if(channel_ == elec){
      //      lep1_pt_ =   65.;
      lep1_pt_ =   80.;
      jet1_pt  = 185.;
      jet2_pt  =  50.;
      //      jet2_pt  =  300.; //TEST
      MET      =  120.;
      HT_lep   =   0.;
      triangul_cut = false;
      topleppt_cut = false;
      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;
      QCD_BDT_cut = -10;
     
    }
  }
  else if(keyword == "T0_v07" || keyword == "T1_v07"){
    chi2_cut_ = 30.;
    if     (keyword == "T0_v07") use_ttagging_ = false;
    else if(keyword == "T1_v07") use_ttagging_ = true;
    if(channel_ == muon){
      //throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined working-point for \""+keyword+"\" in \"muon\" channel");
      lep1_pt_ =   55.;
      jet1_pt  = 150.;
      jet2_pt  =  50.;
      MET      =  120.;
      HT_lep   = 0.;
      triangul_cut = false;                                                                                                                                           
      topleppt_cut = false;                          
      muo1_pt_max_ = 0.0;
      muo1_eta_max_ = 0.0;
      chi2_cut_ = 30.;
      QCD_BDT_cut = -10;        
    }
    else if(channel_ == elec){
      //      lep1_pt_ =   65.;
      lep1_pt_ =   80.;
      jet1_pt  = 185.;
      jet2_pt  =  50.;
      //      jet2_pt  =  300.; //TEST
      MET      =  120.;
      HT_lep   =   0.;
      triangul_cut = false;
      topleppt_cut = false;
      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;
      QCD_BDT_cut = -10;
    }
  }
  else if(keyword == "T0_v08" || keyword == "T1_v08"){
    if     (keyword == "T0_v08") use_ttagging_ = false;
    else if(keyword == "T1_v08") use_ttagging_ = true;
    if(channel_ == muon){
      throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined working-point for \""+keyword+"\" in \"muon\" channel");
    }
    else if(channel_ == elec){

      lep1_pt_ =   65.;
      jet1_pt  = 185.;
      jet2_pt  =  50.;

      //      MET      =   0.;
      MET      =   250.;
      HT_lep   =   0.;

      triangul_cut = false;
      topleppt_cut = false;

      muo1_pt_max_ = 0;
      muo1_eta_max_ = 0;
      // chi2_cut_ = 30.;
      //      QCD_BDT_cut = 0.5;
      QCD_BDT_cut = -10;
      // chi2_cut_ = uhh2::infinity;
    }
  }
  else throw std::runtime_error("TTbarLJAnalysisLiteModule::TTbarLJAnalysisLiteModule -- undefined \"keyword\" argument in .xml configuration file: "+keyword);
  

  

  //  COMMON MODULES

  //  CMS-certified luminosity sections
  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  /* MET filters */
  metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
  metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices");
  metfilters_sel->add<TriggerSelection>("globalTightHalo2016Filter", "Flag_globalTightHalo2016Filter");
  metfilters_sel->add<TriggerSelection>("HBHENoiseFilter", "Flag_HBHENoiseFilter");
  metfilters_sel->add<TriggerSelection>("HBHENoiseIsoFilter", "Flag_HBHENoiseIsoFilter");
  metfilters_sel->add<TriggerSelection>("EcalDeadCellTriggerPrimitiveFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter");
  //  metfilters_sel->add<TriggerSelection>("eeBadScFilter", "Flag_eeBadScFilter");
  metfilters_sel->add<TriggerSelection>("chargedHadronTrackResolutionFilter", "Flag_chargedHadronTrackResolutionFilter");
  metfilters_sel->add<TriggerSelection>("muonBadTrackFilter", "Flag_muonBadTrackFilter");
  //metantifilters_sel.reset(new uhh2::AndSelection(ctx, "metantifilters"));                                                                                           
  //  metantifilters_sel->add<TriggerSelection>("muonBadTrackFilter", "Flag_muonBadTrackFilter");                                                                      
  /**********************************/                                
  
  //OBJ CLEANING
  

  //  EVENT SELECTION
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));

  const std::string& trigger = ctx.get("trigger", "NULL");
  //  if(trigger != "NULL" && (!isMC || ctx.get("dataset_version") == "TTbar")) trigger_sel.reset(new TriggerSelection(trigger));
  //  if(trigger != "NULL" && !isMC ) trigger_sel.reset(new TriggerSelection(trigger));
  if(trigger != "NULL") trigger_sel.reset(new TriggerSelection(trigger)); //now Trigger infor should be added
  else                  trigger_sel.reset(new uhh2::AndSelection(ctx));
  const std::string& trigger2 = ctx.get("trigger2", "NULL");
  if(trigger2 != "NULL") trigger2_sel.reset(new TriggerSelection(trigger2)); //now Trigger infor should be added
  else                  trigger2_sel.reset(new uhh2::AndSelection(ctx));
  const std::string& trigger3 = ctx.get("trigger3", "NULL");
  if(trigger3 != "NULL") trigger3_sel.reset(new TriggerSelection(trigger3)); //now Trigger infor should be added
  else                  trigger3_sel.reset(new uhh2::AndSelection(ctx));

  std::cout<<"Trigger1 = "<<trigger<<" Trigger2 = "<<trigger2<<" Trigger3 = "<<trigger3<<std::endl;
  met_sel  .reset(new METCut  (MET   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep, uhh2::infinity));

  if(triangul_cut){

    if     (channel_ == elec) triangc_sel.reset(new TriangularCuts(M_PI/2., (M_PI/2.)/75.));
    else if(channel_ == muon) triangc_sel.reset(new uhh2::AndSelection(ctx));
  }
  else triangc_sel.reset(new uhh2::AndSelection(ctx));
  

  //  b-tagging
  const std::string& btag_wp = ctx.get("btag_wp");

  if     (btag_wp == "CSVL") btag_ID_ = CSVBTag(CSVBTag::WP_LOOSE);
  else if(btag_wp == "CSVM") btag_ID_ = CSVBTag(CSVBTag::WP_MEDIUM);
  else if(btag_wp == "CSVT") btag_ID_ = CSVBTag(CSVBTag::WP_TIGHT);

  if     (btag_wp == "CSVL") b_working_point = CSVBTag::WP_LOOSE;
  else if(btag_wp == "CSVM") b_working_point = CSVBTag::WP_MEDIUM;
  else if(btag_wp == "CSVT") b_working_point = CSVBTag::WP_TIGHT;


  //  if     (btag_wp == "MVAL") btag_ID_ = MVABTag(MVABTag::WP_LOOSE);
  //  else if(btag_wp == "MVAM") btag_ID_ = MVABTag(MVABTag::WP_MEDIUM);
  //  else if(btag_wp == "MVAT") btag_ID_ = MVABTag(MVABTag::WP_TIGHT);

  //  if     (btag_wp == "MVAL") b_working_point = MVABTag::WP_LOOSE;
  //  else if(btag_wp == "MVAM") b_working_point = MVABTag::WP_MEDIUM;
  //  else if(btag_wp == "MVAT") b_working_point = MVABTag::WP_TIGHT;

  //  h_btagMCeffi.reset(new BTagMCEfficiencyHists(ctx,"chi2__BTAG",b_working_point));
  //  h_btagMCeffi.reset(new BTagMCEfficiencyHists(ctx,"BTAG",b_working_point));


  //  t-tagging
  const std::string& ttag_wp = ctx.get("ttag_wp");

  ttag_ID_ = TopTagID_SoftDrop(ttag_wp);
  ttag_minDR_jet_ = 1.2;

  ttagevt_sel.reset(new TopTagEventSelection(ttag_ID_, ttag_minDR_jet_));
  

  //  TTBAR KINEMATICAL RECO

  const std::string ttbar_gen_label ("ttbargen");
  const std::string ttbar_hyps_label("TTbarReconstruction");
  const std::string ttbar_chi2_label("Chi2");

  ttgenprod.reset(new TTbarGenProducer(ctx, ttbar_gen_label, false));
  h_ttbar_gen = ctx.get_handle<TTbarGen>   (ttbar_gen_label);

  reco_primlep.reset(new PrimaryLepton(ctx));

  ttbar_reco__ttag0.reset(new HighMassTTbarReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label));
  ttbar_reco__ttag1.reset(new        TopTagReconstruction(ctx, NeutrinoReconstruction, ttbar_hyps_label, ttag_ID_, ttag_minDR_jet_));

  ttbar_chi2__ttag0.reset(new Chi2Discriminator(ctx, ttbar_hyps_label));
  ttbar_chi2__ttag0->set_Mtlep_mean (175.);
  ttbar_chi2__ttag0->set_Mtlep_sigma( 19.);
  ttbar_chi2__ttag0->set_Mthad_mean (177.);
  ttbar_chi2__ttag0->set_Mthad_sigma( 16.);

  ttbar_chi2__ttag1.reset(new Chi2DiscriminatorTTAG(ctx, ttbar_hyps_label));
  ttbar_chi2__ttag1->set_Mtlep_mean (175.);
  ttbar_chi2__ttag1->set_Mtlep_sigma( 19.);
  ttbar_chi2__ttag1->set_Mthad_mean (173.);
  ttbar_chi2__ttag1->set_Mthad_sigma( 15.);
  ttbar_chi2__ttag1->use_subjet_mass(false);

  h_ttbar_hyps = ctx.get_handle<std::vector<ReconstructionHypothesis> >(ttbar_hyps_label);
  

  if(topleppt_cut){

    if     (channel_ == elec) topleppt_sel.reset(new LeptonicTopPtCut(ctx, 140., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label));
    else if(channel_ == muon) topleppt_sel.reset(new uhh2::AndSelection(ctx));
  }
  else topleppt_sel.reset(new uhh2::AndSelection(ctx));

  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., chi2_cut_, ttbar_hyps_label, ttbar_chi2_label));
  //  chi2_sel.reset(new HypothesisDiscriminatorCut(ctx,  0., uhh2::infinity, ttbar_hyps_label, ttbar_chi2_label)); 
  //TEST no chi2 for QCD studies

  //  HISTS

  std::vector<std::string> htags_1({

      "jet2",
	"jet1",
	"trigger",
	"met",
    "htlep",
    //"triangc",
    "topleppt",
	});

  for(const auto& tag : htags_1){

    book_HFolder(tag, new TTbarLJHists(ctx, tag, ttag_ID_, ttag_minDR_jet_));
  }
  

  std::vector<std::string> htags_2({
        "antichi2",
	"antichi2__t0",
	"antichi2__t1",
	"antichi2__b0",
	"antichi2__b1",
	"antichi2__t0__b0",
	"antichi2__t0__b1",
	"antichi2__t1__b0",
	"antichi2__t1__b1",
	"antichi2__WJetsBDT",	
	"antichi2__t1__WJetsBDT",
	"antichi2__t0__WJetsBDT",
	"antichi2__antiWJetsBDT",
	"antichi2__t1__antiWJetsBDT",
	"antichi2__t0__antiWJetsBDT",
	"antichi2__WJetsBDT2",
	"antichi2__t1__WJetsBDT2",
	"antichi2__t0__WJetsBDT2",
	"antichi2__WJetsBDT3",
	"antichi2__t1__WJetsBDT3",
	"antichi2__t0__WJetsBDT3",
	// "antichi2__WJetsBDT_step1",	
	// "antichi2__t1__WJetsBDT_step1",
	// "antichi2__t0__WJetsBDT_step1",
	// "antichi2__WJetsBDT_step2",	
	// "antichi2__t1__WJetsBDT_step2",
	// "antichi2__t0__WJetsBDT_step2",
	// "antichi2__WJetsBDT_step3",	
	// "antichi2__t1__WJetsBDT_step3",
	// "antichi2__t0__WJetsBDT_step3",
	// "antichi2__WJetsBDT_step4",	
	// "antichi2__t1__WJetsBDT_step4",
	// "antichi2__t0__WJetsBDT_step4",
	// "antichi2__WJetsBDT_step5",	
	// "antichi2__t1__WJetsBDT_step5",
	// "antichi2__t0__WJetsBDT_step5",
	// "antichi2__WJetsBDT_step6",	
	// "antichi2__t1__WJetsBDT_step6",
	// "antichi2__t0__WJetsBDT_step6",
	// "antichi2__WJetsBDT_step7",	
	// "antichi2__t1__WJetsBDT_step7",
	// "antichi2__t0__WJetsBDT_step7",
	// "antichi2__WJetsBDT_step8",	
	// "antichi2__t1__WJetsBDT_step8",
	// "antichi2__t0__WJetsBDT_step8",



	"chi2",
	"chi2__t0",
	"chi2__t1",
	"chi2__b0",
	"chi2__b1",
	"chi2__t0__b0",
	"chi2__t0__b1",
	"chi2__t1__b0",
	"chi2__t1__b1",
	"chi2__WJetsBDT",
	"chi2__antiWJetsBDT",
	"chi2__t1__WJetsBDT",
	"chi2__t0__WJetsBDT",
	"chi2__t1__antiWJetsBDT",
	"chi2__t0__antiWJetsBDT",
	"chi2__WJetsBDT2",
	"chi2__t1__WJetsBDT2",
	"chi2__t0__WJetsBDT2",
	"chi2__WJetsBDT3",
	"chi2__t1__WJetsBDT3",
	"chi2__t0__WJetsBDT3",
	// "chi2__WJetsBDT_step1",	
	// "chi2__t1__WJetsBDT_step1",
	// "chi2__t0__WJetsBDT_step1",
	// "chi2__WJetsBDT_step2",	
	// "chi2__t1__WJetsBDT_step2",
	// "chi2__t0__WJetsBDT_step2",
	// "chi2__WJetsBDT_step3",	
	// "chi2__t1__WJetsBDT_step3",
	// "chi2__t0__WJetsBDT_step3",
	// "chi2__WJetsBDT_step4",	
	// "chi2__t1__WJetsBDT_step4",
	// "chi2__t0__WJetsBDT_step4",
	// "chi2__WJetsBDT_step5",	
	// "chi2__t1__WJetsBDT_step5",
	// "chi2__t0__WJetsBDT_step5",
	// "chi2__WJetsBDT_step6",	
	// "chi2__t1__WJetsBDT_step6",
	// "chi2__t0__WJetsBDT_step6",
	// "chi2__WJetsBDT_step7",	
	// "chi2__t1__WJetsBDT_step7",
	// "chi2__t0__WJetsBDT_step7",
	// "chi2__WJetsBDT_step8",	
	// "chi2__t1__WJetsBDT_step8",
	// "chi2__t0__WJetsBDT_step8",
	
	});

  for(const auto& tag : htags_2){

    book_HFolder(tag          , new TTbarLJHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  }
  

  // std::vector<std::string> htags_3({
  //   "chi2_L2",
  //   "chi2_L2__t0b0",
  //   "chi2_L2__t0b1",
  //   "chi2_L2__t0b2",
  //   "chi2_L2__t1",
  //     //    "chi2_L2__t1b0",
  //     //    "chi2_L2__t1b1",
  //     //    "chi2_L2__t1b2",
  // });

  // for(const auto& tag : htags_3){

  //   book_HFolder(tag          , new TTbarLJHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
  //   book_HFolder(tag+"__dilep", new DileptonHists     (ctx, tag+"__dilep"));
  //   book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  // }
  

  std::vector<std::string> htags_4({
      "Final",
	// "Final__t0b0",
	// "Final__t0b1",
	// "Final__t0b2",
	"Final__t0",
	"Final__t1",
	});

  for(const auto& tag : htags_4){

    book_HFolder(tag          , new TTbarLJHists      (ctx, tag          , ttag_ID_, ttag_minDR_jet_));
    book_HFolder(tag+"__ttbar", new EffyTTbarRECOHists(ctx, tag+"__ttbar", ttbar_gen_label, ttbar_hyps_label, ttbar_chi2_label));
  }

  

  //  Data/MC scale factors

  

  //  muon-ID
  const std::string& muonID_SFac    = ctx.get("muonID_SF_file");
  const std::string& muonID_directory    = ctx.get("muonID_SF_directory");


  //  muon-HLT
  const std::string& muonHLT_SFac   = ctx.get("muonHLT_SF_file");
  const std::string& muonHLT_directory   = ctx.get("muonHLT_SF_directory");
  //  const std::string& muonHLT2_directory   = ctx.get("muonHLT2_SF_directory");

  //  muon-Trk
  const std::string& muonTRK_SFac   = ctx.get("muonTRK_SF_file");


  //  elec-ID
  const std::string& elecID_SFac    = ctx.get("elecID_SF_file");
  //  const std::string& elecID_SFac_Data_part1    = ctx.get("elecID_SF_file_Data_part1");
  //   elecID_SF_Data_part1.reset(new MCElecScaleFactor(ctx, elecID_SFac_Data_part1, 0.0, "ID"));must be here to avoid double weight vars in the TTree
  //   const std::string& elecID_hist    = ctx.get("elecID_SF_hist");
  // elecIDSF.reset(new weightcalc_elecID(ctx, "electrons", elecID_SFac, elecID_hist, 0.00));

  //  elec-ID
  const std::string& elecGsf_SFac    = ctx.get("elecGsf_SF_file");

  // //!!  elec-HLT
  const std::string& elecHLT_SFac   = ctx.get("elecHLT_SF_file");

  //!!  const std::string& elecHLT_SFac   = ctx.get("elecHLT_SF_file");
  //!!  const std::string& elecHLT_hist   = ctx.get("elecHLT_SF_hist");
  //!!
  //!!  elecHLTSF.reset(new weightcalc_elecHLT(ctx, "electrons", elecHLT_SFac, elecHLT_hist, 0.005));
  //!!  


  //  t-tagging
  const std::string& ttag_SFac_file = ctx.get("ttag_SFs");
  const std::string& ttag_effy_file = ctx.get("ttag_eff");
  const std::string& ttag_effyL     = ctx.get("ttag_eff__jetL");
  const std::string& ttag_effyT     = ctx.get("ttag_eff__jetT");

  ttagSF_ct.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "CT", ttag_effy_file, ttag_effyL, ttag_effyT, false));
  ttagSF_upL.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "UP", "CT", ttag_effy_file, ttag_effyL, ttag_effyT, false));
  ttagSF_dnL.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "DN", "CT", ttag_effy_file, ttag_effyL, ttag_effyT, false));
  
  ttagSF_upT.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "UP", ttag_effy_file, ttag_effyL, ttag_effyT, false));
  ttagSF_dnT.reset(new weightcalc_ttagging(ttag_SFac_file, ttag_wp, "comb", "comb", "CT", "DN", ttag_effy_file, ttag_effyL, ttag_effyT, false));
  // //

  // // top-pt reweighting
  // if(ctx.get("dataset_version").find("TTbar") != std::string::npos || ctx.get("dataset_version").find("TTBar") != std::string::npos){
  //   std::cout<<"Set top pt reweighting!"<<std::endl;
  //   topptREWGT.reset(new TopPtReweight(ctx, 0.156, -0.00137, ttbar_gen_label, "wgtMC__topptREWGT_ct"));
  // }
  //

  // // W+jets reweighting (NLO/LO k-factors)
  // if(ctx.get("dataset_version").find("WJets") != std::string::npos){
  //   wjetsREWGT.reset(new weightcalc_WjetsREWGT());
  // }
  // //

  ////


  //// VARS
  ctx.undeclare_all_event_output();

  //pileup (define it after undeclaring all other variables to keep the weights in the output)
  pileupSF.reset(new MCPileupReweight(ctx));

  // //muon ID scale factors

  muonTRK_SF.reset(new MCMuonTrkScaleFactor(ctx, muonTRK_SFac, 0.0, "TRK"));
  muonID_SF.reset(new MCMuonScaleFactor(ctx, muonID_SFac, muonID_directory, 1., "ID")); //hypot(1.0%,0.5%) //used 1.12
  //muonHLT_SF.reset(new MCMuonScaleFactor(ctx, muonHLT_SFac, muonHLT_directory, 0.5, "HLT",false));//TEST
  muonHLT_SF.reset(new MCMuonScaleFactor(ctx, muonHLT_SFac, muonHLT_directory, 5.0, "HLT",true));//TEST
  //lumi_tot = string2double(ctx.get("target_lumi"));
  //lumi1 = 622.;//0.622/fb in 2016 data
  //lumi2 = lumi_tot - lumi1;

  //muonTRK_SF.reset(new MCMuonTrkScaleFactor(ctx, muonTRK_SFac, 0.0, "TRK"));

  // // elec-ID
  elecID_SF.reset(new MCElecScaleFactor(ctx, elecID_SFac, 0.0, "ID"));
  // double lumi_tot = string2double(ctx.get("target_lumi"));
  // double lumi1 = 500.;//0.5/fb in 2016 data
  // double lumi2 = lumi_tot - lumi1;
  // elecID_SF.reset(new MCElecScaleFactor2(ctx, elecID_SFac_Data_part1, elecID_SFac, lumi1, lumi2, 0.0, "ID"));

  // // elec-ID
  elecGsf_SF.reset(new MCElecScaleFactor(ctx, elecGsf_SFac, 0.0, "Gsf"));
  // // elec-HLT
  elecHLT_SF.reset(new MCElecScaleFactor(ctx, elecHLT_SFac, 0.0, "HLT"));

  // // // //b-tagging scale factors
  // // //  btagSF.reset(new MCBTagScaleFactor(ctx, b_working_point));
  // btagSF.reset(new MCBTagScaleFactor(ctx, b_working_point,"jets","central","comb","incl","MCBtagEfficiencies"));//CSV
  // //  btagSF.reset(new MCBTagScaleFactor(ctx, b_working_point,"jets","central","ttbar","incl","MCBtagEfficiencies"));//MVA

  // CSVv2 Shape Systematic
  csvSF.reset(new MCCSVv2ShapeSystematic(ctx, "jets","central","iterativefit","","MCCSVv2ShapeSystematic"));//CSV

  // event
  h_run             = ctx.declare_event_output<int>("run");
  h_lumi_block      = ctx.declare_event_output<int>("lumi_block");
  h_event           = ctx.declare_event_output<int>("event");

  h_pvN             = ctx.declare_event_output<int>("pvN");

  h_muoN            = ctx.declare_event_output<int>("muoN");
  h_eleN            = ctx.declare_event_output<int>("eleN");

  h_btagN           = ctx.declare_event_output<int>("btagN");
  h_ttagN           = ctx.declare_event_output<int>("ttagN");

  h_ttagevt         = ctx.declare_event_output<bool>("ttagevt");

  h_ttgen           = ctx.declare_event_output<int>("ttgen");
  //

  // lepton
  h_lep1            = ctx.declare_event_output<TLorentzVector>("lep1");
  h_lep1__pdgID     = ctx.declare_event_output<int>           ("lep1__pdgID");
  h_lep1__charge    = ctx.declare_event_output<int>           ("lep1__charge");
  h_lep1__minDR_jet = ctx.declare_event_output<float>         ("lep1__minDR_jet");
  h_lep1__pTrel_jet = ctx.declare_event_output<float>         ("lep1__pTrel_jet");
  /*
    h_lep2            = ctx.declare_event_output<TLorentzVector>("lep2");
    h_lep2__pdgID     = ctx.declare_event_output<int>           ("lep2__pdgID");
    h_lep2__charge    = ctx.declare_event_output<int>           ("lep2__charge");
    h_lep2__minDR_jet = ctx.declare_event_output<float>         ("lep2__minDR_jet");
    h_lep2__pTrel_jet = ctx.declare_event_output<float>         ("lep2__pTrel_jet");
  */

  //

  // jet
  h_jet1            = ctx.declare_event_output<TLorentzVector>("jet1");
  h_jet2            = ctx.declare_event_output<TLorentzVector>("jet2");
  //

  // MET
  h_MET             = ctx.declare_event_output<TLorentzVector>("MET");
  h_MET__pz         = ctx.declare_event_output<float>         ("MET__pz");
  //

  // ttbar reco hyp
  h_rec_chi2        = ctx.declare_event_output<float>         ("rec_chi2");
  h_rec_tlep        = ctx.declare_event_output<TLorentzVector>("rec_tlep");
  h_rec_thad        = ctx.declare_event_output<TLorentzVector>("rec_thad");
  //

  // weight
  h_wgtMC__GEN            = ctx.declare_event_output<float>("wgtMC__GEN");

  // h_wgtMC__elecIDSF_ct    = ctx.declare_event_output<float>("wgtMC__elecIDSF_ct");
  // h_wgtMC__elecIDSF_up    = ctx.declare_event_output<float>("wgtMC__elecIDSF_up");
  // h_wgtMC__elecIDSF_dn    = ctx.declare_event_output<float>("wgtMC__elecIDSF_dn");

  // h_wgtMC__elecHLTSF_ct   = ctx.declare_event_output<float>("wgtMC__elecHLTSF_ct");
  // h_wgtMC__elecHLTSF_up   = ctx.declare_event_output<float>("wgtMC__elecHLTSF_up");
  // h_wgtMC__elecHLTSF_dn   = ctx.declare_event_output<float>("wgtMC__elecHLTSF_dn");

  h_wgtMC__ttagSF_ct      = ctx.declare_event_output<float>("wgtMC__ttagSF_ct");
  h_wgtMC__ttagSF_upL     = ctx.declare_event_output<float>("wgtMC__ttagSF_upL");
  h_wgtMC__ttagSF_dnL     = ctx.declare_event_output<float>("wgtMC__ttagSF_dnL");
  h_wgtMC__ttagSF_upT     = ctx.declare_event_output<float>("wgtMC__ttagSF_upT");
  h_wgtMC__ttagSF_dnT     = ctx.declare_event_output<float>("wgtMC__ttagSF_dnT");

  h_wgtMC__muR_ct__muF_up = ctx.declare_event_output<float>("wgtMC__muR_ct__muF_up");
  h_wgtMC__muR_ct__muF_dn = ctx.declare_event_output<float>("wgtMC__muR_ct__muF_dn");
  h_wgtMC__muR_up__muF_ct = ctx.declare_event_output<float>("wgtMC__muR_up__muF_ct");
  h_wgtMC__muR_up__muF_up = ctx.declare_event_output<float>("wgtMC__muR_up__muF_up");
  h_wgtMC__muR_dn__muF_ct = ctx.declare_event_output<float>("wgtMC__muR_dn__muF_ct");
  h_wgtMC__muR_dn__muF_dn = ctx.declare_event_output<float>("wgtMC__muR_dn__muF_dn");

  h_wgtMC__muRmuF_min = ctx.declare_event_output<float>("wgtMC__muRmuF_min");
  h_wgtMC__muRmuF_max = ctx.declare_event_output<float>("wgtMC__muRmuF_max");

  // h_wgtMC__topptREWGT_ct  = ctx.declare_event_output<float>("wgtMC__topptREWGT_ct");
  // h_wgtMC__topptREWGT_up  = ctx.declare_event_output<float>("wgtMC__topptREWGT_up");
  // h_wgtMC__topptREWGT_dn  = ctx.declare_event_output<float>("wgtMC__topptREWGT_dn");

  //  h_wgtMC__wjetsREWGT_ct  = ctx.declare_event_output<float>("wgtMC__wjetsREWGT_ct");
  h_wgtMC__PDF            = ctx.declare_event_output<std::vector<float> >("wgtMC__PDF");

  ///Homemade ttbar MVA input
  met_pt = -100;met_phi = -100;  rawmet_pt = -100;
  ljet_pt = -100; cjet_pt = -100;
  ljet_phi = -100; cjet_phi = -100;
  ljet_eta = -100; cjet_eta = -100;
  fjet2_pt = -100; fjet3_pt = -100;                                                                                                                 
  fjet2_phi = -100; fjet3_phi = -100;                                                                                                               
  fjet2_eta = -100; fjet3_eta = -100;  
  lep_pt = -100; lep_eta = -100; lep_eta_SC = -100; fabs_lep_eta = -100; lep_phi = -100; 
  lep_pt_err = -100; lep_eta_err = -100; lep_phi_err = -100; 
  lep_xy = -100; lep_fbrem = -100;

  MwT = -100; WlepPt = -100;
  lep_pt_ljet = -100; lep_pt_cjet = -100; cjet_pt_ljet = -100;
  dR_cljet_ljet = -100; dR_lep_cljet = -100; dR_lep_ljet = -100;
  lep_class = -10;
  ev_weight = -100;
  // log_ljet_pt = -100; log_dR_cljet_ljet = -100; log_dR_lep_cljet = -100; log_lep_pt = -100;
  jets_pt = -100;
  // jets_pt_to_lep_pt = -100; lep_pt_ljet_to_lep_pt=0; log_met_pt_to_ljet_pt = -100;
  // jets_pt_to_ljet_pt = -100;  log_lep_xy_corr = -100;  log_ljet_CSV_ljet_pt = -100;
  gen_ttbar_M_ = -100; rec_ttbar_M_= -100;
  ljet_M = -100; cjet_M = -100; jet2_M = -100; jet3_M = -100;
  cjet_CSV = -100; ljet_CSV = -100; jet2_CSV = -100; jet3_CSV = -100;
  tt_met_pt = ctx.declare_event_output<float>("met_pt");
  tt_rawmet_pt = ctx.declare_event_output<float>("raw_met_pt");
  tt_met_phi = ctx.declare_event_output<float>("met_phi");
  tt_lep_pt = ctx.declare_event_output<float>("lep_pt");
  tt_lep_pt_err = ctx.declare_event_output<float>("lep_pt_err");
  tt_lep_eta = ctx.declare_event_output<float>("lep_eta");
  tt_lep_eta_SC = ctx.declare_event_output<float>("lep_eta_SC");
  tt_lep_eta_err = ctx.declare_event_output<float>("lep_eta_err");
  tt_lep_phi = ctx.declare_event_output<float>("lep_phi");
  tt_lep_phi_err = ctx.declare_event_output<float>("lep_phi_err");
  tt_ljet_pt = ctx.declare_event_output<float>("ljet_pt");
  tt_cjet_pt = ctx.declare_event_output<float>("cjet_pt");
  tt_ljet_phi = ctx.declare_event_output<float>("ljet_phi");
  tt_cjet_phi = ctx.declare_event_output<float>("cjet_phi");
  tt_ljet_eta = ctx.declare_event_output<float>("ljet_eta");
  tt_cjet_eta = ctx.declare_event_output<float>("cjet_eta");
  tt_jet2_pt = ctx.declare_event_output<float>("fjet2_pt");                                                                                  
  tt_jet3_pt = ctx.declare_event_output<float>("fjet3_pt");                                                                                  
  tt_jet2_phi = ctx.declare_event_output<float>("fjet2_phi");                                                                                  
  tt_jet3_phi = ctx.declare_event_output<float>("fjet3_phi");                                                                                
  tt_jet2_eta = ctx.declare_event_output<float>("fjet2_eta");                                                                                
  tt_jet3_eta = ctx.declare_event_output<float>("fjet3_eta");
  tt_lep_xy = ctx.declare_event_output<float>("lep_xy");
  tt_lep_fbrem = ctx.declare_event_output<float>("lep_fbrem");
  tt_MwT = ctx.declare_event_output<float>("MwT");
  tt_WlepPt = ctx.declare_event_output<float>("WlepPt");
  tt_lep_pt_ljet = ctx.declare_event_output<float>("lep_pt_ljet");
  tt_lep_pt_cjet = ctx.declare_event_output<float>("lep_pt_cjet");
  tt_cjet_pt_ljet = ctx.declare_event_output<float>("cjet_pt_ljet");
  tt_dR_cljet_ljet = ctx.declare_event_output<float>("dR_cljet_ljet");
  tt_dR_lep_cljet = ctx.declare_event_output<float>("dR_lep_cljet");
  tt_dR_lep_ljet = ctx.declare_event_output<float>("dR_lep_ljet");
  tt_dPhi_lep_met = ctx.declare_event_output<float>("dPhi_lep_met");
  tt_dPhi_ljet_met = ctx.declare_event_output<float>("dPhi_ljet_met");
  tt_dPhi_cjet_met = ctx.declare_event_output<float>("dPhi_cjet_met");
  tt_lep_class = ctx.declare_event_output<int>("lep_class");
  tt_ev_weight = ctx.declare_event_output<float>("weight");
  tt_mttbar = ctx.declare_event_output<float>("Mttbar");
  tt_mttbar_gen = ctx.declare_event_output<float>("Mttbar_gen");
  tt_nJets= ctx.declare_event_output<float>("nJets");
  tt_jets_pt = ctx.declare_event_output<float>("jets_pt");

  tt_ljet_M = ctx.declare_event_output<float>("ljet_M");
  tt_cjet_M = ctx.declare_event_output<float>("cjet_M");
  tt_jet2_M = ctx.declare_event_output<float>("jet2_M");
  tt_jet3_M = ctx.declare_event_output<float>("jet3_M");
  tt_ljet_CSV = ctx.declare_event_output<float>("ljet_CSV");
  tt_cjet_CSV = ctx.declare_event_output<float>("cjet_CSV");
  tt_jet2_CSV = ctx.declare_event_output<float>("jet2_CSV");
  tt_jet3_CSV = ctx.declare_event_output<float>("jet3_CSV");
  
  lep_Nclusters = -100; lep_full5x5_e1x5 = -100; lep_full5x5_e2x5Max = -100; lep_full5x5_e5x5 = -100; lep_dEtaInSeed = -100;
  tt_Nclusters = ctx.declare_event_output<float>("lep_Nclusters");
  tt_full5x5_e1x5 = ctx.declare_event_output<float>("lep_full5x5_e1x5");
  tt_full5x5_e2x5Max = ctx.declare_event_output<float>("lep_full5x5_e2x5Max");
  tt_full5x5_e5x5 = ctx.declare_event_output<float>("lep_full5x5_e5x5");
  tt_dEtaInSeed = ctx.declare_event_output<float>("lep_dEtaInSeed");
  lep_dB = -100; lep_sigmaIEtaIEta = -100; lep_HoverE = -100; lep_EoverPIn = -100; lep_hcalOverEcal = -100; lep_dr03TkSumPt = -100; lep_effArea = -100; //lep_mvaNonTrigV0 = -100;
  lep_dEtaIn = -100; lep_dPhiIn = -100;
  tt_dB = ctx.declare_event_output<float>("lep_dB");
  tt_sigmaIEtaIEta = ctx.declare_event_output<float>("lep_sigmaIEtaIEta");
  tt_HoverE = ctx.declare_event_output<float>("lep_HoverE");
  tt_EoverPIn = ctx.declare_event_output<float>("lep_EoverPIn");
  tt_hcalOverEcal = ctx.declare_event_output<float>("lep_hcalOverEcal");
  tt_dr03TkSumPt = ctx.declare_event_output<float>("lep_dr03TkSumPt");
  tt_effArea = ctx.declare_event_output<float>("lep_effArea");
  //  tt_mvaNonTrigV0 = ctx.declare_event_output<float>("lep_mvaNonTrigV0");
  tt_dEtaIn = ctx.declare_event_output<float>("lep_dEtaIn");
  tt_dPhiIn = ctx.declare_event_output<float>("lep_dPhiIn");

  top_qjets_volatility = -100; top_tau1 = -100; top_tau2 = -100; top_tau3 = -100; top_mvahiggsdiscr = -100; top_prunedmass = -100; top_softdropmass = -100;
  tt_qjets_volatility = ctx.declare_event_output<float>("top_qjets_volatility");
  tt_tau1 = ctx.declare_event_output<float>("top_tau1");
  tt_tau2 = ctx.declare_event_output<float>("top_tau2");
  tt_tau3 = ctx.declare_event_output<float>("top_tau3");
  tt_mvahiggsdiscr = ctx.declare_event_output<float>("top_mvahiggsdiscr");
  tt_prunedmass = ctx.declare_event_output<float>("top_prunedmass");
  tt_softdropmass = ctx.declare_event_output<float>("top_softdropmass");

  M123jet = -100;  M12jet = -100;
  tt_M12jet = ctx.declare_event_output<float>("M12jet");
  tt_M123jet = ctx.declare_event_output<float>("M123jet");
  NDaughters_jet2 = -100;  NDaughters_jet1 = -100; 
  tt_NDaughters_jet1 = ctx.declare_event_output<int>("NDaughters_jet1");
  tt_NDaughters_jet2 = ctx.declare_event_output<int>("NDaughters_jet2");

  dPhi_reclep_recneu = -100; dPhi_recblep_recneu = -100; dR_reclep_recneu = -100; dR_recblep_recneu = -100;
  tt_dPhi_reclep_recneu = ctx.declare_event_output<float>("dPhi_reclep_recneu");
  tt_dPhi_recblep_recneu = ctx.declare_event_output<float>("dPhi_recblep_recneu");
  tt_dR_reclep_recneu = ctx.declare_event_output<float>("dR_reclep_recneu");
  tt_dR_recblep_recneu = ctx.declare_event_output<float>("dR_recblep_recneu");

  /// Homemade ttbar MVA output for QCD





  // --- Create the Reader object
  TMVA_response = -100;
  tt_TMVA_response = ctx.declare_event_output<float>("TMVA_response"); // this var is ploted in hist class, should always be filled
  if(channel_ == elec){
    reader.reset(new TMVA::Reader( "!Color:!Silent" ));
    // reader->AddVariable("lep_pt/Mttbar", &varMVA[0]);  
    // reader->AddVariable("fabs(lep_eta)", &varMVA[1]);
    // reader->AddVariable("lep_eta_err",&varMVA[2]); 
    // reader->AddVariable("lep_pt_err", &varMVA[3]);
    // //    reader->AddVariable("lep_full5x5_e5x5", &varMVA[4]);
    // reader->AddVariable("lep_dB", &varMVA[4]);
    // reader->AddVariable("fabs(lep_dPhiIn)", &varMVA[5]);
    // reader->AddVariable("fabs(lep_dEtaInSeed)", &varMVA[6]);
    // //    reader->AddVariable("lep_hcalOverEcal", &varMVA[8]);
    // reader->AddVariable("lep_dr03TkSumPt", &varMVA[7]);
    // reader->AddVariable("lep_effArea", &varMVA[8]);
    // reader->AddVariable("lep1__minDR_jet", &varMVA[9]);
    // reader->AddVariable("fabs(ljet_eta)", &varMVA[10]);
    // reader->AddVariable("ljet_CSV", &varMVA[11]);
    // reader->AddVariable("fabs(fjet2_eta)", &varMVA[12]);
    // reader->AddVariable("fjet2_pt/Mttbar", &varMVA[13]);
    // reader->AddVariable("jet2_CSV", &varMVA[14]);
    // reader->AddVariable("met_pt/MwT", &varMVA[15]);                                                                                 
    // reader->AddVariable("ttagN", &varMVA[16]);                                                                                             
    // reader->AddVariable("btagN", &varMVA[17]); 

    // reader->AddVariable("lep_pt/Mttbar", &varMVA[0]);  
    // reader->AddVariable("fabs(lep_eta)", &varMVA[1]);
    // reader->AddVariable("log(lep_eta_err)",&varMVA[2]); 
    // reader->AddVariable("log(lep1__minDR_jet)", &varMVA[3]);
    // reader->AddVariable("fabs(ljet_eta)", &varMVA[4]);
    // //    reader->AddVariable("ljet_CSV", &varMVA[5]);
    // reader->AddVariable("fabs(fjet2_eta)", &varMVA[5]);
    // //    reader->AddVariable("jet2_CSV", &varMVA[7]);
    // reader->AddVariable("ttagN", &varMVA[6]);                                                                                             
    // reader->AddVariable("btagN", &varMVA[7]); 
    // //    reader->AddVariable("lep_mvaNonTrigV0", &varMVA[10]);
    // reader->AddVariable("lep_class", &varMVA[8]);
    // reader->AddVariable("NDaughters_jet1", &varMVA[9]);
    // reader->AddVariable("NDaughters_jet2", &varMVA[10]);
    // reader->AddVariable("log((jets_pt-ljet_pt-fjet2_pt)/Mttbar)", &varMVA[11]);
  

    reader->AddVariable("lep_pt/Mttbar", &varMVA[0]);  
    reader->AddVariable("fabs(lep_eta)", &varMVA[1]);
    reader->AddVariable("log(lep1__minDR_jet)", &varMVA[2]);
    reader->AddVariable("log((lep1__pTrel_jet)/Mttbar)", &varMVA[3]);
    reader->AddVariable("fabs(ljet_eta)", &varMVA[4]);
    reader->AddVariable("fabs(fjet2_eta)", &varMVA[5]);
    reader->AddVariable("ttagN", &varMVA[6]);                                                                                             
    reader->AddVariable("btagN", &varMVA[7]); 
    reader->AddVariable("log((jets_pt-ljet_pt)/Mttbar)", &varMVA[8]);
    reader->AddVariable("log(rec_chi2)", &varMVA[9]); 
    reader->AddVariable("dR_recblep_recneu", &varMVA[10]); 
    reader->AddVariable("dR_reclep_recneu", &varMVA[11]); 


    //  //  TString dir    = "/afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_7_6_3_patch2/src/UHH2/ZprimeSemiLeptonic/TMVA_weights/76X/"; //ToDo: make it param in xml
    //  TString dir    = "/afs/desy.de/user/k/karavdia/CMSSW_8_0_8_patch1/src/UHH2/ZprimeSemiLeptonic/TMVA_weights/76X/"; //ToDo: make it param in xml
    // methodName = "BDT::BDTG";
    // TString weightfile = dir + "Homemade_TTbarMVAClassification_BDTG_DataDriven_MET40_20vras.weights.xml";
    // methodName = "MLP::MLPBNN";
    // TString weightfile = dir + "Homemade_TTbarMVAClassification_MLPBNN_DataDrivenMET30_24Vars_N-22_N+2.weights.xml";

    //    TString dir    = "/afs/desy.de/user/k/karavdia/CMSSW_8_0_9/src/UHH2/ZprimeSemiLeptonic/TMVA_weights/80X/"; //ToDo: make it param in xml
    //    TString dir    = "/afs/desy.de/user/k/karavdia/CMSSW_8_0_19_patch2/UHH2/ZprimeSemiLeptonic/TMVA_weights/80_19/"; //ToDo: make it param in xml
    //TString dir    = "/afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/TMVA_weights/80_19/"; //ToDo: make it param in xml
    //    TString weightfile = dir + "Homemade_TTbarMVAClassification_BDTG.weights.xml";
    //    TString weightfile = dir + "Homemade_TTbarMVAClassification_BDTG_12Vars.weights.xml";
    //TString weightfile = dir + "Homemade_TTbarMVAClassification_BDTG_blep.weights.xml";
    TString weightfile = ctx.get("qcd_ele_bdt");
    methodName = "BDT::BDTG";
    reader->BookMVA(methodName, weightfile);
  }
  // ////

  lumihists_before.reset(new LuminosityHists(ctx, "lumi_before","",true));
  lumihists.reset(new LuminosityHists(ctx, "lumi","",true));

  //W+Jets MVA related
  h_s33             = ctx.declare_event_output<float>("s33");
  h_jet2_pt          = ctx.declare_event_output<float>          ("jet2_pt");
  h_ht_met_lep_norm   = ctx.declare_event_output<float>          ("ht_met_lep_norm");
  h_jet1_csv         = ctx.declare_event_output<float>           ("jet1_csv");
  h_jet2_csv         = ctx.declare_event_output<float>           ("jet2_csv");
  h_njets             = ctx.declare_event_output<float>             ("njets");
  h_DRpt              = ctx.declare_event_output<float>           ("DRpt");
  h_lep1__pTrel_jet_norm = ctx.declare_event_output<float>         ("lep1__pTrel_jet_norm"); 
  h_jet1_m         = ctx.declare_event_output<float>("jet1_m");
  h_lep1__minDR_norm = ctx.declare_event_output<float>("lep1__minDR_jet");
  h_jet2_m         = ctx.declare_event_output<float>("jet2_m");
  //  h_jet1pt =  ctx.declare_event_output<float>("h_jet1pt");
  //  h_mttbar =  ctx.declare_event_output<float>("h_mttbar");
  h_jet1pt_chi2 = ctx.declare_event_output<float>("h_jet1pt_chi2");
  h_mttbar_chi2 = ctx.declare_event_output<float>("h_mttbar_chi2");
  
  WJets_TMVA_response = -100;
  wjets_TMVA_response = ctx.declare_event_output<float>("WJets_TMVA_response");
  H_Rec_chi2 = ctx.declare_event_output<float>("H_Rec_chi2");
  //h_wjets_bdtresponse = ctx.declare_event_output<float>("wjets_bdtresponse");
  TMVA::Tools::Instance();
  reader_wjets = new TMVA::Reader();
  reader_wjets->AddVariable("DRpt", &mva_DRpt_norm);
  reader_wjets->AddVariable("ht_met_lep_norm", &mva_ht_met_lep_norm);
  reader_wjets->AddVariable("lep1__minDR_jet", &mva_lep1__minDR_jet);
  reader_wjets->AddVariable("lep1__pTrel_jet_norm", &mva_ptrel_norm);
  reader_wjets->AddVariable("jet1_csv", &mva_j1CSV);
  //  reader_wjets->AddVariable("jet1_pt", &mva_jet1pt_norm);
  reader_wjets->AddVariable("jet1_m", &mva_jet1m_norm);
  reader_wjets->AddVariable("jet2_csv", &mva_j2CSV);
  //reader_wjets->AddVariable("jet2_pt",&mva_jet2pt_norm);
  reader_wjets->AddVariable("jet2_m", &mva_jet2m_norm);
  reader_wjets->AddVariable("njets", &mva_njets);
  //  reader_wjets->AddVariable("WlepPt/ljet_pt", &mva_WptResponse);
  reader_wjets->AddVariable("s33", &mva_s33);
  //TString dirWJetsMVA = "/afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/TMVA_weights/80X/weights_80Xv3BDT_OPTIMIZED_50-001-10-0p2/TMVAClassification_BDT.weights.xml";
  TString dirWJetsMVA = ctx.get("wjet_bdt");
  reader_wjets->BookMVA("BDT method", dirWJetsMVA);

}

bool TTbarLJAnalysisLiteModule::process(uhh2::Event& event){
  
  event.set(wjets_TMVA_response,0);//set some dummy initial value
  //
  event.set(H_Rec_chi2,0);
  //event.set(h_jet1_pt,0);
  event.set(h_jet1_m,0);
  event.set(h_jet1_csv,0);
  event.set(h_jet2_m,0);   
  //event.set(h_lep1__minDR_norm,0); 
  event.set(h_jet2_csv,0);  
  event.set(h_njets,1);
  event.set(h_ht_met_lep_norm,0);
  event.set(h_lep1__pTrel_jet_norm,0);
  event.set(h_lep1__minDR_norm,0);
  event.set(h_s33,0);
  event.set(h_DRpt,0);
  event.set(h_jet1pt_chi2,0);
  event.set(h_mttbar_chi2,0);

  
  //  std::cout<<"   --- NEW event ---  "<<std::endl;
  //  std::cout << " Evt# "<<event.event<<" Run: "<<event.run<<" " << std::endl;
  // std::cout<<"   elecs = "<<event.electrons->size()<<" muons = "<<event.muons->size()<<" N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<std::endl;
  if(channel_ == muon && (event.electrons->size()>0 || event.muons->size()!=1)) return false; //veto additional leptons
  if(channel_ == elec && (event.muons->size()>0 || event.electrons->size()!=1)) return false;//veto additional leptons

  if(channel_ == elec && event.electrons->at(0).Class()==4) return false;//TEST veto gap electrons
  //  std::cout<<" Now let's do the selections "<<std::endl;
  event.set(tt_TMVA_response, 0);//set some dummy initial value
  //
  event.set(wjets_TMVA_response,0);
  event.set(h_rec_chi2,0);
  //event.set(h_jet1_pt,0);
  event.set(h_jet1_m,0);
  event.set(h_jet1_csv,0);
  event.set(h_jet2_pt,0);   
  //event.set(h_lep1__minDR_norm,0); 
  event.set(h_jet2_csv,0);  
  event.set(h_njets,1);
  event.set(h_ht_met_lep_norm,0);
  event.set(h_lep1__pTrel_jet_norm,0);
  event.set(h_lep1__minDR_norm,0);
  event.set(h_s33,0);
  event.set(h_DRpt,0);
  event.set(h_jet1pt_chi2,0);
  event.set(h_mttbar_chi2,0);
  //// COMMON MODULES

  float w_GEN(1.);
  if(!event.isRealData)
    w_GEN = event.weight;


  if(!event.isRealData){
    ttgenprod->process(event);
  }

  /* CMS-certified luminosity sections */
  if(event.isRealData){

    if(!lumi_sel->passes(event)) return false;
  }
  //  std::cout<<"Pile up next..."<<std::endl;
  ////

  //// HLT selection
  const bool pass_trigger = trigger_sel->passes(event);
  bool pass_trigger2 = false;
  if((event.run>275657 && channel_ == muon) || channel_ == elec || !event.isRealData){
    //  const bool pass_trigger2 = trigger2_sel->passes(event);
    pass_trigger2 = trigger2_sel->passes(event);
  }
  const bool pass_trigger3 = trigger3_sel->passes(event);
  // // //  if(event.run>274953 && channel_ == muon)
  // if(channel_ == muon)
  //   pass_trigger2 = trigger2_sel->passes(event);

  //  const bool pass_trigger2 = trigger2_sel->passes(event);
  //  if(!pass_trigger) return false;
  //  else 
  //  if(pass_trigger)  std::cout<<"Trigger1!!! HLT_1: "<<pass_trigger<<" HLT_2: "<<pass_trigger2<<std::endl;
  //  if(pass_trigger2) std::cout<<"Trigger2!!! HLT_1: "<<pass_trigger<<" HLT_2: "<<pass_trigger2<<std::endl;
  // if(pass_trigger || pass_trigger2) std::cout<<"Event passes the triggers"<<std::endl;
  //  std::cout<<"Trigger!!! "<<pass_trigger2<<" "<<pass_trigger<<std::endl;
  //  if(event.isRealData){
  //  if(!(pass_trigger || pass_trigger2)) return false; 
  //  if(!(pass_trigger || pass_trigger2 || pass_trigger3)) return false; 
  //  if(!pass_trigger) return false; //TEST only 1 trigger
  // if((event.run>275657 && channel_ == muon) || channel_ == elec){
    if(!pass_trigger && !pass_trigger2) return false; //TEST 
    // }
    //else
    // if(!pass_trigger) return false; //TEST 
 
  //}
  //   else std::cout<<" Passed trigger!!! "<<std::endl;
  //  if(lepN == 1) 
  HFolder("trigger")->fill(event);
  ////
  lumihists_before->fill(event);

  //// Data/MC scale factors
  ///  float w_elecIDSF_ct(1.) , w_elecIDSF_up(1.) , w_elecIDSF_dn(1.);
  //  float w_elecHLTSF_ct(1.), w_elecHLTSF_up(1.), w_elecHLTSF_dn(1.);

  //ttag SFs
  float w_ttagSF_ct(1.), w_ttagSF_upL(1.), w_ttagSF_dnL(1.), w_ttagSF_upT(1.), w_ttagSF_dnT(1.);

  float w_muR_ct__muF_up(1.), w_muR_ct__muF_dn(1.), w_muR_up__muF_ct(1.), w_muR_up__muF_up(1.), w_muR_dn__muF_ct(1.), w_muR_dn__muF_dn(1.);
  //  float w_topptREWGT_up(1.), w_topptREWGT_dn(1.); //w_topptREWGT_ct(1.);
  //  float w_wjetsREWGT_ct(1.);
  std::vector<float> w_PDF;
  w_PDF.clear();

  //    std::cout<<event.weight<<std::endl;
  //
  //pileup
  pileupSF->process(event);
  //  std::cout<<"Afte PileUp "<<event.weight<<std::endl;
  // // // b-tagging
  // std::cout<<"Before Btag SF: "<<event.weight<<std::endl;
  //  btagSF->process(event);
  csvSF->process(event);

  //  std::cout<<event.weight<<std::endl;
  //  muon-ID
  muonID_SF->process(event);
  //double w_wo_HLT = event.weight;
  // std::cout<<"HLT, w_wo_HLT = "<<w_wo_HLT<<std::endl;
  // // muon-HLT eff
  //muonHLT2_SF->process(event);
  //double w1 = event.weight;
  //event.weight = w_wo_HLT;
  muonHLT_SF->process(event);
  //double w2 = event.weight;
  ///double w = (lumi1*w1+lumi2*w2)/(lumi_tot);
  // std::cout<<"w1 = "<<w1<<" w2 = "<<w2<<" w = "<<w<<std::endl;
  //  std::cout<<"w = "<<w<<std::endl;
  //event.weight = w;

  //in 2016 data ICHEP JSON from [271036-274093] contains 0.622/fb


  //  std::cout<<event.weight<<std::endl;
  //  muon-Trk

  muonTRK_SF->process(event);
  //  std::cout<<event.weight<<std::endl;


  // // // elec-ID
  // //std::cout<<event.weight<<std::endl;
  elecID_SF->process(event);
  // //std::cout<<event.weight<<std::endl;
  // // elec-Gsf
  elecGsf_SF->process(event);
  // //  std::cout<<"BEFORE "<<event.weight<<std::endl;
  elecHLT_SF->process(event);//TEST HLT!!!
  //  std::cout<<"AFTER "<<event.weight<<std::endl;
  if(!event.isRealData){
    // if(channel_ == elec) event.weight *= 0.965657;//HLT SF
    // //std::cout<<event.weight<<std::endl;
    // //std::cout<<""<<std::endl;
    
    // // w_elecIDSF_ct  = elecIDSF->weight(event, "CT");
    // // w_elecIDSF_up  = elecIDSF->weight(event, "UP");
    // // w_elecIDSF_dn  = elecIDSF->weight(event, "DN");
    // // //
   
    // // // elec-HLT
    // w_elecHLTSF_ct = 0.965657;//!!elecHLTSF->weight(event, "CT");
    // w_elecHLTSF_up = 0.976657;//!!elecHLTSF->weight(event, "UP");
    // w_elecHLTSF_dn = 0.954657;//!!elecHLTSF->weight(event, "DN");
    // // //


    // elec-HLT
    // w_elecHLTSF_ct = 1.0;//!!elecHLTSF->weight(event, "CT");
    // w_elecHLTSF_up = 1.0;//!!elecHLTSF->weight(event, "UP");
    // w_elecHLTSF_dn = 1.0;//!!elecHLTSF->weight(event, "DN");
    //    if(channel_ == elec) event.weight *= w_elecHLTSF_ct;
    // 

    //    std::cout<<"event.weight = "<<event.weight<<std::endl;

    // // t-tagging
    w_ttagSF_ct    = ttagSF_ct ->weight(event);
    event.weight *= w_ttagSF_ct;
    if(fabs(w_ttagSF_ct)>10.)
      std::cout<<"!!!!!!!!!!!!!!!! w_ttagSF_ct = "<<w_ttagSF_ct<<std::endl;  
    w_ttagSF_upL   = ttagSF_upL->weight(event);
    if(fabs(w_ttagSF_upL)>10.)
      std::cout<<"!!!!!!!!!!!!!!!! w_ttagSF_upL = "<<w_ttagSF_upL<<std::endl;
    w_ttagSF_dnL   = ttagSF_dnL->weight(event);
    w_ttagSF_upT   = ttagSF_upT->weight(event);
    if(fabs(w_ttagSF_upT)>10.)
      std::cout<<"!!!!!!!!!!!!!! w_ttagSF_upT = "<<w_ttagSF_upT<<std::endl;
    w_ttagSF_dnT   = ttagSF_dnT->weight(event);
    // //

    // Renormalization/Factorization scales
    if(event.genInfo){

      if(event.genInfo->systweights().size() >= 9){

        if(event.genInfo->originalXWGTUP()){

          w_muR_ct__muF_up = (event.genInfo->systweights().at(1) / event.genInfo->originalXWGTUP());
          w_muR_ct__muF_dn = (event.genInfo->systweights().at(2) / event.genInfo->originalXWGTUP());
          w_muR_up__muF_ct = (event.genInfo->systweights().at(3) / event.genInfo->originalXWGTUP());
          w_muR_up__muF_up = (event.genInfo->systweights().at(4) / event.genInfo->originalXWGTUP());
          w_muR_dn__muF_ct = (event.genInfo->systweights().at(6) / event.genInfo->originalXWGTUP());
          w_muR_dn__muF_dn = (event.genInfo->systweights().at(8) / event.genInfo->originalXWGTUP());

          if(store_PDF_weights_){

            for(unsigned int i=9; i<event.genInfo->systweights().size(); ++i){

              const float pdf_w(event.genInfo->systweights().at(i) / event.genInfo->originalXWGTUP());
              w_PDF.push_back(pdf_w);
            }
          }
        }
      }
    }
    

    // // top-pt reweighting
    // if(topptREWGT.get()){
    //   //      std::cout<<"aw!"<<std::endl;
    //   topptREWGT->process(event);
    //   float w_topptREWGT_ct = event.get(h_wgtMC__topptREWGT_ct);
    //   //      std::cout<<w_topptREWGT_ct<<std::endl;
    //   //apply twice the shift as uncertainty
    //   w_topptREWGT_dn = w_topptREWGT_ct*w_topptREWGT_ct;
    //   w_topptREWGT_up = 1;
    //   //
    // }
    // //  


    // // W+jets reweighting
    // if(wjetsREWGT.get()) w_wjetsREWGT_ct = wjetsREWGT->weight(event);
    // //

    // central weight (histograms)
    //    if(fabs(w_ttagSF_ct-1.)>1e-4)
    //    event.weight *= w_ttagSF_ct;

    //

    //  if(channel_ == elec) event.weight *= w_elecIDSF_ct;
    // std::cout<<event.weight<<std::endl;
  }
  //  std::cout<<" ==== "<<std::endl;
  //

  ////

  //// LEPTON SELECTION

  // OF lepton veto
  bool pass_lepV(0);
  if     (channel_ == muon) pass_lepV = ((event.electrons->size() == 0));
  else if(channel_ == elec) pass_lepV = ((event.muons    ->size() == 0));
  if(!pass_lepV) return false;
  //
  //  std::cout<<"passed lepV "<<std::endl;

  // //due to unknown efficiency in 2016 data, skip events with: muon pt>500 GeV in the endcap
  // bool good_muon(0);
  // if (channel_ == muon){
  //   const Particle* lep1 = leading_lepton(event);
  //   good_muon = (!(lep1->pt()>muo1_pt_max_ && lep1->eta()>muo1_eta_max_));
  // }
  // if(!good_muon && channel_ == muon) return false;


  // lepton multiplicity
  int lepN(-1);
  if     (channel_ == muon) lepN = int(event.muons    ->size());
  else if(channel_ == elec) lepN = int(event.electrons->size());
  //  if(!(lepN >= 1)) return false;
  if(lepN < 1 || lepN >1) return false;
  //

  // pt-leading lepton selection
  const Particle* lep1 = leading_lepton(event);
  if(!(lep1->pt() > lep1_pt_)) return false; 
  //
  //  std::cout<<"passed lep1_pt "<<std::endl;
  ////

  //// JET selection

  /* 2nd AK4 jet selection */
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  //if(lepN == 1) HFolder("jet2")->fill(event);

  /* 1st AK4 jet selection */
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  if(lepN == 1) HFolder("jet1")->fill(event);

  ////


  // // //TEST: no  MET, HT_lep, TRIANGULAR-CUTS cuts for QCD studies
  /* MET filters */
  if(!metfilters_sel->passes(event)) return false;   
  /**********************************/                                
  //// MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  if(lepN == 1) HFolder("met")->fill(event);


  // //TEST: rho cut
  // if(event.rho<20) return false;

  // TEST: wlep_pt cut
  WlepPt = (event.met->v4()+lep1->v4()).Pt();
  //  if((event.met->v4()+lep1->v4()).Pt()<200.) return false;

  //TEST: lep phi cut
  //  if(fabs((event.electrons->at(0)).phi())<1.8) return false;
  //  if(fabs((event.electrons->at(0)).phi())>1.8) return false;
  
  //TEST: photon EF in the leading jet
  //  if(event.jet->at(0).photonEnergyFraction()>0.5) return false;

  ////

  //// HT_lep selection
  const bool pass_htlep = htlep_sel->passes(event);
  if(!pass_htlep) return false;
  if(lepN == 1) HFolder("htlep")->fill(event);
  ////
  /*
  //// TRIANGULAR-CUTS selection
  const bool pass_triangc = triangc_sel->passes(event);
  if(!pass_triangc) return false;
  HFolder("triangc")->fill(event);
  */
  // // //--------------------------------------------------------------------

  //// TTBAR KIN RECO

  /* TOPTAG-EVENT boolean */
  const bool pass_ttagevt = ttagevt_sel->passes(event) && use_ttagging_;

  const std::string ttag_posx = (pass_ttagevt ? "t1" : "t0");
  /************************/

  reco_primlep->process(event);

  if(!pass_ttagevt){ ttbar_reco__ttag0->process(event); ttbar_chi2__ttag0->process(event); }
  else             { ttbar_reco__ttag1->process(event); ttbar_chi2__ttag1->process(event); }

  std::vector<ReconstructionHypothesis>& ttbar_hyps = event.get(h_ttbar_hyps);

  ////

  //// LEPTONIC-TOP pt selection
  const bool pass_topleppt = topleppt_sel->passes(event);
  if(!pass_topleppt) return false;
  //  std::cout<<"passed  topleppt"<<std::endl;
  if(lepN == 1) HFolder("topleppt")->fill(event);
  ////

  //// FINAL selection

  /* ttagN counters */
  int ttagN(0);
  //  std::cout<<"------ Count N topTAG -------"<<std::endl;
  for(const auto& tj : *event.topjets) if(ttag_ID_(tj, event)) ++ttagN;
  if(ttagN>1) return false; //veto events with 2 and more top-tags
  //  std::cout<<"------ [END] Count N topTAG "<<ttagN<<"-------"<<std::endl;
  //  if(ttagN==1) std::cout<<"HEY!!! Look at this!"<<std::endl;

  //TEST
  top_qjets_volatility = -100; top_tau1 = -100; top_tau2 = -100; top_tau3 = -100;
  top_mvahiggsdiscr = -100; top_prunedmass = -100; top_softdropmass = -100;
  //  if(ttagN>0){
  for(const auto& tj : *event.topjets){
    top_qjets_volatility = tj.qjets_volatility();
    top_tau1 = tj.tau1();
    top_tau2 = tj.tau2();
    top_tau3 = tj.tau3();
    top_mvahiggsdiscr = tj.mvahiggsdiscr();
    top_prunedmass = tj.prunedmass();
    top_softdropmass = tj.softdropmass();
  }
  //  }
  event.set(tt_qjets_volatility,top_qjets_volatility); 
  event.set(tt_tau1,top_tau1); 
  event.set(tt_tau2,top_tau2); 
  event.set(tt_tau3,top_tau3); 
  event.set(tt_mvahiggsdiscr,top_mvahiggsdiscr); 
  event.set(tt_prunedmass,top_prunedmass); 
  event.set(tt_softdropmass,top_softdropmass); 
  

  //TEST for QCD studies
  // veto on 2-ttag events
  //  if(!(ttagN <= 1)) return false;

  /******************/

  /* btagN counters */
  int jetbtagN(0), subjbtagN(0);

  if(!pass_ttagevt){

    for(const auto& j : *event.jets) if(btag_ID_(j, event)) ++jetbtagN;
  }
  else {

    const ReconstructionHypothesis* ttbar_hyp = get_best_hypothesis(ttbar_hyps, "Chi2");

    const TopJet* thad = ttbar_hyp->tophad_topjet_ptr();

    for(const auto& j : thad->subjets()) if(btag_ID_(j, event)) ++subjbtagN;

    for(const auto& j : *event.jets){

      if(!(uhh2::deltaR(*thad, j) > ttag_minDR_jet_)) continue;
      if(btag_ID_(j, event)) ++jetbtagN;
    }
  }

  const int btagN = jetbtagN + subjbtagN;
  //  std::cout<<"btagN = "<<btagN<<std::endl;
  //  const std::string btag_posx = (btagN >= 2 ? "b2" : (btagN >= 1 ? "b1" : "b0"));
  const std::string btag_posx = (btagN >= 1 ? "b1" : "b0");
  
  ////const std::string btag_posx =  ( pass_ttagevt ? "b" :(btagN == 0 ? "b0": "b1"));
  //const std::string btag_posx = (btagN >= 2 ? "b2" : (btagN >= 1 ? "b1" : "b0"));
  /******************/

  /* CHI2 selection */
  const bool pass_chi2 = chi2_sel->passes(event);

  const std::string chi2_posx = pass_chi2 ? "chi2" : "antichi2";
  /******************/

  /* DATA blinding */
  
  //  if(blind_DATA_ && event.isRealData ){
  if(blind_DATA_){

    //    if(lepN == 1 && pass_chi2){
    //    if(lepN == 1){
    if(lepN > 0){

      const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");

      const float rec_ttbar_M((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());

      if(!( rec_ttbar_M < 2000. )) return false;
    }
  }
  
  /*****************/

  /* KINE plots */
  /* if(lepN == 1){

     HFolder("kine")       ->fill(event);
     HFolder("kine__ttbar")->fill(event);

     if(!pass_ttagevt){
     //HFolder("kine__"+ttag_posx+btag_posx)          ->fill(event);
     // HFolder("kine__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
     HFolder("kine__"+ttag_posx)          ->fill(event);
     HFolder("kine__"+ttag_posx+"__ttbar")          ->fill(event);
     }
     else{
     //HFolder("kine__"+ttag_posx+btag_posx)          ->fill(event);
     HFolder("kine__"+ttag_posx)          ->fill(event); 
     HFolder("kine__"+ttag_posx+"__ttbar")->fill(event);
     //HFolder("kine__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
     }
     }*/
  /**************/

  ////

  //// VARS

  // event
  event.set(h_run       , event.run);
  event.set(h_lumi_block, event.luminosityBlock);
  event.set(h_event     , event.event);

  event.set(h_pvN  , event.pvs->size());

  event.set(h_muoN , event.muons    ->size());
  event.set(h_eleN , event.electrons->size());

  event.set(h_btagN, btagN);
  event.set(h_ttagN, ttagN);

  event.set(h_ttagevt, pass_ttagevt);

  int ttgen_decay(-1);
  if(!event.isRealData){

    const auto& ttgen = event.get(h_ttbar_gen);

    if     (ttgen.DecayChannel() == TTbarGen::e_notfound) ttgen_decay = -1;
    else if(ttgen.DecayChannel() == TTbarGen::e_had     ) ttgen_decay = 00;
    else if(ttgen.DecayChannel() == TTbarGen::e_ehad    ) ttgen_decay = 01;
    else if(ttgen.DecayChannel() == TTbarGen::e_muhad   ) ttgen_decay = 02;
    else if(ttgen.DecayChannel() == TTbarGen::e_tauhad  ) ttgen_decay = 03;
    else if(ttgen.DecayChannel() == TTbarGen::e_ee      ) ttgen_decay = 11;
    else if(ttgen.DecayChannel() == TTbarGen::e_emu     ) ttgen_decay = 12;
    else if(ttgen.DecayChannel() == TTbarGen::e_etau    ) ttgen_decay = 13;
    else if(ttgen.DecayChannel() == TTbarGen::e_mumu    ) ttgen_decay = 22;
    else if(ttgen.DecayChannel() == TTbarGen::e_mutau   ) ttgen_decay = 23;
    else if(ttgen.DecayChannel() == TTbarGen::e_tautau  ) ttgen_decay = 33;
  }

  event.set(h_ttgen, ttgen_decay);
  //

  // jet
  if(!(event.jets->size() >= 2)) throw std::runtime_error("TTbarLJAnalysisLiteModule::process -- logic error: jet multiplicity < 2 ("+std::to_string(event.jets->size())+")");

  TLorentzVector jet1__p4(event.jets->at(0).v4().Px(), event.jets->at(0).v4().Py(), event.jets->at(0).v4().Pz(), event.jets->at(0).v4().E());
  TLorentzVector jet2__p4(event.jets->at(1).v4().Px(), event.jets->at(1).v4().Py(), event.jets->at(1).v4().Pz(), event.jets->at(1).v4().E());

  event.set(h_jet1           , jet1__p4);
  event.set(h_jet2           , jet2__p4); 
  const int jet_n = event.jets->size();
  event.set(tt_nJets,jet_n);
  //leading jet
  const Jet* jet1 = &event.jets->at(0);
  ljet_pt = jet1->pt();
  event.set(tt_ljet_pt, ljet_pt);
  ljet_phi = jet1->phi();     ljet_eta = jet1->eta();
  event.set(tt_ljet_phi, ljet_phi);     event.set(tt_ljet_eta, ljet_eta);
  ljet_CSV = jet1->btag_combinedSecondaryVertexMVA();
  event.set(tt_ljet_CSV,ljet_CSV);
  ljet_M = jet1->v4().M();
  event.set(tt_ljet_M, ljet_M);
  NDaughters_jet1 = jet1->numberOfDaughters();

  if(jet_n>1){
    const Jet* jet2 =  &event.jets->at(1);
    fjet2_pt = jet2->pt(); fjet2_eta = jet2->eta(); fjet2_phi = jet2->phi();
    jet2_M = jet2->v4().M();
    jet2_CSV = jet2->btag_combinedSecondaryVertexMVA();
    NDaughters_jet2 = jet2->numberOfDaughters();
    //    std::cout<<"jet2_CSV = "<<jet2_CSV<<std::endl;
  }
  if(jet_n>2){
    const Jet* jet3 =  &event.jets->at(2);                                                                                              
    fjet3_pt = jet3->pt(); fjet3_eta = jet3->eta(); fjet3_phi = jet3->phi(); 
    jet3_M = jet3->v4().M();                        
    jet3_CSV = jet3->btag_combinedSecondaryVertexMVA();        
  }
  event.set(tt_jet2_pt,fjet2_pt); event.set(tt_jet2_phi,fjet2_phi); event.set(tt_jet2_eta,fjet2_eta);
  event.set(tt_jet3_pt,fjet3_pt); event.set(tt_jet3_phi,fjet3_phi); event.set(tt_jet3_eta,fjet3_eta);
  event.set(tt_jet2_M,jet2_M); event.set(tt_jet3_M,jet3_M);
  event.set(tt_jet2_CSV,jet2_CSV);
  //  std::cout<<"one more time ... jet2_CSV = "<<jet2_CSV<<std::endl;
  event.set(tt_jet3_CSV,jet3_CSV);

  //
  event.set(tt_NDaughters_jet1,NDaughters_jet1);
  event.set(tt_NDaughters_jet2,NDaughters_jet2);
  // MET
  event.set(h_MET, TLorentzVector(event.met->v4().Px(), event.met->v4().Py(), event.met->v4().Pz(), event.met->v4().P()));
  met_pt = event.met->pt();
  event.set(tt_met_pt, met_pt); 
  rawmet_pt = event.met->uncorr_v4().Pt();
  event.set(tt_rawmet_pt, rawmet_pt); 
  met_phi = event.met->phi();
  event.set(tt_met_phi, met_phi);
  //
  
  //----------------------------------


  // lepton
  /*const Particle* lep2(0);
    if(lepN == 2){

    if     (channel_ == muon) lep2 = &((lep1 == &event.muons    ->at(0)) ? event.muons    ->at(1) : event.muons    ->at(0));
    else if(channel_ == elec) lep2 = &((lep1 == &event.electrons->at(0)) ? event.electrons->at(1) : event.electrons->at(0));
    }
  */

  


  TLorentzVector lep1__p4(0.,0.,0.,0.);
  // lep2__p4(0.,0.,0.,0.);
  int   lep1__pdgID(0), lep1__charge(0); 
  //lep2__pdgID(0), lep2__charge(0);
  float lep1__minDR_jet(-1.), lep1__pTrel_jet(-1.);
  // lep2__minDR_jet(-1.), lep2__pTrel_jet(-1.);
  if(channel_ == muon){

    lep1__pdgID     = lep1->charge() * -13;
    lep1__charge    = lep1->charge();
    lep1__minDR_jet = ((Muon*) lep1)->get_tag(Muon::twodcut_dRmin);
    lep1__pTrel_jet = ((Muon*) lep1)->get_tag(Muon::twodcut_pTrel);
    lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());

    /*  if(lep2){

	lep2__pdgID     = lep2->charge() * -13;
	lep2__charge    = lep2->charge();
	lep2__minDR_jet = ((Muon*) lep2)->get_tag(Muon::twodcut_dRmin);
	lep2__pTrel_jet = ((Muon*) lep2)->get_tag(Muon::twodcut_pTrel);
	lep2__p4        = TLorentzVector(lep2->v4().Px(), lep2->v4().Py(), lep2->v4().Pz(), lep2->v4().E());
	}
    */ 
  }
  else if(channel_ == elec){

    lep1__pdgID     = lep1->charge() * -11;
    lep1__charge    = lep1->charge();
    lep1__minDR_jet = ((Electron*) lep1)->get_tag(Electron::twodcut_dRmin);
    lep1__pTrel_jet = ((Electron*) lep1)->get_tag(Electron::twodcut_pTrel);
    lep1__p4        = TLorentzVector(lep1->v4().Px(), lep1->v4().Py(), lep1->v4().Pz(), lep1->v4().E());

    /* if(lep2){

       lep2__pdgID     = lep2->charge() * -11;
       lep2__charge    = lep2->charge();
       lep2__minDR_jet = ((Electron*) lep2)->get_tag(Electron::twodcut_dRmin);
       lep2__pTrel_jet = ((Electron*) lep2)->get_tag(Electron::twodcut_pTrel);
       lep2__p4        = TLorentzVector(lep2->v4().Px(), lep2->v4().Py(), lep2->v4().Pz(), lep2->v4().E());
       }
    */

    //Set variables for MVA ------------
    lep_class = ((Electron*)lep1)->Class();
    lep_pt = lep1->pt(); lep_eta = lep1->eta(); fabs_lep_eta = fabs(lep_eta); lep_phi = lep1->phi(); lep_eta_SC = ((Electron*)lep1)->supercluster_eta();
    lep_pt_err = ((Electron*)lep1)->ptError(); lep_eta_err = ((Electron*)lep1)->etaError(); lep_phi_err = ((Electron*)lep1)->phiError();
    lep_xy = hypot(((Electron*)lep1)->gsfTrack_vx(),((Electron*)lep1)->gsfTrack_vy());
    lep_fbrem = ((Electron*)lep1)->fbrem();//f_brem = (Pin-Pout)/Pin where Pin, Pout - electron momentum in and out of the tracker

    lep_Nclusters = ((Electron*)lep1)->Nclusters();
    lep_full5x5_e1x5 = ((Electron*)lep1)->full5x5_e1x5();
    lep_full5x5_e2x5Max = ((Electron*)lep1)->full5x5_e2x5Max();
    lep_full5x5_e5x5 = ((Electron*)lep1)->full5x5_e5x5();
    lep_dEtaInSeed = ((Electron*)lep1)->dEtaInSeed();
    lep_dB = ((Electron*)lep1)->dB(); 
    lep_sigmaIEtaIEta = ((Electron*)lep1)->sigmaIEtaIEta(); 
    lep_HoverE = ((Electron*)lep1)->HoverE(); 
    lep_EoverPIn = ((Electron*)lep1)->EoverPIn(); 
    lep_hcalOverEcal = ((Electron*)lep1)->hcalOverEcal(); 
    lep_dr03TkSumPt = ((Electron*)lep1)->dr03TkSumPt(); 
    lep_effArea = ((Electron*)lep1)->effArea(); 
    //    lep_mvaNonTrigV0 = ((Electron*)lep1)->mvaNonTrigV0();
    lep_dEtaIn = ((Electron*)lep1)->dEtaIn();
    lep_dPhiIn = ((Electron*)lep1)->dPhiIn();

    //the closest to lepton jet
    // find jet with smallest angle to lepton (the closest jet to lepton)
    int jet_pos = 0;
    dR_lep_cljet = 1e7;
    jets_pt = (&event.jets->at(0))->pt();
    for(int i=1; i<jet_n; i++){//skip leading jet
      const Particle* jeti =  &event.jets->at(i);
      jets_pt += jeti->pt();
      float dR_current = uhh2::deltaR(*lep1, *jeti);
      if(dR_lep_cljet>dR_current){// min distance in eta-phi
	dR_lep_cljet = dR_current;      
	jet_pos = i;
      }
    }
   
    const Jet*  jet0 =  &event.jets->at(jet_pos); 
    cjet_pt = jet0->pt();
    cjet_phi = jet0->phi(); cjet_eta = jet0->eta();
    dR_lep_ljet = uhh2::deltaR(*lep1, *jet1);
    lep_pt_ljet = pTrel(*lep1, jet1);
    dR_cljet_ljet = uhh2::deltaR(*jet0, *jet1);
    dPhi_lep_met = uhh2::deltaPhi(*event.met, *lep1);
    MwT = sqrt(2*fabs(lep_pt*met_pt*(1-cos(fabs(dPhi_lep_met)))));
    dPhi_ljet_met = uhh2::deltaPhi(*event.met,*jet1);
    dPhi_cjet_met = uhh2::deltaPhi(*event.met,*jet0);
    lep_pt_cjet = pTrel(*lep1, jet0);
    cjet_pt_ljet = pTrel(*jet0, jet1);// the closest not leading jet Pt to the leading jet axis
    cjet_M = jet0->v4().M();
    cjet_CSV = jet0->btag_combinedSecondaryVertexMVA();        

    //invariant mass
    const Jet*  jet1 =  &event.jets->at(1); 
    LorentzVector P12 = jet0->v4()+jet1->v4();
    M12jet = P12.M();
    if(jet_n>2){
      const Jet*  jet2 =  &event.jets->at(2); 
      LorentzVector P123 = P12+jet2->v4();
      M123jet = P123.M();
    }
  }
 
  event.set(tt_lep_class, lep_class);
  event.set(tt_lep_pt, lep_pt);   event.set(tt_lep_eta, lep_eta); event.set(tt_lep_phi, lep_phi); event.set(tt_lep_eta_SC, lep_eta_SC);
  event.set(tt_lep_pt_err, lep_pt_err); event.set(tt_lep_eta_err, lep_eta_err); event.set(tt_lep_phi_err, lep_phi_err);
  event.set(tt_lep_xy,lep_xy);
  event.set(tt_lep_fbrem,lep_fbrem);
  event.set(tt_Nclusters,lep_Nclusters);   
  event.set(tt_full5x5_e1x5,lep_full5x5_e1x5);
  event.set(tt_full5x5_e2x5Max,lep_full5x5_e2x5Max);
  event.set(tt_full5x5_e5x5,lep_full5x5_e5x5);
  event.set(tt_dEtaInSeed,lep_dEtaInSeed);
  event.set(tt_dB, lep_dB);
  event.set(tt_sigmaIEtaIEta,lep_sigmaIEtaIEta);
  event.set(tt_HoverE, lep_HoverE);
  event.set(tt_EoverPIn, lep_EoverPIn);
  event.set(tt_hcalOverEcal, lep_hcalOverEcal);
  event.set(tt_dr03TkSumPt, lep_dr03TkSumPt);
  event.set(tt_effArea, lep_effArea);
  //  event.set(tt_mvaNonTrigV0, lep_mvaNonTrigV0);
  event.set(tt_dEtaIn, lep_dEtaIn);
  event.set(tt_dPhiIn, lep_dPhiIn);

  event.set(tt_dR_lep_cljet, dR_lep_cljet); 
  event.set(tt_jets_pt,jets_pt);
  event.set(tt_cjet_pt,cjet_pt);
  event.set(tt_cjet_phi,cjet_phi); event.set(tt_cjet_eta,cjet_eta);
  event.set(tt_dR_lep_ljet, dR_lep_ljet); 
  event.set(tt_lep_pt_ljet, lep_pt_ljet);
  event.set(tt_dR_cljet_ljet, dR_cljet_ljet);
  event.set(tt_MwT,MwT);
  event.set(tt_WlepPt,WlepPt);
  event.set(tt_dPhi_lep_met,dPhi_lep_met);
  event.set(tt_dPhi_ljet_met,dPhi_ljet_met);
  event.set(tt_dPhi_cjet_met,dPhi_cjet_met);
  event.set(tt_cjet_pt_ljet,cjet_pt_ljet);
  event.set(tt_lep_pt_cjet,lep_pt_cjet);
  event.set(tt_cjet_M, cjet_M);
  event.set(tt_cjet_CSV,cjet_CSV);
  event.set(tt_M12jet,M12jet);
  event.set(tt_M123jet,M123jet);
  // std::cout<<"M12 = "<<M12jet<<" M123jet = "<<M123jet<<std::endl;

  event.set(h_lep1           , lep1__p4);
  event.set(h_lep1__pdgID    , lep1__pdgID);
  event.set(h_lep1__charge   , lep1__charge);
  event.set(h_lep1__minDR_jet, lep1__minDR_jet);
  event.set(h_lep1__pTrel_jet, lep1__pTrel_jet);

  // event.set(h_lep2           , lep2__p4);
  // event.set(h_lep2__pdgID    , lep2__pdgID);
  // event.set(h_lep2__charge   , lep2__charge);
  // event.set(h_lep2__minDR_jet, lep2__minDR_jet);
  // event.set(h_lep2__pTrel_jet, lep2__pTrel_jet);
  //

  

  // ttbar reco hyp
  const ReconstructionHypothesis* rec_ttbar = get_best_hypothesis(ttbar_hyps, "Chi2");
  if(!rec_ttbar) throw std::runtime_error("TTbarLJAnalysisLiteModule::process -- logic error: ttbar reconstruction hypothesis (\"get_best_hypothesis\", discr=Chi2) not found");
  const float MET__pz = rec_ttbar->neutrino_v4().Pz();
  event.set(h_MET__pz, MET__pz);

  const float rec_chi2 = rec_ttbar->discriminator("Chi2");
  event.set(h_rec_chi2,rec_chi2);
  const LorentzVector tlep(rec_ttbar->toplep_v4());
  const LorentzVector thad(rec_ttbar->tophad_v4());

  event.set(h_rec_tlep, TLorentzVector(tlep.Px(), tlep.Py(), tlep.Pz(), tlep.E()));
  event.set(h_rec_thad, TLorentzVector(thad.Px(), thad.Py(), thad.Pz(), thad.E()));
  //

  // weight
  event.set(h_wgtMC__GEN         , w_GEN);

  // event.set(h_wgtMC__elecIDSF_ct , w_elecIDSF_ct);
  // event.set(h_wgtMC__elecIDSF_up , w_elecIDSF_up);
  // event.set(h_wgtMC__elecIDSF_dn , w_elecIDSF_dn);

   // event.set(h_wgtMC__elecHLTSF_ct, w_elecHLTSF_ct);
   // event.set(h_wgtMC__elecHLTSF_up, w_elecHLTSF_up);
   // event.set(h_wgtMC__elecHLTSF_dn, w_elecHLTSF_dn);

  //ttag SFs
  event.set(h_wgtMC__ttagSF_ct  , w_ttagSF_ct );
  event.set(h_wgtMC__ttagSF_upL , w_ttagSF_upL);
  event.set(h_wgtMC__ttagSF_dnL , w_ttagSF_dnL);
  event.set(h_wgtMC__ttagSF_upT , w_ttagSF_upT);
  event.set(h_wgtMC__ttagSF_dnT , w_ttagSF_dnT);

  event.set(h_wgtMC__muR_ct__muF_up, w_muR_ct__muF_up);
  event.set(h_wgtMC__muR_ct__muF_dn, w_muR_ct__muF_dn);
  event.set(h_wgtMC__muR_up__muF_ct, w_muR_up__muF_ct);
  event.set(h_wgtMC__muR_up__muF_up, w_muR_up__muF_up);
  event.set(h_wgtMC__muR_dn__muF_ct, w_muR_dn__muF_ct);
  event.set(h_wgtMC__muR_dn__muF_dn, w_muR_dn__muF_dn);

  double w__muRmuF_min, w__muRmuF_max;
  w__muRmuF_min = w_muR_ct__muF_up;
  w__muRmuF_max = w_muR_ct__muF_up;
  if(w_muR_ct__muF_dn<w__muRmuF_min) w__muRmuF_min = w_muR_ct__muF_dn;
  if(w_muR_ct__muF_dn>w__muRmuF_max) w__muRmuF_max = w_muR_ct__muF_dn;
  if(w_muR_up__muF_ct<w__muRmuF_min) w__muRmuF_min = w_muR_up__muF_ct;
  if(w_muR_up__muF_ct>w__muRmuF_max) w__muRmuF_max = w_muR_up__muF_ct;
  if(w_muR_up__muF_up<w__muRmuF_min) w__muRmuF_min = w_muR_up__muF_up;
  if(w_muR_up__muF_up>w__muRmuF_max) w__muRmuF_max = w_muR_up__muF_up;
  if(w_muR_dn__muF_ct<w__muRmuF_min) w__muRmuF_min = w_muR_dn__muF_ct;
  if(w_muR_dn__muF_ct>w__muRmuF_max) w__muRmuF_max = w_muR_dn__muF_ct;
  if(w_muR_dn__muF_dn<w__muRmuF_min) w__muRmuF_min = w_muR_dn__muF_dn;
  if(w_muR_dn__muF_dn>w__muRmuF_max) w__muRmuF_max = w_muR_dn__muF_dn;

  event.set(h_wgtMC__muRmuF_min, w__muRmuF_min);
  event.set(h_wgtMC__muRmuF_max, w__muRmuF_max);

  //std::cout<<"w__muRmuF_min = "<<w__muRmuF_min<<" w__muRmuF_max = "<<w__muRmuF_max<<std::endl;

  // if(!topptREWGT.get())
  //   event.set(h_wgtMC__topptREWGT_ct , 1.);

  // event.set(h_wgtMC__topptREWGT_up , w_topptREWGT_up);
  // event.set(h_wgtMC__topptREWGT_dn , w_topptREWGT_dn);

  // event.set(h_wgtMC__wjetsREWGT_ct , w_wjetsREWGT_ct);

  event.set(h_wgtMC__PDF, std::move(w_PDF));
  //

  ////

  const ReconstructionHypothesis* rec_ttbar_ = get_best_hypothesis(ttbar_hyps, "Chi2");
  rec_ttbar_M_ = ((rec_ttbar_->top_v4()+rec_ttbar_->antitop_v4()).M());

  event.set(tt_mttbar,rec_ttbar_M_);
  const LorentzVector& rec_lep = rec_ttbar_->lepton().v4();
  const LorentzVector& rec_neu = rec_ttbar_->neutrino_v4();
  dPhi_reclep_recneu = delta_phi(rec_lep .Phi(), rec_neu.Phi());
  event.set(tt_dPhi_reclep_recneu,dPhi_reclep_recneu);
  dR_reclep_recneu = uhh2::deltaR(rec_lep , rec_neu);
  event.set(tt_dR_reclep_recneu,dR_reclep_recneu);
  const LorentzVector& rec_blep = (rec_ttbar_->toplep_v4()-rec_ttbar_->wlep_v4());
  dPhi_recblep_recneu  = delta_phi(rec_blep.Phi(), rec_neu.Phi());
  event.set(tt_dPhi_recblep_recneu,dPhi_recblep_recneu);
  dR_recblep_recneu  = uhh2::deltaR(rec_blep, rec_neu);
  event.set(tt_dR_recblep_recneu,dR_recblep_recneu);


  if(channel_ == elec){
    varMVA[0] = lep_pt/rec_ttbar_M_;
    varMVA[1] = fabs(lep_eta);
    varMVA[2] = log(lep1__minDR_jet);
    varMVA[3] = log(lep1__pTrel_jet/rec_ttbar_M_);
    varMVA[4] = fabs(ljet_eta);
    varMVA[5] = fabs(fjet2_eta);
    varMVA[6] = ttagN;
    varMVA[7] = btagN;
    varMVA[8] = log((jets_pt-ljet_pt)/rec_ttbar_M_);
    varMVA[9] = log(rec_chi2);
    varMVA[10] = dR_recblep_recneu;
    varMVA[11] = dR_reclep_recneu;

    // if(ljet_CSV<-1. || lep_pt_err>1000.) 
    //    return false; // do NOT use unphysical data
    TMVA_response = reader->EvaluateMVA(methodName);
    //  TMVA_response = -1;//TEST
    //      if(TMVA_response<QCD_BDT_cut) return false; //TEST BDTG_DATADriven 21.11.2016
    //  if(TMVA_response<0.76) return false; //BDTG_DATADriven_MET40_20vars
    event.set(tt_TMVA_response, TMVA_response);
    //  std::cout<<"TMVA_response = "<<TMVA_response<<std::endl;
    if(TMVA_response<0) return false;
  }
  // if(!pass_chi2) 
  //   return false;

  //if(TMVA_response<0) return false;


  event.set(tt_ev_weight,event.weight);
  if(!event.isRealData){
    const TTbarGen* ttbargen(0);
    const auto& ttgen = event.get(h_ttbar_gen);
    ttbargen = &ttgen;
    LorentzVector gen_ttbar = ttbargen->Top().v4()+ttbargen->Antitop().v4();
    gen_ttbar_M_ = gen_ttbar.M();
  }
  event.set(tt_mttbar_gen,gen_ttbar_M_);

  //FILL HERE THE BDT WJETS VARIABLES
  float s11 = 0.0;
  float s12 = 0.0;
  float s13 = 0.0;
  float s22 = 0.0;
  float s23 = 0.0;
  float s33 = 0.0;
  float s11d = 0.0;
  float s12d = 0.0;
  float s13d = 0.0;
  float s22d = 0.0;
  float s23d = 0.0;
  float s33d =0.0;
  float mag = 0.0;
  float ht=0.0;
  for (auto jet : *event.jets){
    if (jet.pt()>30.0){
      ht+=jet.pt();
      s11d += jet.v4().Px()*jet.v4().Px();
      mag  += (jet.v4().Px()*jet.v4().Px()+jet.v4().Py()*jet.v4().Py()+jet.v4().Pz()*jet.v4().Pz());
      s22d += jet.v4().Py()*jet.v4().Py();
      s12d += jet.v4().Px()*jet.v4().Py();
      s13d += jet.v4().Px()*jet.v4().Pz();
      s23d += jet.v4().Py()*jet.v4().Pz();
      s33d += jet.v4().Pz()*jet.v4().Pz();
    }
  }
  s11 =  s11d/mag;
  s12 =  s12d/mag;
  s13 =  s13d/mag;
  s22 =  s22d/mag;
  s23 =  s23d/mag;
  s33 =  s33d/mag;
  const float j1CSV    = event.jets->at(0).btag_combinedSecondaryVertex();
  const float j2CSV    = event.jets->at(1).btag_combinedSecondaryVertex();
  const float njets    = event.jets->size();
  const float j1M      = jet1__p4.M();
  const float j2M      = jet2__p4.M();
    
  const float jet1pt_norm = jet1__p4.Pt()/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
  const float jet2pt_norm = jet2__p4.Pt()/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
  const float ptrel_norm =  lep1__pTrel_jet/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
  const float htmetlep_norm = (ht+met_pt+lep1__p4.Pt())/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
  const float DRpt_norm = lep1__minDR_jet*jet1__p4.Pt()/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
  /*  
      event.set(h_DRpt, DRpt_norm);//1
      event.set(h_ht_met_lep_norm, htmetlep_norm);//2
      event.set(h_lep1__minDR_norm, lep1__minDR_jet);//3
      event.set(h_lep1__pTrel_jet_norm, ptrel_norm);//4
      event.set(h_jet1_pt,jet1pt_norm);//5
      event.set(h_jet2_pt,jet2pt_norm);//6
      event.set(h_njets, njets); //9
      event.set(h_jet1_m,  j1M/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M())); //10
      event.set(h_jet2_m,  j2M/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M())); //11
  */
# define N 3
  double d[N];
  double sph_mat[N*N] = {
    s11, s12, s13,
    s12, s22, s23,
    s13, s23, s33
  };
  double v[N*N];
  int n = 3;
  int it_max = 100;
  jacobi_eigenvalue( n, sph_mat, it_max, v, d, it_num, rot_num);
  const float sphericity = 1.5*(d[1]+d[2]);
  const float aplanarity = 1.5*d[0];
    
  mva_jet1pt_norm = jet1pt_norm;
  mva_jet2pt_norm = jet2pt_norm;
  mva_ptrel_norm =  ptrel_norm;
  mva_ht_met_lep_norm = htmetlep_norm;
  mva_jet1m_norm = j1M/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
  mva_jet2m_norm = j2M/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M());
  mva_DRpt_norm = DRpt_norm;
  mva_lep1__minDR_jet = lep1__minDR_jet;
  mva_j1CSV = j1CSV;
  mva_j2CSV = j2CSV;
  mva_njets = njets;
  mva_WptResponse = WlepPt/ljet_pt;
  mva_s11 = s11;
  mva_s12 = s12;
  mva_s13 = s13;
  mva_s22 = s22;
  mva_s23 = s23;
  mva_s33 = s33;
  mva_aplanarity= aplanarity;
  mva_sphericity = sphericity;
  WJets_TMVA_response = reader_wjets->EvaluateMVA("BDT method");
  
  event.set(wjets_TMVA_response, WJets_TMVA_response);
  //  std::cout<<" WJets_TMVA_response = "<< WJets_TMVA_response<<std::endl;
  event.set(H_Rec_chi2, rec_chi2);
  //  std::cout<<" rec_chi2 = "<< rec_chi2<<std::endl;
  event.set(h_DRpt, DRpt_norm);//1
  //  std::cout<<" DRpt_norm = "<< DRpt_norm<<std::endl;
  event.set(h_ht_met_lep_norm, htmetlep_norm);//2
  
  event.set(h_lep1__minDR_norm, lep1__minDR_jet);//3
  event.set(h_lep1__pTrel_jet_norm, ptrel_norm);//4
  //event.set(h_jet1_pt,jet1pt_norm);//5
  // event.set(h_jet2_pt,jet2pt_norm);//6
  event.set(h_jet1_csv, j1CSV );//7
  event.set(h_jet2_csv, j2CSV );//8
  event.set(h_njets, njets); //9
  event.set(h_jet1_m,  j1M/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M())); //10
  event.set(h_jet2_m,  j2M/((rec_ttbar->top_v4()+rec_ttbar->antitop_v4()).M())); //11
  event.set(h_s33, s33);
  

  // if (!pass_chi2 && lepN==1 && WJets_TMVA_response <0.5){
  //   HFolder("antichi2_antibdt")          ->fill(event);
  //   HFolder("antichi2_antibdt__ttbar")->fill(event);
  //   HFolder("antichi2_antibdt__"+ttag_posx)          ->fill(event);
  //   HFolder("antichi2_antibdt__"+ttag_posx+"__ttbar")->fill(event);
  //   //HFolder("antichi2_antibdt__"+ttag_posx+btag_posx)          ->fill(event);
  //   //HFolder("antichi2_antibdt__"+ttag_posx+btag_posx+"__ttbar")->fill(event);   
  // }

  HFolder("Final")->fill(event);
  HFolder("Final__ttbar")->fill(event);
  HFolder("Final__"+ttag_posx)          ->fill(event);
  HFolder("Final__"+ttag_posx+"__ttbar")->fill(event);
  // if(pass_ttagevt){
  //   std::cout<<"Fill hist in Final!"<<std::endl;
  // }
  // if(!pass_ttagevt){
  //   HFolder("Final__"+ttag_posx+btag_posx)          ->fill(event);
  //   HFolder("Final__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
  // }
  // else{
  //   HFolder("Final__"+ttag_posx)          ->fill(event);
  //   HFolder("Final__"+ttag_posx+"__ttbar")->fill(event);
  // }
  //  std::cout<<" pass_ttagevt = "<<pass_ttagevt<<" ttag_posx = "<<ttag_posx<<std::endl;
  //  std::cout<<"weight = "<<event.weight<<std::endl;
  //  std::cout<<"elecID = "<<event.weight_sfelec_ID<<std::endl;
  //  std::cout<<"End of the event "<<std::endl;
  //(weight_sfelec_ID)*(wgtMC__elecHLTSF_ct)*(weight_pu)*(weight_btag)*(wgtMC__ttagSF_ct)*(weight_sfelec_Gsf)
  lumihists->fill(event);





  /* CHI2 plots */
  if(lepN == 1){

    HFolder(chi2_posx)          ->fill(event);
    HFolder(chi2_posx+"__ttbar")->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx)          ->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx+"__ttbar")->fill(event);
    HFolder(chi2_posx+"__"+btag_posx)          ->fill(event);
    HFolder(chi2_posx+"__"+btag_posx+"__ttbar")->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx+"__"+btag_posx)          ->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx+"__"+btag_posx+"__ttbar")->fill(event);
   

    // if(!pass_ttagevt){
    //   HFolder(chi2_posx+"__"+ttag_posx+btag_posx)          ->fill(event);
    //   HFolder(chi2_posx+"__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
    // }
    // else{
    //   HFolder(chi2_posx+"__"+ttag_posx)          ->fill(event);
    //   HFolder(chi2_posx+"__"+ttag_posx+"__ttbar")->fill(event);
    // }
    //    if(pass_chi2 && !event.isRealData){
    // if(!event.isRealData){//TEST
    //   h_btagMCeffi->fill(event);
    // }

    //WJets
    bool pass_WJetsMVA = false;
    if(WJets_TMVA_response>=0.5) pass_WJetsMVA=true;
    const std::string wjetsMVA_posx = pass_WJetsMVA ? "WJetsBDT" : "antiWJetsBDT";
    HFolder(chi2_posx+"__"+ttag_posx+"__"+wjetsMVA_posx)          ->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx+"__"+wjetsMVA_posx+"__ttbar")          ->fill(event);
    HFolder(chi2_posx+"__"+wjetsMVA_posx)->fill(event);
    HFolder(chi2_posx+"__"+wjetsMVA_posx+"__ttbar")->fill(event);

    if(WJets_TMVA_response<-0.75){
    HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT2")          ->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT2__ttbar")          ->fill(event);
    HFolder(chi2_posx+"__WJetsBDT2")->fill(event);
    HFolder(chi2_posx+"__WJetsBDT2__ttbar")->fill(event);
    }

    if(WJets_TMVA_response>0.0 && WJets_TMVA_response<0.5){
    HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT3")          ->fill(event);
    HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT3__ttbar")          ->fill(event);
    HFolder(chi2_posx+"__WJetsBDT3")->fill(event);
    HFolder(chi2_posx+"__WJetsBDT3__ttbar")->fill(event);
    }

    // if(WJets_TMVA_response>-1.0 && WJets_TMVA_response<-0.75){
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step1")          ->fill(event);
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step1__ttbar")          ->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step1")->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step1__ttbar")->fill(event);
    // }

    // if(WJets_TMVA_response>-0.75 && WJets_TMVA_response<-0.50){
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step2")          ->fill(event);
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step2__ttbar")          ->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step2")->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step2__ttbar")->fill(event);
    // }
    // if(WJets_TMVA_response>-0.5 && WJets_TMVA_response<-0.25){
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step3")          ->fill(event);
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step3__ttbar")          ->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step3")->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step3__ttbar")->fill(event);
    // }
    // if(WJets_TMVA_response>-0.25 && WJets_TMVA_response<0.00){
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step4")          ->fill(event);
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step4__ttbar")          ->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step4")->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step4__ttbar")->fill(event);
    // }
    // if(WJets_TMVA_response>0.00 && WJets_TMVA_response<0.25){
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step5")          ->fill(event);
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step5__ttbar")          ->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step5")->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step5__ttbar")->fill(event);
    // }
    // if(WJets_TMVA_response>0.25 && WJets_TMVA_response<0.50){
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step6")          ->fill(event);
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step6__ttbar")          ->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step6")->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step6__ttbar")->fill(event);
    // }
    // if(WJets_TMVA_response>0.50 && WJets_TMVA_response<0.75){
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step7")          ->fill(event);
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step7__ttbar")          ->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step7")->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step7__ttbar")->fill(event);
    // }
    // if(WJets_TMVA_response>0.75 && WJets_TMVA_response<1.00){
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step8")          ->fill(event);
    // HFolder(chi2_posx+"__"+ttag_posx+"__WJetsBDT_step8__ttbar")          ->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step8")->fill(event);
    // HFolder(chi2_posx+"__WJetsBDT_step8__ttbar")->fill(event);
    // }


  }
  /*  else if(lepN == 2){

      bool l2_ossf(false);
      if     (channel_ == muon) l2_ossf = ((event.muons    ->at(0).charge() * event.muons    ->at(1).charge()) == -1);
      else if(channel_ == elec) l2_ossf = ((event.electrons->at(0).charge() * event.electrons->at(1).charge()) == -1);

      if(l2_ossf && chi2_posx == "chi2"){

      HFolder(chi2_posx+"_L2")          ->fill(event);
      HFolder(chi2_posx+"_L2"+"__dilep")->fill(event);
      HFolder(chi2_posx+"_L2"+"__ttbar")->fill(event);
      if(!pass_ttagevt){
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx)          ->fill(event);
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx+"__dilep")->fill(event);
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+btag_posx+"__ttbar")->fill(event);
      }
      else{
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx)          ->fill(event);
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+"__dilep")->fill(event);
      HFolder(chi2_posx+"_L2"+"__"+ttag_posx+"__ttbar")->fill(event);
      }
      }
      } */
  /**************/
  // if(event.met->pt()>500) 
  //  std::cout<<"#### N_ele = "<<event.electrons->size()<<" N_muo = "<<event.muons->size()<<" N_jets = "<<event.jets->size()<<" N_topjets = "<<event.topjets->size()<<" met = "<<event.met->pt()<<" raw MET = "<<event.met->uncorr_v4().Pt()<<" event weight = "<<event.weight<<std::endl;
  //  std::cout<<"-- End of Event --"<<std::endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(TTbarLJAnalysisLiteModule)
