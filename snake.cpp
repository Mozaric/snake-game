#include "snake.h"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

SnakeGame::SnakeGame(const int width, const int height, const int difficulty) : 
SCREEN_SIZE_X(width),
SCREEN_SIZE_Y(height),
SNAKE_LENGTH_MAX(SCREEN_SIZE_X * SCREEN_SIZE_Y), 
SNAKE_HEAD('#'),
SNAKE_BODY('o'),
EGG('*'),
DIFFICULTY(difficulty),
SPEED((3 - difficulty + 1) * 100)
{
	srand((unsigned)time(NULL));
	
	//screen memory allocation
	screen = new char*[SCREEN_SIZE_X];
	for(int i = 0; i < SCREEN_SIZE_X; ++i)
		screen[i] = new char[SCREEN_SIZE_Y];
	
	//snake object
	snake_length = 4;
	snake_direction = DIR_W;
	snake_pos_x = new int[SNAKE_LENGTH_MAX];
	snake_pos_y = new int[SNAKE_LENGTH_MAX];
	for(int i = 0; i < SNAKE_LENGTH_MAX; ++i)
	{
		snake_pos_x[i] = -1;
		snake_pos_y[i] = -1;
	}
	
	//init game status
	score = 0;
	min = 0;
	sec = 0.f;
	game_over = false;
	
	key_input = ' ';
	
	//print first screen
	ClearScreen();
	
	InitSnake();
	PutSnake();
	CreateEgg();
	PutEgg();
	
	PrintStatus();
	PrintScreenAndBoundary();
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

SnakeGame::~SnakeGame()
{
	delete snake_pos_x;
	delete snake_pos_y;
	delete [] screen;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::InitSnake()
{
	snake_pos_x[0] = SCREEN_SIZE_X / 2;
	snake_pos_y[0] = SCREEN_SIZE_Y / 2;
	
	for(int i = 1; i < snake_length; ++i)
	{
		snake_pos_x[i] = SCREEN_SIZE_X / 2;
		snake_pos_y[i] = SCREEN_SIZE_Y / 2 + i;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::CreateEgg()
{
	do
	{
		egg_x=rand()%SCREEN_SIZE_X;
		egg_y=rand()%SCREEN_SIZE_Y;
	}while(screen[egg_x][egg_y] != ' ');
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::PutSnake()
{
	screen[ snake_pos_x[0] ][ snake_pos_y[0] ] = SNAKE_HEAD;
	for(int i = 1; i < snake_length; ++i)
	{
		screen[ snake_pos_x[i] ][ snake_pos_y[i] ] = SNAKE_BODY;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::PutEgg()
{
	screen[egg_x][egg_y] = EGG;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::ClearScreen()
{
	for(int i = 0; i < SCREEN_SIZE_X; ++i)
	{
		for(int j = 0; j < SCREEN_SIZE_Y; ++j)
		{
			screen[i][j] = ' ';
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::PrintStatus()
{
	cout << "Width: " << setw(5) << SCREEN_SIZE_X;
	cout << "\tHeight: " << setw(5) << SCREEN_SIZE_Y;
	cout << "\tDifficulty: " << setw(5) << DIFFICULTY << endl;
	cout << "Score: " << setw(5) << score;
	cout << "\tTime: " << setw(2) << min << ":" << setw(2) << (int)sec << endl;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::PrintScreenAndBoundary()
{
	cout << " x";
	for(int i = 0; i < SCREEN_SIZE_X; ++i)
	{
		cout << "-";
	}
	cout << "x\n";
	
	for(int i = 0; i < SCREEN_SIZE_Y; ++i)
	{
		cout << " |";
		for(int j = 0; j < SCREEN_SIZE_X; ++j)
		{
			if(screen[j][i] == SNAKE_HEAD)
			{
				SetColor(14);
				cout << screen[j][i];
				SetColor(7);
			}
			else if(screen[j][i] == SNAKE_BODY)
			{
				SetColor(2);
				cout << screen[j][i];
				SetColor(7);
			}
			else if(screen[j][i] == EGG)
			{
				SetColor(240);
				cout << screen[j][i];
				SetColor(7);
			}
			else
				cout << screen[j][i];
		}
		cout << "|\n";
	}
	
	cout << " x";
	for(int i = 0; i < SCREEN_SIZE_X; ++i)
	{
		cout << "-";
	}
	cout << "x\n";
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int SnakeGame::Start()
{
    start_time = clock();
	
	while(true)
	{
		if(_kbhit())
		{
			key_input = _getch();
		}
		
		if(clock() - start_time >= SPEED)
		{
			UpdateTimer();
			
			CheckDir();
			game_over = Move(snake_direction);
			
			ClearScreen();
			PutCursor(0, 0);
			
			PutSnake();
			PutEgg();
			
			PrintStatus();
			PrintScreenAndBoundary();

			if(game_over)
			{
				SetColor(240);

				//print game over message
				PutCursor(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 + 2);
				if(snake_length == SNAKE_LENGTH_MAX)
					cout << "Congratulation! You are Winner!";
				else
					cout << "Game Over!";

				//print score
				PutCursor(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 + 3);
				cout << "Your Score is ";
				SetColor(252);
				cout << score;
				PutCursor(SCREEN_SIZE_X / 3, SCREEN_SIZE_Y / 2 + 4);

				SetColor(7);

				return score;
			}
		}
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::CheckDir()
{
	switch(key_input)
	{
	case 'W':
	case 'w':
		key_input = DIR_W;
		break;
	case 'S':
	case 's':
		key_input = DIR_S;
		break;
	case 'D':
	case 'd':
		key_input = DIR_D;
		break;
	case 'A':
	case 'a':
		key_input = DIR_A;
		break;
	}
	
	if(abs(snake_direction - key_input) == 1 || abs(snake_direction - key_input) == 3)
		snake_direction = key_input;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SnakeGame::Move(int dir)
{
	switch(dir)
	{
	case DIR_W:
		return MoveTo(snake_pos_x[0], snake_pos_y[0] - 1);
	case DIR_A:
		return MoveTo(snake_pos_x[0] - 1, snake_pos_y[0]);
	case DIR_S:
		return MoveTo(snake_pos_x[0], snake_pos_y[0] + 1);
	case DIR_D:
		return MoveTo(snake_pos_x[0] + 1, snake_pos_y[0]);
	default:
		return true;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

bool SnakeGame::MoveTo(int x, int y)
{
	//if reach the boundary, across it.
	if(x < 0)
		x += SCREEN_SIZE_X;
	else if(x >= SCREEN_SIZE_X)
		x -= SCREEN_SIZE_X;
	if(y < 0)
		y += SCREEN_SIZE_Y;
	else if(y >= SCREEN_SIZE_Y)
		y -= SCREEN_SIZE_Y;
	
	//if reach the snake body and not the tail, game over
	if(screen[x][y] == SNAKE_BODY && !(x == snake_pos_x[snake_length - 1] && y == snake_pos_y[snake_length - 1]))
		return true;
	
	//when eat food
	if(screen[x][y] == EGG)
	{
		snake_length++;
		score++;
		if(!(snake_length == SNAKE_LENGTH_MAX))
			CreateEgg();
	}
	
	//change the snake pos
	for(int i = snake_length - 1; i > 0; --i)
	{
		snake_pos_x[i] = snake_pos_x[i-1];
		snake_pos_y[i] = snake_pos_y[i-1];
	}
	snake_pos_x[0] = x;
	snake_pos_y[0] = y;

	//if finish the game
	if(snake_length == SNAKE_LENGTH_MAX)
		return true;

	return false;
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::UpdateTimer()
{
	start_time = clock();
	sec += (float)SPEED/1000;
	if((int)sec == 60)
	{
		sec = 0;
		min += 1;
	}
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::PutCursor(const int x, const int y)
{
	COORD pos;
	pos.X = x;
	pos.Y = y;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), pos);
}

////////////////////////////////////////////////////////////////////////////////////

void SnakeGame::SetColor(const int c)
{
	SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), c);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////