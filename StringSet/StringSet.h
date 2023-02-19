// Program: StringSet Class
// Author: Ahmad Reda Bayoumi
// Date: November 2022
// ...........................................................................................
/* Document similarity measures are very important in the field of information
 retrieval and search engines. They are measures that tell us how similar to documents are in terms of
 their word content. They can be used to find similar documents or to find how close a document is to a
 query on a search engine.
*/  

#include <iostream>
#include <string>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;

class StringSet
{
private:
  vector<string> set;
public:
  StringSet() = default;
  StringSet(fstream &file, string filename); // Loads a file into tokens(words (lowercased) without punctecion) to store these tokens into the set
  StringSet(string sentence); // Break a string into tokens(words (lowercased) without punctecion) and load it into the set
  void addString(string str); 
  // Remove a every occurence of str from the set by default, and offer a feature to remove the first occurence only
  void removeString(string str, bool firstOccurOnly = false); 
  void clearSet(){ set.clear(); }
  int setSize() { return set.size(); } // Returns the number of strings in the set
  StringSet operator+(StringSet secondSet); // Returns the union the two sets 
  StringSet operator*(const StringSet& secondSet); // Returns the intersection of the two sets
  void printSet();
  /* 
    Once we have a "query"(secondSet) represented as a set of words
    and a document "doc" represented as a set of words (each word counts once even if repeated in document multiple times),
    The similarity between Query and Doc is computed by: The size of set of common words / (sqrt size of Doc * sqrt size of Query)
  */ 
  double similarity(StringSet secondSet); // Returns ( (Doc * Query).setSize() ) / ( (sqrt(Doc.setSize())) * (sqrt(Query.setSize())) );
  /*
    Make A Distinct versions of this->set and secondSet.set
    Doc --> distinct version of (*this)
    Query --> distinct version of secondSet
  */
};





