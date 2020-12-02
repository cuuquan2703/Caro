#include<iostream>
#include<Windows.h>
#include <conio.h>
#include "Function.h"

using namespace std;

HANDLE hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);


#define BOARD_SIZE 12
#define LEFT 3
#define TOP 1

struct _POINT {
	int x, y, c;
	char q;
} _A[BOARD_SIZE+1][BOARD_SIZE+1];

bool TURN = TRUE;
char _COMMAND, check;
int _X, _Y, countPlayer1 = 0, countPlayer2 = 0;



void resetdata() 
{
	for (int i = 0; i <= BOARD_SIZE; i++) {
		for (int j = 0; j <= BOARD_SIZE; j++) {
			_A[i][j].q ='.';
		}
	}
}



void Reset() 
{
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


void starGame() 
{
	system("cls");
	Draw(BOARD_SIZE);
	Reset();
};

void FixConsoleWindow() 
{
	HWND consoleWindow = GetConsoleWindow();
	LONG style = GetWindowLong(consoleWindow, GWL_STYLE);
	style = style & ~(WS_MAXIMIZEBOX) & ~(WS_THICKFRAME);
	SetWindowLong(consoleWindow, GWL_STYLE, style);
};

void Draw(int pSize) 
{
	for (int i = 0; i <= pSize; i++) {
		for (int j = 0; j <= pSize; j++) {
			gotoxy(LEFT + 4 * i, TOP + 2 * j);
			cout << ".";
		};
	};
};

int Checkboard(int pX, int pY) 
{
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

void gotoxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
};

void MoveRight() 
{
	if (_X < _A[BOARD_SIZE-1 ][BOARD_SIZE -1].x) {
		_X += 4;
		gotoxy(_X, _Y);
	}
};

void MoveLeft() 
{
	if (_X > _A[0][0].x) {
		_X -= 4;
		gotoxy(_X, _Y);
	}
};

void MoveDown() 
{
	if (_Y < _A[BOARD_SIZE-1 ][BOARD_SIZE-1 ].y) {
		_Y+= 2;
		gotoxy(_X, _Y);
	}
};

void MoveUp() 
{
	if (_Y > _A[0][0].y) {
		_Y -= 2;
		gotoxy(_X, _Y);
	}
};

int  check_row(int pX,int pY,char check)
{
	int x = pX, y = pY,count=1;
	while ((x >= 0) && (_A[x][y].q = check))
	{
		x--;
		count++;
	};
	x = pX;
	while ((x <= BOARD_SIZE-1) && (_A[x][y].q = check))
	{
		x++;
		count++;
	};
	if (count == 5) return 1;
	else return 0;
};

int ProcessFinish(int pWhoWin) 
	{
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

void event(int pX,int pY,char check)
{
    int temp=0;
    char swap_turn='.';
    if (check=='X')
    { 
        temp=14;
        swap_turn='O';
		countPlayer1++;
    }
    else 
    {
        temp=12;
        swap_turn='X';
		countPlayer2++;
    };
    SetConsoleTextAttribute(hConsoleColor,temp);
    cout<<check;
    gotoxy(78,3);
    SetConsoleTextAttribute(hConsoleColor,15);
    cout<<"Current Turn: "<<swap_turn;
    _A[(pY-2)/2][(pX-5)/4].q=check;
};

int run() {
	char chck='.';

	FixConsoleWindow();
	starGame();
	resetdata();

	bool validEnter = true;

	gotoxy(78, 3);
	cout << "Current Turn: X";
	gotoxy(80, 4);
	SetConsoleTextAttribute(hConsoleColor, 14);
	cout << "Player 1: " << 0;
	gotoxy(80, 5);
	SetConsoleTextAttribute(hConsoleColor, 12);
	cout << "Player 2: " << 0;
	gotoxy(5, 2);

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
					chck = 'X';
					event(_X, _Y, 'X');
					break;
				case 1: 
					chck = 'O';
					event(_X, _Y, 'O');
					break;
				case 0: validEnter = false;
				}
				gotoxy(80, 4);
				SetConsoleTextAttribute(hConsoleColor, 14);
				cout << "Player 1: " << countPlayer1;
				gotoxy(80, 5);
				SetConsoleTextAttribute(hConsoleColor, 12);
				cout << "Player 2: " << countPlayer2;
			}
			int x = (_Y - 2) / 2, y = (_X - 5) / 4;
			if (check_row(x, y, chck) == 1)
			{
				break;
			}
		}
	}
	system("cls");
	cout << "win";
	cout << endl;
	system("cls");
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			if (_A[i][j].q == 'X') cout << i << "  " << j << endl;
		}
		cout << endl;
	}
	return 0;
}







