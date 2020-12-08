#include "../include/TopJetCorrections.h"
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

void TopJetCorrections::fail_if_init() const{
  if(init_done){
    throw invalid_argument("TopJetCorrections::init already called!");
  }
}


TopJetCorrections::TopJetCorrections(){
  tjec_tag_2016 = "Summer16_07Aug2017";
  tjec_ver_2016 = "11";

  tjec_tag_2017 = "Fall17_17Nov2017";
  tjec_ver_2017 = "32";

  tjec_tag_2018 = "Autumn18";
  tjec_ver_2018 = "19";

  tjec_tjet_coll = "dummy";
  tjec_subjet_coll = "dummy";
}


void TopJetCorrections::init(Context & ctx){
  if(init_done){
    throw invalid_argument("TopJetCorrections::init called twice!");
  }
  init_done = true;

  is_data = ctx.get("dataset_type") == "DATA";
  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);

  // setup correction tjet type for JECs
  std::string userTopJetColl = string2lowercase(ctx.get("TopJetCollection"));

  std::string algo = "";
  // algo size
  if (userTopJetColl.find("ak4") != std::string::npos) {
    algo = "AK4";
  }
  else if(userTopJetColl.find("ak8") != std::string::npos){
    algo = "AK8";
  }
  else if (userTopJetColl.find("ak8") == std::string::npos) {
    std::cout << "TopJetCorrections.cxx: Cannot determine tjet cone + radius (neither AK4 nor AK8) - going to assume it is AK8 for JECs" << '\n';
    algo = "AK8";
  }

  std::string pus = "PFchs";
  // Pileup subtraction
  if (userTopJetColl.find("puppi") != std::string::npos) {
    pus = "PFPuppi";
  } else if (userTopJetColl.find("chs") == std::string::npos) {
    std::cout << "Cannot determine pileup subtraction (neither CHS nor PUPPI) - going to assume it is CHS for JECs" << std::endl;
  }
  tjec_tjet_coll = algo + pus;
  tjec_subjet_coll = "AK4PFchs";

  if(is_mc){
    tjet_corrector_MC.reset(new YearSwitcher(ctx));
    tjet_corrector_MC->setup2016(std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesMC(tjec_tag_2016, tjec_ver_2016, tjec_tjet_coll)));
    tjet_corrector_MC->setup2017(std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesMC(tjec_tag_2017, tjec_ver_2017, tjec_tjet_coll)));
    tjet_corrector_MC->setup2018(std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesMC(tjec_tag_2018, tjec_ver_2018, tjec_tjet_coll)));

    tjet_subjet_corrector_MC.reset(new YearSwitcher(ctx));
    tjet_subjet_corrector_MC->setup2016(std::make_shared<SubJetCorrector>(ctx, JERFiles::JECFilesMC(tjec_tag_2016, tjec_ver_2016, tjec_subjet_coll)));
    tjet_subjet_corrector_MC->setup2017(std::make_shared<SubJetCorrector>(ctx, JERFiles::JECFilesMC(tjec_tag_2017, tjec_ver_2017, tjec_subjet_coll)));
    tjet_subjet_corrector_MC->setup2018(std::make_shared<SubJetCorrector>(ctx, JERFiles::JECFilesMC(tjec_tag_2018, tjec_ver_2018, tjec_subjet_coll)));

    tjet_JLC_MC.reset(new YearSwitcher(ctx));
    tjet_JLC_MC->setup2016(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tjec_tag_2016, tjec_ver_2016, tjec_tjet_coll),"topjets"));
    tjet_JLC_MC->setup2017(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tjec_tag_2017, tjec_ver_2017, tjec_tjet_coll),"topjets"));
    tjet_JLC_MC->setup2018(std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesMC(tjec_tag_2018, tjec_ver_2018, tjec_tjet_coll),"topjets"));

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
    tjet_resolution_smearer.reset(new GenericJetResolutionSmearer(ctx, "topjets", "gentopjets", JERFiles::JERPathStringMC(jer_tag,algo+pus,"SF"), JERFiles::JERPathStringMC(jer_tag,algo+pus,"PtResolution")));


  }
   if(is_data){

    tjec_switcher_16.reset(new RunSwitcher(ctx, "2016"));
    tjec_subjet_switcher_16.reset(new RunSwitcher(ctx, "2016"));
    tjec_JLC_switcher_16.reset(new RunSwitcher(ctx, "2016"));
    for (const auto & runItr : runPeriods2016) { // runPeriods defined in common/include/Utils.h
      tjec_switcher_16->setupRun(runItr, std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesDATA(tjec_tag_2016, tjec_ver_2016, tjec_tjet_coll, runItr)));
      tjec_subjet_switcher_16->setupRun(runItr, std::make_shared<SubJetCorrector>(ctx, JERFiles::JECFilesDATA(tjec_tag_2016, tjec_ver_2016, tjec_subjet_coll, runItr)));
      tjec_JLC_switcher_16->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tjec_tag_2016, tjec_ver_2016, tjec_subjet_coll, runItr),"topjets"));
    }
      
    tjec_switcher_17.reset(new RunSwitcher(ctx, "2017"));
    tjec_subjet_switcher_17.reset(new RunSwitcher(ctx, "2017"));
    tjec_JLC_switcher_17.reset(new RunSwitcher(ctx, "2017"));
    for (const auto & runItr : runPeriods2017) {   
      tjec_switcher_17->setupRun(runItr, std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesDATA(tjec_tag_2017, tjec_ver_2017, tjec_tjet_coll, runItr)));
      tjec_subjet_switcher_17->setupRun(runItr, std::make_shared<SubJetCorrector>(ctx, JERFiles::JECFilesDATA(tjec_tag_2017, tjec_ver_2017, tjec_subjet_coll, runItr)));
      tjec_JLC_switcher_17->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tjec_tag_2017, tjec_ver_2017, tjec_subjet_coll, runItr),"topjets"));
    }

    tjec_switcher_18.reset(new RunSwitcher(ctx, "2018"));
    tjec_subjet_switcher_18.reset(new RunSwitcher(ctx, "2018"));
    tjec_JLC_switcher_18.reset(new RunSwitcher(ctx, "2018"));
    for (const auto & runItr : runPeriods2018) {
      tjec_switcher_18->setupRun(runItr, std::make_shared<TopJetCorrector>(ctx, JERFiles::JECFilesDATA(tjec_tag_2018, tjec_ver_2018, tjec_tjet_coll, runItr)));
      tjec_subjet_switcher_18->setupRun(runItr, std::make_shared<SubJetCorrector>(ctx, JERFiles::JECFilesDATA(tjec_tag_2018, tjec_ver_2018, tjec_subjet_coll, runItr)));
      tjec_JLC_switcher_18->setupRun(runItr, std::make_shared<JetLeptonCleaner_by_KEYmatching>(ctx, JERFiles::JECFilesDATA(tjec_tag_2018, tjec_ver_2018, tjec_subjet_coll, runItr),"topjets"));
    }

    tjet_corrector_data.reset(new YearSwitcher(ctx));
    tjet_corrector_data->setup2016(tjec_switcher_16);
    tjet_corrector_data->setup2017(tjec_switcher_17);
    tjet_corrector_data->setup2018(tjec_switcher_18);

    tjet_subjet_corrector_data.reset(new YearSwitcher(ctx));
    tjet_subjet_corrector_data->setup2016(tjec_subjet_switcher_16);
    tjet_subjet_corrector_data->setup2017(tjec_subjet_switcher_17);
    tjet_subjet_corrector_data->setup2018(tjec_subjet_switcher_18);

    tjet_JLC_data.reset(new YearSwitcher(ctx));
    tjet_JLC_data->setup2016(tjec_JLC_switcher_16);
    tjet_JLC_data->setup2017(tjec_JLC_switcher_17);
    tjet_JLC_data->setup2018(tjec_JLC_switcher_18);

  }

}

bool TopJetCorrections::process(uhh2::Event & event){
  if(!init_done){
    throw runtime_error("TopJetCorrections::init not called (has to be called in AnalysisModule constructor)");
  }
  if (is_mc) {
    //cout << "Going to correct CHS Ak8 jets" << endl;
    tjet_corrector_MC->process(event);
    tjet_subjet_corrector_MC->process(event);
    tjet_JLC_MC->process(event);
    tjet_resolution_smearer->process(event);
  } 
  if (is_data) {
    //cout << "Correct DATA for CHS jets" << endl;
    tjet_corrector_data->process(event);
    tjet_subjet_corrector_data->process(event);
    tjet_JLC_data->process(event);
  } 

  return true;
}

