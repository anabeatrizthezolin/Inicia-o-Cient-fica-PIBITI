import sys, time, argparse, subprocess, os.path, pathlib

def main():
    path = os.path.split(sys.argv[0])[0]
    step1(path)
    step2(path)

def step1(path):
    gsufsort_exe = 'external/gsufsort/gsufsort'
    exe = os.path.join(path, gsufsort_exe)
    command = "{exe} {ifile} --bwt --sa --lcp".format(exe = exe, ifile = sys.argv[1])
    execute_command(command)

def step2(path):
    #repeat_exe = 'Repeat-DNA/build/CMakeFiles/Project.dir/Repeat-DNA'
    repeat_exe = 'repeat/RepeatDNA'
    exe = os.path.join(path, repeat_exe)
    file_bwt = sys.argv[1] + '.bwt'
    file_sa = sys.argv[1] + '.4.sa'
    file_lcp = sys.argv[1] + '.4.lcp'
    command = "{exe} {file_bwt} {file_sa} {file_lcp} {size}".format(exe = exe, file_bwt = file_bwt, file_sa = file_sa, file_lcp = file_lcp, size = sys.argv[2])
    execute_command(command)

def execute_command(command):
    try:
        subprocess.call(command, shell = True)
    except subprocess.CalledProcessError:
        print("Error to executing command line: {command}".format(command = command))
        return False
    return True
if __name__ == '__main__':
    main()
