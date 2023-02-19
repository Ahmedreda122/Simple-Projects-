// Implementation of a Stack

#ifndef STACK_HPP
#define STACK_HPP

#include <iostream>
#include <list>
#include <string>
#include <vector>
#include <exception>
#include <sstream>

using namespace std;

class StackOverflowException: public exception
{
private:
  int fixedSize;
public:
  StackOverflowException(int Size) : fixedSize(Size){}
  string what()
  {
    stringstream error; 
    error << "Stack overflow.(cannot push to it) Fixed size = " << fixedSize << endl;
    return error.str();
  }
  
};

class StackEmptyException: public exception
{
public:
  const char* what()
  {
    return ("Stack is Empty. Cannot pop from it.\n");
  }
};

template <typename T>
class Stack
{
private:
  vector<T> stack;
  int fixedSize;
public:
  Stack(int size = 0): fixedSize(size){}

  Stack(const Stack& other)
  {
    stack = other.stack;
    fixedSize = other.fixedSize;
  }

  Stack& operator=(const Stack& other)
  {
    if (this != &other)
    {
      stack = other.stack;
      fixedSize = other.fixedSize;
    }
    return *this;
  }

  ~Stack()
  {
    stack.clear();
  }

  void push(T value)
  {
    if (stack.size() == fixedSize)
    {
      StackOverflowException overflow(fixedSize);
      throw overflow;
      return;
    }
    stack.push_back(value);
  }

  void pop()
  {
    if (stack.size() == 0)
    {
      StackEmptyException emptyEx;
      throw emptyEx;
      return;
    }
    stack.pop_back(); 
  }

  T top() const
  {
    if (stack.size() == 0)
    {
      cout << "Stack is empty!" << endl;
      return T();
    }
    return stack[stack.size() - 1];
  }

  int Size() const
  {
    return fixedSize;
  }

  bool empty() const
  {
    return (stack.size() == 0);
  }

};

#endif