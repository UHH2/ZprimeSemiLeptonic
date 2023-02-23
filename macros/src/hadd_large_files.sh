#!/bin/bash

# script for hadding root files/trees larger than 100 GB
# from: https://root-forum.cern.ch/t/root-6-04-14-hadd-100gb-and-rootlogon/24581/2

year="UL17" # UL16preVFP / UL16postVFP / UL17 / UL18
channel="muon" # electron / muon
input_dir="/nfs/dust/cms/group/zprime-uhh/Analysis_${year}/${channel}/workdir_Analysis_${year}_${channel}/"
output_dir="/nfs/dust/cms/group/zprime-uhh/Analysis_${year}/${channel}/"

pwd="$(pwd)/"
root.exe -b -l -q startup.C+
LD_PRELOAD=${pwd}startup_C.so hadd ${output_dir}uhh2.AnalysisModuleRunner.MC.TTbar_test.root ${input_dir}uhh2.AnalysisModuleRunner.MC.TTTo*.root
