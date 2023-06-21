#!/usr/bin/env python2

import sys
sys.argv.append('-b') # for root in batch mode
import ROOT as root

from collections import OrderedDict
from plotter import NiceStackWithRatio, Process
from constants import _YEARS
from constants_prefit_kinematics import _VARIABLES
from constants_prefit_kinematics import _REGIONS


years = [
    'UL16preVFP',
    'UL16postVFP',
    'UL17',
    'UL18',
    'Run2',
]
channels = [
    'electron',
    'muon',
]

for year in years:
    print('year: ' + year)

    systematics = [
        # 'pdf',
        # 'mcscale',
        # 'pu',
        # 'prefiring',
        # 'mu_id',
        # 'mu_iso',
        # 'mu_reco',
        # 'mu_trigger',
        # 'ele_id',
        # 'ele_reco',
        # 'ele_trigger',
        # 'btag_cferr1',
        # 'btag_cferr2',
        # 'btag_hf',
        # 'btag_hfstats1_' + year,
        # 'btag_hfstats2_' + year,
        # 'btag_lf',
        # 'btag_lfstats1_' + year,
        # 'btag_lfstats2_' + year,
        # 'ttag_corr',
        # 'ttag_uncorr_' + year,
        # 'jec',
        # 'jer',
        # 'isr',
        # 'fsr',
    ]

    for channel in channels:
        print('channel: ' + channel)

        for key, reg in _REGIONS.items():
            region = reg.get('name')
            print('region: ' + region)

            for key, var in _VARIABLES.items():
                variable = var.get('name')
                # print('variable: ' + variable)

                # SM processes
                processes_Plotter = [
                    Process(variable + '_TTbar_' + region, 't#bar{t}', root.kPink-3, 1., 0.2),
                    Process(variable + '_WJets_' + region, 'W+jets', root.kSpring-3, 1., 0.5),
                    Process(variable + '_ST_' + region, 'Single t', root.kBlue, 1., 0.3),
                    Process(variable + '_DY_' + region, 'Drell-Yan', root.kOrange, 1., 0.5),
                    Process(variable + '_Diboson_' + region, 'Diboson', root.kMagenta, 1., 0.5),
                    Process(variable + '_QCD_' + region, 'QCD', root.kAzure+10, 1., 0.5),
                ]
                processes_Plotter_temp = OrderedDict()
                for index, p in enumerate(processes_Plotter):
                    p.index = index
                    processes_Plotter_temp[p.name] = p
                    processes_Plotter = processes_Plotter_temp

                # signal
                signals_Plotter = [
                    Process(variable + '_ZPrimeToTT_M500_W50_' + region, "Z' (m = 500 GeV, #Gamma = 50 GeV)", root.kBlack, 1),
                    Process(variable + '_ZPrimeToTT_M1000_W100_' + region, "Z' (m = 1 TeV, #Gamma = 100 GeV)", root.kGray+2, 1),
                    Process(variable + '_ZPrimeToTT_M3000_W300_' + region, "Z' (m = 3 TeV, #Gamma = 300 GeV)", root.kGray, 1),
                ]
                signals_Plotter_temp = OrderedDict()
                for index, s in enumerate(signals_Plotter):
                    s.index = index
                    signals_Plotter_temp[s.name] = s
                    signals_Plotter = signals_Plotter_temp

                if region == 'SR':
                    blinded = True
                else:
                    blinded = False

                nice = NiceStackWithRatio(
                    infile_path = '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/systematics/' + year + '/' + channel + '/combine_input_after_dnn.root',
                    # infile_directory = '', # the directory within the ROOT file
                    x_axis_title = var.get('x_axis_title'),
                    x_axis_unit = var.get('x_axis_unit'),
                    y_axis_min = 1,
                    y_axis_max = 1E+09,
                    prepostfit = 'prefitRaw',
                    processes = processes_Plotter.values(),
                    signals = signals_Plotter.values(),
                    syst_names = systematics,
                    lumi_unc = _YEARS.get(year).get('lumi_unc'),
                    divide_by_bin_width = False,
                    data_name = variable + '_DATA_' + region,
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
                legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_TTbar_' + region].index), processes_Plotter[variable + '_TTbar_' + region].legend, 'f')
                legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_WJets_' + region].index), processes_Plotter[variable + '_WJets_' + region].legend, 'f')
                legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_ST_' + region].index), processes_Plotter[variable + '_ST_' + region].legend, 'f')
                legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_DY_' + region].index), processes_Plotter[variable + '_DY_' + region].legend, 'f')
                legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_Diboson_' + region].index), processes_Plotter[variable + '_Diboson_' + region].legend, 'f')
                legend.AddEntry(nice.stack.GetStack().At(processes_Plotter[variable + '_QCD_' + region].index), processes_Plotter[variable + '_QCD_' + region].legend, 'f')
                legend.AddEntry(nice.signal_hists[signals_Plotter[variable + '_ZPrimeToTT_M500_W50_' + region].index], signals_Plotter[variable + '_ZPrimeToTT_M500_W50_' + region].legend, 'l')
                legend.AddEntry(nice.signal_hists[signals_Plotter[variable + '_ZPrimeToTT_M1000_W100_' + region].index], signals_Plotter[variable + '_ZPrimeToTT_M1000_W100_' + region].legend, 'l')
                legend.AddEntry(nice.signal_hists[signals_Plotter[variable + '_ZPrimeToTT_M3000_W300_' + region].index], signals_Plotter[variable + '_ZPrimeToTT_M3000_W300_' + region].legend, 'l')
                legend.SetTextSize(0.025)
                legend.SetBorderSize(0)
                legend.SetFillStyle(0)
                legend.Draw()

                # region tag
                tlatex_region = root.TLatex(nice.coord.graph_to_pad_x(0.05), nice.coord.graph_to_pad_y(0.83), reg.get('text'))
                tlatex_region.SetTextAlign(13) # top left
                tlatex_region.SetTextFont(42) # bold: 62
                tlatex_region.SetTextSize(0.025)
                tlatex_region.SetNDC()
                tlatex_region.Draw()

                nice.save_plot('03_dnn/' + year + '/' + channel + '/' + variable + '_' + region + '.pdf')
                nice.canvas.Close()

            # # for webpage
            # def add_plots_to_html():
            #     string = ""
            #     for key, var in _VARIABLES.items():
            #         string += """<iframe src="%s.pdf" width="300px" height="300px"></iframe>\n  """ % (region)
            #     return string
            #
            # def write_html():
            #     html = """
            # <!DOCTYPE html>
            # <html>
            # <header>
            #   <h1>
            #     Plots After Baseline Selection
            #   </h1>
            # </header>
            # <body>
            #   <h2> %s: %s channel </h2>
            #   %s
            # </body>
            # </html>
            # """ % (year, channel, add_plots_to_html())
            #
            #     file = open("02_baseline_selection/" +  year + "_jetvetomaps/" + channel + "/index.html", "w")
            #     file.write(html)
            #     file.close()
            #
            # write_html()
