import os
import sys
import subprocess
import time
import signal
from multiprocessing import Process
from multiprocessing import Pool

if len(sys.argv) != 2: raise ValueError('Didn\'t pass exactly one additional argument (which should be the workdir-string) to the script! Exit.')
workdirname = sys.argv[1]
txtfile = open(workdirname+'/missing_files.txt','r')
lines = txtfile.readlines()
ntotal = len(lines)
processes = []
logfiles = []
for line in lines:
    if line == '': break
    line = line.split('\n')[0]
    command = line.split('  ')[1]
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
            # print 'only %i jobs are running, going to spawn new ones.' % nrunning
            wait = False

    xmlfilename = workdirname + '/' + command.split(' ')[1]
    logfilename = xmlfilename[:len(xmlfilename)-4]+'log.txt'
    print 'Spawning job: %s' % xmlfilename[:len(xmlfilename)-4]
    f = open(logfilename,'w')
    logfiles.append(f)
    command = ['sframe_main', xmlfilename]
    processes.append(subprocess.Popen(command, stdout=f))

for proc in processes:
    proc.wait()
