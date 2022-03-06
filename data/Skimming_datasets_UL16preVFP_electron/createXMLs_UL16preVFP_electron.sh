#!/bin/bash

# simple script for creating xmls

dir="/nfs/dust/cms/group/zprime-uhh/Analysis_UL16preVFP/electron/workdir_Zprime_Analysis_UL16preVFP_electron/"

# DATA
for i in DATA_SingleElectron_RunB_UL16preVFP_blinded DATA_SingleElectron_RunC_UL16preVFP_blinded DATA_SingleElectron_RunD_UL16preVFP_blinded DATA_SingleElectron_RunE_UL16preVFP_blinded DATA_SingleElectron_RunF_UL16preVFP_blinded DATA_SinglePhoton_RunB_UL16preVFP_blinded DATA_SinglePhoton_RunC_UL16preVFP_blinded DATA_SinglePhoton_RunD_UL16preVFP_blinded DATA_SinglePhoton_RunE_UL16preVFP_blinded DATA_SinglePhoton_RunF_UL16preVFP_blinded
do
  echo "----- ${i} -----"
  ./../../../scripts/create-dataset-xmlfile "${dir}uhh2.AnalysisModuleRunner.DATA.${i}_*.root" ${i}.xml
  python ../../../scripts/crab/readaMCatNloEntries.py 10 ${i}.xml True
done

# MC
for i in TTToSemiLeptonic_UL16preVFP TTToHadronic_UL16preVFP TTTo2L2Nu_UL16preVFP WJetsToLNu_HT-70To100_UL16preVFP WJetsToLNu_HT-100To200_UL16preVFP WJetsToLNu_HT-200To400_UL16preVFP WJetsToLNu_HT-400To600_UL16preVFP WJetsToLNu_HT-600To800_UL16preVFP WJetsToLNu_HT-800To1200_UL16preVFP WJetsToLNu_HT-1200To2500_UL16preVFP WJetsToLNu_HT-2500ToInf_UL16preVFP DYJetsToLL_M-50_HT-70to100_UL16preVFP DYJetsToLL_M-50_HT-100to200_UL16preVFP DYJetsToLL_M-50_HT-200to400_UL16preVFP DYJetsToLL_M-50_HT-400to600_UL16preVFP DYJetsToLL_M-50_HT-600to800_UL16preVFP DYJetsToLL_M-50_HT-800to1200_UL16preVFP DYJetsToLL_M-50_HT-1200to2500_UL16preVFP DYJetsToLL_M-50_HT-2500toInf_UL16preVFP WW_UL16preVFP WZ_UL16preVFP ZZ_UL16preVFP ST_tW_antitop_5f_inclusiveDecays_UL16preVFP ST_tW_top_5f_inclusiveDecays_UL16preVFP ST_tW_antitop_5f_NoFullyHadronicDecays_UL16preVFP ST_tW_top_5f_NoFullyHadronicDecays_UL16preVFP ST_t-channel_antitop_4f_InclusiveDecays_UL16preVFP ST_t-channel_top_4f_InclusiveDecays_UL16preVFP ST_s-channel_4f_leptonDecays_UL16preVFP QCD_HT50to100_UL16preVFP QCD_HT100to200_UL16preVFP QCD_HT200to300_UL16preVFP QCD_HT300to500_UL16preVFP QCD_HT500to700_UL16preVFP QCD_HT700to1000_UL16preVFP QCD_HT1000to1500_UL16preVFP QCD_HT1500to2000_UL16preVFP QCD_HT2000toInf_UL16preVFP ALP_ttbar_signal_UL16preVFP ALP_ttbar_interference_UL16preVFP
do
  echo "----- ${i} -----"
  ./../../../scripts/create-dataset-xmlfile "${dir}uhh2.AnalysisModuleRunner.MC.${i}_*.root" ${i}.xml
  python ../../../scripts/crab/readaMCatNloEntries.py 10 ${i}.xml True
done
