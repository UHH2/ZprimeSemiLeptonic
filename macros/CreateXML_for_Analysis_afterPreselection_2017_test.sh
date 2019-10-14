#!/bin/bash
#where UHH2 code installed
pathGL_code=/nfs/dust/cms/user/deleokse/analysis/CMSSW_10_2_10/src/UHH2/
#where (NOT MERGED) trees after preselection stored
path_data=/nfs/dust/cms/user/deleokse/analysis/ZprimeSemileptonic_Test/Preselection_2017_test/workdir_Zprime_PreSelec_2017_test/uhh2.AnalysisModuleRunner. 

mkdir $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_20191011_test
cd $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_20191011_test


# #MC
for sample_name in TTToSemiLeptonic_2017 TTTo2L2Nu_2017  

do
    echo $sample_name

       $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"MC."${sample_name}"*.root" MC_$sample_name.xml
       python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 MC_$sample_name.xml True
done

pwd
cd $pathGL_code/ZprimeSemiLeptonic/macros
