#!/bin/bash
cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming/ElecID_efficiency_AddQCD_MET50_Rebin/
#for path in v02 v03 v04 v05 v06 v07 
#for path in v07/ v061/4/40/ v061/2/20/ v061/2/40/ v061/4/20/ v061/4/60/ v061/2/60/
for path in v02/ v021/4/40/ v021/4/20/ v021/2/40/ v021/2/20/ v021/2/60/ v021/4/60/  
do
    rm $path/uhh2.AnalysisModuleRunner.MC.QCD.root
    rm $path/uhh2.AnalysisModuleRunner.MC.GJets.root
    rm $path/uhh2.AnalysisModuleRunner.MC.QCDGJets.root
    hadd $path/uhh2.AnalysisModuleRunner.MC.QCD.root $path/uhh2.AnalysisModuleRunner.MC.QCD*.root
    hadd $path/uhh2.AnalysisModuleRunner.MC.GJets.root $path/uhh2.AnalysisModuleRunner.MC.GJets*.root
    hadd $path/uhh2.AnalysisModuleRunner.MC.QCDGJets.root $path/uhh2.AnalysisModuleRunner.MC.QCD.root $path/uhh2.AnalysisModuleRunner.MC.GJets.root
done
