#!/bin/bash
#where UHH2 code installed
pathGL_code=/nfs/dust/cms/user/deleokse/RunII_106_v2/CMSSW_10_6_28/src/UHH2/
#where (NOT MERGED) trees after preselection stored
path_data=/nfs/dust/cms/user/deleokse/RunII_106_v2/HHSignal_NNVars_DEEPAK8/muon/workdir_Zprime_Analysis_UL18/uhh2.AnalysisModuleRunner.

mkdir $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_UL18_HHSignal_NNVars_DEEPAK8
cd $pathGL_code/ZprimeSemiLeptonic/data/Skimming_datasets_UL18_HHSignal_NNVars_DEEPAK8


# #MC

#for sample_name in HscalarToTTTo1L1Nu2J_m365_w36p5_res_UL18 HscalarToTTTo1L1Nu2J_m400_w40p0_res_UL18 HscalarToTTTo1L1Nu2J_m500_w50p0_res_UL18 HscalarToTTTo1L1Nu2J_m600_w60p0_res_UL18 HscalarToTTTo1L1Nu2J_m800_w80p0_res_UL18 HscalarToTTTo1L1Nu2J_m1000_w100p0_res_UL18 HscalarToTTTo1L1Nu2J_m365_w36p5_int_UL18 HscalarToTTTo1L1Nu2J_m400_w40p0_int_UL18 HscalarToTTTo1L1Nu2J_m500_w50p0_int_UL18 HscalarToTTTo1L1Nu2J_m600_w60p0_int_UL18 HscalarToTTTo1L1Nu2J_m800_w80p0_int_UL18 HscalarToTTTo1L1Nu2J_m1000_w100p0_int_UL18 HpseudoToTTTo1L1Nu2J_m365_w36p5_res_UL18 HpseudoToTTTo1L1Nu2J_m400_w40p0_res_UL18 HpseudoToTTTo1L1Nu2J_m500_w50p0_res_UL18 HpseudoToTTTo1L1Nu2J_m600_w60p0_res_UL18 HpseudoToTTTo1L1Nu2J_m800_w80p0_res_UL18 HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_UL18 HpseudoToTTTo1L1Nu2J_m365_w36p5_int_UL18 HpseudoToTTTo1L1Nu2J_m400_w40p0_int_UL18 HpseudoToTTTo1L1Nu2J_m500_w50p0_int_UL18 HpseudoToTTTo1L1Nu2J_m600_w60p0_int_UL18 HpseudoToTTTo1L1Nu2J_m800_w80p0_int_UL18 HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_UL18 

for sample_name in HscalarToTTTo1L1Nu2J_m365_w36p5_res_UL18

do
    echo $sample_name

       $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"MC."${sample_name}"*.root" MC_$sample_name.xml
       python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 MC_$sample_name.xml True
done

## # #DATA
#for sample_name in DATA_EGamma_Run2018A DATA_EGamma_Run2018B DATA_EGamma_Run2018C DATA_EGamma_Run2018D DATA_SingleMuon_Run2018A DATA_SingleMuon_Run2018B DATA_SingleMuon_Run2018C DATA_SingleMuon_Run2018D 
#
#do
#    echo $sample_name 
#    $pathGL_code/scripts/create-dataset-xmlfile ${path_data}"DATA."${sample_name}"*.root" DATA_$sample_name.xml
#    python $pathGL_code/scripts/crab/readaMCatNloEntries.py 10 DATA_$sample_name.xml True
#
#done
pwd
cd $pathGL_code/ZprimeSemiLeptonic/macros
