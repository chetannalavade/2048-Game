// 2048_Game_New.cpp

#include<iostream>
#include<iomanip>
#include<ctime>//for random position
#include<cstdlib>
using namespace std;

int board[4][4];//global board

int dirLine[] = { 1,0,-1,0 };//for directional mapping 
int dirCol[] = { 0,1,0,-1 };

//function for generating random position
pair<int, int> generateunoccupiedposition()
{
	int occupied = 1;
	int line, column;
	while (occupied)
	{
		line = rand() % 4;
		column = rand() % 4;
		if (board[line][column] == 0)//check if the location is free or not
		{
			occupied = 0;
		}
	}

	return make_pair(line, column);
}

//function to randomly genrate no at any random location
void addpiece()
{
	pair<int, int> pos = generateunoccupiedposition();
	board[pos.first][pos.second] = 2;
}

//function to reset the game
void newgame()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			board[i][j] = 0;
		}
	}

	addpiece();

}

//printing menu and board
void printUI()
{
	system("cls");
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 0)
			{
				cout << setw(4) << ".";
			}
			else
			{
				cout << setw(4) << board[i][j];
			}
		}
		cout << endl;
	}

	cout << "n : New game , w : up , s : down , a : left , d : right , q : quit\n";
}

//function to check if move can be done or not
bool candomove(int line, int column, int nextline, int nextcolumn)
{
	if (nextline < 0 || nextcolumn < 0 || nextline >= 4 || nextcolumn >= 4 || (board[line][column] != board[nextline][nextcolumn] && board[nextline][nextcolumn] != 0))
	{
		return false;//can not do the move
	}
	return true;
}

//function to move in the enterd direction
void applymove(int direction)
{
	int startline = 0, startcolumn = 0, linestep = 1, columnstep = 1;
	if (direction == 0)
	{
		startline = 3;
		linestep = -1;
	}
	if (direction == 1)
	{
		startcolumn = 3;
		columnstep = -1;
	}

	int movepossible, canaddpiece = 0;
	
	do
	{
		movepossible = 0;
		for (int i = startline; i >= 0 && i < 4; i = i + linestep)
		{
			for (int j = startcolumn; j >= 0 && j < 4; j = j + columnstep)
			{
				int nextI = i + dirLine[direction], nextJ = j + dirCol[direction];
				if (board[i][j] && candomove(i, j, nextI, nextJ))
				{
					board[nextI][nextJ] = board[nextI][nextJ] + board[i][j];
					board[i][j] = 0;
					movepossible = 1;
					canaddpiece = 1;
				}
			}
		}

		printUI();
	} while (movepossible);

	if (canaddpiece)
	{
		addpiece();//if the term moves generates new number
	}
}

int wincheck()
{
	for (int i = 0; i < 4; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (board[i][j] == 128)
			{
				return 1;
			}
		}
	}

	return 0;
}

//main function
int main()
{
	int flag = 0;
	srand(time(0));
	char commandtodir[128];
	commandtodir['s'] = 0;
	commandtodir['d'] = 1;
	commandtodir['w'] = 2;
	commandtodir['a'] = 3;

	newgame();

	while (true)
	{
		printUI();
		char command;
		cin >> command;
		if (command == 'n')
		{
			newgame();
		}
		else if (command == 'q')
		{
			break;
		}
		else
		{
			int currentdir = commandtodir[command];
			applymove(currentdir);
		}
		cout << flag << endl;
		cout << wincheck() << endl;
		if (wincheck() == 1 && flag == 0)
		{
			flag = 1;
			cout << "Congrats you have won the game\n";
			char c;
			jump:
			cout << "c: continue playing , q: quit\n";
			cin >> c;
			if (c == 'q')
			{
				break;
			}
			else if (c == 'c')
			{
				continue;
			}
			else
			{
				goto jump;
			}
		}
	}

	return 0;
}
