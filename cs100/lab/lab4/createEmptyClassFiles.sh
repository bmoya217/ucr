#pass in "class name" and it will create classname.hh and classname.cc

#create files
f1=".hh"
f2=".cc"
touch $1$f1
touch $1$f2

#modify file1 (f1-- myclass.hh)
header=`cat branden_861121591.txt`
printf "$header\n#ifndef $1_hh\n#define $1_hh\n\nclass $1\n{\n    public:\n    $1();\n    ~$1();\n\nprivate:\n};\n#endif\n" > $1$f1

#modify file2 (f2-- myclass.cc)
printf "$header \n#include \"./$1.hh\"\n\n$1::$1()\n{}\n\n$1::$1()\n{}\n" > $1$f2
