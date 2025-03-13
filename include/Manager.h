#pragma once
#include "Board.h"
#include "Player.h"

class Manager {
private:
	Board* board; //�����
	Player* player1;
	Player* player2;
	Player* currentPlayer; //�����, ������� ����� � ������ ������
	bool bGameFinished = false;
public:
	Manager();
	virtual ~Manager();
	bool Init();
	void ShowBoard(); //��������� �����
	void MakeMove(); //��� ������
	bool IsGameFinished();
};

