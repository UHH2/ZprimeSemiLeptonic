#!/usr/bin/env python2

from collections import OrderedDict

_VARIABLES = OrderedDict([
    ('SR_bin1_TopTag', {
        'name': 'SR_bin1_TopTag',
        'text': '#splitline{t#bar{t} SR, #geq1 t-tag,}{#chi^{2} < 30, #minus1 #leq cos(#theta*) < #minus0.7}'
    }),
    ('SR_bin1_NoTopTag', {
        'name': 'SR_bin1_NoTopTag',
        'text': '#splitline{t#bar{t} SR, 0 t-tag,}{#chi^{2} < 30, #minus1 #leq cos(#theta*) < #minus0.7}'
    }),
    ('SR_bin2_TopTag', {
        'name': 'SR_bin2_TopTag',
        'text': '#splitline{t#bar{t} SR, #geq1 t-tag,}{#chi^{2} < 30, #minus0.7 #leq cos(#theta*) < #minus0.5}'
    }),
    ('SR_bin2_NoTopTag', {
        'name': 'SR_bin2_NoTopTag',
        'text': '#splitline{t#bar{t} SR, 0 t-tag,}{#chi^{2} < 30, #minus0.7 #leq cos(#theta*) < #minus0.5}'
    }),
    ('SR_bin3_TopTag', {
        'name': 'SR_bin3_TopTag',
        'text': '#splitline{t#bar{t} SR, #geq1 t-tag,}{#chi^{2} < 30, #minus0.5 #leq cos(#theta*) < 0}'
    }),
    ('SR_bin3_NoTopTag', {
        'name': 'SR_bin3_NoTopTag',
        'text': '#splitline{t#bar{t} SR, 0 t-tag,}{#chi^{2} < 30, #minus0.5 #leq cos(#theta*) < 0}'
    }),
    ('SR_bin4_TopTag', {
        'name': 'SR_bin4_TopTag',
        'text': '#splitline{t#bar{t} SR, #geq1 t-tag,}{#chi^{2} < 30, 0 #leq cos(#theta*) < 0.5}'
    }),
    ('SR_bin4_NoTopTag', {
        'name': 'SR_bin4_NoTopTag',
        'text': '#splitline{t#bar{t} SR, 0 t-tag,}{#chi^{2} < 30, 0 #leq cos(#theta*) < 0.5}'
    }),
    ('SR_bin5', {
        'name': 'SR_bin5',
        'text': '#splitline{t#bar{t} SR,}{#chi^{2} < 30, 0.5 #leq cos(#theta*) < 0.7}'
    }),
    ('SR_bin6', {
        'name': 'SR_bin6',
        'text': '#splitline{t#bar{t} SR,}{#chi^{2} < 30, 0.7 #leq cos(#theta*) < 1}'
    }),
    ('CR1', {
        'name': 'CR1',
        'text': 'Single t CR'
    }),
    ('CR2', {
        'name': 'CR2',
        'text': 'W#plusjets, Drell-Yan CR'
    }),
])
