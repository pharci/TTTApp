#pragma once
#include "CellType.h"

class Board {
private:
	unsigned int boardsize; //Размер стола
	unsigned int sizeToWin; //Количество клеток для победы
	CellType** cells; //Поддерживаемые клетки

	//События доски, в зависимости от заполнения клеток
	bool bVictory = false;
	bool IsRowMade(unsigned int row);
	bool IsColumnMade(unsigned int col);
	bool IsDiagMade();
	bool IsBoardFull();
public:
	Board(unsigned int size, unsigned int sizeToWin);
	void Copy(Board* board);
	virtual ~Board();
	void Show(); //Отрисовать доску
	void SetCell(unsigned int xpos, unsigned int ypos, CellType ct); //Установить значение в клетку
	bool CheckLegal(unsigned int xpos, unsigned int ypos); //Проверка на установку (Свободна ли клетка)
	bool CheckEndCondition(); //Проверка всех событий 
	bool IsVictory();
	bool PaintBlock();
	unsigned int getBoardsize() { return boardsize; }
	unsigned int getSizeToWin() { return sizeToWin; }
};