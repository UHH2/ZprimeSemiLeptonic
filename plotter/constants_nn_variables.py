#!/usr/bin/env python2

from collections import OrderedDict

_VARIABLES = OrderedDict([
    ('NN_Mu_pt', {
        'name': 'NN_Mu_pt',
        'x_axis_title': 'p_{T}^{#mu}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Mu_eta', {
        'name': 'NN_Mu_eta',
        'x_axis_title': '#eta^{#mu}',
        'x_axis_unit': None
    }),
    ('NN_Mu_phi', {
        'name': 'NN_Mu_phi',
        'x_axis_title': '#phi^{#mu}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Mu_E', {
        'name': 'NN_Mu_E',
        'x_axis_title': 'E^{#mu}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ele_pt', {
        'name': 'NN_Ele_pt',
        'x_axis_title': 'p_{T}^{e}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ele_eta', {
        'name': 'NN_Ele_eta',
        'x_axis_title': '#eta^{e}',
        'x_axis_unit': None
    }),
    ('NN_Ele_phi', {
        'name': 'NN_Ele_phi',
        'x_axis_title': '#phi^{e}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ele_E', {
        'name': 'NN_Ele_E',
        'x_axis_title': 'E^{#mu}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_MET_pt', {
        'name': 'NN_MET_pt',
        'x_axis_title': 'MET',
        'x_axis_unit': 'GeV'
    }),
    ('NN_MET_phi', {
        'name': 'NN_MET_phi',
        'x_axis_title': '#phi^{MET}',
        'x_axis_unit': 'rad'
    }),
    ('NN_N_Ak4', {
        'name': 'NN_N_Ak4',
        'x_axis_title': 'N^{AK4 jets}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j1_pt', {
        'name': 'NN_Ak4_j1_pt',
        'x_axis_title': 'p_{T}^{AK4 jet 1}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j1_eta', {
        'name': 'NN_Ak4_j1_eta',
        'x_axis_title': '#eta^{AK4 jet 1}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j1_phi', {
        'name': 'NN_Ak4_j1_phi',
        'x_axis_title': '#phi^{AK4 jet 1}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak4_j1_E', {
        'name': 'NN_Ak4_j1_E',
        'x_axis_title': 'E^{AK4 jet 1}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j1_m', {
        'name': 'NN_Ak4_j1_m',
        'x_axis_title': 'm^{AK4 jet 1}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j1_btag', {
        'name': 'NN_Ak4_j1_btag',
        'x_axis_title': 'b-tag score^{AK4 jet 1}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j2_pt', {
        'name': 'NN_Ak4_j2_pt',
        'x_axis_title': 'p_{T}^{AK4 jet 2}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j2_eta', {
        'name': 'NN_Ak4_j2_eta',
        'x_axis_title': '#eta^{AK4 jet 2}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j2_phi', {
        'name': 'NN_Ak4_j2_phi',
        'x_axis_title': '#phi^{AK4 jet 2}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak4_j2_E', {
        'name': 'NN_Ak4_j2_E',
        'x_axis_title': 'E^{AK4 jet 2}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j2_m', {
        'name': 'NN_Ak4_j2_m',
        'x_axis_title': 'm^{AK4 jet 2}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j2_btag', {
        'name': 'NN_Ak4_j2_btag',
        'x_axis_title': 'b-tag score^{AK4 jet 2}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j3_pt', {
        'name': 'NN_Ak4_j3_pt',
        'x_axis_title': 'p_{T}^{AK4 jet 3}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j3_eta', {
        'name': 'NN_Ak4_j3_eta',
        'x_axis_title': '#eta^{AK4 jet 3}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j3_phi', {
        'name': 'NN_Ak4_j3_phi',
        'x_axis_title': '#phi^{AK4 jet 3}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak4_j3_E', {
        'name': 'NN_Ak4_j3_E',
        'x_axis_title': 'E^{AK4 jet 3}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j3_m', {
        'name': 'NN_Ak4_j3_m',
        'x_axis_title': 'm^{AK4 jet 3}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j3_btag', {
        'name': 'NN_Ak4_j3_btag',
        'x_axis_title': 'b-tag score^{AK4 jet 3}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j4_pt', {
        'name': 'NN_Ak4_j4_pt',
        'x_axis_title': 'p_{T}^{AK4 jet 4}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j4_eta', {
        'name': 'NN_Ak4_j4_eta',
        'x_axis_title': '#eta^{AK4 jet 4}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j4_phi', {
        'name': 'NN_Ak4_j4_phi',
        'x_axis_title': '#phi^{AK4 jet 4}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak4_j4_E', {
        'name': 'NN_Ak4_j4_E',
        'x_axis_title': 'E^{AK4 jet 4}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j4_m', {
        'name': 'NN_Ak4_j4_m',
        'x_axis_title': 'm^{AK4 jet 4}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j4_btag', {
        'name': 'NN_Ak4_j4_btag',
        'x_axis_title': 'b-tag score^{AK4 jet 4}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j5_pt', {
        'name': 'NN_Ak4_j5_pt',
        'x_axis_title': 'p_{T}^{AK4 jet 5}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j5_eta', {
        'name': 'NN_Ak4_j5_eta',
        'x_axis_title': '#eta^{AK4 jet 5}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j5_phi', {
        'name': 'NN_Ak4_j5_phi',
        'x_axis_title': '#phi^{AK4 jet 5}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak4_j5_E', {
        'name': 'NN_Ak4_j5_E',
        'x_axis_title': 'E^{AK4 jet 5}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j5_m', {
        'name': 'NN_Ak4_j5_m',
        'x_axis_title': 'm^{AK4 jet 5}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j5_btag', {
        'name': 'NN_Ak4_j5_btag',
        'x_axis_title': 'b-tag score^{AK4 jet 5}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j6_pt', {
        'name': 'NN_Ak4_j6_pt',
        'x_axis_title': 'p_{T}^{AK4 jet 6}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j6_eta', {
        'name': 'NN_Ak4_j6_eta',
        'x_axis_title': '#eta^{AK4 jet 6}',
        'x_axis_unit': None
    }),
    ('NN_Ak4_j6_phi', {
        'name': 'NN_Ak4_j6_phi',
        'x_axis_title': '#phi^{AK4 jet 6}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak4_j6_E', {
        'name': 'NN_Ak4_j6_E',
        'x_axis_title': 'E^{AK4 jet 6}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j6_m', {
        'name': 'NN_Ak4_j6_m',
        'x_axis_title': 'm^{AK4 jet 6}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak4_j6_btag', {
        'name': 'NN_Ak4_j6_btag',
        'x_axis_title': 'b-tag score^{AK4 jet 6}',
        'x_axis_unit': None
    }),
    ('NN_N_Ak8', {
        'name': 'NN_N_Ak8',
        'x_axis_title': 'N^{AK8 jets}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j1_pt', {
        'name': 'NN_Ak8_j1_pt',
        'x_axis_title': 'p_{T}^{AK8 jet 1}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j1_eta', {
        'name': 'NN_Ak8_j1_eta',
        'x_axis_title': '#eta^{AK8 jet 1}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j1_phi', {
        'name': 'NN_Ak8_j1_phi',
        'x_axis_title': '#phi^{AK8 jet 1}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak8_j1_E', {
        'name': 'NN_Ak8_j1_E',
        'x_axis_title': 'E^{AK8 jet 1}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j1_mSD', {
        'name': 'NN_Ak8_j1_mSD',
        'x_axis_title': 'm_{soft drop}^{AK8 jet 1}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j1_tau21', {
        'name': 'NN_Ak8_j1_tau21',
        'x_axis_title': '#tau_{21}^{AK8 jet 1}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j1_tau32', {
        'name': 'NN_Ak8_j1_tau32',
        'x_axis_title': '#tau_{32}^{AK8 jet 1}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j2_pt', {
        'name': 'NN_Ak8_j2_pt',
        'x_axis_title': 'p_{T}^{AK8 jet 2}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j2_eta', {
        'name': 'NN_Ak8_j2_eta',
        'x_axis_title': '#eta^{AK8 jet 2}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j2_phi', {
        'name': 'NN_Ak8_j2_phi',
        'x_axis_title': '#phi^{AK8 jet 2}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak8_j2_E', {
        'name': 'NN_Ak8_j2_E',
        'x_axis_title': 'E^{AK8 jet 2}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j2_mSD', {
        'name': 'NN_Ak8_j2_mSD',
        'x_axis_title': 'm_{soft drop}^{AK8 jet 2}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j2_tau21', {
        'name': 'NN_Ak8_j2_tau21',
        'x_axis_title': '#tau_{21}^{AK8 jet 2}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j2_tau32', {
        'name': 'NN_Ak8_j2_tau32',
        'x_axis_title': '#tau_{32}^{AK8 jet 2}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j3_pt', {
        'name': 'NN_Ak8_j3_pt',
        'x_axis_title': 'p_{T}^{AK8 jet 3}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j3_eta', {
        'name': 'NN_Ak8_j3_eta',
        'x_axis_title': '#eta^{AK8 jet 3}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j3_phi', {
        'name': 'NN_Ak8_j3_phi',
        'x_axis_title': '#phi^{AK8 jet 3}',
        'x_axis_unit': 'rad'
    }),
    ('NN_Ak8_j3_E', {
        'name': 'NN_Ak8_j3_E',
        'x_axis_title': 'E^{AK8 jet 3}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j3_mSD', {
        'name': 'NN_Ak8_j3_mSD',
        'x_axis_title': 'm_{soft drop}^{AK8 jet 3}',
        'x_axis_unit': 'GeV'
    }),
    ('NN_Ak8_j3_tau21', {
        'name': 'NN_Ak8_j3_tau21',
        'x_axis_title': '#tau_{21}^{AK8 jet 3}',
        'x_axis_unit': None
    }),
    ('NN_Ak8_j3_tau32', {
        'name': 'NN_Ak8_j3_tau32',
        'x_axis_title': '#tau_{32}^{AK8 jet 3}',
        'x_axis_unit': None
    }),
])
