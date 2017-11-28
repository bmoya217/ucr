#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cstdlib>
#include <iostream>

using namespace std;

list<int> Intersect(list<int> list1, list<int> list2){
    list<int> list3;
    list<int>::iterator one= list1.begin();
    list<int>::iterator two= list2.begin();
    
    while(one!=list1.end() && two!=list2.end()){
        if(*one<*two)
            ++one;
        
        else if(*one>*two)
            ++two;
        
        else{
            list3.push_back(*one);
            ++one;
            ++two;
        }
    }
    return list3;
}

list<int> Union(list<int> list1, list<int> list2){
    list<int> list3;
    list<int>::iterator one= list1.begin();
    list<int>::iterator two= list2.begin();
    
    while(one!=list1.end() || two!=list2.end()){
        if(one==list1.end()){
            list3.push_back(*two);
            ++two;
        }
        else if(two==list2.end()){
            list3.push_back(*one);
            ++one;
        }
        else{
            if(*one<*two){
                list3.push_back(*one);
                ++one;
            }
            else{
                list3.push_back(*two);
                ++two;
            }
        }
    }
    return list3;
}

int main(){
    list<int> list1;
    list1.push_back(1);
    list1.push_back(2);
    list1.push_back(2);
    list1.push_back(7);
    list1.push_back(9);
    list1.push_back(11);
    
    
    list<int> list2;
    list2.push_back(0);
    list2.push_back(2);
    list2.push_back(4);
    list2.push_back(6);
    
    list<int> list3= Intersect(list1, list2);
    for(list<int>::iterator three= list3.begin(); three != list3.end(); ++three)
        cout << *three << " ";
    cout << endl;
    
    list3= Union(list1,list2);
    for(list<int>::iterator three= list3.begin(); three != list3.end(); ++three)
        cout << *three << " ";
    cout << endl;
    
    return 0;
}