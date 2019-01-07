import subprocess
import os
import time

from python.ModuleRunner import *


"""This macro and guide describes and steers the complete progress of the LQ->t mu search."""


"""
First of all, the user has to set up the Preselection for the Signal Region. For this, basically two files have to be modified.
1) LQToTopMu/src/LQToTopMuPreselectionModule.cxx
2) LQToTopMu/config/LQToTopMuPreselection.xml
"""

#Modify these items, everything else will work. The files given here must already be adapted to new settings in case there are any.
#path_LQDIR = '/nfs/dust/cms/user/reimersa/CMSSWTEST/CMSSW_8_0_24_patch1/src/UHH2/LQToTopMu'
path_ZPRIMEDIR = '/nfs/dust/cms/user/reimersa/CMSSW_9_4_1/src/UHH2/ZprimeSemiLeptonic'
name_PRESEL_SR = 'ZprimePreselection_Puppi.xml'
name_SEL_SR    = 'ZprimeAnalysis_Puppi.xml'
ModuleRunner = ModuleRunner(path_ZPRIMEDIR)




###      PRESEL for SR
###      =============

# ModuleRunner.CompileModules()
# ModuleRunner.BuildBatch(name_PRESEL_SR)
# ModuleRunner.SubmitBatch(name_PRESEL_SR)
# ModuleRunner.RetrieveLogBatch(name_PRESEL_SR, kill_proc=False)
# ModuleRunner.ResubmitBatch(name_PRESEL_SR)
# ModuleRunner.RetrieveLogBatch(name_PRESEL_SR, kill_proc=False)
# ModuleRunner.SubmitMissingFiles(name_PRESEL_SR)
# ModuleRunner.RetrieveLogBatch(name_PRESEL_SR, kill_proc=True)
# ModuleRunner.AddBatch(name_PRESEL_SR)
# while isThisRunning('hadd'): time.sleep(20)
# ModuleRunner.CleanUp(name_PRESEL_SR)





### FULL SEL FOR SR

# ModuleRunner.CompileModules()
# ModuleRunner.BuildBatch(name_SEL_SR)
# ModuleRunner.SubmitMissingFiles(name_SEL_SR)
# ModuleRunner.RetrieveLogBatch(name_SEL_SR, kill_proc=True)
# ModuleRunner.AddBatch(name_SEL_SR)
ModuleRunner.AddFiles(name_SEL_SR, True)
# while isThisRunning('hadd'): time.sleep(20)
# ModuleRunner.CleanUp(name_SEL_SR)


###MACROS FOR SR
