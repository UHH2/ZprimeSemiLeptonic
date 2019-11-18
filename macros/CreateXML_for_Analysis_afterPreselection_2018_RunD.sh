#!/bin/bash
#where UHH2 code installed
pathGL_code=/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/
#where (NOT MERGED) trees after preselection stored
path_data=/nfs/dust/cms/user/deleokse/analysis/ZPrime_2018/Output_2018_RunD/workdir_Zprime_PreSelec_2018_RunD/uhh2.AnalysisModuleRunner. 

mkdir $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_2018_RunD
cd $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_2018_RunD


# #MC

for sample_name in TTToSemiLeptonic_2018 TTToHadronic_2018 TTTo2L2Nu_2018 WW_2018 WZ_2018 ZZ_2018 ST_t-channel_antitop_2018 ST_t-channel_top_2018 ST_tW_antitop_5f_inclusiveDecays_2018 ST_tW_top_5f_inclusiveDecays_2018 ST_s-channel_lepton_2018 ST_s-channel_hadronic_2018  WJetsToLNu_HT-70To100_2018 WJetsToLNu_HT-100To200_2018 WJetsToLNu_HT-200To400_2018 WJetsToLNu_HT-400To600_2018 WJetsToLNu_HT-600To800_2018 WJetsToLNu_HT-800To1200_2018 WJetsToLNu_HT-1200To2500_2018 WJetsToLNu_HT-2500ToInf_2018 ZprimeToTT_M1000_W100_2018 QCD_Pt-15to20_EMEnriched_2018 QCD_Pt-20to30_EMEnriched_2018 QCD_Pt-30to50_EMEnriched_2018 QCD_Pt-50to80_EMEnriched_2018 QCD_Pt-80to120_EMEnriched_2018 QCD_Pt-120to170_EMEnriched_2018 QCD_Pt-170to300_EMEnriched_2018 QCD_Pt-300toInf_EMEnriched_2018 QCD_Pt-15to20_MuEnrichedPt5_2018 QCD_Pt-20to30_MuEnrichedPt5_2018 QCD_Pt-30to50_MuEnrichedPt5_2018 QCD_Pt-50to80_MuEnrichedPt5_2018 QCD_Pt-80to120_MuEnrichedPt5_2018 QCD_Pt-120to170_MuEnrichedPt5_2018 QCD_Pt-170to300_MuEnrichedPt5_2018 QCD_Pt-300to470_MuEnrichedPt5_2018 QCD_Pt-470to600_MuEnrichedPt5_2018 QCD_Pt-600to800_MuEnrichedPt5_2018 QCD_Pt-800to1000_MuEnrichedPt5_2018 QCD_Pt-1000toInf_MuEnrichedPt5_2018 

do
    echo $sample_name

       $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"MC."${sample_name}"*.root" MC_$sample_name.xml
       python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 MC_$sample_name.xml True
done

# # #DATA
for sample_name in DATA_EGamma_Run2018D DATA_SingleMuon_Run2018D 

do
    echo $sample_name 
    $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"DATA."${sample_name}"*.root" DATA_$sample_name.xml
    python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 DATA_$sample_name.xml True

done
pwd
cd $pathGL_code/ZprimeSemiLeptonic/macros
