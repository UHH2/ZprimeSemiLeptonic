import os
import sys
import subprocess
import time
import signal
import ROOT

from multiprocessing import Process
from multiprocessing import Pool


"""handy little functions"""

#check wether or not the workdir used by sframe_batch already exists in /config and in the target dir
def check_workdir(path, filename):
    configfile = open(path + filename,'r')
    lines = configfile.readlines()
    for line in lines:
        if '<ConfigSGE' in line:
            confs = line.split()
            for conf in confs:
                if 'Workdir' in conf:
                    workdirname = conf.split('"')[1]
                    #print workdirname
        if '<!ENTITY TargetLumi' in line:
            lumi = line.split('"')[1]
            #print lumi
        if '<!ENTITY PRESELdir' in line:
            outputconf = line.split('"')[1]
            #print outputconf
            outputdir = outputconf.replace('&TargetLumi;', str(lumi))
            #print outputdir
    path_to_check1 = outputdir+'/'+workdirname
    if os.path.isdir(path_to_check1):
        #print 'workdir "%s" already exists, please remove it before trying again' % path_to_check1
        return False
    path_to_check2 = path+workdirname
    if os.path.isdir(path_to_check2):
        #print 'workdir "%s" already exists, please remove it before trying again' % path_to_check2
        return False
    return True

def check_treeexists(filename,treename):
     rootfile = ROOT.TFile.Open(filename)
     if treename!='AnalysisTree':
          raise ValueError('treename is not \'AnalysisTree\'')
     try:
          entries = rootfile.AnalysisTree.GetEntriesFast()
          # print filename,' entries: ',entries,entries>0
          return  entries>0
     except:
          # print 'tree '+treename+' in file '+filename+' has ==0 entries: '
          return False

def hadd_files(dottbar):
    commands = {
                'uhh2.AnalysisModuleRunner.DATA.DATA_blinded.root' : 'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_Run*_blinded.root',
                'uhh2.AnalysisModuleRunner.DATA.DATA.root' : 'uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_RunB.root uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_RunC.root uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_RunD.root uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_RunE.root uhh2.AnalysisModuleRunner.DATA.DATA_SingleMuon_RunF.root',
                'uhh2.AnalysisModuleRunner.MC.DYJets.root' : 'uhh2.AnalysisModuleRunner.MC.DYJets_*Jets.root',
                'uhh2.AnalysisModuleRunner.MC.ST.root' : 'uhh2.AnalysisModuleRunner.MC.ST_*.root',
                'uhh2.AnalysisModuleRunner.MC.WJets.root' : 'uhh2.AnalysisModuleRunner.MC.WJets_*Jets.root',
                'uhh2.AnalysisModuleRunner.MC.WJets_B.root' : 'uhh2.AnalysisModuleRunner.MC.WJets_*Jets_B.root',
                'uhh2.AnalysisModuleRunner.MC.WJets_C.root' : 'uhh2.AnalysisModuleRunner.MC.WJets_*Jets_C.root',
                'uhh2.AnalysisModuleRunner.MC.WJets_L.root' : 'uhh2.AnalysisModuleRunner.MC.WJets_*Jets_L.root',
                'uhh2.AnalysisModuleRunner.MC.QCD_Mu.root' : 'uhh2.AnalysisModuleRunner.MC.QCD_Mu_*.root'};
    if dottbar: commands['uhh2.AnalysisModuleRunner.MC.TTbar.root'] = 'uhh2.AnalysisModuleRunner.MC.TTbar_*.root'

    processes = []
    for key in commands.keys():
        command = 'ls ' + key + ' ' + commands[key]
        thisproc = subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE)
        tuple = thisproc.communicate()
        list = tuple[0].split('\n')[:-1]
        if key in list: list.remove(key)
        # print list

        string = ''
        position = -1
        command = 'nice -n 10 hadd -f ' + key
        for i in range(len(list)):
            if check_treeexists(list[i],'AnalysisTree') and position ==-1:
                position = i
                string+=str(list[i])
                break

        for i in range(len(list)):
            if not position == i and not position == -1:
                string += ' '+str(list[i])
            elif position ==-1:
                string += str(list[i])
                position = 0

        # print string
        command += ' ' + string + ' > hadd.log'
        # print command
        processes.append(subprocess.Popen(command, shell=True, stdout=subprocess.PIPE, stderr=subprocess.PIPE))

    for proc in processes:
        proc.wait()

    os.remove('hadd.log')
    print 'Done adding all files!'


def RunBatch(path, filename, options='', terminate=False):
    cwd = os.getcwd()
    os.chdir(path+'/config')
    if not (check_workdir(path+'/config/',filename) and options == 's'):
        if options == '':
            command = 'sframe_batch.py ' + filename
        else:
            command = 'sframe_batch.py -' + options + ' ' + filename
        process = subprocess.Popen(command, shell=True, preexec_fn=os.setsid)
        if terminate:
            time.sleep(60)
            print "Waited long enough, killing process."
            os.killpg(os.getpgid(process.pid), signal.SIGTERM)
        else:
            #kill after 3h max.
            start = time.time()
            wait = True
            while wait:
                if process.poll() != None:
                    wait = False
                else:
                    waitfor = 11000
                    if options == '':
                        waitfor = 120
                    if time.time() - start < waitfor:
                        time.sleep(60)
                    else:
                        os.killpg(os.getpgid(process.pid), signal.SIGTERM)
    else:
        print 'You used option "-s", but the workdir already exists. Please remove it first.'
    os.chdir(cwd)

def find_workdir_name(path, filename):
    configfile = open(path+filename,'r')
    lines = configfile.readlines()
    new_lines = []
    for line in lines:
        if '<ConfigSGE' in line:
            workdir = (line.split(' ')[5]).split('"')[1]
            return workdir


def submit_missing(path, filename, nice=10, maxjobs=25):

    if nice < -20 or nice > 19:
        raise ValueError('niceness has to be within -20 and 19. Exit')
    if maxjobs <= 0:
        raise ValueError('Number of jobs has to be positive. Exit')

    cwd = os.getcwd()
    os.chdir(path+'/config/')
    workdir = find_workdir_name(path+'/config/', filename)
    txtfile = open(path+'/config/'+workdir+'/missing_files.txt','r')
    lines = txtfile.readlines()
    ntotal = len(lines)
    processes = []
    nrunning = 0
    ncompleted = 0
    for line in lines:
        if line == '': break
        line = line.split('\n')[0]
        command = line.split('  ')[1]
        wait = (nrunning >= maxjobs)
        while wait:
            nrunning = 0
            ncompleted = 0
            for proc in processes:
                if proc[0].poll() == None : nrunning += 1
                else:
                    ncompleted += 1
                    if not proc[1].closed:
                        proc[1].close()
                        print 'Job with logfile {} has finished.'.format(proc[1].name[proc[1].name.rfind('/')+1:proc[1].name.rfind('.')])

            percent = round(float(ncompleted)/float(ntotal)*100, 1)
            sys.stdout.write( '{0:d} of {1:d} ({2:4.2f}%) jobs done.\r'.format(ncompleted, ntotal, percent))
            sys.stdout.flush()
            time.sleep(10)
            wait = (nrunning >= maxjobs)

        xmlfilename = path+'/config/'+workdir + '/' + command.split(' ')[1]
        logfilename = xmlfilename[:xmlfilename.rfind('.')]+'_log.txt'
        print 'Spawning job: {}'.format(command.split(' ')[1][:command.split(' ')[1].rfind('.')])
        nrunning += 1
        f = open(logfilename,'w')
        command = ['nice', '-n', str(nice),'sframe_main', xmlfilename]
        processes.append((subprocess.Popen(command, stdout=f),f))

    wait = (ncompleted < ntotal)
    while wait:
        nrunning = 0
        ncompleted = 0
        for proc in processes:
            if proc[0].poll() == None: nrunning += 1
            else:
                ncompleted += 1
                if not proc[1].closed:
                    proc[1].close()
                    # print 'Job "%s" has finished.' % proc[1].name
                    print 'Job with logfile {} has finished.'.format(proc[1].name[proc[1].name.rfind('/')+1:proc[1].name.rfind('.')])
        percent = float(ncompleted)/float(ntotal)*100
        sys.stdout.write( '{0:d} of {1:d} ({2:4.2f} %) jobs done.\r'.format(ncompleted, njobs, percent))
        sys.stdout.flush()
        time.sleep(10)
        wait = (ncompleted < njobs)
    print ''
    print 'Done'
    os.chdir(cwd)


def delete_workdir(path, filename):
    cwd = os.getcwd()
    os.chdir(path+'/config/')
    workdir = find_workdir_name(path+'/config/', filename)
    processes1 = []
    command1 = 'rm -rf '
    command1 += workdir
    # print command1
    processes1.append(subprocess.Popen(command1, shell=True))
    for proc in processes1:
        proc.wait()


    configfile = open(path + '/config/' + filename,'r')
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

    print 'outputdir is: ', outputdir
    os.chdir(outputdir)
    command2 = 'rm -rf '
    command2 += workdir
    processes2 = []
    # print command2
    processes2.append(subprocess.Popen(command2, shell=True))
    for proc in processes2:
        proc.wait()

    os.chdir(cwd)

def get_lines(path, filename):
    infile = open(path+filename, 'r')
    lines = infile.readlines()
    infile.close()
    return lines


def write_lines(path, filename, lines):
    outfile = open(path+filename, 'w')
    for line in lines:
        outfile.write(line)
    outfile.close()


def get_xml_entity(lines, entityname):
    check_for = '<!ENTITY '
    check_for += entityname
    nfound = 0
    for line in lines:
        if check_for in line:
            parts = line.split('"')
            value = parts[1]
            nfound += 1

    if nfound == 0:
        raise RuntimeError('Did not find specified ENTITY Name. Abort.')
    elif nfound > 1:
        raise RuntimeError('Found ENTITY Name more than once. Abort.')

    return value


def modify_xml_entity(lines, entityname, replaceby):
    check_for = '<!ENTITY '
    check_for += entityname
    new_lines = []
    nmod = 0
    for line in lines:
        if check_for in line:
            parts = line.split('"')
            new_line = parts[0] + '"' + replaceby + '"' + parts[2]
            nmod += 1
        else:
            new_line = line

        new_lines.append(new_line)
    if nmod == 0:
        raise RuntimeError('Did not find specified ENTITY Name. Abort.')
    return new_lines


def modify_xml_item(lines, itemname, newval):
    check_for = '<Item'
    new_lines = []
    nmod = 0
    for line in lines:
        if check_for in line: #this line is a potential candidate. Next search for the item name
            parts = line.split('"')
            name = parts[1]
            if name == itemname: #found correct line. Now modify the value to 'newval'
                new_line = parts[0] + '"' + parts[1] + '"' + parts[2] + '"' + newval + '"' + parts[4]
                nmod += 1
            else:
                new_line = line
        else:
            new_line = line

        new_lines.append(new_line)
    if nmod == 0:
        raise RuntimeError('Did not find specified Item Name. Abort.')
    return new_lines


def out_dir(path, filename):
    configfile = open(path + '/config/' + filename,'r')
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
    return outputdir


def isThisRunning( process_name ):

    tmp = os.popen("ps -eF").readlines()
    count = 0
    for line in tmp:
        if line[:len('reimersa')] == 'reimersa':
            if process_name in line:
                count += 1
    if count > 0: return True
    else: return False


def is_commented(line):
    #get rid of whitespace
    beginning = line.split()[0]

    #if first two chars of beginning is '//', the line is commented, else it is not
    if beginning[0:2] == '//': return True
    else: return False


def number_leading_whitespace(line):
    n = 0
    while line[n] == ' ':
        n += 1
    return n


def comment_line(line):
    if is_commented(line):
        print 'Warning: This line is already commented.'
        return line
    else: return '//' + line


def uncomment_line(line):
    if not is_commented(line):
        print 'Warning: This line is already uncommented.'
        return line
    else:
        n = number_leading_whitespace(line)
        newline = line[0:n]
        newline += line[n+2:]
        return newline

def create_path(path):
    if os.path.isdir(path):
        print 'path "%s" already exists, not creating it.' % (path)
    else:
        os.makedirs(path)
        print 'Created path "%s"' % (path)
