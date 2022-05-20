import sys, time, argparse, subprocess, os.path, pathlib, shutil

Description = """ Tool for identifying repeats in DNA strings

For example
    {exe} example.txt -o output -3 -4
will produce the files output.one and output.two
with the type 1 and type 2 repeats, respectively

--------------------------
Command line options:
--------------------------
""".format(exe=sys.argv[0])

gsufsort_exe = 'external/gsufsort/gsufsort'
repeat_exe = './repeat-dna'

def main():
    parser = argparse.ArgumentParser(description=Description, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('input',      help='input file name', type=str, nargs='+')
    parser.add_argument('-o','--out', help='output base name (def. input base name)', default="", type=str)  
    parser.add_argument('-s','--size', help='minimum repeat size', default=-1, type=int)
    parser.add_argument('-1', '--p1', help='print 1: repeats', action='store_true',default=True)
    parser.add_argument('-2', '--p2', help='print 2: number of repeats', action='store_true')
    #parser.add_argument('-3', '--p3', help='print 3: repeats type 1', action='store_true')
    #parser.add_argument('-4', '--p4', help='print 4: repeats type 2', action='store_true')
    parser.add_argument('-v',         help='verbose: extra info in the log file',action='store_true')
    args = parser.parse_args()
    
    define_basename(args)

    logfile_name = args.basename + ".repeat.log"
    path = os.path.split(sys.argv[0])[0]
    print("Sending logging messages to file:", logfile_name)

    with open(logfile_name,"a") as logfile:
        print(">>> Begin computation",file=logfile)
        show_command_line(logfile)
        logfile.flush()
        step1(path, logfile)
        if(args.p2): 
            args.p1 = False
        #if(args.p3): 
          #  args.p1 = args.p2 = args.p4 = False
        #if(args.p4): 
           # args.p1 = args.p2 = args.p3 = False
        ##

        if(args.p1):
            print(">>> print 1: repeats",file=logfile) 
            print("\n>>> print 1: repeats")
            p_op = 1
        if(args.p2):
            print(">>> print 2: number of repeats",file=logfile) 
            print(">>> print 2: number of repeats")
            p_op = 2
        '''if(args.p3):
            print(">>> print 3: repeats type 1",file=logfile) 
            print(">>> print 3: repeats type 1")
        if(args.p4):
            print(">>> print 4: repeats type 1",file=logfile) 
            print(">>> print 4: repeats type 1")'''
        
        step2(path, p_op, logfile)

def step1(path, logfile):
    exe = os.path.join(path, gsufsort_exe)
    command = "{exe} {ifile} --bwt --sa --lcp".format(exe = exe, ifile = sys.argv[1])
    execute_command(command, logfile)

def step2(path, p_op,logfile):
    exe = os.path.join(path, repeat_exe)
    file_bwt = sys.argv[1] + '.bwt'
    file_sa = sys.argv[1] + '.4.sa'
    file_lcp = sys.argv[1] + '.4.lcp'
    command = "{exe} {file_bwt} {file_sa} {file_lcp} {size} {p}".format(exe = exe, file_bwt = file_bwt, file_sa = file_sa, file_lcp = file_lcp, size = sys.argv[2], p = p_op)
    execute_command(command, logfile)

def define_basename(args):
    if len(args.out)==0:
        args.basename = args.input[0]
    else:
        args.basename = args.out

def execute_command(command, logfile):
    try:
        print(command)        
        start = time.time()
        subprocess.call(command, shell = True)
        print("Elapsed time: {0:.4f}".format(time.time()-start));
    except subprocess.CalledProcessError:
        print("Error to executing command line: {command}".format(command = command))
        return False
    return True

def show_command_line(f):
    f.write("Python command line: ") 
    for x in sys.argv:
        f.write(x+" ")
    f.write("\n") 

if __name__ == '__main__':
    main()
