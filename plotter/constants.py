#!/usr/bin/env python2

# import sys
# import numpy as np

from collections import OrderedDict

# Source: https://twiki.cern.ch/twiki/bin/viewauth/CMS/TopSystematics#Luminosity
# See also: https://twiki.cern.ch/twiki/bin/view/CMS/TWikiLUM#SummaryTable (includes links to CMS publications which you can cite)
_YEARS = OrderedDict([
    ('UL16', {
        'short_name': 'UL16',
        'year': '2016',
        'long_name': 'Ultra Legacy 2016',
        'lumi_fb': 36.333, # TopSystematics source and my own brilcalc give the same results (36.333380073.916976929 with PHYSICS normtag)
        'lumi_pb': 36333.,
        'lumi_unc': 0.012,
        'lumi_fb_display': '36.3',
    }),
    ('UL16preVFP', {
        'short_name': 'UL16preVFP',
        'year': '2016 (early)',
        'long_name': 'Ultra Legacy 2016 (early)',
        # 'lumi_fb': 19.52,
        # 'lumi_pb': 19520.,
        'lumi_fb': 19.536, # brilcalc gives 19.536411965198516846 with PHYSICS normtag
        'lumi_pb': 19536.,
        'lumi_unc': 0.012,
        'lumi_fb_display': '19.5',
    }),
    ('UL16postVFP', {
        'short_name': 'UL16postVFP',
        'year': '2016 (late)',
        'long_name': 'Ultra Legacy 2016 (late)',
        # 'lumi_fb': 16.81,
        # 'lumi_pb': 16810.,
        'lumi_fb': 16.797, # brilcalc gives 16.796968109 with PHYSICS normtag
        'lumi_pb': 16797.,
        'lumi_unc': 0.012,
        'lumi_fb_display': '16.8',
    }),
    ('UL17', {
        'short_name': 'UL17',
        'year': '2017',
        'long_name': 'Ultra Legacy 2017',
        'lumi_fb': 41.480, # TopSystematics source and my own brilcalc give the same results (41.4796805287616 with PHYSICS normtag)
        'lumi_pb': 41480.,
        'lumi_unc': 0.023,
        'lumi_fb_display': '41.5',
    }),
    ('UL18', {
        'short_name': 'UL18',
        'year': '2018',
        'long_name': 'Ultra Legacy 2018',
        'lumi_fb': 59.832, # TopSystematics source and my own brilcalc give the same results (59.8324753390886 with PHYSICS normtag)
        'lumi_pb': 59832.,
        'lumi_unc': 0.025,
        'lumi_fb_display': '59.8',
    }),
    ('Run2', {
        'short_name': 'ULRunII',
        'year': '2016 + 2017 + 2018',
        'long_name': 'Run II Ultra Legacy',
        'lumi_fb': 137.645, # sum from above brilcalc calculations: 137.645535941767
        'lumi_pb': 137645.,
        'lumi_unc': 0.016,
        'lumi_fb_display': '138',
    }),
])
