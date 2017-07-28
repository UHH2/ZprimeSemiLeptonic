#! /usr/bin/env python
from ROOT import *
import sys
import numpy
#import matplotlib.pyplot as plt
#from matplotlib.ticker import AutoMinorLocator, MultipleLocator

# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/ElecID_MVA_tight_noKinCuts/HLT_Ele45_CaloIdVT_GsfTrkIdT_PFJet200_PFJet50_v*NULL
# python ~/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros/FastTest_TriggerEff.py
samplelist = {'RSGluon_M0500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M0500.root','RSGluon_M0750':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M0750.root','RSGluon_M1000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1000.root','RSGluon_M1250':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1250.root','RSGluon_M1500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1500.root','RSGluon_M2000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M2000.root','RSGluon_M2500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M2500.root','RSGluon_M3000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3000.root','RSGluon_M3500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3500.root','RSGluon_M4000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M4000.root'}

#levels=['T0B0','T1','T0B1']
#fout = TFile('Ele_Trigger.root', 'recreate')
#gROOT.SetBatch(kTRUE)
ele1__pt_b = {}
ele1__pt_a = {}
ele1__pt_ratio = {}
#c1=TCanvas("c1","c1",600,600)
c1 = TCanvas("c1","",800,600)
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)
i = 0
for key_sample in samplelist:
    i = i+1
    myfile = TFile(samplelist[key_sample])
    print "opening", myfile
    # print "key_sample", key_sample
    print "i = ", i
    ele1__pt_b[key_sample] = myfile.Get("jet1/ele1__pt")
    ele1__pt_a[key_sample] = myfile.Get("trigger/ele1__pt")
    ele1__pt_ratio[key_sample] = ele1__pt_a[key_sample].Clone()
    ele1__pt_ratio[key_sample].Divide(ele1__pt_b[key_sample])
    # ele1__pt_ratio[key_sample].SetLineColor(i)
    ele1__pt_ratio[key_sample].SetMarkerStyle(20)
    ele1__pt_ratio[key_sample].SetMarkerColor(kRed)
    if i<2:
        ele1__pt_ratio[key_sample].Draw("EP")
        print "1st plot"
    else:
        ele1__pt_ratio[key_sample].Draw("EPSAME")
        print "more plots ..."

c1.SaveAs("Ele_Trigger.root")
