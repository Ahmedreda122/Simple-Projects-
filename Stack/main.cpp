#include "Stack.hpp"

template <typename T>
void menu(Stack<T>& myStack);

void manageStack();

int main()
{
  manageStack();
}
/*
Displays a menu and allows the user to create a stack of the size he likes 
and give him the options to check top element, push or pop elements from the stack.
*/
void manageStack()
{
  int size = 0;
  string type;
  cout << "\n\t\tWelcome to Stack Manager\n" << endl;
  
  while (true)
  {
    try
    {
      cout << "Please Enter the size of your stack: \n>";
      cin >> size;

      //If user enter a string or a number less than 0
      if (cin.fail() || size < 0)
      {
        throw invalid_argument("Invalid Input.");
      }
      break;
    }

    catch (const invalid_argument e)
    {
      // Print error message
      cout << e.what() << endl;
      cout << "Try again, ";
    }
    // Clears the error flags on cin caused by the failure that happens when entering invalid input
    cin.clear();
    // Ignoring previous input up to 9999 or when a newline char is located
    cin.ignore(9999, '\n');
  }

  while(true)
  {
    cout << "Enter the type of your stack(i for Int, d for double, s for string, c for char): \n>";
    cin >> type;

    if (type == "i")
    {
      Stack<int> IntStack(size);
      menu(IntStack);
      return;
    }

    else if (type == "d")
    {
      Stack<double> DStack(size);
      menu(DStack);
      return;
    }
    else if (type == "s")
    {
      Stack<string> strStack(size);
      menu(strStack);
      return;
    }
    else if (type == "c")
    {
      Stack<char> ChrStack(size);
      menu(ChrStack);
      return;
    }
    else
    {
      cout << "Invalid Input, Please try again." << endl;
    }
  }  
}

template <typename T>
void menu(Stack<T>& myStack)
{
  bool run = true;
  string option;
  T element;

  while(run)
  {
    cout << "Please, Choose one Option to perform to your Stack\n1-Push an Element\n2-Pop an Element From Stack\n3-Get Top Element from the Stack\n4-Exit\nStack Size: "<< myStack.Size() << "\n>";
    cin >> option;

    if (option == "1")
    {
      while (true)
      {
        try
        {
          cout << "Enter an Element to push it on the Stack: \n>";
          cin >> element;

          //If user enter an invalid input
          if (cin.fail())
          {
            throw invalid_argument("Invalid Input.");
          }
          break;
        }

        catch (const invalid_argument e)
        {
          // Print error message
          cout << e.what() << endl;
          cout << "Try again, ";
        }
        // Clears the error flags on cin caused by the failure that happens when entering invalid input
        cin.clear();
        // Ignoring previous input up to 9999 or when a newline char is located
        cin.ignore(9999, '\n');
      }

      try
      {
        myStack.push(element);
      }

      catch(StackOverflowException overflow)
      {
        cout << overflow.what() << endl;
      }
    }
    else if (option == "2")
    {
      try
      {
        myStack.pop();
      }

      catch(StackEmptyException Ex)
      {
        cout << Ex.what();
      }
      cout << "We have poped an element from your stack." << endl;
    }
    else if (option == "3")
    {
      if (myStack.empty())
      {
        myStack.top();
        continue;
      }
      cout << "Top Element is " << myStack.top() << endl;
    }
    else if (option == "4")
    {
      run = false;
      break;
    }
    else
    {
      cout << "Invalid Input, Please try again." << endl;
    }
  }
    
}