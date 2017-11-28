#include <cmath>
#include <string>
#include <cmath>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <iostream>

using namespace std;

int rollNDice(int num_of_dice, int sides_on_dice) // sim 2 dice rolls
{
    int total = 0;
    
    for(int i = 0; i < num_of_dice; i++)
    {
        total += rand()%sides_on_dice +1;    
    }
    
    return total;
}

int mostLandings(vector<int> gameboard, int start, int end) // find most stuff'
{
    int value =0;
    int index = start;
    for (int i = start; i <= end; i++)
    {
        if(gameboard.at(i)> value)
        {
            value = gameboard.at(i);
            index = i;
        }
    }
    
    return index;
}

int main (){
    srand(time(0)); ///// do main shit
    int numSides;
    int numCells;
    int numSims;
    int hold;
    
    cout << "How many sides of the board are there? ";
    cin >> numSides;
    cout << endl;
    
    cout << "How many spots are on each side? ";
    cin >> numCells;
    cout << endl;
    
    cout << "How many simulations? ";
    cin >> numSims;
    cout << endl;
    
    //also things
    
    vector <int> board ((numCells * numSides)+1);
    
    for(int i = 0; i < numSims; i++)
    {
        hold = 0;
        while (hold < numSides*numCells)
        {
            hold += rollNDice(2,6);
            if(hold <= numSides*numCells)
            {
                board.at(hold)++;
            }
        }
    }
    
    cout << "The following spots on each side have the most landings: " << endl;
    for (int i = 1; i <= numSides;i++)
    {
        hold = mostLandings(board,(i-1)*numCells+1, i*numCells);
        cout << "On side " << i << ", spot " << hold << " has the most";
        cout << " landings: " << board.at(hold) << endl;
    }
    
    return 0;
}