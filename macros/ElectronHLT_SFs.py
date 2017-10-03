#! /usr/bin/env python 
# Measure efficiency of electron trigger with tag&probe method
# tag: muon HLT, probe: electron HLT 
# compare results in MC and DATA, derive SFs
# usage:
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJTrigger/ElectronID_MVAGeneralPurpose_Spring16_loose/
# python /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros/ElectronHLT_SFs.py
from ROOT import *
import sys
import numpy

#Set names of channels, hists, etc
samplelist = {'DATA_Run2016':'uhh2.AnalysisModuleRunner.DATA.DATA.root','TTbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root'}
#samplelist = {'DATA_Run2016':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016.root','DATA_Run2016BCD':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016BCD.root','DATA_Run2016EF':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016EF.root','DATA_Run2016G':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016G.root','DATA_Run2016H':'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run2016H.root','TTbar':'uhh2.AnalysisModuleRunner.MC.TTbar.root'}
#path = {'Ele50_PFJet165 || Ele115/105': 'Ele50_PFJet165__Ele115_CaloIdVT_GsfTrkIdT__Ele105_CaloIdVT_GsfTrkIdT__NULL__NULL__NULL/'}
path = {'Ele50_PFJet165': 'Ele50_PFJet165__NULL__NULL__NULL__NULL__NULL'}
#path = {'Ele50PFJet165_OR_Ele115': 'Ele50_PFJet165__Ele115_CaloIdVT_GsfTrkIdT__NULL__NULL__NULL__NULL/'} 
eff = {}
eff_err = {}

#read_hist = {'elec_pt':'ele1__pt','elec_eta':'ele1__eta','jet1_pt':'jet1__pt','jet2_pt':'jet2__pt',}
#name_hist = {'elec_pt':'electron p_{T}, GeV','elec_eta':'electron #eta','jet1_pt':'jet1 p_{T}, GeV','jet2_pt':'jet2 p_{T}, GeV'}
#read_hist = {'elec_pt':'ele1__pt'}
#name_hist = {'elec_pt':'electron p_{T}, GeV'}
#read_hist = {'elec_eta':'ele1__eta'}
#name_hist = {'elec_eta':'electron #eta'}
#read_hist = {'jet1_pt':'jet1__pt','jet2_pt':'jet2__pt',}
#name_hist = {'jet1_pt':'jet1 p_{T}, GeV','jet2_pt':'jet2 p_{T}, GeV'}
#read_hist = {'muo_pt':'muo1__pt'}
#name_hist = {'muo_pt':'muon p_{T}, GeV'}

read_hist = {'elec_eta_pt':'ele1__eta__pt'}
#name_hist = {'elec_eta_pt':'electron p_{T}, GeV'}

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
        cHLTeff[key_hist+key_sample] = TCanvas("cHLT_SFs_"+key_hist,"HLT_SFs_"+key_hist,800,600)
        #legend = TLegend(.48,.85,.98,.95)
        #legend.SetTextSize(0.025)
        #legend.SetTextFont(62)
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
        #gStyle.SetPalette(100)
        i = -7
        sig_eff_mgr[key_hist+key_sample] = TMultiGraph()
        for key_path in path:
            print "path = ",key_path
            i = i+1
            myfile_eff = TFile(path[key_path]+'/'+samplelist[key_sample])
            myfile_ttbar = TFile(path[key_path]+'/'+samplelist['TTbar'])
            key_hists_full = key_sample+'_'+key_hist+'_'+key_path
            key_TTbar_hists_full = 'TTbar_'+key_hist+'_'+key_path
            print "key_hists_full",key_hists_full
            sig_denom[key_hists_full] = myfile_eff.Get('tag/'+read_hist[key_hist]).Clone()
            sig_eleID[key_hists_full] = myfile_eff.Get('tagNprobe/'+read_hist[key_hist]).Clone()
            #sig_eff_gr[key_hists_full] = TGraphAsymmErrors()
            #sig_eff_gr[key_hists_full].Divide(sig_eleID[key_hists_full],sig_denom[key_hists_full],"cl=0.68 b(1,1) mode") #calculate efficiency
            sig_eff_gr[key_hists_full] = sig_eleID[key_hists_full]
            sig_eff_gr[key_hists_full].Divide(sig_denom[key_hists_full])

            sig_denom[key_TTbar_hists_full] = myfile_ttbar.Get('tag/'+read_hist[key_hist]).Clone()
            sig_eleID[key_TTbar_hists_full] = myfile_ttbar.Get('tagNprobe/'+read_hist[key_hist]).Clone()
            sig_eff_gr[key_TTbar_hists_full] = sig_eleID[key_TTbar_hists_full]
            sig_eff_gr[key_TTbar_hists_full].Divide(sig_denom[key_TTbar_hists_full]) #calculate efficiency in TTbar
            sig_eff_gr[key_hists_full].Divide(sig_eff_gr[key_TTbar_hists_full]) #calculate SF #comment this line to get 2D efficiency plots
            #loop over bins to fill empty once with 1
            for i in range(1,sig_eff_gr[key_hists_full].GetNbinsX() + 1):
                for j in range(1,sig_eff_gr[key_hists_full].GetNbinsY() + 1):
                    #sig_eff_gr[key_hists_full].SetBinContent(i,j,0.94/0.962)
                    if sig_eff_gr[key_hists_full].GetBinContent(i,j)==0: 
                        sig_eff_gr[key_hists_full].SetBinContent(i,j,1)
            sig_eff_gr[key_hists_full].SetName('EGamma_SF2D')
            #sig_eff_gr[key_hists_full].SetMarkerStyle(27+i)
            #sig_eff_gr[key_hists_full].SetMarkerSize(1.4)
            #sig_eff_gr[key_hists_full].SetMarkerColor(kRed+i)
            #sig_eff_gr[key_hists_full].GetXaxis().SetTitle(name_hist[key_hist])
            #sig_eff_gr[key_hists_full].GetYaxis().SetTitle("#varepsilon")
            sig_eff_gr[key_hists_full].GetXaxis().SetTitle('electron #eta')
            sig_eff_gr[key_hists_full].GetYaxis().SetTitle('electron p_{T}, GeV')
            #sig_eff_gr[key_hists_full].GetYaxis().SetRangeUser(0.0,1.2)
            #fitres = sig_eff_gr[key_hists_full].Fit('pol0','S','',100,800)
            #fitres = sig_eff_gr[key_hists_full].Fit('pol0','S','',200,1200)
            #fitres = sig_eff_gr[key_hists_full].Fit('pol1','S0')
            ##eff[key_hists_full] = sig_eleID[key_hists_full].GetEntries()/ sig_denom[key_hists_full].GetEntries()
            #eff[key_hists_full] = fitres.Value(0)
            #eff_err[key_hists_full] = fitres.Error(0)
            #sig_eff_mgr[key_hist+key_sample].Add(sig_eff_gr[key_hists_full])
            #eff_str = "%.3f" % eff[key_hists_full]
            #eff_err_str = "%.3f" % eff_err[key_hists_full]
            #legend.AddEntry(sig_eff_gr[key_hists_full],key_path+", #bar{#varepsilon} = "+eff_str+"#pm"+eff_err_str,"p")

            sig_eff_gr[key_hists_full].Draw('colz TEXT')
            sig_eff_gr[key_hists_full].GetZaxis().SetRangeUser(0.5,1.6)
            sig_eff_gr[key_hists_full].GetXaxis().SetRangeUser(0.,2.5)
            gPad.SetLogy();
            #cHLTeff[key_hist+key_sample].SaveAs('SFs_'+key_hist+'_'+key_sample+'.root')
#            cHLTeff[key_hist+key_sample].SaveAs('/afs/desy.de/user/k/karavdia/www/Zprime_plots/ElecHLTeff_jetCut_MET120_vetoGapEle_HLT1ORHLT2/SFs_'+key_hist+'_'+key_sample+'.pdf')
            cHLTeff[key_hist+key_sample].SaveAs('/afs/desy.de/user/k/karavdia/www/Zprime_plots/ElecHLTeff_jetCut_MET120_vetoGapEle/SFs_'+key_hist+'_'+key_sample+'.pdf')
            f = TFile('SFs_'+key_hist+'_'+key_sample+'_'+key_path+'.root', 'recreate')
            sig_eff_gr[key_hists_full].Write()
            f.Write()

#  LocalWords:  Sig
