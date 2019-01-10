
do_puppi = True
preseltag = '2017_Moriond19JEC'
tag = preseltag + '_looserselection'

path_ZPRIMEDIR = '/nfs/dust/cms/user/reimersa/CMSSW_9_4_1/src/UHH2/ZprimeSemiLeptonic'
name_PRESEL_SR = 'ZprimePreselection_Puppi.xml'
name_SEL_SR    = 'ZprimeAnalysis_Puppi.xml'

presel_path_puppi = '/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Preselection/' + preseltag + '_Puppi'
presel_path_chs = '/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Preselection/' + preseltag
fullsel_path_puppi = '/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/' + tag + '_Puppi'
fullsel_path_chs = '/nfs/dust/cms/user/reimersa/ZprimeSemiLeptonic/94X_v1/Fullselection/' + tag
path_theta = '/nfs/dust/cms/user/reimersa/theta_Zprime/utils2/' + tag + '/'
path_theta_to_copy_from = '/nfs/dust/cms/user/reimersa/theta_Zprime/utils2/Limits_MC/'
path_plotter = '/nfs/dust/cms/user/reimersa/SFramePlotter/'
steerfilename = 'Zprime/Fullselection_blinded.steer'

signalmasses = [500, 750, 1000, 1250, 1500, 2000, 2500, 3000, 3500, 4000, 4500, 5000, 5500, 6000, 6500, 7000, 7500, 8000]
