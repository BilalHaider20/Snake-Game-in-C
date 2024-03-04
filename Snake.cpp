#include <iostream>
using namespace std;
#include <deque>
#include <conio.h>
#include <thread>
#include <chrono>
#include <ctime>
string SnakeHead = "@";
string SnakeBody = "o";
string Snakefruit="Q";
string background_board=" ";
string board[20][20];
int board_size = sizeof(board) / sizeof(board[0]);
int Snake_size = 1;
int score = 0;
int gamelevel=1;
int speedmultiplier=1;
void start();
struct Snakesegment
{
	int pos_x;
	int pos_y;
	Snakesegment(int x, int y)
	{
		this->pos_x = x;
		this->pos_y = y;
	}
};
deque<Snakesegment> snake;

void Draw_Snake()
{

	for (const auto segment : snake)
	{
		if (segment.pos_x == snake.front().pos_x && segment.pos_y == snake.front().pos_y)
		{
			board[segment.pos_x][segment.pos_y] = SnakeHead;
		}
		else
			board[segment.pos_x][segment.pos_y] = SnakeBody;
	}
	
}
void Create_Fruit(int s)
{
    srand(time(0));

    
    
        int x = rand() % (board_size - 1);
        int y = rand() % (board_size - 1);
        while (true)
        {
            if (board[x][y] == background_board)
            {
                board[x][y] = Snakefruit;
                break;
            }
            else
            {
                x = rand() % (board_size - 1);
                y = rand() % (board_size - 1);
            }
        }
    
}

void reset()
{
	score=0;
	gamelevel=1;
	Snake_size=1;
	snake.clear();
}
void initialize_Board()
{
	reset();
    for (int i = 0; i < board_size; i++)
    {
        for (int j = 0; j < board_size; j++)
        {
            board[i][j] = background_board;
        }
    }
    Create_Fruit(1);
}
void Display_Board()
{
	string Snake_board[20][20];
	for (int i = 0; i < board_size; i++)
	{
		for (int j = 0; j < board_size; j++)
		{
			Snake_board[i][j] = board[i][j];
		}
	}
	string output;
	output += "\n\n\t\t|==============================================|\n";
	output += "\t\t|  Score: "+to_string(score) +"\t\t\t"+"Level: "+to_string(gamelevel)+"       |\n";
	output += "\t\t|==============================================|\n";
	output += "\t\t|//////////////////////////////////////////////|\n";
	for (int i = 0; i < board_size; i++)
	{
		output += "\t\t|/| ";
		for (int j = 0; j < board_size; j++)
		{
			output +=Snake_board[i][j] + " ";
		}
		output += " |/|\n";
	}
	output += "\t\t|//////////////////////////////////////////////|\n";
	output += "\t\t|==============================================|";

	cout << output;
}
bool isGameOver(int x, int y)
{
    if (board[x][y] == Snakefruit)
    {
        score++;
        if(score%5==0)
        {
        gamelevel++;
        speedmultiplier*=2;
		}
        Snake_size++;
        Create_Fruit(1);
        return false;
    }
    else if (board[x][y] == SnakeBody)
    {
        cout << "\n\n\t   Game Over! Your Score: " << score << endl;
        chrono::milliseconds duration(2000);
        this_thread::sleep_for(duration);
        return true;
    }
    return false;
}
void removebody(int x, int y)
{
	board[x][y]=background_board;
}
void snake_position(int x, int y)
{
	snake.push_front(Snakesegment(x, y));
	if (snake.size() > Snake_size)
	{
		Snakesegment tail= snake.back();
		snake.pop_back();
		removebody(tail.pos_x,tail.pos_y);
	}
}
int pause()
{
    char c;
    cout << "\n\nGame Paused";
    cout << "\n\n1. Resume \n2. Quit\n";
    while (true)
    {
        c = _getch();
        switch (c)
        {
        case 27:
        case '1':
            return 0;
        case '2':
            return 1;
        default:
            break;
        }
    }
}
void replay()
{
	cout<<"Press any key to continue....."<<endl;
	_getch();
	cout<<"\nPress 1 to play again "<<endl;
	cout<<"\nPress 2 to Quit Game "<<endl;
	char temp=getch();
	if(temp=='2')
	exit(0);
	else if(temp=='1')
	start();
		
}
void SnakeMovements(int Head_X, int Head_Y)
{
	char lastkey='d';
	while (true)
	{
		
		if (isGameOver(Head_X, Head_Y))
        {
          replay();
            return;
        }
		snake_position(Head_X, Head_Y);
		Draw_Snake();
		system("cls");
		Display_Board();
		 int delay_factor = 200 - ((gamelevel - 1) * 10 *speedmultiplier);
        if (delay_factor < 50)
            delay_factor = 50;
			
		chrono::milliseconds duration(delay_factor);
		this_thread::sleep_for(duration);

		if (_kbhit())
		{
			 char key = _getch();
			 if(key==27)	//ESC character
			 {
			 
			 switch(pause())
			 {
			 	case 0:
			 		break;
			 	case 1:
			 		return;
			 }
			}
			if(key=='w'|| key=='s'|| key=='a'|| key=='d')
			{
				if(lastkey=='w'&& key!='s'
				|| lastkey=='s'&& key!='w'|| lastkey=='a'&& key!='d'|| lastkey=='d'&& key!='a')
				lastkey=key;
			}
			switch (lastkey)
			{
			case 'w':
				lastkey = 'w';
				break;
			case 's':
				lastkey = 's';
				break;
			case 'a':
				lastkey = 'a';
				break;
			case 'd':
				lastkey = 'd';
				break;
			default:
				break;
			}
		}
		if (lastkey == 'w')
			Head_X--;
		else if (lastkey == 's')
			Head_X++;
		else if (lastkey == 'a')
			Head_Y--;
		else if (lastkey == 'd')
			Head_Y++;
		if(Head_Y<0)
		Head_Y=board_size-1;
		if(Head_Y>=board_size)
		Head_Y=0;
		if(Head_X<0)
		Head_X=board_size-1;
		if(Head_X>=board_size)
		Head_X=0;
	}
}
void start()
{
	initialize_Board();
	int x = board_size / 2;
	int y = board_size / 2;
	SnakeMovements(x, y);
}
void instructions()
{
    while (true)
    {
        system("cls");
        cout << "\n\n<======================= Snake Game ===========================>\n";
        cout << "\n                 Gameplay Instructions\n";

        cout << "\n\n\t\tSnake Movement\n";
        cout << "\n\t\t   Move up\t:  W \n";
        cout << "\n\t\t   Move Down\t:  S \n";
        cout << "\n\t\t   Move Left\t:  A \n";
        cout << "\n\t\t   Move Right\t:  D \n";
        cout << "\n\t\t   Pause\t:  Esc \n";
        cout << "\n\n\t\t The Snake speed will incease as \n\t\tthe game approaches Higher level\n\n";

        cout << "\n\t\tPress Esc to Go Back\n\n";

        char c;
        c = _getch();

        switch (c)
        {
        case 27:
            return;
        default:
            break;
        }
    }
}
int main()
{
	 while (true)
    {
        system("cls");
        cout << "\n\n<======================= Snake Game ===========================>\n";
        cout << "\n\n\n\t\t\t1. Start Game";
        cout << "\n\n\n\t\t\t2. Game Instruction";
        cout << "\n\n\n\t\t\t3. Exit\n\n";
        char c;
        c = _getch();

        switch (c)
        {
        case '1':
			start();
            break;

        case '2':
            instructions();
            break;
        case '3':
            cout << "\n\n\t\tExiting...\n\n";
            return 0;
        default:
            break;
        }
    }

	return 0;
}