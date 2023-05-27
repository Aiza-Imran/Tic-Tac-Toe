#include <iostream>
using namespace std;

enum PlayerTurn { FIRST_PLAYER = 1, SECOND_PLAYER = 2 };
enum GameStatus { Draw, WIN, IN_PROGRESS };


class GameBoard
{
	char data[3][3];   //a two dimensional array of size 9.
	GameStatus gameStatus;
	int validMovesCount;
	

	//return type is ENUM(Game Status). It returns win, draw or in_progress based on marked positions by both players.
	GameStatus status()
	{
		if (validMovesCount <= 9)
		{
			if ((data[0][0] == data[0][1] and data[0][0] == data[0][2]) || (data[1][0] == data[1][1] and data[1][0] == data[1][2]) || (data[2][0] == data[2][1] and data[2][0] == data[2][2]) ||
				(data[0][0] == data[1][0] and data[0][0] == data[2][0]) || (data[0][1] == data[1][1] and data[0][1] == data[2][1]) || (data[0][2] == data[1][2] and data[0][2] == data[2][2]) ||
				(data[0][0] == data[1][1] and data[0][0] == data[2][2]) || (data[0][2] == data[1][1] and data[0][2] == data[2][0]))
			{
				return WIN;
				
			}
			return IN_PROGRESS;
		}
		return Draw;
	}

	public:
		GameBoard()        //initializes game board and sets moves count.
		{
			char input = '1';
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					data[i][j] = input;
					input++;
				}
			}
			gameStatus = IN_PROGRESS;
			validMovesCount = 0;
		}

		//displays the updated board with marked and unmarked positions.
		void displayBoard()
		{
			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 3; j++)
				{
					cout << data[i][j] << " ";
				}
				cout << endl;
			}
		}

		//marks given position with given symbol on board.
		void markBoard(char pos, char playerSymbol)
		{
			data[0][pos - '1'] = playerSymbol;
		}

		//checks whether the position is valid or not with respect to the game board.
		bool isValidPosition(char pos)
		{
			if (data[0][pos-'1'] >= '1' && data[0][pos-'1'] <= '9')
			{
				return true;
			}
			return false;
		}

		//returns true if the position is already marked/selected by any player.
		bool isAlreadyMarked(char pos)
		{
			if (data[0][pos - '1'] >= '1' && data[0][pos - '1'] <= '9')
			{
				return false;
			}
			return true;
		}

		//increments in validMoves after every turn and returns updated moves.
		int getValidMovesCount()
		{
			validMovesCount = validMovesCount + 1;
			return validMovesCount;
		}

		//returns whether the status of game is draw, won or in_progress.
		GameStatus getGameStatus()
		{
			return status();
		}
};

class TicTacToe
{
public:	
	
	//starts game.
	void playGame()
	{
		char player1Symbol;
		char player2Symbol;
		bool validSymbol = false;

		while (validSymbol == false)
		{
			cout << "Enter symbol for player 1: ";
			cin >> player1Symbol;

			validSymbol = isValidSymbol(player1Symbol);  //checks whether the symbol chosen by player 1 is a valid symbol or not.

			if (validSymbol == false)
			{
				cout << "Not a valid symbol.\n";
			}
		}

		validSymbol = false;

		while (validSymbol == false)
		{
			cout << "Enter symbol for player 2: ";
			cin >> player2Symbol;

			validSymbol = isValidSymbol(player2Symbol);

			if (validSymbol == false)
			{
				cout << "Not a valid symbol.\n";
			}
			 
			else if (player2Symbol == player1Symbol)     //For player 2, additional check that second player's symbol should not be same as first player's symbol.
			{
				validSymbol = false;
				cout << "Symbol already taken.\n";
			}
			
		}

		GameBoard tictac;
		char position;
		int movesCount;
		bool validMove;

		PlayerTurn currentPlayer = FIRST_PLAYER;    //maintains which player's turn it is.
		char currentPlayerSymbol = player1Symbol;

		while (tictac.getGameStatus() == IN_PROGRESS)
		{
			tictac.displayBoard();
			do
			{
				validMove = false;
				cout << "Player " << currentPlayer << " Turn: Enter cell#: ";
				cin >> position;

				bool alreadyMarked;

				if (!(position >= '1' && position <= '9')) {      //to check the position entered by players is a valid position within range or not.
					cout << "Choose a position between 1-9.\n";
					alreadyMarked = true;
				}
				else {
					alreadyMarked = tictac.isAlreadyMarked(position);          //checks whether that position is already marked by any player or not.
					if (alreadyMarked) {
						cout << "Position already marked. Choose any other position.\n";
					}
				}
				
				if (!tictac.isAlreadyMarked(position) && tictac.isValidPosition(position))
				{
					tictac.markBoard(position, currentPlayerSymbol);
					validMove = true;
					movesCount = tictac.getValidMovesCount();
					cout <<"Moves count: " << movesCount << endl;
				}
			} while (validMove == false);

			if (tictac.getGameStatus() == WIN)
			{
				tictac.displayBoard();
				cout << "Game won by Player " << currentPlayer << '\n';
			}
			else if (tictac.getGameStatus() == Draw)
			{
				tictac.displayBoard();
				cout << "Game Draw\n";
			}
			else //switches turn if game is in_process
			{
				currentPlayer = (currentPlayer == FIRST_PLAYER ? SECOND_PLAYER : FIRST_PLAYER);
				currentPlayerSymbol = (currentPlayerSymbol == player1Symbol ? player2Symbol : player1Symbol);
			}
		}
	}
	bool isValidSymbol(char playerSymbol)     //returns true if symbol selected by player is a valid position.
	{
		if (playerSymbol >= '1' && playerSymbol <= '9')
		{
			return false;
		}
		return true;
	}
};

int main()
{
	TicTacToe tic;
	tic.playGame();   //starts game.
	
	return 0;
}
