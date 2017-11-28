#return largest of 3 numbers passed as parameters
if [ $# -eq 3 ]
then

    if [ $1 -ge $2 -a $1 -ge $3 ]
    then
	printf "$1\n"

    elif [ $2 -ge $1 -a $2 -ge $3 ]
    then
	printf "$2\n"

    else
	printf "$3\n"
    fi

else
printf "Incorrect number of parrameters passed! Enter 3 numbers next time\n"
fi
