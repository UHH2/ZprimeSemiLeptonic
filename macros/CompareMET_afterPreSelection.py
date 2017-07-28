#! /usr/bin/env python 
# Compare MET from different collections after Preselection
# usage:
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming
# python /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros/CompareMET_afterPreSelection.py
from ROOT import *
import sys
import numpy

#Set names of channels, hists, etc
samplelist = {'unCorrMET':'ElecID_CutBased_tight_MET50_elecPt50_woEGReg_jetIDtight_slimmedMETs_woMETrecorr_JLCkey/uhh2.AnalysisModuleRunner.DATA.DATA_SingleElectron_Run2016H.root','CorrMET':'ElecID_CutBased_tight_MET50_elecPt50_woEGReg_jetIDtight_slimmedMETsMuEGClean_METrecorr_JLCkey/uhh2.AnalysisModuleRunner.DATA.DATA_SingleElectron_Run2016H.root',
              'CorrMET2':'ElecID_CutBased_tight_MET50_elecPt50_woEGReg_jetIDtight_slimmedMETsMuEGClean_woPhotonEGReg_JLCkey/uhh2.AnalysisModuleRunner.DATA.DATA_SingleElectron_Run2016H.root'}
varlist = {'unCorrMET':'slimmedMETs.m_pt','CorrMET':'slimmedMETsMuEGClean.m_pt','CorrMET2':'slimmedMETsMuEGClean.m_pt'}
colorlist = {'unCorrMET':2,'CorrMET':3,'CorrMET2':4}
#TH2
hists = {}
histsDraw = {}


#TCanvas
canvas = TCanvas('MET','MET',800,600)  
legend = TLegend(.64,.59,.99,.95)
gStyle.SetOptStat(0)
gStyle.SetOptTitle(0)

for key_sample in samplelist:
    inf = TFile.Open(samplelist[key_sample])
    tree = inf.Get('AnalysisTree')
    hists[key_sample]  = TH1D('h_MET'+key_sample,'h_MET'+key_sample,100,0,1000)
#    tree.Draw(varlist[key_sample]+'>>h_MET'+key_sample,'weight*(0<1)')
    tree.Draw(varlist[key_sample]+'>>h_MET'+key_sample)
    hists[key_sample].Print()
    hists[key_sample].SetMarkerStyle(20)
    hists[key_sample].SetMarkerColor(colorlist[key_sample])
    hists[key_sample].SetLineColor(colorlist[key_sample])
    hists[key_sample].GetXaxis().SetTitle("MET, GeV")
    hists[key_sample].GetYaxis().SetTitle("Events")
    hists[key_sample].GetXaxis().SetLabelSize(0.045)
    hists[key_sample].GetYaxis().SetLabelSize(0.045)
    hists[key_sample].GetXaxis().SetTitleSize(0.05)
    hists[key_sample].GetYaxis().SetTitleSize(0.05)
 #   hists[key_sample].GetYaxis().SetNdivisions(5,5,0)
 #   hists[key_sample].GetXaxis().SetNdivisions(5,5,0)
    hists[key_sample].GetXaxis().SetTitleOffset(0.95)
#    histsDraw[key_sample] = hists[key_sample].DrawClone("ep same")
    histsDraw[key_sample] = hists[key_sample].Clone()
    histsDraw[key_sample].SetDirectory(0) 
#    legend.AddEntry(histsDraw[key_sample],key_sample,"lp")  
#    hists[key_var+key_sample].GetZaxis().SetRangeUser(0,1e4)
 
#legend.Draw()
 
histsDraw['CorrMET2'].Add(histsDraw['unCorrMET'],-1)
histsDraw['CorrMET2'].GetYaxis().SetTitle("corrMET2-unCorrMET")    
histsDraw['CorrMET2'].SetTitle('RunH')
histsDraw['CorrMET2'].Draw()
#canvas.SetLogy() 
canvas.SaveAs('MET_w_wo_corr.root')
canvas.SaveAs('MET_w_wo_corr.pdf')


