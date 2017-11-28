#create empty main.cc file
touch main.cc
header=`cat branden_861121591.txt`
printf "$header \nint main(int argc, const char** argv)\n    {}\n" > main.cc
