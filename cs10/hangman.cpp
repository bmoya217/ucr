#include <iostream>
#include <string>
#include <ctime>
#include <ios>
#include <iomanip>
#include <cstdlib>
#include "assn.h"

using namespace std;

/// @brief Puts dashes in place of alphabetic characters in the phrase
string setupUnsolved(string phrase)
{
    string unsolved = phrase;
    for (int i = 0; i < phrase.size(); i++)
        if (isalpha(phrase[i]))
            unsolved[i] = '-';

    return unsolved;
}

/// @brief Replaces the dashes with the guessed character
string updateUnsolved(string phrase, string unsolved, char guess)
{
    for (int i = 0; i < phrase.size(); i ++)
        if (guess == phrase[i])
            unsolved[i] = phrase[i];

    return unsolved;
}

/// @brief Gets valid guess as input
char getGuess(string prevGuesses)
{
    char guess;
    cout << endl << "Enter a guess: ";
    cin >> guess;
    
    while ((prevGuesses.find(guess) < prevGuesses.size()) || !(isalpha(guess)))
    {
        cout << endl << "Invalid guess! Please re-enter a guess: ";
        cin >> guess;
    }
    
    return guess;
}

int main()
{
    char guess;
    string phrase, unsolved, prevGuesses;
    int guessRemain = 7;
    
    cout << "Enter phrase: ";
    getline(cin,phrase);
    clearScreen();
    
    unsolved = setupUnsolved(phrase);
    cout << "\nPhrase: " << unsolved << endl;
    
    while (guessRemain > 0 && unsolved != phrase)
    {
        guess = getGuess(prevGuesses);
        clearScreen();
        prevGuesses += guess;
        string unsolvedNew = updateUnsolved(phrase, unsolved, guess);
        if (unsolvedNew == unsolved)
            guessRemain --;
        
        unsolved = unsolvedNew;
        
        cout << "\nPhrase: " << unsolved << endl;
        cout << "\nGuessed so far: " << prevGuesses;
        cout << "\nWrong guesses left: " << guessRemain << endl;
    }
    
    if (unsolved == phrase)
        cout << "\nCongratulations!!\n";
    
    else
        cout << "\nYou lost!\n";
    
    return 0;
}