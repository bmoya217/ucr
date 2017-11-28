#include <iostream>
#include <vector>

using namespace std;

void display(vector<vector<int> > &seqs, vector<vector<int> > &freqs, int m){
    for(int x = 0; x < seqs.size(); x++){
        cout << "<";
        for(int y = 0; y < seqs.at(x).size(); y++){
            cout << seqs.at(x).at(y);
            if(y < seqs.at(x).size()-1)
                cout << " ";
        }
        cout << "> ";
        
        cout << " <";
        for(int y = 0; y < m; y++){
            cout << y << ":" << freqs.at(x).at(y);
            if(y < freqs.at(x).size()-1)
                cout << ", ";
        }
        cout << ">";
        cout << endl;
    }
}

vector<int> super_freqy(vector<int> to_count, int m){
    vector<int> counted(m,0);
    for(int i = 0; i < to_count.size(); i++){
        counted.at(to_count.at(i))++;
    }
    return counted;
}

void update_pairs(vector<vector<bool> > &pairs, vector<int> seq){
    for(int i = 0; i < seq.size()-1; i++){
        pairs.at(seq.at(i)).at(seq.at(i+1)) = true;
    }
    pairs.at(seq.at(seq.size()-1)).at(seq.at(0)) = true;
    return;
}

// finds out if we have all the pairs we need and selects the next
// pair of values to start off the next fib seq with
bool got_pair(vector<vector<bool> > &v, int &a, int &b){
    for(int x = 0; x < v.size(); x++){
        for(int y = 0; y < v.at(x).size(); y++){
            if(v.at(x).at(y)==false){
                a = x;
                b = y;
                return true;
            }
        }
    }
    return false;
}

vector<int> fibmod(int m, int a, int b){
    vector<int> seq; // stores fib seq
    seq.push_back(a);
    seq.push_back(b);
    int size;
    
    do{ // extends vector seq with (f(n-1)+f(n))%m
        size = seq.size();
        seq.push_back((seq[size-2]+seq[size-1])%m);
        
        if(size>=3){
            if(seq[size]==seq[size-2]&&seq[size-1]==seq[size-3]){
                return seq;
            }
        }
    }while(!(seq[0]==seq[size-1]&&seq[1]==seq[size]));
    
    seq.pop_back(); // these get rid of base case that actually belong in the
    seq.pop_back(); // next sub sequence
    return seq;
}

int main(){
    int a = 0; // first value of fib sec (fibbonanci sequence)
    int b = 1; // sencond value of fib sec
    int m; // number to mod each value in fib sec by -> f(n)%m
    vector<vector<int> > subseqs;
    vector<vector<int> > valfreqs; // value frequencies of each subseq
    
    cout << "Enter \"m\" to mod each value of the fib seq by: ";
    cin >> m;
    cout << endl;

    //creats a 2d bool table until every v[x][y] is true
    vector<vector<bool > > pairs(m, vector<bool>(m, false));
    pairs.at(0).at(0) = true;
    
    do{
        subseqs.push_back(fibmod(m,a,b));
        valfreqs.push_back(super_freqy(subseqs.at(subseqs.size()-1),m));
        update_pairs(pairs, subseqs.at(subseqs.size()-1));
    }while(got_pair(pairs, a, b));
    
    display(subseqs, valfreqs, m);
    
    return 0;
}