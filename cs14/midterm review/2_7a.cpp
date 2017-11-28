#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cstdlib>
#include <iostream>

using namespace std;

int one(int n){
    int sum= 0;
    for(int i = 0; i < n; ++i)
        ++sum;
    return sum;
}

int two(int n){
    int sum= 0;
    for(int i = 0; i < n; i++)
        for(int j = 0; j < n; ++j)
            sum++;
    return sum;
}

int three(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i )
        for(int j = 0; j < n * n; ++j )
            ++sum;
    return sum;
}

int four(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i )
        for(int j = 0; j < i; ++j )
            ++sum;
    return sum;
}

int five(int n){
    int sum = 0;
    for(int i = 0; i < n; ++i )
        for(int j = 0; j < i * i; ++j )
            for(int k = 0; k < j; ++k )
                ++sum;
    return sum;
}

int six(int n){
    int sum = 0;
    for(int i = 1; i < n; ++i )
        for(int j = 1; j < i * i; ++j )
            if( j % i == 0 )
                for(int k = 0; k < j; ++k )
                    ++sum;
    return sum;
}

int main(){
    int n= 100;
    cout << "For n= " << n << endl;
    cout << "\t" << one(n) << endl;
    cout << "\t" << two(n) << endl;
    cout << "\t" << three(n) << endl;
    cout << "\t" << four(n) << endl;
    cout << "\t" << five(n) << endl;
    cout << "\t" << six(n) << endl;
    
    n= 500;
    cout << "For n= " << n << endl;
    cout << "\t" << one(n) << endl;
    cout << "\t" << two(n) << endl;
    cout << "\t" << three(n) << endl;
    // cout << "\t" << four(n) << endl;
    // cout << "\t" << five(n) << endl;
    // cout << "\t" << six(n) << endl;
    
    return 0;
}