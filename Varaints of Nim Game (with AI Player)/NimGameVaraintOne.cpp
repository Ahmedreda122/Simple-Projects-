/*•	Variant one. In the simple Nim game we developed, the player who takes the last coin loses 
and the coins the players took away were simply ignored.
=> In this game, the coins go into a pile for each player.
=> The player whose pile contains an even number of coins after the last one is taken wins the game. */

#include <iostream>
#include <vector>
#include <algorithm>

// Max number of Coins you can revoke at a time (turn)
#define MAX_MOVE 3
// Number of Total Coins
#define N_COINS 23
z
using namespace std;

int findGoodMove(int AIpile, int PlrPile, int nCoins);
bool isGoodMove(int AIpile, int PlrPile, int nCoins, bool AIturn);


bool isEven(const int& pile)
{
	if (pile % 2 == 0)
	{
		return true;
	}
	return false;
}


int findGoodMove(int AIpile, int PlrPile, int nCoins)
{
	int bestUtilty = -1;
	int utilty;
	int move = 1;
	
	for (int n = 1; n <= MAX_MOVE; n++)
	{
		if (nCoins - n < 0)
		{
			break;
		}
		
		utilty = isGoodMove(AIpile + n, PlrPile, nCoins - n, true);
		// Choose the best Utilty of the AI Utilites
		if (utilty > bestUtilty)
		{
			bestUtilty = utilty;
			// Update the move to be the best move
			move = n;
		}
	}
	// return the best move the AI could Play
	return move;
}



bool isGoodMove(int AIpile, int PlrPile, int nCoins, bool AIturn)
{
	vector<int> max;
	vector<int> min;

	// Base Case
	if (nCoins == 0 && isEven(AIpile))
	{
		return true;
	}
	else if (nCoins == 0 && !isEven(AIpile)) // && !isEven(AIpile)
	{
		return false;
	}

	// Simuation all possible plays
	for (int n = 1; n <= MAX_MOVE; n++)
	{
		if (nCoins - n < 0)
		{
			break;
		}

		// if I am in the AIturn, make the human play and minimize its plays to evaluate its plays (he will win at these branches or not)
		if (AIturn)
		{
			min.push_back(isGoodMove(AIpile, PlrPile + n, nCoins - n, false));
		}
		// if I am in the Human turn, make the AI play and maximize its plays to evaluate its plays (AI could win in this branch(tree) or not)
		else // Human Turn
		{
			max.push_back(isGoodMove(AIpile + n, PlrPile, nCoins - n, true));
		}
	}

	if (AIturn)
	{
	/*
		Return minimum utilty of the human utilties
		if = 1, means that Human could not win in this branch (Best Branch), 
		if = 0, means that Human can win in this branch (bad branch)
	*/ 
		return *min_element(min.begin(), min.end());
	}
	else // Human turn
	{
	/*	
		Return Maximum utilty of the AI utilties
		if = 1, means that AI could win in this branch or move (good move)
		if = 0, means that AI could not win in this branch or move (worst move)
	*/
		
		return *max_element(max.begin(), max.end());
	}
	
	return 0;
}

int main()
{
	int nCoins = N_COINS;
	int AIpile = 0;
	int PlrPile = 0;
	int move;
	while (nCoins > 0)
	{
		do 
		{
			cout << "\nPlease Enter A number from 1 to 3 "<< "\nWe Have nCoins:" << nCoins << " |Human Pile: " << PlrPile << "\n>";
			cin >> move;
		} while (nCoins - move < 0 || move > 3 || move < 1);

		nCoins -= move;
		PlrPile += move;

		if (nCoins == 0 && isEven(PlrPile))
		{
			cout << "Human Player is the Winnnerrrr!!!";
			exit(1);
		}
		else if (nCoins == 0 && isEven(AIpile))
		{
			cout << "As Expected the AI is the Winnnerrrr!!!";
			exit(0);
		}

		move = findGoodMove(AIpile, PlrPile, nCoins);
		nCoins -= move;
		AIpile += move;
		cout << "AI Take: " << move << " Coins, Remaining: " << nCoins << " |AIPile: " << AIpile << endl;

		if (nCoins == 0 && isEven(PlrPile))
		{
			cout << "Human Player is the Winnnerrrr!!!";
			exit(1);
		}
		else if (nCoins == 0 && isEven(AIpile))
		{
			cout << "As Expected the AI is the Winnnerrrr!!!";
			exit(0);
		}
	}
}