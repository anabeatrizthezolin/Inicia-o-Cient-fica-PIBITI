import sys, time, argparse, subprocess, os.path, pathlib, shutil

Description = """ Tool for identifying repeats in DNA strings

For example
    {exe} example.txt --txt -o output -s 1 -1 -2 -r --print
will produce the files output.type1 and output.type2 with the type 1 and type 2 repeats, respectively

--------------------------
Command line options:
--------------------------
""".format(exe=sys.argv[0])

gsufsort_exe = 'external/gsufsort/gsufsort'
repeat_exe = './repeat-dna'
word_cloud_exe = 'word_cloud.py'

def main():
    parser = argparse.ArgumentParser(description=Description, formatter_class=argparse.RawTextHelpFormatter)
    parser.add_argument('input',         help='input file name', type=str, nargs='+')
    parser.add_argument('-o','--out',    help='output base name (def. input base name)', default="", type=str)  
    parser.add_argument('-s','--size',   help='minimum repeat size', default=-1, type=int)
    parser.add_argument('-1', '--p1',    help='print 1: type 1', action='store_true', default = False)
    parser.add_argument('-2', '--p2',    help='print 2: type 2', action='store_true', default = False)
    parser.add_argument('-r',            help='repeats', action='store_true', default = True) 
    parser.add_argument('-si',           help='size and index', action='store_true')   
    parser.add_argument('-p', '--print', help='print', action='store_true', default = False)
    parser.add_argument('-t', '--txt',   help='input as txt files', action='store_true', default = True)
    parser.add_argument('-f', '--fast',  help='input as fasta or fastq files', action='store_true', default = False)
    parser.add_argument('-v',            help='verbose: extra info in the log file',action='store_true')
    args = parser.parse_args()
    
    define_basename(args)

    path = os.path.split(sys.argv[0])[0]
    path_inp = os.path.split(sys.argv[1])[0]

    if(args.out): # all output files named args.out
        logfile_name = os.path.join(path_inp, args.out) + ".repeat.log"
    else:
        logfile_name = args.basename + ".repeat.log"

    print("Sending logging messages to file:", logfile_name)

    with open(logfile_name,"a") as logfile:
        print(">>> Begin computation",file=logfile)
        show_command_line(logfile)
        logfile.flush()
        
        if(args.out): # all output files named args.out
            file_type1 = os.path.join(path_inp, args.out) + '.type1'
            file_type2 = os.path.join(path_inp, args.out) + '.type2'
            file_out = os.path.join(path_inp, args.out)
        else:
            file_type1 = sys.argv[1] + '.type1'
            file_type2 = sys.argv[1] + '.type2'
            file_out = sys.argv[1]

        step1(path, logfile, file_out)

        op = 0
        if(args.si): 
            args.r = False
        if(args.p1):
            print(">>> print 1: type 1",file=logfile)
            op = 1
        if(args.p2):
            print(">>> print 2: type 2",file=logfile)
            if(op == 1): op = 0
            else: op = 2
        if(args.r):
            print(">>> repeats",file=logfile)
            op_p = 1
        if(args.si):
            print(">>> size and index",file=logfile)
            op_p = 2

        if(args.fast):
            op_file = 1
        else:
            op_file = 0
        
        step2(path, op, op_p, op_file, logfile, args, file_out)

        if(args.print):
            print_type(op, file_out)

        if(op_p == 1):
            word_cloud(path, op, file_out)
            
def step1(path, logfile, file_out):
    exe = os.path.join(path, gsufsort_exe)

    command = "{exe} {ifile} --output {output} --bwt --sa --lcp"\
        .format(exe = exe, ifile = sys.argv[1], output=file_out)
    execute_command(command)

def step2(path, op, op_p, op_file, logfile, args, file_out):
    exe = os.path.join(path, repeat_exe)
    file_bwt = file_out + '.bwt'
    file_sa = file_out + '.4.sa'
    file_lcp = file_out + '.4.lcp'

    command = "{exe} {file_txt} {file_bwt} {file_sa} {file_lcp} {size} {op} {op_p} {op_file} {file_out}"\
        .format(exe=exe, file_txt=sys.argv[1], file_bwt=file_bwt, file_sa=file_sa, \
        file_lcp=file_lcp, size=(int)(args.size), op=op, op_p=op_p, op_file = op_file, file_out=file_out)
    execute_command(command)

def word_cloud(path, op, file_out):
    exe = os.path.join(path, word_cloud_exe)
    command = "python3 {file} {ifile} {op}".format(file=exe, ifile=file_out, op=op)
    subprocess.call(command, shell = True)

def define_basename(args):
    if len(args.out)==0:
        args.basename = args.input[0]
    else:
        args.basename = args.out

def execute_command(command):
    try:    
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

def print_type(op, file_out):
    print("\n## Repeat DNA ##")
    if(op == 0):
        file_type1 = file_out + '.type1'
        file_type2 = file_out + '.type2'
        print("Type 1:")
        with open(file_type1) as f:
            content = f.readlines()
        for x in content:
            print(x, end = '')
        print("")

        print("Type 2:")
        with open(file_type2) as f:
            content = f.readlines()
        for x in content:
            print(x, end = '')

    elif(op == 1):
        file_type1 = file_out + '.type1'
        print("Type 1:")
        with open(file_type1) as f:
            content = f.readlines()
        for x in content:
            print(x, end = '')

    elif(op == 2):
        file_type2 = file_out + '.type2'
        print("Type 2:")
        with open(file_type2) as f:
            content = f.readlines()
        for x in content:
            print(x, end = '')

if __name__ == '__main__':
    main()
