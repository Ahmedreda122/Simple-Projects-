// Program: TicTacToe with AI
// Author: Ahmad Reda Bayoumi
// Date: November 2022
// ...........................................................................................
#include "XO_Classes.h"

Player::Player(char symbol, string name)
{
	name[0] = toupper(name[0]);
	this->name = name;
	this->symbol = symbol;
}

Player::Player(char symbol)
{
	this->symbol = toupper(symbol);
	cout << "\nPlayer" << symbol << ", please enter your name:" << endl;
	getline(cin, this->name);
	name[0] = toupper(name[0]);
}

void Player::getMove(int& move)
{
	do
	{
		cout << name << ", please enter a number from (0 to 9) to play your turn: ";
		cin >> move;
	} while (move > 9 || move < 1);
}

string Player::info()
{
	if (symbol == 'X')
	{
		return ("PlayerX: " + name);
	}
	else
	{
		return ("PlayerO: " + name);
	}
	
}

char Player::getSymbol()
{
	return symbol;
}

//________________________________________________

smrtPlayer::smrtPlayer(char sym)
{
	name = "AI";
	this->symbol = sym;
}

void smrtPlayer::getMove(Board board, int& move)
{
	int utilty;
	int bestUtilty = -10;
	int index = 0;
	
	for (int i : avliblePlaces(board.getBoard()))
	{
		// Getting AI utilties (possible turns)
		utilty = minmax(board, i, true);
		// Choose the AI bestUtilty ever
		if (utilty > bestUtilty)
		{
			bestUtilty = utilty;
			index = i;
		}
	}

	move = index + 1;
}

int smrtPlayer::nSqLeft(array <char, 9> board)
{
	int nSquaresLeft = 0;

	for (int i = 0; i < 9; i++)
	{
		if (board[i] != 'X' && board[i] != 'O')
		{
			nSquaresLeft++;
		}
	}
	return nSquaresLeft;
}


vector<int> smrtPlayer::avliblePlaces(array<char, 9> board)
{
	vector<int> avPlaces;
	for (int i = 0; i < 9; i++)
	{
		if (board[i] != 'X' && board[i] != 'O')
		{
			avPlaces.push_back(i);
		}
	}
	return avPlaces;
}

int smrtPlayer::minmax(Board board, int index, bool isMax)
{
	int utilty = 0;
	char sym;
	vector<int> avPlaces;
	vector<int> max;
	vector<int> min;
	
	static const char plrSym = (this->symbol == 'X')? 'O' : 'X';

	if (isMax)
	{
		sym = this->symbol;
	}
	else
	{
		sym = plrSym;
	}
	

	board.updateBoard(sym, index + 1);
	utilty = (nSqLeft(board.getBoard()) + 1);
	avPlaces = avliblePlaces(board.getBoard());

	if (board.isWinner() && this->symbol == sym)
	{
		return utilty;
	}
	else if (board.isWinner() && this->symbol != sym)
	{
		utilty = -1 * utilty;
		return utilty;
	}
	else if (board.isDraw())
	{
		return 0;
	}
	else // if (!board.isWinner() && !(board.isDraw()))
	{
		for (int i : avPlaces)
		{
			// if AI played X 
			if (isMax)
			{
				// Push human's utilites (returns) to minimize it
				min.push_back(minmax(board, i, false));
			}
			// if human played O 
			else
			{
				// Push AI's utilties (returns) to maximize it
				max.push_back(minmax(board, i, true));
			}	
		}
		// If the program in AI turn
		if (isMax)
		{
			//Return Minimum utilty of human utilties (returns) to evaluate the branch (is it good branch to play in it or not)
			return *min_element(min.begin(), min.end());
		}
		// if the program in human turn
		else
		{
			// Return maximum utilty of AI utilties (returns) to evaluate the branch (to choose which is the best turn to make(the best square to play in it))
			return *max_element(max.begin(), max.end());
		}
	}
	return 0;
}


// utilty = max -> 1 (ai wins) or min -> -1 (human wins) or draw -> 0 (no one wins) * (squares left + 1)
// utilty means if it is +ve means that AI win with (utilty - 1) left squares (wins faster)
// utilty if it is -ve means that human wins with (utility - 1) left squares (bigger utilty faster you win)
// utilty equal zero means draw and 
// min max branch ends either the board is filled (draw) or some one wins
// we can store utilties in vector  
// in the layers that x (AI) plays we maxmmize the x turns (or utilties) in order to win
// in the layers that y (human) plays we minimize the y turns (utilties) in order to tell the program that in this branch human can win or return draw
// minimizing the y to give this branch low score because that will be useful in maxmizing x after that layer to choose the best branch or the highest branch (give the branch the lowest possible score of it to choose the highest from the lowest(best branch))