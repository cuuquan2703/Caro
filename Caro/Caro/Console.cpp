#include<iostream>
#include<Windows.h>
#include <conio.h>
using namespace std;
#define BOARD_SIZE 12
#define LEFT 3
#define TOP 1

struct _POINT {
	int x, y, c;
	char q;
} _A[BOARD_SIZE][BOARD_SIZE];
bool TURN=TRUE;
char _COMMAND,check;
int _X, _Y;
int p1 = 0, p2 = 0;
void resetdata() {
	for (int i = 0; i <= BOARD_SIZE; i++) {
		for (int j = 0; j <= BOARD_SIZE; j++) {
			_A[i][j].q ='.';
		}
	}
}

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
	gotoxy(5, 2);
};

void Draw(int pSize) {
	for (int i = 0; i <= pSize; i++) {
		for (int j = 0; j <= pSize; j++) {
			gotoxy(LEFT + 4 * i, TOP + 2 * j);
			cout << ".";
		};
	};
};

void starGame() {
	system("cls");
	Draw(BOARD_SIZE);
	Reset();
};

int ProcessFinish(int pWhoWin) {
	gotoxy(0, _A[BOARD_SIZE - 1][BOARD_SIZE - 1].y + 2);
	switch (pWhoWin)
	{
	case -1: cout << "asdadadasdadad"; break;
	case 1: cout << "sadadadadadadad"; break;
	case 0: cout << "adadasddadasd"; break;
	case 2: TURN = !TURN;
	}
	gotoxy(_X, _Y);
	return pWhoWin;
}


int Checkboard(int pX, int pY) {
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++) {
			if (_A[i][j].x == pX && _A[i][j].y == pY && _A[i][j].c == 0) {
				if (TURN == true) {
					_A[i][j].c = -1;
					TURN = false;
				}
				else {
					_A[i][j].c = 1;
					TURN = true;
				};
				return _A[i][j].c;
			}
		}
	}
	return 0;

};

void MoveRight() {
	if (_X < _A[BOARD_SIZE-1 ][BOARD_SIZE -1].x) {
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
	if (_Y < _A[BOARD_SIZE-1 ][BOARD_SIZE-1 ].y) {
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
void checkRow(int pX, int pY ) {

	int count = 1;
	bool t = false;
	int x = pX;
	while (((x - 4) >= _A[0][0].x) && (_A[x][pY].q = check)) {
		count++;
		x -= 4;

	};
	while (((x + 4) <= _A[BOARD_SIZE - 1][BOARD_SIZE - 1].x) && (_A[x][pY].q = check)) {
		count++;
		x += 4;
	};
	if (count == 5) t=true;
	if (t == true) cout << "win";
};


int main() {
	HANDLE hConsoleColor;
	hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);
	FixConsoleWindow();
	starGame();
	resetdata();
	bool validEnter = true;
	while (1) {
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27)
		{
			break;
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
					check = 'X';
					SetConsoleTextAttribute(hConsoleColor, 14);
					cout << "X";
					p1++;
					break;
				case 1: 
					check = 'O';
					SetConsoleTextAttribute(hConsoleColor, 12);
					cout << "O";
					p2++;
					break;
				case 0: validEnter = false;
				}
				_A[(_Y - 2) / 2][(_X - 5) / 4].q = check;
				gotoxy(80, 1);
				SetConsoleTextAttribute(hConsoleColor, 14);
				cout << "Player 1: " << p1-46;
				gotoxy(80, 2);
				SetConsoleTextAttribute(hConsoleColor, 12);
				cout << "Player 2: " << p2;
			//	checkRow(_X, _Y);
			}
		}
	}
	cout << endl;
	system("cls");
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			
			cout << _A[i][j].q << "    ";
		}
		cout << endl;
	}
	return 0;
}

