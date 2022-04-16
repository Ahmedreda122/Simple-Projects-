#include <iostream>
#include <cctype>
#include <string>
#include <cmath>
#include <algorithm>

using namespace std;

// defining decrypted globally
string decrypted = "";

string& decrypt (string txt , string& decrypted);
void encrypt(string& txt);

int main()
{
	
    cout << "1- Encrypt a text using Baconian cipher\n" <<
            "2- Decrypt a text using Baconian cipher\n" <<
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
                encrypt(txt);
                return 0;
        
            // IF the choice = 2, Ask the user for encrypted text and print the decrypted one.
            case ('2'):

                cout << "Enter a text to decrypt it (Every decrypted letter contain 5 characters equal to a or b): ";
                // Getting a text from the user
                getline(cin, txt);
     
                // Decrypting the encrypted text
                cout << decrypt(txt, decrypted);
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


void encrypt(string& txt)
{
	// removing the spaces from the text to the end of it, then returning a pointer to the beginning of the removed spaces
    auto removed = remove(txt.begin(), txt.end(), ' ');
    // Erasing the spaces from the end of the text
    txt.erase(removed, txt.end());

  	for (int i = 0; i < txt.length(); ++i)
  	{
		// Array for binary representation of character index in alphabet  
		int bin[5] = {0,0,0,0,0};
		txt[i] = (char) tolower(txt[i]);
		// Getting the letter index in alphabet
		int index = (int) txt[i] - 'a';

		int j = 0;
		// Getting the binary representation of the letter index
		while (index != 0)
		{
			if (index % 2 > 0)
			{
				bin[j] = 1;
			}
			else
			{
				bin[j] = 0;
			}

			++j;

			index = index / 2;
		}

		//returning binary ascii code of the letter as a for 0 and b for 1.
		for(int k = 4; k >= 0; --k)
		{
			if (bin[k] == 0)
				cout << 'a';
			else 
				cout << 'b';	
		}
		cout << " ";
			
    }
	
}


string& decrypt (string txt , string& decrypted)
{
	int charIndex;
	int counter;
	// removing the spaces from the text to the end of it, then returning a pointer to the beginning of the removed spaces
	auto removed = remove(txt.begin(), txt.end(), ' ');
	// Erasing the spaces from the end of the text
	txt.erase(removed, txt.end());
	// Checking if every letter written as a five character
	if (txt.size() % 5 != 0)
	{
		return decrypted = "You MUST Enter every encrypted letter as FIVE character";
	}   	

	for (int j = 0; j < txt.size(); j += 5)
	{
		charIndex = 0;
		// counter for count the index of every five characters separated.
		counter = -1;
		// Looping over every five characters
		for (int i = j; i < (j+5); ++i)
		{
			// incrementing the counter
			++counter;
			// that means that this char equal one
			if ((char) tolower(txt[i]) == 'b')
			{
				// getting decimal representation of character, we start at 2 up to power 4 cause we takes the characters from the right.
				charIndex += pow(2 , (4-counter));
			}
			// if the character not a or b, tell that to the user
			else if ((char) tolower(txt[i])!= 'a')
			{
				return decrypted = "You MUST Enter every encrypted letter as a,b,A,B only";
			}
		}
		// Getting the decrypted text by adding every char index (starting from 0) in alphabet to decimal ascii code of a
		decrypted += (char) (charIndex + 'a');
	}

	// Returning decrypted text by reference
	return decrypted;

}