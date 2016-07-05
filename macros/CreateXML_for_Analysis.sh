#!/bin/bash
path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJSkimming/Selas2015_4fb_TightMuonID/workdir_Skimming/uhh2.AnalysisModuleRunner.
#source ~/Scripts/StartMe_CMSSW_8_0_8_patch1.sh
cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_8_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleMUON_*" DATA_SingleMUON.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_*" DATA_SingleEG.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_NLO_M10to50_*" MC_DYJetsToLL_NLO_M10to50.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_NLO_M50_*" MC_DYJetsToLL_NLO_M50.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200_*" MC_WJets_LNu_HT100To200.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400_*" MC_WJets_LNu_HT200To400.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600_*" MC_WJets_LNu_HT400To600.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800_*" MC_WJets_LNu_HT600To800.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200_*" MC_WJets_LNu_HT800To1200.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500_*" MC_WJets_LNu_HT1200To2500.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf_*" MC_WJets_LNu_HT2500ToInf.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT500to700_*" MC_QCD_HT500to700.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT700to1000_*" MC_QCD_HT700to1000.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT1000to1500_*" MC_QCD_HT1000to1500.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT1500to2000_*" MC_QCD_HT1500to2000.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.QCD_HT2000toInf_*" MC_QCD_HT2000toInf.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WW_*" MC_WW.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WZ_*" MC_WZ.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.ZZ_*" MC_ZZ.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.ST_s-channel-4f_*" MC_ST_s-channel-4f.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.ST_t-channel_4f_*" MC_ST_t-channel_4f.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.STneg_tW_inc_*" MC_STneg_tW_inc.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.STpos_tW_inc_*" MC_STpos_tW_inc.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.TTbar_*" MC_TTbar.xml

cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_8_patch1/src/UHH2/ZprimeSemiLeptonic/config/