#!/bin/bash
echo "Please run this from the directory with the makefile"
echo
./bin/rshell <<EOF
echo We are now running our rshell
echo These are single commands
echo
echo ls
ls
echo
echo pwd
pwd
echo
echo mkdir temp
mkdir temp
echo
echo ls
ls
echo
echo mv temp temp1
mv temp temp1
echo
echo ls
ls
echo
echo rmdir temp1
rmdir temp1
echo
echo ls
ls
echo
echo date
date
echo test -e tests
test -e tests
echo [ -f bin ]
[ -f bin ]
echo "ls inside parenthesis"
((((ls))))
echo
echo exit
exit
EOF
echo
