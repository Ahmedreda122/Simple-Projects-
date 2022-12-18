// Program: TicTacToe with AI
// Author: Ahmad Reda Bayoumi
// Date: November 2022
// ...........................................................................................
#ifndef XO_CLASSES_H_
#define XO_CLASSES_H_

#include <ctype.h>
#include <iostream>
#include <string>
#include <array>
#include <vector>
#include <algorithm>

using namespace std;

class Board 
{
protected:
	array<char, 9> board = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	int nactions = 0;
public:
	bool updateBoard(char symbol, int move);
	void displayBoard();
	bool isWinner();
	bool isDraw();
	array<char, 9> getBoard();
};

class Player
{
protected:
	string name;
	char symbol;
	Player(char symbol, string name);
public:
	Player(){ name = "AI"; symbol = 'X'; }
	Player(char symbol);
	virtual void getMove(int& move);
	// Give player info as a string
	string info();
	// Get symbol used by player
	char getSymbol();
};

class smrtPlayer: public Player
{
private:
	string name = "AI";
public:
	vector<int> avliblePlaces(array <char, 9> board);
	smrtPlayer(char sym);
	void getMove(Board board, int& move);
	int nSqLeft(array <char, 9> board);
	int minmax(Board board, int index , bool isMax);
};

class GameManager 
{
public:
	void run();
};

#endif