#include <iostream>
#include <string>
#include <ctime>
#include <ios>
#include <iomanip>
#include <cstdlib>

using namespace std;

void monsterRoom(int& banana, int& orange, string monster)
{
    banana = 0;
    orange = 0;
    
    cout << "WATCH OUT!!\n" << monster << " attacks you and ";
    cout << "steals all of your bananas and oranges.\n" << endl;
}

void genieRoom(int& banana, int& orange)
{
    banana += 2;
    orange += 1;
    
    cout << "!!POOF!!\nA genie pops out and grants you 2 bananas and 1 orange.";
    cout << endl << endl;
}

void pictureRoom()
{
    cout << "You found a picture!" << endl << endl;
    cout << "        _--~~--_" << endl;
    cout << "      /~/_|  |_\\~\\" << endl;
    cout << "     |____________|" << endl;
    cout << "     |[][][][][][]|" << endl;
    cout << "   __| __         |__" << endl;
    cout << "  |  ||. |   ==   |  |" << endl;
    cout << " (|  ||__|   ==   |  |)" << endl;
    cout << "  |  |[] []  ==   |  |" << endl;
    cout << "  |  |____________|  |" << endl;
    cout << "  /__\\            /__\\" << endl;
    cout << "   ~~              ~~" << endl;
    cout << endl;
}

int main()
{
    srand(time(0));
    
    // defines all variables
    int banana = 5;
    int orange = 3;
    string monster, name;
    char door, M, G, P, E;
    bool end = false;
    
    cout << "Please enter your name: ";
    cin >> name;
    cout << endl;
    
    cout << "Name your scariest monster: ";
    cin >> monster;
    cout << "\n";
    
    // game loop
    while (!end)
    {
        cout << name << ", you are in a room with 4 doors.\n";
        cout << "You are carrying " << banana << " bananas and " << orange;
        cout << " oranges.\n" << endl;
        
        do
        {
            cout << "Pick a door to enter by typing the direction it is in";
            cout << " (N/E/S/W): ";
            cin >> door;
            cout << endl;
        }while (door != 'N' && door != 'S' && door != 'E' && door != 'W');
        
        M = 'N';
        G = 'S';
        P = 'E';
        E = 'W';
        if (rand()%2 == 1)
        {
            M = 'S';
            G = 'E';
            P = 'W';
            E = 'N';
        }
        
        if (door == M)
        {
            monsterRoom(banana, orange, monster);
        }
        
        else if (door == G)
        {
            genieRoom(banana, orange);
        }
        
        else if (door == P)
        {
            pictureRoom();
        }
        
        else if (door == E)
        {
            end = true;
        }
    }
    
    // game over output
    cout << "You found the exit!\n";
    cout << "Your score is " << banana + orange << " (" << banana << " bananas";
    cout << " and " << orange << " oranges).\nBye bye!!!\n";
    
    return 0;
}