import os
import sys
import subprocess
from multiprocessing import Process

from functions import *
from constants import *


#This file contains aaaaall the fancy functions and classes to clean up the steer.py code


class ModuleRunner:

    def __init__(self, path):
        self.path = path


    def CompileModules(self):
        cwd = os.getcwd()
        os.chdir(self.path);
        process = subprocess.Popen("make -j", shell=True)
        process.wait()
        os.chdir(cwd)

    def RunLocal(self, filename):
        cwd = os.getcwd()
        os.chdir(self.path+'/config')
        command = 'sframe_main '+filename
        process = subprocess.Popen(command, shell=True)
        process.wait()
        os.chdir(cwd)

    def BuildBatch(self, filename, sys = '', direction = ''):
        if sys == '':
            RunBatch(self.path, filename)
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            RunBatch(self.path, name)

    def SubmitBatch(self, filename, sys = '', direction = ''):
        if sys == '':
            RunBatch(self.path, filename, 's')
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            RunBatch(self.path, name, 's')

    def RetrieveLogBatch(self, filename, sys = '', direction = '', kill_proc = False):
        if sys == '':
            RunBatch(self.path, filename, 'l', kill_proc)
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            RunBatch(self.path, name, 'l', kill_proc)

    def ResubmitBatch(self, filename, sys = '', direction = ''):
        if sys == '':
            RunBatch(self.path, filename, 'r')
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            RunBatch(self.path, name, 'r')


    def AddBatch(self, filename, sys = '', direction = ''):
        if sys == '':
            RunBatch(self.path, filename, 'a')
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            RunBatch(self.path, name, 'a')
        time.sleep(10)
        self.WaitForProcess('hadd')


    def ForceAddBatch(self, filename, sys = '', direction = ''):
        if sys == '':
            RunBatch(self.path, filename, 'f')
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            RunBatch(self.path, name, 'f')
        time.sleep(10)
        self.WaitForProcess('hadd')



    #adds files that were produced with a given .xml file (like the SPlotter)
    def AddFiles(self, filename, dottbar, syst=''):
        cwd = os.getcwd()
        configfile = open(self.path + '/config/' + filename,'r')
        lines = configfile.readlines()
        for line in lines:
            if '<!ENTITY TargetLumi' in line:
                lumi = line.split('"')[1]
            if '<!ENTITY PRESELdir' in line and 'Preselection' in filename:
                outputconf = line.split('"')[1]
                outputdir = outputconf.replace('&TargetLumi;', str(lumi))
            elif '<!ENTITY OUTPUTdir' in line and 'Analysis' in filename:
                outputconf = line.split('"')[1]
                outputdir = outputconf.replace('&TargetLumi;', str(lumi))

        if syst != '':
            outputdir = outputdir.replace('NOMINAL', syst)
        print 'outputdir is: ', outputdir
        os.chdir(outputdir)
        hadd_files(dottbar)
        os.chdir(cwd)


    def AddFilesWithSyst(self, filename, dottbar, systematics=[]):
        do_for_syst = []
        for syst in systematics:
            if 'SCALE' not in syst and syst!='NOMINAL':
                do_for_syst.append(syst + '_up')
                do_for_syst.append(syst + '_down')
            elif 'SCALE' in syst:
                do_for_syst.append(syst + '_upup')
                do_for_syst.append(syst + '_downdown')
                do_for_syst.append(syst + '_upnone')
                do_for_syst.append(syst + '_noneup')
                do_for_syst.append(syst + '_downnone')
                do_for_syst.append(syst + '_nonedown')
            elif syst == 'NOMINAL':
                do_for_syst.append(syst)

        for syst in do_for_syst:
            self.AddFiles(filename, dottbar, syst)


    def create_JECJER_xmlfiles(self, filename):
        cwd = os.getcwd()
        proc = [Process(target=create_syst_file_JECJER, args=(self.path + '/config/', filename, 'JEC', 'up')),
                Process(target=create_syst_file_JECJER, args=(self.path + '/config/', filename, 'JEC', 'down')),
                Process(target=create_syst_file_JECJER, args=(self.path + '/config/', filename, 'JER', 'up')),
                Process(target=create_syst_file_JECJER, args=(self.path + '/config/', filename, 'JER', 'down'))]
        run_parallel(proc)
        os.chdir(cwd)


    def SubmitMissingFiles(self, filename, sys = '', direction = ''):
        if sys == '':
            submit_missing(self.path, filename)
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            submit_missing(self.path, name)


    def CleanUp(self, filename, sys = '', direction = ''):
        if sys == '':
            delete_workdir(self.path, filename)
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            delete_workdir(self.path, name)


    def ModifyEntity(self, filename, entityname, replaceby, postfix=''):
        lines = get_lines(self.path+'/config/', filename)
        lines = modify_xml_entity(lines, entityname, replaceby)
        if not postfix=='': write_lines(self.path+'/config/', filename[:len(filename)-4]+'_'+postfix+'.xml', lines)
        else: write_lines(self.path+'/config/', filename+'', lines)


    def ModifyItemValue(self, filename, itemname, newval, postfix):
        lines = get_lines(self.path+'/config/', filename)
        lines = modify_xml_item(lines, itemname, newval)
        write_lines(self.path+'/config/', filename[:len(filename)-4]+'_'+postfix+'.xml', lines)


    def MakeOutDir(self, filename):
        outdir = out_dir(self.path, filename)
        dirs_to_create = []
        if os.path.exists(outdir):
            print 'Outdir %s already exists. Not creating it.' % outdir
        while not os.path.exists(outdir):
            dirs_to_create[:0] = [outdir]
            split_dir = outdir.split('/')
            outdir = ''
            for i in range(len(split_dir)-2):
                outdir += '/'
                outdir = outdir+split_dir[i+1]
        for directory in dirs_to_create:
            os.mkdir(directory)
            print 'created directory %s' % directory

    def WaitForProcess(self, proc):
        wait = isThisRunning(proc)
        while wait:
            time.sleep(10)
            wait = isThisRunning(proc)

    def CreateMacroPrerequisites(self):
        outdir = out_dir(path_ZPRIMEDIR, name_SEL_SR)
        path_to_create = outdir + '/Plots/SingleEPS'
        create_path(path_to_create)
        create_path(path_theta + 'input')
        create_path(path_theta + 'output')
        create_path('Plots/' + tag + '/CHSPuppiComparison')

        processes = []
        command = 'cp ' + path_theta_to_copy_from + '{limits_mc.py,limits_mc_puppi.py} ' + path_theta
        # print command
        processes.append(subprocess.Popen(command, shell=True))
        for p in processes:
            p.wait()

    def SetupMacros(self):

        #Get Tools.cc lines
        lines = get_lines('src/', 'Tools.cc')
        newlines = []
        for line in lines:
            newline = ''
            if 'base_path_puppi' in line:
                parts = line.split('"')
                newline = parts[0] + '"' + fullsel_path_puppi + '"' + parts[2]
            elif 'base_path_chs' in line:
                parts = line.split('"')
                newline = parts[0] + '"' + fullsel_path_chs + '"' + parts[2]
            elif 'path_theta' in line:
                parts = line.split('"')
                newline = parts[0] + '"' + path_theta + '"' + parts[2]
            elif 'tag = ' in line:
                parts = line.split('"')
                newline = parts[0] + '"' + tag + '"' + parts[2]
            elif 'signalmasses = {' in line:
                parts = line.split('=')
                newline = parts[0] + '= {'
                for i in range(len(signalmasses)):
                    if i < len(signalmasses)-1: newline += str(signalmasses[i]) + ', '
                    else: newline += str(signalmasses[i]) + '};\n'
            else: newline = line
            newlines.append(newline)
        write_lines('src/', 'Tools.cc', newlines)



    def CompileMacros(self):
        processes = []
        command = 'make'
        processes.append(subprocess.Popen(command, shell=True))
        for p in processes:
            p.wait()
        print 'Compiled macros!'


    def RunMacros(self, function):
        processes = []
        command = './main ' + function
        if do_puppi: command += ' true'
        else: command += ' false'
        # print command
        processes.append(subprocess.Popen(command, shell=True))
        for p in processes:
            p.wait()

    def RunTheta(self):
        name_exec = 'limits_mc_puppi'
        if not do_puppi: name_exec = 'limits_mc'
        # 'eval `scramv1 runtime -sh`' is what 'cmsenv' is an alias for!
        command = 'cd /nfs/dust/cms/user/reimersa/CMSSW_8_0_8_patch1/src; '
        command += 'eval `scramv1 runtime -sh`; '
        command += 'cd ' + path_theta + '; '
        command += './../theta-auto.py ' + name_exec + '.py; '
        command += 'rm -rf ' + name_exec
        print 'executing theta now'
        logfilename = path_theta + 'theta_output.log'
        logfile = open(logfilename,'w')
        proc = subprocess.Popen(command, shell=True, stdout=logfile, stderr=logfile)
        proc.wait()
        print 'theta finished!'

    def CreateSteerfile(self, do_singleeps):
        filename = steerfilename[:steerfilename.rfind('.')] + '_template.steer'
        # print filename
        lines = get_lines(path_plotter, filename)
        inpath = fullsel_path_puppi
        if not do_puppi: inpath = fullsel_path_chs
        newlines = []
        for line in lines:
            # print line
            if 'fCycleName' in line:
                parts = line.split('"')
                newline = parts[0] + '"' + inpath + '/NOMINAL/uhh2.AnalysisModuleRunner"' + parts[2]
            elif 'fOutputPsFile' in line:
                parts = line.split('"')
                if not do_singleeps: newline = parts[0] + '"' + inpath + '/NOMINAL/Plots/Plots_blinded.ps"' + parts[2]
                else: newline = parts[0] + '"' + inpath + '/NOMINAL/Plots/SingleEPS/Plots_blinded.ps"' + parts[2]
            elif 'bSingleEPS' in line:
                parts = line.split('=')
                newline = parts[0] + '= '
                if do_singleeps: newline += 'true;\n'
                else: newline += 'false;\n'
            else:
                newline = line
            newlines.append(newline)

        write_lines(path_plotter, steerfilename, newlines)

    def RunPlotter(self, do_singleeps):
        self.CreateSteerfile(do_singleeps)
        command = 'cd /nfs/dust/cms/user/reimersa/CMSSW_8_0_24_patch1/src; '
        command += 'eval `scramv1 runtime -sh`; '
        command += 'cd ' + path_plotter + '; '
        command += 'make; '
        command += 'Plots -f Zprime/Fullselection_blinded.steer'
        print 'executing plotter'
        # print command
        logfilename = path_plotter + 'plotter_output.log'
        logfile = open(logfilename,'w')
        proc = subprocess.Popen(command, shell=True, stdout=logfile, stderr=logfile)
        proc.wait()
        print 'plotter finished!'
