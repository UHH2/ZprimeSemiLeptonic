#include "../include/TopPuppiJetCorrections.h"
#include "UHH2/common/include/JetCorrections.h"
#include "UHH2/common/include/JetCorrectionSets.h"
#include "UHH2/common/include/MCWeight.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/CleaningModules.h"
#include "UHH2/common/include/EventVariables.h"
#include "UHH2/common/include/LumiSelection.h"
#include "UHH2/common/include/Utils.h"
#include "UHH2/common/include/TriggerSelection.h"

using namespace uhh2;
using namespace std;

void TopPuppiJetCorrections::fail_if_init() const{
  if(init_done){
    throw invalid_argument("TopPuppiJetCorrections::init already called!");
  }
}


TopPuppiJetCorrections::TopPuppiJetCorrections(){
  tpuppijec_tag_2016 = "Summer16_07Aug2017";
  tpuppijec_ver_2016 = "11";

  tpuppijec_tag_2017 = "Fall17_17Nov2017";
  tpuppijec_ver_2017 = "32";

  tpuppijec_tag_2018 = "Autumn18";
  tpuppijec_ver_2018 = "19";

  tpuppijec_tjet_coll = "dummy";
  tpuppijec_subjet_coll = "dummy";
}


void TopPuppiJetCorrections::init(Context & ctx){
  if(init_done){
    throw invalid_argument("TopPuppiJetCorrections::init called twice!");
  }
  init_done = true;

  is_data = ctx.get("dataset_type") == "DATA";
  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);

  // setup correction tjet type for JECs
  std::string userTopJetColl = string2lowercase(ctx.get("TopPuppiJetCollection"));

  std::string algo = "";
  // algo size
  if (userTopJetColl.find("ak4") != std::string::npos) {
    algo = "AK4";
  }
  else if(userTopJetColl.find("ak8") != std::string::npos){
    algo = "AK8";
  }
  else if (userTopJetColl.find("ak8") == std::string::npos) {
    std::cout << "TopPuppiJetCorrections.cxx: Cannot determine tjet cone + radius (neither AK4 nor AK8) - going to assume it is AK8 for JECs" << '\n';
    algo = "AK8";
  }

  std::string pus = "PFchs";
  // Pileup subtraction
  if (userTopJetColl.find("puppi") != std::string::npos) {
    pus = "PFPuppi";
  } else if (userTopJetColl.find("chs") == std::string::npos) {
    std::cout << "Cannot determine pileup subtraction (neither CHS nor PUPPI) - going to assume it is CHS for JECs" << std::endl;
  }
  tpuppijec_tjet_coll = algo + pus;
  tpuppijec_subjet_coll = "AK4PFPuppi";

  if(is_mc){
    tpuppijet_corrector_MC.reset(new YearSwitcher(ctx));
    tpuppijet_corrector_MC->setup2016(std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2016, tpuppijec_ver_2016, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_corrector_MC->setup2017(std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2017, tpuppijec_ver_2017, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_corrector_MC->setup2018(std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2018, tpuppijec_ver_2018, tpuppijec_tjet_coll),"toppuppijets"));

    tpuppijet_subjet_corrector_MC.reset(new YearSwitcher(ctx));
    tpuppijet_subjet_corrector_MC->setup2016(std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2016, tpuppijec_ver_2016, tpuppijec_subjet_coll),"toppuppijets"));
    tpuppijet_subjet_corrector_MC->setup2017(std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2017, tpuppijec_ver_2017, tpuppijec_subjet_coll),"toppuppijets"));
    tpuppijet_subjet_corrector_MC->setup2018(std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2018, tpuppijec_ver_2018, tpuppijec_subjet_coll),"toppuppijets"));

    tpuppijet_JLC_MC.reset(new YearSwitcher(ctx));
    tpuppijet_JLC_MC->setup2016(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2016, tpuppijec_ver_2016, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_JLC_MC->setup2017(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2017, tpuppijec_ver_2017, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_JLC_MC->setup2018(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_2018, tpuppijec_ver_2018, tpuppijec_tjet_coll),"toppuppijets"));


    const Year & year = extract_year(ctx);
    std::string jer_tag = "";
    if (year == Year::is2016v2 || year == Year::is2016v3) {
      jer_tag = "Summer16_25nsV1";
    } else if (year == Year::is2017v1 || year == Year::is2017v2) {
      jer_tag = "Fall17_V3";
    } else if (year == Year::is2018) {
      jer_tag = "Autumn18_V7";
    } else {
      throw runtime_error("Cannot find suitable jet resolution file & scale factors for this year for JetResolutionSmearer");
    }
    tpuppijet_resolution_smearer.reset(new GenericJetResolutionSmearer(ctx, "toppuppijets", "gentopjets", JERFiles::JERPathStringMC(jer_tag,algo+pus,"SF"), JERFiles::JERPathStringMC(jer_tag,algo+pus,"PtResolution")));


  }

  if(is_data){

    tpuppijec_switcher_16.reset(new RunSwitcher(ctx, "2016"));
    tpuppijec_subjet_switcher_16.reset(new RunSwitcher(ctx, "2016"));
    tpuppijec_JLC_switcher_16.reset(new RunSwitcher(ctx, "2016"));
    for (const auto & runItr : runPeriods2016) { // runPeriods defined in common/include/Utils.h
      tpuppijec_switcher_16->setupRun(runItr, std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2016, tpuppijec_ver_2016, tpuppijec_tjet_coll, runItr),"toppuppijets"));
      tpuppijec_subjet_switcher_16->setupRun(runItr, std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2016, tpuppijec_ver_2016, tpuppijec_subjet_coll, runItr),"toppuppijets"));
      tpuppijec_JLC_switcher_16->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2016, tpuppijec_ver_2016, tpuppijec_subjet_coll, runItr),"toppuppijets"));
    }

    tpuppijec_switcher_17.reset(new RunSwitcher(ctx, "2017"));
    tpuppijec_subjet_switcher_17.reset(new RunSwitcher(ctx, "2017"));
    tpuppijec_JLC_switcher_17.reset(new RunSwitcher(ctx, "2017"));
    for (const auto & runItr : runPeriods2017) {
      tpuppijec_switcher_17->setupRun(runItr, std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2017, tpuppijec_ver_2017, tpuppijec_tjet_coll, runItr),"toppuppijets"));
      tpuppijec_subjet_switcher_17->setupRun(runItr, std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2017, tpuppijec_ver_2017, tpuppijec_subjet_coll, runItr),"toppuppijets"));
      tpuppijec_JLC_switcher_17->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2017, tpuppijec_ver_2017, tpuppijec_subjet_coll, runItr),"toppuppijets"));
    }

    tpuppijec_switcher_18.reset(new RunSwitcher(ctx, "2018"));
    tpuppijec_subjet_switcher_18.reset(new RunSwitcher(ctx, "2018"));
    tpuppijec_JLC_switcher_18.reset(new RunSwitcher(ctx, "2018"));
    for (const auto & runItr : runPeriods2018) {
      tpuppijec_switcher_18->setupRun(runItr, std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2018, tpuppijec_ver_2018, tpuppijec_tjet_coll, runItr),"toppuppijets"));
      tpuppijec_subjet_switcher_18->setupRun(runItr, std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2018, tpuppijec_ver_2018, tpuppijec_subjet_coll, runItr),"toppuppijets"));
      tpuppijec_JLC_switcher_18->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_2018, tpuppijec_ver_2018, tpuppijec_subjet_coll, runItr),"toppuppijets"));
    }

    tpuppijet_corrector_data.reset(new YearSwitcher(ctx));
    tpuppijet_corrector_data->setup2016(tpuppijec_switcher_16);
    tpuppijet_corrector_data->setup2017(tpuppijec_switcher_17);
    tpuppijet_corrector_data->setup2018(tpuppijec_switcher_18);

    tpuppijet_subjet_corrector_data.reset(new YearSwitcher(ctx));
    tpuppijet_subjet_corrector_data->setup2016(tpuppijec_subjet_switcher_16);
    tpuppijet_subjet_corrector_data->setup2017(tpuppijec_subjet_switcher_17);
    tpuppijet_subjet_corrector_data->setup2018(tpuppijec_subjet_switcher_18);

    tpuppijet_JLC_data.reset(new YearSwitcher(ctx));
    tpuppijet_JLC_data->setup2016(tpuppijec_JLC_switcher_16);
    tpuppijet_JLC_data->setup2017(tpuppijec_JLC_switcher_17);
    tpuppijet_JLC_data->setup2018(tpuppijec_JLC_switcher_18);
  }


}

bool TopPuppiJetCorrections::process(uhh2::Event & event){
  if(!init_done){
    throw runtime_error("TopPuppiJetCorrections::init not called (has to be called in AnalysisModule constructor)");
  }
  if (is_mc) {
    //cout << "Correct MC for PUPPI jets" << endl;
    tpuppijet_corrector_MC->process(event);
    tpuppijet_subjet_corrector_MC->process(event);
    tpuppijet_JLC_MC->process(event);
    tpuppijet_resolution_smearer->process(event);
  } 
  if (is_data) {
    //cout << "Correct DATA for PUPPI jets" << endl;
    tpuppijet_corrector_data->process(event);
    tpuppijet_subjet_corrector_data->process(event);
    tpuppijet_JLC_data->process(event);
  }
  return true;
}

