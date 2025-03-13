#include "Player.h"
#include "MonteCarloEval.h"

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


bool AiPlayer::MakeMove() {
	vector<MonteCarloEval*> evals;

	for (unsigned int i = 0; i < board->getBoardsize(); i++) {
		for (unsigned int j = 0; j < board->getBoardsize(); j++) {
 			if (this->board->CheckLegal(j, i)) {
				this->board->SetCell(j, i, this->cellType);
				evals.push_back(new MonteCarloEval(this->board, 10, (this->cellType == CellType_X) ? CellType_O : CellType_X, j, i));
				this->board->SetCell(j, i, CellType_Empty);
			}
		}
	}

	Board* b = new Board(board->getBoardsize(), board->getSizeToWin());
	RandomPlayer* player1 = new RandomPlayer();
	RandomPlayer* player2 = new RandomPlayer();
	player1->SetupPlayer("RandomX", CellType_X);
	player2->SetupPlayer("RandomO", CellType_O);
	player1->SetBoard(b);
	player2->SetBoard(b);
	for (auto eval : evals) {
		eval->Eval(player1, player2, b);
	}

	int biggestVictories = -1;

	for (auto eval : evals) {
		cout << "Позиция из расчета: " << eval->GetXPos() << ", " << eval->GetYPos() << " Победы: " << eval->GetVictories() << " Поражения: " << eval->GetLosses() << endl;

		if (this->cellType == CellType_X) {
			if (eval->GetVictories() > biggestVictories)
				biggestVictories = eval->GetVictories();
		}
		else {
			if (eval->GetLosses() > biggestVictories)
				biggestVictories = eval->GetLosses();
		}
	}

	vector<MonteCarloEval*> biggestWinEvals;

	for (auto eval : evals) {
		int numVictories;
		if (this->cellType == CellType_X) {
			numVictories = eval->GetVictories();
		}
		else { 
			numVictories = eval->GetLosses();
		};
		if (numVictories == biggestVictories) {
			biggestWinEvals.push_back(eval);
		}
	}
	cout << "Лучшая позиция: " << biggestWinEvals[0]->GetXPos() << ", " << biggestWinEvals[0]->GetYPos() << endl;
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