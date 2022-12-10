#include <string.h>
#include <cctype>
#include <iostream>
#include <algorithm>

using namespace std;

string& make_key(string& key);
void encrypt(string txt, string key);
void decrypt(string txt, string key);

int main()
{
    string key;

    cout << "Please, Enter a key of 5 characters: ";

    cin >> key;

    if (key.size() != 5)
    {
        printf("Key must contain 5 characters.\n");
        return 1;
    }
    
    key = make_key(key);

    int keyLen = key.size();

    for (int i = 0; i < keyLen; i++)
    {
        if (isalpha(key[i]) == 0)
        {
            printf("Key must only contain alphabetic character.\n");
            return 1;
        }
    }

    for (int t = 0; t < keyLen; t++)
    {
        for (int r = t + 1; r < keyLen; r++)
        {
            if ((int)key[t] == (int)key[r])
            {
                printf("Key must not contain repeated character.\n");
                return 1;
            }
        }
    }

    cout << "1- Encrypt a text using substitution.\n" <<
            "2- Decrypt a text using substitution.\n" <<
            "3- Exit.\n" <<
            "Please Choose a number to perform its content: ";

    char choice;
    string txt;
    
    while (true)
    {
        // Getting the chosen option from the user   
        cin >> choice;
        // ignoring what stored in cin from previous input
        cin.ignore(9999, '\n');
        
        switch(choice)
        {
            // IF the choice = 1, Ask the user for text and print it encrypted
            case('1'):
                
                cout << "Enter a text to encrypt it: ";
                // Getting a text from the user
                getline(cin, txt);
                // Print encrypted text
                encrypt(txt, key);
                return 0;
        
            // IF the choice = 2, Ask the user for encrypted text and print the decrypted one.
            case ('2'):

                cout << "Enter a text to decrypt it: ";
                // Getting a text from the user
                getline(cin, txt);        
                // Decrypting the encrypted text
                decrypt(txt, key);
                return 0;

            // IF the user chose exit, exit returning 1
            case('3'):

                return 1;

            default:
                cout << "Unexpected input. Please, Try again: ";
                break;
        }
    }



}

void encrypt(string txt, string key)
{
    // Here is your output
    cout << "ciphertext: ";

    for (int i = 0; i < txt.size(); ++i)
    {
        if (isalpha(txt[i]))
        {
            if (islower(txt[i]))
                cout << (char) tolower(key[(int) txt[i] - 'a']); 
            else
                cout << (char) tolower(key[(int) txt[i] - 'A']); 
        }
        else
        {
            cout << (char) tolower(txt[i]);
        }
                   
    }
}

void decrypt(string txt, string key)
{
    string letters = "abcdefghijklmnopqrstuvwxyz";
    
    
    // Here is your output
    cout << "decryptedtext: ";

    for (int i = 0; i < txt.size(); ++i)
    {
        if (isalpha(txt[i]))
        {
            for (int j = 0; j < 26; ++j)
            {
                if ( (char) toupper(txt[i]) == key[j])
                    cout << letters[j];  
            }        
        }
        else
        {
            cout << (char) tolower(txt[i]);
        }
                   
    }
}

string& make_key(string& key)
{
    string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char index;
    for (int i = 0; i < key.size(); ++i)
    {
        key[i] = toupper(key[i]);
        index = key[i];
        auto removed = remove(letters.begin(), letters.end(), index);

        letters.erase(removed, letters.end());
    }
    key = key + letters;

    return key;
}
