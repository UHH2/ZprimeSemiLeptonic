#!/bin/bash

# simple script for creating xmls

dir="/nfs/dust/cms/group/zprime-uhh/Analysis_UL16postVFP/electron/workdir_Zprime_Analysis_UL16postVFP_electron/"

# DATA
for i in DATA_SingleElectron_RunF_UL16postVFP_blinded DATA_SingleElectron_RunG_UL16postVFP_blinded DATA_SingleElectron_RunH_UL16postVFP_blinded DATA_SinglePhoton_RunF_UL16postVFP_blinded DATA_SinglePhoton_RunG_UL16postVFP_blinded DATA_SinglePhoton_RunH_UL16postVFP_blinded
do
  echo "----- ${i} -----"
  ./../../../scripts/create-dataset-xmlfile "${dir}uhh2.AnalysisModuleRunner.DATA.${i}_*.root" ${i}.xml
  python ../../../scripts/crab/readaMCatNloEntries.py 10 ${i}.xml True
done

# MC
for i in TTToSemiLeptonic_UL16postVFP TTToHadronic_UL16postVFP TTTo2L2Nu_UL16postVFP WJetsToLNu_HT-70To100_UL16postVFP WJetsToLNu_HT-100To200_UL16postVFP WJetsToLNu_HT-200To400_UL16postVFP WJetsToLNu_HT-400To600_UL16postVFP WJetsToLNu_HT-600To800_UL16postVFP WJetsToLNu_HT-800To1200_UL16postVFP WJetsToLNu_HT-1200To2500_UL16postVFP WJetsToLNu_HT-2500ToInf_UL16postVFP DYJetsToLL_M-50_HT-70to100_UL16postVFP DYJetsToLL_M-50_HT-100to200_UL16postVFP DYJetsToLL_M-50_HT-200to400_UL16postVFP DYJetsToLL_M-50_HT-400to600_UL16postVFP DYJetsToLL_M-50_HT-600to800_UL16postVFP DYJetsToLL_M-50_HT-800to1200_UL16postVFP DYJetsToLL_M-50_HT-1200to2500_UL16postVFP DYJetsToLL_M-50_HT-2500toInf_UL16postVFP WW_UL16postVFP WZ_UL16postVFP ZZ_UL16postVFP ST_tW_antitop_5f_inclusiveDecays_UL16postVFP ST_tW_top_5f_inclusiveDecays_UL16postVFP ST_tW_antitop_5f_NoFullyHadronicDecays_UL16postVFP ST_tW_top_5f_NoFullyHadronicDecays_UL16postVFP ST_t-channel_antitop_4f_InclusiveDecays_UL16postVFP ST_t-channel_top_4f_InclusiveDecays_UL16postVFP ST_s-channel_4f_leptonDecays_UL16postVFP QCD_HT50to100_UL16postVFP QCD_HT100to200_UL16postVFP QCD_HT200to300_UL16postVFP QCD_HT300to500_UL16postVFP QCD_HT500to700_UL16postVFP QCD_HT700to1000_UL16postVFP QCD_HT1000to1500_UL16postVFP QCD_HT1500to2000_UL16postVFP QCD_HT2000toInf_UL16postVFP ALP_ttbar_signal_UL16postVFP ALP_ttbar_interference_UL16postVFP
do
  echo "----- ${i} -----"
  ./../../../scripts/create-dataset-xmlfile "${dir}uhh2.AnalysisModuleRunner.MC.${i}_*.root" ${i}.xml
  python ../../../scripts/crab/readaMCatNloEntries.py 10 ${i}.xml True
done
