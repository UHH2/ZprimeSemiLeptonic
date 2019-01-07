import sys, os
import subprocess
import signal
import argparse
import time

if __name__=="__main__":
    # parse input
    parser = argparse.ArgumentParser(description='Run jobs created with sframe_batch.py using sframe_main in parallel.')
    parser.add_argument('workdir', help='sframe_batch.py work directory')
    parser.add_argument('--nice', '-n', default=10, type=int)
    parser.add_argument('--max_jobs', '-m', default=25, type=int)
    args = parser.parse_args()

    if args.nice < -20 or args.nice > 19:
        raise ValueError('niceness has to be within -20 and 19. Exit')

    if args.max_jobs <= 0:
        raise ValueError('Number of jobs has to be positive. Exit')

    print 'Start looking for missing files in {}...'.format(args.workdir)
    with open(args.workdir+'/missing_files.txt') as f:
        jobs  = f.read().splitlines()
        n_jobs = len(jobs)
    print 'Found {:d} missing files. Start running local spawning {:d} parallel jobs with nicecess of {:d}'.format(n_jobs, args.max_jobs, args.nice)

    n_running = 0
    n_completed = 0
    processes = []
    for job in jobs:
        if job == '': continue
        job = job.split()
        arg = args.workdir + '/' + job[-1]
        log_name = arg[:arg.rfind('.')]+'_log.txt'

        b_wait = (n_running >= args.max_jobs)
        while b_wait:
            n_running = 0
            n_completed = 0
            for proc in processes:
                if proc[0].poll() == None: n_running += 1
                else:
                    n_completed += 1
                    if not proc[1].closed:
                        proc[1].close()
                        print 'Job "{}" has finished.'.format(proc[1].name)
            percent = round(float(n_completed)/float(n_jobs)*100, 1)
            sys.stdout.write( '{0:d} of {1:d} ({2:4.2f}%) jobs done.\r'.format(n_completed, n_jobs, percent))
            sys.stdout.flush()
            time.sleep(10)
            b_wait = (n_running >= args.max_jobs)

        print 'Spawning job: {}'.format(arg[:arg.rfind('.')])
        n_running += 1
        f = open(log_name,'w')
        command = ['nice', '-n', str(args.nice), 'sframe_main', arg]
        processes.append((subprocess.Popen(command, stdout=f),f))

    b_wait = (n_completed < n_jobs)
    while b_wait:
        n_running = 0
        n_completed = 0
        for proc in processes:
            if proc[0].poll() == None: n_running += 1
            else:
                n_completed += 1
                if not proc[1].closed:
                    proc[1].close()
                    print 'Job "%s" has finished.' % proc[1].name
        percent = float(n_completed)/float(n_jobs)*100
        sys.stdout.write( '{0:d} of {1:d} ({2:4.2f} %) jobs done.\r'.format(n_completed, n_jobs, percent))
        sys.stdout.flush()
        time.sleep(10)
        b_wait = (n_completed < n_jobs)
    print ''
    print 'Done'
