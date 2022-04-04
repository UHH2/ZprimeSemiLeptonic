#include <iostream>
#include <memory>
#include <fstream>

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
#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/EventHists.h>
#include <UHH2/common/include/TopPtReweight.h>
#include <UHH2/common/include/CommonModules.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicMulticlassNNHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicCHSMatchHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

#include <UHH2/HOTVR/include/HadronicTop.h>
#include <UHH2/HOTVR/include/HOTVRScaleFactor.h>
#include <UHH2/HOTVR/include/HOTVRIds.h>

#include "UHH2/common/include/NeuralNetworkBase.hpp"

using namespace std;
using namespace uhh2;

/*
██████  ███████ ███████ ██ ███    ██ ██ ████████ ██  ██████  ███    ██
██   ██ ██      ██      ██ ████   ██ ██    ██    ██ ██    ██ ████   ██
██   ██ █████   █████   ██ ██ ██  ██ ██    ██    ██ ██    ██ ██ ██  ██
██   ██ ██      ██      ██ ██  ██ ██ ██    ██    ██ ██    ██ ██  ██ ██
██████  ███████ ██      ██ ██   ████ ██    ██    ██  ██████  ██   ████
*/


class NeuralNetworkModule: public NeuralNetworkBase {
public:
  explicit NeuralNetworkModule(uhh2::Context&, const std::string & ModelName, const std::string& ConfigName);
  virtual void CreateInputs(uhh2::Event & event) override;
protected:

  uhh2::Event::Handle<float> h_Ak4_j1_E;
  uhh2::Event::Handle<float> h_Ak4_j1_eta;
  uhh2::Event::Handle<float> h_Ak4_j1_m;
  uhh2::Event::Handle<float> h_Ak4_j1_phi;
  uhh2::Event::Handle<float> h_Ak4_j1_pt;
  uhh2::Event::Handle<float> h_Ak4_j1_deepjetbscore;

  uhh2::Event::Handle<float> h_Ak4_j2_E;
  uhh2::Event::Handle<float> h_Ak4_j2_eta;
  uhh2::Event::Handle<float> h_Ak4_j2_m;
  uhh2::Event::Handle<float> h_Ak4_j2_phi;
  uhh2::Event::Handle<float> h_Ak4_j2_pt;
  uhh2::Event::Handle<float> h_Ak4_j2_deepjetbscore;

  uhh2::Event::Handle<float> h_Ak4_j3_E;
  uhh2::Event::Handle<float> h_Ak4_j3_eta;
  uhh2::Event::Handle<float> h_Ak4_j3_m;
  uhh2::Event::Handle<float> h_Ak4_j3_phi;
  uhh2::Event::Handle<float> h_Ak4_j3_pt;
  uhh2::Event::Handle<float> h_Ak4_j3_deepjetbscore;

  uhh2::Event::Handle<float> h_Ak4_j4_E;
  uhh2::Event::Handle<float> h_Ak4_j4_eta;
  uhh2::Event::Handle<float> h_Ak4_j4_m;
  uhh2::Event::Handle<float> h_Ak4_j4_phi;
  uhh2::Event::Handle<float> h_Ak4_j4_pt;
  uhh2::Event::Handle<float> h_Ak4_j4_deepjetbscore;

  uhh2::Event::Handle<float> h_Ak4_j5_E;
  uhh2::Event::Handle<float> h_Ak4_j5_eta;
  uhh2::Event::Handle<float> h_Ak4_j5_m;
  uhh2::Event::Handle<float> h_Ak4_j5_phi;
  uhh2::Event::Handle<float> h_Ak4_j5_pt;
  uhh2::Event::Handle<float> h_Ak4_j5_deepjetbscore;

  uhh2::Event::Handle<float> h_Ak4_j6_E;
  uhh2::Event::Handle<float> h_Ak4_j6_eta;
  uhh2::Event::Handle<float> h_Ak4_j6_m;
  uhh2::Event::Handle<float> h_Ak4_j6_phi;
  uhh2::Event::Handle<float> h_Ak4_j6_pt;
  uhh2::Event::Handle<float> h_Ak4_j6_deepjetbscore;

  //Only Ele or Mu variables!!
  uhh2::Event::Handle<float> h_Ele_E;
  uhh2::Event::Handle<float> h_Ele_eta;
  uhh2::Event::Handle<float> h_Ele_phi;
  uhh2::Event::Handle<float> h_Ele_pt;

  uhh2::Event::Handle<float> h_MET_phi;
  uhh2::Event::Handle<float> h_MET_pt;

  //Only Ele or Mu variables!!
  uhh2::Event::Handle<float> h_Mu_E;
  uhh2::Event::Handle<float> h_Mu_eta;
  uhh2::Event::Handle<float> h_Mu_phi;
  uhh2::Event::Handle<float> h_Mu_pt;

  uhh2::Event::Handle<float> h_N_Ak4;

  uhh2::Event::Handle<float> h_Ak8_j1_E;
  uhh2::Event::Handle<float> h_Ak8_j1_eta;
  uhh2::Event::Handle<float> h_Ak8_j1_mSD;
  uhh2::Event::Handle<float> h_Ak8_j1_phi;
  uhh2::Event::Handle<float> h_Ak8_j1_pt;
  uhh2::Event::Handle<float> h_Ak8_j1_tau21;
  uhh2::Event::Handle<float> h_Ak8_j1_tau32;

  uhh2::Event::Handle<float> h_Ak8_j2_E;
  uhh2::Event::Handle<float> h_Ak8_j2_eta;
  uhh2::Event::Handle<float> h_Ak8_j2_mSD;
  uhh2::Event::Handle<float> h_Ak8_j2_phi;
  uhh2::Event::Handle<float> h_Ak8_j2_pt;
  uhh2::Event::Handle<float> h_Ak8_j2_tau21;
  uhh2::Event::Handle<float> h_Ak8_j2_tau32;

  uhh2::Event::Handle<float> h_Ak8_j3_E;
  uhh2::Event::Handle<float> h_Ak8_j3_eta;
  uhh2::Event::Handle<float> h_Ak8_j3_mSD;
  uhh2::Event::Handle<float> h_Ak8_j3_phi;
  uhh2::Event::Handle<float> h_Ak8_j3_pt;
  uhh2::Event::Handle<float> h_Ak8_j3_tau21;
  uhh2::Event::Handle<float> h_Ak8_j3_tau32;

  uhh2::Event::Handle<float> h_N_Ak8;

};


NeuralNetworkModule::NeuralNetworkModule(Context& ctx, const std::string & ModelName, const std::string& ConfigName): NeuralNetworkBase(ctx, ModelName, ConfigName){


  h_Ak4_j1_E   = ctx.get_handle<float>("Ak4_j1_E");
  h_Ak4_j1_eta = ctx.get_handle<float>("Ak4_j1_eta");
  h_Ak4_j1_m   = ctx.get_handle<float>("Ak4_j1_m");
  h_Ak4_j1_phi = ctx.get_handle<float>("Ak4_j1_phi");
  h_Ak4_j1_pt  = ctx.get_handle<float>("Ak4_j1_pt");
  h_Ak4_j1_deepjetbscore  = ctx.get_handle<float>("Ak4_j1_deepjetbscore");

  h_Ak4_j2_E   = ctx.get_handle<float>("Ak4_j2_E");
  h_Ak4_j2_eta = ctx.get_handle<float>("Ak4_j2_eta");
  h_Ak4_j2_m   = ctx.get_handle<float>("Ak4_j2_m");
  h_Ak4_j2_phi = ctx.get_handle<float>("Ak4_j2_phi");
  h_Ak4_j2_pt  = ctx.get_handle<float>("Ak4_j2_pt");
  h_Ak4_j2_deepjetbscore  = ctx.get_handle<float>("Ak4_j2_deepjetbscore");

  h_Ak4_j3_E   = ctx.get_handle<float>("Ak4_j3_E");
  h_Ak4_j3_eta = ctx.get_handle<float>("Ak4_j3_eta");
  h_Ak4_j3_m   = ctx.get_handle<float>("Ak4_j3_m");
  h_Ak4_j3_phi = ctx.get_handle<float>("Ak4_j3_phi");
  h_Ak4_j3_pt  = ctx.get_handle<float>("Ak4_j3_pt");
  h_Ak4_j3_deepjetbscore  = ctx.get_handle<float>("Ak4_j3_deepjetbscore");

  h_Ak4_j4_E   = ctx.get_handle<float>("Ak4_j4_E");
  h_Ak4_j4_eta = ctx.get_handle<float>("Ak4_j4_eta");
  h_Ak4_j4_m   = ctx.get_handle<float>("Ak4_j4_m");
  h_Ak4_j4_phi = ctx.get_handle<float>("Ak4_j4_phi");
  h_Ak4_j4_pt  = ctx.get_handle<float>("Ak4_j4_pt");
  h_Ak4_j4_deepjetbscore  = ctx.get_handle<float>("Ak4_j4_deepjetbscore");

  h_Ak4_j5_E   = ctx.get_handle<float>("Ak4_j5_E");
  h_Ak4_j5_eta = ctx.get_handle<float>("Ak4_j5_eta");
  h_Ak4_j5_m   = ctx.get_handle<float>("Ak4_j5_m");
  h_Ak4_j5_phi = ctx.get_handle<float>("Ak4_j5_phi");
  h_Ak4_j5_pt  = ctx.get_handle<float>("Ak4_j5_pt");
  h_Ak4_j5_deepjetbscore  = ctx.get_handle<float>("Ak4_j5_deepjetbscore");

  h_Ak4_j6_E   = ctx.get_handle<float>("Ak4_j6_E");
  h_Ak4_j6_eta = ctx.get_handle<float>("Ak4_j6_eta");
  h_Ak4_j6_m   = ctx.get_handle<float>("Ak4_j6_m");
  h_Ak4_j6_phi = ctx.get_handle<float>("Ak4_j6_phi");
  h_Ak4_j6_pt  = ctx.get_handle<float>("Ak4_j6_pt");
  h_Ak4_j6_deepjetbscore  = ctx.get_handle<float>("Ak4_j6_deepjetbscore");

  //Only Ele or Mu variables!!
  h_Ele_E    = ctx.get_handle<float>("Ele_E");
  h_Ele_eta  = ctx.get_handle<float>("Ele_eta");
  h_Ele_phi  = ctx.get_handle<float>("Ele_phi");
  h_Ele_pt   = ctx.get_handle<float>("Ele_pt");

  h_MET_phi = ctx.get_handle<float>("MET_phi");
  h_MET_pt = ctx.get_handle<float>("MET_pt");

  //Only Ele or Mu variables!!
  h_Mu_E    = ctx.get_handle<float>("Mu_E");
  h_Mu_eta  = ctx.get_handle<float>("Mu_eta");
  h_Mu_phi  = ctx.get_handle<float>("Mu_phi");
  h_Mu_pt   = ctx.get_handle<float>("Mu_pt");

  h_N_Ak4 = ctx.get_handle<float>("N_Ak4");

  h_Ak8_j1_E     = ctx.get_handle<float>("Ak8_j1_E");
  h_Ak8_j1_eta   = ctx.get_handle<float>("Ak8_j1_eta");
  h_Ak8_j1_mSD   = ctx.get_handle<float>("Ak8_j1_mSD");
  h_Ak8_j1_phi   = ctx.get_handle<float>("Ak8_j1_phi");
  h_Ak8_j1_pt    = ctx.get_handle<float>("Ak8_j1_pt");
  h_Ak8_j1_tau21 = ctx.get_handle<float>("Ak8_j1_tau21");
  h_Ak8_j1_tau32 = ctx.get_handle<float>("Ak8_j1_tau32");

  h_Ak8_j2_E     = ctx.get_handle<float>("Ak8_j2_E");
  h_Ak8_j2_eta   = ctx.get_handle<float>("Ak8_j2_eta");
  h_Ak8_j2_mSD   = ctx.get_handle<float>("Ak8_j2_mSD");
  h_Ak8_j2_phi   = ctx.get_handle<float>("Ak8_j2_phi");
  h_Ak8_j2_pt    = ctx.get_handle<float>("Ak8_j2_pt");
  h_Ak8_j2_tau21 = ctx.get_handle<float>("Ak8_j2_tau21");
  h_Ak8_j2_tau32 = ctx.get_handle<float>("Ak8_j2_tau32");

  h_Ak8_j3_E     = ctx.get_handle<float>("Ak8_j3_E");
  h_Ak8_j3_eta   = ctx.get_handle<float>("Ak8_j3_eta");
  h_Ak8_j3_mSD   = ctx.get_handle<float>("Ak8_j3_mSD");
  h_Ak8_j3_phi   = ctx.get_handle<float>("Ak8_j3_phi");
  h_Ak8_j3_pt    = ctx.get_handle<float>("Ak8_j3_pt");
  h_Ak8_j3_tau21 = ctx.get_handle<float>("Ak8_j3_tau21");
  h_Ak8_j3_tau32 = ctx.get_handle<float>("Ak8_j3_tau32");

  h_N_Ak8 = ctx.get_handle<float>("N_Ak8");

}

void NeuralNetworkModule::CreateInputs(Event & event){
  NNInputs.clear();
  NNoutputs.clear();

  string varname[65];
  string scal[65];
  string mean[65];
  string std[65];
  double mean_val[65];
  double std_val[65];
  //Only Ele or Mu variables!!
  // ifstream normfile ("/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL18_muon/NormInfo.txt", ios::in);
  ifstream normfile ("/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL18_ele/NormInfo.txt", ios::in);
  if(!normfile.good()) throw runtime_error("NeuralNetworkModule: The specified norm file does not exist.");
  if (normfile.is_open()){
    for(int i = 0; i < 65; ++i)
    {
      normfile >> varname[i] >> scal[i] >> mean[i] >> std[i];
      mean_val[i] = std::stod(mean[i]);
      std_val[i] = std::stod(std[i]);
    }
    normfile.close();
  }


  NNInputs.push_back( tensorflow::Tensor(tensorflow::DT_FLOAT, {1, 65}));


  //Only Ele or Mu variables!!

// vector<uhh2::Event::Handle<float>> inputs = { h_Ak4_j1_E, h_Ak4_j1_deepjetbscore, h_Ak4_j1_eta, h_Ak4_j1_m, h_Ak4_j1_phi, h_Ak4_j1_pt,h_Ak4_j2_E,h_Ak4_j2_deepjetbscore,h_Ak4_j2_eta,h_Ak4_j2_m,h_Ak4_j2_phi,h_Ak4_j2_pt,h_Ak4_j3_E,h_Ak4_j3_deepjetbscore,h_Ak4_j3_eta,h_Ak4_j3_m,h_Ak4_j3_phi, h_Ak4_j3_pt,  h_Ak4_j4_E, h_Ak4_j4_deepjetbscore,  h_Ak4_j4_eta, h_Ak4_j4_m,   h_Ak4_j4_phi, h_Ak4_j4_pt,  h_Ak4_j5_E, h_Ak4_j5_deepjetbscore,  h_Ak4_j5_eta, h_Ak4_j5_m,   h_Ak4_j5_phi, h_Ak4_j5_pt,  h_Ak4_j6_E, h_Ak4_j6_deepjetbscore,  h_Ak4_j6_eta, h_Ak4_j6_m,   h_Ak4_j6_phi, h_Ak4_j6_pt,  h_Ak8_j1_E,     h_Ak8_j1_eta,   h_Ak8_j1_mSD,   h_Ak8_j1_phi,   h_Ak8_j1_pt,    h_Ak8_j1_tau21, h_Ak8_j1_tau32, h_Ak8_j2_E,     h_Ak8_j2_eta,   h_Ak8_j2_mSD,   h_Ak8_j2_phi,   h_Ak8_j2_pt,    h_Ak8_j2_tau21, h_Ak8_j2_tau32, h_Ak8_j3_E,     h_Ak8_j3_eta,   h_Ak8_j3_mSD,   h_Ak8_j3_phi,h_Ak8_j3_pt,h_Ak8_j3_tau21,h_Ak8_j3_tau32,h_MET_phi,h_MET_pt,h_Mu_E,  h_Mu_eta,h_Mu_phi,h_Mu_pt, h_N_Ak4,h_N_Ak8 };
vector<uhh2::Event::Handle<float>> inputs = { h_Ak4_j1_E, h_Ak4_j1_deepjetbscore, h_Ak4_j1_eta, h_Ak4_j1_m, h_Ak4_j1_phi, h_Ak4_j1_pt,h_Ak4_j2_E,h_Ak4_j2_deepjetbscore,h_Ak4_j2_eta,h_Ak4_j2_m,h_Ak4_j2_phi,h_Ak4_j2_pt,h_Ak4_j3_E,h_Ak4_j3_deepjetbscore,h_Ak4_j3_eta,h_Ak4_j3_m,h_Ak4_j3_phi, h_Ak4_j3_pt,  h_Ak4_j4_E, h_Ak4_j4_deepjetbscore,  h_Ak4_j4_eta, h_Ak4_j4_m,   h_Ak4_j4_phi, h_Ak4_j4_pt,  h_Ak4_j5_E, h_Ak4_j5_deepjetbscore,  h_Ak4_j5_eta, h_Ak4_j5_m,   h_Ak4_j5_phi, h_Ak4_j5_pt,  h_Ak4_j6_E, h_Ak4_j6_deepjetbscore,  h_Ak4_j6_eta, h_Ak4_j6_m,   h_Ak4_j6_phi, h_Ak4_j6_pt,  h_Ak8_j1_E,     h_Ak8_j1_eta,   h_Ak8_j1_mSD,   h_Ak8_j1_phi,   h_Ak8_j1_pt,    h_Ak8_j1_tau21, h_Ak8_j1_tau32, h_Ak8_j2_E,     h_Ak8_j2_eta,   h_Ak8_j2_mSD,   h_Ak8_j2_phi,   h_Ak8_j2_pt,    h_Ak8_j2_tau21, h_Ak8_j2_tau32, h_Ak8_j3_E,     h_Ak8_j3_eta,   h_Ak8_j3_mSD,   h_Ak8_j3_phi,h_Ak8_j3_pt,h_Ak8_j3_tau21,h_Ak8_j3_tau32,h_Ele_E, h_Ele_eta, h_Ele_phi, h_Ele_pt, h_MET_phi,h_MET_pt,h_N_Ak4,h_N_Ak8 };

  for(int i = 0; i < 65; ++i){
    NNInputs.at(0).tensor<float, 2>()(0,i)  = (event.get(inputs.at(i))   - mean_val[i]) / (std_val[i]);
  }

  if (NNInputs.size()!=LayerInputs.size()) throw logic_error("NeuralNetworkModule.cxx: Create a number of inputs diffetent wrt. LayerInputs.size()="+to_string(LayerInputs.size()));
}



class ZprimeAnalysisModule_applyNN : public ModuleBASE {

public:
  explicit ZprimeAnalysisModule_applyNN(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

protected:

  bool debug;

  // Scale Factors -- Systematics
  unique_ptr<MCMuonScaleFactor> MuonID_module_low, MuonISO_module_low, MuonID_module_high, MuonTrigger_module_low, MuonTrigger_module_high;
  unique_ptr<MCElecScaleFactor> EleID_module, EleTrigger_module;

  // AnalysisModules
  unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, TopPtReweight_module, MCScale_module;
  unique_ptr<AnalysisModule> Corrections_module;
  unique_ptr<AnalysisModule> CustomBTagWeight_module;

  // Taggers
  unique_ptr<HOTVRTopTagger> TopTaggerHOTVR;
  unique_ptr<AnalysisModule> hadronic_top;
  unique_ptr<AnalysisModule> sf_toptag;
  unique_ptr<DeepAK8TopTagger> TopTaggerDeepAK8;

  // Mass reconstruction
  unique_ptr<ZprimeCandidateBuilder> CandidateBuilder;

  // Chi2 discriminator
  unique_ptr<ZprimeChi2Discriminator> Chi2DiscriminatorZprime;
  unique_ptr<ZprimeCorrectMatchDiscriminator> CorrectMatchDiscriminatorZprime;

  // Selections
  unique_ptr<Selection> MuonVeto_selection, EleVeto_selection, NMuon1_LowPt_selection, NMuon1_HighPt_selection, NEle1_LowPt_selection, NEle1_HighPt_selection;
  unique_ptr<Selection> Trigger_mu_A_selection, Trigger_mu_B_selection, Trigger_mu_C_selection, Trigger_mu_D_selection;
  unique_ptr<Selection> Trigger_ele_A_selection, Trigger_ele_B_selection, Trigger_ph_A_selection;
  unique_ptr<Selection> TwoDCut_selection, Jet1_selection, Jet2_selection, Met_selection, Chi2_selection1, Chi2_selection2, TTbarMatchable_selection, Chi2CandidateMatched_selection, ZprimeTopTag_selection, BlindData_selection;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<Selection> sel_1btag, sel_2btag;
  std::unique_ptr<Selection> TopJetBtagSubjet_selection;
  std::unique_ptr<Selection> HEM_selection;
  unique_ptr<Selection> ThetaStar_selection_bin1, ThetaStar_selection_bin2, ThetaStar_selection_bin3;

  // NN variables handles
  unique_ptr<Variables_NN> Variables_module;

  //Handles
  Event::Handle<bool> h_is_zprime_reconstructed_chi2, h_is_zprime_reconstructed_correctmatch;
  Event::Handle<float> h_chi2;   Event::Handle<float> h_weight;
  Event::Handle<float> h_MET;   Event::Handle<int> h_NPV;
  Event::Handle<float> h_lep1_pt; Event::Handle<float> h_lep1_eta;
  Event::Handle<float> h_ak4jet1_pt; Event::Handle<float> h_ak4jet1_eta;
  Event::Handle<float> h_ak8jet1_pt; Event::Handle<float> h_ak8jet1_eta;
  Event::Handle<float> h_Mttbar;

  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;

  // Set handles for mu iso sf - necessary for high pt muons, where no ISO SF are applied
  uhh2::Event::Handle<float> h_musf_iso;
  uhh2::Event::Handle<float> h_musf_iso_up;
  uhh2::Event::Handle<float> h_musf_iso_down;

  // Lumi hists
  std::unique_ptr<Hists> lumihists_Weights_Init, lumihists_Weights_PU, lumihists_Weights_Lumi, lumihists_Weights_TopPt, lumihists_Weights_MCScale, lumihists_Muon1_LowPt, lumihists_Muon1_HighPt, lumihists_Ele1_LowPt, lumihists_Ele1_HighPt, lumihists_TriggerMuon, lumihists_TriggerEle, lumihists_TwoDCut_Muon, lumihists_TwoDCut_Ele, lumihists_Jet1, lumihists_Jet2, lumihists_MET, lumihists_HTlep, lumihists_Chi2;


  float inv_mass(const LorentzVector& p4){ return p4.isTimelike() ? p4.mass() : -sqrt(-p4.mass2()); }

  // DNN multiclass output hist
  std::unique_ptr<Hists> h_MulticlassNN_output;

  // Configuration
  bool isMC, ishotvr, isdeepAK8, islooserselection;
  string Sys_MuonID_low, Sys_MuonISO_low, Sys_MuonID_high, Sys_MuonTrigger_low, Sys_MuonTrigger_high;
  string Sys_PU, Sys_btag, Sys_EleID, Sys_EleTrigger;
  TString sample;
  int runnr_oldtriggers = 299368;

  bool isUL16preVFP, isUL16postVFP, isUL17, isUL18;
  bool isMuon, isElectron;
  bool isPhoton;

  Event::Handle<float> h_Ak4_j1_E;
  Event::Handle<float> h_Ak4_j1_eta;
  Event::Handle<float> h_Ak4_j1_m;
  Event::Handle<float> h_Ak4_j1_phi;
  Event::Handle<float> h_Ak4_j1_pt;
  Event::Handle<float> h_Ak4_j1_deepjetbscore;

  Event::Handle<float> h_Ak4_j2_E;
  Event::Handle<float> h_Ak4_j2_eta;
  Event::Handle<float> h_Ak4_j2_m;
  Event::Handle<float> h_Ak4_j2_phi;
  Event::Handle<float> h_Ak4_j2_pt;
  Event::Handle<float> h_Ak4_j2_deepjetbscore;

  Event::Handle<float> h_Ak4_j3_E;
  Event::Handle<float> h_Ak4_j3_eta;
  Event::Handle<float> h_Ak4_j3_m;
  Event::Handle<float> h_Ak4_j3_phi;
  Event::Handle<float> h_Ak4_j3_pt;
  Event::Handle<float> h_Ak4_j3_deepjetbscore;

  Event::Handle<float> h_Ak4_j4_E;
  Event::Handle<float> h_Ak4_j4_eta;
  Event::Handle<float> h_Ak4_j4_m;
  Event::Handle<float> h_Ak4_j4_phi;
  Event::Handle<float> h_Ak4_j4_pt;
  Event::Handle<float> h_Ak4_j4_deepjetbscore;

  Event::Handle<float> h_Ak4_j5_E;
  Event::Handle<float> h_Ak4_j5_eta;
  Event::Handle<float> h_Ak4_j5_m;
  Event::Handle<float> h_Ak4_j5_phi;
  Event::Handle<float> h_Ak4_j5_pt;
  Event::Handle<float> h_Ak4_j5_deepjetbscore;

  Event::Handle<float> h_Ak4_j6_E;
  Event::Handle<float> h_Ak4_j6_eta;
  Event::Handle<float> h_Ak4_j6_m;
  Event::Handle<float> h_Ak4_j6_phi;
  Event::Handle<float> h_Ak4_j6_pt;
  Event::Handle<float> h_Ak4_j6_deepjetbscore;

  //Only Ele or Mu variables!!
  Event::Handle<float> h_Ele_E;
  Event::Handle<float> h_Ele_eta;
  Event::Handle<float> h_Ele_phi;
  Event::Handle<float> h_Ele_pt;

  Event::Handle<float> h_MET_phi;
  Event::Handle<float> h_MET_pt;

  //Only Ele or Mu variables!!
  Event::Handle<float> h_Mu_E;
  Event::Handle<float> h_Mu_eta;
  Event::Handle<float> h_Mu_phi;
  Event::Handle<float> h_Mu_pt;

  Event::Handle<float> h_N_Ak4;

  Event::Handle<float> h_Ak8_j1_E;
  Event::Handle<float> h_Ak8_j1_eta;
  Event::Handle<float> h_Ak8_j1_mSD;
  Event::Handle<float> h_Ak8_j1_phi;
  Event::Handle<float> h_Ak8_j1_pt;
  Event::Handle<float> h_Ak8_j1_tau21;
  Event::Handle<float> h_Ak8_j1_tau32;

  Event::Handle<float> h_Ak8_j2_E;
  Event::Handle<float> h_Ak8_j2_eta;
  Event::Handle<float> h_Ak8_j2_mSD;
  Event::Handle<float> h_Ak8_j2_phi;
  Event::Handle<float> h_Ak8_j2_pt;
  Event::Handle<float> h_Ak8_j2_tau21;
  Event::Handle<float> h_Ak8_j2_tau32;

  Event::Handle<float> h_Ak8_j3_E;
  Event::Handle<float> h_Ak8_j3_eta;
  Event::Handle<float> h_Ak8_j3_mSD;
  Event::Handle<float> h_Ak8_j3_phi;
  Event::Handle<float> h_Ak8_j3_pt;
  Event::Handle<float> h_Ak8_j3_tau21;
  Event::Handle<float> h_Ak8_j3_tau32;

  Event::Handle<float> h_N_Ak8;

  Event::Handle<std::vector<tensorflow::Tensor> > h_NNoutput;
  Event::Handle<double> h_NNoutput0;
  Event::Handle<double> h_NNoutput1;
  Event::Handle<double> h_NNoutput2;

  std::unique_ptr<NeuralNetworkModule> NNModule;

};

void ZprimeAnalysisModule_applyNN::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    string mytag = tag + "_Skimming";
    mytag = tag+"_General";
    book_HFolder(mytag, new ZprimeSemiLeptonicHists(ctx,mytag));
  }
}

void ZprimeAnalysisModule_applyNN::fill_histograms(uhh2::Event& event, string tag){
  string mytag = tag + "_Skimming";
  mytag = tag+"_General";
  HFolder(mytag)->fill(event);
}

/*
█  ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████
█ ██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█ ██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████
█ ██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█  ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

ZprimeAnalysisModule_applyNN::ZprimeAnalysisModule_applyNN(uhh2::Context& ctx){
  //  debug = true;
  debug = false;
  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }
  // Configuration
  isMC = (ctx.get("dataset_type") == "MC");
  ishotvr = (ctx.get("is_hotvr") == "true");
  isdeepAK8 = (ctx.get("is_deepAK8") == "true");
  TString mode = "hotvr";
  if(isdeepAK8) mode = "deepAK8";
  string tmp = ctx.get("dataset_version");
  sample = tmp;
  isUL16preVFP  = (ctx.get("dataset_version").find("UL16preVFP")  != std::string::npos);
  isUL16postVFP = (ctx.get("dataset_version").find("UL16postVFP") != std::string::npos);
  isUL17        = (ctx.get("dataset_version").find("UL17")        != std::string::npos);
  isUL18        = (ctx.get("dataset_version").find("UL18")        != std::string::npos);

  isPhoton = (ctx.get("dataset_version").find("SinglePhoton") != std::string::npos);

  // Important selection values
  islooserselection = (ctx.get("is_looser_selection") == "true");
  double jet1_pt(50.);
  double jet2_pt(30.);
  double chi2_max1(100.);
  double chi2_max2(30.);
  double mtt_blind(3000.);
  string trigger_mu_A, trigger_mu_B, trigger_mu_C, trigger_mu_D;
  string trigger_ele_A, trigger_ele_B;
  string trigger_ph_A;
  double MET_cut, HT_lep_cut;
  isMuon = false; isElectron = false;
  if(ctx.get("channel") == "muon") isMuon = true;
  if(ctx.get("channel") == "electron") isElectron = true;

  if(isMuon){//semileptonic muon channel
    if(isUL17){
      trigger_mu_A = "HLT_IsoMu27_v*";
    }
    else{
      trigger_mu_A = "HLT_IsoMu24_v*";
    }
    trigger_mu_B = "HLT_IsoTkMu24_v*";
    trigger_mu_C = "HLT_Mu50_v*";
    trigger_mu_D = "HLT_TkMu50_v*";

    MET_cut = 50;
    HT_lep_cut = 0;
  }
  if(isElectron){//semileptonic electron channel
    trigger_ele_B = "HLT_Ele115_CaloIdVT_GsfTrkIdT_v*";
    if(isUL16preVFP || isUL16postVFP){
      trigger_ele_A = "HLT_Ele27_WPTight_Gsf_v*";
    }
    if(isUL17){
      trigger_ele_A = "HLT_Ele35_WPTight_Gsf_v*";
    }
    if(isUL18){
      trigger_ele_A = "HLT_Ele32_WPTight_Gsf_v*";
    }
    if(isUL16preVFP || isUL16postVFP){
      trigger_ph_A = "HLT_Photon175_v*";
    }
    else{
      trigger_ph_A = "HLT_Photon200_v*";
    }
    MET_cut = 50;
    HT_lep_cut = 0;
  }


  double TwoD_dr = 0.4, TwoD_ptrel = 25.;
  if(islooserselection){
    jet1_pt = 100.;
    TwoD_dr = 0.2;
    TwoD_ptrel = 10.;
  }


  double electron_pt_low(35.);
  double muon_pt_low(30.);
  double electron_pt_high(120.);
  double muon_pt_high(55.);

  const MuonId muonID_low(PtEtaCut(muon_pt_low, 2.4));
  const ElectronId electronID_low(PtEtaSCCut(electron_pt_low, 2.5));
  const MuonId muonID_high(PtEtaCut(muon_pt_high, 2.4));
  const ElectronId electronID_high(PtEtaSCCut(electron_pt_high, 2.5));
  const TopJetId toptagID = AndId<TopJet>(HOTVRTopTag(0.8, 140.0, 220.0, 50.0), Tau32Groomed(0.56));

  Sys_MuonID_low = ctx.get("Sys_MuonID_low");
  Sys_MuonISO_low = ctx.get("Sys_MuonISO_low");
  Sys_MuonID_high = ctx.get("Sys_MuonID_high");
  Sys_MuonTrigger_low = ctx.get("Sys_MuonTrigger_low");
  Sys_MuonTrigger_high = ctx.get("Sys_MuonTrigger_high");
  Sys_EleID = ctx.get("Sys_EleID");
  Sys_EleTrigger = ctx.get("Sys_EleTrigger");
  Sys_PU = ctx.get("Sys_PU");
  Sys_btag = ctx.get("Sys_btag");

  BTag::algo btag_algo = BTag::DEEPJET;
  BTag::wp btag_wp = BTag::WP_MEDIUM;
  JetId id_btag = BTag(btag_algo, btag_wp);

  double a_toppt = 0.0615; // par a TopPt Reweighting
  double b_toppt = -0.0005; // par b TopPt Reweighting

  // Modules
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  TopPtReweight_module.reset(new TopPtReweighting(ctx, a_toppt, b_toppt, ctx.get("Systematic_TopPt_a", "nominal"), ctx.get("Systematic_TopPt_b", "nominal"), "", ""));
  MCScale_module.reset(new MCScaleVariation(ctx));
  hadronic_top.reset(new HadronicTop(ctx));
  //sf_toptag.reset(new HOTVRScaleFactor(ctx, toptagID, ctx.get("Sys_TopTag", "nominal"), "HadronicTop", "TopTagSF", "HOTVRTopTagSFs"));
  Corrections_module.reset(new NLOCorrections(ctx));
  //CustomBTagWeight_module.reset(new CustomMCBTagDiscriminantReweighting(ctx, btag_algo, "jets", Sys_btag,"iterativefit","","BTagCalibration"));

  if((isUL16preVFP || isUL16postVFP) && isMuon){
    MuonID_module_low      .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root"     , "NUM_TightID_DEN_genTracks_eta_pt"              , 1.0, "tightID"  , false, Sys_MuonID_low));
    MuonISO_module_low     .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonIso_EfficienciesAndSF_average_RunBtoH.root"    , "NUM_TightRelIso_DEN_TightIDandIPCut_eta_pt"    , 1.0, "isolation", false, Sys_MuonISO_low));
    MuonID_module_high     .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root"     , "NUM_TightID_DEN_genTracks_eta_pt"              , 1.0, "tightID"  , false, Sys_MuonID_high));
    MuonTrigger_module_low .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu24_OR_IsoTkMu24_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger"  , true , Sys_MuonTrigger_low));
    MuonTrigger_module_high.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu50_OR_IsoTkMu50_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger"  , true , Sys_MuonTrigger_high));
  }

  if(isUL17 && isMuon){
    MuonID_module_low      .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2017/MuonID_94X_RunBCDEF_SF_ID.root"                         , "NUM_TightID_DEN_genTracks_pt_abseta"          , 1.0, "tightID"  , true, Sys_MuonID_low));
    MuonISO_module_low     .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2017/MuonIso_94X_RunBCDEF_SF_ISO.root"                       , "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta", 1.0, "isolation", true, Sys_MuonISO_low));
    MuonID_module_high     .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2017/MuonID_94X_RunBCDEF_SF_ID.root"                         , "NUM_TightID_DEN_genTracks_pt_abseta"          , 1.0, "tightID"  , true, Sys_MuonID_high));
    MuonTrigger_module_low .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2017/MuonTrigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "IsoMu27_PtEtaBins/pt_abseta_ratio"            , 0.5, "Trigger"  , true, Sys_MuonTrigger_low));
    MuonTrigger_module_high.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2017/MuonTrigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "Mu50_PtEtaBins/pt_abseta_ratio"               , 0.5, "Trigger"  , true, Sys_MuonTrigger_high));
  }

  if(isUL18 && isMuon){
    MuonID_module_low      .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/Muon_ID_SF_RunABCD.root"                    , "NUM_TightID_DEN_TrackerMuons_pt_abseta"               , 1.0, "tightID"  , true, Sys_MuonID_low));
    MuonISO_module_low     .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/Muon_Iso_SF_RunABCD.root"                   , "NUM_TightRelIso_DEN_TightIDandIPCut_pt_abseta"        , 0.0, "isolation", true, Sys_MuonISO_low));
    MuonID_module_high     .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/Muon_ID_SF_RunABCD.root"                    , "NUM_TightID_DEN_TrackerMuons_pt_abseta"               , 1.0, "tightID"  , true, Sys_MuonID_high));
    MuonTrigger_module_low .reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/Muon_Trigger_Eff_SF_AfterMuonHLTUpdate.root", "IsoMu24_PtEtaBins/pt_abseta_ratio"                    , 0.5, "Trigger"  , true, Sys_MuonTrigger_low));
    MuonTrigger_module_high.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/Muon_Trigger_Eff_SF_AfterMuonHLTUpdate.root", "Mu50_OR_OldMu100_OR_TkMu100_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger"  , true, Sys_MuonTrigger_high));
  }

  if((isUL16preVFP || isUL16postVFP) && isElectron){
    EleID_module.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2016/egammaEffi.txt_EGM2D_CutBased_Tight_ID.root", 0., "TightID", Sys_EleID));
    // EleTrigger_module.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/SF_2018.root", 0.5, "Trigger", Sys_EleTrigger));
  }
  if(isUL17 && isElectron){
    EleID_module.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2017/2017_ElectronTight.root", 0., "TightID", Sys_EleID));
    // EleTrigger_module.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/SF_2018.root", 0.5, "Trigger", Sys_EleTrigger));
  }
  if(isUL18 && isElectron){
    EleID_module.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/2018_ElectronTight.root", 0., "TightID", Sys_EleID));
    // EleTrigger_module.reset(new MCElecScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/RunII_102X_v2/CMSSW_10_2_17/src/UHH2/common/data/2018/SF_2018.root", 0.5, "Trigger", Sys_EleTrigger));
  }


  // Selection modules
  MuonVeto_selection.reset(new NMuonSelection(0, 0));
  EleVeto_selection.reset(new NElectronSelection(0, 0));
  NMuon1_LowPt_selection.reset(new NMuonSelection(1, 1, muonID_low));
  NMuon1_HighPt_selection.reset(new NMuonSelection(1, 1, muonID_high));
  NEle1_LowPt_selection.reset(new NElectronSelection(1, 1, electronID_low));
  NEle1_HighPt_selection.reset(new NElectronSelection(1, 1, electronID_high));

  Trigger_mu_A_selection.reset(new TriggerSelection(trigger_mu_A));
  Trigger_mu_B_selection.reset(new TriggerSelection(trigger_mu_B));
  Trigger_mu_C_selection.reset(new TriggerSelection(trigger_mu_C));
  Trigger_mu_D_selection.reset(new TriggerSelection(trigger_mu_D));

  Trigger_ele_A_selection.reset(new TriggerSelection(trigger_ele_A));
  Trigger_ele_B_selection.reset(new TriggerSelection(trigger_ele_B));
  Trigger_ph_A_selection.reset(new TriggerSelection(trigger_ph_A));


  TwoDCut_selection.reset(new TwoDCut(TwoD_dr, TwoD_ptrel));
  Jet1_selection.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  Jet2_selection.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  met_sel.reset(new METCut  (MET_cut   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep_cut, uhh2::infinity));

  Chi2_selection1.reset(new Chi2Cut(ctx, 0., chi2_max1));
  Chi2_selection2.reset(new Chi2Cut(ctx, 0., chi2_max2));
  TTbarMatchable_selection.reset(new TTbarSemiLepMatchableSelection());
  Chi2CandidateMatched_selection.reset(new Chi2CandidateMatchedSelection(ctx));
  ZprimeTopTag_selection.reset(new ZprimeTopTagSelection(ctx));
  BlindData_selection.reset(new BlindDataSelection(ctx, mtt_blind));

  HEM_selection.reset(new HEMSelection(ctx)); // HEM issue in 2018, veto on leptons and jets

  Variables_module.reset(new Variables_NN(ctx, mode)); // variables for NN

  // Selections on scattering angle theta star
  double theta_bin1(0.5);
  ThetaStar_selection_bin1.reset(new ThetaStarSelection(ctx, theta_bin1));
  double theta_bin2(0.7);
  ThetaStar_selection_bin2.reset(new ThetaStarSelection(ctx, theta_bin2));
  double theta_bin3(0.9);
  ThetaStar_selection_bin3.reset(new ThetaStarSelection(ctx, theta_bin3));

  // Taggers
  TopTaggerHOTVR.reset(new HOTVRTopTagger(ctx));
  TopTaggerDeepAK8.reset(new DeepAK8TopTagger(ctx));

  // Zprime candidate builder
  CandidateBuilder.reset(new ZprimeCandidateBuilder(ctx, mode));

  // Zprime discriminators
  Chi2DiscriminatorZprime.reset(new ZprimeChi2Discriminator(ctx));
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  CorrectMatchDiscriminatorZprime.reset(new ZprimeCorrectMatchDiscriminator(ctx));
  h_is_zprime_reconstructed_correctmatch = ctx.get_handle<bool>("is_zprime_reconstructed_correctmatch");
  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_chi2 = ctx.declare_event_output<float> ("rec_chi2");
  h_MET = ctx.declare_event_output<float> ("met_pt");
  h_Mttbar = ctx.declare_event_output<float> ("Mttbar");
  h_lep1_pt = ctx.declare_event_output<float> ("lep1_pt");
  h_lep1_eta = ctx.declare_event_output<float> ("lep1_eta");
  h_ak4jet1_pt = ctx.declare_event_output<float> ("ak4jet1_pt");
  h_ak4jet1_eta = ctx.declare_event_output<float> ("ak4jet1_eta");
  h_ak8jet1_pt = ctx.declare_event_output<float> ("ak8jet1_pt");
  h_ak8jet1_eta = ctx.declare_event_output<float> ("ak8jet1_eta");

  h_NPV = ctx.declare_event_output<int> ("NPV");
  h_weight = ctx.declare_event_output<float> ("weight");

  sel_1btag.reset(new NJetSelection(1, -1, id_btag));
  sel_2btag.reset(new NJetSelection(2,-1, id_btag));

  h_musf_iso      = ctx.declare_event_output<float>("weight_sfmu_isolation");
  h_musf_iso_up   = ctx.declare_event_output<float>("weight_sfmu_isolation_up");
  h_musf_iso_down = ctx.declare_event_output<float>("weight_sfmu_isolation_down");

  TopJetBtagSubjet_selection.reset(new ZprimeBTagFatSubJetSelection(ctx));

  // Book histograms
 vector<string> histogram_tags = {"Weights_Init", "Weights_PU", "Weights_Lumi", "Weights_TopPt", "Weights_MCScale", "Weights_TopTag_SF", "Corrections", "IDMuon_SF", "IsoMuon_SF", "Muon1_LowPt", "Muon1_HighPt", "Ele1_LowPt", "Ele1_HighPt", "TriggerMuon_SF", "TriggerMuon", "TriggerEle", "TwoDCut_Muon", "TwoDCut_Ele", "Jet1", "Jet2", "MET", "HTlep","Btags1", "Btags1_SF", "NNInputsBeforeReweight","DNN_output0","DNN_output1","DNN_output2","DNN_output0_TopTag","DNN_output1_TopTag","DNN_output2_TopTag","DNN_output0_NoTopTag","DNN_output1_NoTopTag","DNN_output2_NoTopTag", "DNN_output0_thetastar_bin1", "DNN_output0_thetastar_bin2", "DNN_output0_thetastar_bin3", "DNN_output0_thetastar_bin4", "DNN_output0_TopTag_thetastar_bin1", "DNN_output0_TopTag_thetastar_bin2", "DNN_output0_TopTag_thetastar_bin3", "DNN_output0_TopTag_thetastar_bin4", "DNN_output0_NoTopTag_thetastar_bin1", "DNN_output0_NoTopTag_thetastar_bin2", "DNN_output0_NoTopTag_thetastar_bin3", "DNN_output0_NoTopTag_thetastar_bin4", "DNN_output0_TopTag_chi2_max1", "DNN_output0_NoTopTag_chi2_max1", "DNN_output0_TopTag_chi2_max2", "DNN_output0_NoTopTag_chi2_max2", "DNN_output0_thetastar_bin1_chi2_max1", "DNN_output0_thetastar_bin2_chi2_max1", "DNN_output0_thetastar_bin3_chi2_max1", "DNN_output0_thetastar_bin4_chi2_max1", "DNN_output0_TopTag_thetastar_bin1_chi2_max1", "DNN_output0_TopTag_thetastar_bin2_chi2_max1", "DNN_output0_TopTag_thetastar_bin3_chi2_max1", "DNN_output0_TopTag_thetastar_bin4_chi2_max1", "DNN_output0_NoTopTag_thetastar_bin1_chi2_max1", "DNN_output0_NoTopTag_thetastar_bin2_chi2_max1", "DNN_output0_NoTopTag_thetastar_bin3_chi2_max1", "DNN_output0_NoTopTag_thetastar_bin4_chi2_max1", "DNN_output0_thetastar_bin1_chi2_max2", "DNN_output0_thetastar_bin2_chi2_max2", "DNN_output0_thetastar_bin3_chi2_max2", "DNN_output0_thetastar_bin4_chi2_max2", "DNN_output0_TopTag_thetastar_bin1_chi2_max2", "DNN_output0_TopTag_thetastar_bin2_chi2_max2", "DNN_output0_TopTag_thetastar_bin3_chi2_max2", "DNN_output0_TopTag_thetastar_bin4_chi2_max2", "DNN_output0_NoTopTag_thetastar_bin1_chi2_max2", "DNN_output0_NoTopTag_thetastar_bin2_chi2_max2", "DNN_output0_NoTopTag_thetastar_bin3_chi2_max2", "DNN_output0_NoTopTag_thetastar_bin4_chi2_max2", "DNN_output0_chi2_max1", "DNN_output0_Nochi2_max1", "DNN_output0_NoTopTag_Nochi2_max1", "DNN_output0_TopTag_Nochi2_max1"};
  book_histograms(ctx, histogram_tags);

  h_MulticlassNN_output.reset(new ZprimeSemiLeptonicMulticlassNNHists(ctx, "MulticlassNN"));

  lumihists_Weights_Init.reset(new LuminosityHists(ctx, "Lumi_Weights_Init"));
  lumihists_Weights_PU.reset(new LuminosityHists(ctx, "Lumi_Weights_PU"));
  lumihists_Weights_Lumi.reset(new LuminosityHists(ctx, "Lumi_Weights_Lumi"));
  lumihists_Weights_TopPt.reset(new LuminosityHists(ctx, "Lumi_Weights_TopPt"));
  lumihists_Weights_MCScale.reset(new LuminosityHists(ctx, "Lumi_Weights_MCScale"));
  lumihists_Muon1_LowPt.reset(new LuminosityHists(ctx, "Lumi_Muon1_LowPt"));
  lumihists_Muon1_HighPt.reset(new LuminosityHists(ctx, "Lumi_Muon1_HighPt"));
  lumihists_Ele1_LowPt.reset(new LuminosityHists(ctx, "Lumi_Ele1_LowPt"));
  lumihists_Ele1_HighPt.reset(new LuminosityHists(ctx, "Lumi_Ele1_HighPt"));
  lumihists_TriggerMuon.reset(new LuminosityHists(ctx, "Lumi_TriggerMuon"));
  lumihists_TriggerEle.reset(new LuminosityHists(ctx, "Lumi_TriggerEle"));
  lumihists_TwoDCut_Muon.reset(new LuminosityHists(ctx, "Lumi_TwoDCut_Muon"));
  lumihists_TwoDCut_Ele.reset(new LuminosityHists(ctx, "Lumi_TwoDCut_Ele"));
  lumihists_Jet1.reset(new LuminosityHists(ctx, "Lumi_Jet1"));
  lumihists_Jet2.reset(new LuminosityHists(ctx, "Lumi_Jet2"));
  lumihists_MET.reset(new LuminosityHists(ctx, "Lumi_MET"));
  lumihists_HTlep.reset(new LuminosityHists(ctx, "Lumi_HTlep"));
  lumihists_Chi2.reset(new LuminosityHists(ctx, "Lumi_Chi2"));

  h_Ak4_j1_E   = ctx.get_handle<float>("Ak4_j1_E");
  h_Ak4_j1_eta = ctx.get_handle<float>("Ak4_j1_eta");
  h_Ak4_j1_m   = ctx.get_handle<float>("Ak4_j1_m");
  h_Ak4_j1_phi = ctx.get_handle<float>("Ak4_j1_phi");
  h_Ak4_j1_pt  = ctx.get_handle<float>("Ak4_j1_pt");
  h_Ak4_j1_deepjetbscore  = ctx.get_handle<float>("Ak4_j1_deepjetbscore");

  h_Ak4_j2_E   = ctx.get_handle<float>("Ak4_j2_E");
  h_Ak4_j2_eta = ctx.get_handle<float>("Ak4_j2_eta");
  h_Ak4_j2_m   = ctx.get_handle<float>("Ak4_j2_m");
  h_Ak4_j2_phi = ctx.get_handle<float>("Ak4_j2_phi");
  h_Ak4_j2_pt  = ctx.get_handle<float>("Ak4_j2_pt");
  h_Ak4_j2_deepjetbscore  = ctx.get_handle<float>("Ak4_j2_deepjetbscore");

  h_Ak4_j3_E   = ctx.get_handle<float>("Ak4_j3_E");
  h_Ak4_j3_eta = ctx.get_handle<float>("Ak4_j3_eta");
  h_Ak4_j3_m   = ctx.get_handle<float>("Ak4_j3_m");
  h_Ak4_j3_phi = ctx.get_handle<float>("Ak4_j3_phi");
  h_Ak4_j3_pt  = ctx.get_handle<float>("Ak4_j3_pt");
  h_Ak4_j3_deepjetbscore  = ctx.get_handle<float>("Ak4_j3_deepjetbscore");

  h_Ak4_j4_E   = ctx.get_handle<float>("Ak4_j4_E");
  h_Ak4_j4_eta = ctx.get_handle<float>("Ak4_j4_eta");
  h_Ak4_j4_m   = ctx.get_handle<float>("Ak4_j4_m");
  h_Ak4_j4_phi = ctx.get_handle<float>("Ak4_j4_phi");
  h_Ak4_j4_pt  = ctx.get_handle<float>("Ak4_j4_pt");
  h_Ak4_j4_deepjetbscore  = ctx.get_handle<float>("Ak4_j4_deepjetbscore");

  h_Ak4_j5_E   = ctx.get_handle<float>("Ak4_j5_E");
  h_Ak4_j5_eta = ctx.get_handle<float>("Ak4_j5_eta");
  h_Ak4_j5_m   = ctx.get_handle<float>("Ak4_j5_m");
  h_Ak4_j5_phi = ctx.get_handle<float>("Ak4_j5_phi");
  h_Ak4_j5_pt  = ctx.get_handle<float>("Ak4_j5_pt");
  h_Ak4_j5_deepjetbscore  = ctx.get_handle<float>("Ak4_j5_deepjetbscore");

  h_Ak4_j6_E   = ctx.get_handle<float>("Ak4_j6_E");
  h_Ak4_j6_eta = ctx.get_handle<float>("Ak4_j6_eta");
  h_Ak4_j6_m   = ctx.get_handle<float>("Ak4_j6_m");
  h_Ak4_j6_phi = ctx.get_handle<float>("Ak4_j6_phi");
  h_Ak4_j6_pt  = ctx.get_handle<float>("Ak4_j6_pt");
  h_Ak4_j6_deepjetbscore  = ctx.get_handle<float>("Ak4_j6_deepjetbscore");

  //Only Ele or Mu variables!!
  h_Ele_E    = ctx.get_handle<float>("Ele_E");
  h_Ele_eta  = ctx.get_handle<float>("Ele_eta");
  h_Ele_phi  = ctx.get_handle<float>("Ele_phi");
  h_Ele_pt   = ctx.get_handle<float>("Ele_pt");

  h_MET_phi = ctx.get_handle<float>("MET_phi");
  h_MET_pt = ctx.get_handle<float>("MET_pt");

  //Only Ele or Mu variables!!
  h_Mu_E    = ctx.get_handle<float>("Mu_E");
  h_Mu_eta  = ctx.get_handle<float>("Mu_eta");
  h_Mu_phi  = ctx.get_handle<float>("Mu_phi");
  h_Mu_pt   = ctx.get_handle<float>("Mu_pt");

  h_N_Ak4 = ctx.get_handle<float>("N_Ak4");

  h_Ak8_j1_E     = ctx.get_handle<float>("Ak8_j1_E");
  h_Ak8_j1_eta   = ctx.get_handle<float>("Ak8_j1_eta");
  h_Ak8_j1_mSD   = ctx.get_handle<float>("Ak8_j1_mSD");
  h_Ak8_j1_phi   = ctx.get_handle<float>("Ak8_j1_phi");
  h_Ak8_j1_pt    = ctx.get_handle<float>("Ak8_j1_pt");
  h_Ak8_j1_tau21 = ctx.get_handle<float>("Ak8_j1_tau21");
  h_Ak8_j1_tau32 = ctx.get_handle<float>("Ak8_j1_tau32");

  h_Ak8_j2_E     = ctx.get_handle<float>("Ak8_j2_E");
  h_Ak8_j2_eta   = ctx.get_handle<float>("Ak8_j2_eta");
  h_Ak8_j2_mSD   = ctx.get_handle<float>("Ak8_j2_mSD");
  h_Ak8_j2_phi   = ctx.get_handle<float>("Ak8_j2_phi");
  h_Ak8_j2_pt    = ctx.get_handle<float>("Ak8_j2_pt");
  h_Ak8_j2_tau21 = ctx.get_handle<float>("Ak8_j2_tau21");
  h_Ak8_j2_tau32 = ctx.get_handle<float>("Ak8_j2_tau32");

  h_Ak8_j3_E     = ctx.get_handle<float>("Ak8_j3_E");
  h_Ak8_j3_eta   = ctx.get_handle<float>("Ak8_j3_eta");
  h_Ak8_j3_mSD   = ctx.get_handle<float>("Ak8_j3_mSD");
  h_Ak8_j3_phi   = ctx.get_handle<float>("Ak8_j3_phi");
  h_Ak8_j3_pt    = ctx.get_handle<float>("Ak8_j3_pt");
  h_Ak8_j3_tau21 = ctx.get_handle<float>("Ak8_j3_tau21");
  h_Ak8_j3_tau32 = ctx.get_handle<float>("Ak8_j3_tau32");

  h_N_Ak8 = ctx.get_handle<float>("N_Ak8");

  h_NNoutput = ctx.get_handle<std::vector<tensorflow::Tensor>>("NNoutput");
  h_NNoutput0 = ctx.declare_event_output<double>("NNoutput0");
  h_NNoutput1 = ctx.declare_event_output<double>("NNoutput1");
  h_NNoutput2 = ctx.declare_event_output<double>("NNoutput2");
  ////Only Ele or Mu variables!!
  // NNModule.reset( new NeuralNetworkModule(ctx, "/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL18_muon/model.pb", "/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL18_muon/model.config.pbtxt"));
  NNModule.reset( new NeuralNetworkModule(ctx, "/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL18_ele/model.pb", "/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL18_ele/model.config.pbtxt"));

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeAnalysisModule_applyNN::process(uhh2::Event& event){

  if(debug)   cout << "++++++++++++ NEW EVENT ++++++++++++++" << endl;
  if(debug)   cout<<" run.event: "<<event.run<<". "<<event.event<<endl;
  // Initialize reco flags with false
  event.set(h_is_zprime_reconstructed_chi2, false);
  event.set(h_is_zprime_reconstructed_correctmatch, false);
  event.set(h_chi2,-100);
  event.set(h_MET,-100);
  event.set(h_Mttbar,-100);
  event.set(h_lep1_pt,-100);
  event.set(h_lep1_eta,-100);
  event.set(h_ak4jet1_pt,-100);
  event.set(h_ak4jet1_eta,-100);
  event.set(h_ak8jet1_pt,-100);
  event.set(h_ak8jet1_eta,-100);
  event.set(h_NPV,-100);
  event.set(h_weight,-100);

  event.set(h_NNoutput0, 0);
  event.set(h_NNoutput1, 0);
  event.set(h_NNoutput2, 0);

  if(!HEM_selection->passes(event)){
    if(!isMC) return false;
    else event.weight = event.weight*(1-0.64774715284); // calculated following instructions ar https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2018Analysis
  }

  // Run top-tagging
  if(ishotvr){
  TopTaggerHOTVR->process(event);
  hadronic_top->process(event);
  }else if(isdeepAK8){
  TopTaggerDeepAK8->process(event);
  }
  if(debug) cout<<"Top Tagger ok"<<endl;

  fill_histograms(event, "Weights_Init");
  lumihists_Weights_Init->fill(event);

  // Weight modules
  PUWeight_module->process(event);
  if(debug)  cout<<"PUWeight ok"<<endl;
  fill_histograms(event, "Weights_PU");
  lumihists_Weights_PU->fill(event);

  LumiWeight_module->process(event);
  if(debug)  cout<<"LumiWeight ok"<<endl;
  fill_histograms(event, "Weights_Lumi");
  lumihists_Weights_Lumi->fill(event);

  TopPtReweight_module->process(event);
  fill_histograms(event, "Weights_TopPt");
  lumihists_Weights_TopPt->fill(event);

  MCScale_module->process(event);
  fill_histograms(event, "Weights_MCScale");
  lumihists_Weights_MCScale->fill(event);

  // HOTVR TopTag SFs
  //if(ishotvr) sf_toptag->process(event);
  //fill_histograms(event, "Weights_TopTag_SF");

  // Higher order corrections - EWK & QCD NLO
  Corrections_module->process(event);
  fill_histograms(event, "Corrections");

  // Select exactly 1 muon or 1 electron
  bool muon_is_low = false;
  bool muon_is_high = false;
  bool ele_is_low = false;
  bool ele_is_high = false;

  if(isMuon){
    if(!EleVeto_selection->passes(event)) return false;
    if(!NMuon1_HighPt_selection->passes(event)){
      if(NMuon1_LowPt_selection->passes(event)){
        muon_is_low = true;
        fill_histograms(event, "Muon1_LowPt");
        lumihists_Muon1_LowPt->fill(event);
      }
    }
    else{
      muon_is_high = true;
      fill_histograms(event, "Muon1_HighPt");
      lumihists_Muon1_HighPt->fill(event);
    }
    if( !(muon_is_high || muon_is_low) ) return false;
  }
  if(isElectron){
    if(!MuonVeto_selection->passes(event)) return false;
    if(!NEle1_HighPt_selection->passes(event)){
      if(NEle1_LowPt_selection->passes(event)){
        ele_is_low = true;
        fill_histograms(event, "Ele1_LowPt");
        lumihists_Ele1_LowPt->fill(event);
      }
    }
    else{
      ele_is_high = true;
      fill_histograms(event, "Ele1_HighPt");
      lumihists_Ele1_HighPt->fill(event);
    }
    if( !(ele_is_high || ele_is_low) ) return false;
  }

  // Lepton ID SF
  if(isMuon){
    // low pt
    if(muon_is_low){
      MuonID_module_low->process(event);
    }
    // high pt
    if(muon_is_high){
      MuonID_module_high->process(event);
    }
    fill_histograms(event, "IDMuon_SF");
  }
  if(isElectron){
    EleID_module->process(event);
    if(debug)  cout<<"EleID ok"<<endl;
  }


  // Muon ISO SF
  if(isMuon){  // high pt
    event.set(h_musf_iso, 1.);
    event.set(h_musf_iso_up, 1.);
    event.set(h_musf_iso_down, 1.);
    if(muon_is_low){ // low pt
      MuonISO_module_low->process(event);
    }
    fill_histograms(event, "IsoMuon_SF");
  }
  // dummy for ele channel
  if(isElectron){
    event.set(h_musf_iso, 1.);
    event.set(h_musf_iso_up, 1.);
    event.set(h_musf_iso_down, 1.);
  }


  //  // Trigger MUON channel
  //  if(isMuon){
  //     // low pt
  //     if(muon_is_low){
  //        if(is2016v2 || is2016v3){
  //         if(!(Trigger_mu_A_selection->passes(event) || Trigger_mu_B_selection->passes(event))) return false;
  //        }
  //        else{
  //         if(!Trigger_mu_A_selection->passes(event)) return false;
  //        }
  //     }
  //     // high pt
  //     if(muon_is_high){
  //        if(is2016v2 || is2016v3){ // 2016
  //           // DATA below runnumb
  //           if(!isMC && event.run < 274954){
  //            if(!Trigger_mu_C_selection->passes(event)) return false;
  //           }
  //           // DATA above runnumb & MC
  //           else{
  //            if(!(Trigger_mu_C_selection->passes(event) || Trigger_mu_D_selection->passes(event))) return false;
  //           }
  //        } // 2017 & 2018
  //        else{
  //         if(!Trigger_mu_C_selection->passes(event)) return false;
  //        }
  //
  //     }
  //  fill_histograms(event, "TriggerMuon");
  //  lumihists_TriggerMuon->fill(event);
  //  }
  //
  //  // Trigger ELECTRON channel
  //  if(isElectron){
  //     // low pt
  //     if(ele_is_low){
  //         if(!Trigger_ele_A_selection->passes(event)) return false;
  //     }
  //     // high pt
  //     if(ele_is_high){
  //        // MC
  //        if(isMC){
  //          if(!(Trigger_ele_B_selection->passes(event) || Trigger_ph_A_selection->passes(event))) return false;
  //        }else{
  //        //DATA
  //            // 2016
  //            if(is2016v2 || is2016v3){
  //                if(isPhoton){ // photon stream
  //                    if(Trigger_ele_B_selection->passes(event) && !Trigger_ph_A_selection->passes(event)) return false;
  //                }else{ // electron stream
  //                   if(!Trigger_ele_B_selection->passes(event)) return false;
  //                }
  //            }
  //            // 2017
  //            if(is2017v2){
  //              // below runnumb trigger Ele115 does not exist
  //              if(event.run < 299329){
  //                if(isPhoton){ // photon stream
  //                    if(Trigger_ele_A_selection->passes(event) && !Trigger_ph_A_selection->passes(event)) return false;
  //                }else{ // electron stream
  //                   if(!Trigger_ele_A_selection->passes(event)) return false;
  //                }
  //              }else{ // above runnumb with Ele115
  //                if(isPhoton){ // photon stream
  //                    if(Trigger_ele_B_selection->passes(event) && !Trigger_ph_A_selection->passes(event)) return false;
  //                }else{ // electron stream
  //                   if(!Trigger_ele_B_selection->passes(event)) return false;
  //                }
  //              }
  //            }
  //            // 2018 photon & electron together: EGamma DATA
  //            if(is2018){
  //               if(!(Trigger_ele_B_selection->passes(event)|| Trigger_ph_A_selection->passes(event))) return false;
  //            }
  //
  //        }
  //     }
  //  fill_histograms(event, "TriggerEle");
  //  lumihists_TriggerEle->fill(event);
  //  }
  //
  //

  // Lepton Trigger SF
  if(isMuon){
    if(muon_is_low){
      MuonTrigger_module_low->process_onemuon(event, 0);
    }
    if(muon_is_high){
      MuonTrigger_module_high->process_onemuon(event, 0);
    }
    fill_histograms(event, "TriggerMuon_SF");
  }
  //if(isElectron){
  //  EleTrigger_module->process(event);
  //  fill_histograms(event, "TriggerEle");
  //}


  ////btag shape sf (Ak4 chs jets)
  //CustomBTagWeight_module->process(event);
  //fill_histograms(event, "Btags1_SF");

  CandidateBuilder->process(event);
  if(debug) cout<<"CandidateBuilder is ok"<<endl;
  Chi2DiscriminatorZprime->process(event);
  if(debug)  cout<<"Chi2DiscriminatorZprime is ok"<<endl;
  CorrectMatchDiscriminatorZprime->process(event);
  if(debug) cout<<"CorrectMatchDiscriminatorZprime is ok"<<endl;
  if(sample.Contains("_blinded")){
    if(!BlindData_selection->passes(event)) return false;
  }

  // Variables for NN
  Variables_module->process(event);
  fill_histograms(event, "NNInputsBeforeReweight");

  // NN module
  NNModule->process(event);
  std::vector<tensorflow::Tensor> NNoutputs = NNModule->GetOutputs();

  event.set(h_NNoutput0, (double)(NNoutputs[0].tensor<float, 2>()(0,0)));
  event.set(h_NNoutput1, (double)(NNoutputs[0].tensor<float, 2>()(0,1)));
  event.set(h_NNoutput2, (double)(NNoutputs[0].tensor<float, 2>()(0,2)));
  event.set(h_NNoutput, NNoutputs);

  double out0 = (double)(NNoutputs[0].tensor<float, 2>()(0,0));
  double out1 = (double)(NNoutputs[0].tensor<float, 2>()(0,1));
  double out2 = (double)(NNoutputs[0].tensor<float, 2>()(0,2));
  vector<double> out_event = {out0, out1, out2};

  h_MulticlassNN_output->fill(event);

  double max_score = 0.0;
  for ( int i = 0; i < 3; i++ ) {
    if ( out_event[i] > max_score) {
      max_score = out_event[i];
    }
  }

// out0=TTbar, out1=ST, out2=WJets
  if( out0 == max_score ){
    fill_histograms(event, "DNN_output0");
    if( ZprimeTopTag_selection->passes(event) ) fill_histograms(event, "DNN_output0_TopTag");
    else fill_histograms(event, "DNN_output0_NoTopTag");
  }

  if( out1 == max_score ){
    fill_histograms(event, "DNN_output1");
    if( ZprimeTopTag_selection->passes(event) ) fill_histograms(event, "DNN_output1_TopTag");
    else fill_histograms(event, "DNN_output1_NoTopTag");
  }

  if( out2 == max_score ){
    fill_histograms(event, "DNN_output2");
    if( ZprimeTopTag_selection->passes(event) ) fill_histograms(event, "DNN_output2_TopTag");
    else fill_histograms(event, "DNN_output2_NoTopTag");
  }

//Define categories on theta star to reduce ttbar background
  if( out0 == max_score ){
     if(ThetaStar_selection_bin1->passes(event)){
         fill_histograms(event, "DNN_output0_thetastar_bin1");
     }else if(ThetaStar_selection_bin2->passes(event)){
         fill_histograms(event, "DNN_output0_thetastar_bin2");
     }else if(ThetaStar_selection_bin3->passes(event)){
         fill_histograms(event, "DNN_output0_thetastar_bin3");
     }else{
         fill_histograms(event, "DNN_output0_thetastar_bin4");
     }
     if( ZprimeTopTag_selection->passes(event) ){
         if(ThetaStar_selection_bin1->passes(event)){
             fill_histograms(event, "DNN_output0_TopTag_thetastar_bin1");
         }else if(ThetaStar_selection_bin2->passes(event)){
             fill_histograms(event, "DNN_output0_TopTag_thetastar_bin2");
         }else if(ThetaStar_selection_bin3->passes(event)){
             fill_histograms(event, "DNN_output0_TopTag_thetastar_bin3");
         }else{
             fill_histograms(event, "DNN_output0_TopTag_thetastar_bin4");
         }
     }else{
         if(ThetaStar_selection_bin1->passes(event)){
             fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin1");
         }else if(ThetaStar_selection_bin2->passes(event)){
             fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin2");
         }else if(ThetaStar_selection_bin3->passes(event)){
             fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin3");
         }else{
             fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin4");
         }
     }

     if(Chi2_selection1->passes(event)){
         fill_histograms(event, "DNN_output0_chi2_max1");
         if(ThetaStar_selection_bin1->passes(event)){
             fill_histograms(event, "DNN_output0_thetastar_bin1_chi2_max1");
         }else if(ThetaStar_selection_bin2->passes(event)){
             fill_histograms(event, "DNN_output0_thetastar_bin2_chi2_max1");
         }else if(ThetaStar_selection_bin3->passes(event)){
             fill_histograms(event, "DNN_output0_thetastar_bin3_chi2_max1");
         }else{
             fill_histograms(event, "DNN_output0_thetastar_bin4_chi2_max1");
         }
         if( ZprimeTopTag_selection->passes(event) ){
             fill_histograms(event, "DNN_output0_TopTag_chi2_max1");
             if(ThetaStar_selection_bin1->passes(event)){
                 fill_histograms(event, "DNN_output0_TopTag_thetastar_bin1_chi2_max1");
             }else if(ThetaStar_selection_bin2->passes(event)){
                 fill_histograms(event, "DNN_output0_TopTag_thetastar_bin2_chi2_max1");
             }else if(ThetaStar_selection_bin3->passes(event)){
                 fill_histograms(event, "DNN_output0_TopTag_thetastar_bin3_chi2_max1");
             }else{
                 fill_histograms(event, "DNN_output0_TopTag_thetastar_bin4_chi2_max1");
             }
         }else{
             fill_histograms(event, "DNN_output0_NoTopTag_chi2_max1");
             if(ThetaStar_selection_bin1->passes(event)){
                 fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin1_chi2_max1");
             }else if(ThetaStar_selection_bin2->passes(event)){
                 fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin2_chi2_max1");
             }else if(ThetaStar_selection_bin3->passes(event)){
                 fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin3_chi2_max1");
             }else{
                 fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin4_chi2_max1");
             }
         }
     }else{
        fill_histograms(event, "DNN_output0_Nochi2_max1");
        if( ZprimeTopTag_selection->passes(event) ){
           fill_histograms(event, "DNN_output0_TopTag_Nochi2_max1");
        }else{
           fill_histograms(event, "DNN_output0_NoTopTag_Nochi2_max1");
        }
     }
     if(Chi2_selection2->passes(event)){
         if(ThetaStar_selection_bin1->passes(event)){
             fill_histograms(event, "DNN_output0_thetastar_bin1_chi2_max2");
         }else if(ThetaStar_selection_bin2->passes(event)){
             fill_histograms(event, "DNN_output0_thetastar_bin2_chi2_max2");
         }else if(ThetaStar_selection_bin3->passes(event)){
             fill_histograms(event, "DNN_output0_thetastar_bin3_chi2_max2");
         }else{
             fill_histograms(event, "DNN_output0_thetastar_bin4_chi2_max2");
         }
         if( ZprimeTopTag_selection->passes(event) ){
             fill_histograms(event, "DNN_output0_TopTag_chi2_max2");
             if(ThetaStar_selection_bin1->passes(event)){
                 fill_histograms(event, "DNN_output0_TopTag_thetastar_bin1_chi2_max2");
             }else if(ThetaStar_selection_bin2->passes(event)){
                 fill_histograms(event, "DNN_output0_TopTag_thetastar_bin2_chi2_max2");
             }else if(ThetaStar_selection_bin3->passes(event)){
                 fill_histograms(event, "DNN_output0_TopTag_thetastar_bin3_chi2_max2");
             }else{
                 fill_histograms(event, "DNN_output0_TopTag_thetastar_bin4_chi2_max2");
             }
         }else{
             fill_histograms(event, "DNN_output0_NoTopTag_chi2_max2");
             if(ThetaStar_selection_bin1->passes(event)){
                 fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin1_chi2_max2");
             }else if(ThetaStar_selection_bin2->passes(event)){
                 fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin2_chi2_max2");
             }else if(ThetaStar_selection_bin3->passes(event)){
                 fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin3_chi2_max2");
             }else{
                 fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin4_chi2_max2");
             }
         }
     }

  }//end out0


  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeAnalysisModule_applyNN)
