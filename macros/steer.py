import subprocess
import os
import time

from python.ModuleRunner import *
from python.constants import *


"""This macro and guide describes and steers the complete progress of the Zprime analysis."""


#Modify these items, everything else will work. The files given here must already be adapted to new settings in case there are any.
ModuleRunner = ModuleRunner(path_ZPRIMEDIR)

presel_path = ''
output_path = ''
do_puppi_str = ''
if not do_puppi:
    presel_path = presel_path_chs + '/NOMINAL'
    output_path = fullsel_path_chs + '/NOMINAL'
    do_puppi_str = 'false'
else:
    presel_path = presel_path_puppi + '/NOMINAL'
    output_path = fullsel_path_puppi + '/NOMINAL'
    do_puppi_str = 'true'

replace_xml_dict = {}
replace_xml_dict['PRESELdir'] = presel_path
replace_xml_dict['OUTPUTdir'] = output_path
replace_xml_dict['IS_PUPPI']  = do_puppi_str



###      PRESEL for SR
###      =============

# ModuleRunner.CompileModules()
# for key in replace_xml_dict.keys():
#     if not key == 'OUTPUTdir': ModuleRunner.ModifyEntity(name_PRESEL_SR, key, replace_xml_dict[key])
# ModuleRunner.BuildBatch(name_PRESEL_SR)
# ModuleRunner.SubmitBatch(name_PRESEL_SR)
# ModuleRunner.RetrieveLogBatch(name_PRESEL_SR, kill_proc=False)
# ModuleRunner.ResubmitBatch(name_PRESEL_SR)
# ModuleRunner.RetrieveLogBatch(name_PRESEL_SR, kill_proc=False)
# ModuleRunner.SubmitMissingFiles(name_PRESEL_SR)
# ModuleRunner.RetrieveLogBatch(name_PRESEL_SR, kill_proc=True)
# ModuleRunner.AddBatch(name_PRESEL_SR)
# ModuleRunner.CleanUp(name_PRESEL_SR)





### FULL SEL FOR SR

# ModuleRunner.CompileModules()
# for key in replace_xml_dict.keys(): ModuleRunner.ModifyEntity(name_SEL_SR, key, replace_xml_dict[key])
# ModuleRunner.BuildBatch(name_SEL_SR)
# ModuleRunner.SubmitMissingFiles(name_SEL_SR)
# ModuleRunner.RetrieveLogBatch(name_SEL_SR, kill_proc=True)
# ModuleRunner.ForceAddBatch(name_SEL_SR)
# ModuleRunner.AddFiles(name_SEL_SR, True)
# ModuleRunner.CleanUp(name_SEL_SR)



###MACROS FOR SR
# ModuleRunner.CreateMacroPrerequisites()
# ModuleRunner.SetupMacros()
# ModuleRunner.CompileMacros()
# ModuleRunner.RunMacros('CalculateReconstructionQuality')
# ModuleRunner.RunMacros('CalculateChi2Values')
ModuleRunner.RunMacros('ProduceThetaHistograms')
ModuleRunner.RunTheta()
# These need theta to run before executing them
ModuleRunner.RunMacros('PlotLimits')
# ModuleRunner.RunMacros('PlotPostfitDistributions')
ModuleRunner.RunMacros('PlotPostfitParameters')
# Plotter
ModuleRunner.CreateSteerfile(True)
ModuleRunner.RunPlotter(False)
ModuleRunner.RunPlotter(True)
