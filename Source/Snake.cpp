#include <iostream>
#include <conio.h>
#include "stdlib.h"
#include "Windows.h"
#include "time.h"

#define KEY_UP 72
#define KEY_DOWN 80
#define KEY_LEFT 75
#define KEY_RIGHT 77
#define ESC 27

using namespace std;

bool gameOver;
const int width = 40;
const int height = 25;
int playerX, playerY;
int fruitX, fruitY;
int tailX[100], tailY[100];
int numOfTails;
int score;
int c = 0;
enum eDirection
{
	STOP = 0,
	LEFT,
	RIGHT,
	UP,
	DOWN
};
eDirection dir;
void setup()
{
	srand(time(0));
	gameOver = false;
	dir = STOP;
	playerX = width / 2;
	playerY = height / 2;
	fruitX = rand() % width;
	fruitY = rand() % height;
	if (fruitX == playerX) {
		fruitX = rand() % width;
	}
	if (fruitY == playerY) {
		fruitY = rand() % height;
	}
	score = 0;
}

void draw()
{
	system("cls");
	cout << "Score: " <<  score << "\n";
	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}

	cout << endl;

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j < width; j++)
		{
			if (j == 0)
			{
				cout << "#";
			}
			
				if (j == fruitX && i == fruitY) {
					cout << "*";
				}
				else if (j == playerX && i == playerY) {
					cout << "O";
				}
				else {
					bool didPrint = false;
					for (int k = 0; k < numOfTails; k++) {
						if (tailX[k] == j && tailY[k] == i) {
							cout << "o";
							didPrint = true;
						}
					}
					if (!didPrint) {
						cout << " ";
					}
				}
				
			
			if (j == width - 1)
			{
				cout << "#";
			}
		}
		cout << endl;
	}

	for (int i = 0; i < width + 2; i++)
	{
		cout << "#";
	}
	cout << endl;
}

void input()
{
	if (_kbhit()) {
		c = 0;
		switch ((c = _getch()))
		{
		case KEY_UP:
			dir = UP;
			break;

		case KEY_DOWN:
			dir = DOWN;
			break;

		case KEY_LEFT:
			dir = LEFT;
			break;

		case KEY_RIGHT:
			dir = RIGHT;
			break;

		case ESC:
			dir = STOP;
			break;
		}
	
	}
}

void logic()
{
	if (!gameOver) {
		int prevX = tailX[0];
		int prevY = tailY[0];
		int prev2X, prev2Y;
		tailX[0] = playerX;
		tailY[0] = playerY;
		for (int i = 1; i < numOfTails; i++) {
			prev2X = tailX[i];
			prev2Y = tailY[i];
			tailX[i] = prevX;
			tailY[i] = prevY;
			prevX = prev2X;
			prevY = prev2Y;
		}

		switch (dir) {
		case UP:
			playerY--;
			break;

		case DOWN:
			playerY++;
			break;

		case LEFT:
			playerX--;
			break;

		case RIGHT:
			playerX++;
			break;
		}

		if (playerX == fruitX && playerY == fruitY) {
			score += 1;
			numOfTails++;

			fruitX = rand() % width;
			if (fruitX == playerX) {
				fruitX = rand() % width;
			}
			fruitY = rand() % height;
			if (fruitY == playerY) {
				fruitY = rand() % height;
			}
		}

		if (playerX < 0 || playerX > width || playerY < 0 || playerY > height) {
			gameOver = true;
		}
		for (int i = 0; i < numOfTails; i++) {
			if (tailX[i] == playerX && tailY[i] == playerY) {
				gameOver = true;
			}
		}
	}
	else {
		system("cls");
	}

}

int main()
{
	setup();
	while (!gameOver)
	{
		draw();
		input();
		logic();
		Sleep(50);
	}
	

	return 0;
}