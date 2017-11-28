#include <string>
#include <iostream>
#include <vector>
using namespace std;

int main () 
{
    
    // defines the strings
    vector<string> word (10);
    
    // asks for users blind input of strings
    cout << "Enter any type of animal: ";
    cin >> word[0];
    cout << "\n\nEnter another animal: ";
    cin >> word[1];
    cout << "\n\nEnter one more: ";
    cin >> word[2];
    cout << "\n\nEnter your characters name: ";
    cin >> word[3];
    cout << "\n\nEnter a noun bigger than the first animal: ";
    cin >> word[4];
    cout << "\n\nEnter an emotion: ";
    cin >> word[5];
    cout << "\n\nEnter a verb that ends in -ed: ";
    cin >> word[6];
    cout << "\n\nEnter a verb that ends in -ing: ";
    cin >> word[7];
    cout << "\n\nEnter a type of building material: ";
    cin >> word[8];
    cout << "\n\nEnter another type of building material:";
    cin >> word[9];
    
    // 80 dashes to represent the start of the story
    string measuringStick(80, '-');
    cout << measuringStick << endl;
    
    // paragraph 1
    cout << "\033cThere once was a " << animal1 << " who lived in a ";
    cout << homeForCharacter << ". He was very " << emotion << endl;
    cout << "because he";
    cout << " only " << verbED << " all day long. Unfortuneately, " << name;
    cout << " the " << endl;
    cout << animal1 << " was very lonely.\n" << endl;
    
    // paragraph 2
    cout << "One day " << name << " decided that he wanted more friends. ";
    cout << "So then he tried making" << endl;
    cout << "one out of " << object1 << " and ";
    cout << object2 << ". When that didn't work, " << name << " got " <<endl;
    cout << "very sad.";
    cout << endl << endl;
    
    // paragraoh 3
    cout << "To fill in his time " << name << " decided to take " << verbING;
    cout << " classes. Months later," << endl;
    cout << "his newly aquired skill was what helped ";
    cout << "him win over his soon-to-be wife, the" << endl;
    cout << "very bodacios " << animal2;
    cout << ". However, that unkind lady cheated on him with a " << endl; 
    cout << animal3 << " and " << name << " died alone.\n";
    
    // 80 dashes to represent the end of the story
    cout << measuringStick;
    
    return 0;
}