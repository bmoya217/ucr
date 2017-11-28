#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cstdlib>
#include <iostream>

using namespace std;

int binaryOnes(int num){
    if(num==1)
        return 1;
    
    if(num%2==0)
        return binaryOnes(num/2);
    
    return 1+binaryOnes(num/2);
}

int main(){
    int num= 11711;
    cout << binaryOnes(num) << endl;
    
    return 0;
}