#!/bin/bash
# path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJSkimming/Selas2015_4fb_20160721_METcorrected//workdir_Skimming/uhh2.AnalysisModuleRunner.
# cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_8_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets

#path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJSkimming/Selas2015_2DpT40_13fb_20160725/workdir_Skimming/uhh2.AnalysisModuleRunner.
path=/nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v1/ttbarLJSkimming/Selas2015_13fb_20160725_METcorrTEST/workdir_Skimming/uhh2.AnalysisModuleRunner.
cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_8_patch1/src/UHH2/ZprimeSemiLeptonic/Skimming_datasets_13fb_METcorrTEST

~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleMUON_*" DATA_SingleMUON.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"DATA.SingleEG_*" DATA_SingleEG.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_LO_M50_HT0100to0200*" MC_DYJetsToLL_LO_M50_HT0100to0200.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_LO_M50_HT0200to0400*" MC_DYJetsToLL_LO_M50_HT0200to0400.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.DYJetsToLL_LO_M50_HT0400to0600*" MC_DYJetsToLL_LO_M50_HT0400to0600.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__All*" MC_WJets_LNu_HT100To200.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400__All*" MC_WJets_LNu_HT200To400.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600__All*" MC_WJets_LNu_HT400To600.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800__All*" MC_WJets_LNu_HT600To800.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200__All*" MC_WJets_LNu_HT800To1200.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500__All*" MC_WJets_LNu_HT1200To2500.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf__All*" MC_WJets_LNu_HT2500ToInf.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__B*" MC_WJets_LNu_HT100To200__B.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400__B*" MC_WJets_LNu_HT200To400__B.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600__B*" MC_WJets_LNu_HT400To600__B.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800__B*" MC_WJets_LNu_HT600To800__B.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200__B*" MC_WJets_LNu_HT800To1200__B.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500__B*" MC_WJets_LNu_HT1200To2500__B.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf__B*" MC_WJets_LNu_HT2500ToInf__B.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__C*" MC_WJets_LNu_HT100To200__C.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400__C*" MC_WJets_LNu_HT200To400__C.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600__C*" MC_WJets_LNu_HT400To600__C.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800__C*" MC_WJets_LNu_HT600To800__C.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200__C*" MC_WJets_LNu_HT800To1200__C.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500__C*" MC_WJets_LNu_HT1200To2500__C.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf__C*" MC_WJets_LNu_HT2500ToInf__C.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT100To200__L*" MC_WJets_LNu_HT100To200__L.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT200To400__L*" MC_WJets_LNu_HT200To400__L.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT400To600__L*" MC_WJets_LNu_HT400To600__L.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT600To800__L*" MC_WJets_LNu_HT600To800__L.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT800To1200__L*" MC_WJets_LNu_HT800To1200__L.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT1200To2500__L*" MC_WJets_LNu_HT1200To2500__L.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.WJets_LNu_HT2500ToInf__L*" MC_WJets_LNu_HT2500ToInf__L.xml
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
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.ST_t-channel_top_4f_*" MC_ST_t-channel_top_4f.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.STneg_tW_inc_*" MC_STneg_tW_inc.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.STpos_tW_inc_*" MC_STpos_tW_inc.xml
~/CMSSW_8_0_8_patch1//src/UHH2/scripts/create-dataset-xmlfile $path"MC.TTbar_*" MC_TTbar.xml

cd /afs/desy.de/user/k/karavdia/CMSSW_8_0_8_patch1/src/UHH2/ZprimeSemiLeptonic/config/
