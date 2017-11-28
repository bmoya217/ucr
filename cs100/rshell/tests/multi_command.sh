#!/bin/bash
echo "Please run this from the directory with the makefile"
echo
./bin/rshell<<EOF
echo We are now in our rshell
echo parentheses added throughout commands
echo
echo "mkdir temp&&ls; rmdir temp|| rmdir temp;ls;"
mkdir temp&&ls; rmdir temp|| rm random || ls;
echo
echo "nocommand || ls -1"
nocommand || ls -1
echo
echo "nocommand && ls"
nocommand && ls
echo "echo a && test -f  Makefile || echo b"
echo a && ( test -f Makefile || (echo b) )
echo "echo a && test -d  Makefile && echo b"
echo a && test -d Makefile && echo b
echo "echo a && [ -f  makefile ] || echo b"
echo ( a && [ -f makefile ] ) || ( echo b )
echoi
echo exit
exit
EOF
echo
