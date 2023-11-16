#!/bin/bash

for year in UL16preVFP UL16postVFP UL17 UL18
do
  for channel in electron muon
  do
    echo "hadding: year=${year}, channel=${channel}"
    dir="/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/macros/src/PDF_hists/${year}/${channel}/"
    hadd -T -f ${dir}uhh2.AnalysisModuleRunner.MC.ST.root ${dir}uhh2.AnalysisModuleRunner.MC.ST_s-channel.root ${dir}uhh2.AnalysisModuleRunner.MC.ST_t-channel.root ${dir}uhh2.AnalysisModuleRunner.MC.ST_tW.root
  done
done
