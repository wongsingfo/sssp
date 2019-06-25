from __future__ import print_function
import os
import sys
import shutil

home = "/home/gluo/nas/teaching/pdc2019/s1700012753"
submit = os.path.join(home, "ch9-1.1/solvers/mlb-dimacs/sq.exe")
submit = os.path.join(home, "code", "main")
logfile = os.path.join(home, "bin", "log.res")

if len(sys.argv) == 3: 
	submit = os.path.join(home, "code", sys.argv[1])
	logfile = os.path.join(home, "bin", sys.argv[2] + ".res")


try: os.remove(logfile)
except: pass

os.chdir(os.path.join(home, 'ch9-1.1/scripts'))
for script in ['USA-road-d', 'USA-road-t']: 

    os.system('sed "s/..\\/solvers\\/mlb-dimacs\\/sq.exe/{}/" < run{}.ss.pl | perl 2>>{}'
        .format(submit.replace('/', '\\/'),
                script,
                logfile))

    resfile = os.path.join(home, "bin", "{}.ss.res".format(script))
    reffile = os.path.join(home, "bin/checksum", "{}.ss.res".format(script))
    shutil.copyfile("../results/{}.ss.res".format(script),  resfile)

    os.system("echo line diff: ")
    os.system('diff {} {} | wc -l'.format(resfile, reffile))

os.system('cat {}'.format(logfile))

