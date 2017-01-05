#ifndef SNAKE_H
#define SNAKE_H

#include <iostream>

#include <conio.h>//_kbhit(), _getch()
#include <iomanip>//setw()
#include <windows.h>
#include <cmath>
#include <ctime>

using namespace std;

#define DIR_W 0
#define DIR_A 1
#define DIR_S 2
#define DIR_D 3

#define HEAD_SYMBOL '#'
#define BODY_SYMBOL 'o'
#define EGG_SYMBOL '*'

class SnakeGame
{
public:
	SnakeGame(const int width, const int height, const int difficulty);
	~SnakeGame();
	
	void InitSnake();
	void CreateEgg();
	
	void ClearScreen();
	void PutSnake();
	void PutEgg();
	
	void PrintStatus();
	void PrintScreenAndBoundary();
	
	int Start();
	void CheckDir();
	bool Move(int dir);
	bool MoveTo(int x, int y);
	
	void UpdateTimer();
	void PutCursor(const int x, const int y);
	void SetColor(const int c);
	
private:
	//screen
	const int SCREEN_SIZE_X;
	const int SCREEN_SIZE_Y;
	char** screen;
	
	//snake object
	const int SNAKE_LENGTH_MAX;
	const char SNAKE_HEAD;
	const char SNAKE_BODY;
	int snake_length;
	int snake_direction;
	int *snake_pos_x;
	int *snake_pos_y;
	
	//egg object
	const char EGG;
	int egg_x;
	int egg_y;
	
	//game status
	const clock_t SPEED;
	const int DIFFICULTY;
	int score;
	int min;
	float sec;
	bool game_over;
	
	char key_input;
	
	clock_t start_time;
};

#endif