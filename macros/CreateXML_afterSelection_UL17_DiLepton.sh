#!/bin/bash

#where UHH2 code installed
pathGL_code=/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/
#where (NOT MERGED) trees after preselection stored
path_data=/nfs/dust/cms/group/zprime-uhh/Analysis_UL17/dilepton/workdir_Analysis_UL17_muon_dilepton/uhh2.AnalysisModuleRunner.

mkdir $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_UL17_dilepton/
cd $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_UL17_dilepton/


# MC
for sample_name in TTToSemiLeptonic_UL17 TTToHadronic_UL17 TTTo2L2Nu_UL17 WJetsToLNu_HT-70To100_UL17 WJetsToLNu_HT-100To200_UL17 WJetsToLNu_HT-200To400_UL17 WJetsToLNu_HT-400To600_UL17 WJetsToLNu_HT-600To800_UL17 WJetsToLNu_HT-800To1200_UL17 WJetsToLNu_HT-1200To2500_UL17 WJetsToLNu_HT-2500ToInf_UL17 DYJetsToLL_M-50_HT-70to100_UL17 DYJetsToLL_M-50_HT-100to200_UL17 DYJetsToLL_M-50_HT-200to400_UL17 DYJetsToLL_M-50_HT-400to600_UL17 DYJetsToLL_M-50_HT-600to800_UL17 DYJetsToLL_M-50_HT-800to1200_UL17 DYJetsToLL_M-50_HT-1200to2500_UL17 DYJetsToLL_M-50_HT-2500toInf_UL17 WW_UL17 WZ_UL17 ZZ_UL17 ST_tW_antitop_5f_NoFullyHadronicDecays_UL17 ST_tW_top_5f_NoFullyHadronicDecays_UL17 ST_t-channel_antitop_4f_InclusiveDecays_UL17 ST_t-channel_top_4f_InclusiveDecays_UL17 ST_s-channel_4f_leptonDecays_UL17 QCD_HT50to100_UL17 QCD_HT100to200_UL17 QCD_HT200to300_UL17 QCD_HT300to500_UL17 QCD_HT500to700_UL17 QCD_HT700to1000_UL17 QCD_HT1000to1500_UL17 QCD_HT1500to2000_UL17 QCD_HT2000toInf_UL17 ALP_ttbar_signal_UL17 ALP_ttbar_interference_UL17
do
    echo $sample_name
    $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"MC."${sample_name}"*.root" MC_$sample_name.xml
    python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 MC_$sample_name.xml True
done

# DATA
for sample_name in DATA_SingleMuon_RunB_UL17 DATA_SingleMuon_RunC_UL17 DATA_SingleMuon_RunD_UL17 DATA_SingleMuon_RunE_UL17 DATA_SingleMuon_RunF_UL17
do
    echo $sample_name
    $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"DATA."${sample_name}"*.root" $sample_name.xml
    python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 $sample_name.xml True
done
pwd
cd $pathGL_code/ZprimeSemiLeptonic/macros
