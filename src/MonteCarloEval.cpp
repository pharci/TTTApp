#include "MonteCarloEval.h"
#include "Player.h"
#include <chrono>

MonteCarloEval::~MonteCarloEval() {

}

MonteCarloEval::MonteCarloEval(Board* board, int numIterations, CellType startCellType, unsigned int xpos, unsigned int ypos) : 
	board(board), 
	numGames(numIterations), 
	startCellType(startCellType), 
	xpos(xpos), ypos(ypos),
	numVictories(0), numLosses(0), numDraws(0) {
}


void MonteCarloEval::EvalBoard(RandomPlayer* player1, RandomPlayer* player2, Board* b) {
	b->Copy(this->board);
	RandomPlayer* currentPlayer;
	bool bGameFinished = false;
	currentPlayer = (this->startCellType == CellType_X) ? player1 : player2;
	
	if (b->CheckEndCondition()) {
		if (b->IsVictory())
			if (currentPlayer == player1)
				numLosses++;
			else
				numVictories++;
		else
			numDraws++;
		bGameFinished = true;
		return;
	}

	while (!bGameFinished) {
		while (!currentPlayer->MakeMove());
		if (b->CheckEndCondition()) {
			if (b->IsVictory())
				if (currentPlayer == player1)
					numLosses++;
				else
					numVictories++;
			else
				numDraws++;
			bGameFinished = true;
		}
		currentPlayer = (currentPlayer == player1) ? player2 : player1;
	}
}

void MonteCarloEval::Eval(RandomPlayer* player1, RandomPlayer* player2, Board* b) {
	for (int i = 0; i < numGames; i++) {
		EvalBoard(player1, player2, b);
	}
}