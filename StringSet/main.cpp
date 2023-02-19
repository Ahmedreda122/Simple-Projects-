// Program: StringSet Class
// Author: Ahmad Reda Bayoumi
// Date: November 2022
// ...........................................................................................
#include "StringSet.cpp"

// Test Cases
int main()
{
  fstream file;
  StringSet _file(file, "ice.txt"); 
  StringSet _string("Chocolate ice cream, chocolate milk, and chocolate bars are delicious.");

  cout << "File Set:" << endl;
  _file.printSet();

  StringSet set2 = _file + _string;
  cout << "_file union with _string: " << endl;
  set2.printSet();

  cout << "-----------------------" << endl;
  StringSet set3 = _file * _string;
  cout << "intersection between _file and _string: " << endl;
  set3.printSet();

  cout << "-----------------------" << endl;
  cout << "sim between _file and _string: "<< _file.similarity(_string) << endl;

  fstream file2;
  StringSet _file2(file2, "ahmed.txt");
  cout << "-------------------------" << endl;
  cout << "_file2: " << endl;
  _file2.printSet();
  cout << "-------------------------" << endl;
  cout << "sim between _file2 and _string: "<< _file2.similarity(_string) << endl;

  fstream file3;
  StringSet _file3(file3, "file3.txt");
  cout << "-------------------------" << endl;
  cout << "_file3: " << endl;
  _file3.printSet();
  cout << "-------------------------" << endl;
  cout << "sim between _file3 and _string: "<< _file3.similarity(_string) << endl;

  cout << "size of _string: "<< _string.setSize() << endl;
  
  cout << "-----------------------" << endl;

  _string.removeString("Chocolate");
  cout << "Chocolate Removed from _string: " << endl; 
  _string.printSet();

  cout << "------------------------" << endl;

  cout << "Before clear: " << endl;
  _file.printSet();
  _file.clearSet();
  cout << "After clear: " << endl;
  _file.printSet();
}