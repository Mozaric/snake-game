#ifndef GAME_INTERFACE_H
#define GAME_INTERFACE_H

#include <iostream>
#include <fstream>
#include <cstring>
#include <ctime>

#include <conio.h> //_kbhit(), _getch()
#include <windows.h> //SetConsoleTextAttribute(), SetConsoleTextAttribute()
#include <iomanip> //setw()

#include "snake.h"

#define KEY_ENTER 13

#define COLOR_NORMAL 7
#define COLOR_USING 240

#define MENU_LIST_AMOUNT 5
#define OPTION_LIST_AMOUNT 4
#define LEADERBOARD_AMOUNT 5

//OPTION0 = width
//OPTION1 = height
//OPTION2 = difficulty
//OPTION3 = quit

#define DEFAULT_OPTION0 40
#define MAX_OPTION0 70
#define MIN_OPTION0 4
#define DEFAULT_OPTION1 15
#define MAX_OPTION1 18
#define MIN_OPTION1 4
#define DEFAULT_OPTION2 2
#define MAX_OPTION2 3
#define MIN_OPTION2 1

using namespace std;

struct Option
{
public:
	int value;
	string name;
};

struct Data
{
public:
	int value;
	char name[10];
};

class GameInterface
{
public:
	GameInterface();
	~GameInterface();

	//menu
	void Start();
	void PrintMenu(int menuFlag);

	//game
	void GameSection();

	//game option
	void OptionSection();
	void PrintOption(int optionFlag);
	void CreateOptionsFile();
	void LoadOptionsFile();
	void SaveOptionsFile();

	//game leaderboard
	void LeaderboardSection();
	void PrintLeaderboard();
	void CreateLeaderboardFile();
	void LoadLeaderboardFile();
	void SaveLeaderboardFile();
	void SortLeaderboard();

	//game help
	void HelpSection();
	void PrintHelp();

	void ClearScreen();
	void PutCursor(const int x, const int y);
	void SetColor(const int c);
	void PrintColorfulMessage(const int c, const string message);
	string GetString(const string message);

private:
	int menuFlag;
	string menuList[MENU_LIST_AMOUNT];

	int optionFlag;
	struct Option op[OPTION_LIST_AMOUNT];

	struct Data lb[LEADERBOARD_AMOUNT + 1];
	
	string optionsFile;
	string leaderboardFile;

	char keyInput;
};

#endif