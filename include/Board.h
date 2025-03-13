#pragma once
#include "CellType.h"

class Board {
private:
	unsigned int boardsize; //������ �����
	unsigned int sizeToWin; //���������� ������ ��� ������
	CellType** cells; //�������������� ������

	//������� �����, � ����������� �� ���������� ������
	bool bVictory = false;
	bool IsRowMade(unsigned int row);
	bool IsColumnMade(unsigned int col);
	bool IsDiagMade();
	bool IsBoardFull();
public:
	Board(unsigned int size, unsigned int sizeToWin);
	void Copy(Board* board);
	virtual ~Board();
	void Show(); //���������� �����
	void SetCell(unsigned int xpos, unsigned int ypos, CellType ct); //���������� �������� � ������
	bool CheckLegal(unsigned int xpos, unsigned int ypos); //�������� �� ��������� (�������� �� ������)
	bool CheckEndCondition(); //�������� ���� ������� 
	bool IsVictory();
	bool PaintBlock();
	unsigned int getBoardsize() { return boardsize; }
	unsigned int getSizeToWin() { return sizeToWin; }
};