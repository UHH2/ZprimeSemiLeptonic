#! /usr/bin/env python 
# Measure efficiency of electron trigger with tag&probe method
# tag: muon HLT, probe: electron HLT 
# compare results in MC and DATA, derive SFs
# usage:
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJTrigger/TTbarLJTriggerStudyLite_elePt40_jet1pt185_jet2pt50_20170922/
# python /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros/ElectronHLT_study.py
from ROOT import *
import sys
import numpy

#Set names of channels, hists, etc
#samplelist = {'TTbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root'}
#samplelist = {'DATA_Run2016':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016.root'}
samplelist = {'TTbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root','DATA_Run2016':'uhh2.AnalysisModuleRunner.DATA.DATA.root'}
#path = {'Ele50_PFJet165': 'Ele50_PFJet165__NULL__NULL__NULL__NULL__NULL/'}
path = {'Ele50PFJet165_OR_Ele115': 'Ele50_PFJet165__Ele115_CaloIdVT_GsfTrkIdT__NULL__NULL__NULL__NULL/'}
eff = {}
eff_err = {}

read_hist = {'elec_pt':'ele1__pt','jet1_pt':'jet1__pt','jet2_pt':'jet2__pt',}
name_hist = {'elec_pt':'electron p_{T}, GeV','jet1_pt':'jet1 p_{T}, GeV','jet2_pt':'jet2 p_{T}, GeV'}

# read_hist = {'elec_pt':'ele1__pt','elec_eta':'ele1__eta','jet1_pt':'jet1__pt','jet2_pt':'jet2__pt',}
# name_hist = {'elec_pt':'electron p_{T}, GeV','elec_eta':'electron #eta','jet1_pt':'jet1 p_{T}, GeV','jet2_pt':'jet2 p_{T}, GeV'}
# read_hist = {'elec_pt':'ele1__pt'}
# name_hist = {'elec_pt':'electron p_{T}, GeV'}
# read_hist = {'elec_eta':'ele1__eta'}
# name_hist = {'elec_eta':'electron #eta'}
# read_hist = {'jet1_pt':'jet1__pt','jet2_pt':'jet2__pt',}
# name_hist = {'jet1_pt':'jet1 p_{T}, GeV','jet2_pt':'jet2 p_{T}, GeV'}
# read_hist = {'muo_pt':'muo1__pt'}
# name_hist = {'muo_pt':'muon p_{T}, GeV'}

#TH1
sig_denom = {}
sig_eleID = {}
sig_eff = {}
sig_eff_pl = {}
sig_eff_gr = {}
sig_eff_mgr = {}

#TCanvas
cHLTeff = {} 
for key_hist in read_hist:
    #j = j+1 
    for key_sample in samplelist:
        cHLTeff[key_hist+key_sample] = TCanvas("cHLT_Eff_"+key_hist,"HLT_Eff_"+key_hist,800,600)
        legend = TLegend(.45,.85,.98,.95)
        #legend = TLegend(.64,.79,.99,.95)
        #legend = TLegend(.13,.15,.99,.41) 
        #legend = TLegend() 
        legend.SetTextSize(0.035)
        legend.SetTextFont(62)
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
        i = -7
        sig_eff_mgr[key_hist+key_sample] = TMultiGraph()
        for key_path in path:
            print "path = ",key_path
            i = i+1
            myfile_eff = TFile(path[key_path]+samplelist[key_sample])
            key_hists_full = key_sample+'_'+key_hist+'_'+key_path
            print "key_hists_full",key_hists_full
            sig_denom[key_hists_full] = myfile_eff.Get('tag/'+read_hist[key_hist]).Clone()
            sig_eleID[key_hists_full] = myfile_eff.Get('tagNprobe/'+read_hist[key_hist]).Clone()
            sig_eleID[key_hists_full].Print()
            #sig_eff[key_hists_full] = sig_eleID[key_hists_full].Clone()
            #sig_eff_gr[key_hists_full] = TGraphAsymmErrors(sig_denom[key_hists_full])
            sig_eff_gr[key_hists_full] = TGraphAsymmErrors()
            #sig_eff[key_hists_full].SetDefaultSumw2(False)
            #sig_eff[key_hists_full].Sumw2()
            # print "before: ", sig_eff[key_hists_full].GetBinContent(20)
            # print "before: ", sig_eff[key_hists_full].GetBinError(20)
            # print "before: ", sig_denom[key_hists_full].GetBinContent(20)
            # print "before: ", sig_denom[key_hists_full].GetBinError(20)
            #sig_eff[key_hists_full].Divide(sig_denom[key_hists_full])
            sig_eff_gr[key_hists_full].Divide(sig_eleID[key_hists_full],sig_denom[key_hists_full],"cl=0.95 b(1,1) mode")
            #sig_eff_gr[key_hists_full].BayesDivide(sig_eleID[key_hists_full],sig_denom[key_hists_full])
            #sig_eff_gr[key_hists_full].Print()
            #print "after: ", sig_eff[key_hists_full].GetBinContent(20)
            #print "after: ", sig_eff[key_hists_full].GetBinError(20)
            sig_eff_gr[key_hists_full].SetName(key_hists_full)
            sig_eff_gr[key_hists_full].SetMarkerStyle(27+i)
            sig_eff_gr[key_hists_full].SetMarkerSize(1.4)
            sig_eff_gr[key_hists_full].SetMarkerColor(kRed+i)
            sig_eff_gr[key_hists_full].GetXaxis().SetTitle(name_hist[key_hist])
            sig_eff_gr[key_hists_full].GetYaxis().SetTitle("#varepsilon")
            #sig_eff_gr[key_hists_full].GetYaxis().SetRangeUser(0.0,1.2)
            fitres = sig_eff_gr[key_hists_full].Fit('pol0','S','',50,900)
            #fitres = sig_eff_gr[key_hists_full].Fit('pol0','S','',200,900)
            #fitres = sig_eff_gr[key_hists_full].Fit('pol1','S0')
            ##eff[key_hists_full] = sig_eleID[key_hists_full].GetEntries()/ sig_denom[key_hists_full].GetEntries()
            eff[key_hists_full] = fitres.Value(0)
            eff_err[key_hists_full] = fitres.Error(0)
            sig_eff_mgr[key_hist+key_sample].Add(sig_eff_gr[key_hists_full])
            #print "i", i
            #sig_eff_gr[key_hists_full].DrawClone('aep')
            #sig_eff_gr[key_hists_full].SetDirectory(0)
            #if i<-5:
            #    sig_eff_gr[key_hists_full].DrawClone('ep')
            #else:
           #   sig_eff_gr[key_hists_full].DrawClone('same')
        #         sig_eff_pl[key_hists_full] = sig_eff_gr[key_hists_full].DrawClone('ep')
        #         #sig_eff_pl[key_hists_full].SetDirectory(0)
        #     else: 
        #         sig_eff_pl[key_hists_full] = sig_eff_gr[key_hists_full].DrawClone('same')
        #         #sig_eff_pl[key_hists_full].SetDirectory(0)
            eff_str = "%.3f" % eff[key_hists_full]
            eff_err_str = "%.3f" % eff_err[key_hists_full]
            legend.AddEntry(sig_eff_gr[key_hists_full],key_path+", #bar{#varepsilon} = "+eff_str+" #pm "+eff_err_str,"p")
        
        sig_eff_mgr[key_hist+key_sample].Draw('ap')
        sig_eff_mgr[key_hist+key_sample].GetYaxis().SetRangeUser(0.0,1.1)
        sig_eff_mgr[key_hist+key_sample].GetYaxis().SetTitle("#varepsilon")
        sig_eff_mgr[key_hist+key_sample].GetXaxis().SetTitle(name_hist[key_hist])
        legend.Draw()
        cHLTeff[key_hist+key_sample].SaveAs('HLT_Eff_'+key_hist+'_'+key_sample+'.root')
        cHLTeff[key_hist+key_sample].SaveAs('/afs/desy.de/user/k/karavdia/www/Zprime_plots/ElecHLTeff_jetCut_MET120_vetoGapEle_HLT1ORHLT2/HLT_Eff_'+key_hist+'_'+key_sample+'.pdf')
