#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <ctime>
#include <string>
using namespace std;

//Cubic maximum contiguous subsequence sum algorithm.
int maxSubSum1(const vector<int> &v,int minSeq,int &totalTicks,bool &ansValid){
    int maxSum = 0;
    totalTicks = 0;
    ansValid = true;
    bool minSeqZero= false;
    
    if(minSeq==0){
        minSeqZero= true;
        minSeq= 1;
    }
    
    if(v.size() < minSeq){
        ansValid = false;
        return 0;
    }
    
    for(int i = 0; i < minSeq; i++){
        totalTicks+=1;
        maxSum += v[i];
    }
    
    for(int i = 0; i <= v.size( )-minSeq+1; i++)
        for(int j = i+minSeq-1; j < v.size( ); j++){
            int thisSum = 0;
            
            for(int k = i; k <= j; k++){
                totalTicks+=1;
                thisSum += v[k];
            }
            
            if(thisSum > maxSum){
                maxSum = thisSum;
            }
        }
    
    if(minSeqZero== true && maxSum < 0){
        maxSum= 0;
    }
    
    return maxSum;
}

//Quadratic maximum contiguous subsequence sum algorithm.
int maxSubSum2(const vector<int> &v,int minSeq,int &totalTicks,bool &ansValid){
    int maxSum = 0;
    totalTicks = 0;
    ansValid = true;
    
    if(v.size() < minSeq){
        ansValid = false;
        return 0;
    }
    
    for(int i = 0; i < minSeq; i++){
        totalTicks+=1;
        maxSum += v[i];
    }
    
    for(int i = 0; i < v.size( )-minSeq+1; i++){
        int thisSum = 0;
        for(int j = i; j < i+minSeq-1; j++){
            totalTicks+=1;
            thisSum += v[j];
        }
        for(int k = i+minSeq-1; k < v.size( ); k++){
            totalTicks+=1;
            thisSum += v[k];
            
            if(thisSum > maxSum){
                maxSum = thisSum;
            }
        }
    }
    
    return maxSum;
}

//Return maximum of three integers.
int max3(int a, int b, int c){
    return a > b ? a > c ? a : c : b > c ? b : c;
}

//Divide-and-conquer maximum contiguous sum (recursive)
int maxSumRec(const vector<int> & v, int left, int right, int minSeq,int &totalTicks){
    int base= 0;
    for(int i = left; i < left+minSeq; i++){
        totalTicks+=1;
        base+=v[i];
    }
    
    if(right-left+1 == minSeq)  // Base case
        return base;
    
    int center=(left+right)/2, maxLeftSum= base, maxRightSum= base;
    int rBS=0, curBS=0, maxBS= base;
    vector<int> lBSv;
    
    if(center-left+1 >= minSeq)
        maxLeftSum = maxSumRec(v, left, center, minSeq, totalTicks);
    if(right-center >= minSeq)
        maxRightSum = maxSumRec(v, center+1, right,minSeq,totalTicks);
    
    for(int i = center; i >= left; i--){
        totalTicks+=1;
        curBS+=v[i];
        lBSv.push_back(curBS);
        if(center-i+2 == minSeq)
            maxBS= lBSv[lBSv.size()-1]+v[center+1];
    }
    
    for(int j = center + 1; j <= right; j++){
        totalTicks+=1;
        rBS += v[j];
        for(int i = 0; i < lBSv.size(); i++)
            if((j-center)+(i+1)>=minSeq){
                totalTicks+=1;
                if(rBS+lBSv[i]>maxBS)
                    maxBS = rBS+lBSv[i];
            }
    }
    
    return max3(maxLeftSum, maxRightSum, maxBS);
}

//Driver for divide-and-conquer maximum contiguous sum (recursive)
int maxSubSum3(const vector<int> &v,int minSeq,int &totalTicks,bool &ansValid){
    totalTicks = 0;
    ansValid = true;
    int minSeqZero = minSeq;
    
    if(minSeq > v.size()){
        ansValid = false;
        return 0;
    }
    
    if(minSeq==0)
        minSeqZero= 1;
    
    int maxSum= maxSumRec(v, 0, v.size( )-1, minSeqZero, totalTicks);
    
    if(maxSum < 0 && minSeq==0)
        maxSum= 0;
    
    return maxSum;
}

//Linear-time maximum contiguous subsequence sum algorithm.
int maxSubSum4(const vector<int> &v,int minSeq,int &totalTicks,bool &ansValid){
    int maxSum= 0, thisSum= 0, minSum= 0;
    ansValid = true; totalTicks = 0;
    bool minSeqZero = false;
    
    if(v.size() < minSeq){
        ansValid = false;
        return 0;
    }
    
    if(minSeq==0)
        minSeqZero = true;
    else{
        maxSum = 0;
        for(int i = 0; i < minSeq; i++){
            totalTicks+=1;
            maxSum += v[i];
        }
        thisSum = maxSum;
        minSum = maxSum;
    }
    
    for(int i = minSeq; i < v.size( ); i++){
        totalTicks+=2;
        thisSum += v[i];
        if(!minSeqZero)
            minSum += (v[i]-v[i-minSeq]);
        
        if(thisSum < minSum){
            thisSum = minSum;
        }
        if(thisSum > maxSum){
            maxSum = thisSum;
        }
    }
    
    return maxSum;
}

int main(int argc, char *argv[]){
    vector<int> v; string hold; int temp, minSeq;
    int tick1, tick2, tick3, tick4; 
    bool av1, av2, av3, av4;
    int maxSum1, maxSum2, maxSum3, maxSum4;
    
    //sets up iofile streams
    istringstream ofnames(argv[1]);
    ofnames >> hold;
    ifstream ifile(hold.c_str()); 
    
    int pos = hold.find(".");
    if(pos != -1)
        hold= hold.substr(0,pos);
    hold+= ".out";
    ofstream ofile1(hold.c_str());
    
    pos = hold.find(".");
    hold= hold.substr(0,pos);
    hold+= ".csv";
    ofstream ofile2(hold.c_str());
    
    if(!(ifile.is_open() || ofile1.is_open() || ofile2.is_open())){
        cout << "Could not open input and/or output file(s)..\n";
        return -1;
    }
    
    //gets input until eof, does work with it, and outputs results
    while(getline(ifile, hold)){
        istringstream minny(hold);
        minny >> minSeq;
        getline(ifile, hold);
        istringstream in(hold);
        while(in >> temp)
            v.push_back(temp);
        
        //finds maxsum using all 4 algorithms and writes results to *.out
        maxSum1 = maxSubSum1(v, minSeq, tick1, av1);
        if(av1)
            ofile1 << "1 " << maxSum1 << " ";
        else 
            ofile1 << "0 0 ";
        
        maxSum2 = maxSubSum2(v, minSeq, tick2, av2);
        if(av2)
            ofile1 << "1 " << maxSum2 << " ";
        else 
            ofile1 << "0 0 ";
        
        maxSum3 = maxSubSum3(v, minSeq, tick3, av3);
        if(av3)
            ofile1 << "1 " << maxSum3 << " ";
        else 
            ofile1 << "0 0 ";
        
        maxSum4 = maxSubSum4(v, minSeq, tick4, av4);
        if(av4)
            ofile1 << "1 " << maxSum4 << endl;
        else 
            ofile1 << "0 0\n";
        
        //writes to *.csv
        ofile2 << v.size() << " " << minSeq << " ";
        if(av1 && av2 && av3 && av4)
            ofile2 << "1 ";
        else 
            ofile2 << "0 ";
        ofile2 << tick1 << " " << tick2 << " " << tick3 << " " << tick4 << endl;
        
        if(maxSum1 != maxSum2 || maxSum1 != maxSum3 || maxSum1 != maxSum4)
            cout << "unforseen errors in code :(\n";
        
        v.clear();
    }
    
    //closes used files
    ifile.close();
    ofile1.close();
    ofile2.close();
    
    return 0;
}