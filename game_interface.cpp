#include "game_interface.h"

////////////////////////////////////////////////////////////////////////////////////

GameInterface::GameInterface()
{
	optionsFile = "options.txt";
	leaderboardFile = "leaderboard.txt";

	LoadOptionsFile();
	LoadLeaderboardFile();

	menuFlag = 0;
	menuList[0] = "Start";
	menuList[1] = "Option";
	menuList[2] = "Leaderboard";
	menuList[3] = "Help";
	menuList[4] = "Quit";

	optionFlag = 0;
	op[0].name = "Width";
	op[1].name = "Height";
	op[2].name = "Difficulty";
	op[3].name = "Quit";

	keyInput = ' ';
}

////////////////////////////////////////////////////////////////////////////////////

GameInterface::~GameInterface()
{

}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::Start()
{
	PutCursor(0, 0);
	PrintMenu(menuFlag);

	while(true)
	{
		if(_kbhit())
		{
			keyInput = _getch();

			if(keyInput == KEY_ENTER)
			{
				ClearScreen();

				if     (menuFlag == 0) GameSection();
				else if(menuFlag == 1) OptionSection();
				else if(menuFlag == 2) LeaderboardSection();
				else if(menuFlag == 3) HelpSection();
				else                   break;
			}
			else if(keyInput == 'W' || keyInput == 'w')
			{
				if(menuFlag > 0)
					menuFlag -= 1;
			}
			else if(keyInput == 'S' || keyInput == 's')
			{
				if(menuFlag < (MENU_LIST_AMOUNT - 1))
					menuFlag += 1;
			}
			else
				continue;

			PutCursor(0, 0);
			PrintMenu(menuFlag);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::PrintMenu(int menuFlag)
{
	cout << " _ _ _ _ _ _     _ _     _ _     _ _ _ _ _ _     _ __   __ _     _ _ _ _ _ _ " << endl;
	cout << "|           |   |   |_  |   |   |           |   |    |_|    |   |           |" << endl;
	cout << "|          _|   |     |_|   |   |     _     |   |           |   |          _|" << endl;
	cout << "|         |     |           |   |    |_|    |   |           |   |         |_ " << endl;
	cout << "|         |_    |           |   |           |   |          _|   |           |" << endl;
	cout << "|           |   |           |   |           |   |         |     |          _|" << endl;
	cout << "|_          |   |           |   |           |   |         |_    |         |_ " << endl;
	cout << "  |         |   |           |   |           |   |           |   |           |" << endl;
	cout << " _|         |   |    _      |   |     _     |   |           |   |          _|" << endl;
	cout << "|           |   |   | |_    |   |    | |    |   |     _     |   |         |_ " << endl;
	cout << "|_ _ _ _ _ _|   |_ _|   |_ _|   |_ _|   |_ _|   |_ __| |__ _|   |_ _ _ _ _ _|" << endl;
	cout << endl << endl;
	for(int i = 0; i < MENU_LIST_AMOUNT; ++i)
		cout << "\t" << menuList[i].c_str() << endl << endl;

	//print beautiful menulist
	PutCursor(8, 13 + 2 * menuFlag);
	PrintColorfulMessage(COLOR_USING, menuList[menuFlag]);
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::GameSection()
{
	SnakeGame sg(op[0].value, op[1].value, op[2].value);
	int score = sg.Start();

	PrintColorfulMessage(COLOR_USING, "Please Enter Your Name:");
	cin.getline(lb[LEADERBOARD_AMOUNT].name, 10, '\n');

	lb[LEADERBOARD_AMOUNT].value = score;
	SaveLeaderboardFile();

	ClearScreen();
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::OptionSection()
{
	PrintOption(optionFlag);

	while(true)
	{
		if(_kbhit())
		{
			keyInput = _getch();

			if(keyInput == KEY_ENTER && optionFlag == 3)
			{
				SaveOptionsFile();
				menuFlag = 0;
				optionFlag = 0;
				ClearScreen();
				break;
			}
			else if(keyInput == 'W' || keyInput == 'w')
			{
				if(optionFlag > 0)
					optionFlag -= 1;
			}
			else if(keyInput == 'S' || keyInput == 's')
			{
				if(optionFlag < (OPTION_LIST_AMOUNT - 1))
					optionFlag += 1;
			}
			else if(keyInput == 'A' || keyInput == 'a')
			{
				if     (optionFlag == 0 && op[0].value > MIN_OPTION0) op[0].value -= 1;
				else if(optionFlag == 1 && op[1].value > MIN_OPTION1) op[1].value -= 1;
				else if(optionFlag == 2 && op[2].value > MIN_OPTION2) op[2].value -= 1;
			}
			else if(keyInput == 'D' || keyInput == 'd')
			{
				if     (optionFlag == 0 && op[0].value < MAX_OPTION0) op[0].value += 1;
				else if(optionFlag == 1 && op[1].value < MAX_OPTION1) op[1].value += 1;
				else if(optionFlag == 2 && op[2].value < MAX_OPTION2) op[2].value += 1;
			}
			else
				continue;

			PutCursor(0, 0);
			PrintOption(optionFlag);
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::PrintOption(int optionFlag)
{
	cout << endl;
	cout << "\t------- Option -------" << endl;
	cout << endl << endl;
	cout << "\t" << op[0].name.c_str() << "\t\t" << setw(2) << op[0].value << "  " << endl << endl;
	cout << "\t" << op[1].name.c_str() << "\t\t" << setw(2) << op[1].value << "  " << endl << endl;
	cout << "\t" << op[2].name.c_str() << "\t"   << setw(2) << op[2].value << "  " << endl << endl;
	cout << "\tQuit" << "\t\t\t\t" << endl << endl;

	//print beautiful optionlist
	PutCursor(8, 4 + 2 * optionFlag);
	PrintColorfulMessage(COLOR_USING, op[optionFlag].name);
	
	if(optionFlag == 3)
		return;

	PutCursor(22, 4 + 2 * optionFlag);
	cout << "<";
	PutCursor(27, 4 + 2 * optionFlag);
	cout << ">";
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::CreateOptionsFile()
{
	ofstream optionsOut(optionsFile, ofstream::binary);

	int v[OPTION_LIST_AMOUNT - 1];
	v[0] = DEFAULT_OPTION0;
	v[1] = DEFAULT_OPTION1;
	v[2] = DEFAULT_OPTION2;

	optionsOut.write((char*)&v[0], sizeof(int));
	optionsOut.write((char*)&v[1], sizeof(int));
	optionsOut.write((char*)&v[2], sizeof(int));

	optionsOut.close();
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::LoadOptionsFile()
{
	ifstream optionsIn;

	optionsIn.open(optionsFile, ifstream::binary);
	if(optionsIn == false)
	{
		CreateOptionsFile();
		optionsIn.open(optionsFile, ifstream::binary);
	}

	optionsIn.read((char*)&op[0].value, sizeof(int));
	optionsIn.read((char*)&op[1].value, sizeof(int));
	optionsIn.read((char*)&op[2].value, sizeof(int));

	optionsIn.close();
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::SaveOptionsFile()
{
	ofstream optionsOut(optionsFile, ofstream::binary);

	int v[OPTION_LIST_AMOUNT - 1];
	v[0] = DEFAULT_OPTION0;
	v[1] = DEFAULT_OPTION1;
	v[2] = DEFAULT_OPTION2;

	optionsOut.write((char*)&op[0].value, sizeof(int));
	optionsOut.write((char*)&op[1].value, sizeof(int));
	optionsOut.write((char*)&op[2].value, sizeof(int));

	optionsOut.close();
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::LeaderboardSection()
{
	PrintLeaderboard();

	while(true)
	{
		if(_kbhit())
		{
			keyInput = _getch();

			if(keyInput == KEY_ENTER)
			{
				menuFlag = 0;
				ClearScreen();
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::PrintLeaderboard()
{
	cout << endl;
	cout << "\t------- Leaderboard -------" << endl;
	cout << endl << endl;
	for(int i = 0; i < LEADERBOARD_AMOUNT; ++i)
		cout << "\t" << setw(10) << lb[i].name << setw(10) << lb[i].value << endl;

	//print "Quit"
	PutCursor(8, 12);
	PrintColorfulMessage(COLOR_USING, "Quit");
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::CreateLeaderboardFile()
{
	ofstream leaderboardOut(leaderboardFile, ofstream::binary);

	struct Data tmp = {0, "none"};
	for(int i = 0; i < LEADERBOARD_AMOUNT; ++i)
		leaderboardOut.write((char*)&tmp, sizeof(struct Data));

	leaderboardOut.close();
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::LoadLeaderboardFile()
{
	ifstream leaderboardIn;

	leaderboardIn.open(leaderboardFile, ifstream::binary);
	if(leaderboardIn == false)
	{
		CreateLeaderboardFile();
		leaderboardIn.open(leaderboardFile, ifstream::binary);
	}

	for(int i = 0; i < LEADERBOARD_AMOUNT; ++i)
		leaderboardIn.read((char*)&lb[i], sizeof(struct Data));

	leaderboardIn.close();
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::SaveLeaderboardFile()
{
	SortLeaderboard();

	ofstream leaderboardOut(leaderboardFile, ofstream::binary);

	for(int i = 0; i < LEADERBOARD_AMOUNT; ++i)
		leaderboardOut.write((char*)&lb[i], sizeof(struct Data));

	leaderboardOut.close();
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::SortLeaderboard()
{
	struct Data tmp;

	for(int i = 0; i < LEADERBOARD_AMOUNT + 1; ++i)
	{
		for(int j = i + 1; j < LEADERBOARD_AMOUNT + 1; ++j)
		{
			if(lb[j].value > lb[i].value)
			{
				tmp = lb[j];
				lb[j] = lb[i];
				lb[i] = tmp;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::HelpSection()
{
	PrintHelp();

	while(true)
	{
		if(_kbhit())
		{
			keyInput = _getch();

			if(keyInput == KEY_ENTER)
			{
				menuFlag = 0;
				ClearScreen();
				break;
			}
		}
	}
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::PrintHelp()
{
	cout << endl;
	cout << "\t------- Help -------" << endl;
	cout << endl << endl;
	cout << "\tPlease use 'W'/'w' to control snake to eat food." << endl;
	cout << "\t           'A'/'a'" << endl;
	cout << "\t           'S'/'s'" << endl;
	cout << "\t           'D'/'d'" << endl;
	cout << "" << endl;
	cout << "\tThis game is borderless. When you hit boundary, you will across it." << endl;

	//print "Quit"
	PutCursor(8, 12);
	PrintColorfulMessage(COLOR_USING, "Quit");
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::ClearScreen()
{
	PutCursor(0, 0);
	for(int i = 0; i < 25; ++i)
		cout << "                                                                             " << endl;
	PutCursor(0, 0);
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::PutCursor(const int x, const int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::SetColor(const int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

////////////////////////////////////////////////////////////////////////////////////

void GameInterface::PrintColorfulMessage(const int c, const string message)
{
	SetColor(c);
	cout << message.c_str();
	SetColor(COLOR_NORMAL);
}

////////////////////////////////////////////////////////////////////////////////////

string GameInterface::GetString(const string message)
{
	char* input = new char[256];
	
	PrintColorfulMessage(COLOR_USING, message);
	
	cin.getline(input, 256, '\n');
	string fileIn = input;
	
	delete [] input;
	
	return fileIn;
}