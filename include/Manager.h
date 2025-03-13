#pragma once
#include "Board.h"
#include "Player.h"

class Manager {
private:
	Board* board; //Доска
	Player* player1;
	Player* player2;
	Player* currentPlayer; //Игрок, который ходит в данный момент
	bool bGameFinished = false;
public:
	Manager();
	virtual ~Manager();
	bool Init();
	void ShowBoard(); //Отрисовка доски
	void MakeMove(); //Ход игрока
	bool IsGameFinished();
};

