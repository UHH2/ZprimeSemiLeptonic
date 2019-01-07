import os
import sys
import subprocess
from multiprocessing import Process

from functions import *


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


    def ForceAddBatch(self, filename, sys = '', direction = ''):
        if sys == '':
            RunBatch(self.path, filename, 'f')
        else:
            name = filename[:len(filename)-4] + '_' + sys + '_' + direction + '.xml'
            RunBatch(self.path, name, 'f')


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


    def ModifyEntity(self, filename, entityname, replaceby, postfix):
        lines = get_lines(self.path+'/config/', filename)
        lines = modify_xml_entity(lines, entityname, replaceby)
        write_lines(self.path+'/config/', filename[:len(filename)-4]+'_'+postfix+'.xml', lines)


    def ModifyItemValue(self, filename, itemname, newval, postfix):
        lines = get_lines(self.path+'/config/', filename)
        lines = modify_xml_item(lines, itemname, newval)
        write_lines(self.path+'/config/', filename[:len(filename)-4]+'_'+postfix+'.xml', lines)


    def CreateSystXMLFiles(self, filename, systematics, dictionary, outdirname):
        fullnames = []
        fullsysts = []
        for syst in systematics:
            #if syst in ['JEC', 'JER']: continue
            if syst == 'NOMINAL':
                fullsysts.append(syst)
            elif 'SCALE' not in syst:
                for direction in ['up', 'down']:
                    fullsysts.append(syst+'_'+direction)
            else:
                for direction in ['upup', 'upnone', 'noneup', 'nonedown', 'downnone', 'downdown']:
                    fullsysts.append(syst+'_'+direction)

        outpath = self.path+'/config/'+outdirname+'/'
        if os.path.exists(outpath):
            raise RuntimeError('Outdir %s already exists. Abort.' % (outpath))
        else:
            os.mkdir(outpath)
        """
        #first of all: JEC, JER
        if 'JEC' in systematics:
            lines = create_syst_lines_JECJER(self.path + '/config/', filename, 'JEC', 'up')
            #write_lines(outpath, filename[:len(filename)-4]+'_JEC_up.xml', lines)
            lines = create_syst_lines_JECJER(self.path + '/config/', filename, 'JEC', 'down')
            #write_lines(outpath, filename[:len(filename)-4]+'_JEC_down.xml', lines)
        if 'JER' in systematics:
            lines = create_syst_lines_JECJER(self.path + '/config/', filename, 'JER', 'up')
            #write_lines(outpath, filename[:len(filename)-4]+'_JER_up.xml', lines)
            lines = create_syst_lines_JECJER(self.path + '/config/', filename, 'JER', 'down')
            #write_lines(outpath, filename[:len(filename)-4]+'_JER_down.xml', lines)
        """

        #now follow the instructions from the dict.
        # 1) modify output entity
        for syst in fullsysts:
            if syst == 'JEC_up':
                lines = create_syst_lines_JECJER(self.path + '/config/', filename, 'JEC', 'up')
            elif syst == 'JEC_down':
                lines = create_syst_lines_JECJER(self.path + '/config/', filename, 'JEC', 'down')
            elif syst == 'JER_up':
                lines = create_syst_lines_JECJER(self.path + '/config/', filename, 'JER', 'up')
            elif syst == 'JER_down':
                lines = create_syst_lines_JECJER(self.path + '/config/', filename, 'JER', 'down')
            else:
                lines = get_lines(self.path+'/config/', filename)
                entval = get_xml_entity(lines, 'SELdir')
                newentval = entval.replace('NOMINAL', syst)
                lines = modify_xml_entity(lines, 'SELdir', newentval)

            # 1.1) Set JobConfig path
            newlines = []
            for line in lines:
                if not '<!DOCTYPE JobConfiguration PUBLIC "" "JobConfig.dtd"[' in line:
                    newlines.append(line)
                else:
                    newlines.append('<!DOCTYPE JobConfiguration PUBLIC "" "../JobConfig.dtd"[')
            lines = newlines

            # 2) go through dict and follow instructions
            todo = dictionary[syst]
            for key in todo:
                # key contains the item name, todo[key] contains the new value
                lines = modify_xml_item(lines, key, todo[key])

            # 3) write a new file with these lines to an extra directory
            write_lines(outpath, filename[:len(filename)-4]+'_'+syst+'.xml', lines)
            fullname = outpath+filename[:len(filename)-4]+'_'+syst+'.xml'
            fullnames.append(fullname)
        return fullnames


    def RunSystJobsLocal(self, listofxmlfiles):
        processes = []
        logfiles = []
        ntotal = len(listofxmlfiles)
        for xmlfilename in listofxmlfiles:
            #print xmlfilename
            shortname = xmlfilename[len(self.path+'/config/'):]
            #print shortname
            self.MakeOutDir(shortname)
            wait = True
            while wait:
                nrunning = 0
                ncompleted = 0
                idx=0
                for proc in processes:
                    if proc.poll() == None : nrunning += 1
                    else:
                        ncompleted += 1
                        if not logfiles[idx].closed:
                            logfiles[idx].close()
                            print 'Job "%s" has finished.' % logfiles[idx].name
                    idx += 1
                if nrunning >= 25:
                    percentage = float(ncompleted)/float(ntotal)*100
                    sys.stdout.write( 'Already completed '+str(ncompleted)+' out of '+str(ntotal)+' jobs --> '+str(percentage)+'%. Currently running: '+str(nrunning)+' \r')
                    sys.stdout.flush()
                    time.sleep(10)
                else:
                    print 'only %i jobs are running, going to spawn new ones.' % nrunning
                    wait = False
            #command = 'sframe_main ' + xmlfilename
            command = ['sframe_main', xmlfilename]
            logfilename = xmlfilename[:len(xmlfilename)-4]+'_log.txt'
            f = open(logfilename,'w')
            logfiles.append(f)
            processes.append(subprocess.Popen(command, shell=False, stdout=f))
            #print ('Executing sframe_main %s' % (xmlfilename))
            #processes.append(subprocess.Popen(['sframe_main', xmlfilename],  shell=True))
            """ """
        for proc in processes:
            print 'Now waiting for missing jobs to finish.'
            proc.wait()



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


    def PrepareBTagSF(self, filename, switch_btag_off):
        #First the Module
        prepare_module_btagsf(self.path, filename, switch_btag_off)


    def CreateSCALEDirs(self, filename, systematics):
        outdir_base = out_dir(self.path, filename)
        outdir_base = outdir_base[:len(outdir_base)-len('/NOMINAL')]
        dirs_to_create = []
        for syst in systematics:
            if 'SCALE' in syst:
                dirs_to_create.append(outdir_base+'/'+syst+'_up')
                dirs_to_create.append(outdir_base+'/'+syst+'_down')

        createdirs = []
        for mydir in dirs_to_create:
            outdir = mydir
            while not os.path.exists(outdir):
                createdirs[:0] = [outdir]
                split_dir = outdir.split('/')
                outdir = ''
                for i in range(len(split_dir)-2):
                    outdir += '/'
                    outdir = outdir+split_dir[i+1]

        for directory in createdirs:
            if os.path.exists(directory):
                print 'Outdir %s already exists. Not creating it.' % outdir
            else :
                os.mkdir(directory)
                print 'created directory %s' % directory
