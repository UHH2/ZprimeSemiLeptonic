#!/bin/bash

#where UHH2 code installed
pathGL_code=/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/
#where (NOT MERGED) trees after preselection stored
path_data=/nfs/dust/cms/group/zprime-uhh/Analysis_UL18/dilepton/workdir_Analysis_UL18_muon/uhh2.AnalysisModuleRunner.

mkdir $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_UL18_dilepton/
cd $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_UL18_dilepton/


# MC
for sample_name in TTToSemiLeptonic_UL18 TTToHadronic_UL18 TTTo2L2Nu_UL18 WJetsToLNu_HT-70To100_UL18 WJetsToLNu_HT-100To200_UL18 WJetsToLNu_HT-200To400_UL18 WJetsToLNu_HT-400To600_UL18 WJetsToLNu_HT-600To800_UL18 WJetsToLNu_HT-800To1200_UL18 WJetsToLNu_HT-1200To2500_UL18 WJetsToLNu_HT-2500ToInf_UL18 DYJetsToLL_M-50_HT-70to100_UL18 DYJetsToLL_M-50_HT-100to200_UL18 DYJetsToLL_M-50_HT-200to400_UL18 DYJetsToLL_M-50_HT-400to600_UL18 DYJetsToLL_M-50_HT-600to800_UL18 DYJetsToLL_M-50_HT-800to1200_UL18 DYJetsToLL_M-50_HT-1200to2500_UL18 DYJetsToLL_M-50_HT-2500toInf_UL18 WW_UL18 WZ_UL18 ZZ_UL18 ST_tW_antitop_5f_NoFullyHadronicDecays_UL18 ST_tW_top_5f_NoFullyHadronicDecays_UL18 ST_t-channel_antitop_4f_InclusiveDecays_UL18 ST_t-channel_top_4f_InclusiveDecays_UL18 ST_s-channel_4f_leptonDecays_UL18 QCD_HT50to100_UL18 QCD_HT100to200_UL18 QCD_HT200to300_UL18 QCD_HT300to500_UL18 QCD_HT500to700_UL18 QCD_HT700to1000_UL18 QCD_HT1000to1500_UL18 QCD_HT1500to2000_UL18 QCD_HT2000toInf_UL18
do
    echo $sample_name
    $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"MC."${sample_name}"*.root" MC_$sample_name.xml
    python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 MC_$sample_name.xml True
done

# DATA
for sample_name in DATA_SingleMuon_RunA_UL18 DATA_SingleMuon_RunB_UL18 DATA_SingleMuon_RunC_UL18 DATA_SingleMuon_RunD_UL18
do
    echo $sample_name
    $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"DATA."${sample_name}"*.root" $sample_name.xml
    python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 $sample_name.xml True
done
pwd
cd $pathGL_code/ZprimeSemiLeptonic/macros
