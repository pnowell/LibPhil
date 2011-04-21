import os
import sys
import subprocess

## -- build our command line for kicking off jam
cwd = os.getcwd()
commandline = r'jam -f c:\code\jamcore\Jambase.jam -d 0 -q -g -s LIBPHIL_CWD="' + cwd + r'"'
for arg in sys.argv[1:]:
    commandline += " " + arg
result = subprocess.call(commandline)

if result == 0:
    print "\nCompile successful\n"
else:
    print "\n********************"
    print "** COMPILE FAILED **"
    print "********************"
