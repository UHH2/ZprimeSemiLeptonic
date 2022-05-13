#include <iostream>
#include <memory>

#include <UHH2/core/include/AnalysisModule.h>
#include <UHH2/core/include/Event.h>
#include <UHH2/core/include/Selection.h>
#include "UHH2/common/include/PrintingModules.h"

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
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>
#include "UHH2/common/include/LuminosityHists.h"
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/EventHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicPreselectionHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>

using namespace std;

class ZprimePreselectionModule_DNN : public ModuleBASE {

public:
  explicit ZprimePreselectionModule_DNN(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  //void book_histograms(uhh2::Context&, vector<string>);
  //void fill_histograms(uhh2::Event&, string);
  void init_JEC_JLC(uhh2::Context& ctx);

protected:

  // NN vars
  Event::Handle<float> h_MET;
  Event::Handle<float> h_weight;
  Event::Handle<float> h_ST;
  Event::Handle<float> h_STjets;
  Event::Handle<float> h_STlep;
  Event::Handle<float> h_NPV;
  Event::Handle<float> h_N_jets;
  Event::Handle<float> h_pt_jet;
  Event::Handle<float> h_pt_jet1;
  Event::Handle<float> h_pt_jet2;
  Event::Handle<float> h_pt_jet3;
  Event::Handle<float> h_eta_jet;
  Event::Handle<float> h_eta_jet1;
  Event::Handle<float> h_eta_jet2;
  Event::Handle<float> h_eta_jet3;
  Event::Handle<float> h_phi_jet;
  Event::Handle<float> h_phi_jet1;
  Event::Handle<float> h_phi_jet2;
  Event::Handle<float> h_phi_jet3;
  Event::Handle<float> h_mass_jet;
  Event::Handle<float> h_mass_jet1;
  Event::Handle<float> h_mass_jet2;
  Event::Handle<float> h_mass_jet3;
  Event::Handle<float> h_csv_jet;
  Event::Handle<float> h_csv_jet1;
  Event::Handle<float> h_csv_jet2;
  Event::Handle<float> h_csv_jet3;
  Event::Handle<float> h_S11;
  Event::Handle<float> h_S12;
  Event::Handle<float> h_S13;
  Event::Handle<float> h_S22;
  Event::Handle<float> h_S23;
  Event::Handle<float> h_S33;
  Event::Handle<float> h_N_mu;
  Event::Handle<float> h_pt_mu;
  Event::Handle<float> h_ptrel_mu_jet;
  Event::Handle<float> h_eta_mu;
  Event::Handle<float> h_phi_mu;
  Event::Handle<float> h_reliso_mu;
  Event::Handle<float> h_N_ele;
  Event::Handle<float> h_pt_ele;
  Event::Handle<float> h_ptrel_ele_jet;
  Event::Handle<float> h_eta_ele;
  Event::Handle<float> h_phi_ele;
  Event::Handle<float> h_reliso_ele;
  Event::Handle<float> h_N_Ak8Puppijets;
  Event::Handle<float> h_pt_Ak8Puppijets;
  Event::Handle<float> h_pt_Ak8Puppijet1;
  Event::Handle<float> h_pt_Ak8Puppijet2;
  Event::Handle<float> h_pt_Ak8Puppijet3;
  Event::Handle<float> h_eta_Ak8Puppijets;
  Event::Handle<float> h_eta_Ak8Puppijet1;
  Event::Handle<float> h_eta_Ak8Puppijet2;
  Event::Handle<float> h_eta_Ak8Puppijet3;
  Event::Handle<float> h_phi_Ak8Puppijets;
  Event::Handle<float> h_phi_Ak8Puppijet1;
  Event::Handle<float> h_phi_Ak8Puppijet2;
  Event::Handle<float> h_phi_Ak8Puppijet3;
  Event::Handle<float> h_mSD_Ak8Puppijets;
  Event::Handle<float> h_mSD_Ak8Puppijet1;
  Event::Handle<float> h_mSD_Ak8Puppijet2;
  Event::Handle<float> h_mSD_Ak8Puppijet3;
  Event::Handle<float> h_dR_mu_jet;
  Event::Handle<float> h_dRmin_mu_jet;
  Event::Handle<float> h_dR_mu_Ak8Puppijet;
  Event::Handle<float> h_dR_ele_jet;
  Event::Handle<float> h_dRmin_ele_jet;
  Event::Handle<float> h_dR_ele_Ak8Puppijet;
  Event::Handle<float> h_dR_jet_Ak8Puppijet;


  // Corrections
  std::unique_ptr<JetCorrector>                    jet_corrector_A,jet_corrector_B, jet_corrector_C, jet_corrector_D, jet_corrector_E, jet_corrector_F, 
    jet_corrector_G,jet_corrector_H, jet_corrector_MC;
  std::unique_ptr<TopJetCorrector>                 topjet_corrector_A,topjet_corrector_B, topjet_corrector_C, topjet_corrector_D,topjet_corrector_E, topjet_corrector_F, 
    topjet_corrector_G,  topjet_corrector_H, topjet_corrector_MC;
  std::unique_ptr<GenericTopJetCorrector>          topjet_puppi_corrector_A, topjet_puppi_corrector_B, topjet_puppi_corrector_C, topjet_puppi_corrector_D,
    topjet_puppi_corrector_E, topjet_puppi_corrector_F, topjet_puppi_corrector_G, topjet_puppi_corrector_H, topjet_puppi_corrector_MC;
  std::unique_ptr<SubJetCorrector>                 topjet_subjet_corrector_A, topjet_subjet_corrector_B, topjet_subjet_corrector_C, topjet_subjet_corrector_D,
    topjet_subjet_corrector_E, topjet_subjet_corrector_F, topjet_subjet_corrector_G, topjet_subjet_corrector_H, topjet_subjet_corrector_MC;
  std::unique_ptr<GenericSubJetCorrector>          topjet_puppi_subjet_corrector_A, topjet_puppi_subjet_corrector_B, topjet_puppi_subjet_corrector_C, 
    topjet_puppi_subjet_corrector_D, topjet_puppi_subjet_corrector_E, topjet_puppi_subjet_corrector_F, topjet_puppi_subjet_corrector_G, 
    topjet_puppi_subjet_corrector_H, topjet_puppi_subjet_corrector_MC;

  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> JLC_A, JLC_B, JLC_C, JLC_D,JLC_E, JLC_F, JLC_G, JLC_H, JLC_MC;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> TopJLC_A, TopJLC_B, TopJLC_C, TopJLC_D, TopJLC_E, TopJLC_F, TopJLC_G, TopJLC_H, TopJLC_MC;
  std::unique_ptr<JetLeptonCleaner_by_KEYmatching> TopJLC_puppi_A, TopJLC_puppi_B, TopJLC_puppi_C, TopJLC_puppi_D,TopJLC_puppi_E, TopJLC_puppi_F,
    TopJLC_puppi_G, TopJLC_puppi_H, TopJLC_puppi_MC;

  std::unique_ptr<GenericJetResolutionSmearer>     JER_smearer;
  std::unique_ptr<GenericJetResolutionSmearer>     TopJER_smearer;
  std::unique_ptr<GenericJetResolutionSmearer>     TopJER_puppi_smearer;


  // Cleaners
  std::unique_ptr<MuonCleaner>                     muon_cleaner;
  std::unique_ptr<ElectronCleaner>                 electron_cleaner;

  std::unique_ptr<JetCleaner>                      jet_IDcleaner, jet_cleaner1, jet_cleaner2;
  std::unique_ptr<TopJetCleaner>                   topjet_IDcleaner, topjet_cleaner, topjet_puppi_IDcleaner, topjet_puppi_cleaner;



  // Selections
  std::unique_ptr<uhh2::Selection> lumi_sel;
  std::unique_ptr<uhh2::AndSelection> metfilters_sel;

  std::unique_ptr<uhh2::Selection> genflavor_sel;

  std::unique_ptr<uhh2::Selection> jet1_sel;
  std::unique_ptr<uhh2::Selection> jet2_sel;
  std::unique_ptr<uhh2::Selection> met_sel;

  bool isMC, ispuppi;

  std::unique_ptr<Hists> lumihists;
  TString METcollection;


  // Runnumbers for applying different corrections

  constexpr static int s_runnr_B_2016  = 275376; //up to this one, including this one
  constexpr static int s_runnr_C_2016  = 276283; //up to this one, including this one
  constexpr static int s_runnr_D_2016 =  276811; //up to this one, including this one
  constexpr static int s_runnr_E_2016 =  277420; //up to this one, including this one
  constexpr static int s_runnr_F_2016 =  278801; //up to this one, including this one = Fearly
  constexpr static int s_runnr_G_2016 =  280385; //up to this one, including this one
  constexpr static int s_runnr_H_2016 =  284044; //up to this one, including this one

  constexpr static int s_runnr_B_2017  = 299329; //up to this one, including this one
  constexpr static int s_runnr_C_2017  = 302029; //up to this one, including this one
  constexpr static int s_runnr_D_2017 =  303434; //up to this one, including this one
  constexpr static int s_runnr_E_2017 =  304826; //up to this one, including this one
  constexpr static int s_runnr_F_2017  = 306462; //up to this one, including this one

  constexpr static int s_runnr_A_2018  = 316995; //up to this one, including this one
  constexpr static int s_runnr_B_2018  = 319310; //up to this one, including this one
  constexpr static int s_runnr_C_2018  = 320065; //up to this one, including this one
  constexpr static int s_runnr_D_2018 =  325175; //up to this one, including this one

  bool is2016v2, is2016v3, is2017v2, is2018;
};

//void ZprimePreselectionModule_DNN::book_histograms(uhh2::Context& ctx, vector<string> tags){
//  for(const auto & tag : tags){
//    string mytag = tag+"_General";
//    book_HFolder(mytag, new ZprimeSemiLeptonicPreselectionHists(ctx,mytag));
//    mytag = tag+"_Muons";
//    book_HFolder(mytag, new MuonHists(ctx,mytag));
//    mytag = tag+"_Electrons";
//    book_HFolder(mytag, new ElectronHists(ctx,mytag));
//    mytag = tag+"_Jets";
//    book_HFolder(mytag, new JetHists(ctx,mytag));
//    mytag = tag+"_Event";
//    book_HFolder(mytag, new EventHists(ctx,mytag));
//    mytag = tag+"_Generator";
//    book_HFolder(mytag, new ZprimeSemiLeptonicGeneratorHists(ctx,mytag));
//  }
//}

//void ZprimePreselectionModule_DNN::fill_histograms(uhh2::Event& event, string tag){
//  string mytag = tag+"_General";
//  HFolder(mytag)->fill(event);
//  mytag = tag+"_Muons";
//  HFolder(mytag)->fill(event);
//  mytag = tag+"_Electrons";
//  HFolder(mytag)->fill(event);
//  mytag = tag+"_Jets";
//  HFolder(mytag)->fill(event);
//  mytag = tag+"_Event";
//  HFolder(mytag)->fill(event);
//  mytag = tag+"_Generator";
//  HFolder(mytag)->fill(event);
//}



void ZprimePreselectionModule_DNN::init_JEC_JLC(uhh2::Context& ctx){
  // Jet energy corrections
  std::vector<std::string> JEC_AK4CHS_MC, JEC_AK8CHS_MC, JEC_AK4Puppi_MC, JEC_AK8Puppi_MC;
  std::vector<std::string> JEC_AK4CHS_A, JEC_AK4CHS_B, JEC_AK4CHS_C, JEC_AK4CHS_D, JEC_AK4CHS_E, JEC_AK4CHS_F, JEC_AK4CHS_G, JEC_AK4CHS_H;
  std::vector<std::string> JEC_AK4Puppi_A, JEC_AK4Puppi_B, JEC_AK4Puppi_C, JEC_AK4Puppi_D, JEC_AK4Puppi_E, JEC_AK4Puppi_F, JEC_AK4Puppi_G, JEC_AK4Puppi_H;
  std::vector<std::string> JEC_AK8CHS_A, JEC_AK8CHS_B, JEC_AK8CHS_C, JEC_AK8CHS_D, JEC_AK8CHS_E, JEC_AK8CHS_F, JEC_AK8CHS_G, JEC_AK8CHS_H;
  std::vector<std::string> JEC_AK8Puppi_A, JEC_AK8Puppi_B, JEC_AK8Puppi_C, JEC_AK8Puppi_D, JEC_AK8Puppi_E, JEC_AK8Puppi_F, JEC_AK8Puppi_G, JEC_AK8Puppi_H;

  if(!is2017v2 && !is2018 && !is2016v2 && !is2016v3) cout<<"Hm, some is wrong. Did you mention year in Version parameter of xml file?"<<endl;
  if(is2016v2 || is2016v3){
    cout<<"ZprimePreselectionModule uses JEC for 2016 data/MC"<<endl;
    JEC_AK4CHS_B       = JERFiles::Summer16_07Aug2017_V11_B_L123_AK4PFchs_DATA;
    JEC_AK4CHS_C       = JERFiles::Summer16_07Aug2017_V11_C_L123_AK4PFchs_DATA;
    JEC_AK4CHS_D       = JERFiles::Summer16_07Aug2017_V11_D_L123_AK4PFchs_DATA;
    JEC_AK4CHS_E       = JERFiles::Summer16_07Aug2017_V11_E_L123_AK4PFchs_DATA;
    JEC_AK4CHS_F       = JERFiles::Summer16_07Aug2017_V11_F_L123_AK4PFchs_DATA;
    JEC_AK4CHS_G       = JERFiles::Summer16_07Aug2017_V11_G_L123_AK4PFchs_DATA;
    JEC_AK4CHS_H       = JERFiles::Summer16_07Aug2017_V11_H_L123_AK4PFchs_DATA;
    JEC_AK4CHS_MC       = JERFiles::Summer16_07Aug2017_V11_L123_AK4PFchs_MC;

    JEC_AK8CHS_B       = JERFiles::Summer16_07Aug2017_V11_B_L123_AK8PFchs_DATA;
    JEC_AK8CHS_C       = JERFiles::Summer16_07Aug2017_V11_C_L123_AK8PFchs_DATA;
    JEC_AK8CHS_D       = JERFiles::Summer16_07Aug2017_V11_D_L123_AK8PFchs_DATA;
    JEC_AK8CHS_E       = JERFiles::Summer16_07Aug2017_V11_E_L123_AK8PFchs_DATA;
    JEC_AK8CHS_F       = JERFiles::Summer16_07Aug2017_V11_F_L123_AK8PFchs_DATA;
    JEC_AK8CHS_G       = JERFiles::Summer16_07Aug2017_V11_G_L123_AK8PFchs_DATA;
    JEC_AK8CHS_H       = JERFiles::Summer16_07Aug2017_V11_H_L123_AK8PFchs_DATA;
    JEC_AK8CHS_MC       = JERFiles::Summer16_07Aug2017_V11_L123_AK8PFchs_MC;

    JEC_AK4Puppi_B = JERFiles::Summer16_07Aug2017_V11_B_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_C = JERFiles::Summer16_07Aug2017_V11_C_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_D = JERFiles::Summer16_07Aug2017_V11_D_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_E = JERFiles::Summer16_07Aug2017_V11_E_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_F = JERFiles::Summer16_07Aug2017_V11_F_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_G = JERFiles::Summer16_07Aug2017_V11_G_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_H = JERFiles::Summer16_07Aug2017_V11_H_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_MC = JERFiles::Summer16_07Aug2017_V11_L123_AK4PFPuppi_MC;

    JEC_AK8Puppi_B = JERFiles::Summer16_07Aug2017_V11_B_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_C = JERFiles::Summer16_07Aug2017_V11_C_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_D = JERFiles::Summer16_07Aug2017_V11_D_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_E = JERFiles::Summer16_07Aug2017_V11_E_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_F = JERFiles::Summer16_07Aug2017_V11_F_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_G = JERFiles::Summer16_07Aug2017_V11_G_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_H = JERFiles::Summer16_07Aug2017_V11_H_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_MC = JERFiles::Summer16_07Aug2017_V11_L123_AK8PFPuppi_MC;

    /*
    JEC_AK4CHS_B       = JERFiles::Summer16_07Aug2017_V11_L1fix_B_L123_AK4PFchs_DATA;
    JEC_AK4CHS_C       = JERFiles::Summer16_07Aug2017_V11_L1fix_C_L123_AK4PFchs_DATA;
    JEC_AK4CHS_D       = JERFiles::Summer16_07Aug2017_V11_L1fix_D_L123_AK4PFchs_DATA;
    JEC_AK4CHS_E       = JERFiles::Summer16_07Aug2017_V11_L1fix_E_L123_AK4PFchs_DATA;
    JEC_AK4CHS_F       = JERFiles::Summer16_07Aug2017_V11_L1fix_F_L123_AK4PFchs_DATA;
    JEC_AK4CHS_G       = JERFiles::Summer16_07Aug2017_V11_L1fix_G_L123_AK4PFchs_DATA;
    JEC_AK4CHS_H       = JERFiles::Summer16_07Aug2017_V11_L1fix_H_L123_AK4PFchs_DATA;
    JEC_AK4CHS_MC       = JERFiles::Summer16_07Aug2017_V11_L1fix_L123_AK4PFchs_MC;

    JEC_AK8CHS_B       = JERFiles::Summer16_07Aug2017_V11_L1fix_B_L123_AK8PFchs_DATA;
    JEC_AK8CHS_C       = JERFiles::Summer16_07Aug2017_V11_L1fix_C_L123_AK8PFchs_DATA;
    JEC_AK8CHS_D       = JERFiles::Summer16_07Aug2017_V11_L1fix_D_L123_AK8PFchs_DATA;
    JEC_AK8CHS_E       = JERFiles::Summer16_07Aug2017_V11_L1fix_E_L123_AK8PFchs_DATA;
    JEC_AK8CHS_F       = JERFiles::Summer16_07Aug2017_V11_L1fix_F_L123_AK8PFchs_DATA;
    JEC_AK8CHS_G       = JERFiles::Summer16_07Aug2017_V11_L1fix_G_L123_AK8PFchs_DATA;
    JEC_AK8CHS_H       = JERFiles::Summer16_07Aug2017_V11_L1fix_H_L123_AK8PFchs_DATA;
    JEC_AK8CHS_MC       = JERFiles::Summer16_07Aug2017_V11_L1fix_L123_AK8PFchs_MC;

    JEC_AK4Puppi_B = JERFiles::Summer16_07Aug2017_V11_L1fix_B_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_C = JERFiles::Summer16_07Aug2017_V11_L1fix_C_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_D = JERFiles::Summer16_07Aug2017_V11_L1fix_D_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_E = JERFiles::Summer16_07Aug2017_V11_L1fix_E_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_F = JERFiles::Summer16_07Aug2017_V11_L1fix_F_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_G = JERFiles::Summer16_07Aug2017_V11_L1fix_G_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_H = JERFiles::Summer16_07Aug2017_V11_L1fix_H_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_MC = JERFiles::Summer16_07Aug2017_V11_L1fix_L123_AK4PFPuppi_MC;

    JEC_AK8Puppi_B = JERFiles::Summer16_07Aug2017_V11_L1fix_B_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_C = JERFiles::Summer16_07Aug2017_V11_L1fix_C_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_D = JERFiles::Summer16_07Aug2017_V11_L1fix_D_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_E = JERFiles::Summer16_07Aug2017_V11_L1fix_E_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_F = JERFiles::Summer16_07Aug2017_V11_L1fix_F_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_G = JERFiles::Summer16_07Aug2017_V11_L1fix_G_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_H = JERFiles::Summer16_07Aug2017_V11_L1fix_H_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_MC = JERFiles::Summer16_07Aug2017_V11_L1fix_L123_AK8PFPuppi_MC;
    */
  }

  if(is2017v2){
    cout<<"ZprimePreselectionModule uses JEC for 2017 data/MC"<<endl;
    JEC_AK4CHS_B       = JERFiles::Fall17_17Nov2017_V32_B_L123_AK4PFchs_DATA;
    JEC_AK4CHS_C       = JERFiles::Fall17_17Nov2017_V32_C_L123_AK4PFchs_DATA;
    JEC_AK4CHS_D       = JERFiles::Fall17_17Nov2017_V32_D_L123_AK4PFchs_DATA;
    JEC_AK4CHS_E       = JERFiles::Fall17_17Nov2017_V32_E_L123_AK4PFchs_DATA;
    JEC_AK4CHS_F       = JERFiles::Fall17_17Nov2017_V32_F_L123_AK4PFchs_DATA;
    JEC_AK4CHS_MC       = JERFiles::Fall17_17Nov2017_V32_L123_AK4PFchs_MC;

    JEC_AK8CHS_B       = JERFiles::Fall17_17Nov2017_V32_B_L123_AK8PFchs_DATA;
    JEC_AK8CHS_C       = JERFiles::Fall17_17Nov2017_V32_C_L123_AK8PFchs_DATA;
    JEC_AK8CHS_D       = JERFiles::Fall17_17Nov2017_V32_D_L123_AK8PFchs_DATA;
    JEC_AK8CHS_E       = JERFiles::Fall17_17Nov2017_V32_E_L123_AK8PFchs_DATA;
    JEC_AK8CHS_F       = JERFiles::Fall17_17Nov2017_V32_F_L123_AK8PFchs_DATA;
    JEC_AK8CHS_MC       = JERFiles::Fall17_17Nov2017_V32_L123_AK8PFchs_MC;

    JEC_AK4Puppi_B = JERFiles::Fall17_17Nov2017_V32_B_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_C = JERFiles::Fall17_17Nov2017_V32_C_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_D = JERFiles::Fall17_17Nov2017_V32_D_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_E = JERFiles::Fall17_17Nov2017_V32_E_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_F = JERFiles::Fall17_17Nov2017_V32_F_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_MC = JERFiles::Fall17_17Nov2017_V32_L123_AK4PFPuppi_MC;

    JEC_AK8Puppi_B = JERFiles::Fall17_17Nov2017_V32_B_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_C = JERFiles::Fall17_17Nov2017_V32_C_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_D = JERFiles::Fall17_17Nov2017_V32_D_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_E = JERFiles::Fall17_17Nov2017_V32_E_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_F = JERFiles::Fall17_17Nov2017_V32_F_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_MC = JERFiles::Fall17_17Nov2017_V32_L123_AK8PFPuppi_MC;
  }
  if(is2018){
    cout<<"ZprimePreselectionModule uses JEC for 2018 data/MC"<<endl;
    JEC_AK4CHS_A       = JERFiles::Autumn18_V8_A_L123_AK4PFchs_DATA;
    JEC_AK4CHS_B       = JERFiles::Autumn18_V8_B_L123_AK4PFchs_DATA;
    JEC_AK4CHS_C       = JERFiles::Autumn18_V8_C_L123_AK4PFchs_DATA;
    JEC_AK4CHS_D       = JERFiles::Autumn18_V8_D_L123_AK4PFchs_DATA;
    JEC_AK4CHS_MC       = JERFiles::Autumn18_V8_L123_AK4PFchs_MC;

    JEC_AK8CHS_A       = JERFiles::Autumn18_V8_A_L123_AK8PFchs_DATA;
    JEC_AK8CHS_B       = JERFiles::Autumn18_V8_B_L123_AK8PFchs_DATA;
    JEC_AK8CHS_C       = JERFiles::Autumn18_V8_C_L123_AK8PFchs_DATA;
    JEC_AK8CHS_D       = JERFiles::Autumn18_V8_D_L123_AK8PFchs_DATA;
    JEC_AK8CHS_MC       = JERFiles::Autumn18_V8_L123_AK8PFchs_MC;

    JEC_AK4Puppi_A = JERFiles::Autumn18_V8_A_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_B = JERFiles::Autumn18_V8_B_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_C = JERFiles::Autumn18_V8_C_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_D = JERFiles::Autumn18_V8_D_L123_AK4PFPuppi_DATA;
    JEC_AK4Puppi_MC = JERFiles::Autumn18_V8_L123_AK4PFPuppi_MC;

    JEC_AK8Puppi_A = JERFiles::Autumn18_V8_A_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_B = JERFiles::Autumn18_V8_B_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_C = JERFiles::Autumn18_V8_C_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_D = JERFiles::Autumn18_V8_D_L123_AK8PFPuppi_DATA;
    JEC_AK8Puppi_MC = JERFiles::Autumn18_V8_L123_AK8PFPuppi_MC;
  }
  cout<<"And now read JECs"<<endl;

 if(!ispuppi){
   if(is2018) jet_corrector_A.reset(new JetCorrector(ctx, JEC_AK4CHS_A));
    jet_corrector_B.reset(new JetCorrector(ctx, JEC_AK4CHS_B));
    jet_corrector_C.reset(new JetCorrector(ctx, JEC_AK4CHS_C));
    jet_corrector_D.reset(new JetCorrector(ctx, JEC_AK4CHS_D));
    if(is2017v2 or is2016v2 or is2016v3){
      //      jet_corrector_D.reset(new JetCorrector(ctx, JEC_AK4CHS_D));//tmp
      jet_corrector_E.reset(new JetCorrector(ctx, JEC_AK4CHS_E));
      jet_corrector_F.reset(new JetCorrector(ctx, JEC_AK4CHS_F));
      if(is2016v2 or is2016v3){
	jet_corrector_G.reset(new JetCorrector(ctx, JEC_AK4CHS_G));
	jet_corrector_H.reset(new JetCorrector(ctx, JEC_AK4CHS_H));
      }
    }
    jet_corrector_MC.reset(new JetCorrector(ctx,            JEC_AK4CHS_MC));

    //Jet-lepton cleaning
    if(is2018) JLC_A.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_A));
    JLC_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_B));
    JLC_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_C));
    JLC_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_D));
    if(is2017v2 or is2016v2 or is2016v3){
      //  JLC_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_D));//tmp
      JLC_E.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_E));
      JLC_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_F));
      if(is2016v2 or is2016v3){
	JLC_G.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_G));
	JLC_H.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4CHS_H));
      }
    }
    JLC_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,            JEC_AK4CHS_MC));
 }
  else{
    if(is2018) jet_corrector_A.reset(new JetCorrector(ctx, JEC_AK4Puppi_A));
    jet_corrector_B.reset(new JetCorrector(ctx, JEC_AK4Puppi_B));
    jet_corrector_C.reset(new JetCorrector(ctx, JEC_AK4Puppi_C));
    jet_corrector_D.reset(new JetCorrector(ctx, JEC_AK4Puppi_D));
    if(is2017v2 or is2016v2 or is2016v3){
      //  jet_corrector_D.reset(new JetCorrector(ctx, JEC_AK4Puppi_D));//tmp
      jet_corrector_E.reset(new JetCorrector(ctx, JEC_AK4Puppi_E));
      jet_corrector_F.reset(new JetCorrector(ctx, JEC_AK4Puppi_F));
      if(is2016v2 or is2016v3){
	jet_corrector_G.reset(new JetCorrector(ctx, JEC_AK4Puppi_G));
	jet_corrector_H.reset(new JetCorrector(ctx, JEC_AK4Puppi_H));
      }
    }
    jet_corrector_MC.reset(new JetCorrector(ctx, JEC_AK4Puppi_MC));

    //Jet-lepton cleaning
    if(is2018) JLC_A.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_A));
    JLC_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_B));
    JLC_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_C));
    JLC_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_D));
    if(is2017v2 or is2016v2 or is2016v3){
      //  JLC_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_D));//tmp
      JLC_E.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_E));
      JLC_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_F));
      if(is2016v2 or is2016v3){
	JLC_G.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_G));
	JLC_H.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK4Puppi_H));
      }
    }
    JLC_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,            JEC_AK4Puppi_MC));
  }
  cout<<"And now read top JECs"<<endl;
  if(is2018) topjet_corrector_A.reset(new TopJetCorrector(ctx,       JEC_AK8CHS_A));
  topjet_corrector_B.reset(new TopJetCorrector(ctx,       JEC_AK8CHS_B));
  topjet_corrector_C.reset(new TopJetCorrector(ctx,       JEC_AK8CHS_C));
  topjet_corrector_D.reset(new TopJetCorrector(ctx,      JEC_AK8CHS_D));
  if(is2017v2 or is2016v2 or is2016v3){
    //  topjet_corrector_D.reset(new TopJetCorrector(ctx,      JEC_AK8CHS_D));//tmp
    topjet_corrector_E.reset(new TopJetCorrector(ctx,      JEC_AK8CHS_E));
    topjet_corrector_F.reset(new TopJetCorrector(ctx,       JEC_AK8CHS_F));
    if(is2016v2 or is2016v3){
    topjet_corrector_G.reset(new TopJetCorrector(ctx,      JEC_AK8CHS_G));
    topjet_corrector_H.reset(new TopJetCorrector(ctx,      JEC_AK8CHS_H));
    }
  }
  topjet_corrector_MC.reset(new TopJetCorrector(ctx,      JEC_AK8CHS_MC));

  if(is2018) topjet_puppi_corrector_A.reset(new GenericTopJetCorrector(ctx,   JEC_AK8Puppi_A, "toppuppijets"));
  topjet_puppi_corrector_B.reset(new GenericTopJetCorrector(ctx,       JEC_AK8Puppi_B, "toppuppijets"));
  topjet_puppi_corrector_C.reset(new GenericTopJetCorrector(ctx,       JEC_AK8Puppi_C, "toppuppijets"));
  topjet_puppi_corrector_D.reset(new GenericTopJetCorrector(ctx,      JEC_AK8Puppi_D, "toppuppijets"));
  if(is2017v2 or is2016v2 or is2016v3){
    //  topjet_puppi_corrector_D.reset(new GenericTopJetCorrector(ctx,      JEC_AK8Puppi_D, "toppuppijets"));//tmp
    topjet_puppi_corrector_E.reset(new GenericTopJetCorrector(ctx,      JEC_AK8Puppi_E, "toppuppijets"));
    topjet_puppi_corrector_F.reset(new GenericTopJetCorrector(ctx,       JEC_AK8Puppi_F, "toppuppijets"));
    if(is2016v2 or is2016v3){
    topjet_puppi_corrector_G.reset(new GenericTopJetCorrector(ctx,      JEC_AK8Puppi_G, "toppuppijets"));
    topjet_puppi_corrector_H.reset(new GenericTopJetCorrector(ctx,      JEC_AK8Puppi_H, "toppuppijets"));
    }
  }
  topjet_puppi_corrector_MC.reset(new GenericTopJetCorrector(ctx,      JEC_AK8Puppi_MC, "toppuppijets"));

  //Jet subjet corrector
  if(is2018) topjet_subjet_corrector_A.reset(new SubJetCorrector(ctx,       JEC_AK4CHS_A));
  topjet_subjet_corrector_B.reset(new SubJetCorrector(ctx,       JEC_AK4CHS_B));
  topjet_subjet_corrector_C.reset(new SubJetCorrector(ctx,       JEC_AK4CHS_C));
  topjet_subjet_corrector_D.reset(new SubJetCorrector(ctx,      JEC_AK4CHS_D));
  if(is2017v2 or is2016v2 or is2016v3){
    //  topjet_subjet_corrector_D.reset(new SubJetCorrector(ctx,      JEC_AK4CHS_D));//tmp
    topjet_subjet_corrector_E.reset(new SubJetCorrector(ctx,      JEC_AK4CHS_E));
    topjet_subjet_corrector_F.reset(new SubJetCorrector(ctx,       JEC_AK4CHS_F));
    if(is2016v2 or is2016v3){
    topjet_subjet_corrector_G.reset(new SubJetCorrector(ctx,      JEC_AK4CHS_G));
    topjet_subjet_corrector_H.reset(new SubJetCorrector(ctx,      JEC_AK4CHS_H));
    }
  }
  topjet_subjet_corrector_MC.reset(new SubJetCorrector(ctx,      JEC_AK4CHS_MC));

 if(is2018) topjet_puppi_subjet_corrector_A.reset(new GenericSubJetCorrector(ctx,  JEC_AK4Puppi_A, "toppuppijets"));
  topjet_puppi_subjet_corrector_B.reset(new GenericSubJetCorrector(ctx,       JEC_AK4Puppi_B, "toppuppijets"));
  topjet_puppi_subjet_corrector_C.reset(new GenericSubJetCorrector(ctx,       JEC_AK4Puppi_C, "toppuppijets"));
  topjet_puppi_subjet_corrector_D.reset(new GenericSubJetCorrector(ctx,      JEC_AK4Puppi_D, "toppuppijets"));
  if(is2017v2 or is2016v2 or is2016v3){
    //  topjet_puppi_subjet_corrector_D.reset(new GenericSubJetCorrector(ctx,      JEC_AK4Puppi_D, "toppuppijets"));//tmp
    topjet_puppi_subjet_corrector_E.reset(new GenericSubJetCorrector(ctx,      JEC_AK4Puppi_E, "toppuppijets"));
    topjet_puppi_subjet_corrector_F.reset(new GenericSubJetCorrector(ctx,       JEC_AK4Puppi_F, "toppuppijets"));
    if(is2016v2 or is2016v3){
    topjet_puppi_subjet_corrector_G.reset(new GenericSubJetCorrector(ctx,      JEC_AK4Puppi_G, "toppuppijets"));
    topjet_puppi_subjet_corrector_H.reset(new GenericSubJetCorrector(ctx,      JEC_AK4Puppi_H, "toppuppijets"));
    }
  }
  topjet_puppi_subjet_corrector_MC.reset(new GenericSubJetCorrector(ctx,      JEC_AK4Puppi_MC, "toppuppijets"));


  //Jet lepton cleaning
  if(is2018) TopJLC_A.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK8CHS_A, "topjets"));
  TopJLC_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8CHS_B, "topjets"));
  TopJLC_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8CHS_C, "topjets"));
  TopJLC_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8CHS_D, "topjets"));
  if(is2017v2 or is2016v2 or is2016v3){
    //  TopJLC_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8CHS_D, "topjets"));//tmp
    TopJLC_E.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8CHS_E, "topjets"));
    TopJLC_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8CHS_F, "topjets"));
    if(is2016v2 or is2016v3){
    TopJLC_G.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8CHS_G, "topjets"));
    TopJLC_H.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8CHS_H, "topjets"));
    }
  }
  TopJLC_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8CHS_MC, "topjets"));

  if(is2018) TopJLC_puppi_A.reset(new JetLeptonCleaner_by_KEYmatching(ctx, JEC_AK8Puppi_A, "toppuppijets"));
  TopJLC_puppi_B.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8Puppi_B, "toppuppijets"));
  TopJLC_puppi_C.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8Puppi_C, "toppuppijets"));
  TopJLC_puppi_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8Puppi_D, "toppuppijets"));
  if(is2017v2 or is2016v2 or is2016v3){
    //  TopJLC_puppi_D.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8Puppi_D, "toppuppijets"));//tmp
    TopJLC_puppi_E.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8Puppi_E, "toppuppijets"));
    TopJLC_puppi_F.reset(new JetLeptonCleaner_by_KEYmatching(ctx,       JEC_AK8Puppi_F, "toppuppijets"));
    if(is2016v2 or is2016v3){
    TopJLC_puppi_G.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8Puppi_G, "toppuppijets"));
    TopJLC_puppi_H.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8Puppi_H, "toppuppijets"));
    }
  }
  TopJLC_puppi_MC.reset(new JetLeptonCleaner_by_KEYmatching(ctx,      JEC_AK8Puppi_MC, "toppuppijets"));

  cout<<"done with init JEC and JLC"<<endl;
}


ZprimePreselectionModule_DNN::ZprimePreselectionModule_DNN(uhh2::Context& ctx){

  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }

  //// CONFIGURATION
  // const std::string& _METcollection = ctx.get("METName");
  const TString METcollection = ctx.get("METName");
  const bool isMC = (ctx.get("dataset_type") == "MC");
  const bool ispuppi = (ctx.get("is_puppi") == "true");
  is2016v2 = (ctx.get("dataset_version").find("2016v2") != std::string::npos);
  is2016v3 = (ctx.get("dataset_version").find("2016v3") != std::string::npos);
  is2017v2 = (ctx.get("dataset_version").find("2017v2") != std::string::npos);
  is2018 = (ctx.get("dataset_version").find("2018") != std::string::npos);
 
  cout << "Is this running on puppi: " << ispuppi << endl;

  ElectronId eleID;  MuonId muID;
  if(is2017v2 || is2018){
    eleID = ElectronID_Fall17_tight_noIso;//ToDo: compare cutBased without iso and MVA-based via wp in UHH2
    muID      = MuonID(Muon::CutBasedIdGlobalHighPt);
  }
  if(is2016v2 || is2016v3){
    //eleID = ElectronID_Summer16_tight_noIso;//ToDo: compare cutBased without iso and MVA-based via wp in UHH2
    //muID      = MuonID(Muon::Highpt);
    eleID = ElectronID_Summer16_medium_noIso;
    muID  = MuonID(Muon::CutBasedIdTight); // see more muonIDs https://github.com/cms-sw/cmssw/blob/master/DataFormats/MuonReco/interface/Muon.h#L201
  }
  double electron_pt(50.);
  double muon_pt(55.);
  double jet1_pt(50.);
  double jet2_pt(20.);
  double MET(0.);

  // COMMON MODULES

  if(!isMC) lumi_sel.reset(new LumiSelection(ctx));

  // MET filters
  metfilters_sel.reset(new uhh2::AndSelection(ctx, "metfilters"));
  if(!isMC){
    metfilters_sel->add<TriggerSelection>("1-good-vtx", "Flag_goodVertices");
    metfilters_sel->add<TriggerSelection>("globalTightHalo2016Filter", "Flag_globalTightHalo2016Filter");
    metfilters_sel->add<TriggerSelection>("HBHENoiseFilter", "Flag_HBHENoiseFilter");
    metfilters_sel->add<TriggerSelection>("HBHENoiseIsoFilter", "Flag_HBHENoiseIsoFilter");
    metfilters_sel->add<TriggerSelection>("EcalDeadCellTriggerPrimitiveFilter", "Flag_EcalDeadCellTriggerPrimitiveFilter");
    if(!isMC)  metfilters_sel->add<TriggerSelection>("eeBadScFilter", "Flag_eeBadScFilter");
    metfilters_sel->add<TriggerSelection>("chargedHadronTrackResolutionFilter", "Flag_chargedHadronTrackResolutionFilter");
    metfilters_sel->add<TriggerSelection>("muonBadTrackFilter", "Flag_muonBadTrackFilter");
  }


  /******************************************************************/

  /* GEN Flavor selection [W+jets flavor-splitting] */
  if(ctx.get("dataset_version").find("WJets") != std::string::npos){

    if     (ctx.get("dataset_version").find("_B") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("b"));
    else if(ctx.get("dataset_version").find("_C") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("c"));
    else if(ctx.get("dataset_version").find("_L") != std::string::npos) genflavor_sel.reset(new GenFlavorSelection("l"));

    else genflavor_sel.reset(new uhh2::AndSelection(ctx));
  }
  else genflavor_sel.reset(new uhh2::AndSelection(ctx));
  /**************************************************/

  ////

  // Cleaning: Mu, Ele, Jets
  const MuonId muonID(AndId<Muon>(PtEtaCut(muon_pt, 2.4), muID));
  const ElectronId electronID(AndId<Electron>(PtEtaSCCut(electron_pt, 2.5), eleID));
  const JetPFID jetID_CHS(JetPFID::WP_TIGHT_CHS); 
  const JetPFID jetID_PUPPI(JetPFID::WP_TIGHT_PUPPI); 

  muon_cleaner.reset(new MuonCleaner(muonID));
  electron_cleaner.reset(new ElectronCleaner(electronID));
  //  jet_IDcleaner.reset(new JetCleaner(ctx, jetID_CHS));
  jet_IDcleaner.reset(new JetCleaner(ctx, jetID_PUPPI));
  jet_cleaner1.reset(new JetCleaner(ctx, 15., 3.0));
  jet_cleaner2.reset(new JetCleaner(ctx, 30., 2.4));
  topjet_IDcleaner.reset(new TopJetCleaner(ctx, jetID_CHS, "topjets"));
  topjet_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4)), "topjets"));//400
  topjet_puppi_IDcleaner.reset(new TopJetCleaner(ctx, jetID_PUPPI, "toppuppijets"));
  topjet_puppi_cleaner.reset(new TopJetCleaner(ctx, TopJetId(PtEtaCut(400., 2.4)), "toppuppijets")); //400

  //set up JEC and JLC
  init_JEC_JLC(ctx);
  
  if(isMC){
    //    ctx.declare_event_input<std::vector<Particle> >(ctx.get("TopJetCollectionGEN"), "topjetsGEN");
    if(is2016v2 || is2016v3){
      if(!ispuppi) JER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERSmearing::SF_13TeV_Summer16_25nsV1, "2016/Summer16_25nsV1_MC_PtResolution_AK4PFchs.txt"));
      else JER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERSmearing::SF_13TeV_Summer16_25nsV1, "2016/Summer16_25nsV1_MC_PtResolution_AK4PFPuppi.txt"));
      TopJER_smearer.reset(new GenericJetResolutionSmearer(ctx, "topjets", "gentopjets", JERSmearing::SF_13TeV_Summer16_25nsV1, "2016/Summer16_25nsV1_MC_PtResolution_AK8PFchs.txt"));
      TopJER_puppi_smearer.reset(new GenericJetResolutionSmearer(ctx, "toppuppijets", "gentopjets", JERSmearing::SF_13TeV_Summer16_25nsV1, "2016/Summer16_25nsV1_MC_PtResolution_AK8PFPuppi.txt"));
    }
    if(is2017v2){
      if(!ispuppi) JER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERSmearing::SF_13TeV_Fall17_V3, "2017/Fall17_V3_MC_PtResolution_AK4PFchs.txt"));
      else JER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERSmearing::SF_13TeV_Fall17_V3, "2017/Fall17_V3_MC_PtResolution_AK4PFPuppi.txt"));
      TopJER_smearer.reset(new GenericJetResolutionSmearer(ctx, "topjets", "gentopjets", JERSmearing::SF_13TeV_Fall17_V3, "2017/Fall17_V3_MC_PtResolution_AK8PFchs.txt"));
      TopJER_puppi_smearer.reset(new GenericJetResolutionSmearer(ctx, "toppuppijets", "gentopjets", JERSmearing::SF_13TeV_Fall17_V3, "2017/Fall17_V3_MC_PtResolution_AK8PFPuppi.txt"));
    }
    /* Was NOT used yet, 2017 JER SFs were used in previous 2018 iteration!
    if(is2018){
      if(!ispuppi) JER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERSmearing::SF_13TeV_Autumn18_RunABCD_V4, "2018/Autumn18_V4_MC_PtResolution_AK4PFchs.txt"));
      else JER_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERSmearing::SF_13TeV_Autumn18_RunABCD_V4, "2018/Autumn18_V4_MC_PtResolution_AK4PFPuppi.txt"));
      TopJER_smearer.reset(new GenericJetResolutionSmearer(ctx, "topjets", "gentopjets", JERSmearing::SF_13TeV_Autumn18_RunABCD_V4, "2018/Autumn18_V4_MC_PtResolution_AK8PFchs.txt"));
      TopJER_puppi_smearer.reset(new GenericJetResolutionSmearer(ctx, "toppuppijets", "gentopjets", JERSmearing::SF_13TeV_Autumn18_RunABCD_V4, "2018/Autumn18_V4_MC_PtResolution_AK8PFPuppi.txt"));
    }
    */
  }


  //// EVENT SELECTION
  jet1_sel.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  jet2_sel.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  met_sel  .reset(new METCut  (MET   , uhh2::infinity));

  h_MET = ctx.declare_event_output<float> ("met");
  h_weight = ctx.declare_event_output<float> ("weight");
  h_ST = ctx.declare_event_output<float> ("st");
  h_STjets = ctx.declare_event_output<float> ("st_jets");
  h_STlep = ctx.declare_event_output<float> ("st_lep");
  h_NPV = ctx.declare_event_output<float> ("npv_pt");
  h_N_jets = ctx.declare_event_output<float> ("N_jets");
  h_pt_jet = ctx.declare_event_output<float> ("pt_jet");
  h_pt_jet1 = ctx.declare_event_output<float> ("pt_jet1");
  h_pt_jet2 = ctx.declare_event_output<float> ("pt_jet2");
  h_pt_jet3 = ctx.declare_event_output<float> ("pt_jet3");
  h_eta_jet = ctx.declare_event_output<float> ("eta_jet");
  h_eta_jet1 = ctx.declare_event_output<float> ("eta_jet1");
  h_eta_jet2 = ctx.declare_event_output<float> ("eta_jet2");
  h_eta_jet3 = ctx.declare_event_output<float> ("eta_jet3");
  h_phi_jet = ctx.declare_event_output<float> ("phi_jet");
  h_phi_jet1 = ctx.declare_event_output<float> ("phi_jet1");
  h_phi_jet2 = ctx.declare_event_output<float> ("phi_jet2");
  h_phi_jet3 = ctx.declare_event_output<float> ("phi_jet3");
  h_mass_jet = ctx.declare_event_output<float> ("mass_jet");
  h_mass_jet1 = ctx.declare_event_output<float> ("mass_jet1");
  h_mass_jet2 = ctx.declare_event_output<float> ("mass_jet2");
  h_mass_jet3 = ctx.declare_event_output<float> ("mass_jet3");
  h_S11 = ctx.declare_event_output<float> ("s11");
  h_S12 = ctx.declare_event_output<float> ("s12");
  h_S13 = ctx.declare_event_output<float> ("s13");
  h_S22 = ctx.declare_event_output<float> ("s22");
  h_S23 = ctx.declare_event_output<float> ("s23");
  h_S33 = ctx.declare_event_output<float> ("s33");
  h_N_mu = ctx.declare_event_output<float> ("N_mu");
  h_pt_mu = ctx.declare_event_output<float> ("pt_mu");
  h_ptrel_mu_jet = ctx.declare_event_output<float> ("ptrel_mu_jet");
  h_eta_mu = ctx.declare_event_output<float> ("eta_mu");
  h_phi_mu = ctx.declare_event_output<float> ("phi_mu");
  h_reliso_mu = ctx.declare_event_output<float> ("reliso_mu");
  h_N_ele = ctx.declare_event_output<float> ("N_ele");
  h_pt_ele = ctx.declare_event_output<float> ("pt_ele");
  h_ptrel_ele_jet = ctx.declare_event_output<float> ("ptrel_ele_jet");
  h_eta_ele = ctx.declare_event_output<float> ("eta_ele");
  h_phi_ele = ctx.declare_event_output<float> ("phi_ele");
  h_reliso_ele = ctx.declare_event_output<float> ("reliso_ele");
  h_N_Ak8Puppijets = ctx.declare_event_output<float> ("N_Ak8Puppijets");
  h_pt_Ak8Puppijets = ctx.declare_event_output<float> ("pt_Ak8Puppijets");
  h_pt_Ak8Puppijet1 = ctx.declare_event_output<float> ("pt_Ak8Puppijet1");
  h_pt_Ak8Puppijet2 = ctx.declare_event_output<float> ("pt_Ak8Puppijet2");
  h_pt_Ak8Puppijet3 = ctx.declare_event_output<float> ("pt_Ak8Puppijet3");
  h_N_Ak8Puppijets = ctx.declare_event_output<float> ("N_Ak8Puppijets");
  h_pt_Ak8Puppijets = ctx.declare_event_output<float> ("pt_Ak8Puppijets");
  h_pt_Ak8Puppijet1 = ctx.declare_event_output<float> ("pt_Ak8Puppijet1");
  h_pt_Ak8Puppijet2 = ctx.declare_event_output<float> ("pt_Ak8Puppijet2");
  h_pt_Ak8Puppijet3 = ctx.declare_event_output<float> ("pt_Ak8Puppijet3");
  h_eta_Ak8Puppijets = ctx.declare_event_output<float> ("eta_Ak8Puppijets");
  h_eta_Ak8Puppijet1 = ctx.declare_event_output<float> ("eta_Ak8Puppijet1");
  h_eta_Ak8Puppijet2 = ctx.declare_event_output<float> ("eta_Ak8Puppijet2");
  h_eta_Ak8Puppijet3 = ctx.declare_event_output<float> ("eta_Ak8Puppijet3");
  h_phi_Ak8Puppijets = ctx.declare_event_output<float> ("phi_Ak8Puppijets");
  h_phi_Ak8Puppijet1 = ctx.declare_event_output<float> ("phi_Ak8Puppijet1");
  h_phi_Ak8Puppijet2 = ctx.declare_event_output<float> ("phi_Ak8Puppijet2");
  h_phi_Ak8Puppijet3 = ctx.declare_event_output<float> ("phi_Ak8Puppijet3");
  h_mSD_Ak8Puppijets = ctx.declare_event_output<float> ("mSD_Ak8Puppijets");
  h_mSD_Ak8Puppijet1 = ctx.declare_event_output<float> ("mSD_Ak8Puppijet1");
  h_mSD_Ak8Puppijet2 = ctx.declare_event_output<float> ("mSD_Ak8Puppijet2");
  h_mSD_Ak8Puppijet3 = ctx.declare_event_output<float> ("mSD_Ak8Puppijet3");
  h_dR_mu_jet = ctx.declare_event_output<float> ("dR_mu_jet");
  h_dR_mu_Ak8Puppijet = ctx.declare_event_output<float> ("dR_mu_Ak8Puppijet");
  h_dRmin_mu_jet = ctx.declare_event_output<float> ("dRmin_mu_jet");
  h_dRmin_ele_jet = ctx.declare_event_output<float> ("dRmin_ele_jet");
  h_dR_ele_jet = ctx.declare_event_output<float> ("dR_ele_jet");
  h_dR_ele_Ak8Puppijet = ctx.declare_event_output<float> ("dR_ele_Ak8Puppijet");
  h_dR_jet_Ak8Puppijet = ctx.declare_event_output<float> ("dR_jet_Ak8Puppijet");

  // Book histograms
  //vector<string> histogram_tags = {"Input", "Lumiselection", "Metfilters", "Lepton1", "JetID", "JetCleaner1", "JetCleaner2", "TopjetCleaner", "Jet1", "Jet2", "MET"};
  //book_histograms(ctx, histogram_tags);


  lumihists.reset(new LuminosityHists(ctx, "lumi"));
}


bool ZprimePreselectionModule_DNN::process(uhh2::Event& event){

  event.set(h_MET,0);
  event.set(h_weight,0);
  event.set(h_ST,0);
  event.set(h_STjets,0);
  event.set(h_STlep,0);
  event.set(h_NPV,0);
  event.set(h_N_jets,0);
  event.set(h_pt_jet,0);
  event.set(h_pt_jet1,0);
  event.set(h_pt_jet2,0);
  event.set(h_pt_jet3,0);
  event.set(h_eta_jet,0);
  event.set(h_eta_jet1,0);
  event.set(h_eta_jet2,0);
  event.set(h_eta_jet3,0);
  event.set(h_phi_jet,0);
  event.set(h_phi_jet1,0);
  event.set(h_phi_jet2,0);
  event.set(h_phi_jet3,0);
  event.set(h_mass_jet,0);
  event.set(h_mass_jet1,0);
  event.set(h_mass_jet2,0);
  event.set(h_mass_jet3,0);
  event.set(h_S11,0);
  event.set(h_S12,0);
  event.set(h_S13,0);
  event.set(h_S22,0);
  event.set(h_S23,0);
  event.set(h_S33,0);
  event.set(h_N_mu,0);
  event.set(h_pt_mu,0);
  event.set(h_ptrel_mu_jet,0);
  event.set(h_eta_mu,0);
  event.set(h_phi_mu,0);
  event.set(h_reliso_mu,0);
  event.set(h_N_ele,0);
  event.set(h_pt_ele,0);
  event.set(h_ptrel_ele_jet,0);
  event.set(h_eta_ele,0);
  event.set(h_phi_ele,0);
  event.set(h_reliso_ele,0);
  event.set(h_N_Ak8Puppijets,0);
  event.set(h_pt_Ak8Puppijets,0);
  event.set(h_pt_Ak8Puppijet1,0);
  event.set(h_pt_Ak8Puppijet2,0);
  event.set(h_pt_Ak8Puppijet3,0);
  event.set(h_eta_Ak8Puppijets,0);
  event.set(h_eta_Ak8Puppijet1,0);
  event.set(h_eta_Ak8Puppijet2,0);
  event.set(h_eta_Ak8Puppijet3,0);
  event.set(h_phi_Ak8Puppijets,0);
  event.set(h_phi_Ak8Puppijet1,0);
  event.set(h_phi_Ak8Puppijet2,0);
  event.set(h_phi_Ak8Puppijet3,0);
  event.set(h_mSD_Ak8Puppijets,0);
  event.set(h_mSD_Ak8Puppijet1,0);
  event.set(h_mSD_Ak8Puppijet2,0);
  event.set(h_mSD_Ak8Puppijet3,0);
  event.set(h_dR_mu_jet,0);
  event.set(h_dRmin_mu_jet,0);
  event.set(h_dR_mu_Ak8Puppijet,0);
  event.set(h_dR_ele_jet,0);
  event.set(h_dRmin_ele_jet,0);
  event.set(h_dR_ele_Ak8Puppijet,0);
  event.set(h_dR_jet_Ak8Puppijet,0);
  
  bool debug = false;



  if (debug) cout<<"Getting started... "<<event.event<<endl;
  //fill_histograms(event, "Input");
  // Lumi selection
  if(event.isRealData){
    if(!lumi_sel->passes(event)) return false;
    //lumihists->fill(event);
  }
  if (debug) cout << "done with lumi_sel" << endl;
  //fill_histograms(event, "Lumiselection");

  // MET filters
  if(!metfilters_sel->passes(event)) return false;
  //fill_histograms(event, "Metfilters");
  if (debug)  cout<<"Met filters done "<<event.event<<endl;

  // GEN ME quark-flavor selection
  if(!event.isRealData){
    if(!genflavor_sel->passes(event)) return false;
  }

  if (debug)  cout<<"GEN ME quark-flavor selection done"<<event.event<<endl;
  //// LEPTON selection
  muon_cleaner->process(event);
  sort_by_pt<Muon>(*event.muons);

  electron_cleaner->process(event);
  sort_by_pt<Electron>(*event.electrons);

  if (debug) cout << " lepton cleaning and sorting done" <<endl;

  const bool pass_lep1 = ((event.muons->size() >= 1) || (event.electrons->size() >= 1));
  if(!pass_lep1) return false;

  //fill_histograms(event, "Lepton1");
  if (debug) cout<<"Lepton1 done "<<event.event<<endl;

  //// JET selection
  jet_IDcleaner->process(event);
  //fill_histograms(event, "JetID");

  if (debug) cout<<"JetID cleaner done "<<event.event<<endl;


  if(event.isRealData){
    bool apply_A = false;
    bool apply_B = false;
    bool apply_C = false;
    bool apply_D = false;
    bool apply_E = false;
    bool apply_F = false;
    bool apply_G = false;
    bool apply_H = false;
    if(is2016v2 || is2016v3){
      if(event.run <= s_runnr_B_2016)  apply_B = true;
      else if(event.run <= s_runnr_C_2016) apply_C = true;
      else if(event.run <= s_runnr_D_2016) apply_D = true;
      else if(event.run <= s_runnr_E_2016) apply_E = true;
      else if(event.run <= s_runnr_F_2016) apply_F = true;
      else if(event.run <= s_runnr_G_2016) apply_G = true;
      else if(event.run <= s_runnr_H_2016) apply_H = true;
      else throw std::runtime_error("run number not covered by if-statements in process-routine.");
    }

    if(is2017v2){
      if(event.run <= s_runnr_B_2017)  apply_B = true;
      else if(event.run <= s_runnr_C_2017) apply_C = true;
      else if(event.run <= s_runnr_D_2017) apply_D = true;
      else if(event.run <= s_runnr_E_2017) apply_E = true;
      else if(event.run <= s_runnr_F_2017) apply_F = true;
      else throw std::runtime_error("run number not covered by if-statements in process-routine.");
    }
    if(is2018){
      if(event.run <= s_runnr_A_2018)  apply_A = true;
      else if(event.run <= s_runnr_B_2018)  apply_B = true;
      else if(event.run <= s_runnr_C_2018) apply_C = true;
      else if(event.run <= s_runnr_D_2018) apply_D = true;
      else throw std::runtime_error("run number not covered by if-statements in process-routine.");
    }
    
    if (debug) cout << " done with the data" <<endl;

    if(apply_A+apply_B+apply_C+apply_D+apply_E+apply_F+apply_G+apply_H != 1) throw std::runtime_error("In ZprimePreselectionModule.cxx: Sum of apply_* when applying JECs is not == 1. Fix this.");

    //apply proper JECs
    if(apply_A){
      JLC_A->process(event);
      TopJLC_A->process(event);
      TopJLC_puppi_A->process(event);
      jet_corrector_A->process(event);
      topjet_corrector_A->process(event);
      topjet_puppi_corrector_A->process(event);
      jet_corrector_A->correct_met(event);
      topjet_subjet_corrector_A->process(event);
      topjet_puppi_subjet_corrector_A->process(event);
    }
    if(apply_B){
      JLC_B->process(event);
      TopJLC_B->process(event);
      TopJLC_puppi_B->process(event);
      jet_corrector_B->process(event);
      topjet_corrector_B->process(event);
      topjet_puppi_corrector_B->process(event);
      jet_corrector_B->correct_met(event);
      topjet_subjet_corrector_B->process(event);
      topjet_puppi_subjet_corrector_B->process(event);
    }
    if(apply_C){
      JLC_C->process(event);
      TopJLC_C->process(event);
      TopJLC_puppi_C->process(event);
      jet_corrector_C->process(event);
      topjet_corrector_C->process(event);
      topjet_puppi_corrector_C->process(event);
      jet_corrector_C->correct_met(event);
      topjet_subjet_corrector_C->process(event);
      topjet_puppi_subjet_corrector_C->process(event);
    }
    if(apply_D){
      JLC_D->process(event);
      TopJLC_D->process(event);
      TopJLC_puppi_D->process(event);
      jet_corrector_D->process(event);
      topjet_corrector_D->process(event);
      topjet_puppi_corrector_D->process(event);
      jet_corrector_D->correct_met(event);
      topjet_subjet_corrector_D->process(event);
      topjet_puppi_subjet_corrector_D->process(event);
    }
    if(apply_E){
      JLC_E->process(event);
      TopJLC_E->process(event);
      TopJLC_puppi_E->process(event);
      jet_corrector_E->process(event);
      topjet_corrector_E->process(event);
      topjet_puppi_corrector_E->process(event);
      jet_corrector_E->correct_met(event);
      topjet_subjet_corrector_E->process(event);
      topjet_puppi_subjet_corrector_E->process(event);
    }
    if(apply_F){
      JLC_F->process(event);
      TopJLC_F->process(event);
      TopJLC_puppi_F->process(event);
      jet_corrector_F->process(event);
      topjet_corrector_F->process(event);
      topjet_puppi_corrector_F->process(event);
      jet_corrector_F->correct_met(event);
      topjet_subjet_corrector_F->process(event);
      topjet_puppi_subjet_corrector_F->process(event);
    }    
    if(apply_G){
      JLC_G->process(event);
      TopJLC_G->process(event);
      TopJLC_puppi_G->process(event);
      jet_corrector_G->process(event);
      topjet_corrector_G->process(event);
      topjet_puppi_corrector_G->process(event);
      jet_corrector_G->correct_met(event);
      topjet_subjet_corrector_G->process(event);
      topjet_puppi_subjet_corrector_G->process(event);
    }
    if(apply_H){
      JLC_H->process(event);
      TopJLC_H->process(event);
      TopJLC_puppi_H->process(event);
      jet_corrector_H->process(event);
      topjet_corrector_H->process(event);
      topjet_puppi_corrector_H->process(event);
      jet_corrector_H->correct_met(event);
      topjet_subjet_corrector_H->process(event);
      topjet_puppi_subjet_corrector_H->process(event);
    }
  }
  //if (debug) cout << " jet correctors done" <<endl;
  else{ //MC
    if (debug) cout<<"JLC, JEC, JER done"<<endl;
    JLC_MC->process(event);
    if (debug) cout<< " JLC_MC done!"<<endl;
    TopJLC_MC->process(event);
    if (debug) cout<<"  TopJLC_MC done!"<<endl;
    TopJLC_puppi_MC->process(event);

    jet_corrector_MC->process(event);
    if (debug) cout<<" jet_corrector_MC done!"<<endl;
    topjet_corrector_MC->process(event);
    if (debug) cout<<" topjet_corrector_MC done!"<<endl;
    topjet_puppi_corrector_MC->process(event);
    if (debug) cout<<" topjet_puppi_corrector_MC done!"<<endl;
    if(JER_smearer.get()){
      if (debug) cout<<" Start JER_smearer "<<endl;
      JER_smearer->process(event);
    }
    if (debug) cout<<" JER_smearer done!"<<endl;
    if(TopJER_smearer.get()) TopJER_smearer->process(event);
    if (debug) cout<<" TopJER_smearer done!"<<endl;
    if(TopJER_puppi_smearer.get()) TopJER_puppi_smearer->process(event);
    if (debug) cout<<" TopJER_puppi_smearer done!"<<endl;
    jet_corrector_MC->correct_met(event);
    if (debug) cout<<" jet_corrector_MC done!"<<endl;
    topjet_subjet_corrector_MC->process(event);
    if (debug) cout<<" topjet_subjet_corrector_MC done!"<<endl;
    topjet_puppi_subjet_corrector_MC->process(event);
    if (debug) cout<<" topjet_puppi_subjet_corrector_MC done!"<<endl;
  }

  jet_cleaner1->process(event);
  sort_by_pt<Jet>(*event.jets);
  //fill_histograms(event, "JetCleaner1");
  if (debug) cout<<"JetCleaner1 ... "<<event.event<<endl;
  // Lepton-2Dcut variables
  for(auto& muo : *event.muons){

    float    dRmin, pTrel;
    std::tie(dRmin, pTrel) = drmin_pTrel(muo, *event.jets);

    muo.set_tag(Muon::twodcut_dRmin, dRmin);
    muo.set_tag(Muon::twodcut_pTrel, pTrel);
  }

  for(auto& ele : *event.electrons){

    float    dRmin, pTrel;
    std::tie(dRmin, pTrel) = drmin_pTrel(ele, *event.jets);

    ele.set_tag(Electron::twodcut_dRmin, dRmin);
    ele.set_tag(Electron::twodcut_pTrel, pTrel);
  }


  jet_cleaner2->process(event);
  sort_by_pt<Jet>(*event.jets);
  //fill_histograms(event, "JetCleaner2");
  if (debug) cout<<"JetCleaner2 ... "<<event.event<<endl;

  topjet_IDcleaner->process(event);
  topjet_cleaner->process(event);
  sort_by_pt<TopJet>(*event.topjets);

  topjet_puppi_IDcleaner->process(event);
  topjet_puppi_cleaner->process(event);
  sort_by_pt<TopJet>(*event.toppuppijets);
  //fill_histograms(event, "TopjetCleaner");
  if (debug) cout<<"TopjetCleaner Puppi ID ... "<<event.event<<endl;

  // 1st AK4 jet selection
  const bool pass_jet1 = jet1_sel->passes(event);
  if(!pass_jet1) return false;
  //fill_histograms(event, "Jet1");

  // 2nd AK4 jet selection
  const bool pass_jet2 = jet2_sel->passes(event);
  if(!pass_jet2) return false;
  //fill_histograms(event, "Jet2");

  // MET selection
  const bool pass_met = met_sel->passes(event);
  if(!pass_met) return false;
  //fill_histograms(event, "MET");
  if (debug) cout << "done with AK4 jets and MET" << endl;


////////////////////////////////////////////////
// Variables for NN
////////////////////////////////////////////////

  // General
  event.set(h_weight,event.weight);
  
  event.set(h_NPV,event.pvs->size());

  event.set(h_MET,event.met->pt());

  double st = 0., st_jets = 0., st_lep = 0.;
  vector<Jet>* jets = event.jets;
  vector<Electron>* electrons = event.electrons;
  vector<Muon>* muons = event.muons;
  for(unsigned int i=0; i<jets->size(); i++){
           st_jets += jets->at(i).pt();
  }
  for(unsigned int i=0; i<electrons->size(); i++){
           st_lep += electrons->at(i).pt();
  }
  for(unsigned int i=0; i<muons->size(); i++){
           st_lep += muons->at(i).pt();
  }
  st = st_jets + st_lep + event.met->pt();

  event.set(h_ST,st);
  event.set(h_STjets,st_jets);
  event.set(h_STlep,st_lep);
  
  if (debug) cout << " STlep done" << endl;

  // Ak4 jets
  event.set(h_N_jets,jets->size());
  if (debug) cout << " about to loop over AK4 jets" << endl;
  for(unsigned int i=0; i<jets->size(); i++){
    event.set(h_pt_jet,jets->at(i).pt());
    event.set(h_eta_jet,jets->at(i).eta());
    event.set(h_phi_jet,jets->at(i).phi());
    event.set(h_mass_jet,jets->at(i).v4().M());
   // event.set(h_csv_jet,jets->at(i).btag_combinedSecondaryVertex());

    double dRmin_muon_jet = 99999;
    for(unsigned int j=0; j<event.muons->size(); j++){
      double dR_mu_jet = deltaR(jets->at(i), event.muons->at(j));
      if(dR_mu_jet < dRmin_muon_jet) dRmin_muon_jet = dR_mu_jet;
      event.set(h_dR_mu_jet,dR_mu_jet);
    }

    double dRmin_ele_jet = 99999;
    for(unsigned int j=0; j<event.electrons->size(); j++){
      double dR_ele_jet = deltaR(jets->at(i), event.electrons->at(j));
      if(dR_ele_jet < dRmin_ele_jet) dRmin_ele_jet = dR_ele_jet;
      event.set(h_dR_ele_jet,dR_ele_jet);
    }

    if(i==0){
      event.set(h_pt_jet1,jets->at(i).pt());
      event.set(h_eta_jet1,jets->at(i).eta());
      event.set(h_phi_jet1,jets->at(i).phi());
      event.set(h_mass_jet1,jets->at(i).v4().M());
     // event.set(h_csv_jet1,jets->at(i).btag_combinedSecondaryVertex());
    }
    else if(i==1){
      event.set(h_pt_jet2,jets->at(i).pt());
      event.set(h_eta_jet2,jets->at(i).eta());
      event.set(h_phi_jet2,jets->at(i).phi());
      event.set(h_mass_jet2,jets->at(i).v4().M());
     // event.set(h_csv_jet2,jets->at(i).btag_combinedSecondaryVertex());
    }
    else if(i==2){
      event.set(h_pt_jet3,jets->at(i).pt());
      event.set(h_eta_jet3,jets->at(i).eta());
      event.set(h_phi_jet3,jets->at(i).phi());
      event.set(h_mass_jet3,jets->at(i).v4().M());
     // event.set(h_csv_jet3,jets->at(i).btag_combinedSecondaryVertex());
    }
  }
  if (debug) cout << " done with AK4 jets" <<endl;
  // Sphericity tensor
  double s11 = -1., s12 = -1., s13 = -1., s22 = -1., s23 = -1., s33 = -1., mag = -1.;
  for(const Jet jet : *event.jets){
    mag += (jet.v4().Px()*jet.v4().Px()+jet.v4().Py()*jet.v4().Py()+jet.v4().Pz()*jet.v4().Pz());
    s11 += jet.v4().Px()*jet.v4().Px();
    s12 += jet.v4().Px()*jet.v4().Py();
    s13 += jet.v4().Px()*jet.v4().Pz();
    s22 += jet.v4().Py()*jet.v4().Py();
    s23 += jet.v4().Py()*jet.v4().Pz();
    s33 += jet.v4().Pz()*jet.v4().Pz();
  }

  s11 = s11 / mag;
  s12 = s12 / mag;
  s13 = s13 / mag;
  s22 = s22 / mag;
  s23 = s23 / mag;
  s33 = s33 / mag;

  event.set(h_S11,s11);
  event.set(h_S12,s12);
  event.set(h_S13,s13);
  event.set(h_S22,s22);
  event.set(h_S23,s23);
  event.set(h_S33,s33);

  if (debug) cout << " done with sphericity tensors" <<endl;
  // Muons
  int Nmuons = muons->size();
  event.set(h_N_mu,Nmuons);

  for(int i=0; i<Nmuons; i++){

    event.set(h_pt_mu,muons->at(i).pt());
    event.set(h_eta_mu,muons->at(i).eta());
    event.set(h_phi_mu,muons->at(i).phi());
    event.set(h_reliso_mu,muons->at(i).relIso());
    if(muons->at(i).has_tag(Muon::twodcut_dRmin) && muons->at(i).has_tag(Muon::twodcut_pTrel)){
      event.set(h_dRmin_mu_jet,muons->at(i).get_tag(Muon::twodcut_dRmin));
      event.set(h_ptrel_mu_jet,muons->at(i).get_tag(Muon::twodcut_pTrel));
    }
  }


  // Electrons
  int Nelectrons = electrons->size();
  event.set(h_N_ele,Nelectrons);

  for(int i=0; i<Nelectrons; i++){

    event.set(h_pt_ele,electrons->at(i).pt());
    event.set(h_eta_ele,electrons->at(i).eta());
    event.set(h_phi_ele,electrons->at(i).phi());
    event.set(h_reliso_ele,electrons->at(i).relIso());
    if(electrons->at(i).has_tag(Electron::twodcut_dRmin) && electrons->at(i).has_tag(Electron::twodcut_pTrel)){
      event.set(h_dRmin_ele_jet,electrons->at(i).get_tag(Electron::twodcut_dRmin));
      event.set(h_ptrel_ele_jet,electrons->at(i).get_tag(Electron::twodcut_pTrel));
    }
  }

  if (debug) cout << "done with Leptons" <<endl;
  // Ak8 Puppi jets

  vector<TopJet>* AK8Puppijets = event.toppuppijets;
  if (debug) cout<< " number of AK8 jets" << AK8Puppijets->size()<< endl;
  unsigned int NAK8Puppijets = 0;
  for(unsigned int i=0; i<AK8Puppijets->size(); i++){
    if(AK8Puppijets->at(i).numberOfDaughters()<2) continue;
    NAK8Puppijets++;
  
    event.set(h_pt_Ak8Puppijets,AK8Puppijets->at(i).pt());
    event.set(h_eta_Ak8Puppijets,AK8Puppijets->at(i).eta());
    event.set(h_phi_Ak8Puppijets,AK8Puppijets->at(i).phi());
    event.set(h_mSD_Ak8Puppijets,AK8Puppijets->at(i).softdropmass());

    double dRmin_muon = 99999;
    for(unsigned int j=0; j<event.muons->size(); j++){
      double dR_mu = deltaR(AK8Puppijets->at(i), event.muons->at(j));
      if(dR_mu < dRmin_muon) dRmin_muon = dR_mu;
      event.set(h_dR_mu_Ak8Puppijet,dR_mu);
    }

    double dRmin_ele = 99999;
    for(unsigned int j=0; j<event.electrons->size(); j++){
      double dR_ele = deltaR(AK8Puppijets->at(i), event.electrons->at(j));
      if(dR_ele < dRmin_ele) dRmin_ele = dR_ele;
      event.set(h_dR_ele_Ak8Puppijet,dR_ele);
    }

    double dRmin_jet = 99999;
    for(unsigned int j=0; j<event.jets->size(); j++){
      double dR_jet = deltaR(AK8Puppijets->at(i), event.jets->at(j));
      if(dR_jet < dRmin_jet) dRmin_jet = dR_jet;
      event.set(h_dR_jet_Ak8Puppijet,dR_jet);
    }


    if(i==0){
      event.set(h_pt_Ak8Puppijet1,AK8Puppijets->at(i).pt());
      event.set(h_eta_Ak8Puppijet1,AK8Puppijets->at(i).eta());
      event.set(h_phi_Ak8Puppijet1,AK8Puppijets->at(i).phi());
      event.set(h_mSD_Ak8Puppijet1,AK8Puppijets->at(i).softdropmass());
    }

    if(i==1){
      event.set(h_pt_Ak8Puppijet2,AK8Puppijets->at(i).pt());
      event.set(h_eta_Ak8Puppijet2,AK8Puppijets->at(i).eta());
      event.set(h_phi_Ak8Puppijet2,AK8Puppijets->at(i).phi());
      event.set(h_mSD_Ak8Puppijet2,AK8Puppijets->at(i).softdropmass());
    }

    if(i==2){
      event.set(h_pt_Ak8Puppijet3,AK8Puppijets->at(i).pt());
      event.set(h_eta_Ak8Puppijet3,AK8Puppijets->at(i).eta());
      event.set(h_phi_Ak8Puppijet3,AK8Puppijets->at(i).phi());
      event.set(h_mSD_Ak8Puppijet3,AK8Puppijets->at(i).softdropmass());
    }

    event.set(h_N_Ak8Puppijets,NAK8Puppijets);
  }
  
  if (debug) cout << "done with Ak8 jets " <<endl;
  return true;

}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimePreselectionModule_DNN)
