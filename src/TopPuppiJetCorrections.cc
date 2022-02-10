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
  tpuppijec_tag_UL16preVFP = "Summer19UL16APV";
  tpuppijec_ver_UL16preVFP = "7";

  tpuppijec_tag_UL16postVFP = "Summer19UL16";
  tpuppijec_ver_UL16postVFP = "7";

  tpuppijec_tag_UL17 = "Summer19UL17";
  tpuppijec_ver_UL17 = "5";

  tpuppijec_tag_UL18 = "Summer19UL18";
  tpuppijec_ver_UL18 = "5";

  tpuppijec_tjet_coll = "AK8PFPuppi";
  tpuppijec_subjet_coll = "AK4PFPuppi";
}


void TopPuppiJetCorrections::init(Context & ctx){
  if(init_done){
    throw invalid_argument("TopPuppiJetCorrections::init called twice!");
  }
  init_done = true;

  is_data = ctx.get("dataset_type") == "DATA";
  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);

  if(is_mc){
    tpuppijet_corrector_MC.reset(new YearSwitcher(ctx));
    tpuppijet_corrector_MC->setupUL16preVFP(std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL16preVFP, tpuppijec_ver_UL16preVFP, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_corrector_MC->setupUL16postVFP(std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL16postVFP, tpuppijec_ver_UL16postVFP, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_corrector_MC->setupUL17(std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL17, tpuppijec_ver_UL17, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_corrector_MC->setupUL18(std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL18, tpuppijec_ver_UL18, tpuppijec_tjet_coll),"toppuppijets"));

    tpuppijet_subjet_corrector_MC.reset(new YearSwitcher(ctx));
    tpuppijet_subjet_corrector_MC->setupUL16preVFP(std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL16preVFP, tpuppijec_ver_UL16preVFP, tpuppijec_subjet_coll),"toppuppijets"));
    tpuppijet_subjet_corrector_MC->setupUL16postVFP(std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL16postVFP, tpuppijec_ver_UL16postVFP, tpuppijec_subjet_coll),"toppuppijets"));
    tpuppijet_subjet_corrector_MC->setupUL17(std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL17, tpuppijec_ver_UL17, tpuppijec_subjet_coll),"toppuppijets"));
    tpuppijet_subjet_corrector_MC->setupUL18(std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL18, tpuppijec_ver_UL18, tpuppijec_subjet_coll),"toppuppijets"));

    tpuppijet_JLC_MC.reset(new YearSwitcher(ctx));
    tpuppijet_JLC_MC->setupUL16preVFP(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL16preVFP, tpuppijec_ver_UL16preVFP, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_JLC_MC->setupUL16postVFP(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL16postVFP, tpuppijec_ver_UL16postVFP, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_JLC_MC->setupUL17(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL17, tpuppijec_ver_UL17, tpuppijec_tjet_coll),"toppuppijets"));
    tpuppijet_JLC_MC->setupUL18(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tpuppijec_tag_UL18, tpuppijec_ver_UL18, tpuppijec_tjet_coll),"toppuppijets"));


    const Year & year = extract_year(ctx);
    std::string jer_tag = "";
    if (year == Year::isUL16preVFP) {
      jer_tag = "Summer20UL16APV_JRV3";
    } else if (year == Year::isUL16postVFP) {
      jer_tag = "Summer20UL16_JRV3";
    } else if (year == Year::isUL17) {
      jer_tag = "Summer19UL17_JRV2";
    } else if (year == Year::isUL18) {
      jer_tag = "Summer19UL18_JRV2";
    } else {
      throw runtime_error("Cannot find suitable jet resolution file & scale factors for this year for JetResolutionSmearer");
    }
    tpuppijet_resolution_smearer.reset(new GenericJetResolutionSmearer(ctx, "toppuppijets", "gentopjets", JERFiles::JERPathStringMC(jer_tag,tpuppijec_tjet_coll,"SF"), JERFiles::JERPathStringMC(jer_tag,tpuppijec_tjet_coll,"PtResolution")));


  }

  if(is_data){

    tpuppijec_switcher_UL16preVFP.reset(new RunSwitcher(ctx, "2016"));
    tpuppijec_subjet_switcher_UL16preVFP.reset(new RunSwitcher(ctx, "2016"));
    tpuppijec_JLC_switcher_UL16preVFP.reset(new RunSwitcher(ctx, "2016"));
    for (const auto & runItr : runPeriodsUL16preVFP) { // runPeriods defined in common/include/Utils.h
      tpuppijec_switcher_UL16preVFP->setupRun(runItr, std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL16preVFP, tpuppijec_ver_UL16preVFP, tpuppijec_tjet_coll, runItr),"toppuppijets"));
      tpuppijec_subjet_switcher_UL16preVFP->setupRun(runItr, std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL16preVFP, tpuppijec_ver_UL16preVFP, tpuppijec_subjet_coll, runItr),"toppuppijets"));
      tpuppijec_JLC_switcher_UL16preVFP->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL16preVFP, tpuppijec_ver_UL16preVFP, tpuppijec_subjet_coll, runItr),"toppuppijets"));
    }

    tpuppijec_switcher_UL16postVFP.reset(new RunSwitcher(ctx, "2016"));
    tpuppijec_subjet_switcher_UL16postVFP.reset(new RunSwitcher(ctx, "2016"));
    tpuppijec_JLC_switcher_UL16postVFP.reset(new RunSwitcher(ctx, "2016"));
    for (const auto & runItr : runPeriodsUL16postVFP) { // runPeriods defined in common/include/Utils.h
      tpuppijec_switcher_UL16postVFP->setupRun(runItr, std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL16postVFP, tpuppijec_ver_UL16postVFP, tpuppijec_tjet_coll, runItr),"toppuppijets"));
      tpuppijec_subjet_switcher_UL16postVFP->setupRun(runItr, std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL16postVFP, tpuppijec_ver_UL16postVFP, tpuppijec_subjet_coll, runItr),"toppuppijets"));
      tpuppijec_JLC_switcher_UL16postVFP->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL16postVFP, tpuppijec_ver_UL16postVFP, tpuppijec_subjet_coll, runItr),"toppuppijets"));
    }

    tpuppijec_switcher_UL17.reset(new RunSwitcher(ctx, "2017"));
    tpuppijec_subjet_switcher_UL17.reset(new RunSwitcher(ctx, "2017"));
    tpuppijec_JLC_switcher_UL17.reset(new RunSwitcher(ctx, "2017"));
    for (const auto & runItr : runPeriods2017) {
      tpuppijec_switcher_UL17->setupRun(runItr, std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL17, tpuppijec_ver_UL17, tpuppijec_tjet_coll, runItr),"toppuppijets"));
      tpuppijec_subjet_switcher_UL17->setupRun(runItr, std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL17, tpuppijec_ver_UL17, tpuppijec_subjet_coll, runItr),"toppuppijets"));
      tpuppijec_JLC_switcher_UL17->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL17, tpuppijec_ver_UL17, tpuppijec_subjet_coll, runItr),"toppuppijets"));
    }

    tpuppijec_switcher_UL18.reset(new RunSwitcher(ctx, "2018"));
    tpuppijec_subjet_switcher_UL18.reset(new RunSwitcher(ctx, "2018"));
    tpuppijec_JLC_switcher_UL18.reset(new RunSwitcher(ctx, "2018"));
    for (const auto & runItr : runPeriods2018) {
      tpuppijec_switcher_UL18->setupRun(runItr, std::make_shared<GenericTopJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL18, tpuppijec_ver_UL18, tpuppijec_tjet_coll, runItr),"toppuppijets"));
      tpuppijec_subjet_switcher_UL18->setupRun(runItr, std::make_shared<GenericSubJetCorrector>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL18, tpuppijec_ver_UL18, tpuppijec_subjet_coll, runItr),"toppuppijets"));
      tpuppijec_JLC_switcher_UL18->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tpuppijec_tag_UL18, tpuppijec_ver_UL18, tpuppijec_subjet_coll, runItr),"toppuppijets"));
    }

    tpuppijet_corrector_data.reset(new YearSwitcher(ctx));
    tpuppijet_corrector_data->setupUL16preVFP(tpuppijec_switcher_UL16preVFP);
    tpuppijet_corrector_data->setupUL16postVFP(tpuppijec_switcher_UL16postVFP);
    tpuppijet_corrector_data->setupUL17(tpuppijec_switcher_UL17);
    tpuppijet_corrector_data->setupUL18(tpuppijec_switcher_UL18);

    tpuppijet_subjet_corrector_data.reset(new YearSwitcher(ctx));
    tpuppijet_subjet_corrector_data->setupUL16preVFP(tpuppijec_subjet_switcher_UL16preVFP);
    tpuppijet_subjet_corrector_data->setupUL16postVFP(tpuppijec_subjet_switcher_UL16postVFP);
    tpuppijet_subjet_corrector_data->setupUL17(tpuppijec_subjet_switcher_UL17);
    tpuppijet_subjet_corrector_data->setupUL18(tpuppijec_subjet_switcher_UL18);

    tpuppijet_JLC_data.reset(new YearSwitcher(ctx));
    tpuppijet_JLC_data->setupUL16preVFP(tpuppijec_JLC_switcher_UL16preVFP);
    tpuppijet_JLC_data->setupUL16postVFP(tpuppijec_JLC_switcher_UL16postVFP);
    tpuppijet_JLC_data->setupUL17(tpuppijec_JLC_switcher_UL17);
    tpuppijet_JLC_data->setupUL18(tpuppijec_JLC_switcher_UL18);
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

