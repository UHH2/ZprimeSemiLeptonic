#!/bin/bash

year="UL17" # UL16preVFP / UL16postVFP / UL17 / UL18
input_dir="/nfs/dust/cms/group/zprime-uhh/Analysis_${year}/dilepton_TriggerModule/workdir_Analysis_${year}_muon_dilepton_trigger/"
output_dir="/nfs/dust/cms/group/zprime-uhh/Analysis_${year}/dilepton_TriggerModule/"

echo "hadding: year=${year}"

# DATA
hadd -f ${output_dir}uhh2.AnalysisModuleRunner.DATA.DATA.root ${input_dir}uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run*.root
# MC
hadd -f ${output_dir}uhh2.AnalysisModuleRunner.MC.TTbar.root ${input_dir}uhh2.AnalysisModuleRunner.MC.TTTo2L2Nu_UL17_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.TTToHadronic_UL17_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_UL17_*.root
hadd -f ${output_dir}uhh2.AnalysisModuleRunner.MC.ST.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ST_*.root
hadd -f ${output_dir}uhh2.AnalysisModuleRunner.MC.WJets.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WJetsToLNu_HT-*.root
hadd -f ${output_dir}uhh2.AnalysisModuleRunner.MC.DY.root ${input_dir}uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT-*.root
hadd -f ${output_dir}uhh2.AnalysisModuleRunner.MC.QCD.root ${input_dir}uhh2.AnalysisModuleRunner.MC.QCD_HT*.root
hadd -f ${output_dir}uhh2.AnalysisModuleRunner.MC.Diboson.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WW_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WZ_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZZ_*.root
