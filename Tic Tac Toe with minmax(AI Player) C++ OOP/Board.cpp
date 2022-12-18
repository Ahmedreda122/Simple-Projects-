// Program: TicTacToe with AI
// Author: Ahmad Reda Bayoumi
// Date: November 2022
// ...........................................................................................
#include "XO_Classes.h"

bool Board::updateBoard(char symbol, int move)
{
	if (move <= 9 && move >= 1)
	{
		if (board[move - 1] != 'X' && board[move - 1] != 'O')
		{
			board[move - 1] = symbol;
			nactions++;
			return true;
		}
	}
	return false;
}

void Board::displayBoard()
{
   cout << "-------------"  << endl
		<< "| " << board[0] << " | " << board[1] << " | " << board[2] << " | " << endl
		<< "| " << board[3] << " | " << board[4] << " | " << board[5] << " | " << endl
		<< "| " << board[6] << " | " << board[7] << " | " << board[8] << " | " << endl
		<< "-------------";
   cout << endl;
}

bool Board::isWinner()
{
	// Checking the rows
	for (int i = 0; i < 9; i += 3)
	{
		if ((board[i] == board[i + 1]) && (board[i + 1] == board[i + 2]))
		{
			return true;
		}
	}

	// Checking for colums
	for (int j = 0; j < 3; ++j)
	{
		if ((board[j] == board[j + 3]) && (board[j + 3] == board[j + 6]))
		{
			return true;
		}
	}

	// Checking for / \ winning status
	if ((board[0] == board[4]) && (board[4] == board[8]))
	{
		return true;
	}
	else if ((board[2] == board[4]) && (board[4] == board[6])) 
	{
		return true;
	}
						
	return false;
}

bool Board::isDraw()
{
	if (nactions == 9 && !this->isWinner())
	{
		return true;
	}
	return false;
}

array<char, 9> Board::getBoard()
{
	return board;
}