#! /usr/bin/env python 
# Compare variable in different paths
# usage:
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis
# python /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros/CompareVar_in_diff_paths.py
from ROOT import *
import sys
import numpy
#Set paths, samples, vars
#paths = {'3HLT':'TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid/T1_v06/elec/','2HLT':'TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_2HLT/T1_v06/elec/'}
paths = {'3HLT':'TTbarLJAnalysisLiteModule_BLINDED_20180108_JERhybrid/T1_v06/elec/','2HLT':'TTbarLJAnalysisLiteModule_BLINDED_20180108_JERhybrid_2HLTpaths/T1_v06/elec/'}

#paths = {'3HLT':'TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid/T1_v06/muon/','2HLT':'TTbarLJAnalysisLiteModule_NOTBLINDED_20180108_JERhybrid_2HLT/T1_v06/muon/'}

#paths = {'JER_scaling':'TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_w2DEleHLTSF_vetoGapElectrons_HLT1HLT2_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jec_up/T1_v06/elec/','JER_hybrid':'TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wNEW2DEleHLTSF_vetoGapElectrons_HLT1HLT2HLT3_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171214_JERhybridSFs/T1_v06/elec/'}
#paths = {'JER_scaling':'TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wNEW2DEleHLTSF_vetoGapElectrons_HLT1HLT2HLT3_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jer_jec_nominal_topptreweight/T1_v06/elec/','JER_hybrid':'TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wNEW2DEleHLTSF_vetoGapElectrons_HLT1HLT2HLT3_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171214_JERhybridSFs/T1_v06/elec/'}
#paths = {'JER_scaling':'TTbarLJAnalysisLiteModule_dRPUPPI10_wCSVshapeSF_wMisTopTagSF_wNEW2DEleHLTSF_vetoGapElectrons_HLT1HLT2HLT3_NOTBLINED_WJetsOLDbdt_muRmuF_updTTAGeff_20171020_jer_jec_nominal_topptreweight/T1_v06/elec/'}
#samplelist = {'ttbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root','wjets_l':'uhh2.AnalysisModuleRunner.MC.WJets__L.root'}
#varlist = {'jet1_pt':'ljet_pt'}
#colorlist = {'JER_scaling':2,'JER_hybrid':4}
#markerlist = {'JER_scaling':2.2,'JER_hybrid':1.2}

#samplelist = {'ttbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root','wjets_l':'uhh2.AnalysisModuleRunner.MC.WJets__L.root'}

#samplelist = {'DATA':'uhh2.AnalysisModuleRunner.DATA.DATA_NOTBLINDED.root'}
samplelist = {'DATA':'uhh2.AnalysisModuleRunner.DATA.DATA.root'}
varlist = {'jet1_pt':'ljet_pt','lep_pt':'lep_pt','Mttbar':'Mttbar'}
colorlist = {'2HLT':2,'3HLT':4}
markerlist = {'2HLT':2.2,'3HLT':1.2}
#TH2
hists = {}
histsDraw = {}


for key_var in varlist:
    for key_sample in samplelist:
        #TCanvas
        canvas = TCanvas('jet1','jet1',800,600)  
        legend = TLegend(.64,.59,.99,.95)
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)

        for key_path in paths:
            inf = TFile.Open(paths[key_path]+samplelist[key_sample])
            tree = inf.Get('AnalysisTree')
            hists[key_sample+key_var+key_path]  = TH1D('h_'+key_var+'_'+key_sample+key_path,'h_'+key_var+'_'+key_sample+key_path,60,0,6000)
            tree.Draw(varlist[key_var]+'>>h_'+key_var+'_'+key_sample+key_path,'weight*(1>0)')
            hists[key_sample+key_var+key_path].Print()
            hists[key_sample+key_var+key_path].SetMarkerStyle(20)
            hists[key_sample+key_var+key_path].SetMarkerSize(markerlist[key_path])
            hists[key_sample+key_var+key_path].SetMarkerColor(colorlist[key_path])
            hists[key_sample+key_var+key_path].SetLineColor(colorlist[key_path])
            hists[key_sample+key_var+key_path].GetXaxis().SetTitle(key_var)
#            hists[key_sample+key_var+key_path].GetYaxis().SetTitle("N_{JERhybrid}-N_{JERscaling}/N_{JERscaling}")
            hists[key_sample+key_var+key_path].GetYaxis().SetTitle("N_{3HLT}-N_{2HLT}/N_{2HLT}")
            hists[key_sample+key_var+key_path].GetXaxis().SetLabelSize(0.045)
            hists[key_sample+key_var+key_path].GetYaxis().SetLabelSize(0.045)
            hists[key_sample+key_var+key_path].GetXaxis().SetTitleSize(0.05)
            hists[key_sample+key_var+key_path].GetYaxis().SetTitleSize(0.05)
            hists[key_sample+key_var+key_path].GetXaxis().SetTitleOffset(0.95)

            histsDraw[key_sample+key_var+key_path] = hists[key_sample+key_var+key_path].Clone()
            histsDraw[key_sample+key_var+key_path].SetDirectory(0) 

        histsDraw[key_sample+key_var+'3HLT'].Add(histsDraw[key_sample+key_var+'2HLT'],-1)
        histsDraw[key_sample+key_var+'3HLT'].Divide(histsDraw[key_sample+key_var+'2HLT'])
        histsDraw[key_sample+key_var+'3HLT'].Draw('EP')
        canvas.SaveAs(key_sample+'_'+key_var+'.pdf')
 




