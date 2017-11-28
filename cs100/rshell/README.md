# rshell
A shell designed to mimic basic vim functionality
=================================================

Features
--------

* execute the built in bash commands using execvp
* chain commands using ; && and ||
* displays username/hostname with prompt

Limitations
-----------

* does not know how to use "cd" command
* 1000 char for input
* overall weak input checking
* if a cmd ends with && or || then doesnt wait for the rest of the input like in bash
* Parentheses are always checked for first and execute first
