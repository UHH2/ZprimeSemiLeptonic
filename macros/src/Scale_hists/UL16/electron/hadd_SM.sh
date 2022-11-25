#!/bin/bash

path_UL16preVFP_ele=/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/Scale_hists/UL16preVFP/electron/
path_UL16postVFP_ele=/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/Scale_hists/UL16postVFP/electron/

#hadd -T uhh2.AnalysisModuleRunner.MC.DY.root       $path_UL16preVFP_ele/uhh2.AnalysisModuleRunner.MC.DY*       $path_UL16postVFP_ele/uhh2.AnalysisModuleRunner.MC.DY*
#hadd -T uhh2.AnalysisModuleRunner.MC.QCD.root      $path_UL16preVFP_ele/uhh2.AnalysisModuleRunner.MC.QCD*      $path_UL16postVFP_ele/uhh2.AnalysisModuleRunner.MC.QCD*
#hadd -T uhh2.AnalysisModuleRunner.MC.WJets.root    $path_UL16preVFP_ele/uhh2.AnalysisModuleRunner.MC.WJets*    $path_UL16postVFP_ele/uhh2.AnalysisModuleRunner.MC.WJets*
#hadd -T uhh2.AnalysisModuleRunner.MC.TTbar.root    $path_UL16preVFP_ele/uhh2.AnalysisModuleRunner.MC.TT*       $path_UL16postVFP_ele/uhh2.AnalysisModuleRunner.MC.TT*
#hadd -T uhh2.AnalysisModuleRunner.MC.ST.root       $path_UL16preVFP_ele/uhh2.AnalysisModuleRunner.MC.ST*       $path_UL16postVFP_ele/uhh2.AnalysisModuleRunner.MC.ST*
hadd -T uhh2.AnalysisModuleRunner.MC.others.root    $path_UL16preVFP_ele/uhh2.AnalysisModuleRunner.MC.others*   $path_UL16postVFP_ele/uhh2.AnalysisModuleRunner.MC.others*
