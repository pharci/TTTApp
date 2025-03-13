#include "Manager.h"
#include "pch.h"

Manager::Manager() {}

Manager::~Manager() {
	delete this->player2;
	delete this->player1;
	delete this->board;
}

bool Manager::Init() {
	unsigned int boardsize = 25;
	unsigned int sizeToWin;
	string playerName;
	int playerType;

	cout << "Введите сколько нужно собрать подряд для победы (3/25): ";
	cin >> sizeToWin;
	if ((sizeToWin < 3) || (sizeToWin > 25)) {
		cout << "Некорректный ввод." << endl;
		return false;
	}

	this->board = new Board(boardsize, sizeToWin);

	cout << "Введите тип первого игрока:\n1. Человек\n2. Компьютер\n\nВвод: ";
	cin >> playerType;
	if (playerType == 1) this->player1 = new HumanPlayer();
	else if (playerType == 2) this->player1 = new AiPlayer();
	else { cout << "Некорректный ввод" << endl; }
	cout << endl;

	cout << "Введите тип второго игрока:\n1. Человек\n2. Компьютер\n\nВвод: ";
	cin >> playerType;
	if (playerType == 1) this->player2 = new HumanPlayer();
	else if (playerType == 2) this->player2 = new AiPlayer();
	else { cout << "Некорректный ввод" << endl; }
	cout << endl;

	cin.ignore();
	cout << "Введите имя игрока, играющего за X: ";
	getline(cin, playerName);
	player1->SetupPlayer(playerName, CellType_X);
	
	cout << "Введите имя игрока, играющего за O: ";
	getline(cin, playerName);
	player2->SetupPlayer(playerName, CellType_O);
	
	player1->SetBoard(this->board);
	player2->SetBoard(this->board);

	currentPlayer = player1;
	return true;
}

void Manager::ShowBoard() {
	this->board->Show();
}

void Manager::MakeMove() {
	ShowBoard();
	while (!currentPlayer->MakeMove()) {
		cout << "Недопустимый ход, попробуйте еще раз" << endl;
		ShowBoard();
	}
	if (this->board->CheckEndCondition()) {
		if (this->board->IsVictory())
			cout << "Игрок " << currentPlayer->GetName() << " победил!" << endl;
		else
			cout << "Ничья!" << endl;
		this->bGameFinished = true;
		ShowBoard();
		return;
	}
	currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool Manager::IsGameFinished() {
	return bGameFinished;
}