#!/usr/bin/env python2

import sys
sys.argv.append('-b') # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS
from constants_combine_input import _REGIONS
from constants_combine_input import _HISTNAME


years = [
    'UL16preVFP',
    'UL16postVFP',
    'UL17',
    'UL18',
]
channels = [
    'electron',
    'muon',
]

hist_name = _HISTNAME + '_'

for year in years:
    print("year: " + year)

    systematics = [
    'pdf',
    'mcscale',
    'pu',
    'prefiring',
    'mu_id',
    'mu_iso',
    'mu_reco',
    'mu_trigger',
    'ele_id',
    'ele_reco',
    'ele_trigger',
    'btag_cferr1',
    'btag_cferr2',
    'btag_hf',
    'btag_hfstats1_' + year,
    'btag_hfstats2_' + year,
    'btag_lf',
    'btag_lfstats1_' + year,
    'btag_lfstats2_' + year,
    'ttag_corr',
    'ttag_uncorr_' + year,
    'tmistag',
    'jec',
    'jer',
    # 'isr',
    # 'fsr',
    ]

    for channel in channels:
        print("channel: " + channel)
        # for region in regions:
        for key, var in _REGIONS.items():
            region = var.get('name')

            print("region: " + region)

            # SM processes
            processes_Plotter = [
                Process(hist_name + region + '_TTbar', 't#bar{t}', root.kPink-3, 1., 0.2),
                Process(hist_name + region + '_WJets', 'W+jets', root.kSpring-3, 1., 0.5),
                Process(hist_name + region + '_ST', 'Single t', root.kBlue, 1., 0.3),
                Process(hist_name + region + '_others', 'Drell-Yan #plus Diboson #plus QCD', root.kOrange, 1., 0.5),
            ]
            processes_Plotter_temp = OrderedDict()
            for index, p in enumerate(processes_Plotter):
                p.index = index
                processes_Plotter_temp[p.name] = p
                processes_Plotter = processes_Plotter_temp

            # signal
            signals_Plotter = [
                Process(hist_name + region + '_ALP_ttbar_signal', 'ALP signal', root.kBlack, 1),
                Process(hist_name + region + '_ALP_ttbar_interference', 'ALP interference', root.kGray+2, 1),
            ]
            signals_Plotter_temp = OrderedDict()
            for index, s in enumerate(signals_Plotter):
                s.index = index
                signals_Plotter_temp[s.name] = s
                signals_Plotter = signals_Plotter_temp


            if region.startswith('SR'):
                blinded = True
            else:
                blinded = False

            nice = NiceStackWithRatio(
                infile_path = '/nfs/dust/cms/user/jabuschh/combine/CMSSW_11_3_4/src/HiggsAnalysis/CombinedLimit/B2G-22-006/rootfiles/inputhists_' + year + '_' + channel + '_fa10000.root',
                # infile_directory = '', # the directory within the ROOT file
                x_axis_title = 'm(t#bar{t})',
                x_axis_unit = 'GeV',
                y_axis_min = 0.1,
                y_axis_max = 1E+09,
                prepostfit = 'prefitRaw',
                processes = processes_Plotter.values(),
                signals = signals_Plotter.values(),
                syst_names = systematics,
                lumi_unc = _YEARS.get(year).get('lumi_unc'),
                divide_by_bin_width = False,
                data_name = hist_name + region + '_data_obs', # this is now real DATA! -> keep unblinded in SRs
                text_prelim = 'Private Work',
                text_top_left = channel + ' channel (' + year + ')',
                text_top_right = _YEARS.get(year).get('lumi_fb_display') + ' fb^{#minus1} (13 TeV)',
                nostack = False,
                logy = True,
                blind_data = blinded,
            )

            nice.plot()
            nice.canvas.cd()

            # legend
            leg_offset_x = 0.10
            leg_offset_y = 0.23
            legend = root.TLegend(nice.coord.graph_to_pad_x(0.45+leg_offset_x), nice.coord.graph_to_pad_y(0.45+leg_offset_y), nice.coord.graph_to_pad_x(0.7+leg_offset_x), nice.coord.graph_to_pad_y(0.73+leg_offset_y))
            if not nice.blind_data: legend.AddEntry(nice.data_hist, 'Data', 'ep')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[hist_name + region + '_TTbar'].index), processes_Plotter[hist_name + region + '_TTbar'].legend, 'f')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[hist_name + region + '_WJets'].index), processes_Plotter[hist_name + region + '_WJets'].legend, 'f')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[hist_name + region + '_ST'].index), processes_Plotter[hist_name + region + '_ST'].legend, 'f')
            legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[hist_name + region + '_others'].index), processes_Plotter[hist_name + region + '_others'].legend, 'f')
            legend.AddEntry(nice.signal_hists[signals_Plotter[hist_name + region + '_ALP_ttbar_signal'].index], signals_Plotter[hist_name + region + '_ALP_ttbar_signal'].legend, 'l')
            legend.AddEntry(nice.signal_hists[signals_Plotter[hist_name + region + '_ALP_ttbar_interference'].index], signals_Plotter[hist_name + region + '_ALP_ttbar_interference'].legend, 'l')
            legend.SetTextSize(0.025)
            legend.SetBorderSize(0)
            legend.SetFillStyle(0)
            legend.Draw()

            # region tag
            tlatex_region = root.TLatex(nice.coord.graph_to_pad_x(0.05), nice.coord.graph_to_pad_y(0.83), var.get('text'))
            tlatex_region.SetTextAlign(13) # top left
            tlatex_region.SetTextFont(42) # bold: 62
            tlatex_region.SetTextSize(0.025)
            tlatex_region.SetNDC()
            tlatex_region.Draw()

            nice.save_plot('04_combine_input/' + year + '/' + channel + '/mtt_' + region + '.pdf')
            nice.canvas.Close()
