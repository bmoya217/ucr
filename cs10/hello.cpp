 #include <iostream>
#include <string>
using namespace std;
    
int main() {
    string usersName;
    
    cout << "\nHello, What is your name?" << endl;
    cin >> usersName; // user enters their name
    
    cout << "Hi, " << usersName << ", I bid you good day." << endl;
    
    return 0;
}