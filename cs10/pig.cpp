#include <iostream>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <ios>
using namespace std;

int main()
{
    // variables
    int turns, int minScore, actScore=0, int roll, int fails = 0;;
    vector<int> msc(6,0);
    
    srand(time(0));
    
    cout << "What value should we hold at? ";
    cin >> minScore;
    
    cout << "\nHold-at-N turn simulations? ";
    cin >> turns;
    
    // math ish
    for (int i = 0; i < turns; i++)
    {
        // individual game
        while(actScore < minScore)
        {
            roll = rand()%6+1;
            if (roll != 1)
            {
                actScore += roll;
            }
            else
            {
                fails ++;
                actScore = 0;
                break;
            }
        }
        
        // counts the scores
        msc[actScore-minScore]++;
    }
    
    // out puts scores probabilty
    cout << "Score\tEstimated Probability\n";
    cout << "0\t" << fixed << setprecision(6) << showpoint << fails/(turns*1.0);
    cout << endl;
    for (int i = 0; i < 6; i++)
    {
        cout << minScore << "\t" << fixed << setprecision(6) << showpoint;
        cout << msc[i]/(turns*1.0) << endl;
    }
    return 0;
}