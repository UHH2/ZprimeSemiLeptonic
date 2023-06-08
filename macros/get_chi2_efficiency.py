#!/usr/bin/env python3

import ROOT as root

years = [
    'UL18'
]

channels = [
    'electron',
    'muon'
]

samples = [
    'TTbar',
    'WJets',
    'ST',
    'DY',
    'Diboson',
    'QCD',
    'ALP_ttbar_signal',
    'HpseudoToTTTo1L1Nu2J_m500_w125p0_res',
    'HscalarToTTTo1L1Nu2J_m500_w125p0_res',
    'RSGluonToTT_M-1000',
    'ZPrimeToTT_M1000_W100',
]


for year in years:
    print('year: ' + year)

    for channel in channels:
        print('channel: ' + channel)
        file_dir = '/nfs/dust/cms/group/zprime-uhh/AnalysisDNN_' + year + '/' + channel + '/'

        for sample in samples:
            file_name = 'uhh2.AnalysisModuleRunner.MC.' + sample + '.root'
            root_file = root.TFile(file_dir + file_name, 'READ')

            hist_before = root_file.Get('DNN_output0_beforeChi2Cut_General/sum_event_weights')
            events_before = hist_before.GetBinContent(1)
            # print(events_before)

            hist_after = root_file.Get('DNN_output0_General/sum_event_weights')
            events_after = hist_after.GetBinContent(1)
            # print(events_after)

            efficiency = events_after / events_before
            percentage = efficiency * 100
            print(str(sample) + ': {:.1f}%'.format(percentage))
            root_file.Close()
