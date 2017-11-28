#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector <string> acquireKeys()
{
    string key;
    vector <string> keys;
    
    for (int i = 0; i < 3; i++)
    {
        cin >> key;
        keys.push_back(key);
    }
    return keys;
}

vector <string>  acquireCompWords()
{
    string compWord;
    vector <string> compWords;
    
    for (int i = 0; cin >> compWord; i++)
    {
        compWords.push_back(compWord);
    }
    return compWords;
}

string findMatches (string key,vector<string> compWords, int &overlap)
{
    string word;
    int matchIndex = -1;
    int count;
    overlap = 0;
    
    for (int i = 0; i < compWords.size(); i++) // picks word
    {
        count = 0;
        word = compWords[i]; // initialized said word
        int potentialMatchIndex = i;
        for (int i = 0; i < key.size(); i++)
        {
            // add substr functyion
            if (word.substr(0,key.size()-i)==key.substr(i,key.size()))
            {
                count = key.size()-i;
            }
        }
        if (overlap < count)
        {
            overlap = count;
            matchIndex = potentialMatchIndex;
        }
        
        // from behind overlap
        for (int i = 0; i < word.size(); i++)
        {
            if (key.substr(0,word.size()-i)==word.substr(i,word.size()))
            {
                count = word.size()-i;
            }
        }
        if (overlap < count)
        {
            overlap = count;
            matchIndex = potentialMatchIndex;
        }
    }
    if (matchIndex == -1)
    {
        return "No Match";
    }
    return compWords[matchIndex];
}

int main ()
{
    vector <string> keys = acquireKeys();
    vector <string> compWords = acquireCompWords();
    vector <string> matches;
    vector <int> overlap(3);
    
    // finds matches and stores their overlap value
    for (int i = 0; i < 3; i++)
    {
        matches.push_back(findMatches(keys[i], compWords, overlap[i]));
    }
    
    for (int i = 0; i < 3; i++)
    {
        cout << "Key: " << keys[i] << endl;
        cout << "Match: " << matches[i] << endl;
        cout << "Overlap: " << overlap[i] << endl << endl;
    }
    return 0;
}