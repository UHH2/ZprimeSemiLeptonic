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
#include <UHH2/common/include/LeptonScaleFactors.h>
#include <UHH2/common/include/PSWeights.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSystematicsHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicPDFHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicMulticlassNNHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicCHSMatchHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicMistagHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>
#include <UHH2/ZprimeSemiLeptonic/include/ElecTriggerSF.h>
#include <UHH2/ZprimeSemiLeptonic/include/TopTagScaleFactor.h>

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

  uhh2::Event::Handle<float> h_Ele_E;
  uhh2::Event::Handle<float> h_Ele_eta;
  uhh2::Event::Handle<float> h_Ele_phi;
  uhh2::Event::Handle<float> h_Ele_pt;

  uhh2::Event::Handle<float> h_MET_phi;
  uhh2::Event::Handle<float> h_MET_pt;

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

  h_Ele_E    = ctx.get_handle<float>("Ele_E");
  h_Ele_eta  = ctx.get_handle<float>("Ele_eta");
  h_Ele_phi  = ctx.get_handle<float>("Ele_phi");
  h_Ele_pt   = ctx.get_handle<float>("Ele_pt");

  h_MET_phi = ctx.get_handle<float>("MET_phi");
  h_MET_pt = ctx.get_handle<float>("MET_pt");

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

  string varname[59];
  string scal[59];
  string mean[59];
  string std[59];
  double mean_val[59];
  double std_val[59];
  //Only Ele or Mu variables!!
  ifstream normfile ("/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL17_muon/NormInfo.txt", ios::in);
  //ifstream normfile ("/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL17_ele/NormInfo.txt", ios::in);
  if(!normfile.good()) throw runtime_error("NeuralNetworkModule: The specified norm file does not exist.");
  if (normfile.is_open()){
    for(int i = 0; i < 59; ++i)
    {
      normfile >> varname[i] >> scal[i] >> mean[i] >> std[i];
      mean_val[i] = std::stod(mean[i]);
      std_val[i] = std::stod(std[i]);
    }
    normfile.close();
  }

  NNInputs.push_back( tensorflow::Tensor(tensorflow::DT_FLOAT, {1, 59}));

  //Only Ele or Mu variables!!
   vector<uhh2::Event::Handle<float>> inputs = {h_Ak4_j1_E, h_Ak4_j1_deepjetbscore, h_Ak4_j1_eta, h_Ak4_j1_m, h_Ak4_j1_phi, h_Ak4_j1_pt, h_Ak4_j2_E, h_Ak4_j2_deepjetbscore, h_Ak4_j2_eta, h_Ak4_j2_m, h_Ak4_j2_phi, h_Ak4_j2_pt, h_Ak4_j3_E, h_Ak4_j3_deepjetbscore, h_Ak4_j3_eta, h_Ak4_j3_m, h_Ak4_j3_phi, h_Ak4_j3_pt, h_Ak4_j4_E, h_Ak4_j4_deepjetbscore, h_Ak4_j4_eta, h_Ak4_j4_m, h_Ak4_j4_phi, h_Ak4_j4_pt, h_Ak4_j5_E, h_Ak4_j5_deepjetbscore, h_Ak4_j5_eta, h_Ak4_j5_m, h_Ak4_j5_phi, h_Ak4_j5_pt, h_Ak8_j1_E, h_Ak8_j1_eta, h_Ak8_j1_mSD, h_Ak8_j1_phi, h_Ak8_j1_pt, h_Ak8_j1_tau21, h_Ak8_j1_tau32, h_Ak8_j2_E, h_Ak8_j2_eta, h_Ak8_j2_mSD, h_Ak8_j2_phi, h_Ak8_j2_pt, h_Ak8_j2_tau21, h_Ak8_j2_tau32, h_Ak8_j3_E, h_Ak8_j3_eta, h_Ak8_j3_mSD, h_Ak8_j3_phi, h_Ak8_j3_pt, h_Ak8_j3_tau21, h_Ak8_j3_tau32, h_MET_phi, h_MET_pt, h_Mu_E, h_Mu_eta, h_Mu_phi, h_Mu_pt, h_N_Ak4, h_N_Ak8}; // in alphabetical order to match NormInfo.txt
  // vector<uhh2::Event::Handle<float>> inputs = {h_Ak4_j1_E, h_Ak4_j1_deepjetbscore, h_Ak4_j1_eta, h_Ak4_j1_m, h_Ak4_j1_phi, h_Ak4_j1_pt, h_Ak4_j2_E, h_Ak4_j2_deepjetbscore, h_Ak4_j2_eta, h_Ak4_j2_m, h_Ak4_j2_phi, h_Ak4_j2_pt, h_Ak4_j3_E, h_Ak4_j3_deepjetbscore, h_Ak4_j3_eta, h_Ak4_j3_m, h_Ak4_j3_phi, h_Ak4_j3_pt, h_Ak4_j4_E, h_Ak4_j4_deepjetbscore, h_Ak4_j4_eta, h_Ak4_j4_m, h_Ak4_j4_phi, h_Ak4_j4_pt, h_Ak4_j5_E, h_Ak4_j5_deepjetbscore, h_Ak4_j5_eta, h_Ak4_j5_m, h_Ak4_j5_phi, h_Ak4_j5_pt, h_Ak8_j1_E, h_Ak8_j1_eta, h_Ak8_j1_mSD, h_Ak8_j1_phi, h_Ak8_j1_pt, h_Ak8_j1_tau21, h_Ak8_j1_tau32, h_Ak8_j2_E, h_Ak8_j2_eta, h_Ak8_j2_mSD, h_Ak8_j2_phi, h_Ak8_j2_pt, h_Ak8_j2_tau21, h_Ak8_j2_tau32, h_Ak8_j3_E, h_Ak8_j3_eta, h_Ak8_j3_mSD, h_Ak8_j3_phi, h_Ak8_j3_pt, h_Ak8_j3_tau21, h_Ak8_j3_tau32, h_Ele_E, h_Ele_eta, h_Ele_phi, h_Ele_pt, h_MET_phi, h_MET_pt, h_N_Ak4, h_N_Ak8}; // in alphabetical order to match NormInfo.txt

  for(int i = 0; i < 59; ++i){
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

  // Cleaners
  std::unique_ptr<MuonCleaner>     muon_cleaner_low, muon_cleaner_high;
  std::unique_ptr<ElectronCleaner> electron_cleaner_low, electron_cleaner_high;

  // scale factors
  unique_ptr<AnalysisModule> sf_muon_iso_low, sf_muon_id_low, sf_muon_id_high, sf_muon_trigger_low, sf_muon_trigger_high;
  unique_ptr<AnalysisModule> sf_muon_iso_low_dummy, sf_muon_id_dummy, sf_muon_trigger_dummy;
  unique_ptr<AnalysisModule> sf_ele_id_low, sf_ele_id_high, sf_ele_reco;
  unique_ptr<AnalysisModule> sf_ele_id_dummy, sf_ele_reco_dummy;
  unique_ptr<MuonRecoSF> sf_muon_reco;
  unique_ptr<AnalysisModule> sf_ele_trigger;
  unique_ptr<AnalysisModule> sf_btagging;

  // AnalysisModules
  unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, TopPtReweight_module, MCScale_module;
  unique_ptr<AnalysisModule> NLOCorrections_module;
  unique_ptr<PSWeights> ps_weights;

  // Top tagging
  unique_ptr<HOTVRTopTagger> TopTaggerHOTVR;
  unique_ptr<AnalysisModule> hadronic_top;
  unique_ptr<AnalysisModule> sf_toptag;
  unique_ptr<DeepAK8TopTagger> TopTaggerDeepAK8;

  // TopTags veto
  unique_ptr<Selection> TopTagVetoSelection;

  // Mass reconstruction
  unique_ptr<ZprimeCandidateBuilder> CandidateBuilder;

  // Chi2 discriminator
  unique_ptr<ZprimeChi2Discriminator> Chi2DiscriminatorZprime;
  unique_ptr<ZprimeCorrectMatchDiscriminator> CorrectMatchDiscriminatorZprime;

  // Selections
  unique_ptr<Selection> Chi2_selection, TTbarMatchable_selection, Chi2CandidateMatched_selection, ZprimeTopTag_selection;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<Selection> sel_1btag, sel_2btag;
  std::unique_ptr<Selection> HEM_selection;
  unique_ptr<Selection> ThetaStar_selection_bin1, ThetaStar_selection_bin2, ThetaStar_selection_bin3, ThetaStar_selection_bin4, ThetaStar_selection_bin5, ThetaStar_selection_bin6;
  unique_ptr<Selection> AbsThetaStar_selection_bin1, AbsThetaStar_selection_bin2, AbsThetaStar_selection_bin3, AbsThetaStar_selection_bin4, AbsThetaStar_selection_bin5;

  // NN variables handles
  unique_ptr<Variables_NN> Variables_module;

  //Handles
  Event::Handle<bool> h_is_zprime_reconstructed_chi2, h_is_zprime_reconstructed_correctmatch;
  Event::Handle<float> h_chi2;
  Event::Handle<float> h_weight;

  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;

  // Lumi hists
  std::unique_ptr<Hists> lumihists_Weights_Init, lumihists_Weights_PU, lumihists_Weights_Lumi, lumihists_Weights_TopPt, lumihists_Weights_MCScale, lumihists_Weights_PS, lumihists_Chi2;

  float inv_mass(const LorentzVector& p4){ return p4.isTimelike() ? p4.mass() : -sqrt(-p4.mass2()); }

  // DNN multiclass output hist
  std::unique_ptr<Hists> h_MulticlassNN_output;

  // Hists with systematics variations
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output1;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output2;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output1_TopTag;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output2_TopTag;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output1_NoTopTag;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output2_NoTopTag;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_thetastar_bin6;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin6;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin6;


  // Hists with PDF variations
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output1;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output2;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output1_TopTag;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output2_TopTag;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output1_NoTopTag;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output2_NoTopTag;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_thetastar_bin6;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin6;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin1;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin2;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin3;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin4;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin5;
  std::unique_ptr<Hists> h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin6;

  std::unique_ptr<Hists> h_MistagHists;

  // Configuration
  bool isMC, ishotvr, isdeepAK8;
  string Sys_PU, Prefiring_direction, Sys_TopPt_a, Sys_TopPt_b;
  TString sample;
  int runnr_oldtriggers = 299368;

  bool isUL16preVFP, isUL16postVFP, isUL17, isUL18;
  bool isMuon, isElectron;
  bool isPhoton;
  TString year;

  TH2F *ratio_hist_muon;
  TH2F *ratio_hist_ele;

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

  Event::Handle<float> h_Ele_E;
  Event::Handle<float> h_Ele_eta;
  Event::Handle<float> h_Ele_phi;
  Event::Handle<float> h_Ele_pt;

  Event::Handle<float> h_MET_phi;
  Event::Handle<float> h_MET_pt;

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
  // debug = true;
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
  if(isUL16preVFP) year = "UL16preVFP";
  if(isUL16postVFP) year = "UL16postVFP";
  if(isUL17) year = "UL17";
  if(isUL18) year = "UL18";

  isPhoton = (ctx.get("dataset_version").find("SinglePhoton") != std::string::npos);

  // Lepton IDs
  ElectronId eleID_low  = ElectronTagID(Electron::mvaEleID_Fall17_iso_V2_wp80);
  ElectronId eleID_high = ElectronTagID(Electron::mvaEleID_Fall17_noIso_V2_wp80);
  MuonId     muID_low   = AndId<Muon>(MuonID(Muon::CutBasedIdTight), MuonID(Muon::PFIsoTight));
  MuonId     muID_high  = MuonID(Muon::CutBasedIdGlobalHighPt);

  double electron_pt_low;
  if(isUL17){
    electron_pt_low = 38.; // UL17 ele trigger threshold is 35 (HLT_Ele35WPTight _Gsf) -> be above turn on
  }
  else{
    electron_pt_low = 35.;
  }
  double muon_pt_low(30.);
  double electron_pt_high(120.);
  double muon_pt_high(55.);

  const MuonId muonID_low(AndId<Muon>(PtEtaCut(muon_pt_low, 2.4), muID_low));
  const ElectronId electronID_low(AndId<Electron>(PtEtaSCCut(electron_pt_low, 2.5), eleID_low));
  const MuonId muonID_high(AndId<Muon>(PtEtaCut(muon_pt_high, 2.4), muID_high));
  const ElectronId electronID_high(AndId<Electron>(PtEtaSCCut(electron_pt_high, 2.5), eleID_high));

  muon_cleaner_low.reset(new MuonCleaner(muonID_low));
  electron_cleaner_low.reset(new ElectronCleaner(electronID_low));
  muon_cleaner_high.reset(new MuonCleaner(muonID_high));
  electron_cleaner_high.reset(new ElectronCleaner(electronID_high));

  // Important selection values
  double chi2_max(30.);
  string trigger_mu_A, trigger_mu_B, trigger_mu_C, trigger_mu_D, trigger_mu_E, trigger_mu_F;
  string trigger_ele_A, trigger_ele_B;
  string trigger_ph_A;
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
    trigger_mu_E = "HLT_OldMu100_v*";
    trigger_mu_F = "HLT_TkMu100_v*";

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
  }


  const TopJetId toptagID = AndId<TopJet>(HOTVRTopTag(0.8, 140.0, 220.0, 50.0), Tau32Groomed(0.56));

  Sys_PU = ctx.get("Sys_PU");
  Prefiring_direction = ctx.get("Sys_prefiring");
  Sys_TopPt_a = ctx.get("Systematic_TopPt_a");
  Sys_TopPt_b = ctx.get("Systematic_TopPt_b");

  BTag::algo btag_algo = BTag::DEEPJET;
  BTag::wp btag_wp = BTag::WP_MEDIUM;
  JetId id_btag = BTag(btag_algo, btag_wp);

  // double a_toppt = 0.0615; // par a TopPt Reweighting
  // double b_toppt = -0.0005; // par b TopPt Reweighting

  // Modules
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  //TopPtReweight_module.reset(new TopPtReweighting(ctx, a_toppt, b_toppt, Sys_TopPt_a, Sys_TopPt_b, ""));
  MCScale_module.reset(new MCScaleVariation(ctx));
  hadronic_top.reset(new HadronicTop(ctx));
  // sf_toptag.reset(new HOTVRScaleFactor(ctx, toptagID, ctx.get("Sys_TopTag", "nominal"), "HadronicTop", "TopTagSF", "HOTVRTopTagSFs"));
  sf_toptag.reset(new TopTagScaleFactor(ctx));
  NLOCorrections_module.reset(new NLOCorrections(ctx));
  ps_weights.reset(new PSWeights(ctx));

  // b-tagging SFs
  sf_btagging.reset(new MCBTagDiscriminantReweighting(ctx, BTag::algo::DEEPJET, "CHS_matched"));

  // set lepton scale factors: see UHH2/common/include/LeptonScaleFactors.h
  sf_muon_iso_low.reset(new uhh2::MuonIsoScaleFactors(ctx, Muon::Selector::PFIsoTight, Muon::Selector::CutBasedIdTight, true));
  sf_muon_id_low.reset(new uhh2::MuonIdScaleFactors(ctx, Muon::Selector::CutBasedIdTight, true));
  sf_muon_id_high.reset(new uhh2::MuonIdScaleFactors(ctx, Muon::Selector::CutBasedIdGlobalHighPt, true));
  sf_muon_trigger_low.reset(new uhh2::MuonTriggerScaleFactors(ctx, false, true));
  sf_muon_trigger_high.reset(new uhh2::MuonTriggerScaleFactors(ctx, true, false));
  sf_muon_reco.reset(new MuonRecoSF(ctx));
  sf_ele_id_low.reset(new uhh2::ElectronIdScaleFactors(ctx, Electron::tag::mvaEleID_Fall17_iso_V2_wp80, true));
  sf_ele_id_high.reset(new uhh2::ElectronIdScaleFactors(ctx, Electron::tag::mvaEleID_Fall17_noIso_V2_wp80, true));
  sf_ele_reco.reset(new uhh2::ElectronRecoScaleFactors(ctx, false, true));

  sf_ele_trigger.reset( new uhh2::ElecTriggerSF(ctx, "central", "eta_ptbins", year) );

  // dummies (needed to aviod set value errors)
  sf_muon_iso_low_dummy.reset(new uhh2::MuonIsoScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, boost::none, true));
  sf_muon_id_dummy.reset(new uhh2::MuonIdScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, true));
  sf_muon_trigger_dummy.reset(new uhh2::MuonTriggerScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, boost::none, true));
  sf_ele_id_dummy.reset(new uhh2::ElectronIdScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, true));
  sf_ele_reco_dummy.reset(new uhh2::ElectronRecoScaleFactors(ctx, boost::none, boost::none, boost::none, boost::none, true));

  // Selection modules
  Chi2_selection.reset(new Chi2Cut(ctx, 0., chi2_max));
  TTbarMatchable_selection.reset(new TTbarSemiLepMatchableSelection());
  Chi2CandidateMatched_selection.reset(new Chi2CandidateMatchedSelection(ctx));
  ZprimeTopTag_selection.reset(new ZprimeTopTagSelection(ctx));

  HEM_selection.reset(new HEMSelection(ctx)); // HEM issue in 2018, veto on leptons and jets

  Variables_module.reset(new Variables_NN(ctx, mode)); // variables for NN

  // Selections on scattering angle theta star
  double theta_bin1_low (-1.);
  double theta_bin1_high (-0.7);
  ThetaStar_selection_bin1.reset(new ThetaStarSelection(ctx, theta_bin1_low, theta_bin1_high));
  double theta_bin2_low (-0.7);
  double theta_bin2_high (-0.5);
  ThetaStar_selection_bin2.reset(new ThetaStarSelection(ctx, theta_bin2_low, theta_bin2_high));
  double theta_bin3_low (-0.5);
  double theta_bin3_high (0.0);
  ThetaStar_selection_bin3.reset(new ThetaStarSelection(ctx, theta_bin3_low, theta_bin3_high));
  double theta_bin4_low (0.0);
  double theta_bin4_high (0.5);
  ThetaStar_selection_bin4.reset(new ThetaStarSelection(ctx, theta_bin4_low, theta_bin4_high));
  double theta_bin5_low (0.5);
  double theta_bin5_high (0.7);
  ThetaStar_selection_bin5.reset(new ThetaStarSelection(ctx, theta_bin5_low, theta_bin5_high));
  double theta_bin6_low (0.7);
  double theta_bin6_high (1.);
  ThetaStar_selection_bin6.reset(new ThetaStarSelection(ctx, theta_bin6_low, theta_bin6_high));

  // Selections on absolute value of scattering angle theta star
  double abs_theta_bin1_low (0.);
  double abs_theta_bin1_high (0.4);
  AbsThetaStar_selection_bin1.reset(new AbsThetaStarSelection(ctx, abs_theta_bin1_low, abs_theta_bin1_high));
  double abs_theta_bin2_low (0.4);
  double abs_theta_bin2_high (0.6);
  AbsThetaStar_selection_bin2.reset(new AbsThetaStarSelection(ctx, abs_theta_bin2_low, abs_theta_bin2_high));
  double abs_theta_bin3_low (0.6);
  double abs_theta_bin3_high (0.8);
  AbsThetaStar_selection_bin3.reset(new AbsThetaStarSelection(ctx, abs_theta_bin3_low, abs_theta_bin3_high));
  double abs_theta_bin4_low (0.8);
  double abs_theta_bin4_high (0.9);
  AbsThetaStar_selection_bin4.reset(new AbsThetaStarSelection(ctx, abs_theta_bin4_low, abs_theta_bin4_high));
  double abs_theta_bin5_low (0.9);
  double abs_theta_bin5_high (1.);
  AbsThetaStar_selection_bin5.reset(new AbsThetaStarSelection(ctx, abs_theta_bin5_low, abs_theta_bin5_high));

  // Top Taggers
  TopTaggerHOTVR.reset(new HOTVRTopTagger(ctx));
  TopTaggerDeepAK8.reset(new DeepAK8TopTagger(ctx));

  // TopTags veto
  TopTagVetoSelection.reset(new TopTag_VetoSelection(ctx, mode));

  // Zprime candidate builder
  CandidateBuilder.reset(new ZprimeCandidateBuilder(ctx, mode));

  // Zprime discriminators
  Chi2DiscriminatorZprime.reset(new ZprimeChi2Discriminator(ctx));
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  CorrectMatchDiscriminatorZprime.reset(new ZprimeCorrectMatchDiscriminator(ctx));
  h_is_zprime_reconstructed_correctmatch = ctx.get_handle<bool>("is_zprime_reconstructed_correctmatch");
  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  h_chi2 = ctx.declare_event_output<float> ("rec_chi2");

  h_weight = ctx.declare_event_output<float> ("weight");

  sel_1btag.reset(new NJetSelection(1, -1, id_btag));
  sel_2btag.reset(new NJetSelection(2,-1, id_btag));

  // Hist with Syst Variations
  h_Zprime_SystVariations_DNN_output0.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0"));
  h_Zprime_SystVariations_DNN_output1.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output1"));
  h_Zprime_SystVariations_DNN_output2.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output2"));
  h_Zprime_SystVariations_DNN_output0_TopTag.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag"));
  h_Zprime_SystVariations_DNN_output1_TopTag.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output1_TopTag"));
  h_Zprime_SystVariations_DNN_output2_TopTag.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output2_TopTag"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag"));
  h_Zprime_SystVariations_DNN_output1_NoTopTag.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output1_NoTopTag"));
  h_Zprime_SystVariations_DNN_output2_NoTopTag.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output2_NoTopTag"));
  h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin1.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_abs_thetastar_bin1"));
  h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin2.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_abs_thetastar_bin2"));
  h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin3.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_abs_thetastar_bin3"));
  h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin4.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_abs_thetastar_bin4"));
  h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin5.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_abs_thetastar_bin5"));
  h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin1.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin1"));
  h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin2.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin2"));
  h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin3.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin3"));
  h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin4.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin4"));
  h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin5.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin5"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin1.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin1"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin2.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin2"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin3.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin3"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin4.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin4"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin5.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin5"));
  h_Zprime_SystVariations_DNN_output0_thetastar_bin1.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_thetastar_bin1"));
  h_Zprime_SystVariations_DNN_output0_thetastar_bin2.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_thetastar_bin2"));
  h_Zprime_SystVariations_DNN_output0_thetastar_bin3.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_thetastar_bin3"));
  h_Zprime_SystVariations_DNN_output0_thetastar_bin4.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_thetastar_bin4"));
  h_Zprime_SystVariations_DNN_output0_thetastar_bin5.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_thetastar_bin5"));
  h_Zprime_SystVariations_DNN_output0_thetastar_bin6.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_thetastar_bin6"));
  h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin1.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin1"));
  h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin2.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin2"));
  h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin3.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin3"));
  h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin4.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin4"));
  h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin5.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin5"));
  h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin6.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin6"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin1.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin1"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin2.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin2"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin3.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin3"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin4.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin4"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin5.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin5"));
  h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin6.reset(new ZprimeSemiLeptonicSystematicsHists(ctx, "Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin6"));

  // Hist with PDF variations
  h_Zprime_PDFVariations_DNN_output0.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0"));
  h_Zprime_PDFVariations_DNN_output1.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output1"));
  h_Zprime_PDFVariations_DNN_output2.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output2"));
  h_Zprime_PDFVariations_DNN_output0_TopTag.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag"));
  h_Zprime_PDFVariations_DNN_output1_TopTag.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output1_TopTag"));
  h_Zprime_PDFVariations_DNN_output2_TopTag.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output2_TopTag"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag"));
  h_Zprime_PDFVariations_DNN_output1_NoTopTag.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output1_NoTopTag"));
  h_Zprime_PDFVariations_DNN_output2_NoTopTag.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output2_NoTopTag"));
  h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin1.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_abs_thetastar_bin1"));
  h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin2.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_abs_thetastar_bin2"));
  h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin3.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_abs_thetastar_bin3"));
  h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin4.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_abs_thetastar_bin4"));
  h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin5.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_abs_thetastar_bin5"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin1.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin1"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin2.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin2"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin3.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin3"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin4.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin4"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin5.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin5"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin1.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin1"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin2.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin2"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin3.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin3"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin4.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin4"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin5.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin5"));
  h_Zprime_PDFVariations_DNN_output0_thetastar_bin1.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_thetastar_bin1"));
  h_Zprime_PDFVariations_DNN_output0_thetastar_bin2.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_thetastar_bin2"));
  h_Zprime_PDFVariations_DNN_output0_thetastar_bin3.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_thetastar_bin3"));
  h_Zprime_PDFVariations_DNN_output0_thetastar_bin4.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_thetastar_bin4"));
  h_Zprime_PDFVariations_DNN_output0_thetastar_bin5.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_thetastar_bin5"));
  h_Zprime_PDFVariations_DNN_output0_thetastar_bin6.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_thetastar_bin6"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin1.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin1"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin2.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin2"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin3.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin3"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin4.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin4"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin5.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin5"));
  h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin6.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin6"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin1.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin1"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin2.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin2"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin3.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin3"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin4.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin4"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin5.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin5"));
  h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin6.reset(new ZprimeSemiLeptonicPDFHists(ctx, "Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin6"));

  h_MistagHists.reset(new ZprimeSemiLeptonicMistagHists(ctx, "Mistag"));

  // Book histograms
  vector<string> histogram_tags = {"Weights_Init", "Weights_HEM", "Weights_PU", "Weights_Lumi", "Weights_TopPt", "Weights_MCScale", "Weights_Prefiring", "Weights_TopTag_SF", "Weights_PS", "NLOCorrections", "IdMuon_SF", "IdEle_SF", "IsoMuon_SF", "RecoEle_SF", "MuonReco_SF", "TriggerMuon_SF", "BeforeBtagSF", "AfterBtagSF", "AfterCustomBtagSF", "TriggerEle_SF", "NNInputsBeforeReweight", "TopTagVeto", "DNN_output0_beforeChi2Cut", "DNN_output0_TopTag_beforeChi2Cut", "DNN_output0_NoTopTag_beforeChi2Cut", "DNN_output0","DNN_output1","DNN_output2","DNN_output0_TopTag","DNN_output1_TopTag","DNN_output2_TopTag","DNN_output0_NoTopTag","DNN_output1_NoTopTag","DNN_output2_NoTopTag", "DNN_output0_abs_thetastar_bin1", "DNN_output0_abs_thetastar_bin2", "DNN_output0_abs_thetastar_bin3", "DNN_output0_abs_thetastar_bin4", "DNN_output0_abs_thetastar_bin5", "DNN_output0_TopTag_abs_thetastar_bin1", "DNN_output0_TopTag_abs_thetastar_bin2", "DNN_output0_TopTag_abs_thetastar_bin3", "DNN_output0_TopTag_abs_thetastar_bin4", "DNN_output0_TopTag_abs_thetastar_bin5", "DNN_output0_NoTopTag_abs_thetastar_bin1", "DNN_output0_NoTopTag_abs_thetastar_bin2", "DNN_output0_NoTopTag_abs_thetastar_bin3", "DNN_output0_NoTopTag_abs_thetastar_bin4", "DNN_output0_NoTopTag_abs_thetastar_bin5", "DNN_output0_thetastar_bin1", "DNN_output0_thetastar_bin2", "DNN_output0_thetastar_bin3", "DNN_output0_thetastar_bin4", "DNN_output0_thetastar_bin5", "DNN_output0_thetastar_bin6", "DNN_output0_TopTag_thetastar_bin1", "DNN_output0_TopTag_thetastar_bin2", "DNN_output0_TopTag_thetastar_bin3", "DNN_output0_TopTag_thetastar_bin4", "DNN_output0_TopTag_thetastar_bin5", "DNN_output0_TopTag_thetastar_bin6", "DNN_output0_NoTopTag_thetastar_bin1", "DNN_output0_NoTopTag_thetastar_bin2", "DNN_output0_NoTopTag_thetastar_bin3", "DNN_output0_NoTopTag_thetastar_bin4", "DNN_output0_NoTopTag_thetastar_bin5", "DNN_output0_NoTopTag_thetastar_bin6"};
  book_histograms(ctx, histogram_tags);

  h_MulticlassNN_output.reset(new ZprimeSemiLeptonicMulticlassNNHists(ctx, "MulticlassNN"));

  lumihists_Weights_Init.reset(new LuminosityHists(ctx, "Lumi_Weights_Init"));
  lumihists_Weights_PU.reset(new LuminosityHists(ctx, "Lumi_Weights_PU"));
  lumihists_Weights_Lumi.reset(new LuminosityHists(ctx, "Lumi_Weights_Lumi"));
  lumihists_Weights_TopPt.reset(new LuminosityHists(ctx, "Lumi_Weights_TopPt"));
  lumihists_Weights_MCScale.reset(new LuminosityHists(ctx, "Lumi_Weights_MCScale"));
  lumihists_Weights_PS.reset(new LuminosityHists(ctx, "Lumi_Weights_PS"));
  lumihists_Chi2.reset(new LuminosityHists(ctx, "Lumi_Chi2"));

  if(isMC){
    TString sample_name = "";
    vector<TString> names = {"ST", "WJets", "DY", "QCD", "ALP_ttbar_signal", "ALP_ttbar_interference", "HscalarToTTTo1L1Nu2J_m365_w36p5_res", "HscalarToTTTo1L1Nu2J_m400_w40p0_res", "HscalarToTTTo1L1Nu2J_m500_w50p0_res", "HscalarToTTTo1L1Nu2J_m600_w60p0_res", "HscalarToTTTo1L1Nu2J_m800_w80p0_res", "HscalarToTTTo1L1Nu2J_m1000_w100p0_res", "HscalarToTTTo1L1Nu2J_m365_w36p5_int_pos", "HscalarToTTTo1L1Nu2J_m400_w40p0_int_pos", "HscalarToTTTo1L1Nu2J_m500_w50p0_int_pos", "HscalarToTTTo1L1Nu2J_m600_w60p0_int_pos", "HscalarToTTTo1L1Nu2J_m800_w80p0_int_pos", "HscalarToTTTo1L1Nu2J_m1000_w100p0_int_pos", "HscalarToTTTo1L1Nu2J_m365_w36p5_int_neg", "HscalarToTTTo1L1Nu2J_m400_w40p0_int_neg", "HscalarToTTTo1L1Nu2J_m500_w50p0_int_neg", "HscalarToTTTo1L1Nu2J_m600_w60p0_int_neg", "HscalarToTTTo1L1Nu2J_m800_w80p0_int_neg", "HscalarToTTTo1L1Nu2J_m1000_w100p0_int_neg", "HpseudoToTTTo1L1Nu2J_m365_w36p5_res", "HpseudoToTTTo1L1Nu2J_m400_w40p0_res", "HpseudoToTTTo1L1Nu2J_m500_w50p0_res", "HpseudoToTTTo1L1Nu2J_m600_w60p0_res", "HpseudoToTTTo1L1Nu2J_m800_w80p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res", "HpseudoToTTTo1L1Nu2J_m365_w36p5_int_pos", "HpseudoToTTTo1L1Nu2J_m400_w40p0_int_pos", "HpseudoToTTTo1L1Nu2J_m500_w50p0_int_pos", "HpseudoToTTTo1L1Nu2J_m600_w60p0_int_pos", "HpseudoToTTTo1L1Nu2J_m800_w80p0_int_pos", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_pos", "HpseudoToTTTo1L1Nu2J_m365_w36p5_int_neg", "HpseudoToTTTo1L1Nu2J_m400_w40p0_int_neg", "HpseudoToTTTo1L1Nu2J_m500_w50p0_int_neg", "HpseudoToTTTo1L1Nu2J_m600_w60p0_int_neg", "HpseudoToTTTo1L1Nu2J_m800_w80p0_int_neg", "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_neg", "HscalarToTTTo1L1Nu2J_m365_w91p25_res", "HscalarToTTTo1L1Nu2J_m400_w100p0_res", "HscalarToTTTo1L1Nu2J_m500_w125p0_res", "HscalarToTTTo1L1Nu2J_m600_w150p0_res", "HscalarToTTTo1L1Nu2J_m800_w200p0_res", "HscalarToTTTo1L1Nu2J_m1000_w250p0_res", "HscalarToTTTo1L1Nu2J_m365_w91p25_int_pos", "HscalarToTTTo1L1Nu2J_m400_w100p0_int_pos", "HscalarToTTTo1L1Nu2J_m500_w125p0_int_pos", "HscalarToTTTo1L1Nu2J_m600_w150p0_int_pos", "HscalarToTTTo1L1Nu2J_m800_w200p0_int_pos", "HscalarToTTTo1L1Nu2J_m1000_w250p0_int_pos", "HscalarToTTTo1L1Nu2J_m365_w91p25_int_neg", "HscalarToTTTo1L1Nu2J_m400_w100p0_int_neg", "HscalarToTTTo1L1Nu2J_m500_w125p0_int_neg", "HscalarToTTTo1L1Nu2J_m600_w150p0_int_neg", "HscalarToTTTo1L1Nu2J_m800_w200p0_int_neg", "HscalarToTTTo1L1Nu2J_m1000_w250p0_int_neg", "HpseudoToTTTo1L1Nu2J_m365_w91p25_res", "HpseudoToTTTo1L1Nu2J_m400_w100p0_res", "HpseudoToTTTo1L1Nu2J_m500_w125p0_res", "HpseudoToTTTo1L1Nu2J_m600_w150p0_res", "HpseudoToTTTo1L1Nu2J_m800_w200p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res", "HpseudoToTTTo1L1Nu2J_m365_w91p25_int_pos", "HpseudoToTTTo1L1Nu2J_m400_w100p0_int_pos", "HpseudoToTTTo1L1Nu2J_m500_w125p0_int_pos", "HpseudoToTTTo1L1Nu2J_m600_w150p0_int_pos", "HpseudoToTTTo1L1Nu2J_m800_w200p0_int_pos", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_pos", "HpseudoToTTTo1L1Nu2J_m365_w91p25_int_neg", "HpseudoToTTTo1L1Nu2J_m400_w100p0_int_neg", "HpseudoToTTTo1L1Nu2J_m500_w125p0_int_neg", "HpseudoToTTTo1L1Nu2J_m600_w150p0_int_neg", "HpseudoToTTTo1L1Nu2J_m800_w200p0_int_neg", "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_neg", "HscalarToTTTo1L1Nu2J_m365_w9p125_res", "HscalarToTTTo1L1Nu2J_m400_w10p0_res", "HscalarToTTTo1L1Nu2J_m500_w12p5_res", "HscalarToTTTo1L1Nu2J_m600_w15p0_res", "HscalarToTTTo1L1Nu2J_m800_w20p0_res", "HscalarToTTTo1L1Nu2J_m1000_w25p0_res", "HscalarToTTTo1L1Nu2J_m365_w9p125_int_pos", "HscalarToTTTo1L1Nu2J_m400_w10p0_int_pos", "HscalarToTTTo1L1Nu2J_m500_w12p5_int_pos", "HscalarToTTTo1L1Nu2J_m600_w15p0_int_pos", "HscalarToTTTo1L1Nu2J_m800_w20p0_int_pos", "HscalarToTTTo1L1Nu2J_m1000_w25p0_int_pos", "HscalarToTTTo1L1Nu2J_m365_w9p125_int_neg", "HscalarToTTTo1L1Nu2J_m400_w10p0_int_neg", "HscalarToTTTo1L1Nu2J_m500_w12p5_int_neg", "HscalarToTTTo1L1Nu2J_m600_w15p0_int_neg", "HscalarToTTTo1L1Nu2J_m800_w20p0_int_neg", "HscalarToTTTo1L1Nu2J_m1000_w25p0_int_neg", "HpseudoToTTTo1L1Nu2J_m365_w9p125_res", "HpseudoToTTTo1L1Nu2J_m400_w10p0_res", "HpseudoToTTTo1L1Nu2J_m500_w12p5_res", "HpseudoToTTTo1L1Nu2J_m600_w15p0_res", "HpseudoToTTTo1L1Nu2J_m800_w20p0_res", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res", "HpseudoToTTTo1L1Nu2J_m365_w9p125_int_pos", "HpseudoToTTTo1L1Nu2J_m400_w10p0_int_pos", "HpseudoToTTTo1L1Nu2J_m500_w12p5_int_pos", "HpseudoToTTTo1L1Nu2J_m600_w15p0_int_pos", "HpseudoToTTTo1L1Nu2J_m800_w20p0_int_pos", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_pos", "HpseudoToTTTo1L1Nu2J_m365_w9p125_int_neg", "HpseudoToTTTo1L1Nu2J_m400_w10p0_int_neg", "HpseudoToTTTo1L1Nu2J_m500_w12p5_int_neg", "HpseudoToTTTo1L1Nu2J_m600_w15p0_int_neg", "HpseudoToTTTo1L1Nu2J_m800_w20p0_int_neg", "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_neg", "RSGluonToTT_M-500", "RSGluonToTT_M-1000", "RSGluonToTT_M-1500", "RSGluonToTT_M-2000", "RSGluonToTT_M-2500", "RSGluonToTT_M-3000", "RSGluonToTT_M-3500", "RSGluonToTT_M-4000", "RSGluonToTT_M-4500", "RSGluonToTT_M-5000", "RSGluonToTT_M-5500", "RSGluonToTT_M-6000", "ZPrimeToTT_M400_W40", "ZPrimeToTT_M500_W50", "ZPrimeToTT_M600_W60", "ZPrimeToTT_M700_W70", "ZPrimeToTT_M800_W80", "ZPrimeToTT_M900_W90", "ZPrimeToTT_M1000_W100", "ZPrimeToTT_M1200_W120", "ZPrimeToTT_M1400_W140", "ZPrimeToTT_M1600_W160", "ZPrimeToTT_M1800_W180", "ZPrimeToTT_M2000_W200", "ZPrimeToTT_M2500_W250", "ZPrimeToTT_M3000_W300", "ZPrimeToTT_M3500_W350", "ZPrimeToTT_M4000_W400", "ZPrimeToTT_M4500_W450", "ZPrimeToTT_M5000_W500", "ZPrimeToTT_M6000_W600",  "ZPrimeToTT_M7000_W700", "ZPrimeToTT_M8000_W800", "ZPrimeToTT_M9000_W900", "ZPrimeToTT_M400_W120", "ZPrimeToTT_M500_W150", "ZPrimeToTT_M600_W180", "ZPrimeToTT_M700_W210", "ZPrimeToTT_M800_W240", "ZPrimeToTT_M900_W270", "ZPrimeToTT_M1000_W300", "ZPrimeToTT_M1200_W360", "ZPrimeToTT_M1400_W420", "ZPrimeToTT_M1600_W480", "ZPrimeToTT_M1800_W540", "ZPrimeToTT_M2000_W600", "ZPrimeToTT_M2500_W750", "ZPrimeToTT_M3000_W900", "ZPrimeToTT_M3500_W1050", "ZPrimeToTT_M4000_W1200", "ZPrimeToTT_M4500_W1350", "ZPrimeToTT_M5000_W1500", "ZPrimeToTT_M6000_W1800", "ZPrimeToTT_M7000_W2100", "ZPrimeToTT_M8000_W2400", "ZPrimeToTT_M9000_W2700", "ZPrimeToTT_M400_W4", "ZPrimeToTT_M500_W5", "ZPrimeToTT_M600_W6", "ZPrimeToTT_M700_W7", "ZPrimeToTT_M800_W8", "ZPrimeToTT_M900_W9", "ZPrimeToTT_M1000_W10", "ZPrimeToTT_M1200_W12", "ZPrimeToTT_M1400_W14", "ZPrimeToTT_M1600_W16", "ZPrimeToTT_M1800_W18", "ZPrimeToTT_M2000_W20", "ZPrimeToTT_M2500_W25", "ZPrimeToTT_M3000_W30", "ZPrimeToTT_M3500_W35", "ZPrimeToTT_M4000_W40", "ZPrimeToTT_M4500_W45", "ZPrimeToTT_M5000_W50", "ZPrimeToTT_M6000_W60", "ZPrimeToTT_M7000_W70", "ZPrimeToTT_M8000_W80", "ZPrimeToTT_M9000_W90"};

    for(unsigned int i=0; i<names.size(); i++){
      if( ctx.get("dataset_version").find(names.at(i)) != std::string::npos ) sample_name = names.at(i);
    }
    if( (ctx.get("dataset_version").find("TTToHadronic") != std::string::npos) || (ctx.get("dataset_version").find("TTToSemiLeptonic") != std::string::npos) || (ctx.get("dataset_version").find("TTTo2L2Nu") != std::string::npos) ) sample_name = "TTbar";
    if( (ctx.get("dataset_version").find("WW") != std::string::npos) || (ctx.get("dataset_version").find("ZZ") != std::string::npos) || (ctx.get("dataset_version").find("WZ") != std::string::npos) ) sample_name = "Diboson";

    if(isMuon){
      TFile* f_btag2Dsf_muon = new TFile("/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/files_BTagSF/customBtagSF_muon_"+year+".root");
      ratio_hist_muon = (TH2F*)f_btag2Dsf_muon->Get("N_Jets_vs_HT_" + sample_name);
      ratio_hist_muon->SetDirectory(0);
    }
    else if(!isMuon){
      TFile* f_btag2Dsf_ele = new TFile("/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/files_BTagSF/customBtagSF_electron_"+year+".root");
      ratio_hist_ele = (TH2F*)f_btag2Dsf_ele->Get("N_Jets_vs_HT_" + sample_name);
      ratio_hist_ele->SetDirectory(0);
    }
  }

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

  h_Ele_E    = ctx.get_handle<float>("Ele_E");
  h_Ele_eta  = ctx.get_handle<float>("Ele_eta");
  h_Ele_phi  = ctx.get_handle<float>("Ele_phi");
  h_Ele_pt   = ctx.get_handle<float>("Ele_pt");

  h_MET_phi = ctx.get_handle<float>("MET_phi");
  h_MET_pt = ctx.get_handle<float>("MET_pt");

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
  //Only Ele or Mu variables!!
  NNModule.reset( new NeuralNetworkModule(ctx, "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL17_muon/model.pb", "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL17_muon/model.config.pbtxt"));
  //NNModule.reset( new NeuralNetworkModule(ctx, "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL17_ele/model.pb", "/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_DeepAK8_UL17_ele/model.config.pbtxt"));
}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeAnalysisModule_applyNN::process(uhh2::Event& event){

  if(debug) cout << "++++++++++++ NEW EVENT ++++++++++++++" << endl;
  if(debug) cout << " run.event: " << event.run << ". " << event.event << endl;
  // Initialize reco flags with false
  event.set(h_is_zprime_reconstructed_chi2, false);
  event.set(h_is_zprime_reconstructed_correctmatch, false);
  event.set(h_chi2,-100);
  event.set(h_weight,-100);

  event.set(h_NNoutput0, 0);
  event.set(h_NNoutput1, 0);
  event.set(h_NNoutput2, 0);

  // Run top-tagging
  if(ishotvr){
    TopTaggerHOTVR->process(event);
    hadronic_top->process(event);
  }else if(isdeepAK8){
    TopTaggerDeepAK8->process(event);
    hadronic_top->process(event);
  }
  if(debug) cout<<"Top Tagger ok"<<endl;

  fill_histograms(event, "Weights_Init");
  lumihists_Weights_Init->fill(event);

  if(!HEM_selection->passes(event)){
    if(!isMC) return false;
    else event.weight = event.weight*(1-0.64774715284); // calculated following instructions ar https://twiki.cern.ch/twiki/bin/view/CMS/PdmV2018Analysis
  }
  fill_histograms(event, "Weights_HEM");

  // pileup weight
  PUWeight_module->process(event);
  if(debug)  cout<<"PUWeight ok"<<endl;
  fill_histograms(event, "Weights_PU");
  lumihists_Weights_PU->fill(event);

  // lumi weight
  LumiWeight_module->process(event);
  if(debug)  cout<<"LumiWeight ok"<<endl;
  fill_histograms(event, "Weights_Lumi");
  lumihists_Weights_Lumi->fill(event);

  // top pt reweighting
  //TopPtReweight_module->process(event);
  //fill_histograms(event, "Weights_TopPt");
  //lumihists_Weights_TopPt->fill(event);

  // MC scale
  MCScale_module->process(event);
  fill_histograms(event, "Weights_MCScale");
  lumihists_Weights_MCScale->fill(event);

  // Prefiring weights
  if (isMC) {
    if (Prefiring_direction == "nominal") event.weight *= event.prefiringWeight;
    else if (Prefiring_direction == "up") event.weight *= event.prefiringWeightUp;
    else if (Prefiring_direction == "down") event.weight *= event.prefiringWeightDown;
  }
  fill_histograms(event, "Weights_Prefiring");

  // Write PSWeights from genInfo to own branch in output tree
  ps_weights->process(event);
  fill_histograms(event, "Weights_PS");
  lumihists_Weights_PS->fill(event);

  // DeepAK8 TopTag SFs
  if(isdeepAK8) sf_toptag->process(event);
  if(debug) cout << "Weights_TopTag_SF: ok" << endl;
  fill_histograms(event, "Weights_TopTag_SF");

  //Clean muon collection with ID based on muon pT
  double muon_pt_high(55.);
  bool muon_is_low = false;
  bool muon_is_high = false;

  if(isMuon){
    vector<Muon>* muons = event.muons;
    for(unsigned int i=0; i<muons->size(); i++){
      if(event.muons->at(i).pt()<=muon_pt_high){
        muon_is_low = true;
      }else{
        muon_is_high = true;
      }
    }
  }
  sort_by_pt<Muon>(*event.muons);

  //Clean ele collection with ID based on ele pT
  double electron_pt_high(120.);
  bool ele_is_low = false;
  bool ele_is_high = false;

  if(isElectron){
    vector<Electron>* electrons = event.electrons;
    for(unsigned int i=0; i<electrons->size(); i++){
      if(event.electrons->at(i).pt()<=electron_pt_high){
        ele_is_low = true;
      }else{
        ele_is_high = true;
      }
    }
  }
  sort_by_pt<Electron>(*event.electrons);

  // apply electron id scale factors
  if(isMuon){
    sf_ele_id_dummy->process(event);
  }
  if(isElectron){
    if(ele_is_low){
      sf_ele_id_low->process(event);
    }
    else if(ele_is_high){
      sf_ele_id_high->process(event);
    }
    fill_histograms(event, "IdEle_SF");
  }

  // apply muon isolation scale factors (low pT only)
  if(isMuon){
    if(muon_is_low){
      sf_muon_iso_low->process(event);
    }
    else if(muon_is_high){
      sf_muon_iso_low_dummy->process(event);
    }
    fill_histograms(event, "IsoMuon_SF");
  }
  if(isElectron){
    sf_muon_iso_low_dummy->process(event);
  }
  // apply muon id scale factors
  if(isMuon){
    if(muon_is_low){
      sf_muon_id_low->process(event);
    }
    else if(muon_is_high){
      sf_muon_id_high->process(event);
    }
    fill_histograms(event, "IdMuon_SF");
  }
  if(isElectron){
    sf_muon_id_dummy->process(event);
  }

  // apply electron reco scale factors
  if(isMuon){
    sf_ele_reco_dummy->process(event);
  }
  if(isElectron){
    sf_ele_reco->process(event);
    fill_histograms(event, "RecoEle_SF");
  }

  // apply muon reco scale factors
  sf_muon_reco->process(event);
  fill_histograms(event, "MuonReco_SF");


  // apply lepton trigger scale factors
  if(isMuon){
    if(muon_is_low){
      sf_muon_trigger_low->process(event);
    }
    if(muon_is_high){
      sf_muon_trigger_high->process(event);
    }
    fill_histograms(event, "TriggerMuon_SF");
  }
  if(isElectron){
    sf_muon_trigger_dummy->process(event);
  }

  //Fill histograms before BTagging SF - used to extract Custom BTag SF in (NJets,HT)
  fill_histograms(event, "BeforeBtagSF");

  // btag shape sf (Ak4 chs jets)
  // new: using new modules, with PUPPI-CHS matching
  sf_btagging->process(event);
  fill_histograms(event, "AfterBtagSF");

  // apply custom SF to correct for BTag SF shape effects on NJets/HT
  if(isMC && isMuon){
    float custom_sf;

    vector<Jet>* jets = event.jets;
    int Njets = jets->size();
    double st_jets = 0.;
    for(const auto & jet : *jets) st_jets += jet.pt();
    custom_sf = ratio_hist_muon->GetBinContent( ratio_hist_muon->GetXaxis()->FindBin(Njets), ratio_hist_muon->GetYaxis()->FindBin(st_jets) );

    event.weight *= custom_sf;
  }
  if(isMC && !isMuon){
    float custom_sf;

    vector<Jet>* jets = event.jets;
    int Njets = jets->size();
    double st_jets = 0.;
    for(const auto & jet : *jets) st_jets += jet.pt();
    custom_sf = ratio_hist_ele->GetBinContent( ratio_hist_ele->GetXaxis()->FindBin(Njets), ratio_hist_ele->GetYaxis()->FindBin(st_jets) );

    event.weight *= custom_sf;
  }
  fill_histograms(event, "AfterCustomBtagSF");

  // Higher order corrections - EWK & QCD NLO
  NLOCorrections_module->process(event);
  fill_histograms(event, "NLOCorrections");

  //apply ele trigger sf
  sf_ele_trigger->process(event);
  fill_histograms(event, "TriggerEle_SF");

  CandidateBuilder->process(event);
  if(debug) cout << "CandidateBuilder: ok" << endl;
  Chi2DiscriminatorZprime->process(event);
  if(debug) cout << "Chi2DiscriminatorZprime: ok" << endl;
  CorrectMatchDiscriminatorZprime->process(event);
  if(debug) cout << "CorrectMatchDiscriminatorZprime: ok" << endl;

  // Variables for NN
  Variables_module->process(event);
  fill_histograms(event, "NNInputsBeforeReweight");
  if(debug) cout << "Variables_module: ok" << endl;

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
  // Veto events with >= 2 TopTagged large-R jets
  if(!TopTagVetoSelection->passes(event)) return false;
  fill_histograms(event, "TopTagVeto");

  // out0=TTbar, out1=ST, out2=WJets
  if( out0 == max_score ){
    fill_histograms(event, "DNN_output0_beforeChi2Cut");
    if( ZprimeTopTag_selection->passes(event) ){
      fill_histograms(event, "DNN_output0_TopTag_beforeChi2Cut");
    }
    else{
      fill_histograms(event, "DNN_output0_NoTopTag_beforeChi2Cut");
    }
    if(Chi2_selection->passes(event)){  // cut on chi2<30 - only in SR == out0)
      fill_histograms(event, "DNN_output0");
      h_Zprime_SystVariations_DNN_output0->fill(event);
      h_Zprime_PDFVariations_DNN_output0->fill(event);
      if( ZprimeTopTag_selection->passes(event) ){
        fill_histograms(event, "DNN_output0_TopTag");
        h_Zprime_SystVariations_DNN_output0_TopTag->fill(event);
        h_Zprime_PDFVariations_DNN_output0_TopTag->fill(event);
      }
      else{
        fill_histograms(event, "DNN_output0_NoTopTag");
        h_Zprime_SystVariations_DNN_output0_NoTopTag->fill(event);
        h_Zprime_PDFVariations_DNN_output0_NoTopTag->fill(event);
      }
    }
  }

  if( out1 == max_score ){
    fill_histograms(event, "DNN_output1");
    h_Zprime_SystVariations_DNN_output1->fill(event);
    h_Zprime_PDFVariations_DNN_output1->fill(event);
    if( ZprimeTopTag_selection->passes(event) ){
      fill_histograms(event, "DNN_output1_TopTag");
      h_Zprime_SystVariations_DNN_output1_TopTag->fill(event);
      h_Zprime_PDFVariations_DNN_output1_TopTag->fill(event);
    }else{
      fill_histograms(event, "DNN_output1_NoTopTag");
      h_Zprime_SystVariations_DNN_output1_NoTopTag->fill(event);
      h_Zprime_PDFVariations_DNN_output1_NoTopTag->fill(event);
    }
  }

  if( out2 == max_score ){
    fill_histograms(event, "DNN_output2");
    h_Zprime_SystVariations_DNN_output2->fill(event);
    h_Zprime_PDFVariations_DNN_output2->fill(event);
    h_MistagHists->fill(event);
    if( ZprimeTopTag_selection->passes(event) ){
      fill_histograms(event, "DNN_output2_TopTag");
      h_Zprime_SystVariations_DNN_output2_TopTag->fill(event);
      h_Zprime_PDFVariations_DNN_output2_TopTag->fill(event);
    }else{
      fill_histograms(event, "DNN_output2_NoTopTag");
      h_Zprime_SystVariations_DNN_output2_NoTopTag->fill(event);
      h_Zprime_PDFVariations_DNN_output2_NoTopTag->fill(event);
    }
  }

  //Define categories on absolute value of theta star to reduce ttbar background - only in SR == out0
  if( out0 == max_score ){
    if(Chi2_selection->passes(event)){  // cut on chi2<30 - only in SR == out0
      if(AbsThetaStar_selection_bin1->passes(event)){
        fill_histograms(event, "DNN_output0_abs_thetastar_bin1");
        h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin1->fill(event);
        h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin1->fill(event);
      }if(AbsThetaStar_selection_bin2->passes(event)){
        fill_histograms(event, "DNN_output0_abs_thetastar_bin2");
        h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin2->fill(event);
        h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin2->fill(event);
      }if(AbsThetaStar_selection_bin3->passes(event)){
        fill_histograms(event, "DNN_output0_abs_thetastar_bin3");
        h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin3->fill(event);
        h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin3->fill(event);
      }if(AbsThetaStar_selection_bin4->passes(event)){
        fill_histograms(event, "DNN_output0_abs_thetastar_bin4");
        h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin4->fill(event);
        h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin4->fill(event);
      }if(AbsThetaStar_selection_bin5->passes(event)){
        fill_histograms(event, "DNN_output0_abs_thetastar_bin5");
        h_Zprime_SystVariations_DNN_output0_abs_thetastar_bin5->fill(event);
        h_Zprime_PDFVariations_DNN_output0_abs_thetastar_bin5->fill(event);
      }
      if( ZprimeTopTag_selection->passes(event) ){
        if(AbsThetaStar_selection_bin1->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_abs_thetastar_bin1");
          h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin1->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin1->fill(event);
        }if(AbsThetaStar_selection_bin2->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_abs_thetastar_bin2");
          h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin2->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin2->fill(event);
        }if(AbsThetaStar_selection_bin3->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_abs_thetastar_bin3");
          h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin3->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin3->fill(event);
        }if(AbsThetaStar_selection_bin4->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_abs_thetastar_bin4");
          h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin4->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin4->fill(event);
        }if(AbsThetaStar_selection_bin5->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_abs_thetastar_bin5");
          h_Zprime_SystVariations_DNN_output0_TopTag_abs_thetastar_bin5->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_abs_thetastar_bin5->fill(event);
        }
      }else{
        if(AbsThetaStar_selection_bin1->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_abs_thetastar_bin1");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin1->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin1->fill(event);
        }if(AbsThetaStar_selection_bin2->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_abs_thetastar_bin2");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin2->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin2->fill(event);
        }if(AbsThetaStar_selection_bin3->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_abs_thetastar_bin3");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin3->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin3->fill(event);
        }if(AbsThetaStar_selection_bin4->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_abs_thetastar_bin4");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin4->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin4->fill(event);
        }if(AbsThetaStar_selection_bin5->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_abs_thetastar_bin5");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_abs_thetastar_bin5->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_abs_thetastar_bin5->fill(event);
        }
      }
    } // end chi2 cut
  }//end out0

  //Define categories on theta star to reduce ttbar background - only in SR == out0
  if( out0 == max_score ){
    if(Chi2_selection->passes(event)){  // cut on chi2<30 - only in SR == out0
      if(ThetaStar_selection_bin1->passes(event)){
        fill_histograms(event, "DNN_output0_thetastar_bin1");
        h_Zprime_SystVariations_DNN_output0_thetastar_bin1->fill(event);
        h_Zprime_PDFVariations_DNN_output0_thetastar_bin1->fill(event);
      }if(ThetaStar_selection_bin2->passes(event)){
        fill_histograms(event, "DNN_output0_thetastar_bin2");
        h_Zprime_SystVariations_DNN_output0_thetastar_bin2->fill(event);
        h_Zprime_PDFVariations_DNN_output0_thetastar_bin2->fill(event);
      }if(ThetaStar_selection_bin3->passes(event)){
        fill_histograms(event, "DNN_output0_thetastar_bin3");
        h_Zprime_SystVariations_DNN_output0_thetastar_bin3->fill(event);
        h_Zprime_PDFVariations_DNN_output0_thetastar_bin3->fill(event);
      }if(ThetaStar_selection_bin4->passes(event)){
        fill_histograms(event, "DNN_output0_thetastar_bin4");
        h_Zprime_SystVariations_DNN_output0_thetastar_bin4->fill(event);
        h_Zprime_PDFVariations_DNN_output0_thetastar_bin4->fill(event);
      }if(ThetaStar_selection_bin5->passes(event)){
        fill_histograms(event, "DNN_output0_thetastar_bin5");
        h_Zprime_SystVariations_DNN_output0_thetastar_bin5->fill(event);
        h_Zprime_PDFVariations_DNN_output0_thetastar_bin5->fill(event);
      }if(ThetaStar_selection_bin6->passes(event)){
        fill_histograms(event, "DNN_output0_thetastar_bin6");
        h_Zprime_SystVariations_DNN_output0_thetastar_bin6->fill(event);
        h_Zprime_PDFVariations_DNN_output0_thetastar_bin6->fill(event);
      }
      if( ZprimeTopTag_selection->passes(event) ){
        if(ThetaStar_selection_bin1->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_thetastar_bin1");
          h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin1->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin1->fill(event);
        }if(ThetaStar_selection_bin2->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_thetastar_bin2");
          h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin2->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin2->fill(event);
        }if(ThetaStar_selection_bin3->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_thetastar_bin3");
          h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin3->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin3->fill(event);
        }if(ThetaStar_selection_bin4->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_thetastar_bin4");
          h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin4->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin4->fill(event);
        }if(ThetaStar_selection_bin5->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_thetastar_bin5");
          h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin5->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin5->fill(event);
        }if(ThetaStar_selection_bin6->passes(event)){
          fill_histograms(event, "DNN_output0_TopTag_thetastar_bin6");
          h_Zprime_SystVariations_DNN_output0_TopTag_thetastar_bin6->fill(event);
          h_Zprime_PDFVariations_DNN_output0_TopTag_thetastar_bin6->fill(event);
        }
      }else{
        if(ThetaStar_selection_bin1->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin1");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin1->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin1->fill(event);
        }if(ThetaStar_selection_bin2->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin2");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin2->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin2->fill(event);
        }if(ThetaStar_selection_bin3->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin3");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin3->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin3->fill(event);
        }if(ThetaStar_selection_bin4->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin4");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin4->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin4->fill(event);
        }if(ThetaStar_selection_bin5->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin5");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin5->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin5->fill(event);
        }if(ThetaStar_selection_bin6->passes(event)){
          fill_histograms(event, "DNN_output0_NoTopTag_thetastar_bin6");
          h_Zprime_SystVariations_DNN_output0_NoTopTag_thetastar_bin6->fill(event);
          h_Zprime_PDFVariations_DNN_output0_NoTopTag_thetastar_bin6->fill(event);
        }
      }
    } // end chi2 cut
  }//end out0

  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeAnalysisModule_applyNN)
