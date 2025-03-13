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

	cout << "������� ������� ����� ������� ������ ��� ������ (3/25): ";
	cin >> sizeToWin;
	if ((sizeToWin < 3) || (sizeToWin > 25)) {
		cout << "������������ ����." << endl;
		return false;
	}

	this->board = new Board(boardsize, sizeToWin);

	cout << "������� ��� ������� ������:\n1. �������\n2. ���������\n\n����: ";
	cin >> playerType;
	if (playerType == 1) this->player1 = new HumanPlayer();
	else if (playerType == 2) this->player1 = new AiPlayer();
	else { cout << "������������ ����" << endl; }
	cout << endl;

	cout << "������� ��� ������� ������:\n1. �������\n2. ���������\n\n����: ";
	cin >> playerType;
	if (playerType == 1) this->player2 = new HumanPlayer();
	else if (playerType == 2) this->player2 = new AiPlayer();
	else { cout << "������������ ����" << endl; }
	cout << endl;

	cin.ignore();
	cout << "������� ��� ������, ��������� �� X: ";
	getline(cin, playerName);
	player1->SetupPlayer(playerName, CellType_X);
	
	cout << "������� ��� ������, ��������� �� O: ";
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
		cout << "������������ ���, ���������� ��� ���" << endl;
		ShowBoard();
	}
	if (this->board->CheckEndCondition()) {
		if (this->board->IsVictory())
			cout << "����� " << currentPlayer->GetName() << " �������!" << endl;
		else
			cout << "�����!" << endl;
		this->bGameFinished = true;
		ShowBoard();
		return;
	}
	currentPlayer = (currentPlayer == player1) ? player2 : player1;
}

bool Manager::IsGameFinished() {
	return bGameFinished;
}