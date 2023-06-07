#!/usr/bin/env python2

from collections import OrderedDict

_HEPData = OrderedDict([
    ('parton_abs_ttm+cts_1', {
        'hep_name': 'parton_abs_ttm+cts_1',
        'file_name': '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/ALP_reinterpretation/TOP-20-001/HEPData/HEPData-ins1901295-v1-parton_abs_ttm+cts_1.root',
        'hist_name': 'cts_mtt250To420',
        'mtt_bin_width': 420-250,
    }),
    ('parton_abs_ttm+cts_2', {
        'hep_name': 'parton_abs_ttm+cts_2',
        'file_name': '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/ALP_reinterpretation/TOP-20-001/HEPData/HEPData-ins1901295-v1-parton_abs_ttm+cts_2.root',
        'hist_name': 'cts_mtt420To520',
        'mtt_bin_width': 520-420,
    }),
    ('parton_abs_ttm+cts_3', {
        'hep_name': 'parton_abs_ttm+cts_3',
        'file_name': '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/ALP_reinterpretation/TOP-20-001/HEPData/HEPData-ins1901295-v1-parton_abs_ttm+cts_3.root',
        'hist_name': 'cts_mtt520To620',
        'mtt_bin_width': 620-520,
    }),
    ('parton_abs_ttm+cts_4', {
        'hep_name': 'parton_abs_ttm+cts_4',
        'file_name': '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/ALP_reinterpretation/TOP-20-001/HEPData/HEPData-ins1901295-v1-parton_abs_ttm+cts_4.root',
        'hist_name': 'cts_mtt620To800',
        'mtt_bin_width': 800-620,
    }),
    ('parton_abs_ttm+cts_5', {
        'hep_name': 'parton_abs_ttm+cts_5',
        'file_name': '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/ALP_reinterpretation/TOP-20-001/HEPData/HEPData-ins1901295-v1-parton_abs_ttm+cts_5.root',
        'hist_name': 'cts_mtt800To1000',
        'mtt_bin_width': 1000-800,
    }),
    ('parton_abs_ttm+cts_6', {
        'hep_name': 'parton_abs_ttm+cts_6',
        'file_name': '/nfs/dust/cms/user/jabuschh/uhh2-106X_v2/CMSSW_10_6_28/src/UHH2/ZprimeSemiLeptonic/ALP_reinterpretation/TOP-20-001/HEPData/HEPData-ins1901295-v1-parton_abs_ttm+cts_6.root',
        'hist_name': 'cts_mtt1000To3500',
        'mtt_bin_width': 3500-1000,
    }),
])

_SAMPLES = OrderedDict([
    ('TTToSemiLeptonic', {
        'name': 'TTToSemiLeptonic',
        'xsec': 831.76,
        'br': 0.438,
        'nevt': 327148781380.1,
        'file_name': '/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/TOP-20-001/uhh2.AnalysisModuleRunner.MC.TTToSemiLeptonic.root'
    }),
    ('ALP_ttbar_signal', {
        'name': 'ALP_ttbar_signal',
        'xsec': 7.048,
        'br': 1.0, # inclusive ttbar decay
        'nevt': 29131000.0,
        'file_name': '/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/TOP-20-001/uhh2.AnalysisModuleRunner.MC.ALP_ttbar_signal.root'
    }),
    ('ALP_ttbar_interference', {
        'name': 'ALP_ttbar_interference',
        'xsec': -28.24802, # use as positive interference
        'br': 1.0, # inclusive ttbar decay
        'nevt': 29389940.0,
        'file_name': '/nfs/dust/cms/user/jabuschh/ZprimeSemiLeptonic/RunII_106X_v2/TOP-20-001/uhh2.AnalysisModuleRunner.MC.ALP_ttbar_interference.root'
    }),
])

# _SYSTEMATICS = OrderedDict([
#     (''
#
#     )
# ])


# source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/LumiRecommendationsRun2#Quick_summary_table
_YEARS = OrderedDict([
    ('Run2', {
        'short_name': 'ULRunII',
        'year': '2016 + 2017 + 2018',
        'long_name': 'Run II pre-Legacy',
        'lumi_fb': 137.58,
        'lumi_pb': 137580.,
        'lumi_unc': 0.016,
        'lumi_fb_display': '138',
    }),
])
