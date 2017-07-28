#! /usr/bin/env python compare signal and background efficiencies for different 2D cuts and draw ROC curve
# /nfs/dust/cms/user/karavdia/ttbar_semilep_13TeV/RunII_80X_v3/ttbarLJSkimming/ElecID_efficiency_AddQCD_MET50_Rebin
# python /afs/desy.de/user/k/karavdia/xxl/af-cms/CMSSW_8_0_24_patch1/src/UHH2/ZprimeSemiLeptonic/macros/TwoD_study.py
from ROOT import *
#TH1.DrawClone._creates = False
import sys
import numpy

#Set names of channels, hists, etc
#samplelist = {'RSGluon_M3000':'uhh2.AnalysisModuleRunner.MC.RSGluonToTT_M3000.root'}
#samplelist = {'ZprimeToTTJet_M0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M0750.root','ZprimeToTTJet_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1000.root','ZprimeToTTJet_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1250.root','ZprimeToTTJet_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M1500.root','ZprimeToTTJet_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M2000.root','ZprimeToTTJet_M2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M2500.root','ZprimeToTTJet_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M3000.root','ZprimeToTTJet_M3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M3500.root','ZprimeToTTJet_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTTJet_M4000.root'}
#samplelist = {'ZprimeToTT_01w_M0500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M0500.root','ZprimeToTT_01w_M0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M0750.root','ZprimeToTT_01w_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1000.root','ZprimeToTT_01w_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1250.root','ZprimeToTT_01w_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M1500.root','ZprimeToTT_01w_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M2000.root','ZprimeToTT_01w_M2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M2500.root','ZprimeToTT_01w_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3000.root','ZprimeToTT_01w_M3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M3500.root','ZprimeToTT_01w_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_01w_M4000.root','ZprimeToTT_10w_M0500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M0500.root','ZprimeToTT_10w_M0750':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M0750.root','ZprimeToTT_10w_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1000.root','ZprimeToTT_10w_M1250':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1250.root','ZprimeToTT_10w_M1500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M1500.root','ZprimeToTT_10w_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M2000.root','ZprimeToTT_10w_M2500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M2500.root','ZprimeToTT_10w_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3000.root','ZprimeToTT_10w_M3500':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M3500.root','ZprimeToTT_10w_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_10w_M4000.root'}
#samplelist = {'ZprimeToTT_30w_M1000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M1000.root','ZprimeToTT_30w_M2000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M2000.root','ZprimeToTT_30w_M3000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M3000.root','ZprimeToTT_30w_M4000':'uhh2.AnalysisModuleRunner.MC.ZprimeToTT_30w_M4000.root'}
#samplelist = {'QCD':'uhh2.AnalysisModuleRunner.MC.QCD.root','GJets':'uhh2.AnalysisModuleRunner.MC.GJets.root'}
path = {'CutBased medium noIso':'v06/', 'CutBased loose noIso':'v05/', 'CutBased tight noIso':'v04/', 'MVA tight':'v03/', 'MVA loose': 'v02/'} #'No_ElecID':'v07/'
#read_hist = {'sig_lep_pt':'lep_eff_sig/ele1__pt','sig_lep_eta':'lep_eff_sig/ele1__eta','sig_jet1_pt':'lep_eff_sig/jet1__pt','sig_jet1_eta':'lep_eff_sig/jet1__eta'}
#name_hist = {'sig_lep_pt':'electron p_{T}, GeV','sig_lep_eta':'electron #eta','sig_jet1_pt':'jet1 p_{T}, GeV','sig_jet1_eta':'jet1 #eta'}
#read_hist = {'bkg_lep_pt':'lep_eff_bkg/ele1__pt','bkg_lep_eta':'lep_eff_bkg/ele1__eta'}
#name_hist = {'bkg_lep_pt':'electron p_{T}, GeV','bkg_lep_eta':'electron #eta'}
#read_hist = {'sig_lep_pt':'lep_eff_sig/ele1__pt'}
#name_hist = {'sig_lep_pt':'electron p_{T}, GeV'}
#read_hist = {'sig_lep_eta':'lep_eff_sig/ele1__eta'}
#name_hist = {'sig_lep_eta':'electron #eta'}
#read_hist = {'jet1_pt':'lep_eff_sig/jet1__pt'}
#name_hist = {'jet1_pt':'jet1 p_{T}, GeV'}
#TH1
sig_denom = {}
sig_eleID = {}
sig_eff = {}
#sig_eff = []
sig_eff_pl = {}
#sig_eff_pl = []

#TCanvas
cSigEff_Sig = {} 
#for key_hist in read_hist:
for key_sample in samplelist:
    cSigEff_Sig[key_sample] = TCanvas("c_2D_Eff_"+key_sample,"2D_Eff"+key_sample,800,600)
    legend = TLegend(.74,.69,.99,.95) 
    gStyle.SetOptStat(0)
    gStyle.SetOptTitle(0)
    #i = -7
    for key_path in path:
        #i = i+1
        #myfile_denom = TFile(path['No_ElecID']+samplelist[key_sample])
        myfile_denom = TFile('v07/'+samplelist[key_sample])
        myfile_eff = TFile(path[key_path]+samplelist[key_sample])
        key_hists_full = key_sample+'_'+'_'+key_path
        print "key_hists_full",key_hists_full
        sig_denom[key_hists_full] = myfile_denom.Get('lep_eff_sig/ele1__pt').Clone()
        sig_eleID[key_hists_full] = myfile_eff.Get('lep_eff_sig/ele1__pt').Clone()

        #print " denom:", sig_denom[key_hists_full].Print()
        #print " eff:", sig_eleID[key_hists_full].Print()
        #sig_eff[key_hists_full] = new TH1()
        #sig_eleID[key_hists_full].Copy(sig_eff[key_hists_full])
        #sig_eff.append(sig_eleID[key_hists_full].Clone())
        sig_eff[key_hists_full] = sig_eleID[key_hists_full].Clone()
        #sig_eleID[key_hists_full].Copy(sig_eff[key_hists_full])
        sig_eff[key_hists_full].Divide(sig_denom[key_hists_full])
        sig_eff[key_hists_full].SetName(key_hists_full)
        sig_eff[key_hists_full].SetMarkerStyle(27+i)
        sig_eff[key_hists_full].SetMarkerSize(1.4)
        sig_eff[key_hists_full].SetMarkerColor(kRed+i)
        sig_eff[key_hists_full].GetXaxis().SetTitle(name_hist[key_hist])
        #            sig_eff[key_hists_full].GetYaxis().SetTitle("Efficiency")
        sig_eff[key_hists_full].GetYaxis().SetTitle("#varepsilon_{SIG}")
        # sig_eff[key_hists_full].GetYaxis().SetTitle("#varepsilon_{BKG}")
        sig_eff[key_hists_full].GetYaxis().SetRangeUser(0.2,1.2)
        # sig_eff[key_hists_full].GetYaxis().SetRangeUser(0.0,0.5)
        #print "sig_eleID: ", sig_eleID
        #print "sig_eff: ", sig_eff
        # print "i", i
        if i<-5:
            sig_eff_pl[key_hists_full] = sig_eff[key_hists_full].DrawClone('ep')
            #sig_eff_pl.append(sig_eff[key_hists_full].DrawClone("ap"))
            sig_eff_pl[key_hists_full].SetDirectory(0)
        else: 
            sig_eff_pl[key_hists_full] = sig_eff[key_hists_full].DrawClone('same')
            sig_eff_pl[key_hists_full].SetDirectory(0)
            legend.AddEntry(sig_eff_pl[key_hists_full],key_path,"lp")
            #sig_eff_pl.append(sig_eff[key_hists_full].DrawClone("same"))
            # # #cSigEff_Sig[key_hist].Update()
            # #sig_eff_pl[key_hists_full].Print()
            # print "sig_eff_pl:  ", sig_eff_pl
            legend.Draw()
            cSigEff_Sig[key_hist+key_sample].SaveAs('EleID_Eff_'+key_hist+'_'+key_sample+'.root')
            cSigEff_Sig[key_hist+key_sample].SaveAs('/afs/desy.de/user/k/karavdia/www/Zprime_plots/ElecIDeff/EleID_Eff_'+key_hist+'_'+key_sample+'.pdf')
            #output.Write()
            
            
            # from ROOT import TCanvas, TH1I, TF1
            # f = TF1("line", "[0]*x + [1]", 0, 2000)
            # f.SetParameters( 200, 0 )
            # temp_0 = f.DrawClone("l")
            # g = TF1("line2", "[0]*x + [1]", 0, 2000)
            # g.SetParameters( 220, 0 )
            # temp_1 = g.DrawClone("l same")
            # g.SetParameters( 250, 0 )
            # temp_2 = g.DrawClone("l same")
            
            #cSigEff_Sig.SaveAs("EleID_SigEff_Sig.root")
