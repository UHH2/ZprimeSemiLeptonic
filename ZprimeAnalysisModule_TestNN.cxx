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
#include <UHH2/common/include/TopPtReweight.h>
#include <UHH2/common/include/Utils.h>
#include <UHH2/common/include/AdditionalSelections.h>
#include "UHH2/common/include/LuminosityHists.h"
#include <UHH2/common/include/MCWeight.h>
#include <UHH2/common/include/MuonHists.h>
#include <UHH2/common/include/ElectronHists.h>
#include <UHH2/common/include/JetHists.h>
#include <UHH2/common/include/EventHists.h>

#include <UHH2/ZprimeSemiLeptonic/include/ModuleBASE.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicSelections.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicModules.h>
#include <UHH2/ZprimeSemiLeptonic/include/TTbarLJHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeSemiLeptonicGeneratorHists.h>
#include <UHH2/ZprimeSemiLeptonic/include/ZprimeCandidate.h>

//#include <UHH2/common/include/TTbarGen.h>
#include <UHH2/common/include/TTbarReconstruction.h>
#include <UHH2/common/include/ReconstructionHypothesisDiscriminators.h>

using namespace std;
using namespace uhh2;

#include "UHH2/common/include/NeuralNetworkBase.hpp"


//#include <UHH2/Eigen/Eigen/Dense>

using namespace std;

//using Eigen::MatrixXd;
//using Eigen::VectorXd;
//using Eigen::EigenSolver;

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

uhh2::Event::Handle<float> h_DeltaR_j1_lep;
uhh2::Event::Handle<float> h_chi2;  
uhh2::Event::Handle<float> h_weight;
uhh2::Event::Handle<float> h_Lep_pt;
uhh2::Event::Handle<float> h_Lep_eta;
uhh2::Event::Handle<float> h_Lep_phi;
uhh2::Event::Handle<float> h_Nu_pt;
uhh2::Event::Handle<float> h_Nu_eta;
uhh2::Event::Handle<float> h_Nu_phi;
uhh2::Event::Handle<float> h_JetLep_pt;
uhh2::Event::Handle<float> h_JetLep_eta;
uhh2::Event::Handle<float> h_JetLep_phi;
uhh2::Event::Handle<float> h_JetHadAK8_pt;
uhh2::Event::Handle<float> h_JetHadAK8_eta;
uhh2::Event::Handle<float> h_JetHadAK8_phi;
uhh2::Event::Handle<float> h_JetHadAK4_1j_pt;
uhh2::Event::Handle<float> h_JetHadAK4_1j_eta;
uhh2::Event::Handle<float> h_JetHadAK4_1j_phi;
uhh2::Event::Handle<float> h_N_AK4_HadJets;
uhh2::Event::Handle<float> h_N_AK8_Jets;
uhh2::Event::Handle<float> h_N_AK4_LepJets;
uhh2::Event::Handle<float> h_JetHadAK4_2j_pt;
uhh2::Event::Handle<float> h_JetHadAK4_2j_eta;
uhh2::Event::Handle<float> h_JetHadAK4_2j_phi;
uhh2::Event::Handle<float> h_TopLep_pt;
uhh2::Event::Handle<float> h_TopLep_m;
uhh2::Event::Handle<float> h_TopLep_eta;
uhh2::Event::Handle<float> h_TopLep_phi;
uhh2::Event::Handle<float> h_TopHad_pt;
uhh2::Event::Handle<float> h_TopHad_m;
uhh2::Event::Handle<float> h_TopHad_eta;
uhh2::Event::Handle<float> h_TopHad_phi;
uhh2::Event::Handle<float> h_TopHadOverLep_pt;
uhh2::Event::Handle<float> h_DeltaR_j1j2_had;
uhh2::Event::Handle<float> h_DeltaR_j1lep_j1had;
uhh2::Event::Handle<float> h_DeltaR_j1_nu;
uhh2::Event::Handle<float> h_DeltaR_tlep_thad;
uhh2::Event::Handle<float> h_S11;
uhh2::Event::Handle<float> h_S12;
uhh2::Event::Handle<float> h_S13;
uhh2::Event::Handle<float> h_S22;
uhh2::Event::Handle<float> h_S23;
uhh2::Event::Handle<float> h_S33;

};

NeuralNetworkModule::NeuralNetworkModule(Context& ctx, const std::string & ModelName, const std::string& ConfigName): NeuralNetworkBase(ctx, ModelName, ConfigName){

h_DeltaR_j1_lep      = ctx.get_handle<float>("DeltaR_j1_lep");
h_chi2               = ctx.get_handle<float> ("rec_chi2");
h_Lep_pt             = ctx.get_handle<float> ("Lep_pt");
h_Lep_eta            = ctx.get_handle<float> ("Lep_eta");
h_Lep_phi            = ctx.get_handle<float> ("Lep_phi");
h_Nu_pt              = ctx.get_handle<float> ("Nu_pt");
h_Nu_eta             = ctx.get_handle<float> ("Nu_eta");
h_Nu_phi             = ctx.get_handle<float> ("Nu_phi");
h_JetLep_pt          = ctx.get_handle<float> ("JetLep_pt");
h_JetLep_eta         = ctx.get_handle<float> ("JetLep_eta");
h_JetLep_phi         = ctx.get_handle<float> ("JetLep_phi");
h_JetHadAK8_pt       = ctx.get_handle<float> ("JetHadAK8_pt");
h_JetHadAK8_eta      = ctx.get_handle<float> ("JetHadAK8_eta");
h_JetHadAK8_phi      = ctx.get_handle<float> ("JetHadAK8_phi");
h_JetHadAK4_1j_pt    = ctx.get_handle<float> ("JetHadAK4_1j_pt");
h_JetHadAK4_1j_eta   = ctx.get_handle<float> ("JetHadAK4_1j_eta");
h_JetHadAK4_1j_phi   = ctx.get_handle<float> ("JetHadAK4_1j_phi");
h_N_AK4_HadJets      = ctx.get_handle<float> ("N_AK4_HadJets");
h_N_AK8_Jets         = ctx.get_handle<float> ("N_AK8_Jets");
h_N_AK4_LepJets      = ctx.get_handle<float> ("N_AK4_LepJets");
h_JetHadAK4_2j_pt    = ctx.get_handle<float> ("JetHadAK4_2j_pt");
h_JetHadAK4_2j_eta   = ctx.get_handle<float> ("JetHadAK4_2j_eta");
h_JetHadAK4_2j_phi   = ctx.get_handle<float> ("JetHadAK4_2j_phi");
h_TopLep_pt          = ctx.get_handle<float> ("TopLep_pt");
h_TopLep_m           = ctx.get_handle<float> ("TopLep_m");
h_TopLep_eta         = ctx.get_handle<float> ("TopLep_eta");
h_TopLep_phi         = ctx.get_handle<float> ("TopLep_phi");
h_TopHad_pt          = ctx.get_handle<float> ("TopHad_pt");
h_TopHad_m           = ctx.get_handle<float> ("TopHad_m");
h_TopHad_eta         = ctx.get_handle<float> ("TopHad_eta");
h_TopHad_phi         = ctx.get_handle<float> ("TopHad_phi");
h_TopHadOverLep_pt   = ctx.get_handle<float> ("TopHadOverLep_pt");
h_DeltaR_j1j2_had    = ctx.get_handle<float> ("DeltaR_j1j2_had");
h_DeltaR_j1lep_j1had = ctx.get_handle<float> ("DeltaR_j1lep_j1had");
h_DeltaR_j1_nu       = ctx.get_handle<float> ("DeltaR_j1_nu");
h_DeltaR_tlep_thad   = ctx.get_handle<float> ("DeltaR_tlep_thad");
h_S11                = ctx.get_handle<float> ("S11");
h_S12                = ctx.get_handle<float> ("S12");
h_S13                = ctx.get_handle<float> ("S13");
h_S22                = ctx.get_handle<float> ("S22");
h_S23                = ctx.get_handle<float> ("S23");
h_S33                = ctx.get_handle<float> ("S33");
h_weight             = ctx.get_handle<float> ("weight");

}

void NeuralNetworkModule::CreateInputs(Event & event){
  NNInputs.clear();
  NNoutputs.clear();

  string varname[43];
  string scal[43];
  string min[43];
  string max[43];
  double min_val[43];
  double max_val[43];
  ifstream normfile ("/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/ZprimeSemiLeptonic/KerasNN/ML_test/NormInfo_sig.txt", ios::in);
  if (normfile.is_open()){ 
        for(int i = 0; i < 43; ++i)
        {   
            normfile >> varname[i] >> scal[i] >> min[i] >> max[i];
            min_val[i] = std::stod(min[i]);
            max_val[i] = std::stod(max[i]);
        }
    normfile.close();
  }


  NNInputs.push_back( tensorflow::Tensor(tensorflow::DT_FLOAT, {1, 43}));
/*
  NNInputs.at(0).tensor<float, 2>()(0,0) = event.get(h_DeltaR_j1_lep);
  NNInputs.at(0).tensor<float, 2>()(0,1) = event.get(h_DeltaR_j1_nu);
  NNInputs.at(0).tensor<float, 2>()(0,2) = event.get(h_DeltaR_j1j2_had);
  NNInputs.at(0).tensor<float, 2>()(0,3) = event.get(h_DeltaR_j1lep_j1had);
  NNInputs.at(0).tensor<float, 2>()(0,4) = event.get(h_DeltaR_tlep_thad);
  NNInputs.at(0).tensor<float, 2>()(0,5) = event.get(h_JetHadAK4_1j_eta);
  NNInputs.at(0).tensor<float, 2>()(0,6) = event.get(h_JetHadAK4_1j_phi);
  NNInputs.at(0).tensor<float, 2>()(0,7) = event.get(h_JetHadAK4_1j_pt);
  NNInputs.at(0).tensor<float, 2>()(0,8) = event.get(h_JetHadAK4_2j_eta);
  NNInputs.at(0).tensor<float, 2>()(0,9) = event.get(h_JetHadAK4_2j_phi);
  NNInputs.at(0).tensor<float, 2>()(0,10) = event.get(h_JetHadAK4_2j_pt);
  NNInputs.at(0).tensor<float, 2>()(0,11) = event.get(h_JetHadAK8_eta);
  NNInputs.at(0).tensor<float, 2>()(0,12) = event.get(h_JetHadAK8_phi);
  NNInputs.at(0).tensor<float, 2>()(0,13) = event.get(h_JetHadAK8_pt);
  NNInputs.at(0).tensor<float, 2>()(0,14) = event.get(h_JetLep_eta);
  NNInputs.at(0).tensor<float, 2>()(0,15) = event.get(h_JetLep_phi);
  NNInputs.at(0).tensor<float, 2>()(0,16) = event.get(h_JetLep_pt);
  NNInputs.at(0).tensor<float, 2>()(0,17) = event.get(h_Lep_eta);
  NNInputs.at(0).tensor<float, 2>()(0,18) = event.get(h_Lep_phi);
  NNInputs.at(0).tensor<float, 2>()(0,19) = event.get(h_Lep_pt);
  NNInputs.at(0).tensor<float, 2>()(0,20) = event.get(h_N_AK4_HadJets);
  NNInputs.at(0).tensor<float, 2>()(0,21) = event.get(h_N_AK4_LepJets);
  NNInputs.at(0).tensor<float, 2>()(0,22) = event.get(h_N_AK8_Jets);
  NNInputs.at(0).tensor<float, 2>()(0,23) = event.get(h_Nu_eta);
  NNInputs.at(0).tensor<float, 2>()(0,24) = event.get(h_Nu_phi);
  NNInputs.at(0).tensor<float, 2>()(0,25) = event.get(h_Nu_pt);
  NNInputs.at(0).tensor<float, 2>()(0,26) = event.get(h_S11);
  NNInputs.at(0).tensor<float, 2>()(0,27) = event.get(h_S12);
  NNInputs.at(0).tensor<float, 2>()(0,28) = event.get(h_S13);
  NNInputs.at(0).tensor<float, 2>()(0,29) = event.get(h_S22);
  NNInputs.at(0).tensor<float, 2>()(0,30) = event.get(h_S23);
  NNInputs.at(0).tensor<float, 2>()(0,31) = event.get(h_S33);
  NNInputs.at(0).tensor<float, 2>()(0,32) = event.get(h_TopHadOverLep_pt);
  NNInputs.at(0).tensor<float, 2>()(0,33) = event.get(h_TopHad_eta);
  NNInputs.at(0).tensor<float, 2>()(0,34) = event.get(h_TopHad_m);
  NNInputs.at(0).tensor<float, 2>()(0,35) = event.get(h_TopHad_phi);
  NNInputs.at(0).tensor<float, 2>()(0,36) = event.get(h_TopHad_pt);
  NNInputs.at(0).tensor<float, 2>()(0,37) = event.get(h_TopLep_eta);
  NNInputs.at(0).tensor<float, 2>()(0,38) = event.get(h_TopLep_m);
  NNInputs.at(0).tensor<float, 2>()(0,39) = event.get(h_TopLep_phi);
  NNInputs.at(0).tensor<float, 2>()(0,40) = event.get(h_TopLep_pt);
  NNInputs.at(0).tensor<float, 2>()(0,41) = event.get(h_chi2);
  NNInputs.at(0).tensor<float, 2>()(0,42) = event.get(h_weight);
*/



  NNInputs.at(0).tensor<float, 2>()(0,0)  = (event.get(h_DeltaR_j1_lep) - min_val[0]) / (max_val[0]-min_val[0]);
  NNInputs.at(0).tensor<float, 2>()(0,1)  = (event.get(h_DeltaR_j1_nu) - min_val[1]) / (max_val[1]-min_val[1]);
  NNInputs.at(0).tensor<float, 2>()(0,2)  = (event.get(h_DeltaR_j1j2_had) - min_val[2]) / (max_val[2]-min_val[2]);
  NNInputs.at(0).tensor<float, 2>()(0,3)  = (event.get(h_DeltaR_j1lep_j1had) - min_val[3]) / (max_val[3]-min_val[3]);
  NNInputs.at(0).tensor<float, 2>()(0,4)  = (event.get(h_DeltaR_tlep_thad) - min_val[4]) / (max_val[4]-min_val[4]);
  NNInputs.at(0).tensor<float, 2>()(0,5)  = (event.get(h_JetHadAK4_1j_eta) - min_val[5]) / (max_val[5]-min_val[5]);
  NNInputs.at(0).tensor<float, 2>()(0,6)  = (event.get(h_JetHadAK4_1j_phi) - min_val[6]) / (max_val[6]-min_val[6]);
  NNInputs.at(0).tensor<float, 2>()(0,7)  = (event.get(h_JetHadAK4_1j_pt) - min_val[7]) / (max_val[7]-min_val[7]);
  NNInputs.at(0).tensor<float, 2>()(0,8)  = (event.get(h_JetHadAK4_2j_eta) - min_val[8]) / (max_val[8]-min_val[8]);
  NNInputs.at(0).tensor<float, 2>()(0,9)  = (event.get(h_JetHadAK4_2j_phi) - min_val[9]) / (max_val[9]-min_val[9]);
  NNInputs.at(0).tensor<float, 2>()(0,10) = (event.get(h_JetHadAK4_2j_pt) - min_val[10]) / (max_val[10]-min_val[10]);
  NNInputs.at(0).tensor<float, 2>()(0,11) = (event.get(h_JetHadAK8_eta) - min_val[11]) / (max_val[11]-min_val[11]);
  NNInputs.at(0).tensor<float, 2>()(0,12) = (event.get(h_JetHadAK8_phi) - min_val[12]) / (max_val[12]-min_val[12]);
  NNInputs.at(0).tensor<float, 2>()(0,13) = (event.get(h_JetHadAK8_pt) - min_val[13]) / (max_val[13]-min_val[13]);
  NNInputs.at(0).tensor<float, 2>()(0,14) = (event.get(h_JetLep_eta) - min_val[14]) / (max_val[14]-min_val[14]);
  NNInputs.at(0).tensor<float, 2>()(0,15) = (event.get(h_JetLep_phi) - min_val[15]) / (max_val[15]-min_val[15]);
  NNInputs.at(0).tensor<float, 2>()(0,16) = (event.get(h_JetLep_pt) - min_val[16]) / (max_val[16]-min_val[16]);
  NNInputs.at(0).tensor<float, 2>()(0,17) = (event.get(h_Lep_eta) - min_val[17]) / (max_val[17]-min_val[17]);
  NNInputs.at(0).tensor<float, 2>()(0,18) = (event.get(h_Lep_phi) - min_val[18]) / (max_val[18]-min_val[18]);
  NNInputs.at(0).tensor<float, 2>()(0,19) = (event.get(h_Lep_pt) - min_val[19]) / (max_val[19]-min_val[19]);
  NNInputs.at(0).tensor<float, 2>()(0,20) = (event.get(h_N_AK4_HadJets) - min_val[20]) / (max_val[20]-min_val[20]);
  NNInputs.at(0).tensor<float, 2>()(0,21) = (event.get(h_N_AK4_LepJets) - min_val[21]) / (max_val[21]-min_val[21]);
  NNInputs.at(0).tensor<float, 2>()(0,22) = (event.get(h_N_AK8_Jets) - min_val[22]) / (max_val[22]-min_val[22]);
  NNInputs.at(0).tensor<float, 2>()(0,23) = (event.get(h_Nu_eta) - min_val[23]) / (max_val[23]-min_val[23]);
  NNInputs.at(0).tensor<float, 2>()(0,24) = (event.get(h_Nu_phi) - min_val[24]) / (max_val[24]-min_val[24]);
  NNInputs.at(0).tensor<float, 2>()(0,25) = (event.get(h_Nu_pt) - min_val[25]) / (max_val[25]-min_val[25]);
  NNInputs.at(0).tensor<float, 2>()(0,26) = (event.get(h_S11) - min_val[26]) / (max_val[26]-min_val[26]);
  NNInputs.at(0).tensor<float, 2>()(0,27) = (event.get(h_S12) - min_val[27]) / (max_val[27]-min_val[27]);
  NNInputs.at(0).tensor<float, 2>()(0,28) = (event.get(h_S13) - min_val[28]) / (max_val[28]-min_val[28]);
  NNInputs.at(0).tensor<float, 2>()(0,29) = (event.get(h_S22) - min_val[29]) / (max_val[29]-min_val[29]);
  NNInputs.at(0).tensor<float, 2>()(0,30) = (event.get(h_S23) - min_val[30]) / (max_val[30]-min_val[30]);
  NNInputs.at(0).tensor<float, 2>()(0,31) = (event.get(h_S33) - min_val[31]) / (max_val[31]-min_val[31]);
  NNInputs.at(0).tensor<float, 2>()(0,32) = (event.get(h_TopHadOverLep_pt) - min_val[32]) / (max_val[32]-min_val[32]);
  NNInputs.at(0).tensor<float, 2>()(0,33) = (event.get(h_TopHad_eta) - min_val[33]) / (max_val[33]-min_val[33]);
  NNInputs.at(0).tensor<float, 2>()(0,34) = (event.get(h_TopHad_m) - min_val[34]) / (max_val[34]-min_val[34]);
  NNInputs.at(0).tensor<float, 2>()(0,35) = (event.get(h_TopHad_phi) - min_val[35]) / (max_val[35]-min_val[35]);
  NNInputs.at(0).tensor<float, 2>()(0,36) = (event.get(h_TopHad_pt) - min_val[36]) / (max_val[36]-min_val[36]);
  NNInputs.at(0).tensor<float, 2>()(0,37) = (event.get(h_TopLep_eta) - min_val[37]) / (max_val[37]-min_val[37]);
  NNInputs.at(0).tensor<float, 2>()(0,38) = (event.get(h_TopLep_m) - min_val[38]) / (max_val[38]-min_val[38]);
  NNInputs.at(0).tensor<float, 2>()(0,39) = (event.get(h_TopLep_phi) - min_val[39]) / (max_val[39]-min_val[39]);
  NNInputs.at(0).tensor<float, 2>()(0,40) = (event.get(h_TopLep_pt) - min_val[40]) / (max_val[40]-min_val[40]);
  NNInputs.at(0).tensor<float, 2>()(0,41) = (event.get(h_chi2) - min_val[41]) / (max_val[41]-min_val[41]);
  NNInputs.at(0).tensor<float, 2>()(0,42) = (event.get(h_weight) - min_val[42]) / (max_val[42]-min_val[42]);


  if (NNInputs.size()!=LayerInputs.size()) throw logic_error("NeuralNetworkModule.cxx: Create a number of inputs diffetent wrt. LayerInputs.size()="+to_string(LayerInputs.size())); 
}



class ZprimeAnalysisModule_TestNN : public ModuleBASE {

public:
  explicit ZprimeAnalysisModule_TestNN(uhh2::Context&);
  virtual bool process(uhh2::Event&) override;
  void book_histograms(uhh2::Context&, vector<string>);
  void fill_histograms(uhh2::Event&, string);

protected:

  bool debug;
  // Cleaners (to make sure the pre-selection did everything right)
  std::unique_ptr<MuonCleaner> muon_cleaner;
  std::unique_ptr<ElectronCleaner> electron_cleaner;

  // Scale Factors -- Systematics
  unique_ptr<MCMuonScaleFactor> MuonID_module, MuonTrigger_module;

  // AnalysisModules
  unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, printer_genparticles; //CSVWeight_module

  // Taggers
  unique_ptr<AK8PuppiTopTagger> TopTaggerPuppi;

  // Mass reconstruction
  unique_ptr<ZprimeCandidateBuilder> CandidateBuilder;

  // Chi2 discriminator
  unique_ptr<ZprimeChi2Discriminator> Chi2DiscriminatorZprime;
  unique_ptr<ZprimeCorrectMatchDiscriminator> CorrectMatchDiscriminatorZprime;

  // Selections
  unique_ptr<Selection> Trigger1_selection, Trigger2_selection, NMuon1_selection, NMuon2_selection, NElectron_selection, Jet1_selection, Jet2_selection, Met_selection, Chi2_selection, TTbarMatchable_selection, Chi2CandidateMatched_selection, ZprimeTopTag_selection, BlindData_selection;
  unique_ptr<Selection> TwoDCut_selection;
  std::unique_ptr<uhh2::Selection> met_sel;
  std::unique_ptr<uhh2::Selection> htlep_sel;
  std::unique_ptr<Selection> sel_1btag, sel_2btag;
  std::unique_ptr<Selection> TopJetBtagSubjet_selection;
  std::unique_ptr<Selection> HEM_selection;


  //Handles
  Event::Handle<bool> h_is_zprime_reconstructed_chi2, h_is_zprime_reconstructed_correctmatch;
  Event::Handle<float> h_MET;   Event::Handle<int> h_NPV;
  Event::Handle<float> h_lep1_pt; Event::Handle<float> h_lep1_eta; 
  Event::Handle<float> h_ak4jet1_pt; Event::Handle<float> h_ak4jet1_eta; 
  Event::Handle<float> h_ak8jet1_pt; Event::Handle<float> h_ak8jet1_eta; 
  Event::Handle<float> h_Mttbar; 

  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;


  float inv_mass(const LorentzVector& p4){ return p4.isTimelike() ? p4.mass() : -sqrt(-p4.mass2()); }

  // Configuration
  bool isMC, ispuppi, islooserselection;
  string Sys_MuonID, Sys_MuonTrigger, Sys_PU;
  TString sample;
  int runnr_oldtriggers = 299368;

  bool is2016v2, is2016v3, is2017v2, is2018;
  bool isMuon, isElectron;

  Event::Handle<float> h_DeltaR_j1_lep;
  Event::Handle<float> h_chi2;
  Event::Handle<float> h_weight;
  Event::Handle<float> h_Lep_pt;
  Event::Handle<float> h_Lep_eta;
  Event::Handle<float> h_Lep_phi;
  Event::Handle<float> h_Nu_pt;
  Event::Handle<float> h_Nu_eta;
  Event::Handle<float> h_Nu_phi;
  Event::Handle<float> h_JetLep_pt;
  Event::Handle<float> h_JetLep_eta;
  Event::Handle<float> h_JetLep_phi;
  Event::Handle<float> h_JetHadAK8_pt;
  Event::Handle<float> h_JetHadAK8_eta;
  Event::Handle<float> h_JetHadAK8_phi;
  Event::Handle<float> h_JetHadAK4_1j_pt;
  Event::Handle<float> h_JetHadAK4_1j_eta;
  Event::Handle<float> h_JetHadAK4_1j_phi;
  Event::Handle<float> h_N_AK4_HadJets;
  Event::Handle<float> h_N_AK8_Jets;
  Event::Handle<float> h_N_AK4_LepJets;
  Event::Handle<float> h_JetHadAK4_2j_pt;
  Event::Handle<float> h_JetHadAK4_2j_eta;
  Event::Handle<float> h_JetHadAK4_2j_phi;
  Event::Handle<float> h_TopLep_pt;
  Event::Handle<float> h_TopLep_m;
  Event::Handle<float> h_TopLep_eta;
  Event::Handle<float> h_TopLep_phi;
  Event::Handle<float> h_TopHad_pt;
  Event::Handle<float> h_TopHad_m;
  Event::Handle<float> h_TopHad_eta;
  Event::Handle<float> h_TopHad_phi;
  Event::Handle<float> h_TopHadOverLep_pt;
  Event::Handle<float> h_DeltaR_j1j2_had;
  Event::Handle<float> h_DeltaR_j1lep_j1had;
  Event::Handle<float> h_DeltaR_j1_nu;
  Event::Handle<float> h_DeltaR_tlep_thad;
  Event::Handle<float> h_S11;
  Event::Handle<float> h_S12;
  Event::Handle<float> h_S13;
  Event::Handle<float> h_S22;
  Event::Handle<float> h_S23;
  Event::Handle<float> h_S33;


  Event::Handle<std::vector<tensorflow::Tensor> > h_NNoutput;
  Event::Handle<double> h_NNoutput0;
  Event::Handle<double> h_NNoutput1;
  Event::Handle<double> h_NNoutput2;

  std::unique_ptr<NeuralNetworkModule> NNModule;

};

void ZprimeAnalysisModule_TestNN::book_histograms(uhh2::Context& ctx, vector<string> tags){
  for(const auto & tag : tags){
    string mytag = tag + "_Skimming";
    // book_HFolder(mytag, new TTbarLJHistsSkimming(ctx,mytag));
    mytag = tag+"_General";
    book_HFolder(mytag, new ZprimeSemiLeptonicHists(ctx,mytag));
    mytag = tag+"_Muons";
    book_HFolder(mytag, new MuonHists(ctx,mytag));
    mytag = tag+"_Electrons";
    book_HFolder(mytag, new ElectronHists(ctx,mytag));
    mytag = tag+"_Jets";
    book_HFolder(mytag, new JetHists(ctx,mytag));
    mytag = tag+"_Event";
    book_HFolder(mytag, new EventHists(ctx,mytag));
    mytag = tag+"_Generator";
    book_HFolder(mytag, new ZprimeSemiLeptonicGeneratorHists(ctx,mytag));
  }
}

void ZprimeAnalysisModule_TestNN::fill_histograms(uhh2::Event& event, string tag){
  string mytag = tag + "_Skimming";
  // HFolder(mytag)->fill(event);
  mytag = tag+"_General";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Muons";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Electrons";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Jets";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Event";
  HFolder(mytag)->fill(event);
  mytag = tag+"_Generator";
  HFolder(mytag)->fill(event);
}

/*
█  ██████  ██████  ███    ██ ███████ ████████ ██████  ██    ██  ██████ ████████  ██████  ██████
█ ██      ██    ██ ████   ██ ██         ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█ ██      ██    ██ ██ ██  ██ ███████    ██    ██████  ██    ██ ██         ██    ██    ██ ██████
█ ██      ██    ██ ██  ██ ██      ██    ██    ██   ██ ██    ██ ██         ██    ██    ██ ██   ██
█  ██████  ██████  ██   ████ ███████    ██    ██   ██  ██████   ██████    ██     ██████  ██   ██
*/

ZprimeAnalysisModule_TestNN::ZprimeAnalysisModule_TestNN(uhh2::Context& ctx){
  //  debug = true;
  debug = false;
  for(auto & kv : ctx.get_all()){
    cout << " " << kv.first << " = " << kv.second << endl;
  }
  // Configuration
  isMC = (ctx.get("dataset_type") == "MC");
  ispuppi = (ctx.get("is_puppi") == "true");
  TString mode = "chs";
  if(ispuppi) mode = "puppi";
  string tmp = ctx.get("dataset_version");
  sample = tmp;
  is2016v2 = (ctx.get("dataset_version").find("2016v2") != std::string::npos);
  is2016v3 = (ctx.get("dataset_version").find("2016v3") != std::string::npos);
  is2017v2 = (ctx.get("dataset_version").find("2017v2") != std::string::npos);
  is2018 = (ctx.get("dataset_version").find("2018") != std::string::npos);


  // Important selection values
  islooserselection = (ctx.get("is_looser_selection") == "true");
  double muon_pt(55.);
  double elec_pt(80.);
  double jet1_pt(150.);
  double jet2_pt(50.);
  //  double stlep_plus_met(150.);
  double chi2_max(30.);
  double mtt_blind(3000.);
  int nmuon_min1, nmuon_max1;
  int nmuon_min2, nmuon_max2;
  int nele_min, nele_max;
  string trigger1,trigger2;// trigger3;
  double MET_cut, HT_lep_cut;
  isMuon = false; isElectron = false;
  if(ctx.get("channel") == "muon") isMuon = true;
  if(ctx.get("channel") == "electron") isElectron = true;

  if(isMuon){//semileptonic muon channel
    trigger1 = "HLT_Mu50_v*";
    if(is2016v2 || is2016v3)
      //trigger2 = "HLT_TkMu50_v*";
      trigger2 = "HLT_Mu50_v*"; //TkMu path does not exist in 2017/2018 and RunB 2016
    else
      trigger2 = "HLT_Mu50_v*"; //TkMu path does not exist in 2017/2018
    nmuon_min1 = 1, nmuon_max1 = -1;
    nmuon_min2 = 1, nmuon_max2 = 1;
    nele_min = 0; nele_max = 0;
    MET_cut = 50;
    jet1_pt = 150.;
    HT_lep_cut = 150;
    //HT_lep_cut = 0; //loose cuts
  }
  if(isElectron){//semileptonic electron channel
    nmuon_min1 = 0; nmuon_max1 = 0;
    nmuon_min2 = 0; nmuon_max2 = 0;
    nele_min = 1; nele_max = 1;
    trigger1 = "HLT_Ele50_CaloIdVT_GsfTrkIdT_PFJet165_v*";
    trigger2 = "HLT_Ele115_CaloIdVT_GsfTrkIdT_v*";
    //MET_cut = 120;
    MET_cut = 50; // loose cuts
    jet1_pt = 185.;
    HT_lep_cut = 0;
    //    trigger3 = "HLT\_Ele115_v*";
  }

 // Remove TwoD cut for DNN 
  double TwoD_dr = 0.4, TwoD_ptrel = 25.;
  if(islooserselection){
    jet1_pt = 100.;
    TwoD_dr = 0.2;
    TwoD_ptrel = 10.;
    //    stlep_plus_met = 100.;
  }
  const MuonId muonID(PtEtaCut(muon_pt, 2.4));
  const ElectronId electronID(PtEtaSCCut(elec_pt, 2.5));

  

  Sys_MuonID = ctx.get("Sys_MuonID");
  Sys_MuonTrigger = ctx.get("Sys_MuonTrigger");
  Sys_PU = ctx.get("Sys_PU");


  // Modules
  printer_genparticles.reset(new GenParticlesPrinter(ctx));
  muon_cleaner.reset(new MuonCleaner(muonID));
  electron_cleaner.reset(new ElectronCleaner(electronID));
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  //CSVWeight_module.reset(new MCCSVv2ShapeSystematic(ctx, "jets","central","iterativefit","","MCCSVv2ShapeSystematic")); //old version, replaced with MCBTagDiscriminantReweighting

  //if((is2016v3 || is2016v2) && isMuon){
  //  MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root", "MC_NUM_TightID_DEN_genTracks_PAR_pt_eta", 0., "MuonID", true, Sys_MuonID));
  //  MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu50_OR_IsoTkMu50_PtEtaBins", 0.5, "MuonTrigger", true, Sys_MuonTrigger));
  //}
  //if(is2017v2 || is2018){
  //  MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2017/MuonID_94X_RunBCDEF_SF_ID.root", "NUM_HighPtID_DEN_genTracks_pair_newTuneP_probe_pt_abseta", 0., "HighPtID", true, Sys_MuonID));
  //  MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2017/MuonTrigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "Mu50_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger", true, Sys_MuonTrigger));
  //}

  // Selection modules
  Trigger1_selection.reset(new TriggerSelection(trigger1));
  Trigger2_selection.reset(new TriggerSelection(trigger2));
  //  Trigger3_selection.reset(new TriggerSelection(trigger3));
  NMuon1_selection.reset(new NMuonSelection(nmuon_min1, nmuon_max1));
  NMuon2_selection.reset(new NMuonSelection(nmuon_min2, nmuon_max2));
  NElectron_selection.reset(new NElectronSelection(nele_min, nele_max));
  TwoDCut_selection.reset(new TwoDCut(TwoD_dr, TwoD_ptrel));
  Jet1_selection.reset(new NJetSelection(1, -1, JetId(PtEtaCut(jet1_pt, 2.4))));
  Jet2_selection.reset(new NJetSelection(2, -1, JetId(PtEtaCut(jet2_pt, 2.4))));
  //  STlepPlusMet_selection.reset(new STlepPlusMetCut(stlep_plus_met, -1.));
  met_sel.reset(new METCut  (MET_cut   , uhh2::infinity));
  htlep_sel.reset(new HTlepCut(HT_lep_cut, uhh2::infinity));

  TTbarMatchable_selection.reset(new TTbarSemiLepMatchableSelection());
  Chi2_selection.reset(new Chi2Cut(ctx, 0., chi2_max));
  //TTbarMatchable_selection.reset(new TTbarSemiLepMatchableSelection());
  Chi2CandidateMatched_selection.reset(new Chi2CandidateMatchedSelection(ctx));
  ZprimeTopTag_selection.reset(new ZprimeTopTagSelection(ctx));
  BlindData_selection.reset(new BlindDataSelection(ctx, mtt_blind));

  HEM_selection.reset(new HEMSelection(ctx)); // HEM issue in 2017, veto on electron and jets

  // Taggers
  TopTaggerPuppi.reset(new AK8PuppiTopTagger(ctx));

  // Zprime candidate builder
  CandidateBuilder.reset(new ZprimeCandidateBuilder(ctx, mode));

  // Zprime discriminators
  CorrectMatchDiscriminatorZprime.reset(new ZprimeCorrectMatchDiscriminator(ctx));
  h_is_zprime_reconstructed_correctmatch = ctx.get_handle<bool>("is_zprime_reconstructed_correctmatch");
  Chi2DiscriminatorZprime.reset(new ZprimeChi2Discriminator(ctx));
  h_is_zprime_reconstructed_chi2 = ctx.get_handle<bool>("is_zprime_reconstructed_chi2");
  //CorrectMatchDiscriminatorZprime.reset(new ZprimeCorrectMatchDiscriminator(ctx));
  //h_is_zprime_reconstructed_correctmatch = ctx.get_handle<bool>("is_zprime_reconstructed_correctmatch");
  h_BestZprimeCandidateChi2 = ctx.get_handle<ZprimeCandidate*>("ZprimeCandidateBestChi2");
  //  h_chi2 = ctx.get_handle<float>("rec_chi2");
  //h_chi2 = ctx.declare_event_output<float> ("rec_chi2");
  h_MET = ctx.declare_event_output<float> ("met_pt");
  h_Mttbar = ctx.declare_event_output<float> ("Mttbar");

  h_lep1_pt = ctx.declare_event_output<float> ("lep1_pt");
  h_lep1_eta = ctx.declare_event_output<float> ("lep1_eta");
  h_ak4jet1_pt = ctx.declare_event_output<float> ("ak4jet1_pt");
  h_ak4jet1_eta = ctx.declare_event_output<float> ("ak4jet1_eta");
  h_ak8jet1_pt = ctx.declare_event_output<float> ("ak8jet1_pt");
  h_ak8jet1_eta = ctx.declare_event_output<float> ("ak8jet1_eta");

  h_NPV = ctx.declare_event_output<int> ("NPV");
  //h_weight = ctx.declare_event_output<float> ("weight");

  // btag 
  CSVBTag::wp btag_wp = CSVBTag::WP_TIGHT; // b-tag workingpoint
  JetId id_btag = CSVBTag(btag_wp);

  // DeepCSVBTag::wp btag_wp = DeepCSVBTag::WP_TIGHT; // b-tag workingpoint
  // JetId id_btag = DeepCSVBTag(btag_wp);

  // DeepJetBTag::wp btag_wp = DeepJetBTag::WP_TIGHT; // b-tag workingpoint
  // JetId id_btag = DeepJetBTag(btag_wp);

  sel_1btag.reset(new NJetSelection(1, 1, id_btag));
  sel_2btag.reset(new NJetSelection(2,-1, id_btag));


  TopJetBtagSubjet_selection.reset(new ZprimeBTagFatSubJetSelection(ctx));

  // Book histograms
  vector<string> histogram_tags = {"Weights", "Muon1", "Trigger", "Muon2", "Electron1", "Jet1", "Jet2", "MET", "HTlep", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction", "Btags2", "Btags1","TopJetBtagSubjet","DNN_output0","DNN_output1","DNN_output2"};
  book_histograms(ctx, histogram_tags);

//  h_topjets = ctx.get_handle<std::vector<TopJet>>("toppuppijets");DeltaR_j1_lep
  h_DeltaR_j1_lep      = ctx.get_handle<float> ("DeltaR_j1_lep");
  h_chi2               = ctx.get_handle<float> ("rec_chi2");
  h_Lep_pt             = ctx.get_handle<float> ("Lep_pt");
  h_Lep_eta            = ctx.get_handle<float> ("Lep_eta");
  h_Lep_phi            = ctx.get_handle<float> ("Lep_phi");
  h_Nu_pt              = ctx.get_handle<float> ("Nu_pt");
  h_Nu_eta             = ctx.get_handle<float> ("Nu_eta");
  h_Nu_phi             = ctx.get_handle<float> ("Nu_phi");
  h_JetLep_pt          = ctx.get_handle<float> ("JetLep_pt");
  h_JetLep_eta         = ctx.get_handle<float> ("JetLep_eta");
  h_JetLep_phi         = ctx.get_handle<float> ("JetLep_phi");
  h_JetHadAK8_pt       = ctx.get_handle<float> ("JetHadAK8_pt");
  h_JetHadAK8_eta      = ctx.get_handle<float> ("JetHadAK8_eta");
  h_JetHadAK8_phi      = ctx.get_handle<float> ("JetHadAK8_phi");
  h_JetHadAK4_1j_pt    = ctx.get_handle<float> ("JetHadAK4_1j_pt");
  h_JetHadAK4_1j_eta   = ctx.get_handle<float> ("JetHadAK4_1j_eta");
  h_JetHadAK4_1j_phi   = ctx.get_handle<float> ("JetHadAK4_1j_phi");
  h_N_AK4_HadJets      = ctx.get_handle<float> ("N_AK4_HadJets");
  h_N_AK8_Jets         = ctx.get_handle<float> ("N_AK8_Jets");
  h_N_AK4_LepJets      = ctx.get_handle<float> ("N_AK4_LepJets");
  h_JetHadAK4_2j_pt    = ctx.get_handle<float> ("JetHadAK4_2j_pt");
  h_JetHadAK4_2j_eta   = ctx.get_handle<float> ("JetHadAK4_2j_eta");
  h_JetHadAK4_2j_phi   = ctx.get_handle<float> ("JetHadAK4_2j_phi");
  h_TopLep_pt          = ctx.get_handle<float> ("TopLep_pt");
  h_TopLep_m           = ctx.get_handle<float> ("TopLep_m");
  h_TopLep_eta         = ctx.get_handle<float> ("TopLep_eta");
  h_TopLep_phi         = ctx.get_handle<float> ("TopLep_phi");
  h_TopHad_pt          = ctx.get_handle<float> ("TopHad_pt");
  h_TopHad_m           = ctx.get_handle<float> ("TopHad_m");
  h_TopHad_eta         = ctx.get_handle<float> ("TopHad_eta");
  h_TopHad_phi         = ctx.get_handle<float> ("TopHad_phi");
  h_TopHadOverLep_pt   = ctx.get_handle<float> ("TopHadOverLep_pt");
  h_DeltaR_j1j2_had    = ctx.get_handle<float> ("DeltaR_j1j2_had");
  h_DeltaR_j1lep_j1had = ctx.get_handle<float> ("DeltaR_j1lep_j1had");
  h_DeltaR_j1_nu       = ctx.get_handle<float> ("DeltaR_j1_nu");
  h_DeltaR_tlep_thad   = ctx.get_handle<float> ("DeltaR_tlep_thad");
  h_S11                = ctx.get_handle<float> ("S11");
  h_S12                = ctx.get_handle<float> ("S12");
  h_S13                = ctx.get_handle<float> ("S13");
  h_S22                = ctx.get_handle<float> ("S22");
  h_S23                = ctx.get_handle<float> ("S23");
  h_S33                = ctx.get_handle<float> ("S33");
  h_weight             = ctx.get_handle<float> ("weight");


  h_NNoutput = ctx.get_handle<std::vector<tensorflow::Tensor>>("NNoutput");
  h_NNoutput0 = ctx.declare_event_output<double>("NNoutput0");
  h_NNoutput1 = ctx.declare_event_output<double>("NNoutput1");
  h_NNoutput2 = ctx.declare_event_output<double>("NNoutput2");
  NNModule.reset( new NeuralNetworkModule(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/ZprimeSemiLeptonic/KerasNN/ML_test/model_sig.pb", "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/ZprimeSemiLeptonic/KerasNN/ML_test/model_sig.config.pbtxt"));

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeAnalysisModule_TestNN::process(uhh2::Event& event){

  if(debug)   cout << "++++++++++++ NEW EVENT ++++++++++++++" << endl;
  if(debug)   cout<<" run.event: "<<event.run<<". "<<event.event<<endl;
  // Initialize reco flags with false
  event.set(h_is_zprime_reconstructed_chi2, false);
  event.set(h_is_zprime_reconstructed_correctmatch, false);

  //event.set(h_chi2,-100);
  event.set(h_MET,-100);
  event.set(h_Mttbar,-100);
  event.set(h_lep1_pt,-100);
  event.set(h_lep1_eta,-100);
  event.set(h_ak4jet1_pt,-100);
  event.set(h_ak4jet1_eta,-100);
  event.set(h_ak8jet1_pt,-100);
  event.set(h_ak8jet1_eta,-100);
  event.set(h_NPV,-100);
  //event.set(h_weight,0);

  event.set(h_NNoutput0, 0); 
  event.set(h_NNoutput1, 0); 
  event.set(h_NNoutput2, 0);


  // Printing
  // if(!event.isRealData) printer_genparticles->process(event);

  // TODO Apply things that should've been done in the pre-selection already... Fix pre-selection and then remove these steps
  if(isMuon) muon_cleaner->process(event);
  if(isElectron) electron_cleaner->process(event);
  if(debug)  cout<<"Muon and Electron cleaner ok"<<endl;
  //if(isElectron && !HEM_selection->passes(event)) return false;


  // Weight modules
  LumiWeight_module->process(event);
  if(debug)  cout<<"LumiWeight ok"<<endl;
  // in fisrt round re-weighting is switched off
  PUWeight_module->process(event);
  //if(debug)  cout<<"PUWeight ok"<<endl;
  //CSVWeight_module->process(event);
  //if(isMuon){
  //  MuonID_module->process(event);
  //  if(debug)  cout<<"MuonID ok"<<endl;
  //}
  // Run top-tagging
  TopTaggerPuppi->process(event);
  if(debug) cout<<"Top Tagger ok"<<endl;
  fill_histograms(event, "Weights");
 
  // if(isMC || (!isMC && event.run >= runnr_oldtriggers)){
  //   if(!(Trigger1_selection->passes(event) || Trigger2_selection->passes(event) || Trigger3_selection->passes(event))) return false;
  // }
  // else{
  //   if(!(Trigger1_selection->passes(event))) return false;
  // }
  if(!(Trigger1_selection->passes(event)|| Trigger2_selection->passes(event))) return false;
  if(isMuon){
    if(!NMuon1_selection->passes(event)) return false;
    fill_histograms(event, "Muon1");
//    MuonTrigger_module->process_onemuon(event, 0);
//    fill_histograms(event, "Trigger");
    if(!NMuon2_selection->passes(event)) return false;
    fill_histograms(event, "Muon2");
  }
  if(isElectron){
    if(!NElectron_selection->passes(event)) return false;
    fill_histograms(event, "Electron1");
  }
  //  if(event.electrons->size()<1 && event.muons->size()<1) return false; //veto events without leptons
  if((event.muons->size()+event.electrons->size()) != 1) return false; //veto events without leptons or with too many 
  if(debug) cout<<"N leptons ok: Nelectrons="<<event.electrons->size()<<" Nmuons="<<event.muons->size()<<endl;
  if(!TwoDCut_selection->passes(event)) return false;
  //fill_histograms(event, "TwoDCut");

  // Here, the Zprime must be reconstructed (we ensured to have >= 2 AK4 jets, >= 1 muon)
  // Only consider well-separated AK4 jets
  // //FixME: 
  // for(const TopJet & chsjet : *event.topjets){
  //   int n_separatedjets = 0;
  //   for(unsigned int k = 0; k < event.jets->size(); k++){
  //     if(deltaR(event.jets->at(k), chsjet) > 1.2) n_separatedjets++;
  //   }
  //   //    cout<<"n_separatedjets = "<<n_separatedjets<<endl;
  //   if(n_separatedjets<1) return false;
  // }

  CandidateBuilder->process(event);
  if(debug) cout<<"CandidateBuilder is ok"<<endl;
  Chi2DiscriminatorZprime->process(event);
  if(debug)  cout<<"Chi2DiscriminatorZprime is ok"<<endl;
  CorrectMatchDiscriminatorZprime->process(event);
  if(debug) cout<<"CorrectMatchDiscriminatorZprime is ok"<<endl;
  if(sample.Contains("_blinded")){
    if(!BlindData_selection->passes(event)) return false;
  }
  if(!Jet1_selection->passes(event)) return false;
  if(debug) cout<<"Jet1_selection is ok"<<endl;
  fill_histograms(event, "Jet1");

  if(!Jet2_selection->passes(event)) return false;
  if(debug) cout<<"Jet2_selection is ok"<<endl;
  fill_histograms(event, "Jet2");

  // if(!STlepPlusMet_selection->passes(event)) return false;
  // fill_histograms(event, "STlepPlusMet");

  // MET selection
  if(!met_sel->passes(event)) return false;
  if(debug) cout<<"MET is ok"<<endl;
  fill_histograms(event, "MET");
  if(isMuon){
    if(!htlep_sel->passes(event)) return false;
    fill_histograms(event, "HTlep");
    if(debug) cout<<"HTlep is ok"<<endl;
  }

  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "MatchableBeforeChi2Cut");
  else fill_histograms(event, "NotMatchableBeforeChi2Cut");
  if(debug) cout<<"TTbarMatchable_selection is ok"<<endl;

  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatchBeforeChi2Cut");
  else fill_histograms(event, "NotCorrectMatchBeforeChi2Cut");
  if(debug) cout<<"Chi2CandidateMatched_selection is ok"<<endl;

  if(!Chi2_selection->passes(event)) return false;
  fill_histograms(event, "Chi2");

  if(debug) cout<<"Chi2_selection is ok"<<endl;

  if(TTbarMatchable_selection->passes(event)) fill_histograms(event, "Matchable");
  else fill_histograms(event, "NotMatchable");
  if(debug) cout<<"TTbarMatchable_selection is ok"<<endl;

  if(Chi2CandidateMatched_selection->passes(event)) fill_histograms(event, "CorrectMatch");
  else fill_histograms(event, "NotCorrectMatch");
  if(debug) cout<<"Chi2CandidateMatched_selection is ok"<<endl;

  if(ZprimeTopTag_selection->passes(event)) fill_histograms(event, "TopTagReconstruction");
  else fill_histograms(event, "NotTopTagReconstruction");
  if(debug) cout<<"ZprimeTopTag_selection is ok"<<endl;

  //Test with b-tagging
  if(sel_2btag->passes(event)) fill_histograms(event, "Btags2");
  if(sel_1btag->passes(event)) fill_histograms(event, "Btags1");
  if(debug) cout<<"Btags1 is ok"<<endl;
  if(TopJetBtagSubjet_selection->passes(event)) fill_histograms(event, "TopJetBtagSubjet");
  if(debug) cout<<"TopJetBtagSubjet_selection is ok"<<endl;

  //Fill some vars for monitoring and comparison
  bool is_zprime_reconstructed_chi2 = event.get(h_is_zprime_reconstructed_chi2); 
  if(is_zprime_reconstructed_chi2){
    ZprimeCandidate* BestZprimeCandidate = event.get(h_BestZprimeCandidateChi2);
    //    float chi2 = BestZprimeCandidate->discriminator("chi2_total");
    event.set(h_chi2,BestZprimeCandidate->discriminator("chi2_total"));
    event.set(h_Mttbar,BestZprimeCandidate->Zprime_v4().M());
  }

  if(debug) cout<<"Set ttbar reconstruction vars for monitoring"<<endl;

  //event.set(h_weight,event.weight);
  event.set(h_MET,event.met->pt());
  if(isMuon){
    event.set(h_lep1_pt,event.muons->at(0).pt());
    event.set(h_lep1_eta,event.muons->at(0).eta());
  }
  if(isElectron){
    event.set(h_lep1_pt,event.electrons->at(0).pt());
    event.set(h_lep1_eta,event.electrons->at(0).eta());
  }
  if(event.jets->size()>0){
    event.set(h_ak4jet1_pt,event.jets->at(0).pt());
    event.set(h_ak4jet1_eta,event.jets->at(0).eta());
  }
  if(event.topjets->size()>0){
    event.set(h_ak8jet1_pt,event.topjets->at(0).pt());
    event.set(h_ak8jet1_eta,event.topjets->at(0).eta());
  }
  event.set(h_NPV,event.pvs->size());





  //////// NN
  NNModule->process(event);
  std::vector<tensorflow::Tensor> NNoutputs = NNModule->GetOutputs();
  event.set(h_NNoutput0, (double)(NNoutputs[0].tensor<float, 2>()(0,0)));
  event.set(h_NNoutput1, (double)(NNoutputs[0].tensor<float, 2>()(0,1)));
  event.set(h_NNoutput2, (double)(NNoutputs[0].tensor<float, 2>()(0,2)));
  event.set(h_NNoutput, NNoutputs);


  if( (double)(NNoutputs[0].tensor<float, 2>()(0,0)) >= 0.5){
  fill_histograms(event, "DNN_output0");
  }

  if( (double)(NNoutputs[0].tensor<float, 2>()(0,1)) >= 0.9){
  fill_histograms(event, "DNN_output1");
  }

  if( (double)(NNoutputs[0].tensor<float, 2>()(0,2)) >= 0.9){
  fill_histograms(event, "DNN_output2");
  }


  if(debug) cout<<"Set some vars for monitoring"<<endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeAnalysisModule_TestNN)
