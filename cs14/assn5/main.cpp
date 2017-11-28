#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <list>
#include <iterator>
#include <cctype>
#include <cstdlib>
#include <vector>
#include "chain.h"
#include "probe.h"
using namespace std;

template <typename type>
void spellchecker(type &myHash, vector<string> lines, ofstream &ofile){
    string shold;
    for(unsigned int i= 0; i < lines.size(); i++){
        istringstream line(lines[i]);
        while(line >> shold)
            if(!myHash.contains(shold))
                ofile << shold << endl;
    }
}

template <typename type>
void hashedOut(type &myHash, ifstream &dicfile){
    string shold;
    while(dicfile >> shold)
        myHash.insert(shold);
}

template <typename type>
void hashedOut(type &myHash, ifstream &dicfile, ofstream &ofile2){
    string shold; int ihold; 
    vector<int> stats;
    
    while(dicfile >> shold){
        myHash.insert(shold, ihold);
        while(ihold >= stats.size())
            stats.push_back(0);
        stats[ihold]++;
    }
    
    for(int i= 0; i < stats.size(); i++)
        ofile2 << i << " " << stats[i] << endl;
}

void processInput(vector<string> &lines, ifstream &ifile){
    string shold;
    while(getline(ifile, shold)){
        for(unsigned int i= 0; i < shold.size(); i++){
            if(shold[i] >= 'A' && shold[i] <= 'Z')
                shold[i]+= 'a'-'A';
            else if(shold[i] < 'a' || shold[i] > 'z')
                shold[i]= ' ';
        }
        lines.push_back(shold);
    }
}

//hash spell checker usage:(a).out -(1 or 2) -(chain or probe) (spellcheckme).txt
int main(int argc, char *argv[]){
    //variable ish
    string shold= argv[1]; int ihold; vector<string> lines; 
    chainHash<string> myChain; probeHash<string> myProbe;
    
    //ifile ish
    if(shold== "-1")
        shold= "smalldic.txt";
    else
        shold= "ispelldic.txt";
    ifstream dicfile(shold.c_str());
    shold= argv[3];
    ifstream ifile(shold.c_str());
    
    //ofile ish
    ihold = shold.find(".");
    if(ihold != -1)
        shold= shold.substr(0,ihold);
    shold+= ".out";
    ofstream ofile1(shold.c_str());
    
    ihold = shold.find(".");
    shold= shold.substr(0,ihold);
    shold+= ".stats";
    ofstream ofile2(shold.c_str());
    
    //driver ish
    processInput(lines, ifile); //gets rid of non letters and converts to lower
    
    shold= argv[2];
    if(shold == "-chain"){ //runs using chaining method
        hashedOut(myChain, dicfile);
        spellchecker(myChain, lines, ofile1);
        myChain.chainStats(ofile2);
    }
    else{ //else, runs using probing method
        hashedOut(myProbe, dicfile, ofile2);
        spellchecker(myProbe, lines, ofile1);
    }
    
    return 0;
}