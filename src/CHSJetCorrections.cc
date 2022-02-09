#include "../include/CHSJetCorrections.h"
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

void CHSJetCorrections::fail_if_init() const{
  if(init_done){
    throw invalid_argument("CHSJetCorrections::init already called!");
  }
}


CHSJetCorrections::CHSJetCorrections(){
  jec_tag_UL16preVFP = "Summer19UL16APV";
  jec_ver_UL16preVFP = "7";

  jec_tag_UL16postVFP = "Summer19UL16";
  jec_ver_UL16postVFP = "7";

  jec_tag_UL17 = "Summer19UL17";
  jec_ver_UL17 = "5";

  jec_tag_UL18 = "Summer19UL18";
  jec_ver_UL18 = "5";

  jec_jet_coll = "AK4PFchs";
}


void CHSJetCorrections::init(Context & ctx){
  if(init_done){
    throw invalid_argument("CHSJetCorrections::init called twice!");
  }
  init_done = true;

  h_CHSjets_branch = ctx.get_handle< std::vector<Jet> >("jetsAk4CHS");

  is_data = ctx.get("dataset_type") == "DATA";
  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);

  if(is_mc){
    jet_corrector_MC.reset(new YearSwitcher(ctx));
    jet_corrector_MC->setupUL16preVFP(std::make_shared<GenericJetCorrector>(ctx, JERFiles::JECFilesMC(jec_tag_UL16preVFP, jec_ver_UL16preVFP, jec_jet_coll),"jetsAk4CHS"));
    jet_corrector_MC->setupUL16postVFP(std::make_shared<GenericJetCorrector>(ctx, JERFiles::JECFilesMC(jec_tag_UL16postVFP, jec_ver_UL16postVFP, jec_jet_coll),"jetsAk4CHS"));
    jet_corrector_MC->setupUL17(std::make_shared<GenericJetCorrector>(ctx, JERFiles::JECFilesMC(jec_tag_UL17, jec_ver_UL17, jec_jet_coll),"jetsAk4CHS"));
    jet_corrector_MC->setupUL18(std::make_shared<GenericJetCorrector>(ctx, JERFiles::JECFilesMC(jec_tag_UL18, jec_ver_UL18, jec_jet_coll),"jetsAk4CHS"));

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
    jet_resolution_smearer.reset(new GenericJetResolutionSmearer(ctx, "jetsAk4CHS", "genjets", JERFiles::JERPathStringMC(jer_tag,"AK4PFchs","SF"), JERFiles::JERPathStringMC(jer_tag,"AK4PFchs","PtResolution")));


  }

}

bool CHSJetCorrections::process(uhh2::Event & event){
  if(!init_done){
    throw runtime_error("CHSJetCorrections::init not called (has to be called in AnalysisModule constructor)");
  }
  vector<Jet> CHSjets_branch = event.get(h_CHSjets_branch);

  if (is_mc) {
    //cout << "Going to correct CHS Ak4 jets" << endl;
    jet_corrector_MC->process(event);
    jet_resolution_smearer->process(event);
  } 

  return true;
}

