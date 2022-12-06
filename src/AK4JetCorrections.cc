#include "../include/AK4JetCorrections.h"
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

void AK4JetCorrections::fail_if_init() const{
  if(init_done){
    throw invalid_argument("AK4JetCorrections::init already called!");
  }
}


AK4JetCorrections::AK4JetCorrections(){
  jec_tag_UL16preVFP = "Summer19UL16APV";
  jec_ver_UL16preVFP = "7";

  jec_tag_UL16postVFP = "Summer19UL16";
  jec_ver_UL16postVFP = "7";

  jec_tag_UL17 = "Summer19UL17";
  jec_ver_UL17 = "5";

  jec_tag_UL18 = "Summer19UL18";
  jec_ver_UL18 = "5";

  jec_jet_coll = "AK4PFPuppi";
}


void AK4JetCorrections::init(Context & ctx){
  if(init_done){
    throw invalid_argument("AK4JetCorrections::init called twice!");
  }
  init_done = true;

  is_data = ctx.get("dataset_type") == "DATA";
  is_mc = ctx.get("dataset_type") == "MC";
  year = extract_year(ctx);

  if(is_mc){
    jet_corrector_MC.reset(new YearSwitcher(ctx));
    jet_corrector_MC->setupUL16preVFP(std::make_shared<GenericJetCorrector>(ctx, JERFiles::JECFilesMC(jec_tag_UL16preVFP, jec_ver_UL16preVFP, jec_jet_coll),"jets"));
    jet_corrector_MC->setupUL16postVFP(std::make_shared<GenericJetCorrector>(ctx, JERFiles::JECFilesMC(jec_tag_UL16postVFP, jec_ver_UL16postVFP, jec_jet_coll),"jets"));
    jet_corrector_MC->setupUL17(std::make_shared<GenericJetCorrector>(ctx, JERFiles::JECFilesMC(jec_tag_UL17, jec_ver_UL17, jec_jet_coll),"jets"));
    jet_corrector_MC->setupUL18(std::make_shared<GenericJetCorrector>(ctx, JERFiles::JECFilesMC(jec_tag_UL18, jec_ver_UL18, jec_jet_coll),"jets"));

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
    jet_resolution_smearer.reset(new GenericJetResolutionSmearer(ctx, "jets", "genjets", JERFiles::JERPathStringMC(jer_tag,"AK4PFPuppi","SF"), JERFiles::JERPathStringMC(jer_tag,"AK4PFPuppi","PtResolution")));


  }

}

  //propagate to MET
  //apply type1 MET correction to RAW MET
  //NB: jet with substracted muon Pt should be used
  void correct_MET(const Event & event, double pt_thresh = 15., double eta_thresh_low=0., double eta_thresh_high=5.5){
    //we start from raw MET
    LorentzVector metv4= event.met->uncorr_v4();
    for(auto & jet : *event.jets){
      //thresholds on the corrected jets: pt > 15, EM fraction < 0.9
      bool to_be_corrected = jet.v4().Pt() > 15.;
      to_be_corrected = to_be_corrected && ( fabs(jet.v4().Eta())<eta_thresh_low || fabs(jet.v4().Eta())>eta_thresh_high || jet.v4().Pt() > pt_thresh );
      to_be_corrected = to_be_corrected && (jet.neutralEmEnergyFraction()+jet.chargedEmEnergyFraction())<0.9;
      if(to_be_corrected){
        //slimmed MET is corrected by L1FastJet
        auto factor_raw = jet.JEC_factor_raw();
        auto L1factor_raw = jet.JEC_L1factor_raw();

        LorentzVector L1corr =   (L1factor_raw*factor_raw)*jet.v4();            //L1 corrected jets
        LorentzVector L123corr = jet.v4();                                      //L123 corrected jets (L23 in case of puppi)
        metv4 -=  L123corr;

        //slimmed MET is corrected by L1FastJet, for Puppi: L1factor_raw = 1 --> L1corr = raw-jet pT.
        metv4 += L1corr;
      }
    }
    event.met->set_pt(metv4.Pt());
    event.met->set_phi(metv4.Phi());
  }


bool AK4JetCorrections::process(uhh2::Event & event){
  if(!init_done){
    throw runtime_error("AK4JetCorrections::init not called (has to be called in AnalysisModule constructor)");
  }

  if (is_mc) {
    //cout << "Going to correct PUPPI Ak4 jets" << endl;
    jet_corrector_MC->process(event);
    jet_resolution_smearer->process(event);
    correct_MET(event);
  } 

  return true;
}

