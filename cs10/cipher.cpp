#include <iostream>
#include <string>
using namespace std;

int main()
{
    // variables
    string method;
    string type;
    string word;
    string map1 = "abcdefghijklmnopqrstuvwxyz";
    string map2;
    int s = 0;
    int e;
    int i;
    
    // what cryption method
    cout << "What is method (encryption of decryption)? ";
    cin >> method;
    cout << endl;
    
    if (method == "encryption")
    {
        cout << "What is the translation map (type 'default' to use default): ";
        cin >> map2;
        cout << endl;
        
        // sets map to default
        if (map2 == "default")
        {
            map2 = "zyxwvutsrqponmlkjihgfedcba";
        }
        
        // kills program for bad map size
        else if (map2.size() != map1.size())
        {
            cout << "Error: invalid translation map size." << endl;
            return 0;
        }
        
        cout << "What is the single word to translate: ";
        getline(cin,word);
        getline(cin,word);
        cout << endl;
        
        // checks for a validity of inputed word
        for(i = 0;i<word.size();i++)
        {
            if(word[i]<'a' || word[i]>'z')
            {
                if (word[i] == ' ')
                {
                    
                }
                
                else
                {
                    cout << "Error: encryption cannot be performed.";
                    return 0;
                }
            }
        }
        
        // encrypts
        for(i = 0;i<word.size();i++)
        {
            if (word[i] == ' ')
            {
                word[i] = ' ';
            }
            else
            {
                word[i] = map2[map1.find(word[i])];
            }
        }
        
        cout << "Encrypted word: " << word << endl;
    }
    
    // decryption -- steps almost identical 
    else if (method == "decryption")
    {
        cout << "What is the translation map (type 'default' to use default): ";
        cin >> map2;
        cout << endl;
        
        if (map2 == "default")
        {
            map2 = "zyxwvutsrqponmlkjihgfedcba";
        }
        
        else if (map2.size() != map1.size())
        {
            cout << "Error: invalid translation map size." << endl;
            return 0;
        }
        
        cout << "What is the single word to translate: ";
        getline(cin,word);
        getline(cin,word);
        cout << endl;
        
        // decrypts until cant be preformed
        for(i = 0;i<word.size();i++)
        {
            if (word[i] == ' ')
            {
                word[i] = ' ';
            }
            else
            {
                word[i] = map1[map2.find(word[i])];
            }
            
            if (word[i]<'a' || word[i]>'z')
            {
                if (word[i] == ' ')
                {
                    
                }
                else 
                {
                    cout << "Error: decryption cannot be performed.";
                    return 0;
                }
            }
        }
        
        cout << "Decrypted word: " << word << endl;
    }
    
    // if encryption or decryption isnt entered the program dies
    else 
    {
        cout << "Error: invalid method choice." << endl;
    }
    
    return 0;
}