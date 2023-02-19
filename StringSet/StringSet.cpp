#include "StringSet.h"

StringSet::StringSet(fstream &file, string filename)
{
  string token;
  // Opening file in reading mode
  file.open(filename, ios::in);

  while(file >> token)
  {
    for (int i = 0; i < token.length(); ++i)
    { 
      if(ispunct(token[i]))
      {
        // if punctuation was in the end of the token, just delete it
        if (i == token.length() - 1)
        {
          token.erase(i, 1);
        }
        // If the punctuation was found in the middle, we divide the token into two tokens and push the before punc part of the original token into the set then continueing looping on the second token that was after the removed punctuation
        else
        {
          //Pushing the before punc part of the original token
          set.push_back(token.substr(0, i));
          // Erasing the before punc part of the original token with the punctuation
          // updating token value with the new token(after punc part)
          token.erase(0, i+1);
          // Returning i to represent the first character of the new token
          // -1 will be index 0 in the coming for loop
          i = -1;
        }
      }
      else if(isupper(token[i]))
      {
        token[i] = tolower(token[i]);
      }
    }
    set.push_back(token);
  }
}

StringSet::StringSet(string sentence)
{
  string word = "";

  // Adding a space in the end of the sentence to push back the last word to the set
  sentence += ' ';

  for (auto i : sentence)
  {
    /*
      if current char is a space or a punctuation ignore it and push the word before it to the set, 
      And clear word string to receive the next letters and hold the next word.
    */ 
    if (i == ' ' || ispunct(i))
    {
      // if there is no word to push it, continue the loop in order to get the next letter if exist
      if (word == "")
      {
        continue;
      }
      set.push_back(word);
      word = "";
    }
    else
    {
      // if this char is a letter, then add this letter(in a lowercase) to the word string until a space or a punctuation occur
      word += tolower(i);
    } 
  }
}

void StringSet::addString(string str)
{
  set.push_back(str);
}

void StringSet::removeString(string str, bool firstOccurOnly) 
{
  // Erasing the spaces from it
  str.erase(remove_if(str.begin(), str.end(), ::isspace), str.end());
  // Transforming the whole string to lowercase by Getting every character in the string and perform tolower function to it.
  transform(str.begin(), str.end(), str.begin(), ::tolower);

  for (int i = 0; i < set.size(); i++)
  {
    if (set[i] == str)
    {
      // Erasing str from the set 
      set.erase(set.begin() + i);
      if (firstOccurOnly)
      {
        break;
      }
    }
  }

}


void StringSet::printSet()
{
  for (string i : set)
  {
    cout << i << endl;
  }
}

StringSet StringSet::operator+ (StringSet secondSet)
{
  StringSet _union; // union = (this - intersec) + intersec(this, secondSec) + (secondSet - intersec)

  // StringSet filled with intersected elements from the two sets
  StringSet intersec = (*this) * secondSet;

  // Copy of this set to modify it
  StringSet thisSet = *this;

  for (int j = 0; j < intersec.set.size(); j++)
  {
    // Make a copy of this set but without intersected elements with second set (Delete intersected elements once)
    thisSet.removeString(intersec.set[j], true);
    // Remove the intersected elements with this set from the second set (Delete intersected elements once)
    secondSet.removeString(intersec.set[j], true);
  }

  for (int i = 0; i < thisSet.set.size(); i++)
  {
    // Adding remaining elements from this set to the union
    _union.set.push_back(thisSet.set[i]);
  }

  // Adding intersected elements one time in the _union set
  for (int j = 0; j < intersec.set.size(); j++)
  {
    _union.set.push_back(intersec.set[j]);
  } 

  for (int i = 0; i < secondSet.set.size(); i++)
  {
    // Adding remaining elements from secondSet to the union
    _union.set.push_back(secondSet.set[i]);
  }

  return _union;
}



StringSet StringSet::operator*(const StringSet& secondSet)
{
  StringSet intersec;
  // if you trying to get the intersection of two same sets
  if (set == secondSet.set)
  {
    return *this;
  }

  for (int i = 0; i < set.size(); ++i)
  {
    for (int j = 0; j < secondSet.set.size(); ++j)
    {
      if (set[i] == secondSet.set[j])
      {
        intersec.set.push_back(set[i]);
        // Break to avoid adding the element again if it is repeated (if it is repeated twice, will take 4 occurences if we don't break).
        break;
      }
    }
  }

  return intersec;
}

double StringSet::similarity(StringSet secondSet)
{
  // Make Sets Distinct
  // Distinct version of this->set
  StringSet doc;
  // Distinct version of secondSet
  StringSet query;

  // Copy of this set
  StringSet thisSet = *this;

  for (int i = 0; i < thisSet.set.size(); ++i)
  {
    // if we not at the last element
    if (i != doc.set.size() - 1)
    {
      // Push current element to doc set
      doc.set.push_back(thisSet.set[i]);
      // Delete that element from the this set
      thisSet.removeString(thisSet.set[i]);
      // Decrease "i" because i deleted the current element --> ahmed(index 0) reda(index1) --> ahmed(removed) reda(index 0)
      --i;
    }
    else
    {
      // if we are at the last element, just push this last element to the doc set
      doc.set.push_back(thisSet.set[i]);
    }
  }
  // Doing the previous process on query and secondSet
  for (int i = 0; i < secondSet.set.size(); ++i)
  {
    if (i != secondSet.set.size() - 1)
    {
      query.set.push_back(secondSet.set[i]);
      secondSet.removeString(secondSet.set[i]);
      --i;
    }
    else
    {
      query.set.push_back(secondSet.set[i]);
    }
  }

  // similarity = The size of set of common words / (sqrt size of Doc * sqrt size of Query)
  return ( (doc * query).setSize() ) / ( (sqrt(doc.setSize())) * (sqrt(query.setSize())) );
}