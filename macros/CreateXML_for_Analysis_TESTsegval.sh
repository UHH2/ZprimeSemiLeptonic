#!/bin/bash

path=/afs/desy.de/user/k/karavdia/ZprimeSemiLeptonic_DATA_tmp/TESTsegval/uhh2.AnalysisModuleRunner.
mkdir /afs/desy.de/user/k/karavdia/CMSSW_8_0_19_patch2/UHH2/ZprimeSemiLeptonic/Skimming_datasets_TESTsegval
cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_19_patch2/UHH2/ZprimeSemiLeptonic/Skimming_datasets_TESTsegval
echo "MC.WJets_LNu_HT100To200__B"
~/CMSSW_8_0_19_patch2//UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__B*" MC_WJets_LNu_HT100To200__B.xml

cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_19_patch2/UHH2/ZprimeSemiLeptonic/config/
