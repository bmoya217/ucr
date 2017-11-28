#include <cmath>
#include <iostream>
using namespace std;

int main(){

	int matrix[4] = {1,2,3,4};
	int mhold[4]= {1,2,3,4};
	int current[4] = {0,0,0,0};

	for(int i = 0; i < 2; i++){
        for(int j = 0; j < 2; j++){
            for(int k = 0; k < 2; k++){
                current[j*2+i] += matrix[k*2 + i] * mhold[j*2 + k];
            }
        }
    }

    for (int i = 0; i<4; i++){
    	cout << current[i] << " ";
    }
    cout << endl;

	return 0;
}