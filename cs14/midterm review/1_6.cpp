#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cstdlib>
#include <iostream>

using namespace std;

void swap(string &s, int low, int high){
    char hold= s[low];
    s[low]= s[high];
    s[high]= hold;
}

void permute(const string &s){
    permute(s,0,s.size()-1);
}

void permute(string &s, int low, int high){
    int i;
    if (low == high)
        cout << s[a] << " ";
    else{
        for (i = l; i <= r; i++){
            swap(s, low, i);
            permute(s, low+1, high);
            swap(s, low, i); //backtrack
        }
    }
}


int main(){
    string s= "abc";
    permute(s);
    cout << endl;
    
    return 0;
}