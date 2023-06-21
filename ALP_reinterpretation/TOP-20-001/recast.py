#!/usr/bin/env python2

import ROOT as root
import numpy as np
import math
import os

from constants import _HEPData, _SAMPLES, _YEARS

cwd = os.getcwd() + '/'
LUMI = _YEARS.get('Run2').get('lumi_pb')

outputfiles_dir_name = cwd
outputfiles_dir_name += 'output_datasyst_as_shape/' # output_datasyst_as_shape or output_datasyst_as_binerror
if not os.path.exists(outputfiles_dir_name):
    os.mkdir(outputfiles_dir_name)


# DATA
outputfile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.DATA.data_obs.root', 'RECREATE')
outputfile.Close()
print('Data')
for key_hist, hist in _HEPData.items():
    hep_name = hist.get('hep_name')
    file_name = hist.get('file_name')
    hist_name = hist.get('hist_name')
    mtt_bin_width = hist.get('mtt_bin_width')

    inputfile = root.TFile(file_name, 'READ')
    hist_data = inputfile.Get(hep_name + '/Hist1D_y1')
    hist_data_err_stat = inputfile.Get(hep_name + '/Hist1D_y1_e1')
    hist_data_err_syst = inputfile.Get(hep_name + '/Hist1D_y1_e2')

    # set bin error to stat. error
    for bin in range(1,hist_data.GetNbinsX()+1):
        data_err_stat = hist_data_err_stat.GetBinContent(bin)
        data_err_syst = hist_data_err_syst.GetBinContent(bin)
        data_err_total = math.sqrt(data_err_stat**2 + data_err_syst**2)
        hist_data.SetBinError(bin, data_err_stat) # choose stat. error only or total error
        hist_data_err_stat.SetBinError(bin, 0)
        hist_data_err_syst.SetBinError(bin, 0)

    # scale by bin width
    hists = [hist_data, hist_data_err_stat, hist_data_err_syst]
    histnames = [hist_name, hist_name + '_err_stat', hist_name + '_err_syst']
    for hist, histname in zip(hists, histnames):
        for bin in range(1,hist.GetNbinsX()+1):
            bin_content = hist.GetBinContent(bin)
            bin_error = hist.GetBinError(bin)
            bin_width = hist.GetXaxis().GetBinWidth(bin)
            hist.SetBinContent(bin, bin_content * bin_width)
            hist.SetBinError(bin, bin_error * bin_width)

        hist.Scale(LUMI)
        hist.Scale(mtt_bin_width)
        hist.SetName(histname)
        hist.GetYaxis().SetTitle('Nevents');
        outputfile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.DATA.data_obs.root', 'UPDATE')
        hist.Write()
        outputfile.Close()
inputfile.Close()

# MC
for key_sample, sample in _SAMPLES.items():
    sample_name = sample.get('name')
    xsec = sample.get('xsec')
    br = sample.get('br')
    nevt = sample.get('nevt')
    file_name = sample.get('file_name')
    print(sample_name)
    is_tttosemileptonic = True if sample_name == 'TTToSemiLeptonic' else False

    outputfile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.MC.' + sample_name + '.root', 'RECREATE')
    outputfile.Close()
    inputfile = root.TFile(file_name)
    for key_hist, hist in _HEPData.items():
        hep_name = hist.get('hep_name')
        file_name = hist.get('file_name')
        hist_name = hist.get('hist_name')
        mtt_bin_width = hist.get('mtt_bin_width')

        hist_nominal = inputfile.Get('ttgenhists/' + hist_name)
        hist_nominal.Scale(LUMI)
        hist_nominal.Scale(xsec * br / nevt)
        hist_nominal.GetYaxis().SetTitle('Nevents');

        # add Data stat. error to TTToSemiLeptonic MC stat. error
        if is_tttosemileptonic:
            for bin in range(1,hist_nominal.GetNbinsX()+1):
                bin_content = hist_nominal.GetBinContent(bin)
                bin_error = hist_nominal.GetBinError(bin)

                datafile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.DATA.data_obs.root', 'READ')
                hist_data = datafile.Get(hist_name)
                data_err_stat = hist_data.GetBinError(bin)
                bin_error = math.sqrt(bin_error**2 + data_err_stat**2)
                hist_nominal.SetBinError(bin, bin_error)
                datafile.Close()

        outputfile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.MC.' + sample_name + '.root', 'UPDATE')
        hist_nominal.Write()
        outputfile.Close()

        # create shape syst. uncert. on TTToSemiLeptonic from Data syst. error
        if is_tttosemileptonic:
            datafile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.DATA.data_obs.root', 'READ')
            hist_data_err_syst = datafile.Get(hist_name + '_err_syst')
            hist_datasyst_up = hist_nominal.Clone()
            hist_datasyst_down = hist_nominal.Clone()
            hist_datasyst_up.SetName(hist_name + '_datasyst_up')
            hist_datasyst_down.SetName(hist_name + '_datasyst_down')
            for bin in range(1,hist_nominal.GetNbinsX()+1):
                bin_content = hist_nominal.GetBinContent(bin)
                data_err_syst = hist_data_err_syst.GetBinContent(bin)
                hist_datasyst_up.SetBinContent(bin, bin_content + data_err_syst)
                hist_datasyst_down.SetBinContent(bin, bin_content - data_err_syst)
            outputfile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.MC.' + sample_name + '.root', 'UPDATE')
            hist_datasyst_up.Write()
            hist_datasyst_down.Write()
            outputfile.Close()
            datafile.Close()

        # handle other up/down systematics
        for syst in ['pu', 'isr', 'fsr']:
            hist_syst_up = inputfile.Get('SystematicsHists/' + hist_name + '_' + syst + '_up')
            hist_syst_down = inputfile.Get('SystematicsHists/' + hist_name + '_' + syst + '_down')
            for hist in [hist_syst_up, hist_syst_down]:
                hist.Scale(LUMI)
                hist.Scale(xsec * br / nevt)
                outputfile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.MC.' + sample_name + '.root', 'UPDATE')
                hist.Write()
                outputfile.Close()

        # mcscale: take envelope
        hist_mcscale_up = hist_nominal.Clone()
        hist_mcscale_down = hist_nominal.Clone()
        hist_mcscale_up.SetName(hist_name + '_mcscale_up')
        hist_mcscale_down.SetName(hist_name + '_mcscale_down')
        for bin in range(1,hist_nominal.GetNbinsX()+1):
            max_value = 0
            min_value = float('inf')
            for mcscale in ['murmuf_upup', 'murmuf_upnone', 'murmuf_noneup', 'murmuf_nonedown', 'murmuf_downnone', 'murmuf_downdown']:
                hist_mcscale = inputfile.Get('SystematicsHists/' + hist_name + '_' + mcscale)
                bin_content = hist_mcscale.GetBinContent(bin)
                bin_content *= LUMI
                bin_content *= xsec * br / nevt
                if bin_content > max_value:
                    max_value = bin_content
                if bin_content < min_value:
                    min_value = bin_content
            hist_mcscale_up.SetBinContent(bin, max_value)
            hist_mcscale_down.SetBinContent(bin, min_value)
        for hist in [hist_mcscale_up, hist_mcscale_down]:
            outputfile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.MC.' + sample_name + '.root', 'UPDATE')
            hist.Write()
            outputfile.Close()

        # pdf
        hist_pdf_nominal = hist_nominal.Clone()
        hist_pdf_up = hist_nominal.Clone()
        hist_pdf_down = hist_nominal.Clone()
        hist_pdf_up.SetName(hist_name + '_pdf_up')
        hist_pdf_down.SetName(hist_name + '_pdf_down')

        for bin in range(1,hist_nominal.GetNbinsX()+1):
            nominal = hist_pdf_nominal.GetBinContent(bin)
            sum = 0
            for i in range(1,101):
                hist_pdf = inputfile.Get('PDFHists/' + hist_name + '_PDF_' + str(i))
                bin_content = hist_pdf.GetBinContent(bin)
                bin_content *= LUMI
                bin_content *= xsec * br / nevt
                sum += (nominal - bin_content)**2
            rms = math.sqrt(sum/100)
            hist_pdf_up.SetBinContent(bin, nominal + rms)
            hist_pdf_down.SetBinContent(bin, nominal - rms)
        for hist in [hist_pdf_up, hist_pdf_down]:
            outputfile = root.TFile(outputfiles_dir_name + 'uhh2.AnalysisModuleRunner.MC.' + sample_name + '.root', 'UPDATE')
            hist.Write()
            outputfile.Close()

    inputfile.Close()
