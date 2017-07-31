#! /usr/bin/env python 
# Study correlation between Wlep Pt and other variables: MET, lep pt, etc
# usage:
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJAnalysis/ElecID_CutBased_medium_MET50_elecPt50_EGReg_jetIDtight_slimmedMETs_JLCdR_BLINDED_HLT1ORHLT2_wBtagSFs_jet2pt50/T1_v06/
# python /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros/ElectronWlepPt_study.py
from ROOT import *
import sys
import numpy

#Set names of channels, hists, etc
#samplelist = {'TTbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root'}
#samplelist = {'DATA_Run2016':'uhh2.AnalysisModuleRunner.DATA.DATA.root','MC':'uhh2.AnalysisModuleRunner.MC.MC.root','TTbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root','WJets':'uhh2.AnalysisModuleRunner.MC.WJets.root'}
samplelist = {'MC':'uhh2.AnalysisModuleRunner.MC.MC.root','TTbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root','WJets':'uhh2.AnalysisModuleRunner.MC.WJets.root'}
varlist = {'ele_pt':'lep_pt','met_pt':'met_pt','jet1_pt':'ljet_pt','jet2_pt':'fjet2_pt','2DminDR_lep_jet':'lep1__minDR_jet'} #'MYminDR_lep_jet':'dR_lep_cljet'
varnamelist = {'ele_pt':'electron pt, GeV','met_pt':'MET, GeV','jet1_pt':'jet1 pt, GeV','jet2_pt':'jet2 pt,GeV','2DminDR_lep_jet':'2D #deltaR(lep,jet)'}
Xvarlist = {'WlepPt':'W_{lep} pt, GeV','lep_pt':'electron pt, GeV','Mttbar':'M_{ttbar}, GeV'}
varlist_upperY = {'ele_pt':3000,'met_pt':2000,'jet1_pt':3000,'jet2_pt':3000,'2DminDR_lep_jet':5.0}
Xvarlist_upperX = {'WlepPt':3000,'lep_pt':3000,'Mttbar':10000}

#TH2
hists = {}


#TCanvas
canvas = {} 
for key_sample in samplelist:
    inf = TFile.Open(samplelist[key_sample])
    tree = inf.Get('AnalysisTree')
    for key_Xvar in Xvarlist: 
        for key_var in varlist:
            canvas[key_var+key_sample] = TCanvas('Correlation__'+key_Xvar+'_'+key_var,'WlepPt_'+key_var,800,600)
            canvas[key_var+key_sample].SetLogz()
            gStyle.SetOptStat(0)
            gStyle.SetOptTitle(0)
#            print "", Xvarlist_upperX[key_Xvar]
            hists[key_var+key_sample]  = TH2D('h_'+key_Xvar+'__'+key_var,'h_'+key_Xvar+'__'+key_var,50,0,Xvarlist_upperX[key_Xvar],50,0,varlist_upperY[key_var])
#            tree.Draw(varlist[key_var]+':'+key_Xvar+'>>h_'+key_Xvar+'__'+key_var,'weight*(Mttbar<2000.)','colz')
            tree.Draw(varlist[key_var]+':'+key_Xvar+'>>h_'+key_Xvar+'__'+key_var,'weight*(0<1)','colz')
            hists[key_var+key_sample].GetXaxis().SetTitle(Xvarlist[key_Xvar])
            hists[key_var+key_sample].GetYaxis().SetTitle(varnamelist[key_var])
            hists[key_var+key_sample].GetXaxis().SetLabelSize(0.045)
            hists[key_var+key_sample].GetYaxis().SetLabelSize(0.045)
            hists[key_var+key_sample].GetXaxis().SetTitleSize(0.05)
            hists[key_var+key_sample].GetYaxis().SetTitleSize(0.05)
            hists[key_var+key_sample].GetYaxis().SetNdivisions(5,5,0)
            hists[key_var+key_sample].GetXaxis().SetNdivisions(5,5,0)
            hists[key_var+key_sample].GetXaxis().SetTitleOffset(0.95)
            hists[key_var+key_sample].GetZaxis().SetRangeUser(0,1e4)
            canvas[key_var+key_sample].SaveAs('Correlation__'+key_Xvar+'_'+key_var+'_'+key_sample+'.root')
            canvas[key_var+key_sample].SaveAs('Correlation__'+key_Xvar+'_'+key_var+'_'+key_sample+'.pdf')


