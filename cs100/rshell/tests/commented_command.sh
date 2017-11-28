#!/bin/bash
echo "Please run this from the directory with the makefile"
echo
./bin/rshell <<EOF
echo "We are now executing commands through rshell"
echo "Parentheses are added throughout commands to see if they work"
ls #Command with comments
(((((mkdir temp)))) && ls )     #With more comments
rmdir temp; ls        #Remove just created temp folder
echo should output a
(test bin && echo a ) #should output a
echo should output true
(((([ -e bin ])))) #some more comments
echo
echo "exit"
exit
echo
EOF
echo
