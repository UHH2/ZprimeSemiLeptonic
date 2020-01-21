#!/bin/bash
#where UHH2 code installed
pathGL_code=/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/
#where (NOT MERGED) trees after preselection stored
path_data=/nfs/dust/cms/user/deleokse/analysis/ZPrime_2016/Preselection_ttbarReco/workdir_Zprime_PreSelec_2016_ttbarReco/uhh2.AnalysisModuleRunner. 

mkdir $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_2016_ttbarReco
cd $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_2016_ttbarReco


# #MC
for sample_name in TT_TuneCUETP8M2T4_2016v3 
do
    echo $sample_name

       $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"MC."${sample_name}"*.root" MC_$sample_name.xml
       python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 MC_$sample_name.xml True
done

pwd
cd $pathGL_code/ZprimeSemiLeptonic/macros
