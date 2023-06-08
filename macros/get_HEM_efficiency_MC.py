#!/usr/bin/env python2

import ROOT as root

year = 'UL18'

channels = [
    # 'electron',
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
    'ZPrimeToTT_M1000_W100'
]

regions = [
    'DNN_output0_General', # SR
    'DNN_output1_General', # CR1
    'DNN_output2_General', # CR2
    'TopTagVeto_General' # total
]


for channel in channels:
    print('channel: ' + channel)

    for region in regions:
        print('region: ' + region)

        for sample in samples:

            file_name = 'uhh2.AnalysisModuleRunner.MC.' + sample + '.root'

            file_dir_noHEM = '/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/03_dnn/' + year + '_noHEMselection/' + channel + '/'
            root_file_noHEM = root.TFile(file_dir_noHEM + file_name, 'READ')
            hist_noHEM = root_file_noHEM.Get(region + '/sum_event_weights')
            events_noHEM = hist_noHEM.GetBinContent(1)
            # print(events_noHEM)

            file_dir = '/nfs/dust/cms/group/zprime-uhh/AnalysisDNN_' + year + '/' + channel + '/'
            root_file = root.TFile(file_dir + file_name, 'READ')
            hist = root_file.Get(region + '/sum_event_weights')
            events = hist.GetBinContent(1)
            # print(events)

            efficiency = events / events_noHEM
            percentage = (1 - efficiency) * 100
            print(str(sample) + ': {:.1f}%'.format(percentage))

            root_file_noHEM.Close()
            root_file.Close()

        print('')


    # hist_after = root_file.Get('DNN_output0_General/sum_event_weights')
    # events_after = hist_after.GetBinContent(1)
    #
    # efficiency = events_after / events_noHEM
    # percentage = efficiency * 100
    # print(str(sample) + ': {:.1f}%'.format(percentage))
