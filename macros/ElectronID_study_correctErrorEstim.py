#! /usr/bin/env python compare signal and background efficiencies for
# different electron IDs cd
# /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming/ElecID_efficiency/
# cd
# /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming/ElecID_efficiency_BetterPlots
# python /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros/ElectronID_study_correctErrorEstim.py
from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy

#Set names of channels, hists, etc
#samplelist = {'RSGluon_M0500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M0500.root','RSGluon_M0750':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M0750.root','RSGluon_M1000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1000.root','RSGluon_M1250':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1250.root','RSGluon_M1500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1500.root','RSGluon_M2000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M2000.root','RSGluon_M2500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M2500.root','RSGluon_M3000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3000.root','RSGluon_M3500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3500.root','RSGluon_M4000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M4000.root'}
#samplelist = {'RSGluon_M0500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M0500.root','RSGluon_M0750':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M0750.root','RSGluon_M1000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1000.root','RSGluon_M1500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1500.root','RSGluon_M2000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M2000.root','RSGluon_M2500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M2500.root','RSGluon_M3000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3000.root','RSGluon_M3500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3500.root','RSGluon_M4000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M4000.root'}
#samplelist = {'RSGluon_M0500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M0500.root','RSGluon_M3500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3500.root','RSGluon_M4000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M4000.root'}
#samplelist = {'RSGluon_M0500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M0500.root'}
#samplelist = {'RSGluon_M3000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3000.root'}
#samplelist = {'ZprimeToTTJet_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M4000.root'}
#samplelist = {'ZprimeToTTJet_M0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M0750.root','ZprimeToTTJet_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1000.root','ZprimeToTTJet_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1250.root','ZprimeToTTJet_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1500.root','ZprimeToTTJet_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M2000.root','ZprimeToTTJet_M2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M2500.root','ZprimeToTTJet_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M3000.root','ZprimeToTTJet_M3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M3500.root','ZprimeToTTJet_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M4000.root'}
#samplelist = {'ZprimeToTTJet_M0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M0750.root','ZprimeToTTJet_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1000.root','ZprimeToTTJet_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1250.root','ZprimeToTTJet_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1500.root','ZprimeToTTJet_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M3000.root','ZprimeToTTJet_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M4000.root'}

#samplelist = {'ZprimeToTT_01w_M0500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M0500.root','ZprimeToTT_01w_M0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M0750.root','ZprimeToTT_01w_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1000.root','ZprimeToTT_01w_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1250.root','ZprimeToTT_01w_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1500.root','ZprimeToTT_01w_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M2000.root','ZprimeToTT_01w_M2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M2500.root','ZprimeToTT_01w_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3000.root','ZprimeToTT_01w_M3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3500.root','ZprimeToTT_01w_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M4000.root','ZprimeToTT_10w_M0500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M0500.root','ZprimeToTT_10w_M0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M0750.root','ZprimeToTT_10w_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1000.root','ZprimeToTT_10w_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1250.root','ZprimeToTT_10w_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1500.root','ZprimeToTT_10w_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M2000.root','ZprimeToTT_10w_M2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M2500.root','ZprimeToTT_10w_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3000.root','ZprimeToTT_10w_M3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3500.root','ZprimeToTT_10w_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M4000.root'}
#samplelist = {'ZprimeToTT_01w_M0500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M0500.root','ZprimeToTT_01w_M0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M0750.root','ZprimeToTT_01w_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1000.root','ZprimeToTT_01w_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1250.root','ZprimeToTT_01w_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1500.root','ZprimeToTT_01w_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M2000.root','ZprimeToTT_01w_M2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M2500.root','ZprimeToTT_01w_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3000.root','ZprimeToTT_01w_M3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3500.root','ZprimeToTT_01w_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M4000.root','ZprimeToTT_10w_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1250.root','ZprimeToTT_10w_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1500.root','ZprimeToTT_10w_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M2000.root','ZprimeToTT_10w_M2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M2500.root','ZprimeToTT_10w_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3000.root','ZprimeToTT_10w_M3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3500.root','ZprimeToTT_10w_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M4000.root'}
#samplelist = {'ZprimeToTT_30w_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M1000.root','ZprimeToTT_30w_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M2000.root','ZprimeToTT_30w_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M3000.root','ZprimeToTT_30w_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M4000.root'}
samplelist = {'QCD':'uhh2.AnalysisModuleRunner.MC.QCD.root','GJets':'uhh2.AnalysisModuleRunner.MC.GJets.root','QCDGJets':'uhh2.AnalysisModuleRunner.MC.QCDGJets.root'}
#samplelist = {'QCD':'uhh2.AnalysisModuleRunner.MC.QCD.root'}
#samplelist = {'GJets':'uhh2.AnalysisModuleRunner.MC.GJets.root'}
#samplelist = {'QCDGJets':'uhh2.AnalysisModuleRunner.MC.QCDGJets.root'}
path = {'CutBased medium':'v06/', 'CutBased loose noIso':'v05/', 'CutBased tight noIso':'v04/', 'MVA tight':'v03/', 'MVA loose': 'v02/'} #'No_ElecID':'v07/'
#path = {'MVA loose':'v02/', 'MVA loose+2D (0.2,20)':'v021/2/20/', 'MVA loose+2D (0.2,40)':'v021/2/40/', 'MVA loose+2D (0.2,60)':'v021/2/60/', 'MVA loose+2D (0.4,20)':'v021/4/20/', 'MVA loose+2D (0.4,40)':'v021/4/40/', 'MVA loose+2D (0.4,60)':'v021/4/60/'} #'No_ElecID':'v07/'
eff = {}
eff_ave = {}
eff_err = {}

#eff = []
#path = {'CutBased medium noIso':'v06/', 'CutBased medium noIso+2D (0.4,20)':'v061/4/20/'} #'No_ElecID':'v07/'
#path = {'CutBased medium noIso':'v06/', 'CutBased loose noIso':'v05/', 'CutBased tight noIso':'v04/'} #'No_ElecID':'v07/'
#path = {'CutBased tight noIso':'v04/'} #'No_ElecID':'v07/'
#path = {'ElecID_MVA_loose': 'v07/'}
#path = {'ElecID_CutBased_medium_noIso':'v07/', 'No_ElecID':'v07/'}
#read_hist = {'sig_lep_pt':'lep_eff_sig/ele1__pt','sig_lep_eta':'lep_eff_sig/ele1__eta','sig_met':'lep_eff_sig/met__pt','bkg_lep_pt':'lep_eff_bkg/ele1__pt','bkg_lep_eta':'lep_eff_bkg/ele1__eta','bkg_met':'lep_eff_bkg/met__pt',}
#name_hist = {'sig_lep_pt':'electron p_{T}, GeV','sig_lep_eta':'electron #eta','sig_met':'MET GeV','bkg_lep_pt':'electron p_{T}, GeV','bkg_lep_eta':'electron #eta','bkg_met':'MET GeV'}
#read_hist = {'sig_lep_pt':'lep_eff_sig/ele1__pt','sig_lep_eta':'lep_eff_sig/ele1__eta','sig_jet1_pt':'lep_eff_sig/jet1__pt','sig_jet1_eta':'lep_eff_sig/jet1__eta'}
#name_hist = {'sig_lep_pt':'electron p_{T}, GeV','sig_lep_eta':'electron #eta','sig_jet1_pt':'jet1 p_{T}, GeV','sig_jet1_eta':'jet1 #eta'}
read_hist = {'bkg_lep_pt':'lep_eff_bkg/ele1__pt','bkg_lep_eta':'lep_eff_bkg/ele1__eta'}
name_hist = {'bkg_lep_pt':'electron p_{T}, GeV','bkg_lep_eta':'electron #eta'}
#read_hist = {'sig_lep_pt':'lep_eff_sig/ele1__pt'}
#name_hist = {'sig_lep_pt':'electron p_{T}, GeV'}
#read_hist = {'sig_lep_eta':'lep_eff_sig/ele1__eta'}
#name_hist = {'sig_lep_eta':'electron #eta'}
#read_hist = {'sig_jet1_pt':'lep_eff_sig/jet1__pt'}
#name_hist = {'sig_jet1_pt':'jet1 p_{T}, GeV'}
#TH1
sig_denom = {}
sig_eleID = {}
sig_eff = {}
sig_eff_mgr = {}
#sig_eff = []
sig_eff_pl = {}
#sig_eff_pl = []

#TCanvas
cSigEff_Sig = {} 
#TCanvas("c1","ElectronID_SigEff_Sig",800,600)
#output = TFile('EleID_Eff_Plots.root', 'RECREATE')
#j = 0
for key_hist in read_hist:
    #j = j+1 
    for key_sample in samplelist:
        cSigEff_Sig[key_hist+key_sample] = TCanvas("cElectronID_Eff_"+key_hist,"ElectronID_Eff_"+key_hist,800,600)
        #cSigEff_Sig[key_hist+key_sample] = TCanvas("cTwoDcut_Eff_"+key_hist,"TwoDcut_Eff_"+key_hist,800,600)
        legend = TLegend(.64,.49,.99,.95) 
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
        i = -7
        sig_eff_mgr[key_hist+key_sample] = TMultiGraph()
        for key_path in path:
            print "path = ",key_path
            i = i+1
            #myfile_denom = TFile(path['No_ElecID']+samplelist[key_sample])
            myfile_denom = TFile('v07/'+samplelist[key_sample])
            myfile_eff = TFile(path[key_path]+samplelist[key_sample])
            key_hists_full = key_sample+'_'+key_hist+'_'+key_path
            print "key_hists_full",key_hists_full
            sig_denom[key_hists_full] = myfile_denom.Get(read_hist[key_hist]).Clone()
            sig_eleID[key_hists_full] = myfile_eff.Get(read_hist[key_hist]).Clone()
            sig_eff[key_hists_full] = TGraphAsymmErrors()
            sig_eff[key_hists_full].Divide(sig_eleID[key_hists_full],sig_denom[key_hists_full],"cl=0.95 b(1,1) mode")
            sig_eff[key_hists_full].SetName(key_hists_full)
            sig_eff[key_hists_full].SetMarkerStyle(27+i)
            sig_eff[key_hists_full].SetMarkerSize(1.4)
            sig_eff[key_hists_full].SetMarkerColor(kRed+i)
            sig_eff[key_hists_full].GetXaxis().SetTitle(name_hist[key_hist])
            sig_eff[key_hists_full].GetYaxis().SetTitle("#varepsilon_{SIG}")
            sig_denom[key_hists_full].Print()
            eff[key_hists_full] = sig_eleID[key_hists_full].GetEntries()/ sig_denom[key_hists_full].GetEntries()
            #fitres = sig_eff[key_hists_full].Fit('pol1','S0')
            #eff[key_hists_full] = fitres.Value(0)
            #eff_err[key_hists_full] = fitres.Error(0)
            sig_eff_mgr[key_hist+key_sample].Add(sig_eff[key_hists_full])
            eff_str = "%.2f " % eff[key_hists_full]
            #eff_err_str = "%.2f " % eff_err[key_hists_full]
            #legend.AddEntry(sig_eff[key_hists_full],key_path+", #bar{#varepsilon} = "+eff_str+" #pm "+eff_err_str,"lp")
            legend.AddEntry(sig_eff[key_hists_full],key_path+", #bar{#varepsilon} = "+eff_str,"lp")
        sig_eff_mgr[key_hist+key_sample].Draw('ap')
        #sig_eff_mgr[key_hist+key_sample].GetYaxis().SetRangeUser(0.0,1.2)
        sig_eff_mgr[key_hist+key_sample].GetYaxis().SetRangeUser(0.0,0.5)
        sig_eff_mgr[key_hist+key_sample].GetYaxis().SetTitle("#varepsilon")
        sig_eff_mgr[key_hist+key_sample].GetXaxis().SetTitle(name_hist[key_hist])
        legend.Draw()
        #cSigEff_Sig[key_hist+key_sample].SaveAs('TwoDcut_Eff_'+key_hist+'_'+key_sample+'.root')
        #cSigEff_Sig[key_hist+key_sample].SaveAs('/afs/desy.de/user/k/karavdia/www/Zprime_plots/ElecIDeff/TwoDcut_Eff_'+key_hist+'_'+key_sample+'.pdf')
        cSigEff_Sig[key_hist+key_sample].SaveAs('EleID_Eff_'+key_hist+'_'+key_sample+'.root')
        cSigEff_Sig[key_hist+key_sample].SaveAs('/afs/desy.de/user/k/karavdia/www/Zprime_plots/ElecIDeff/EleID_Eff_'+key_hist+'_'+key_sample+'.pdf')
