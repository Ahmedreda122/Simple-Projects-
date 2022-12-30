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
    // Clear cin buffer and ignore previous input
    cin.clear();
    cin.ignore(999, '\n');
  }

  cout << "You Entered: " << num << endl;
}