#include "Board.h"
#include "pch.h"

Board::Board(unsigned int size, unsigned int sizeToWin) {
	this->sizeToWin = sizeToWin;
	this->boardsize = size;
	cells = new CellType*[size];
	for (unsigned int i = 0; i < size; i++)
		cells[i] = new CellType[size];
	for (unsigned int i = 0; i < size; i++)
		for (unsigned int j = 0; j < size; j++)
			cells[i][j] = CellType_Empty;
}

void Board::Copy(Board* board) {
	for (unsigned int i = 0; i < boardsize; i++) {
		cells[i] = new CellType[boardsize];
		for (unsigned int j = 0; j < boardsize; j++)
			cells[i][j] = board->cells[i][j];
	}
}

Board::~Board() {
	for (unsigned int i = 0; i < boardsize; i++)
		delete[]cells[i];
	delete[]cells;
}

void Board::Show() {
	//system("CLS");
	cout << "\n              ";
	for (unsigned int j = 0; j < boardsize; j++)
		if (j > 9) {
			cout << j / 10 << " ";
		}
		else cout << " ";
	cout << endl;

	cout << "    ";
	for (unsigned int j = 0; j < boardsize; j++)
		cout << j % 10 << " ";
	cout << endl;


	for (unsigned int i = 0; i < boardsize; i++) {
		if (i < 10)
			cout << "  " << i << " ";
		else cout << " " << i << ' ';

		for (unsigned int j = 0; j < boardsize; j++) {

			switch (cells[i][j]) {
			case CellType_X:
				cout << "X";
				break;
			case CellType_O:
				cout << "O";
				break;
			case CellType_Block:
				cout << "#";
				break;
			case CellType_Empty:
				cout << "·";
				break;
			}
			cout << " ";
		}
		cout << endl;
	}
}

void Board::SetCell(unsigned int xpos, unsigned int ypos, CellType ct) {
	cells[ypos][xpos] = ct;
}

bool Board::CheckLegal(unsigned int xpos, unsigned int ypos) {
	if ((xpos < 0) || (xpos > boardsize - 1) || (ypos < 0) || (ypos > boardsize - 1))
		return false;
	return (cells[ypos][xpos] == CellType_Empty);
}

bool Board::IsRowMade(unsigned int row) {
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < boardsize; i++) {
		if (cells[row][i] == CellType_O) {
			numO++;
			if (numO == sizeToWin) {
				bVictory = true;
				return true;
			}
			numX = 0;
		}
		if (cells[row][i] == CellType_X) {
			numX++;
			if (numX == sizeToWin) {
				bVictory = true;
				return true;
			}
			numO = 0;
		}
		if (cells[row][i] == CellType_Empty) {
			numO = 0;
			numX = 0;
		}
		if (cells[row][i] == CellType_Block) {
			numO = 0;
			numX = 0;
		}
	}
	return false;
}

bool Board::IsColumnMade(unsigned int col) {
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < boardsize; i++) {
		if (cells[i][col] == CellType_O) {
			numO++;
			if (numO == sizeToWin) {
				bVictory = true;
				return true;
			}
			numX = 0;
		}
		if (cells[i][col] == CellType_X) {
			numX++;
			if (numX == sizeToWin) {
				bVictory = true;
				return true;
			}
			numO = 0;
		}
		if (cells[i][col] == CellType_Block) {
			numO = 0;
			numX = 0;
		}
		if (cells[i][col] == CellType_Empty) {
			numO = 0;
			numX = 0;
		}
	}
	return false;
}

bool Board::IsDiagMade() {
	for (unsigned int k = 0; k < boardsize; k++) {
		int numX = 0, numO = 0;
		for (int i = 0; i < boardsize - k; i++) { //верхние диагонали
			if (cells[i][i + k] == CellType_O) {
				numO++;
				if (numO == sizeToWin) {
					bVictory = true;
					return true;
				}
				numX = 0;
			}
			else if (cells[i][i + k] == CellType_X) {
				numX++;
				if (numX == sizeToWin) {
					bVictory = true;
					return true;
				}
				numO = 0;
			}
			else {
				numO = 0;
				numX = 0;
			}
		}

		numX = numO = 0;
		for (int i = 0; i < boardsize - k; i++) { //нижние диагонали
			if (cells[i + k][i] == CellType_O) {
				numO++;
				if (numO == sizeToWin) {
					bVictory = true;
					return true;
				}
				numX = 0;
			}
			else if (cells[i + k][i] == CellType_X) {
				numX++;
				if (numX == sizeToWin) {
					bVictory = true;
					return true;
				}
				numO = 0;
			}
			else {
				numO = 0;
				numX = 0;
			}
		}

		numX = numO = 0;
		for (int i = 0; i < boardsize - k; i++) { //верхние инверсия диагонали
			if (cells[i][(boardsize - 1) - (i + k)] == CellType_O) {
				numO++;
				if (numO == sizeToWin) {
					bVictory = true;
					return true;
				}
				numX = 0;
			}
			else if (cells[i][(boardsize - 1) - (i + k)] == CellType_X) {
				numX++;
				if (numX == sizeToWin) {
					bVictory = true;
					return true;
				}
				numO = 0;
			}
			else {
				numO = 0;
				numX = 0;
			}
		}

		numX = numO = 0;
		for (int i = 0; i < boardsize - k; i++) { //нижние инверсия диагонали
			if (cells[i + k][(boardsize - 1) - i] == CellType_O) {
				numO++;
				if (numO == sizeToWin) {
					bVictory = true;
					return true;
				}
				numX = 0;
			}
			else if (cells[i + k][(boardsize - 1) - i] == CellType_X) {
				numX++;
				if (numX == sizeToWin) {
					bVictory = true;
					return true;
				}
				numO = 0;
			}
			else {
				numO = 0;
				numX = 0;
			}
		}
	}

	return false;
}

bool Board::IsBoardFull() {
	int numX = 0, numO = 0, blocks = 0;
	for (unsigned int i = 0; i < boardsize; i++) {
		for (unsigned int j = 0; j < boardsize; j++) {
			if (cells[i][j] == CellType_O)
				numO++;
			if (cells[i][j] == CellType_X)
				numX++;
			if (cells[i][j] == CellType_Block)
				blocks++;
		}
	}

	if ((numX + numO + blocks) == (boardsize * boardsize)) {
		return true;
	}
	return false;
}

bool Board::PaintBlock() {
	//Подсчет количества занятых клеток. 
	int numX = 0, numO = 0;
	for (unsigned int i = 0; i < boardsize; i++) {
		for (unsigned int j = 0; j < boardsize; j++) {
			if (cells[i][j] == CellType_O)
				numO++;
			if (cells[i][j] == CellType_X)
				numX++;
		}
	}

	//Проверяем является ли количество клеток кратным 5.
	if ((numX + numO) % 10 == 5 || (numX + numO) % 10 == 0) {
		for (int i = 0; i < boardsize * boardsize; i++) {
			unsigned int row = (unsigned int)(rand() % boardsize);
			unsigned int col = (unsigned int)(rand() % boardsize);

			if (cells[row][col] != (CellType_O || CellType_X)) { //Если клетка не занята
				cells[row][col] = CellType_Block; //"Закрашиваем" ее.
				return true;
			}
		}
	}
	return false;
}

bool Board::CheckEndCondition() {
	PaintBlock();

	for (unsigned int i = 0; i < boardsize; i++) {
		if (IsRowMade(i) || IsColumnMade(i))
			return true;
	}
	if (IsDiagMade() || IsBoardFull())
		return true;
	return false;
}

bool Board::IsVictory() {
	return bVictory;
}