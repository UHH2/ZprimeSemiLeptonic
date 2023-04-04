#!/bin/bash

year="UL16postVFP" # UL16preVFP / UL16postVFP / UL17 / UL18
#input_dir="/nfs/dust/cms/group/zprime-uhh/Analysis_${year}/dilepton_TriggerModule/workdir_Analysis_${year}_muon_dilepton_trigger/"
input_dir="/nfs/dust/cms/group/zprime-uhh/Analysis_${year}/dilepton_TriggerModule/workdir_Analysis_${year}_muon/"
output_dir="/nfs/dust/cms/group/zprime-uhh/Analysis_${year}/dilepton_TriggerModule/"

echo "hadding: year=${year}"

# DATA
hadd ${output_dir}uhh2.AnalysisModuleRunner.DATA.DATA.root ${input_dir}uhh2.AnalysisModuleRunner.DATA.*.root
# MC
hadd ${output_dir}uhh2.AnalysisModuleRunner.MC.TTbar.root ${input_dir}uhh2.AnalysisModuleRunner.MC.TTTo2L2Nu_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.TTToHadronic_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic_*.root
hadd ${output_dir}uhh2.AnalysisModuleRunner.MC.ST.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ST_*.root
hadd ${output_dir}uhh2.AnalysisModuleRunner.MC.WJets.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WJetsToLNu_HT-*.root
hadd ${output_dir}uhh2.AnalysisModuleRunner.MC.DY.root ${input_dir}uhh2.AnalysisModuleRunner.MC.DYJetsToLL_M-50_HT-*.root
hadd ${output_dir}uhh2.AnalysisModuleRunner.MC.QCD.root ${input_dir}uhh2.AnalysisModuleRunner.MC.QCD_HT*.root
hadd ${output_dir}uhh2.AnalysisModuleRunner.MC.Diboson.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WW_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.WZ_*.root ${input_dir}uhh2.AnalysisModuleRunner.MC.ZZ_*.root
