#pragma once
#include "Board.h"
#include "pch.h"
#include "Player.h"

class MonteCarloEval {
private:
	Board* board;
	int numGames;
	int numVictories;
	int numLosses;
	int numDraws;
	unsigned int xpos, ypos;
	CellType startCellType;
public:
	MonteCarloEval(Board* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos);
	~MonteCarloEval();
	void EvalBoard(RandomPlayer* player1, RandomPlayer* player2, Board* b);
	void Eval(RandomPlayer* player1, RandomPlayer* player2, Board* b);
	int GetVictories() { return numVictories; }
	int GetLosses() { return numLosses; }
	int GetDraws() { return numDraws; }
	int GetXPos() { return xpos; }
	int GetYPos() { return ypos; }
};