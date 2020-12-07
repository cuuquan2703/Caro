#include<iostream>
#include<Windows.h>
#include <conio.h>
#include <mmsystem.h>
#include"Function.h"

using namespace std;
#pragma comment(lib, "winmm.lib")

HANDLE hConsoleColor = GetStdHandle(STD_OUTPUT_HANDLE);


#define BOARD_SIZE 12
#define LEFT 3
#define TOP 1

struct _POINT {
	int x, y, c;
	
} _A[BOARD_SIZE+1][BOARD_SIZE+1];

bool TURN = TRUE;
char _COMMAND, check;
int _X, _Y, countPlayer1 = 0, countPlayer2 = 0, count_win = 0, check_loop = 0;
string A[] = { "New Game","Load Game","Instruction","ABout Us","Exit" };

void ShowCur(bool CursorVisibility)
{
	HANDLE handle = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO ConCurInf;

	ConCurInf.dwSize = 10;
	ConCurInf.bVisible = CursorVisibility;

	SetConsoleCursorInfo(handle, &ConCurInf);
};
void PrintCaro()
{
	int x = 25, y = 0;
	gotoxy(x, y);				   cout << "ooooooooooooo";
	gotoxy(x - 3, y + 1);			cout << "oooooooooooooooo";
	gotoxy(x - 5, y + 2);    cout << "oooooooooooooooooo";
	gotoxy(x - 6, y + 3);   cout << "ooooooooooooooooooo";
	
	gotoxy(x - 7, y + 4);  cout << "ooooooo";
	gotoxy(x - 8, y + 5); cout << "ooooooo";
	gotoxy(x - 8, y + 6); cout << "ooooooo";
	gotoxy(x - 8, y + 7); cout << "ooooooo";
	gotoxy(x - 8, y + 8); cout << "ooooooo";
	gotoxy(x - 8, y + 9); cout << "ooooooo";
	gotoxy(x - 8, y + 10); cout << "ooooooo";
	gotoxy(x - 7, y + 11); cout << "ooooooo";
	gotoxy(x - 6, y + 12);  cout << "ooooooooooooooooooo";
	gotoxy(x - 5, y + 13);   cout << "oooooooooooooooooo";
	
	gotoxy(x - 3, y + 14);		cout << "oooooooooooooooo";
	gotoxy(x, y + 15);			   cout << "ooooooooooooo";
	
	gotoxy(x - 4 + 22, y + 4);				    cout << "ooooooooooo";
	gotoxy(x - 4 + 22 - 2, y + 5);		      cout << "ooooooooooooooo";
	gotoxy(x - 4 + 22 - 3, y + 6);		     cout << "ooooooooooooooooo";
	
	gotoxy(x - 4 + 22 - 3, y + 7);			 cout << "ooooooooooooooooo";
	gotoxy(x - 4 + 22 - 3, y + 8);			 cout << "oooooo     oooooo";
	gotoxy(x - 4 + 22 - 3, y + 9);			 cout << "oooooo     oooooo";
	
	gotoxy(x - 4 + 22 - 3, y + 10);		 cout << "oooooo     oooooo";
	gotoxy(x - 4 + 22 - 3, y + 11);		 cout << "ooooooooooooooooo";
	gotoxy(x - 4 + 22 - 3, y + 12);		 cout << "oooooo     oooooo";
	
	gotoxy(x - 4 + 22 - 3, y + 13);		 cout << "oooooo     oooooo";
	gotoxy(x - 4 + 22 - 3, y + 14);		 cout << "oooooo     oooooo";
	gotoxy(x - 4 + 22 - 3, y + 15);		 cout << "oooooo     oooooo";
	
	gotoxy(x + 33, y + 4);			cout << "ooooo   ooooooooo";
	gotoxy(x + 33, y + 5);			cout << "oooooooooooooooooo";
	gotoxy(x + 33, y + 6);			cout << "ooooooooooooooooooo";
	
	gotoxy(x + 33, y + 7);			cout << "oooooooooooooooooooo";
	gotoxy(x + 1 + 33, y + 8);			 cout << "ooooooo     ooooooo";
	gotoxy(x + 1 + 33, y + 9);			 cout << "ooooooo     ooooooo";
	
	gotoxy(x + 1 + 33, y + 10);		 cout << "ooooooo";
	gotoxy(x + 1 + 33, y + 11);		 cout << "ooooooo";
	gotoxy(x + 1 + 33, y + 12);		 cout << "ooooooo";
	
	gotoxy(x + 1 + 33, y + 13);		 cout << "ooooooo";
	gotoxy(x + 1 + 33, y + 14);		 cout << "ooooooo";
	gotoxy(x + 1 + 33, y + 15);		 cout << "ooooooo";
	gotoxy(x + 57, y + 4);					cout << "ooooooooooo";
	gotoxy(x + 57 - 2, y + 5);			  cout << "ooooooooooooooo";
	gotoxy(x + 57 - 3, y + 6);			 cout << "ooooooooooooooooo";
	gotoxy(x + 57 - 3, y + 7);			 cout << "ooooooooooooooooo";
	
	gotoxy(x + 57 - 3, y + 8);			 cout << "oooooo     oooooo";
	gotoxy(x + 57 - 3, y + 9);			 cout << "oooooo     oooooo";
	gotoxy(x + 57 - 3, y + 10);		 cout << "oooooo     oooooo";
	gotoxy(x + 57 - 3, y + 11);		 cout << "oooooo     oooooo";
	
	gotoxy(x + 57 - 3, y + 12);		 cout << "ooooooooooooooooo";
	gotoxy(x + 57 - 3, y + 13);		 cout << "ooooooooooooooooo";
	
	gotoxy(x + 57 - 2, y + 14);		  cout << "ooooooooooooooo";
	gotoxy(x + 57, y + 15);				cout << "ooooooooooo";

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
	SetConsoleTextAttribute(hConsoleColor, 1);
	for (int i = 0; i <= pSize; i++) {
		for (int j = 0; j <= pSize; j++) {
			gotoxy(LEFT + 4 * i, TOP + 2 * j);
			cout << "";
		};
	};
	for (int i = 0; i <= pSize-1 ; i++) {
		for (int j = 0; j <= pSize; j++) {
			gotoxy((LEFT + 4 * i), (TOP + 2 * j)+1);
			cout << "----";
		};
	};
	for (int i = 0; i <= pSize-1; i++) {
		for (int j = 0; j <= pSize-1; j++) {
			gotoxy((LEFT + 4 * i)+2, (TOP + 2 * j)+1);
			cout << "|";
			gotoxy((LEFT + 4 * i) + 2, (TOP + 2 * j) + 2);
			cout << "|";
		};
	};
	SetConsoleTextAttribute(hConsoleColor, 10);
	for (int i = 0; i <=2* pSize; i++)
	{
		gotoxy(51, TOP+i+1);
		if ((i + 1) % 2 == 1)
			cout << char(21);
		else
			cout << char(23);
	};
	for (int i = 0; i < 4 * pSize; i++)
	{
		gotoxy(LEFT + i , 26);
		if (i % 2 == 0)
			cout << char(29);
		else
			cout << char(3);
	};
	for (int i = 0; i < 2 * pSize; i++)
	{
		gotoxy(LEFT, TOP + i + 1);
		if ((i + 1) % 2 == 1)
			cout << char(21);
		else
			cout << char(23);
	};
	for (int i = 0; i < 4 * pSize; i++)
	{
		gotoxy(LEFT + i , TOP);
		if (i % 2 == 0)
			cout << char(5);
		else
			cout << char(127);

	}

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

void _cout(int x, int y, string c)
{
	gotoxy(x, y);
	cout << c;
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
  };

/*void check_win(int pX, int pY,int value)
{
	bool temp = false;
	int x = pX, y = pY;
	for (int i = pX; i < BOARD_SIZE; i++)
	{
		if (_A[i][y].c == -1) count_win++;
	 }
	for (int i = pX; i > 0; i--)
	{
		if (_A[i][y].c == -1) count_win++;
	};
	if (count_win == 6) temp = true;
	if (temp == true) {
		gotoxy(80, 7);
		cout << count_win;
	}
	else count_win = 0;
};*/
void about_us()
{
	int q=0;
	system("cls");
	do
	{
		_cout(50, 15, "20120354   DANG HUYNH CUU QUAN");
		_COMMAND = toupper(_getch());
		if (_COMMAND == 27) q = 1;
	} while (q != 1);
	
}

int run() {
	char chck='.';

	FixConsoleWindow();
	starGame();
	ShowCur(1);
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
			return 1;
			break;
		}
		else {
			if (_COMMAND == 'A')
			{
				PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
				MoveLeft();
				
			}
			else if (_COMMAND == 'W')
			{
				PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
				MoveUp();
				
			}
			else if (_COMMAND == 'S')
			{
				PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
				MoveDown();
				
			}
			else if (_COMMAND == 'D')
			{
				PlaySound(TEXT("move.wav"), NULL, SND_FILENAME | SND_ASYNC);
				MoveRight();
				
			}
			else if (_COMMAND == 13) {
				switch ((Checkboard(_X, _Y)))
				{
				case -1:
						event(_X, _Y, 'X');
//	check_win((_Y - 2) / 2, (_X - 5) / 4, _A[(_Y - 2) / 2][(_X - 5) / 4].c);

						break;
				case 1: 
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
		
		}
	}
/*	system("cls");
	for (int i = 0; i < BOARD_SIZE; i++) {
		for (int j = 0; j < BOARD_SIZE; j++)
		{
			cout << _A[i][j].c << "  ";
		}
		cout << endl;
	}*/
	return 0;
}

void _Setcolor(int c)
{
	SetConsoleTextAttribute(hConsoleColor, c);
};

void DisableSelection()
{
	HANDLE hStdin = GetStdHandle(STD_INPUT_HANDLE);

	SetConsoleMode(hStdin, ~ENABLE_QUICK_EDIT_MODE);
};

int _SelectCmd()
{

	
		ShowCur(0);
		int cn = 1;
		while(1)
		{
		_COMMAND = toupper(_getch());
		if (_COMMAND == 'S')
		{
			if (cn == 1)
			{
				cn++;
				system("cls");
				PrintCaro();
				_Setcolor(15);
				_cout(50, 20, A[0]);
				_Setcolor(14);
				_cout(49, 21, ">");
				_cout(50, 21, A[1]);
				_Setcolor(15);
				_cout(50, 22, A[2]);
				_cout(50, 23, A[3]);
				_cout(50, 24, A[4]);
			}
			else if (cn == 2)
			{
				cn++;
				system("cls");
				PrintCaro();
				_Setcolor(15);
				_cout(50, 20, A[0]);
				_cout(50, 21, A[1]);
				_Setcolor(14);
				_cout(49, 22, ">");
				_cout(50, 22, A[2]);
				_Setcolor(15);
				_cout(50, 23, A[3]);
				_cout(50, 24, A[4]);
			}
			else if (cn == 3)
			{
				cn++;
				system("cls");
				PrintCaro();
				_Setcolor(15);
				_cout(50, 20, A[0]);
				_cout(50, 21, A[1]);
				_cout(50, 22, A[2]);
				_Setcolor(14);
				_cout(49, 23, ">");
				_cout(50, 23, A[3]);
				_Setcolor(15);
				_cout(50, 24, A[4]);
			}
			else if (cn == 4)
			{
				cn++;
				system("cls");
				PrintCaro();
				_Setcolor(15);
				_cout(50, 20, A[0]);
				_cout(50, 21, A[1]);
				_cout(50, 22, A[2]);
				_cout(50, 23, A[3]);
				_Setcolor(14);
				_cout(49, 24, ">");
				_cout(50, 24, A[4]);
			}
			else if (cn == 5)
			{
				cn = 1;
				system("cls");
				PrintCaro();
				_Setcolor(14);
				_cout(49, 20, ">");
				_cout(50, 20, A[0]);
				_Setcolor(15);
				_cout(50, 21, A[1]);
				_cout(50, 22, A[2]);
				_cout(50, 23, A[3]);
				_cout(50, 24, A[4]);
			}
		}
		else if (_COMMAND == 'W')
		{
			if (cn == 1)
			{
				cn = 5;
				system("cls");
				PrintCaro();
				_Setcolor(15);
				_cout(50, 20, A[0]);
				_cout(50, 21, A[1]);
				_cout(50, 22, A[2]);
				_cout(50, 23, A[3]);
				_Setcolor(14);
				_cout(49, 24, ">");
				_cout(50, 24, A[4]);
			}
			else  if (cn == 2)
			{
				cn--;
				system("cls");
				PrintCaro();
				_Setcolor(14);
				_cout(49, 20, ">");
				_cout(50, 20, A[0]);
				_Setcolor(15);
				_cout(50, 21, A[1]);
				_cout(50, 22, A[2]);
				_cout(50, 23, A[3]);
				_cout(50, 24, A[4]);
			}
			else if (cn == 3)
			{
				cn--;
				system("cls");
				PrintCaro();
				_Setcolor(15);
				_cout(50, 20, A[0]);
				_Setcolor(14);
				_cout(49, 21, ">");
				_cout(50, 21, A[1]);
				_Setcolor(15);
				_cout(50, 22, A[2]);
				_cout(50, 23, A[3]);
				_cout(50, 24, A[4]);
			}
			else if (cn == 4)
			{
				cn--;
				system("cls");
				PrintCaro();
				_Setcolor(15);
				_cout(50, 20, A[0]);
				_cout(50, 21, A[1]);
				_Setcolor(14);
				_cout(49, 22, ">");
				_cout(50, 22, A[2]);
				_Setcolor(15);
				_cout(50, 23, A[3]);
				_cout(50, 24, A[4]);
			}
			else if (cn == 5)
			{
				cn--;
				system("cls");
				PrintCaro();
				_Setcolor(15);
				_cout(50, 20, A[0]);
				_cout(50, 21, A[1]);
				_cout(50, 22, A[2]);
				_Setcolor(14);
				_cout(49, 23, ">");
				_cout(50, 23, A[3]);
				_Setcolor(15);
				_cout(50, 24, A[4]);
			}
		}
		else if (_COMMAND == 13)
		{
		if (cn == 1)
			return 1;
		else if (cn == 2) return 2;
		else if (cn == 3) return 3;
		else if (cn == 4)return 4;
		else if (cn == 5)return 5;
		}
	}
	return 0;
};




int main()
{
	int k = 0, k1 = 0;
	do
	{
		system("cls");
		PrintCaro();
		_Setcolor(14);
		_cout(49, 20, ">");
		_cout(50, 20, A[0]);
		_Setcolor(15);
		_cout(50, 21, A[1]);
		_cout(50, 22, A[2]);
		_cout(50, 23, A[3]);
		_cout(50, 24, A[4]);

		k=_SelectCmd();
		if (k == 1)  k1 = run();
		else if (k == 4) about_us();
		
	} while (k != 5);
	gotoxy(0, 0);
	_Setcolor(15);
	exit(0);
}
