#sorts a "built-in" array
myArray=(8 6 7 5 3 0 9)

for hold in {1..100}
do
    for i in {0..6}
    do
	j=i+1
	if [[ "${myArray[i]}" > "${myArray[j]}" ]]
	then
	    temp=${myArray[i]}
	    myArray[i]=${myArray[j]}
	    myArray[j]=${temp}
	fi
    done
done

echo "${myArray[*]}"
