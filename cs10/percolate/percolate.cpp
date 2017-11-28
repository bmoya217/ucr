#include <iostream>
#include <vector>
using namespace std;

// Provided functions from <perc_functions.o>
void animationPause();
void clearScreen();
void printEmpty();
void printColor();
void printWall();
void readGrid(vector <vector <int> > &, vector <vector <bool> > &);

/// @brief percolates the fluid from grid blocks with fluid in them
void perc(vector <vector <int> > &grid)
{
    for (int y = 0; y < grid.size(); y++)
        for (int x = 0; x < grid[y].size(); x++)
            if (grid[y][x] == 3)
            {
                if (y < (grid.size()-1))
                    if (grid[y+1][x] ==1)
                        grid[y+1][x] = 4;
                
                if (y>0)
                    if (grid[y-1][x] ==1)
                        grid[y-1][x] = 4;
                
                if (x < (grid[y].size()-1))
                    if (grid[y][x+1] ==1)
                        grid[y][x+1] = 4;
                
                if (x>0)
                    if (grid[y][x-1] ==1)
                        grid[y][x-1] = 4;
            }
    
    /// Traverse 2D grid converting intermediate states to color state
    for (int y = 0; y < grid.size(); y++)
        for (int x = 0; x < grid[y].size(); x++)
            if (grid[y][x] == 4)
                grid[y][x] = 3;
}

/// @brief determines whether the percolation has reached goal cell
bool percComplete(const vector <vector <int> > &grid,
    const vector <vector <bool> > &goals)
{ 
    for (int y = 0; y < grid.size(); y++)
        for (int x = 0; x < grid[y].size(); x++)
            if (goals[y][x] && grid[y][x] == 3)
                return true;

    return false;
}

/// @brief prints the NxM grid 
void printGrid(const vector <vector <int> > &grid)
{
    clearScreen();
    /// empty = 1, wall = 2, color = 3, to-be-colored = 4;
    /// Traverse 2D grid, print each cell using each state's helper functions.
    for (int y = 0; y < grid.size(); y++)
    {
        for (int x = 0; x < grid[y].size(); x++)
        {
            if (grid[y][x] == 1)
                printEmpty();
            
            else if (grid[y][x] == 2)
                printWall();
            
            else if (grid[y][x] == 3)
                printColor();
        }
        cout << endl;
    }
}

int main()
{
    // 2D vectors to store states of grid and whether it is a goal cell
    vector <vector <int> > grid;
    vector <vector <bool> > goals;
   
    // Read in the grid from input
    readGrid(grid, goals);

    // Print initial grid
    printGrid(grid);

    // Run the simulation
    do
    {
        animationPause();
        
        perc(grid);
        
        printGrid(grid);
    }while(!percComplete(grid, goals));
    return 0;
}