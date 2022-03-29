/*
	Author: Ahmad Reda Bayoumy
	Date: 24 / 3 / 2022
	Description: This code represent Rail cipher method to encrypt and decrypt text.
*/

#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

// Defining the functions.
string encrypt(string txt);

string decrypt(string txt);

// Defining encrypted globally.
string encrypted;

int main()
{
    cout << "1- Encrypt a text using Rail Cipher.\n" <<
            "2- Decrypt a text using Rail Cipher.\n" <<
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
                cout << encrypt(txt);
                return 0;
        
            // IF the choice = 2, Ask the user for encrypted text and print the decrypted one.
            case ('2'):

                cout << "Enter a text to decrypt it: ";
                // Getting a text from the user
                getline(cin, txt);        
                // Decrypting the encrypted text
                cout << decrypt(txt);
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

// A function to encrypt a text
string encrypt(string txt)
{
    // Defining the three rows
    string row1, row2, row3;

    // removing the spaces from the text to the end of it, then returning a pointer to the beginning of the removed spaces
    auto removed = remove(txt.begin(), txt.end(), ' ');
    // Erasing the spaces from the end of the text
    txt.erase(removed, txt.end());
	
    // Dividing the text to three rows vertically
	for (int i = 0; i < txt.length(); i += 4)
    {
	    row1 += tolower(txt[i]);

        if (i + 1 < txt.length())

	        row2 += tolower(txt[i + 1]);

        if (i + 2 < txt.length())

	        row3 += tolower(txt[i + 2]);
        
        if (i + 3 < txt.length())

            row2 += tolower(txt[i + 3]);
        
	       
	}
	
    // Merging the three rows to generate the encrypted text
    encrypted = row1 + row2 + row3;  
	   
    return encrypted;
}

// Rounding the num if the decimal bigger than or equal the num and 0.25 of it, truncate it if the it is lower
double round(double num)
{
  int rounded = num;
  double decimal = num - rounded;

  if (decimal >= 0.25)
  {
    rounded++;
  }
  
  return rounded;
}

// Decrypting the text
string decrypt(string txt)
{
    string row1, row2, row3;

    // Getting the length of the row1 by deviding the text length over 4 one for the letter and 3 for spaces, a... b. --> if the result equal 1.5 that means that the row contain 2 letters, because 1 represented a letter and three spaces like this for example b... n. 
    double len_row1 = round(txt.length() / 4.0);

    string decrypted; 
    int counter = 0;

    for(int i = 0; i < txt.length(); ++i)
    {
        // Getting the three rows content to decrypt the text. 
        if (i < len_row1)
        {
            row1 += txt[i];
        }
        // Getting the length of the row2 by deviding the text length over 2 one for a space and the other one for the letter --> .a .b .c
        else if (i < (len_row1 + (txt.length() / 2))) 
        {
            row2 += txt[i];
        }
        else 
        {
            row3 += txt[i];
        }

    }

    /* 
    Getting the decrypted text from the rows:
        This is an example of encrypt word "defend the east wall of the castle"
        row1: d . . . n . . . e . . . t . . . l . . . h . . . s . . .
        row2: . e . e . d . h . e . s . w . l . o . t . e . a . t . e
        row3: . . f . . . t . . . a . . . a . . . f . . . c . . . l . 
        
        If we notice that we can get the text by getting a letter from row1 then row2 then row3 then row2 again 
        and repeating this process until we finish
    */
    for(int i = 0; i < row1.length(); ++i)
    {   
        decrypted += row1[i];
        // Making counter to get two letters from row2 for each loop 
        decrypted += row2[counter];
        decrypted += row3[i];
        // if the counter reach the elemnt that exist before last one
        if (counter < row2.length()-1)
        {
            // take the last element by increasing the counter by one
            decrypted += row2[++counter];
        }  
        ++counter;
    }
     
    return decrypted;
}
