#include <TString.h>
#include <TFile.h>

#include "../include/Tools.h"

AnalysisTool::AnalysisTool(bool do_puppi_) : do_puppi(do_puppi_)
{
  tag = "2017_Moriond19JEC_looserselection";
  base_path_puppi = "/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/2017_Moriond19JEC_looserselection_Puppi";
  base_path_chs = "/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/2017_Moriond19JEC_looserselection";
  path_theta = "/nfs/dust/cms/user/reimersa/theta_Zprime/utils2/2017_Moriond19JEC_looserselection/";

  signalmasses = {500, 750, 1000, 1250, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000};
  for(unsigned int i=0; i<signalmasses.size(); i++){
    TString t = "";
    t += signalmasses[i];
    signalmasses_str.emplace_back(t);
  }
}
