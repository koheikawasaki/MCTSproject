#include <iostream>
#include <string>

const int SIZE = 3;
const char PLAYER = 'X';
const char COMPUTER = 'O';
const char TIE = 'T';
const char STILL_PLAY = ' ';

using namespace std;

int findBest(char board[SIZE][SIZE], int player);
bool isOpen(char board[SIZE][SIZE], int row, int col);
void copyBoard(char original[SIZE][SIZE], char copy[SIZE][SIZE]);
void print(char board[SIZE][SIZE]);
char gameOver(char board[SIZE][SIZE]);

int main()
{
	char board[SIZE][SIZE];
	for(int i=0; i < SIZE; i++)
	{
		for(int j=0; j < SIZE; j++)
		{
			board[i][j] = '1' + 3*i+j;
		}
	}
	
	int turn = 1;
	while(gameOver(board) == STILL_PLAY)
	{
		if(turn%2 == 1)
		{
			int play;
			do {
				print(board);
				cout << "What number do you with to play at? ";
				char cplay;
				cin >> cplay;
				cin.ignore(20000,'\n');
				play=cplay-'0';
			} while(!isOpen(board, (play-1)/3, (play-1)%3));
			board[(play-1)/3][(play-1)%3] = PLAYER;
		}
		else
		{
			int bestI = -1;
			int bestJ = -1;
			int bestValue = -1;
			
			for(int i=0; i < SIZE; i++)
			{
				for(int j=0; j < SIZE; j++)
				{
					if(isOpen(board,i,j))
					{
						int value = findBest(board, 1);
						if(value > bestValue)
						{
							bestValue=value;
							bestJ = j;
							bestI = i;
						}
					}
				}
			}
			
			board[bestI][bestJ] = COMPUTER;
					
		}
		turn++;
	}
	
	print(board);
	cout << "Game over!";
	if(gameOver(board) == PLAYER)
	{
		cout << "  You win!\n";
	}
	else if(gameOver(board) == COMPUTER)
	{
		cout << "  You lose!\n";
	}
	else
	{
		cout << "  Tie...\n";
	}		
	
	return 0;
}

char gameOver(char board[SIZE][SIZE])
{

	for(int j=0; j<SIZE; j++)
	{
		bool win=true;
		for(int i=0; i<SIZE-1; i++)
		{
			if(board[i+1][j] != board[i][j])
			{
				win=false;
			}
		}
		if(win)
		{
			return board[0][j];
		}
	}		

	for(int j=0; j<SIZE; j++)
	{
		bool win=true;
		for(int i=0; i<SIZE-1; i++)
		{
			if(board[j][i] != board[j][i+1])
			{
				win=false;
			}
		}
		if(win)
		{
			return board[j][0];
		}
	}		
	
	bool win=true;
	for(int i=0; i < SIZE-1; i++)
	{
		if(board[i][i] != board[i+1][i+1])
		{
			win=false;
		}
	}
	if(win)
	{
		return board[0][0];
	}

	win=true;
	for(int i=0; i < SIZE-1; i++)
	{
		if(board[i][SIZE-1-i] != board[i+1][SIZE-1-i-1])
		{
			win=false;
		}
	}
	if(win)
	{
		return board[0][SIZE-1];
	}
	
	// above is someone wins
	
	for(int i=0; i < SIZE; i++)
	{
		for(int j=0; j < SIZE; j++)
		{
			if(isOpen(board,i,j))
			{
				return STILL_PLAY; // still playing
			}
		}
	}
	
	
	return TIE;
}		

int findBest(char board[SIZE][SIZE], int player)
{
	return 0;
}

bool isOpen(char board[SIZE][SIZE], int row, int col)
{
	return board[row][col] != 'X' && board[row][col] != 'O';
}

void copyBoard(char original[SIZE][SIZE], char copy[SIZE][SIZE])
{
	for(int i=0; i < SIZE; i++)
	{
		for(int j=0; j < SIZE; j++)
		{
			copy[i][j] = original[i][j];
		}
	}
}

void print(char board[SIZE][SIZE])
{
	cout << "\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n";
	string temp;
	for(int i=0; i < SIZE; i++)
	{
		temp = "";
		for(int j=0; j < SIZE; j++)
		{
			temp += board[i][j];
			temp += "|";
		}
		cout << temp.substr(0, temp.length()-1) << endl;;
		if(i != SIZE-1)
		{
			cout << "-----\n";
		}
	}
}
	