#include "Player.h"
#include "MonteCarloEval.h"

#include <thread>

Player::~Player() {}
RandomPlayer::~RandomPlayer() {}
AiPlayer::~AiPlayer() {}
HumanPlayer::~HumanPlayer() {}

void Player::SetupPlayer(string name, CellType cellType) {
	this->name = name;
	this->cellType = cellType;
}

void Player::SetBoard(Board* board) {
	this->board = board;
}

string Player::GetName() {
	return this->name;
}

CellType Player::getCellType() {
	return this->cellType;
};


bool AiPlayer::MakeMove() {
	vector<MonteCarloEval*> evals;

	for (unsigned int i = 0; i < board->getBoardsize(); i++) {
		for (unsigned int j = 0; j < board->getBoardsize(); j++) {

 			if (this->board->CheckLegal(j, i)) {

				board->SetCell(j, i, this->cellType);
				if (board->CheckEndCondition()) { 
					cout << "Победный ход компьютера: " << i << ", " << j << endl;
					return true; 
				}

				board->SetCell(j, i, (this->cellType == CellType_X) ? CellType_O : CellType_X);
				if (board->CheckEndCondition()) {
					board->SetCell(j, i, this->cellType);
					cout << "Заблокирован победный ход противника: " << i << ", " << j << endl;
					return true;
				}

				board->SetCell(j, i, CellType_Empty);

				evals.push_back(new MonteCarloEval(board, 10, this->cellType, j, i));
			}
		}
	}
	//for (auto eval : evals) {
	//	eval->Eval();
	//}

	std::vector<std::thread> threads;
	for (auto eval : evals) {
		std::thread t([eval]() { eval->Eval(); });
		threads.push_back(std::move(t));
	}
	for (auto& t : threads) { t.join(); }

	
	int biggestVictories = -1;
	for (auto eval : evals) {
		//cout << "Позиция из расчета: " << eval->GetXPos() << ", " << eval->GetYPos() << " Победы: " << eval->GetVictories() << " Поражения: " << eval->GetLosses() << endl;
		if (eval->GetVictories() > biggestVictories)
			biggestVictories = eval->GetVictories();
	}

	vector<MonteCarloEval*> biggestWinEvals;

	for (auto eval : evals) {
		if (eval->GetVictories() == biggestVictories) {
			biggestWinEvals.push_back(eval);
		}
	}
	//cout << "Лучшая позиция: " << biggestWinEvals[0]->GetXPos() << ", " << biggestWinEvals[0]->GetYPos() << endl;
	this->board->SetCell(biggestWinEvals[0]->GetXPos(), biggestWinEvals[0]->GetYPos(), this->cellType);

 	for (auto eval : evals)
		delete eval;
	evals.clear();
	biggestWinEvals.clear();
	return true;
}

bool HumanPlayer::MakeMove() {
	unsigned int row, col;
	cout << "Игрок " << name << ", ваш ход..." << endl;
	cout << "Введите строку: ";
	cin >> row;
	cout << "Введите столбец: ";
	cin >> col;

	if (this->board->CheckLegal(col, row)) {
		this->board->SetCell(col, row, this->cellType);
		return true;
	}
	return false;
}


bool RandomPlayer::MakeMove() {
	unsigned int row, col;
	row = (unsigned int)(rand() % board->getBoardsize());
	col = (unsigned int)(rand() % board->getBoardsize());

	if (this->board->CheckLegal(col, row)) {
		this->board->SetCell(col, row, this->cellType);
		return true;
	}
	return false;
}