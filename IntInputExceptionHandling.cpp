/*
  Author: Ahmad Reda Bayoumy
  Program: Handling Integer Input Exception
*/
#include <iostream>
#include <exception>

using namespace std;

int main()
{
  int num;
  
  while (true)
  {
    try
    {
      cout << "Enter a number: \n>";
      cin >> num;

      //If user enter a string or invalid input
      if (cin.fail())
      {
        throw invalid_argument("Invalid Input.");
      }
      break;
    }

    catch (const invalid_argument e)
    {
      // print error message
      cout << e.what() << endl;
      cout << "Try again, ";
    }
    // Clears the error flags on cin caused by the failure that happens when entering invalid input
    cin.clear();
    // Ignoring previous input up to 9999 or when a newline char is located
    cin.ignore(9999, '\n');
  }

  cout << "You Entered: " << num << endl;
}
