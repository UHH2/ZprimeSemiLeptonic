from collections import namedtuple,Mapping

def namedtuple_with_defaults(typename, field_names, default_values=()):
    T = namedtuple(typename, field_names)
    T.__new__.__defaults__ = (None,) * len(T._fields)
    if isinstance(default_values, Mapping):
        prototype = T(**default_values)
    else:
        prototype = T(*default_values)
    T.__new__.__defaults__ = tuple(prototype)
    return T


class MCSampleValuesHelper():
    """Stores the cross sections and k-factors associated to a given physics process.

    The lists of years and energies used to identify a given cross section are also stored within this class.
    Given a process name, and year the appropriate cross section will be returned.

    Args:
        extra_dicts (:obj:`dict` of :obj:`dict` of :obj:`namedtuple_with_defaults`): Extra cross sections and k-factors to add to the __values_dict.

    Example:
        from CrossSectionHelper import *
        helper = MCSampleValuesHelper()
        helper.get_lumi("TTbarTo2L2Nu","13TeV","2018")
        helper.get_xs("TTbarTo2L2Nu","13TeV","2018")
        helper.get_nevt("TTbarTo2L2Nu","13TeV","2018")
        helper.get_br("TTbarTo2L2Nu","13TeV","2018")
        helper.get_xml("TTbar","13TeV","2016")
    """

    __years = ["UL16preVFP","UL16postVFP","UL17","UL18"]
    __energies = ["13TeV"]
    __xs_field_names = []
    __nevt_field_names = []
    __br_field_names = []
    __kfactor_field_names = []
    __corr_field_names = []
    __xml_field_names = []
    __key_field_map = {
        "CrossSection"   : ("XSec",-1.0),
        "NEvents"        : ("NEVT",-1.0),
        "BranchingRatio" : ("BRat",1.0),
        "kFactor"        : ("kFac",1.0),
        "Correction"     : ("Corr",1.0),
        "XMLname"        : ("Xml",""),
    }
    for __val in __years+__energies:
        for mode in ["", "Source"]:
            __xs_field_names.append("XSec"+mode+"_"+__val)
            __nevt_field_names.append("NEVT"+mode+"_"+__val)
            __br_field_names.append("BRat"+mode+"_"+__val)
            __kfactor_field_names.append("kFac"+mode+"_"+__val)
            __corr_field_names.append("Corr"+mode+"_"+__val)
            __xml_field_names.append("Xml"+mode+"_"+__val)
    XSValues      = namedtuple_with_defaults("XSValues",      __xs_field_names,       [__key_field_map["CrossSection"][1],""]*len(__years+__energies))
    NEventsValues = namedtuple_with_defaults("NEventsValues", __nevt_field_names,     [__key_field_map["NEvents"][1],""]*len(__years+__energies))
    BRValues      = namedtuple_with_defaults("BRValues",      __br_field_names,       [__key_field_map["BranchingRatio"][1],""]*len(__years+__energies))
    kFactorValues = namedtuple_with_defaults("kFactorValues", __kfactor_field_names,  [__key_field_map["kFactor"][1],""]*len(__years+__energies))
    CorrValues    = namedtuple_with_defaults("CorrValues",    __corr_field_names,     [__key_field_map["Correction"][1],""]*len(__years+__energies))
    XMLValues     = namedtuple_with_defaults("XMLValues",     __xml_field_names,      [__key_field_map["XMLname"][1],""]*len(__years+__energies))

    __values_dict = {

####################################################################
##    ZPrime 10%
####################################################################

        "ZPrimeToTT_M400_W40" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=261000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=497000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M400_W40_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M400_W40_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M400_W40_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M400_W40_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M400_W40_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M400_W40_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M400_W40_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M400_W40_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M500_W50" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=229000.0,
                NEVT_UL17=491000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M500_W50_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M500_W50_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M500_W50_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M500_W50_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M500_W50_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M500_W50_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M500_W50_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M500_W50_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M600_W60" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=268000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=494000.0,
                NEVT_UL18=491000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M600_W60_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M600_W60_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M600_W60_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M600_W60_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M600_W60_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M600_W60_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M600_W60_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M600_W60_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M700_W70" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=464000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M700_W70_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M700_W70_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M700_W70_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M700_W70_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M700_W70_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M700_W70_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M700_W70_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M700_W70_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M800_W80" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=266000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=494000.0,
                NEVT_UL18=482000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M800_W80_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M800_W80_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M800_W80_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M800_W80_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M800_W80_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M800_W80_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M800_W80_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M800_W80_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M900_W90" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M900_W90_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M900_W90_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M900_W90_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M900_W90_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M900_W90_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M900_W90_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M900_W90_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M900_W90_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1000_W100" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1000_W100_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1000_W100_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1000_W100_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1000_W100_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1000_W100_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1000_W100_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1000_W100_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1000_W100_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1200_W120" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=497000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1200_W120_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1200_W120_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1200_W120_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1200_W120_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1200_W120_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1200_W120_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1200_W120_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1200_W120_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1400_W140" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=262000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=482000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1400_W140_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1400_W140_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1400_W140_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1400_W140_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1400_W140_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1400_W140_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1400_W140_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1400_W140_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1600_W160" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=494000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1600_W160_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1600_W160_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1600_W160_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1600_W160_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1600_W160_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1600_W160_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1600_W160_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1600_W160_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1800_W180" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=264000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=491000.0,
                NEVT_UL18=482000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1800_W180_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1800_W180_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1800_W180_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1800_W180_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1800_W180_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1800_W180_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1800_W180_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1800_W180_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M2000_W200" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M2000_W200_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M2000_W200_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M2000_W200_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M2000_W200_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M2000_W200_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M2000_W200_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M2000_W200_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M2000_W200_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M2500_W250" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=267000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=489000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M2500_W250_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M2500_W250_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M2500_W250_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M2500_W250_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M2500_W250_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M2500_W250_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M2500_W250_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M2500_W250_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M3000_W300" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=491000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M3000_W300_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M3000_W300_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M3000_W300_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M3000_W300_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M3000_W300_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M3000_W300_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M3000_W300_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M3000_W300_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M3500_W350" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M3500_W350_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M3500_W350_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M3500_W350_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M3500_W350_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M3500_W350_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M3500_W350_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M3500_W350_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M3500_W350_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M4000_W400" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=267000.0,
                NEVT_UL16postVFP=210000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M4000_W400_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M4000_W400_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M4000_W400_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M4000_W400_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M4000_W400_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M4000_W400_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M4000_W400_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M4000_W400_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M4500_W450" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=497000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M4500_W450_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M4500_W450_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM ",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M4500_W450_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M4500_W450_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M4500_W450_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M4500_W450_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M4500_W450_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M4500_W450_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M5000_W500" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=200000.0,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M5000_W500_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M5000_W500_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M5000_W500_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M5000_W500_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M5000_W500_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M5000_W500_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },
        "ZPrimeToTT_M6000_W600" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=200000.0,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M6000_W600_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M6000_W600_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M6000_W600_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M6000_W600_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M6000_W600_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M6000_W600_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },
        "ZPrimeToTT_M7000_W700" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=200000.0,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M7000_W700_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M7000_W700_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M7000_W700_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M7000_W700_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M7000_W700_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M7000_W700_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },
        "ZPrimeToTT_M8000_W800" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=-1,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M8000_W800_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M8000_W800_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M8000_W800_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M8000_W800_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/", XmlSource_UL17="",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },
        "ZPrimeToTT_M9000_W900" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=200000.0,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M9000_W900_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M9000_W900_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M9000_W900_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M9000_W900_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M9000_W900_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M9000_W900_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },

####################################################################
##    ZPrime 30%
####################################################################


        "ZPrimeToTT_M400_W120" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M400_W120_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M400_W120_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M400_W120_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M400_W120_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M400_W120_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M400_W120_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M400_W120_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M400_W120_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M500_W150" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=494000.0,
                NEVT_UL18=485000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M500_W150_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M500_W150_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM ",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M500_W150_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M500_W150_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M500_W150_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M500_W150_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M500_W150_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M500_W150_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M600_W180" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=491000.0,
                NEVT_UL18=497000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M600_W180_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M600_W180_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M600_W180_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M600_W180_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M600_W180_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M600_W180_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M600_W180_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M600_W180_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M700_W210" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M700_W210_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M700_W210_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M700_W210_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M700_W210_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M700_W210_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M700_W210_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M700_W70_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M700_W210_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M800_W240" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M800_W240_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M800_W240_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M800_W240_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M800_W240_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M800_W240_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M800_W240_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M800_W240_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M800_W240_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M900_W270" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=227000.0,
                NEVT_UL17=-1,
                NEVT_UL18=497000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M900_W270_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M900_W270_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M900_W270_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M900_W270_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/", XmlSource_UL17="",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M900_W270_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M900_W270_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1000_W300" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1000_W300_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1000_W300_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1000_W300_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1000_W300_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1000_W300_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1000_W300_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1000_W300_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1000_W300_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1200_W360" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=494000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1200_W360_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1200_W360_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1200_W360_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1200_W360_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1200_W360_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1200_W360_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1200_W360_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1200_W360_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1400_W420" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=488000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1400_W420_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1400_W420_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1400_W420_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1400_W420_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1400_W420_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1400_W420_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1400_W420_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1400_W420_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1600_W480" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=497000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1600_W480_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1600_W480_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1600_W480_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1600_W480_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1600_W480_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1600_W480_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1600_W480_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1600_W480_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M1800_W540" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=228000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M1800_W540_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M1800_W540_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M1800_W540_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M1800_W540_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M1800_W540_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M1800_W540_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M1800_W540_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M1800_W540_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M2000_W600" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M2000_W600_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M2000_W600_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M2000_W600_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M2000_W600_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M2000_W600_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M2000_W600_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M2000_W600_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M2000_W600_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M2500_W750" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=489000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M2500_W750_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M2500_W750_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M2500_W750_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M2500_W750_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M2500_W750_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M2500_W750_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M2500_W750_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M2500_W750_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M3000_W900" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=488000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M3000_W900_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M3000_W900_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M3000_W900_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M3000_W900_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M3000_W900_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M3000_W900_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M3000_W900_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M3000_W900_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M3500_W1050" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M3500_W1050_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M3500_W1050_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M3500_W1050_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M3500_W1050_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M3500_W1050_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M3500_W1050_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M3500_W1050_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M3500_W1050_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M4000_W1200" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=228000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M4000_W1200_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M4000_W1200_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M4000_W1200_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M4000_W1200_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M4000_W1200_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M4000_W1200_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M4000_W1200_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M4000_W1200_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M4500_W1350" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=270000.0,
                NEVT_UL16postVFP=230000.0,
                NEVT_UL17=500000.0,
                NEVT_UL18=500000.0,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M4500_W1350_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M4500_W1350_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M4500_W1350_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M4500_W1350_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM ",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M4500_W1350_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M4500_W1350_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/ZPrimeToTT_M4500_W1350_CP2_madgraph-pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/ZPrimeToTT_M4500_W1350_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "ZPrimeToTT_M5000_W1500" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=200000.0,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M5000_W1500_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M5000_W1500_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M5000_W1500_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M5000_W1500_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M5000_W1500_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M5000_W1500_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },
        "ZPrimeToTT_M6000_W1800" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=200000.0,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M6000_W1800_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M6000_W1800_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M6000_W1800_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M6000_W1800_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M6000_W1800_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M6000_W1800_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },
        "ZPrimeToTT_M7000_W2100" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=-1,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M7000_W2100_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M7000_W2100_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M7000_W2100_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M7000_W2100_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/", XmlSource_UL17="",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },
        "ZPrimeToTT_M8000_W2400" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=-1,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M8000_W2400_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M8000_W2400_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M8000_W2400_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M8000_W2400_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/", XmlSource_UL17="",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },
        "ZPrimeToTT_M9000_W2700" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=108000.0,
                NEVT_UL16postVFP=92000.0,
                NEVT_UL17=200000.0,
                NEVT_UL18=-1,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/ZPrimeToTT_M9000_W2700_CP2_madgraph-pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/ZPrimeToTT_M9000_W2700_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/ZPrimeToTT_M9000_W2700_CP2_madgraph-pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/ZPrimeToTT_M9000_W2700_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/ZPrimeToTT_M9000_W2700_CP2_madgraph-pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/ZPrimeToTT_M9000_W2700_TuneCP2_13TeV-madgraph-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/", XmlSource_UL18="",
            ),
        },


####################################################################
##    RS gluons
####################################################################



        "RSGluonToTT_M-500" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=235000,
                NEVT_UL16postVFP=250000,
                NEVT_UL17=500000,
                NEVT_UL18=500000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-500_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-500_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-500_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-500_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-500_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-500_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-1000" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=244000,
                NEVT_UL16postVFP=250000,
                NEVT_UL17=485000,
                NEVT_UL18=479000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-1000_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-1000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-1000_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-1000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-1000_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-1000_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-1000_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-1000_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-1500" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=240000,
                NEVT_UL16postVFP=228000,
                NEVT_UL17=500000,
                NEVT_UL18=500000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-1500_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-1500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-1500_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-1500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-1500_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-1500_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-1500_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-1500_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-2000" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=250000,
                NEVT_UL16postVFP=208000,
                NEVT_UL17=494000,
                NEVT_UL18=494000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-2000_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-2000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-2000_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-2000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-2000_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-2000_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-2000_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-2000_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-2500" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=250000,
                NEVT_UL16postVFP=196000,
                NEVT_UL17=497000,
                NEVT_UL18=488000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-2500_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-2500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-2500_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-2500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-2500_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-2500_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-2500_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-2500_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-3000" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=241000,
                NEVT_UL16postVFP=248000,
                NEVT_UL17=500000,
                NEVT_UL18=500000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-3000_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-3000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-3000_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-3000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-3000_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-3000_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-3000_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-3000_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-3500" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=250000,
                NEVT_UL16postVFP=250000,
                NEVT_UL17=497000,
                NEVT_UL18=500000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-3500_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-3500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-3500_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-3500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-3500_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-3500_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-3500_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-3500_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-4000" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=250000,
                NEVT_UL16postVFP=239000,
                NEVT_UL17=497000,
                NEVT_UL18=484000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-4000_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-4000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-4000_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-4000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-4000_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-4000_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-4000_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-4000_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-4500" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=250000,
                NEVT_UL16postVFP=249000,
                NEVT_UL17=464000,
                NEVT_UL18=482000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-4500_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-4500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-4500_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-4500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-4500_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-4500_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-4500_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-4500_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-5000" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=250000,
                NEVT_UL16postVFP=234000,
                NEVT_UL17=500000,
                NEVT_UL18=500000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-5000_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-5000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-5000_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-5000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-5000_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-5000_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-5000_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-5000_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-5500" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=238000,
                NEVT_UL16postVFP=248000,
                NEVT_UL17=494000,
                NEVT_UL18=479000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-5500_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-5500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-5500_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-5500_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-5500_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-5500_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-5500_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-5500_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },
        "RSGluonToTT_M-6000" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1, XSecSource_13TeV="Fixed to 1 pb",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=250000,
                NEVT_UL16postVFP=248000,
                NEVT_UL17=476000,
                NEVT_UL18=455000,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/RSGluonToTT_M-6000_CP5_pythia8_Summer20UL16APV_v1.xml", XmlSource_UL16preVFP="/RSGluonToTT_M-6000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v1/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/RSGluonToTT_M-6000_CP5_pythia8_Summer20UL16_v1.xml", XmlSource_UL16postVFP="/RSGluonToTT_M-6000_TuneCP5_13TeV-pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v1/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/RSGluonToTT_M-6000_CP5_pythia8_Summer20UL17_v1.xml", XmlSource_UL17="/RSGluonToTT_M-6000_TuneCP5_13TeV-pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v1/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/RSGluonToTT_M-6000_CP5_pythia8_Summer20UL18_v1.xml", XmlSource_UL18="/RSGluonToTT_M-6000_TuneCP5_13TeV-pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v1/MINIAODSIM",
            ),
        },



####################################################################
##    H pseudo RES 25%
####################################################################


        "HpseudoToTTTo1L1Nu2J_m365_w91p25_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.384058, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.37211, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=81204.09208,
                NEVT_UL16postVFP=82251.48621,
                NEVT_UL17=171213.0027,
                NEVT_UL18=172236.535667,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m365_w91p25_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m365_w91p25_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m365_w91p25_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m365_w91p25_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m365_w91p25_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m365_w91p25_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m365_w91p25_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m365_w91p25_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM ",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m400_w100p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.392964, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.25867, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=88520.838147,
                NEVT_UL16postVFP=88492.02305,
                NEVT_UL17=177113.8621,
                NEVT_UL18=176982.22823,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m400_w100p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m400_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m400_w100p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m400_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m400_w100p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m400_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m400_w100p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m400_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m500_w125p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.222718, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.13856, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=50395.421986,
                NEVT_UL16postVFP=50202.848086,
                NEVT_UL17=100770.483906,
                NEVT_UL18=98974.44703,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m500_w125p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m500_w125p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m500_w125p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m500_w125p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m500_w125p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m500_w125p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m500_w125p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m500_w125p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m600_w150p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.108418, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.0793, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=24356.66183,
                NEVT_UL16postVFP=23560.2129205,
                NEVT_UL17=48805.85248,
                NEVT_UL18=48779.242473,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m600_w150p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m600_w150p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m600_w150p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m600_w150p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m600_w150p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m600_w150p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m600_w150p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m600_w150p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m800_w200p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.02871, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.01433, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=6505.440998,
                NEVT_UL16postVFP=6501.2446068,
                NEVT_UL17=13009.3894694,
                NEVT_UL18=13010.468379,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m800_w200p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m800_w200p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m800_w200p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m800_w200p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m800_w200p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m800_w200p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m800_w200p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m800_w200p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m1000_w250p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.00935898, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.97913, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=2119.7220377,
                NEVT_UL16postVFP=2069.06411289,
                NEVT_UL17=4224.5618954,
                NEVT_UL18=4242.4866877,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m1000_w250p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },

####################################################################
##    H pseudo INT 25%
####################################################################


        "HpseudoToTTTo1L1Nu2J_m365_w91p25_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-3.51387, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.88314, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-794059.0838,
                NEVT_UL16postVFP=-795879.67662,
                NEVT_UL17=-1586370.3368,
                NEVT_UL18=-1586907.61682,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m365_w91p25_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m365_w91p25_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m365_w91p25_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m365_w91p25_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m365_w91p25_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m365_w91p25_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m365_w91p25_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m365_w91p25_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m400_w100p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-2.80865, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.83756, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-1,
                NEVT_UL16postVFP=-643622.5466,
                NEVT_UL17=-1248131.677,
                NEVT_UL18=-1278265.00519,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m400_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m400_w100p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m400_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m400_w100p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m400_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m400_w100p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m400_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m500_w125p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-1.06139, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.78803, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-243627.29086,
                NEVT_UL16postVFP=-246766.59487,
                NEVT_UL17=-486918.76265,
                NEVT_UL18=-488398.0432,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m500_w125p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m500_w125p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m500_w125p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m500_w125p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m500_w125p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m500_w125p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m500_w125p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m500_w125p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m600_w150p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.354892, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.76308, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-83281.641741,
                NEVT_UL16postVFP=-84832.311593,
                NEVT_UL17=-165008.109821,
                NEVT_UL18=-165895.03658,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m600_w150p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m600_w150p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m600_w150p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m600_w150p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m600_w150p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m600_w150p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m600_w150p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m600_w150p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m800_w200p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0131675, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.73532, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=2275.8078853,
                NEVT_UL16postVFP=1220.2306676,
                NEVT_UL17=3818.12660971,
                NEVT_UL18=3542.98394915,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m800_w200p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m800_w200p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m800_w200p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m800_w200p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m800_w200p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m800_w200p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m800_w200p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m800_w200p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m1000_w250p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0630704, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.72009, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=13939.756035,
                NEVT_UL16postVFP=13721.556921,
                NEVT_UL17=28024.216226,
                NEVT_UL18=27824.657441,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m1000_w250p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },


####################################################################
##    H pseudo RES 10%
####################################################################


        "HpseudoToTTTo1L1Nu2J_m365_36p5_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1.18764, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.88312, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=256294.89633,
                NEVT_UL16postVFP=145074.15602,
                NEVT_UL17=523391.4965,
                NEVT_UL18=529368.49437,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m365_w36p5_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m365_w36p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m365_w36p5_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m365_w36p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m365_w36p5_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m365_w36p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m365_w36p5_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m365_w36p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m400_w40p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1.28105, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.83757, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=288659.16832,
                NEVT_UL16postVFP=286415.1199,
                NEVT_UL17=574027.6727,
                NEVT_UL18=573900.86455,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m400_w40p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m400_w40p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m400_w40p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m400_w40p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m400_w40p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m400_w40p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m400_w40p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m400_w40p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m500_w50p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.660745, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.78803, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=149616.08465,
                NEVT_UL16postVFP=149629.914053,
                NEVT_UL17=299162.2687,
                NEVT_UL18=296686.89491,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m500_w50p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m500_w50p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m500_w50p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m500_w50p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m500_w50p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m500_w50p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m500_w50p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m500_w50p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m600_w60p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.29944, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.76302, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=66829.024208,
                NEVT_UL16postVFP=67582.717264,
                NEVT_UL17=135699.902294,
                NEVT_UL18=134971.091663,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m600_w60p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m600_w60p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m600_w60p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m600_w60p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m600_w60p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m600_w60p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m600_w60p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m600_w60p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m800_w80p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0709866, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.73535, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=16087.587782,
                NEVT_UL16postVFP=16093.945433,
                NEVT_UL17=32174.2228,
                NEVT_UL18=31987.80998,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m800_w80p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m800_w80p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m800_w80p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m800_w80p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m800_w80p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m800_w80p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m800_w80p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m800_w80p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m1000_w100p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0209362, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.72011, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=4745.017413,
                NEVT_UL16postVFP=4747.91728,
                NEVT_UL17=9494.3699807,
                NEVT_UL18=9263.5783702,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m1000_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },

####################################################################
##    H pseudo INT 10%
####################################################################


        "HpseudoToTTTo1L1Nu2J_m365_36p5_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-4.92926, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.88312, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-1112972.69016,
                NEVT_UL16postVFP=-1117513.98756,
                NEVT_UL17=-2210403.7067,
                NEVT_UL18=-2171094.16728,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m365_w36p5_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m365_w36p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m365_w36p5_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m365_w36p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m365_w36p5_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m365_w36p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m365_w36p5_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m365_w36p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m400_w40p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-3.44265, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.83757, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-786867.006,
                NEVT_UL16postVFP=-789101.34692,
                NEVT_UL17=-1579406.2598,
                NEVT_UL18=-1579689.1022,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m400_w40p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m400_w40p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m400_w40p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m400_w40p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m400_w40p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m400_w40p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m400_w40p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m400_w40p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m500_w50p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.937263, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.78803, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-219110.9435,
                NEVT_UL16postVFP=-227201.4818,
                NEVT_UL17=-421949.39712,
                NEVT_UL18=-436120.3311,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m500_w50p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m500_w50p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m500_w50p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m500_w50p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m500_w50p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m500_w50p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m500_w50p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m500_w50p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m600_w60p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.166936, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.76302, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-37340.34489,
                NEVT_UL16postVFP=-44194.05708,
                NEVT_UL17=-83092.998201,
                NEVT_UL18=-81900.821139,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m600_w60p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m600_w60p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m600_w60p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m600_w60p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m600_w60p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m600_w60p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m600_w60p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m600_w60p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m800_w80p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.135484, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.73535, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=29430.640305,
                NEVT_UL16postVFP=28099.969551,
                NEVT_UL17=58927.923394,
                NEVT_UL18=60225.44581,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m800_w80p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m800_w80p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m800_w80p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m800_w80p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m800_w80p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m800_w80p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m800_w80p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m800_w80p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m1000_w100p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.136502, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.72011, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=30483.761009,
                NEVT_UL16postVFP=30111.835363,
                NEVT_UL17=60820.291822,
                NEVT_UL18=60547.235299,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m1000_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },

####################################################################
##    H pseudo RES 2.5%
####################################################################


        "HpseudoToTTTo1L1Nu2J_m365_w9p125_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=5.86888, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.37207, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=1303218.1199,
                NEVT_UL16postVFP=1303405.7415,
                NEVT_UL17=2607335.746,
                NEVT_UL18=2607045.7854,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m365_w9p125_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m365_w9p125_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m365_w9p125_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m365_w9p125_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m365_w9p125_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m365_w9p125_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m365_w9p125_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m365_w9p125_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m400_w10p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=6.03581, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.2587, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=1361550.8595,
                NEVT_UL16postVFP=1345760.2621,
                NEVT_UL17=2657277.9441,
                NEVT_UL18=2543868.1279,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m400_w10p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m400_w10p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m400_w10p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m400_w10p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m400_w10p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m400_w10p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m400_w10p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m400_w10p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m500_w12p5_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=2.8598, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.13858, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=647810.9576,
                NEVT_UL16postVFP=648333.9809,
                NEVT_UL17=1295076.4766,
                NEVT_UL18=1295687.9387,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m500_w12p5_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m500_w12p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m500_w12p5_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m500_w12p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m500_w12p5_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m500_w12p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m500_w12p5_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m500_w12p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m600_w15p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=1.23894, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.07926, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=280849.12182,
                NEVT_UL16postVFP=280878.1883,
                NEVT_UL17=561601.46323,
                NEVT_UL18=561805.4832,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m600_w15p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m600_w15p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m600_w15p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m600_w15p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m600_w15p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m600_w15p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m600_w15p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m600_w15p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m800_w20p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.273973, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.0144, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=62120.010172,
                NEVT_UL16postVFP=29574.237047,
                NEVT_UL17=124281.764049,
                NEVT_UL18=124293.07307,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m800_w20p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m800_w20p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m800_w20p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m800_w20p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m800_w20p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m800_w20p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m800_w20p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m800_w20p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m1000_w25p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0754245, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.97911, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=17104.940015,
                NEVT_UL16postVFP=16626.1296345,
                NEVT_UL17=34005.567704,
                NEVT_UL18=31349.5508702,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m1000_w25p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
####################################################################
##    H pseudo INT 2.5%
####################################################################


        "HpseudoToTTTo1L1Nu2J_m365_w9p125_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-6.08885, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.88312, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-1382651.7808,
                NEVT_UL16postVFP=-1390762.68325,
                NEVT_UL17=-1779358.20887,
                NEVT_UL18=-2770824.941,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m365_w9p125_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m365_w9p125_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m365_w9p125_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m365_w9p125_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m400_w10p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-3.71856, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.83757, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-861366.33313,
                NEVT_UL16postVFP=-839948.9534,
                NEVT_UL17=-1565961.86264,
                NEVT_UL18=-1658473.7532,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m400_w10p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m400_w10p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m400_w10p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m400_w10p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m400_w10p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m400_w10p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m400_w10p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m400_w10p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m500_w12p5_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.787467, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.78804, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-183156.43415,
                NEVT_UL16postVFP=-195530.84382,
                NEVT_UL17=-374395.86068,
                NEVT_UL18=-358621.8006,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m500_w12p5_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m500_w12p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m500_w12p5_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m500_w12p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m500_w12p5_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m500_w12p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m500_w12p5_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m500_w12p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m600_w15p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.0280567, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.76307, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-5320.2340722,
                NEVT_UL16postVFP=-10244.00829,
                NEVT_UL17=-13291.4155487,
                NEVT_UL18=-23223.570779,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m600_w15p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m600_w15p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m600_w15p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m600_w15p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m600_w15p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m600_w15p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m600_w15p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m600_w15p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m800_w20p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.208417, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.73535, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=47685.61398,
                NEVT_UL16postVFP=46310.2176,
                NEVT_UL17=84343.846579,
                NEVT_UL18=91382.61924,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m800_w20p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m800_w20p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m800_w20p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m800_w20p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m800_w20p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m800_w20p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m800_w20p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m800_w20p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HpseudoToTTTo1L1Nu2J_m1000_w25p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.17625, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.72008, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=39879.742145,
                NEVT_UL16postVFP=39097.948724,
                NEVT_UL17=78350.880834,
                NEVT_UL18=78197.12187,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HpseudoToTTTo1L1Nu2J_m1000_w25p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },






####################################################################
##    H scalar RES 25%
####################################################################


        "HscalarToTTTo1L1Nu2J_m365_w91p25_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0399425, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.36163, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=8579.9033952,
                NEVT_UL16postVFP=9012.0945942,
                NEVT_UL17=17879.6904069,
                NEVT_UL18=18024.894798,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m365_w91p25_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m365_w91p25_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m365_w91p25_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m365_w91p25_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m365_w91p25_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m365_w91p25_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m365_w91p25_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m365_w91p25_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m400_w100p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0530526, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.28739, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=11974.2015662,
                NEVT_UL16postVFP=23944.04088,
                NEVT_UL17=23944.04088,
                NEVT_UL18=23973.1011264,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m400_w100p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m400_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m400_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m400_w100p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m400_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m400_w100p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m400_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m500_w125p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.057073, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.17333, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=12707.539589,
                NEVT_UL16postVFP=12912.4057126,
                NEVT_UL17=25794.11704,
                NEVT_UL18=25806.64633,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m500_w125p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m500_w125p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m500_w125p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m500_w125p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m500_w125p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m500_w125p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m500_w125p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m500_w125p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m600_w150p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0388742, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.11279, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=8806.4777909,
                NEVT_UL16postVFP=8800.454386,
                NEVT_UL17=17599.58449,
                NEVT_UL18=17594.696292,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m600_w150p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m600_w150p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m600_w150p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m600_w150p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m600_w150p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m600_w150p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m600_w150p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m600_w150p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m800_w200p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0138542, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.04658, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=3139.3466361,
                NEVT_UL16postVFP=3127.4778621,
                NEVT_UL17=5951.5560198,
                NEVT_UL18=6278.8737025,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m800_w200p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m800_w200p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m800_w200p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m800_w200p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m800_w200p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m800_w200p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m800_w200p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m800_w200p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m1000_w250p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.00503847, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.01067, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=1141.80461993,
                NEVT_UL16postVFP=1114.5434492,
                NEVT_UL17=2283.7764545,
                NEVT_UL18=2283.69269757,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m1000_w250p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m1000_w250p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m1000_w250p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m1000_w250p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m1000_w250p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m1000_w250p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m1000_w250p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m1000_w250p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },

####################################################################
##    H scalar INT 25%
####################################################################


        "HscalarToTTTo1L1Nu2J_m365_w91p25_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.761555, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.87897, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-170318.50717,
                NEVT_UL16postVFP=-171810.31304,
                NEVT_UL17=-344502.76034,
                NEVT_UL18=-487802.62975,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m365_w91p25_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m365_w91p25_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m365_w91p25_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m365_w91p25_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m365_w91p25_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m365_w91p25_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m365_w91p25_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m400_w100p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.742658, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.8492, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-158971.77207,
                NEVT_UL16postVFP=-168691.582527,
                NEVT_UL17=-337111.85529,
                NEVT_UL18=-335632.73832,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m400_w100p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m400_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m400_w100p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m400_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m400_w100p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m400_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m400_w100p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m400_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m500_w125p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.427226, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.80251, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-97678.856612,
                NEVT_UL16postVFP=-97902.080091,
                NEVT_UL17=-188882.123508,
                NEVT_UL18=-193539.89372,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m500_w125p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m500_w125p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m500_w125p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m500_w125p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m500_w125p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m500_w125p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m500_w125p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m500_w125p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m600_w150p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.187834, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.77723, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-43744.150087,
                NEVT_UL16postVFP=-44496.672295,
                NEVT_UL17=-86039.06483,
                NEVT_UL18=-86085.894465,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m600_w150p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m600_w150p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m600_w150p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m600_w150p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m600_w150p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m600_w150p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m600_w150p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m600_w150p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m800_w200p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.0147037, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.74916, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-3449.2540368,
                NEVT_UL16postVFP=-4074.59180793,
                NEVT_UL17=-7569.7416882,
                NEVT_UL18=-7089.446475,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m800_w200p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m800_w200p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m800_w200p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m800_w200p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m800_w200p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m800_w200p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m800_w200p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m800_w200p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m1000_w250p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0194944, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.73374, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=4328.6188608,
                NEVT_UL16postVFP=3866.5128433,
                NEVT_UL17=8502.5593978,
                NEVT_UL18=8534.8189202,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m1000_w250p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m1000_w250p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m1000_w250p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m1000_w250p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m1000_w250p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m1000_w250p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m1000_w250p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m1000_w250p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },


####################################################################
##    H scalar RES 10%
####################################################################


        "HscalarToTTTo1L1Nu2J_m365_36p5_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0733756, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.36165, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-1,
                NEVT_UL16postVFP=16550.0099108,
                NEVT_UL17=32682.539549,
                NEVT_UL18=33072.517701,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/", XmlSource_UL16preVFP="",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m365_w36p5_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m365_w36p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m365_w36p5_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m365_w36p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m365_w36p5_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m365_w36p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m400_w40p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.134601, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.28741, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=30318.763244,
                NEVT_UL16postVFP=30308.935418,
                NEVT_UL17=60666.94613,
                NEVT_UL18=60389.66898,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m400_w40p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m400_w40p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m400_w40p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m400_w40p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m400_w40p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m400_w40p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m400_w40p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m400_w40p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m500_w50p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.172511, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.17323, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=39022.080062,
                NEVT_UL16postVFP=38888.924959,
                NEVT_UL17=77994.05398,
                NEVT_UL18=78030.369961,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m500_w50p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m500_w50p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m500_w50p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m500_w50p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m500_w50p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m500_w50p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m500_w50p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m500_w50p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m600_w60p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.115724, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.11283, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=26205.193565,
                NEVT_UL16postVFP=26193.54991,
                NEVT_UL17=52100.11534,
                NEVT_UL18=51118.092581,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m600_w60p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m600_w60p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m600_w60p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m600_w60p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m600_w60p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m600_w60p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m600_w60p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m600_w60p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m800_w80p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0381515, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.04663, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=8641.8341922,
                NEVT_UL16postVFP=8643.5531192,
                NEVT_UL17=17186.548258,
                NEVT_UL18=17291.628299,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m800_w80p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m800_w80p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m800_w80p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m800_w80p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m800_w80p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m800_w80p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m800_w80p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m800_w80p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m1000_w100p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0127637, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.01064, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=2893.9334362,
                NEVT_UL16postVFP=2893.8290827,
                NEVT_UL17=5786.270134,
                NEVT_UL18=5751.8822019,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m1000_w100p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m1000_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m1000_w100p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m1000_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m1000_w100p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m1000_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m1000_w100p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m1000_w100p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },

####################################################################
##    H scalar INT 10%
####################################################################


        "HscalarToTTTo1L1Nu2J_m365_36p5_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.941809, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.87898, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-210896.53462,
                NEVT_UL16postVFP=-210239.509572,
                NEVT_UL17=-421755.8942,
                NEVT_UL18=-422050.40195,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m365_w36p5_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m365_w36p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m365_w36p5_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m365_w36p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m365_w36p5_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m365_w36p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m365_w36p5_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m365_w36p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m400_w40p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.936429, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.84921, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-211991.76306,
                NEVT_UL16postVFP=-212560.040131,
                NEVT_UL17=-424753.80961,
                NEVT_UL18=-416737.97976,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m400_w40p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m400_w40p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m400_w40p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m400_w40p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m400_w40p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m400_w40p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m400_w40p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m400_w40p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m500_w50p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.466654, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.80247, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-107012.401862,
                NEVT_UL16postVFP=-109145.38449,
                NEVT_UL17=-212458.66898,
                NEVT_UL18=-215769.226969,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m500_w50p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m500_w50p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m500_w50p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m500_w50p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m500_w50p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m500_w50p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m500_w50p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m500_w50p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m600_w60p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.160288, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.77724, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-37050.257408,
                NEVT_UL16postVFP=-38852.607288,
                NEVT_UL17=-75166.427755,
                NEVT_UL18=-74999.493927,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m600_w60p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m600_w60p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m600_w60p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m600_w60p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m600_w60p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m600_w60p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m600_w60p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m600_w60p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m800_w80p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0234526, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.74918, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=4588.718688,
                NEVT_UL16postVFP=3859.553408,
                NEVT_UL17=9505.6351939,
                NEVT_UL18=9729.5129279,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m800_w80p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m800_w80p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m800_w80p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m800_w80p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m800_w80p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m800_w80p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m800_w80p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m800_w80p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HcalarToTTTo1L1Nu2J_m1000_w100p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0452619, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.73373, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=9766.364654,
                NEVT_UL16postVFP=9822.1785528,
                NEVT_UL17=19995.912164,
                NEVT_UL18=20101.750115,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m1000_w100p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m1000_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m1000_w100p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m1000_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m1000_w100p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m1000_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m1000_w100p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m1000_w100p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },

####################################################################
##    H scalar RES 2.5%
####################################################################


        "HscalarToTTTo1L1Nu2J_m365_w9p125_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.202185, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.36181, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=45455.192162,
                NEVT_UL16postVFP=45490.800092,
                NEVT_UL17=90946.860925,
                NEVT_UL18=88844.529901,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m365_w9p125_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m365_w9p125_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m365_w9p125_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m365_w9p125_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m365_w9p125_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m365_w9p125_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m365_w9p125_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m365_w9p125_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m400_w10p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.54795, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.28735, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=122270.328234,
                NEVT_UL16postVFP=119834.460985,
                NEVT_UL17=241956.114212,
                NEVT_UL18=245091.00191,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m400_w10p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m400_w10p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m400_w10p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m400_w10p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m400_w10p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m400_w10p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m400_w10p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m400_w10p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HcalarToTTTo1L1Nu2J_m500_w12p5_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.770716, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.1733, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=174249.05999,
                NEVT_UL16postVFP=174336.8065,
                NEVT_UL17=348465.2412,
                NEVT_UL18=348466.27838,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m500_w12p5_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m500_w12p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m500_w12p5_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m500_w12p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m500_w12p5_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m500_w12p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m500_w12p5_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m500_w12p5_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m600_w15p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.506278, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.11286, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=112831.104056,
                NEVT_UL16postVFP=114779.796842,
                NEVT_UL17=229209.57815,
                NEVT_UL18=228276.924753,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m600_w15p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m600_w15p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m600_w15p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m600_w15p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m600_w15p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m600_w15p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m600_w15p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m600_w15p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m800_w20p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.158117, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.04658, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=34699.165952,
                NEVT_UL16postVFP=35824.651047,
                NEVT_UL17=71710.15077,
                NEVT_UL18=71697.69614,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m800_w20p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m800_w20p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m800_w20p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m800_w20p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m800_w20p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m800_w20p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m800_w20p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m800_w20p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m1000_w25p0_res" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0500883, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=2.01071, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=11354.2339702,
                NEVT_UL16postVFP=11358.4466789,
                NEVT_UL17=22709.4169,
                NEVT_UL18=22709.2436044,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m1000_w25p0_res_CP5_madgraph_pythia8_Summer20UL16APV_v2.xm", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m1000_w25p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m1000_w25p0_res_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m1000_w25p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m1000_w25p0_res_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m1000_w25p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m1000_w25p0_res_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m1000_w25p0_res_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
####################################################################
##    H scalar INT 2.5%
####################################################################


        "HscalarToTTTo1L1Nu2J_m365_w9p125_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-1.08972, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.87905, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-243891.57659,
                NEVT_UL16postVFP=-244752.00579,
                NEVT_UL17=-484864.87445,
                NEVT_UL18=-487802.62975,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m365_w9p125_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m365_w9p125_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m365_w9p125_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m365_w9p125_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m365_w9p125_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m400_w10p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-1.07602, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.84919, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-240712.32609,
                NEVT_UL16postVFP=-244155.378094,
                NEVT_UL17=-486247.94155,
                NEVT_UL18=-463615.99297,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m400_w10p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m400_w10p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m400_w10p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m400_w10p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m400_w10p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m400_w10p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m400_w10p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m400_w10p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HcalarToTTTo1L1Nu2J_m500_w12p5_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.473926, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.8025, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-108303.190639,
                NEVT_UL16postVFP=-110955.45375,
                NEVT_UL17=-219185.5194,
                NEVT_UL18=-221095.84215,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m500_w12p5_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m500_w12p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m500_w12p5_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m500_w12p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m500_w12p5_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m500_w12p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m500_w12p5_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m500_w12p5_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m600_w15p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=-0.133391, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.77726, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=-28958.368656,
                NEVT_UL16postVFP=-33767.930485,
                NEVT_UL17=-61134.476633,
                NEVT_UL18=-64189.754372,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m600_w15p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m600_w15p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m600_w15p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m600_w15p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m600_w15p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m600_w15p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m600_w15p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m600_w15p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m800_w20p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0478693, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.74916, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=10641.0264321,
                NEVT_UL16postVFP=10966.333264,
                NEVT_UL17=20316.226675,
                NEVT_UL18=19546.6785,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m800_w20p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m800_w20p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m800_w20p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m800_w20p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m800_w20p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m800_w20p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m800_w20p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m800_w20p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },
        "HscalarToTTTo1L1Nu2J_m1000_w25p0_int" : {
            "CrossSection" : XSValues(
                XSec_13TeV=0.0599909, XSecSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "kFactor" : kFactorValues(
                kFac_13TeV=1.73376, kFacSource_13TeV="Provided by DESY group (Alexander Grohsjean)",
            ),
            "NEvents" : NEventsValues(
                NEVT_UL16preVFP=13776.0977588,
                NEVT_UL16postVFP=13125.219647,
                NEVT_UL17=25812.899749,
                NEVT_UL18=26211.349801,
            ),
            "XMLname" : XMLValues(
                Xml_UL16preVFP="RunII_106X_v2/BSM/UL16preVFP/HscalarToTTTo1L1Nu2J_m1000_w25p0_int_CP5_madgraph_pythia8_Summer20UL16APV_v2.xml", XmlSource_UL16preVFP="/HscalarToTTTo1L1Nu2J_m1000_w25p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODAPVv2-106X_mcRun2_asymptotic_preVFP_v11-v2/MINIAODSIM",
                Xml_UL16postVFP="RunII_106X_v2/BSM/UL16postVFP/HscalarToTTTo1L1Nu2J_m1000_w25p0_int_CP5_madgraph_pythia8_Summer20UL16_v2.xml", XmlSource_UL16postVFP="/HscalarToTTTo1L1Nu2J_m1000_w25p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL16MiniAODv2-106X_mcRun2_asymptotic_v17-v2/MINIAODSIM",
                Xml_UL17="RunII_106X_v2/BSM/UL17/HscalarToTTTo1L1Nu2J_m1000_w25p0_int_CP5_madgraph_pythia8_Summer20UL17_v2.xml", XmlSource_UL17="/HscalarToTTTo1L1Nu2J_m1000_w25p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL17MiniAODv2-106X_mc2017_realistic_v9-v2/MINIAODSIM",
                Xml_UL18="RunII_106X_v2/BSM/UL18/HscalarToTTTo1L1Nu2J_m1000_w25p0_int_CP5_madgraph_pythia8_Summer20UL18_v2.xml", XmlSource_UL18="/HscalarToTTTo1L1Nu2J_m1000_w25p0_int_TuneCP5_13TeV-madgraph_pythia8/RunIISummer20UL18MiniAODv2-106X_upgrade2018_realistic_v16_L1v1-v2/MINIAODSIM",
            ),
        },



    }

    def __init__(self, extra_dicts=None):

        if extra_dicts is not None:
            if type(extra_dicts) == dict:
                self.__values_dict.update(extra_dicts)
            elif type(extra_dicts) == list:
                for ed in extra_dicts:
                    self.__values_dict.update(ed)

    def get_value(self, name, energy, year, key, strict=False):
        """Return the value for a given MC sample, energy or year, and information type

        If information is stored for both an energy and a year, the value for the given energy will be preferentially returned.
        If strict checking is turned on the function will raise an error if a given dictionary or piece of information isn't found.
          Otherwise the default value will be returned with no error (i.e. will return 1.0 for kFactors)

        Args:
            name (`str`): The process name for a given MC sample
            energy (`str`): The simulated energy used during production of the MC sample
            year (`str`): The production year of the MC sample
            key (`str`): The type of information being requested. The Options can be found in the __key_field_map.
            strict (`bool`): Whether or not to perform strict checking of the dictionary

        """
        fields = [self.__key_field_map[key][0]+"_"+energy,self.__key_field_map[key][0]+"_"+year]
        if not name in self.__values_dict:
            raise KeyError("ERROR MCSampleValuesHelper::Unknown process \"" + str(name) + "\"")
        if not key in self.__values_dict[name]:
            if strict:
                print(self.__values_dict[name])
                raise KeyError("ERROR MCSampleValuesHelper::The process \"" + str(name) + "\" does not contain a " + str(key) + " tuple")
            else:
                return self.__key_field_map[key][1]
        if not any(f in self.__values_dict[name][key]._fields for f in fields):
            if strict:
                print(self.__values_dict[name][key])
                raise KeyError("ERROR MCSampleValuesHelper::The " + str(key) + " tuple for process \"" + str(name) + "\" does contain the key(s) \"" + str(fields) + "\"")
            else:
                self.__key_field_map[key][1]

        if self.__values_dict[name][key].__getattribute__(fields[0]) != self.__key_field_map[key][1]:
            return self.__values_dict[name][key].__getattribute__(fields[0])
        else:
            return self.__values_dict[name][key].__getattribute__(fields[1])

    def get_xs(self, name, energy, year):
        return self.get_value(name, energy, year, "CrossSection", True)

    def get_nevt(self, name, energy, year):
        return self.get_value(name, energy, year, "NEvents", True)

    def get_br(self, name, energy, year):
        return self.get_value(name, energy, year, "BranchingRatio", False)

    def get_kfactor(self, name, energy, year):
        return self.get_value(name, energy, year, "kFactor", False)

    def get_corr(self, name, energy, year):
        return self.get_value(name, energy, year, "Correction", False)

    def get_xml(self, name, energy, year):
        return self.get_value(name, energy, year, "XMLname", False)

    def get_lumi(self, name, energy, year, kFactor=True, Corrections=False):
        xsec = self.get_xs(name, energy, year)
        xsec *= self.get_br(name, energy, year)
        if kFactor: xsec *= self.get_kfactor(name, energy, year)
        if Corrections: xsec *= self.get_corr(name, energy, year)
        return self.get_nevt(name, energy, year)/xsec

def print_database():
    helper = MCSampleValuesHelper()
    samples = list(MCSampleValuesHelper.__dict__["_MCSampleValuesHelper__values_dict"].keys())
    samples.sort()
    energies = MCSampleValuesHelper.__dict__["_MCSampleValuesHelper__energies"]
    years = MCSampleValuesHelper.__dict__["_MCSampleValuesHelper__years"]
    import re
    run_pattern = re.compile("(?P<run>(Run)+[ABCDEFGH]{1})")

    max_sample_length = max(len(s) for s in samples)

    def banner(text, decorator = "#", line_width = 30):
        print("")
        print(decorator*line_width)
        print("{text:{deco}^{width}s}".format(text=text,deco=decorator,width=line_width))
        print(decorator*line_width)
        print("")

    for energy in energies:
        banner(energy)
        for year in years:
            banner(year)
            for sample in samples:
                run_match = run_pattern.search(sample)
                isData = run_match is not None
                nevt = helper.get_nevt(sample,energy,year)
                lumi = "/" if (isData or nevt<0) else "%10.2g"%helper.get_lumi(sample,energy,year)
                nevt = "%10.2g"%nevt
                print('{sample: <{width}}-> nevt:{nevt: >5}, lumi:{lumi: >5}'.format(sample=sample, width=max_sample_length+3, nevt=nevt, lumi=lumi))
    return 0


if(__name__ == "__main__"):
    import argparse
    parser = argparse.ArgumentParser(description="CrossSectionHelper Database: find and calculate crucial information for your Analysis!")

    parser.add_argument("--print", action="store_true", help="print number of events and calculated luminosity of all samples in database (This is primarily to test the integrety of the database).")

    args = parser.parse_args()

    #if(args.print):
    #    print_database()
