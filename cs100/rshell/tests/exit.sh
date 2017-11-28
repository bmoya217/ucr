echo "Please run this from the makefile directory"
echo
./bin/rshell <<EOF
echo "We are now running this in terminal"
echo Exit works just like any other command executed e.g. ls, rm, mv
echo I put parentheses throughout tests to make sure they work
echo "false && exit"
false && exit
echo
echo "That didnt exit because first command doesnt run"
echo "test bin && exit, will exit because first command does run"
((((test bin))) && ((exit)))
EOF
echo
