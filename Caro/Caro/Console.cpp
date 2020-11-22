#include<iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;
#define BOARD_SIZE 12
#define LEFT 3
#define TOP 1

struct _POINT {
	int x, y, c;
} _A[BOARD_SIZE][BOARD_SIZE];
bool TURN;
char _COMMAND;
int _X, _Y;

void FixConsoleWindow() {
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
};

void gotoxy(int x, int y) {
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void Reset() {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			_A[i][j].x = 4 * j + LEFT + 2;
			_A[i][j].y = 2 * i + TOP + 1;
			_A[i][j].c = 0;
		}
	}
	TURN = true;
	_COMMAND = -1;
	_X = _A[0][0].x;
	_Y = _A[0][0].y;
};

void Draw(int pSize) {
	for (int i = 0; i < pSize; i++) {
		for (int j = 0; j <= pSize; j++) {
			gotoxy(LEFT + 4 * i, TOP + 2 * j);
			cout << ".";
		}
	};
};

void starGame() {
	system("cls");
	Reset();
	Draw(BOARD_SIZE);
};

int Checkboard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (TURN == true) {
					_A[i][j].c = -1; TURN = false;
				}
				else {
					_A[i][j].c = 1; TURN = true;
				};
				return _A[i][j].c;
			}
		}
	}

};

void MoveRight() {
	if (_X < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x) {
		_X += 4;
		gotoxy(_X, _Y);
	}
};

void MoveLeft() {
	if (_X > _A[0][0].x) {
		_X -= 4;
		gotoxy(_X, _Y);
	}
};

void MoveDown() {
	if (_Y < _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y) {
		_Y+= 2;
		gotoxy(_X, _Y);
	}
};

void MoveUp() {
	if (_Y > _A[0][0].y) {
		_Y -= 2;
		gotoxy(_X, _Y);
	}
};


int main() {
	FixConsoleWindow();
	starGame();
	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27)
		{
			return 0;
		}
		else {
			if (_COMMAND == 'A') MoveLeft();
			else if (_COMMAND == 'W') MoveUp();
			else if (_COMMAND == 'S') MoveDown();
			else if (_COMMAND == 'D') MoveRight();
			else if (_COMMAND == 13) {
				switch ((Checkboard(_X, _Y)))
				{
				case -1:
					cout << "X"; break;
				case 1:
					cout << "O"; break;
				}
			}
		}
	}
	return 0;
}

