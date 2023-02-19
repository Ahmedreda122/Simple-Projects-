#include <iostream>
#include <fstream>
#include <string>
#include <map>
#include <cstring>
#include <cctype>
#include <algorithm>
#include <vector>
#include <set>

using namespace std;

// map container
map<string, int> freqTable;
vector<string> words;

/* 
Display a frequency table for a given text file.
A frequency table lists words and the number of times each word appears in a document or a file 
*/
void countWordsFrq(map<string, int>& freqTable);
void load(fstream &file, string filename);
void print(const map<string, int>& freqTable);


int main()
{
  fstream file;
  string filename;

  cout << "Please enter the name of the file: ";
  cin >> filename;
  filename += ".txt";

  load(file, filename);
  countWordsFrq(freqTable);
  print(freqTable);
}


void load(fstream &file, string filename)
{
  string token;
  // Opening file in reading mode
  file.open(filename, ios::in);

  while(file >> token)
  {
    for (int i = 0; i < token.length(); ++i)
    { 
      if(ispunct(token[i]) && token[i] != '-')
      {
        // if punctuation was in the end of the token, just delete it
        if (i == token.length() - 1)
        {
          token.erase(i, 1);
        }
      /* If the punctuation was found in the middle, we divide the token into two tokens, 
        and push the before punc part of the original token into the map, 
        then continueing looping on the second token that was after the removed punctuation */ 
        else
        {
          // Pushing the before punc part of the original token
          freqTable.insert(pair<string, int> ((token.substr(0, i)), 0));
          words.push_back(token.substr(0, i));

       /* Erasing the before punc part of the original token with the punctuation
          Updating token value with the new token(after punc part) */
          token.erase(0, i+1);

       /* Returning i to represent the first character of the new token
          -1 will be index 0 in the coming for loop */
          i = -1;
        }
      }
      else if(isupper(token[i]))
      {
        token[i] = tolower(token[i]);
      }
    }
    // string tmpStr = token;
    // tmpStr.erase(remove(tmpStr.begin(), tmpStr.end(), ' '), tmpStr.end());
    // if (!tmpStr.empty())
    // {
      freqTable.insert(pair<string, int>(token, 0));
      words.push_back(token);
    //}
  }
}

void countWordsFrq(map<string, int>& freqTable)
{
  for(auto it = freqTable.begin(); it != freqTable.end(); it++)
  {
    it->second = count(words.begin(), words.end(),it->first);
  }
}

void print(const map<string, int>& freqTable)
{
  for(auto it = freqTable.begin(); it != freqTable.end(); it++)
  {
    cout << it->first << " : " << it->second << endl;
  }
}