// Program: TicTacToe with AI
// Author: Ahmad Reda Bayoumi
// Date: November 2022
// ...........................................................................................
#include "XO_Classes.h"

void GameManager::run()
{
	int option = 1;
	do
	{
		cout << "Welcome To Our Game\n1-MultiPlayer\n2-Play with AI\nPlease, Choose an option to perform:" << endl;
		cin >> option;
		cin.ignore(1, '\n');
	}
	while (option < 1 || option > 2);
	
	Board board;
	int move;

	if (option == 1)
	{
		Player playerx('X');
		Player playero('O');
		
		board.displayBoard();

		while (true) 
		{
			do 
			{
				// update move value by sending it to getMove FN
				playerx.getMove(move);
			} while (!board.updateBoard('X', move));
			
			board.displayBoard();

			if (board.isWinner())
			{
				cout << playerx.info() << " is the winner!!";
				return;
			}

			if (board.isDraw())
			{
				cout << "Draw.";
				return;
			}

			do {
				playero.getMove(move);
			} while (!board.updateBoard('O', move));
		
			board.displayBoard();

			if (board.isWinner())
			{
				cout << playero.info() << " is the winner!!";
				return;
			}
		}
	}
	else
	{
		int symbol = 0;
		char Plrsym;
		char AIsym;
		
		do
		{
			cout << "Which symbol you wanna play with (Choose it by its number)?\n1- X\n2- O\n>";
			cin >> symbol;
			cin.ignore();
		}
		while (symbol != 1 && symbol != 2);

		if (symbol == 1)
    {
			Plrsym = 'X';
      AIsym = 'O';
		}
		else
		{
			Plrsym = 'O';
      AIsym = 'X';
		}		

		Player player(Plrsym);
    smrtPlayer bot(AIsym);
		
		board.displayBoard();

		while (true)
		{
			do 
			{
				// update move value by sending it to getMove FN
				player.getMove(move);
			} while (!board.updateBoard(player.getSymbol(), move));

			
			if (board.isWinner())
			{
				board.displayBoard();
				cout << player.info() << " is the winner!!";
				return;
			}

			if (board.isDraw())
			{
				board.displayBoard();
				cout << "Draw.";
				return;
			}

			// update move value by sending it to getMove FN
			bot.getMove(board, move);
			board.updateBoard(bot.getSymbol(), move);

			board.displayBoard();

			if (board.isWinner())
			{
				cout << bot.info() << " is the winner!!";
				return;
			}
			
		}
	}
}