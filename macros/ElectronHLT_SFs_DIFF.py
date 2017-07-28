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
filelist = {'ALL':'SFs_elec_eta_pt_DATA_Run2016_Ele50_PFJet165__NULL__NULL__NULL__NULL__NULL.root', 'BCD':'SFs_elec_eta_pt_DATA_Run2016BCD_Ele50_PFJet165__NULL__NULL__NULL__NULL__NULL.root','EF':'SFs_elec_eta_pt_DATA_Run2016EF_Ele50_PFJet165__NULL__NULL__NULL__NULL__NULL.root','G':'SFs_elec_eta_pt_DATA_Run2016G_Ele50_PFJet165__NULL__NULL__NULL__NULL__NULL.root','H':'SFs_elec_eta_pt_DATA_Run2016H_Ele50_PFJet165__NULL__NULL__NULL__NULL__NULL.root'}


diff_SFs = {}



#TCanvas
cHLTeff = {} 
for key_file in filelist:
    myfile_ALL = TFile(filelist['ALL'])
    myfile_run = TFile(filelist[key_file])
    RefSFs = myfile_ALL.Get('EGamma_SF2D')
    diff_SFs[key_file] = myfile_run.Get('EGamma_SF2D')
    diff_SFs[key_file].Add(RefSFs,-1)
    diff_SFs[key_file].GetZaxis().SetRangeUser(-0.3,0.3)
    cHLTeff[key_file] = TCanvas("cHLT_SFs_diff"+key_file,"HLT_dif_SFs_"+key_file,800,600)
    gStyle.SetOptStat(0)
    gStyle.SetOptTitle(0)
    diff_SFs[key_file].Draw('colz')
    cHLTeff[key_file].SaveAs('/afs/desy.de/user/k/karavdia/www/Zprime_plots/ElecHLTeff/SFs_DIFF_'+key_file+'_.pdf')
