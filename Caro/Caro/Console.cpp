#include<iostream>
#include<Windows.h>
using namespace std;
#define BOARD_SIZE 12
#define LEFT 3
#define TOP 1

struct _POINT {
	int x, y, c;
} _A[BOARD_SIZE][BOARD_SIZE];
bool TURN;
int _COMMAND;
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

int main() {
	FixConsoleWindow();
	statGame();
	return 0;
}

