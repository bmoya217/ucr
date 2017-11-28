#include <iostream>
#include <vector>

using namespace std;

const bool CLEAR_SCREEN = true;

/// @brief Utilizes an escape character sequence to clear the screen
void clearScreen()
{
    cout << endl;

    if (CLEAR_SCREEN)
    {
        cout << "\033c";
    }

    cout << endl;
}

/// @brief Draws the provided tic-tac-toe board to the screen
void drawBoard(const vector <char> &board)
{
    clearScreen();
    for (int i = 0; i < 9; i += 3)
    {
        cout << "  " << board.at(i) << "  |  " << board.at(i + 1) << "  |  "
            << board.at(i + 2) << "  " << endl;
        if (i < 6)
            cout << "-----|-----|-----" << endl;
    }
    cout << endl;
}

/// @brief Fills vector with characters starting at lower case a.
void initVector(vector <char> &v)
{
    char a = 'a';
    for (int i = 0; i < v.size(); i++)
    {
        v[i] = a;
        a++;
    }
}

/// @brief Converts a character representing a cell to associated vector index
int convertPosition(char position)
{
    int numPosition = position - 'a';
    
    return numPosition;
}

/// @brief Predicate function to determine if a spot in board is available.
bool validPlacement(const vector <char> &board, int position)
{
    if (position >= 0 && position < 9)
    {
        if (board[position] != 'x' && board[position] != 'o')
        {
            return true;
        }
    }
    return false;
}

/// @brief Acquires a play from the user as to where to put her mark
int getPlay(const vector <char> &board)
{
    char position;
    int numPosition;
    bool proceed = false;
    
    while (!proceed)
    {
        cout << "Please choose a position: ";
        cin >> position;
        cout << endl;
        
        numPosition = convertPosition(position);
        proceed = validPlacement(board, numPosition);
    }
    return numPosition;
}


/// @brief Predicate function to determine if the game has been won
bool gameWon(const vector <char> &board)
{
    bool end = false;
    
    for (int i = 0; i < board.size(); i+=3)
    {
        if (board[i] == board[i+1] && board[i] == board[i+2])
        {
            end = true;
        }
    }
    
    for (int i = 0; i < 3; i++)
    {
        if (board[i] == board[i+3] && board[i] == board[i+6])
        {
            end = true;
        }
    }
    
    if (board[0] == board[4] && board[4] == board[8])
    {
        end = true;
    }
    
    if (board[2] == board[4] && board[4] == board[6])
    {
        end = true;
    }
    return end;
}

/// @brief Predicate function to determine if the board is full
bool boardFull(const vector <char> &board)
{
    bool end = true;
    
    for (int i = 0; i < board.size(); i++)
    {
        if (board[i] != 'x' && board[i] != 'o')
        {
            end = false;
        }
    }
    return end;
}


// Global constants for player representation
const int PLAYER1 = 0;
const int PLAYER2 = 1;

int main()
{
    // Variables that you may find useful to utilize
    vector <char> board(9);
    int curPlay;
    int turn = PLAYER1; // Player 1 always goes first and is 'x'

    initVector(board);
    drawBoard(board);
    
    while (!gameWon(board) && !boardFull(board))
    {
        curPlay = getPlay(board);
        
        if (turn == PLAYER1)
        {
            board[curPlay] = 'x';
        }
        
        else
        {
            board[curPlay] = 'o';
        }
        
        if (turn == PLAYER1)
        {
            turn = PLAYER2;
        }
        
        else 
        {
            turn = PLAYER1;
        }
        
        drawBoard(board);
    }
    
    if (!gameWon(board))
    {
        cout << "No one wins\n";
    }
    else if (gameWon(board) && turn == PLAYER1)
    {
        cout << "Player 2 (o's) wins!\n";
    }
    else if (gameWon(board) && turn == PLAYER2)
    {
        cout << "Player 1 (x's) wins!\n";
    }

    return 0;
}