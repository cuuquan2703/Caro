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

int main() {
	FixConsoleWindow();
	gotoxy(20, 30);
	return 0;
}

