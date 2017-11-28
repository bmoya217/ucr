#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main()
{
    string ISBN;
    int checksum = 0;

    // asks for 9 digits of isbn
    cout << "Please enter the first 9 digits of the ISBN: ";
    cin >> ISBN;

    // calculates checksum
    for (int i = 0; i < ISBN.size(); i++)
        checksum += (static_cast<int>(ISBN[i]) - 48) * (i+1);

    // displays checksum
    cout << "checksum: " << checksum%11 << endl;

    return 0;
}