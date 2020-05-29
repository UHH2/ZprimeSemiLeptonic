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

uhh2::Event::Handle<float> h_Ak4_j1_E;
uhh2::Event::Handle<float> h_Ak4_j1_deepjetbscore;
uhh2::Event::Handle<float> h_Ak4_j1_eta;
uhh2::Event::Handle<float> h_Ak4_j1_m;
uhh2::Event::Handle<float> h_Ak4_j1_phi;
uhh2::Event::Handle<float> h_Ak4_j1_pt;

uhh2::Event::Handle<float> h_Ak4_j2_E;
uhh2::Event::Handle<float> h_Ak4_j2_deepjetbscore;
uhh2::Event::Handle<float> h_Ak4_j2_eta;
uhh2::Event::Handle<float> h_Ak4_j2_m;
uhh2::Event::Handle<float> h_Ak4_j2_phi;
uhh2::Event::Handle<float> h_Ak4_j2_pt;

uhh2::Event::Handle<float> h_Ak4_j3_E;
uhh2::Event::Handle<float> h_Ak4_j3_deepjetbscore;
uhh2::Event::Handle<float> h_Ak4_j3_eta;
uhh2::Event::Handle<float> h_Ak4_j3_m;
uhh2::Event::Handle<float> h_Ak4_j3_phi;
uhh2::Event::Handle<float> h_Ak4_j3_pt;

uhh2::Event::Handle<float> h_Ak4_j4_E;
uhh2::Event::Handle<float> h_Ak4_j4_deepjetbscore;
uhh2::Event::Handle<float> h_Ak4_j4_eta;
uhh2::Event::Handle<float> h_Ak4_j4_m;
uhh2::Event::Handle<float> h_Ak4_j4_phi;
uhh2::Event::Handle<float> h_Ak4_j4_pt;

uhh2::Event::Handle<float> h_Ak4_j5_E;
uhh2::Event::Handle<float> h_Ak4_j5_deepjetbscore;
uhh2::Event::Handle<float> h_Ak4_j5_eta;
uhh2::Event::Handle<float> h_Ak4_j5_m;
uhh2::Event::Handle<float> h_Ak4_j5_phi;
uhh2::Event::Handle<float> h_Ak4_j5_pt;

uhh2::Event::Handle<float> h_Ak4_j6_E;
uhh2::Event::Handle<float> h_Ak4_j6_deepjetbscore;
uhh2::Event::Handle<float> h_Ak4_j6_eta;
uhh2::Event::Handle<float> h_Ak4_j6_m;
uhh2::Event::Handle<float> h_Ak4_j6_phi;
uhh2::Event::Handle<float> h_Ak4_j6_pt;

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

uhh2::Event::Handle<float> h_MET_pt;

uhh2::Event::Handle<float> h_Mu_E;
uhh2::Event::Handle<float> h_Mu_eta;
uhh2::Event::Handle<float> h_Mu_phi;
uhh2::Event::Handle<float> h_Mu_pt;

uhh2::Event::Handle<float> h_N_Ak4;
uhh2::Event::Handle<float> h_N_Ak8;

uhh2::Event::Handle<float> h_weight;

};

NeuralNetworkModule::NeuralNetworkModule(Context& ctx, const std::string & ModelName, const std::string& ConfigName): NeuralNetworkBase(ctx, ModelName, ConfigName){


h_Ak4_j1_E   = ctx.get_handle<float>("Ak4_j1_E");
h_Ak4_j1_deepjetbscore   = ctx.get_handle<float>("Ak4_j1_deepjetbscore");
h_Ak4_j1_eta = ctx.get_handle<float>("Ak4_j1_eta");
h_Ak4_j1_m   = ctx.get_handle<float>("Ak4_j1_m");
h_Ak4_j1_phi = ctx.get_handle<float>("Ak4_j1_phi");
h_Ak4_j1_pt  = ctx.get_handle<float>("Ak4_j1_pt");

h_Ak4_j2_E   = ctx.get_handle<float>("Ak4_j2_E");
h_Ak4_j2_deepjetbscore   = ctx.get_handle<float>("Ak4_j2_deepjetbscore");
h_Ak4_j2_eta = ctx.get_handle<float>("Ak4_j2_eta");
h_Ak4_j2_m   = ctx.get_handle<float>("Ak4_j2_m");
h_Ak4_j2_phi = ctx.get_handle<float>("Ak4_j2_phi");
h_Ak4_j2_pt  = ctx.get_handle<float>("Ak4_j2_pt");

h_Ak4_j3_E   = ctx.get_handle<float>("Ak4_j3_E");
h_Ak4_j3_deepjetbscore   = ctx.get_handle<float>("Ak4_j3_deepjetbscore");
h_Ak4_j3_eta = ctx.get_handle<float>("Ak4_j3_eta");
h_Ak4_j3_m   = ctx.get_handle<float>("Ak4_j3_m");
h_Ak4_j3_phi = ctx.get_handle<float>("Ak4_j3_phi");
h_Ak4_j3_pt  = ctx.get_handle<float>("Ak4_j3_pt");

h_Ak4_j4_E   = ctx.get_handle<float>("Ak4_j4_E");
h_Ak4_j4_deepjetbscore   = ctx.get_handle<float>("Ak4_j4_deepjetbscore");
h_Ak4_j4_eta = ctx.get_handle<float>("Ak4_j4_eta");
h_Ak4_j4_m   = ctx.get_handle<float>("Ak4_j4_m");
h_Ak4_j4_phi = ctx.get_handle<float>("Ak4_j4_phi");
h_Ak4_j4_pt  = ctx.get_handle<float>("Ak4_j4_pt");

h_Ak4_j5_E   = ctx.get_handle<float>("Ak4_j5_E");
h_Ak4_j5_deepjetbscore   = ctx.get_handle<float>("Ak4_j5_deepjetbscore");
h_Ak4_j5_eta = ctx.get_handle<float>("Ak4_j5_eta");
h_Ak4_j5_m   = ctx.get_handle<float>("Ak4_j5_m");
h_Ak4_j5_phi = ctx.get_handle<float>("Ak4_j5_phi");
h_Ak4_j5_pt  = ctx.get_handle<float>("Ak4_j5_pt");

h_Ak4_j6_E   = ctx.get_handle<float>("Ak4_j6_E");
h_Ak4_j6_deepjetbscore   = ctx.get_handle<float>("Ak4_j6_deepjetbscore");
h_Ak4_j6_eta = ctx.get_handle<float>("Ak4_j6_eta");
h_Ak4_j6_m   = ctx.get_handle<float>("Ak4_j6_m");
h_Ak4_j6_phi = ctx.get_handle<float>("Ak4_j6_phi");
h_Ak4_j6_pt  = ctx.get_handle<float>("Ak4_j6_pt");

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

h_MET_pt = ctx.get_handle<float>("MET_pt");

h_Mu_E    = ctx.get_handle<float>("Mu_E");
h_Mu_eta  = ctx.get_handle<float>("Mu_eta");
h_Mu_phi  = ctx.get_handle<float>("Mu_phi");
h_Mu_pt   = ctx.get_handle<float>("Mu_pt");

h_N_Ak4 = ctx.get_handle<float>("N_Ak4");
h_N_Ak8 = ctx.get_handle<float>("N_Ak8");

h_weight = ctx.get_handle<float>("weight");

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
  ifstream normfile ("/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_V4_2605/NormInfo.txt", ios::in);
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


  NNInputs.at(0).tensor<float, 2>()(0,0)  = (event.get(h_Ak4_j1_E)   - mean_val[0]) / (std_val[0]);
  NNInputs.at(0).tensor<float, 2>()(0,1)  = (event.get(h_Ak4_j1_deepjetbscore)   - mean_val[1]) / (std_val[1]);
  NNInputs.at(0).tensor<float, 2>()(0,2)  = (event.get(h_Ak4_j1_eta) - mean_val[2]) / (std_val[2]);
  NNInputs.at(0).tensor<float, 2>()(0,3)  = (event.get(h_Ak4_j1_m)   - mean_val[3]) / (std_val[3]);
  NNInputs.at(0).tensor<float, 2>()(0,4)  = (event.get(h_Ak4_j1_phi) - mean_val[4]) / (std_val[4]);
  NNInputs.at(0).tensor<float, 2>()(0,5)  = (event.get(h_Ak4_j1_pt)  - mean_val[5]) / (std_val[5]);

  NNInputs.at(0).tensor<float, 2>()(0,6)  = (event.get(h_Ak4_j2_E)   - mean_val[6]) / (std_val[6]);
  NNInputs.at(0).tensor<float, 2>()(0,7)  = (event.get(h_Ak4_j2_deepjetbscore)   - mean_val[7]) / (std_val[7]);
  NNInputs.at(0).tensor<float, 2>()(0,8)  = (event.get(h_Ak4_j2_eta) - mean_val[8]) / (std_val[8]);
  NNInputs.at(0).tensor<float, 2>()(0,9)  = (event.get(h_Ak4_j2_m)   - mean_val[9]) / (std_val[9]);
  NNInputs.at(0).tensor<float, 2>()(0,10)  = (event.get(h_Ak4_j2_phi) - mean_val[10]) / (std_val[10]);
  NNInputs.at(0).tensor<float, 2>()(0,11)  = (event.get(h_Ak4_j2_pt)  - mean_val[11]) / (std_val[11]);

  NNInputs.at(0).tensor<float, 2>()(0,12)  = (event.get(h_Ak4_j3_E)   - mean_val[12]) / (std_val[12]);
  NNInputs.at(0).tensor<float, 2>()(0,13)  = (event.get(h_Ak4_j3_deepjetbscore)   - mean_val[13]) / (std_val[13]);
  NNInputs.at(0).tensor<float, 2>()(0,14)  = (event.get(h_Ak4_j3_eta) - mean_val[14]) / (std_val[14]);
  NNInputs.at(0).tensor<float, 2>()(0,15)  = (event.get(h_Ak4_j3_m)   - mean_val[15]) / (std_val[15]);
  NNInputs.at(0).tensor<float, 2>()(0,16)  = (event.get(h_Ak4_j3_phi) - mean_val[16]) / (std_val[16]);
  NNInputs.at(0).tensor<float, 2>()(0,17)  = (event.get(h_Ak4_j3_pt)  - mean_val[17]) / (std_val[17]);

  NNInputs.at(0).tensor<float, 2>()(0,18)  = (event.get(h_Ak4_j4_E)   - mean_val[18]) / (std_val[18]);
  NNInputs.at(0).tensor<float, 2>()(0,19)  = (event.get(h_Ak4_j4_deepjetbscore)   - mean_val[19]) / (std_val[19]);
  NNInputs.at(0).tensor<float, 2>()(0,20)  = (event.get(h_Ak4_j4_eta) - mean_val[20]) / (std_val[20]);
  NNInputs.at(0).tensor<float, 2>()(0,21)  = (event.get(h_Ak4_j4_m)   - mean_val[21]) / (std_val[21]);
  NNInputs.at(0).tensor<float, 2>()(0,22)  = (event.get(h_Ak4_j4_phi) - mean_val[22]) / (std_val[22]);
  NNInputs.at(0).tensor<float, 2>()(0,23)  = (event.get(h_Ak4_j4_pt)  - mean_val[23]) / (std_val[23]);

  NNInputs.at(0).tensor<float, 2>()(0,24)  = (event.get(h_Ak4_j5_E)   - mean_val[24]) / (std_val[24]);
  NNInputs.at(0).tensor<float, 2>()(0,25)  = (event.get(h_Ak4_j4_deepjetbscore)   - mean_val[25]) / (std_val[25]);
  NNInputs.at(0).tensor<float, 2>()(0,26)  = (event.get(h_Ak4_j5_eta) - mean_val[26]) / (std_val[26]);
  NNInputs.at(0).tensor<float, 2>()(0,27)  = (event.get(h_Ak4_j5_m)   - mean_val[27]) / (std_val[27]);
  NNInputs.at(0).tensor<float, 2>()(0,28)  = (event.get(h_Ak4_j5_phi) - mean_val[28]) / (std_val[28]);
  NNInputs.at(0).tensor<float, 2>()(0,29)  = (event.get(h_Ak4_j5_pt)  - mean_val[29]) / (std_val[29]);

  NNInputs.at(0).tensor<float, 2>()(0,30)  = (event.get(h_Ak4_j6_E)   - mean_val[30]) / (std_val[30]);
  NNInputs.at(0).tensor<float, 2>()(0,31)  = (event.get(h_Ak4_j6_deepjetbscore)   - mean_val[31]) / (std_val[31]);
  NNInputs.at(0).tensor<float, 2>()(0,32)  = (event.get(h_Ak4_j6_eta) - mean_val[32]) / (std_val[32]);
  NNInputs.at(0).tensor<float, 2>()(0,33)  = (event.get(h_Ak4_j6_m)   - mean_val[33]) / (std_val[33]);
  NNInputs.at(0).tensor<float, 2>()(0,34)  = (event.get(h_Ak4_j6_phi) - mean_val[34]) / (std_val[34]);
  NNInputs.at(0).tensor<float, 2>()(0,35)  = (event.get(h_Ak4_j6_pt)  - mean_val[35]) / (std_val[35]);

  NNInputs.at(0).tensor<float, 2>()(0,36)  = (event.get(h_Ak8_j1_E)     - mean_val[36]) / (std_val[36]);
  NNInputs.at(0).tensor<float, 2>()(0,37)  = (event.get(h_Ak8_j1_eta)   - mean_val[37]) / (std_val[37]);
  NNInputs.at(0).tensor<float, 2>()(0,38)  = (event.get(h_Ak8_j1_mSD)   - mean_val[38]) / (std_val[38]);
  NNInputs.at(0).tensor<float, 2>()(0,39)  = (event.get(h_Ak8_j1_phi)   - mean_val[39]) / (std_val[39]);
  NNInputs.at(0).tensor<float, 2>()(0,40)  = (event.get(h_Ak8_j1_pt)    - mean_val[40]) / (std_val[40]);
  NNInputs.at(0).tensor<float, 2>()(0,41)  = (event.get(h_Ak8_j1_tau21) - mean_val[41]) / (std_val[41]);
  NNInputs.at(0).tensor<float, 2>()(0,42)  = (event.get(h_Ak8_j1_tau32) - mean_val[42]) / (std_val[42]);

  NNInputs.at(0).tensor<float, 2>()(0,43)  = (event.get(h_Ak8_j2_E)     - mean_val[43]) / (std_val[43]);
  NNInputs.at(0).tensor<float, 2>()(0,44)  = (event.get(h_Ak8_j2_eta)   - mean_val[44]) / (std_val[44]);
  NNInputs.at(0).tensor<float, 2>()(0,45)  = (event.get(h_Ak8_j2_mSD)   - mean_val[45]) / (std_val[45]);
  NNInputs.at(0).tensor<float, 2>()(0,46)  = (event.get(h_Ak8_j2_phi)   - mean_val[46]) / (std_val[46]);
  NNInputs.at(0).tensor<float, 2>()(0,47)  = (event.get(h_Ak8_j2_pt)    - mean_val[47]) / (std_val[47]);
  NNInputs.at(0).tensor<float, 2>()(0,48)  = (event.get(h_Ak8_j2_tau21) - mean_val[48]) / (std_val[48]);
  NNInputs.at(0).tensor<float, 2>()(0,49)  = (event.get(h_Ak8_j2_tau32) - mean_val[49]) / (std_val[49]);

  NNInputs.at(0).tensor<float, 2>()(0,50)  = (event.get(h_Ak8_j3_E)     - mean_val[50]) / (std_val[50]);
  NNInputs.at(0).tensor<float, 2>()(0,51)  = (event.get(h_Ak8_j3_eta)   - mean_val[51]) / (std_val[51]);
  NNInputs.at(0).tensor<float, 2>()(0,52)  = (event.get(h_Ak8_j3_mSD)   - mean_val[52]) / (std_val[52]);
  NNInputs.at(0).tensor<float, 2>()(0,53)  = (event.get(h_Ak8_j3_phi)   - mean_val[53]) / (std_val[53]);
  NNInputs.at(0).tensor<float, 2>()(0,54)  = (event.get(h_Ak8_j3_pt)    - mean_val[54]) / (std_val[54]);
  NNInputs.at(0).tensor<float, 2>()(0,55)  = (event.get(h_Ak8_j3_tau21) - mean_val[55]) / (std_val[55]);
  NNInputs.at(0).tensor<float, 2>()(0,56)  = (event.get(h_Ak8_j3_tau32) - mean_val[56]) / (std_val[56]);

  NNInputs.at(0).tensor<float, 2>()(0,57)  = (event.get(h_MET_pt) - mean_val[57]) / (std_val[57]);

  NNInputs.at(0).tensor<float, 2>()(0,58)  = (event.get(h_Mu_E)   - mean_val[58]) / (std_val[58]);
  NNInputs.at(0).tensor<float, 2>()(0,59)  = (event.get(h_Mu_eta) - mean_val[59]) / (std_val[59]);
  NNInputs.at(0).tensor<float, 2>()(0,60)  = (event.get(h_Mu_phi) - mean_val[60]) / (std_val[60]);
  NNInputs.at(0).tensor<float, 2>()(0,61)  = (event.get(h_Mu_pt)  - mean_val[61]) / (std_val[61]);

  NNInputs.at(0).tensor<float, 2>()(0,62)  = (event.get(h_N_Ak4) - mean_val[62]) / (std_val[62]);
  NNInputs.at(0).tensor<float, 2>()(0,63)  = (event.get(h_N_Ak8) - mean_val[63]) / (std_val[63]);

  NNInputs.at(0).tensor<float, 2>()(0,64)  = (event.get(h_weight) - mean_val[64]) / (std_val[64]);

/*
  NNInputs.at(0).tensor<float, 2>()(0,0)  = event.get(h_Ak4_j1_E);
  NNInputs.at(0).tensor<float, 2>()(0,1)  = event.get(h_Ak4_j1_deepjetbscore);
  NNInputs.at(0).tensor<float, 2>()(0,2)  = event.get(h_Ak4_j1_eta);
  NNInputs.at(0).tensor<float, 2>()(0,3)  = event.get(h_Ak4_j1_m)  ;
  NNInputs.at(0).tensor<float, 2>()(0,4)  = event.get(h_Ak4_j1_phi);
  NNInputs.at(0).tensor<float, 2>()(0,5)  = event.get(h_Ak4_j1_pt) ;

  NNInputs.at(0).tensor<float, 2>()(0,6)  = event.get(h_Ak4_j2_E)  ;
  NNInputs.at(0).tensor<float, 2>()(0,7)  = event.get(h_Ak4_j2_deepjetbscore);
  NNInputs.at(0).tensor<float, 2>()(0,8)  = event.get(h_Ak4_j2_eta);
  NNInputs.at(0).tensor<float, 2>()(0,9)  = event.get(h_Ak4_j2_m)  ;
  NNInputs.at(0).tensor<float, 2>()(0,10)  = event.get(h_Ak4_j2_phi);
  NNInputs.at(0).tensor<float, 2>()(0,11)  = event.get(h_Ak4_j2_pt);

  NNInputs.at(0).tensor<float, 2>()(0,12)  = event.get(h_Ak4_j3_E);
  NNInputs.at(0).tensor<float, 2>()(0,13)  = event.get(h_Ak4_j3_deepjetbscore);
  NNInputs.at(0).tensor<float, 2>()(0,14)  = event.get(h_Ak4_j3_eta) ;
  NNInputs.at(0).tensor<float, 2>()(0,15)  = event.get(h_Ak4_j3_m)   ;
  NNInputs.at(0).tensor<float, 2>()(0,16)  = event.get(h_Ak4_j3_phi) ;
  NNInputs.at(0).tensor<float, 2>()(0,17)  = event.get(h_Ak4_j3_pt)  ;

  NNInputs.at(0).tensor<float, 2>()(0,18)  = event.get(h_Ak4_j4_E)   ;
  NNInputs.at(0).tensor<float, 2>()(0,19)  = event.get(h_Ak4_j4_deepjetbscore);
  NNInputs.at(0).tensor<float, 2>()(0,20)  = event.get(h_Ak4_j4_eta) ;
  NNInputs.at(0).tensor<float, 2>()(0,21)  = event.get(h_Ak4_j4_m)   ;
  NNInputs.at(0).tensor<float, 2>()(0,22)  = event.get(h_Ak4_j4_phi) ;
  NNInputs.at(0).tensor<float, 2>()(0,23)  = event.get(h_Ak4_j4_pt)  ;

  NNInputs.at(0).tensor<float, 2>()(0,24)  = event.get(h_Ak4_j5_E)   ;
  NNInputs.at(0).tensor<float, 2>()(0,25)  = event.get(h_Ak4_j4_deepjetbscore)   ;
  NNInputs.at(0).tensor<float, 2>()(0,26)  = event.get(h_Ak4_j5_eta);
  NNInputs.at(0).tensor<float, 2>()(0,27)  = event.get(h_Ak4_j5_m)  ;
  NNInputs.at(0).tensor<float, 2>()(0,28)  = event.get(h_Ak4_j5_phi);
  NNInputs.at(0).tensor<float, 2>()(0,29)  = event.get(h_Ak4_j5_pt) ;

  NNInputs.at(0).tensor<float, 2>()(0,30)  = event.get(h_Ak4_j6_E)  ;
  NNInputs.at(0).tensor<float, 2>()(0,31)  = event.get(h_Ak4_j6_deepjetbscore);
  NNInputs.at(0).tensor<float, 2>()(0,32)  = event.get(h_Ak4_j6_eta) ;
  NNInputs.at(0).tensor<float, 2>()(0,33)  = event.get(h_Ak4_j6_m)   ;
  NNInputs.at(0).tensor<float, 2>()(0,34)  = event.get(h_Ak4_j6_phi) ;
  NNInputs.at(0).tensor<float, 2>()(0,35)  = event.get(h_Ak4_j6_pt)  ;

  NNInputs.at(0).tensor<float, 2>()(0,36)  = event.get(h_Ak8_j1_E)     ;
  NNInputs.at(0).tensor<float, 2>()(0,37)  = event.get(h_Ak8_j1_eta)   ;
  NNInputs.at(0).tensor<float, 2>()(0,38)  = event.get(h_Ak8_j1_mSD)   ;
  NNInputs.at(0).tensor<float, 2>()(0,39)  = event.get(h_Ak8_j1_phi)   ;
  NNInputs.at(0).tensor<float, 2>()(0,40)  = event.get(h_Ak8_j1_pt)    ;
  NNInputs.at(0).tensor<float, 2>()(0,41)  = event.get(h_Ak8_j1_tau21) ;
  NNInputs.at(0).tensor<float, 2>()(0,42)  = event.get(h_Ak8_j1_tau32) ;

  NNInputs.at(0).tensor<float, 2>()(0,43)  = event.get(h_Ak8_j2_E)     ;
  NNInputs.at(0).tensor<float, 2>()(0,44)  = event.get(h_Ak8_j2_eta)   ;
  NNInputs.at(0).tensor<float, 2>()(0,45)  = event.get(h_Ak8_j2_mSD)   ;
  NNInputs.at(0).tensor<float, 2>()(0,46)  = event.get(h_Ak8_j2_phi)   ;
  NNInputs.at(0).tensor<float, 2>()(0,47)  = event.get(h_Ak8_j2_pt)    ;
  NNInputs.at(0).tensor<float, 2>()(0,48)  = event.get(h_Ak8_j2_tau21) ;
  NNInputs.at(0).tensor<float, 2>()(0,49)  = event.get(h_Ak8_j2_tau32) ;

  NNInputs.at(0).tensor<float, 2>()(0,50)  = event.get(h_Ak8_j3_E)     ;
  NNInputs.at(0).tensor<float, 2>()(0,51)  = event.get(h_Ak8_j3_eta)   ;
  NNInputs.at(0).tensor<float, 2>()(0,52)  = event.get(h_Ak8_j3_mSD)   ;
  NNInputs.at(0).tensor<float, 2>()(0,53)  = event.get(h_Ak8_j3_phi)   ;
  NNInputs.at(0).tensor<float, 2>()(0,54)  = event.get(h_Ak8_j3_pt)    ;
  NNInputs.at(0).tensor<float, 2>()(0,55)  = event.get(h_Ak8_j3_tau21) ;
  NNInputs.at(0).tensor<float, 2>()(0,56)  = event.get(h_Ak8_j3_tau32) ;

  NNInputs.at(0).tensor<float, 2>()(0,57)  = event.get(h_MET_pt) ;

  NNInputs.at(0).tensor<float, 2>()(0,58)  = event.get(h_Mu_E)   ;
  NNInputs.at(0).tensor<float, 2>()(0,59)  = event.get(h_Mu_eta) ;
  NNInputs.at(0).tensor<float, 2>()(0,60)  = event.get(h_Mu_phi) ;
  NNInputs.at(0).tensor<float, 2>()(0,61)  = event.get(h_Mu_pt)  ;

  NNInputs.at(0).tensor<float, 2>()(0,62)  = event.get(h_N_Ak4) ;
  NNInputs.at(0).tensor<float, 2>()(0,63)  = event.get(h_N_Ak8) ;

  NNInputs.at(0).tensor<float, 2>()(0,64)  = event.get(h_weight);
*/

  if (NNInputs.size()!=LayerInputs.size()) throw logic_error("NeuralNetworkModule.cxx: Create a number of inputs diffetent wrt. LayerInputs.size()="+to_string(LayerInputs.size())); 
}



class ZprimeAnalysisModule_TestNN_std : public ModuleBASE {

public:
  explicit ZprimeAnalysisModule_TestNN_std(uhh2::Context&);
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
  unique_ptr<AnalysisModule> LumiWeight_module, PUWeight_module, printer_genparticles, BTagWeight_module;

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
  Event::Handle<float> h_chi2;
  Event::Handle<float> h_MET;   Event::Handle<int> h_NPV;
  Event::Handle<float> h_lep1_pt; Event::Handle<float> h_lep1_eta; 
  Event::Handle<float> h_ak4jet1_pt; Event::Handle<float> h_ak4jet1_eta; 
  Event::Handle<float> h_ak8jet1_pt; Event::Handle<float> h_ak8jet1_eta; 
  Event::Handle<float> h_Mttbar; 

  uhh2::Event::Handle<ZprimeCandidate*> h_BestZprimeCandidateChi2;


  float inv_mass(const LorentzVector& p4){ return p4.isTimelike() ? p4.mass() : -sqrt(-p4.mass2()); }

  // Configuration
  bool isMC, ispuppi, islooserselection;
  string Sys_MuonID, Sys_MuonTrigger, Sys_PU, Sys_btag;
  TString sample;
  int runnr_oldtriggers = 299368;

  bool is2016v2, is2016v3, is2017v2, is2018;
  bool isMuon, isElectron;

  Event::Handle<float> h_Ak4_j1_E;
  Event::Handle<float> h_Ak4_j1_deepjetbscore;
  Event::Handle<float> h_Ak4_j1_eta;
  Event::Handle<float> h_Ak4_j1_m;
  Event::Handle<float> h_Ak4_j1_phi;
  Event::Handle<float> h_Ak4_j1_pt;

  Event::Handle<float> h_Ak4_j2_E;
  Event::Handle<float> h_Ak4_j2_deepjetbscore;
  Event::Handle<float> h_Ak4_j2_eta;
  Event::Handle<float> h_Ak4_j2_m;
  Event::Handle<float> h_Ak4_j2_phi;
  Event::Handle<float> h_Ak4_j2_pt;
  
  Event::Handle<float> h_Ak4_j3_E;
  Event::Handle<float> h_Ak4_j3_deepjetbscore;
  Event::Handle<float> h_Ak4_j3_eta;
  Event::Handle<float> h_Ak4_j3_m;
  Event::Handle<float> h_Ak4_j3_phi;
  Event::Handle<float> h_Ak4_j3_pt;
  
  Event::Handle<float> h_Ak4_j4_E;
  Event::Handle<float> h_Ak4_j4_deepjetbscore;
  Event::Handle<float> h_Ak4_j4_eta;
  Event::Handle<float> h_Ak4_j4_m;
  Event::Handle<float> h_Ak4_j4_phi;
  Event::Handle<float> h_Ak4_j4_pt;
  
  Event::Handle<float> h_Ak4_j5_E;
  Event::Handle<float> h_Ak4_j5_deepjetbscore;
  Event::Handle<float> h_Ak4_j5_eta;
  Event::Handle<float> h_Ak4_j5_m;
  Event::Handle<float> h_Ak4_j5_phi;
  Event::Handle<float> h_Ak4_j5_pt;
  
  Event::Handle<float> h_Ak4_j6_E;
  Event::Handle<float> h_Ak4_j6_deepjetbscore;
  Event::Handle<float> h_Ak4_j6_eta;
  Event::Handle<float> h_Ak4_j6_m;
  Event::Handle<float> h_Ak4_j6_phi;
  Event::Handle<float> h_Ak4_j6_pt;
  
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
  
  Event::Handle<float> h_MET_pt;
  
  Event::Handle<float> h_Mu_E;
  Event::Handle<float> h_Mu_eta;
  Event::Handle<float> h_Mu_phi;
  Event::Handle<float> h_Mu_pt;
  
  Event::Handle<float> h_N_Ak4;
  Event::Handle<float> h_N_Ak8;
  
  Event::Handle<float> h_weight;


  Event::Handle<std::vector<tensorflow::Tensor> > h_NNoutput;
  Event::Handle<double> h_NNoutput0;
  Event::Handle<double> h_NNoutput1;
  Event::Handle<double> h_NNoutput2;

  std::unique_ptr<NeuralNetworkModule> NNModule;

};

void ZprimeAnalysisModule_TestNN_std::book_histograms(uhh2::Context& ctx, vector<string> tags){
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

void ZprimeAnalysisModule_TestNN_std::fill_histograms(uhh2::Event& event, string tag){
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

ZprimeAnalysisModule_TestNN_std::ZprimeAnalysisModule_TestNN_std(uhh2::Context& ctx){
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
  Sys_btag = ctx.get("Sys_BTagSF");

  BTag::algo btag_algo = BTag::DEEPJET;
  BTag::wp btag_wp_tight = BTag::WP_TIGHT;
  JetId id_btag = BTag(btag_algo, btag_wp_tight);

  // Modules
  printer_genparticles.reset(new GenParticlesPrinter(ctx));
  muon_cleaner.reset(new MuonCleaner(muonID));
  electron_cleaner.reset(new ElectronCleaner(electronID));
  LumiWeight_module.reset(new MCLumiWeight(ctx));
  PUWeight_module.reset(new MCPileupReweight(ctx, Sys_PU));
  BTagWeight_module.reset(new MCBTagDiscriminantReweighting(ctx, btag_algo, "jets", Sys_btag));

  //if((is2016v3 || is2016v2) && isMuon){
  //  MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2016/MuonID_EfficienciesAndSF_average_RunBtoH.root", "MC_NUM_TightID_DEN_genTracks_PAR_pt_eta", 0., "MuonID", true, Sys_MuonID));
  //  MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2016/MuonTrigger_EfficienciesAndSF_average_RunBtoH.root", "IsoMu50_OR_IsoTkMu50_PtEtaBins", 0.5, "MuonTrigger", true, Sys_MuonTrigger));
  //}
  if(is2017v2 || is2018){
    MuonID_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2017/MuonID_94X_RunBCDEF_SF_ID.root", "NUM_HighPtID_DEN_genTracks_pair_newTuneP_probe_pt_abseta", 0., "HighPtID", true, Sys_MuonID));
    MuonTrigger_module.reset(new MCMuonScaleFactor(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/common/data/2017/MuonTrigger_EfficienciesAndSF_RunBtoF_Nov17Nov2017.root", "Mu50_PtEtaBins/pt_abseta_ratio", 0.5, "Trigger", true, Sys_MuonTrigger));
  }

  // Selection modules
  Trigger1_selection.reset(new TriggerSelection(trigger1));
  Trigger2_selection.reset(new TriggerSelection(trigger2));
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
  //h_weight = ctx.declare_event_output<float> ("weight");

  // btag 
  //CSVBTag::wp btag_wp = CSVBTag::WP_TIGHT; // b-tag workingpoint
  //JetId id_btag = CSVBTag(btag_wp);

  // DeepCSVBTag::wp btag_wp = DeepCSVBTag::WP_TIGHT; // b-tag workingpoint
  // JetId id_btag = DeepCSVBTag(btag_wp);

  // DeepJetBTag::wp btag_wp = DeepJetBTag::WP_TIGHT; // b-tag workingpoint
  // JetId id_btag = DeepJetBTag(btag_wp);

  sel_1btag.reset(new NJetSelection(1, 1, id_btag));
  sel_2btag.reset(new NJetSelection(2,-1, id_btag));


  TopJetBtagSubjet_selection.reset(new ZprimeBTagFatSubJetSelection(ctx));

  // Book histograms
  vector<string> histogram_tags = {"Weights", "Muon1", "Trigger", "Muon2", "Electron1", "TwoDCut", "Jet1", "Jet2", "MET", "HTlep", "MatchableBeforeChi2Cut", "NotMatchableBeforeChi2Cut", "CorrectMatchBeforeChi2Cut", "NotCorrectMatchBeforeChi2Cut", "Chi2", "Matchable", "NotMatchable", "CorrectMatch", "NotCorrectMatch", "TopTagReconstruction", "NotTopTagReconstruction", "Btags2", "Btags1","TopJetBtagSubjet","DNN_output0","DNN_output1","DNN_output2"};
  book_histograms(ctx, histogram_tags);

  h_Ak4_j1_E   = ctx.get_handle<float>("Ak4_j1_E");
  h_Ak4_j1_deepjetbscore   = ctx.get_handle<float>("Ak4_j1_deepjetbscore");
  h_Ak4_j1_eta = ctx.get_handle<float>("Ak4_j1_eta");
  h_Ak4_j1_m   = ctx.get_handle<float>("Ak4_j1_m");
  h_Ak4_j1_phi = ctx.get_handle<float>("Ak4_j1_phi");
  h_Ak4_j1_pt  = ctx.get_handle<float>("Ak4_j1_pt");
  
  h_Ak4_j2_E   = ctx.get_handle<float>("Ak4_j2_E");
  h_Ak4_j2_deepjetbscore   = ctx.get_handle<float>("Ak4_j2_deepjetbscore");
  h_Ak4_j2_eta = ctx.get_handle<float>("Ak4_j2_eta");
  h_Ak4_j2_m   = ctx.get_handle<float>("Ak4_j2_m");
  h_Ak4_j2_phi = ctx.get_handle<float>("Ak4_j2_phi");
  h_Ak4_j2_pt  = ctx.get_handle<float>("Ak4_j2_pt");
  
  h_Ak4_j3_E   = ctx.get_handle<float>("Ak4_j3_E");
  h_Ak4_j3_deepjetbscore   = ctx.get_handle<float>("Ak4_j3_deepjetbscore");
  h_Ak4_j3_eta = ctx.get_handle<float>("Ak4_j3_eta");
  h_Ak4_j3_m   = ctx.get_handle<float>("Ak4_j3_m");
  h_Ak4_j3_phi = ctx.get_handle<float>("Ak4_j3_phi");
  h_Ak4_j3_pt  = ctx.get_handle<float>("Ak4_j3_pt");
  
  h_Ak4_j4_E   = ctx.get_handle<float>("Ak4_j4_E");
  h_Ak4_j4_deepjetbscore   = ctx.get_handle<float>("Ak4_j4_deepjetbscore");
  h_Ak4_j4_eta = ctx.get_handle<float>("Ak4_j4_eta");
  h_Ak4_j4_m   = ctx.get_handle<float>("Ak4_j4_m");
  h_Ak4_j4_phi = ctx.get_handle<float>("Ak4_j4_phi");
  h_Ak4_j4_pt  = ctx.get_handle<float>("Ak4_j4_pt");
  
  h_Ak4_j5_E   = ctx.get_handle<float>("Ak4_j5_E");
  h_Ak4_j5_deepjetbscore   = ctx.get_handle<float>("Ak4_j5_deepjetbscore");
  h_Ak4_j5_eta = ctx.get_handle<float>("Ak4_j5_eta");
  h_Ak4_j5_m   = ctx.get_handle<float>("Ak4_j5_m");
  h_Ak4_j5_phi = ctx.get_handle<float>("Ak4_j5_phi");
  h_Ak4_j5_pt  = ctx.get_handle<float>("Ak4_j5_pt");
  
  h_Ak4_j6_E   = ctx.get_handle<float>("Ak4_j6_E");
  h_Ak4_j6_deepjetbscore   = ctx.get_handle<float>("Ak4_j6_deepjetbscore");
  h_Ak4_j6_eta = ctx.get_handle<float>("Ak4_j6_eta");
  h_Ak4_j6_m   = ctx.get_handle<float>("Ak4_j6_m");
  h_Ak4_j6_phi = ctx.get_handle<float>("Ak4_j6_phi");
  h_Ak4_j6_pt  = ctx.get_handle<float>("Ak4_j6_pt");
  
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
  
  h_MET_pt = ctx.get_handle<float>("MET_pt");
  
  h_Mu_E    = ctx.get_handle<float>("Mu_E");
  h_Mu_eta  = ctx.get_handle<float>("Mu_eta");
  h_Mu_phi  = ctx.get_handle<float>("Mu_phi");
  h_Mu_pt   = ctx.get_handle<float>("Mu_pt");
  
  h_N_Ak4 = ctx.get_handle<float>("N_Ak4");
  h_N_Ak8 = ctx.get_handle<float>("N_Ak8");
  
  h_weight = ctx.get_handle<float>("weight");

  h_NNoutput = ctx.get_handle<std::vector<tensorflow::Tensor>>("NNoutput");
  h_NNoutput0 = ctx.declare_event_output<double>("NNoutput0");
  h_NNoutput1 = ctx.declare_event_output<double>("NNoutput1");
  h_NNoutput2 = ctx.declare_event_output<double>("NNoutput2");
  NNModule.reset( new NeuralNetworkModule(ctx, "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_V4_2605/model.pb", "/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/ZprimeSemiLeptonic/KerasNN/NN_V4_2605/model.config.pbtxt"));

}

/*
██████  ██████   ██████   ██████ ███████ ███████ ███████
██   ██ ██   ██ ██    ██ ██      ██      ██      ██
██████  ██████  ██    ██ ██      █████   ███████ ███████
██      ██   ██ ██    ██ ██      ██           ██      ██
██      ██   ██  ██████   ██████ ███████ ███████ ███████
*/

bool ZprimeAnalysisModule_TestNN_std::process(uhh2::Event& event){

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
  BTagWeight_module->process(event);
  if(isMuon){
    MuonID_module->process(event);
    if(debug)  cout<<"MuonID ok"<<endl;
  }
  // Run top-tagging
  TopTaggerPuppi->process(event);
  if(debug) cout<<"Top Tagger ok"<<endl;
  fill_histograms(event, "Weights");
 
  if(!(Trigger1_selection->passes(event)|| Trigger2_selection->passes(event))) return false;
  if(isMuon){
    if(!NMuon1_selection->passes(event)) return false;
    fill_histograms(event, "Muon1");
    MuonTrigger_module->process_onemuon(event, 0);
    fill_histograms(event, "Trigger");
    if(!NMuon2_selection->passes(event)) return false;
    fill_histograms(event, "Muon2");
  }
  if(isElectron){
    if(!NElectron_selection->passes(event)) return false;
    fill_histograms(event, "Electron1");
  }
  if((event.muons->size()+event.electrons->size()) != 1) return false; //veto events without leptons or with too many 
  if(debug) cout<<"N leptons ok: Nelectrons="<<event.electrons->size()<<" Nmuons="<<event.muons->size()<<endl;
  //if(!TwoDCut_selection->passes(event)) return false;
  //fill_histograms(event, "TwoDCut");


  CandidateBuilder->process(event);
  if(debug) cout<<"CandidateBuilder is ok"<<endl;
  Chi2DiscriminatorZprime->process(event);
  if(debug)  cout<<"Chi2DiscriminatorZprime is ok"<<endl;
  CorrectMatchDiscriminatorZprime->process(event);
  if(debug) cout<<"CorrectMatchDiscriminatorZprime is ok"<<endl;
  if(sample.Contains("_blinded")){
    if(!BlindData_selection->passes(event)) return false;
  }
/*  if(!Jet1_selection->passes(event)) return false;
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
*/
  if(!Chi2_selection->passes(event)) return false;
  fill_histograms(event, "Chi2");

  if(debug) cout<<"Chi2_selection is ok"<<endl;
/*
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
*/
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

  double out0 = (double)(NNoutputs[0].tensor<float, 2>()(0,0));
  double out1 = (double)(NNoutputs[0].tensor<float, 2>()(0,1));
  double out2 = (double)(NNoutputs[0].tensor<float, 2>()(0,2));
  vector<double> out_event = {out0, out1, out2};

  double max_score = 0.0;
  for ( int i = 0; i < 3; i++ ) {
    if ( out_event[i] > max_score) {
    max_score = out_event[i];
    }
  }


  if( out0 == max_score ){
  fill_histograms(event, "DNN_output0");
  }

  if( out1 == max_score ){
  fill_histograms(event, "DNN_output1");
  }

  if( out2 == max_score ){
  fill_histograms(event, "DNN_output2");
  }


  if(debug) cout<<"Set some vars for monitoring"<<endl;
  return true;
}

UHH2_REGISTER_ANALYSIS_MODULE(ZprimeAnalysisModule_TestNN_std)
