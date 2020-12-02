#pragma once
#ifndef __FUNCTION_H__
#define __FUNCTION_H__
void resetdata();
void FixConsoleWindow();
void gotoxy(int x, int y);
void Reset();
void Draw(int pSize);
void starGame();
int Checkboard(int pX, int pY);
void MoveRight();
void MoveLeft();
void MoveDown();
void MoveUp();
void checkRow(int pX, int pY);
int run();
#endif // !__FUNCTION_H__

