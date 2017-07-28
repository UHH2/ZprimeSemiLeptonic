#!/bin/bash

path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming/ElecID_CutBased_medium_noIso_MET0_elecPt50/workdir_Skimming_QCDMVAinpput/uhh2.AnalysisModuleRunner.
mkdir -p /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets_36fb_QCD_cutElecIDmedium
cd /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets_36fb_QCD_cutElecIDmedium

#MC
#for sample_name in QCD_Pt_15to20_bcToE QCD_Pt_20to30_bcToE QCD_Pt_80to170_bcToE QCD_Pt_170to250_bcToE QCD_Pt_250toInf_bcToE QCD_Pt20to30_EMEnriched QCD_Pt30to50_EMEnriched QCD_Pt50to80_EMEnriched QCD_Pt50to80_EMEnriched QCD_Pt80to120_EMEnriched QCD_Pt120to170_EMEnriched QCD_Pt170to300_EMEnriched QCD_Pt300toInf_EMEnriched GJets_HT-100To200 GJets_HT-200To400 GJets_HT-400To600 GJets_HT-600ToInf GJets_HT-40To100 TTbar_part1 TTbar_part2 WJetsToLNu_Pt-100To250 WJetsToLNu_Pt-250To400 WJetsToLNu_Pt-400To600 WJetsToLNu_Pt-600ToInf WW WZ ZZ ST_s ST_tW_antitop ST_tW_top ST_t-channel_top ST_t-channel_antitop DYJetsToLL_M-50_HT-70to100 DYJetsToLL_M-50_HT-100to200 DYJetsToLL_M-50_HT-200to400 DYJetsToLL_M-50_HT-400to600 DYJetsToLL_M-50_HT-600to800 DYJetsToLL_M-50_HT-800to1200 DYJetsToLL_M-50_HT-1200to2500 DYJetsToLL_M-50_HT-2500toInf 
#for sample_name in QCD_Pt_15to20_bcToE QCD_Pt_20to30_bcToE QCD_Pt_30to80_bcToE QCD_Pt_80to170_bcToE QCD_Pt_170to250_bcToE QCD_Pt_250toInf_bcToE QCD_Pt20to30_EMEnriched QCD_Pt30to50_EMEnriched QCD_Pt50to80_EMEnriched  QCD_Pt80to120_EMEnriched QCD_Pt120to170_EMEnriched QCD_Pt170to300_EMEnriched QCD_Pt300toInf_EMEnriched GJets_HT-100To200 GJets_HT-200To400 GJets_HT-400To600 GJets_HT-600ToInf GJets_HT-40To100 
#for sample_name in TTbar_part1 TTbar_part2 WW WZ ZZ
#for sample_name in WJetsToLNu_Pt-100To250 WJetsToLNu_Pt-250To400 WJetsToLNu_Pt-400To600 WJetsToLNu_Pt-600ToInf
#for sample_name in ST_s ST_tW_antitop ST_tW_top ST_t-channel_top ST_t-channel_antitop DYJetsToLL_M-50_HT-70to100 DYJetsToLL_M-50_HT-100to200 DYJetsToLL_M-50_HT-200to400 DYJetsToLL_M-50_HT-400to600 DYJetsToLL_M-50_HT-600to800 DYJetsToLL_M-50_HT-800to1200 DYJetsToLL_M-50_HT-1200to2500 DYJetsToLL_M-50_HT-2500toInf
for sample_name in QCD_HT100to200 QCD_HT200to300 QCD_HT300to500 QCD_HT500to700 QCD_HT700to1000 QCD_HT1000to1500 QCD_HT1500to2000 QCD_HT2000toInf
do
    echo $sample_name
    /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile ${path}"MC."${sample_name}"*.root" MC_$sample_name.xml
    /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py ${path}"MC."${sample_name}"*.root" MC_$sample_name.xml
done
#DATA
#for sample_name in DATA_SingleElectron_Run2016B DATA_SingleElectron_Run2016C DATA_SingleElectron_Run2016D DATA_SingleElectron_Run2016E DATA_SingleElectron_Run2016F DATA_SingleElectron_Run2016G DATA_SingleElectron_Run2016H
#do
#    echo $sample_name 
#    /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-dataset-xmlfile ${path}"DATA."${sample_name}"*.root" DATA_$sample_name.xml
#    /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/scripts/create-multi-dataset-xmlfiles.py ${path}"DATA."${sample_name}"*.root" DATA_$sample_name.xml
#done

rm uhh2.AnalysisModuleRunner.*
rm TEMPLATE_*
cd /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/config/
