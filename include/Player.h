#pragma once
#include "Board.h"
#include "pch.h"

class Player {
protected:
	Board* board;
	CellType cellType;
	string name;
public: 
	virtual ~Player();
	void SetupPlayer(string name, CellType cellType);
	void SetBoard(Board* board);
	virtual bool MakeMove() = 0;
	string GetName();
	CellType getCellType();
};

class HumanPlayer : public Player {
public:
	virtual ~HumanPlayer();
	bool MakeMove();
};

class AiPlayer : public Player {
public:
	virtual ~AiPlayer();
	bool MakeMove();
};

class RandomPlayer : public Player {
public:
	virtual ~RandomPlayer();
	bool MakeMove();
};