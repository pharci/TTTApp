#include "MonteCarloEval.h"
#include "Player.h"
#include <chrono>

MonteCarloEval::~MonteCarloEval() {}

MonteCarloEval::MonteCarloEval(
		Board* board, 
		int numIterations, 
		CellType startCellType,  
		unsigned int xpos,  
		unsigned int ypos
	) : 
	board(board),
	numGames(numIterations),
	startCellType(startCellType),
	xpos(xpos), ypos(ypos),
	numVictories(0), numLosses(0), numDraws(0) {}


void MonteCarloEval::EvalBoard() {
	Board* b = new Board(board);
	RandomPlayer* player1 = new RandomPlayer();
	RandomPlayer* player2 = new RandomPlayer();
	player1->SetupPlayer("RandomX", CellType_X);
	player2->SetupPlayer("RandomO", CellType_O);
	player1->SetBoard(b);
	player2->SetBoard(b);

	RandomPlayer* currentPlayer;
	bool bGameFinished = false;

	b->SetCell(xpos, ypos, this->startCellType); //ќсновна€ €чейка дл€ расчета (первый ход)
	currentPlayer = (this->startCellType == CellType_X) ? player1 : player2;

	while (!bGameFinished) {
		currentPlayer = (currentPlayer == player1) ? player2 : player1;

		//b->SetCell(xpos, ypos, currentPlayer->getCellType());
		//if (b->CheckEndCondition()) {
		//	if (b->IsVictory())
		//		if (currentPlayer->getCellType() == this->startCellType) numVictories++;
		//		else numLosses++;
		//	else numDraws++;
		//	bGameFinished = true;
		//	continue;
		//}

		//b->SetCell(xpos, ypos, (currentPlayer->getCellType() == CellType_X) ? CellType_O : CellType_X);
		//if (b->CheckEndCondition()) {
		//	b->SetCell(xpos, ypos, currentPlayer->getCellType());
		//	continue;
		//}

		//b->SetCell(xpos, ypos, CellType_Empty);

		while (!currentPlayer->MakeMove());
		if (b->CheckEndCondition()) {
			if (b->IsVictory())
				if (currentPlayer->getCellType() == this->startCellType) numVictories++;
				else numLosses++;
			else numDraws++;
			bGameFinished = true;
		}
	}
}

void MonteCarloEval::Eval() {
	for (int i = 0; i < numGames; i++) {
		EvalBoard();
	}
}