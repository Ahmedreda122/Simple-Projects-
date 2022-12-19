/* 
Author: Ahmad Reda Bayoumy

Explanation of progrom purpose: The game of dominos is played with rectangular pieces composed of two connected squares, each of 
which is marked with a certain number of dots. For example, each of the following five pairs
represents a domino:
1|4  2|6  4|4  6|1  4|3

Dominos can be connected end-to-end to form chains, subject to the condition that two dominos can be 
linked together only if the numbers match. For example, we can form a chain consisting of all five of 
these dominos by connecting them in the following order:
2|6  6|1  1|4  4|4  4|3

->In our Program we find this chain with positive number you enter not just from 1 to 6

->Note: In traditional dominos, you can rotate a domino y so that its numbers are reversed. As a 
simplification in this problem, this operation is not allowed, which means that the dominos must appear 
in their original orientation.
*/

#include <iostream>
#include <vector>

using namespace std;

struct dominoT {
    int leftDots;
    int rightDots;
};

vector<dominoT> setDominos();
bool FormsDominoChain(vector<dominoT>& dominos);
vector<dominoT> res(0);
bool firstime = true;
void printChian();

int main()
{
    auto dominos = setDominos();
    if (FormsDominoChain(dominos))
    {
        printChian();
        return 0;
    }
    else
    {
        cout << "false";
        return 1;
    }

}

bool FormsDominoChain(vector<dominoT>& dominos)
{
    // static var to track how many times the func repeated(the location of the current func)
    static int track = 0;
    track++;

    if (dominos.size() <= 1)
    {
        return true;
    }

    for (int i = 0; i < dominos.size(); i++)
    {
        // if we enter the recursion process(we are in repeated func), so we have to only check dominos[i].rightside (domino j in the previous round(func)) with left sides in the remain dominos and do not increase i 
        // "i" will only increase in the origin (first) round (the non-repeated one)
        if (track > 1 && i > 0)
        {  
            // decrease the track var, because we will break and return to the previous func(func #(track - 1))
            track--;
            break;
        }

        for (int j = 0; j < dominos.size(); j++)
        {
            if (dominos[i].rightDots == dominos[j].leftDots && (i != j))
            {
                vector<dominoT> v(dominos.begin(), dominos.end()); 
                v.erase(v.begin() + i, v.begin() + (i+1));

            // Make domino j in the front of v vector

                // if j == 0 so its already in the front
                if (j != 0)
                {
                    // if i erased index after index j so index j stay in the same position or index
                    if (j < i)
                    {
                        // Swap between v[j] and v[0]
                        auto tmp = v[0];
                        v[0] = v[j];
                        v[j] = tmp;
                    }
                    else
                    {
                        // Else if i erased index before index j, so index j will be index j - 1 in the v vector(after erasing)
                        // Swaping between v[j - 1] and v[0]
                        auto tmp = v[0];
                        v[0] = v[j - 1];
                        v[j - 1] = tmp;
                    }
                }
            /*
                If FormsDominoChain returned false after passing to it the new vector with domino j in the front,
                Continue the loop searching for another match 
            */   
                if (FormsDominoChain(v) == false)
                {
                    continue;
                }
                // Else if branch succeed
                else
                {
              /*  Note: that we pushing elements from last of the chain to the begin, 
              Because the first return of true coming from the Base Case, 
              When the v vector holding only the last element in the dominos and the dominos[i] holding the before last element

                In the first return true (from the end of the chain)  
                    Push_back the the last element in the dominos chain by pushing back the v[0]
                    then push_back the before last element in the dominos chain by pushing back the domino[i]
                */
                    if (firstime)
                    {
                        res.push_back(v[0]);
                        res.push_back(dominos[i]);
                        firstime = false;
                    }
                    // Else return the remain element in the chain by pushing dominos[i]
                    else
                    {
                        res.push_back(dominos[i]);
                    }
                    return true;
                }
            }
        }
    }
    // if this chain not exist return false
    return false;
}

vector<dominoT> setDominos()
{
    int num = 1;
    int n;
    do
    {
        cout << "Enter the number of dominos you want (from 2 to whatever you want): ";
        cin >> n;
    }
    while (n < 2);

    vector<dominoT> dominos(n);

    for (int i = 0; i < n; i++)
    {
        
        do
        {
            cout << "Enter left side of domino number " << num << ": ";
            cin >> dominos[i].leftDots;
        }
        while (dominos[i].leftDots < 0);

        do 
        {
            cout << "Enter right side of domino number " << num << ": ";
            cin >> dominos[i].rightDots;
        } 
        while(dominos[i].rightDots < 0);

        ++num;
    }
    return dominos;
}

void printChian()
{
    for (int i = res.size() - 1; i >= 0; i--)
    {
        if (i == 0)
        {
            cout << res[i].leftDots << "|" << res[i].rightDots << endl;
            return;
        }
        cout << res[i].leftDots << "|" << res[i].rightDots << " - ";
    }
}