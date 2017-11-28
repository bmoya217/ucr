#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>

using namespace std;

void insertSort(vector<int> &v){
    cout << "Insert Sort:\n";
    int runtime= 0;
    for(int i = 1; i < v.size(); i++){
        int value = v[i];
        runtime++;
        int j = i - 1;
        while(j >= 0 && v[j] > value){
            v[j + 1] = v[j];
            j = j - 1;
            runtime++;
        }
        v[j + 1] = value;
        runtime++;
        cout << "\tVector at " << i << ": ";
        for(int i = 0; i < 10; i++)
            cout << v[i] << " ";
        cout << endl;
    }
    cout << "\tRuntime of insert sort: " << runtime << endl;
}

int main(){
    srand(time(0));
    vector<int> v;
    // for(int i = 0; i < 10; i++)
    //     v.push_back(rand()%10);
    for(int i = 0; i < 10; i++)
        v.push_back(10-i);
    
    cout << "Original vector: ";
    for(int i = 0; i < 10; i++)
        cout << v[i] << " ";
    cout << endl;
    
    insertSort(v);
    
    cout << "Sorted vector: ";
    for(int i = 0; i < 10; i++)
        cout << v[i] << " ";
    cout << endl;
}