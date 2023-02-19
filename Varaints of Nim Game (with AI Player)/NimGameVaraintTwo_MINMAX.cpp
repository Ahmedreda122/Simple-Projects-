/*•	Variant two. In the simple Nim game we developed, all the coins where put in one pile. 
In this variant the money is divided to 3 piles as in figure-1. 
Each player takes 1, 2 or 3 coins from any pile he likes. The player that takes the last coin loses. 
Pile 1: O O O
Pile 2: O O O O
Pile 3: O O O O O
figure-1
*/

#include <iostream>
#include <vector>
#include <array>
#include <algorithm>

// Max number of Coins you can revoke at a time (turn)
#define MAX_MOVE 3
#define NO_GOOD_MOVE  {0,0}

// Size of the Piles (The size of a pile exceeds the previous pile by one).
// So you can specify the size of the first Pile to be N and the size of the second Pile will be N + 1 and the Third Pile will be N + 2
#define PILE_1 4
#define PILE_2 (PILE_1 + 1)
#define PILE_3 (PILE_2 + 1)
#define N_COINS (PILE_1 + PILE_2 + PILE_3)

using namespace std;

array<int, 3> piles = { PILE_1, PILE_2 , PILE_3 };

bool minmax(int nCoins, array<int, 3> piles, bool AIturn);

pair<int, int> findGoodMove(int nCoins, array<int, 3> piles)
{
	int bestUtilty = -1;
	int utilty;
	int pile;
	
	pair<int,int> move;

	if (piles[0] >= 1)
	{
		move = pair<int, int>{ 1,0 };
	}
	else if (piles[1] >= 1)
	{
		move = pair<int, int>{ 1,1 };
	}
	else if (piles[2] >= 1)
	{
		move = pair<int, int>{ 1,2 };
	}
	 
	for (int n = 1; n <= MAX_MOVE; n++)
	{
		if (nCoins - n < 0)
		{
			break;
		}
		
		if (piles[0] - n >= 0)
		{
			utilty = minmax(nCoins - n, array<int, 3>{piles[0] - n, piles[1], piles[2]}, true);
			// Choose the best Utilty of the AI Utilites
			if (utilty > bestUtilty)
			{
				bestUtilty = utilty;
				move = { n , 0 };
			}
		}
		else if (piles[1] - n >= 0)
		{
			utilty = minmax(nCoins - n, array<int, 3>{piles[0], piles[1] - n, piles[2]}, true);
			// Choose the best Utilty of the AI Utilites
			if (utilty > bestUtilty)
			{
				bestUtilty = utilty;
				move = { n , 1 };
			}
		}
		else if (piles[2] - n >= 0)
		{
			utilty =  minmax(nCoins - n, array<int, 3>{piles[0], piles[1], piles[2] - n}, true);
			// Choose the best Utilty of the AI Utilites
			if (utilty > bestUtilty)
			{
				bestUtilty = utilty;
				move = { n , 2 };
			}
		}


	}

	return move;
}

bool minmax(int nCoins, array<int, 3> piles, bool AIturn)
{
	vector<int> min;
	vector<int> max;

	if (nCoins == 1)
	{
		return true;
	}
	else if (nCoins == 0)
	{
		return false;
	}
	
	for (int n = 1; n <= MAX_MOVE; n++)
	{
		if (nCoins - n  < 0)
		{
			break;
		}

		if (AIturn)
		{
			if (piles[0] - n >= 0)
			{
				min.push_back(minmax(nCoins - n, array<int, 3>{piles[0] - n, piles[1], piles[2]}, false));
			}
			else if (piles[1] - n >= 0)
			{
				min.push_back(minmax(nCoins - n, array<int, 3>{piles[0], piles[1] - n, piles[2]}, false));
			}
			else if (piles[2] - n >= 0)
			{
				min.push_back(minmax(nCoins - n, array<int, 3>{piles[0], piles[1], piles[2] - n}, false));
			}
		}
		else
		{
			if (piles[0] - n >= 0)
			{
				max.push_back(minmax(nCoins - n, array<int, 3>{piles[0] - n, piles[1], piles[2]}, true));
			}
			else if (piles[1] - n >= 0)
			{
				max.push_back(minmax(nCoins - n, array<int, 3>{piles[0], piles[1] - n, piles[2]}, true));
			}
			else if (piles[2] - n >= 0)
			{
				max.push_back(minmax(nCoins - n, array<int, 3>{piles[0], piles[1], piles[2] - n}, true));
			}
		}
	}

	if (AIturn)
	{
		return *min_element(min.begin(), min.end());
	}
	else
	{
		return *max_element(max.begin(), max.end());
	}

	return false;
}

int main()
{
	int nCoins = N_COINS;
	int move;
	int pile;
	pair<int, int> Move_Pile;
	while (nCoins > 0)
	{
		do
		{
			cout << "\nPlease Enter A number from 1 to 3 and the Number of the pile you choose from saparated by a space" << "\nWe Have Pile1 : " << piles[0] << ", Pile2: " << piles[1] << ", Pile3: " << piles[2] << "\n>";
			cin >> move >> pile;
		} while (nCoins - move < 0 || move > 3 || move < 1 || pile < 1 || pile > 3 || piles[pile - 1] - move < 0);

		nCoins -= move;
		piles[pile - 1] -= move;


		if (nCoins == 1)
		{
			cout << "Human Player is the Winnnerrrr!!!";
			exit(1);
		}

		Move_Pile = findGoodMove(nCoins, piles);
		move = Move_Pile.first;
		nCoins -= move;
		piles[(int)Move_Pile.second] -= move;


		cout << "AI Take: " << move << " Coins From Pile" << Move_Pile.second + 1 << "\nRemaining Pile1 : " << piles[0] << ", Pile2 : " << piles[1] << ", Pile3 : " << piles[2] << "\n";

		if (nCoins == 1)
		{
			cout << "As Expected the AI is the Winnnerrrr!!!";
			exit(0);
		}
	}
}

