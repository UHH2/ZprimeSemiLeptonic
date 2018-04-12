#! /usr/bin/env python 
# Measure efficiency of electron ID on MC signal samples
# usage:
# cd /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming/
# python /nfs/dust/cms/user/karavdia/CMSSW_8_0_27/src/UHH2/ZprimeSemiLeptonic/macros/ElectronID_Eff.py 
from ROOT import *
import sys
import numpy
outputpath = '/afs/desy.de/user/k/karavdia/www/Zprime_plots/ElecIDeff_SignalMC_woFakeElectrons/'
#Set names of channels, hists, etc
samplelist = {'Zprime_01w_3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3000.root',
'Zprime_01w_5000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M5000.root',
'Zprime_01w_1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1500.root',
'Zprime_10w_3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3000.root',
'Zprime_10w_5000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M5000.root',
'Zprime_10w_1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1500.root',
'Zprime_TTJet_3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M3000.root',
'Zprime_TTJet_4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M4000.root',
'Zprime_TTJet_1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1500.root',
'RSGluon_3000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3000.root',
'RSGluon_5000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M5000.root',
'RSGluon_1500':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M1500.root',
}
#path = {'denomin': 'WITHOUTElecID_MET50_elecPt50_woEGReg_jetIDtight_slimmedMETs_JLCkey_20180410_JERhybridSFs/','nomin':'ElecID_CutBased_tight_MET50_elecPt50_woEGReg_jetIDtight_slimmedMETs_JLCkey_20180410_JERhybridSFs/'}
path = {'denomin': 'WITHOUTElecID_MET50_elecPt50_woEGReg_jetIDtight_slimmedMETs_JLCkey_20180410_JERhybridSFs_woFakeElectrons/','nomin':'ElecID_CutBased_tight_MET50_elecPt50_woEGReg_jetIDtight_slimmedMETs_JLCkey_20180410_JERhybridSFs_woFakeElectrons/'}
eff = {}
eff_err = {}

read_hist = {'elec_eta_pt':'ele1__eta__pt'}

#TH1
sig_denom = {}
sig_nomin = {}
sig_eff = {}
sig_eff_pl = {}
sig_eff_gr = {}
#sig_eff_mgr = {}

#TCanvas
cHLTeff = {} 
for key_hist in read_hist:
    for key_sample in samplelist:
        cHLTeff[key_hist+key_sample] = TCanvas("cHLT_SFs_"+key_hist,"HLT_SFs_"+key_hist,800,600)
        gStyle.SetOptStat(0)
        gStyle.SetOptTitle(0)
#        sig_eff_mgr[key_hist+key_sample] = TMultiGraph()
        myfile_eff = TFile(path['nomin']+'/'+samplelist[key_sample])
        myfile_denom = TFile(path['denomin']+'/'+samplelist[key_sample])
        key_hists_full = key_sample+'_'+key_hist
        sig_denom[key_hists_full] = myfile_denom.Get('lep_eff_sig/'+read_hist[key_hist]).Clone()
        sig_nomin[key_hists_full] = myfile_eff.Get('lep_eff_sig/'+read_hist[key_hist]).Clone()
        sig_eff_gr[key_hists_full] = sig_nomin[key_hists_full]
           
        sig_denom[key_hists_full].GetZaxis().SetRangeUser(0,1000)
        sig_denom[key_hists_full].Draw('colz')
        gPad.SetLogy();
        cHLTeff[key_hist+key_sample].SaveAs(outputpath+'/Yield_denom_'+key_hist+'_'+key_sample+'.pdf')
        
        sig_nomin[key_hists_full].GetZaxis().SetRangeUser(0,1000)
        sig_nomin[key_hists_full].Draw('colz')
        gPad.SetLogy();
        cHLTeff[key_hist+key_sample].SaveAs(outputpath+'/Yield_nomin_'+key_hist+'_'+key_sample+'.pdf')

        sig_eff_gr[key_hists_full].Divide(sig_denom[key_hists_full]) #calculate efficiency 
        # #loop over bins to fill empty once with 1
        # for i in range(1,sig_eff_gr[key_hists_full].GetNbinsX() + 1):
        #     for j in range(1,sig_eff_gr[key_hists_full].GetNbinsY() + 1):
        #         if sig_eff_gr[key_hists_full].GetBinContent(i,j)==0: 
        #             sig_eff_gr[key_hists_full].SetBinContent(i,j,1)
        #             sig_eff_gr[key_hists_full].SetBinError(i,j,0.0)

        sig_eff_gr[key_hists_full].Draw('colz TEXTE')
        sig_eff_gr[key_hists_full].GetZaxis().SetRangeUser(0,1.2)
        sig_eff_gr[key_hists_full].GetXaxis().SetRangeUser(0.,2.5)
        gPad.SetLogy();
        cHLTeff[key_hist+key_sample].SaveAs(outputpath+'/Eff_'+key_hist+'_'+key_sample+'.pdf')

