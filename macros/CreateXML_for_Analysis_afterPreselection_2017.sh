#!/bin/bash
#where UHH2 code installed
pathGL_code=/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/
#where (NOT MERGED) trees after preselection stored
path_data=/nfs/dust/cms/user/deleokse/analysis/ZprimeSemileptonic/Preselection/Output_2017/uhh2.AnalysisModuleRunner. 

mkdir $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_20190928
cd $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_20190928


# #MC
for sample_name in TTToSemiLeptonic_2017 TTToHadronic_2017 TTTo2L2Nu_2017 WW_2017 WZ_2017 ZZ_2017 ST_t-channel_antitop_2017 ST_t-channel_top_2017 ST_tW_antitop_5f_inclusiveDecays_2017 ST_tW_top_5f_inclusiveDecays_2017 QCD_Pt-15to30_2017 QCD_Pt-30to50_2017 QCD_Pt-50to80_2017 QCD_Pt-80to120_2017 QCD_Pt-120to170_2017 QCD_Pt-170to300_2017 QCD_Pt-300to470_2017 QCD_Pt-470to600_2017 QCD_Pt-600to800_2017 QCD_Pt-800to1000_2017 QCD_Pt-1000to1400_2017 QCD_Pt-1400to1800_2017 QCD_Pt-1800to2400_2017 QCD_Pt-2400to3200_2017 QCD_Pt-3200toInf_2017 WJetsToLNu_HT-70To100_2017 WJetsToLNu_HT-100To200_2017 WJetsToLNu_HT-200To400_2017 WJetsToLNu_HT-400To600_2017 WJetsToLNu_HT-600To800_2017 WJetsToLNu_HT-800To1200_2017 WJetsToLNu_HT-1200To2500_2017 WJetsToLNu_HT-2500ToInf_2017 ZprimeToTTJet_M1000_2017  

do
    echo $sample_name

       $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"MC."${sample_name}"*.root" MC_$sample_name.xml
       python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 MC_$sample_name.xml True
done

# # #DATA
for sample_name in DATA_SingleMuon_Run2017C DATA_SingleMuon_Run2017D DATA_SingleMuon_Run2017E DATA_SingleMuon_Run2017F DATA_SingleElectron_Run2017C DATA_SingleElectron_Run2017D DATA_SingleElectron_Run2017E DATA_SingleElectron_Run2017F 

do
    echo $sample_name 
    $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"DATA."${sample_name}"*.root" DATA_$sample_name.xml
    python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 DATA_$sample_name.xml True

done
pwd
cd $pathGL_code/ZprimeSemiLeptonic/macros
