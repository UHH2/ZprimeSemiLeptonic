#!/bin/bash

# simple script for creating xmls

dir="/nfs/dust/cms/group/zprime-uhh/Analysis_UL18/muon/workdir_Zprime_Analysis_UL18_muon/"

# DATA
for i in DATA_EGamma_RunA_UL18_blinded DATA_EGamma_RunB_UL18_blinded DATA_EGamma_RunC_UL18_blinded DATA_EGamma_RunD_UL18_blinded
do
  echo "----- ${i} -----"
  ./../../../scripts/create-dataset-xmlfile "${dir}uhh2.AnalysisModuleRunner.DATA.${i}_*.root" ${i}.xml
  python ../../../scripts/crab/readaMCatNloEntries.py 10 ${i}.xml True
done

# MC
for i in TTToSemiLeptonic_UL18 TTToHadronic_UL18 TTTo2L2Nu_UL18 WJetsToLNu_HT-70To100_UL18 WJetsToLNu_HT-100To200_UL18 WJetsToLNu_HT-200To400_UL18 WJetsToLNu_HT-400To600_UL18 WJetsToLNu_HT-600To800_UL18 WJetsToLNu_HT-800To1200_UL18 WJetsToLNu_HT-1200To2500_UL18 WJetsToLNu_HT-2500ToInf_UL18 DYJetsToLL_M-50_HT-70to100_UL18 DYJetsToLL_M-50_HT-100to200_UL18 DYJetsToLL_M-50_HT-200to400_UL18 DYJetsToLL_M-50_HT-400to600_UL18 DYJetsToLL_M-50_HT-600to800_UL18 DYJetsToLL_M-50_HT-800to1200_UL18 DYJetsToLL_M-50_HT-1200to2500_UL18 DYJetsToLL_M-50_HT-2500toInf_UL18 WW_UL18 WZ_UL18 ZZ_UL18 ST_tW_antitop_5f_inclusiveDecays_UL18 ST_tW_top_5f_inclusiveDecays_UL18 ST_tW_antitop_5f_NoFullyHadronicDecays_UL18 ST_tW_top_5f_NoFullyHadronicDecays_UL18 ST_t-channel_antitop_4f_InclusiveDecays_UL18 ST_t-channel_top_4f_InclusiveDecays_UL18 ST_s-channel_4f_leptonDecays_UL18 QCD_HT50to100_UL18 QCD_HT100to200_UL18 QCD_HT200to300_UL18 QCD_HT300to500_UL18 QCD_HT500to700_UL18 QCD_HT700to1000_UL18 QCD_HT1000to1500_UL18 QCD_HT1500to2000_UL18 QCD_HT2000toInf_UL18 ALP_ttbar_signal_UL18 ALP_ttbar_interference_UL18
do
  echo "----- ${i} -----"
  ./../../../scripts/create-dataset-xmlfile "${dir}uhh2.AnalysisModuleRunner.MC.${i}_*.root" ${i}.xml
  python ../../../scripts/crab/readaMCatNloEntries.py 10 ${i}.xml True
done
