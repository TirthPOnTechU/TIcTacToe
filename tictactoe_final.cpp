//TIC-TAC-TOE [game]

#include <iostream>
#include <string>
#include <sstream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int SIZE = 3;

void displayBoard(string b[][SIZE]);
bool userFirst();
bool currentPlayerWon(string b[][SIZE], string symbol);
void generateComputerMove(string b[][SIZE],int &row,int &col);
/*Declaration for new function that generates the position for the next computer
move. This function checks the board to see if user is about to win. If he/she is,
the next computer move produced is such that is does not allow the user's win*/
int main() {
	//construct board
	string board[SIZE][SIZE];

	int position_id = 1;
	for (int i=0; i< SIZE; i++) {
		for (int j=0; j < SIZE; j++) {
			board[i][j] = to_string(position_id);
			/*  stringstream ss;
			   ss << position_id;
			   board[i][j] = ss.str();
			 */position_id++;
		}
	}

	//Initial game output
	cout << "Welcome to Tic-Tac-Toe" << endl;

	bool userTurn = userFirst();
	if (userTurn == true) {
		cout << "Player goes first!" << endl;
	} else {
		cout << "Computer goes first!" << endl;
	}

	//Loop for turn taking in game
	int positionsRemaining = SIZE * SIZE;
	bool userWon = false;
	bool computerWon = false;

	while ((positionsRemaining > 0)
	       && (!userWon) && (!computerWon)) {
		displayBoard(board);

		//User's turn
		if (userTurn) {
			bool validMove = false;
			while (!validMove) {
				int position_id;
				cout << "Enter a position: ";
				cin >> position_id;
				if ((position_id <= (SIZE*SIZE))
				    && (position_id > 0)) {
					int row = (position_id-1)/SIZE;
					int col = (position_id-1)%SIZE;
					//cout << "row = " << row << " col = " << col << endl;
					if ((board[row][col] != "X")
					    && (board[row][col] != "O")) {
						board[row][col] = "X";
						validMove = true;
					} else {
						cout << "Position already used. Try again." << endl;
					}

				} else {
					cout << "Position invalid. Try again." << endl;
				}
			}
			positionsRemaining--;
			userWon = currentPlayerWon(board, "X");
			userTurn = false;
		}

		//Computer's turn
		else {
			int row,col;
      generateComputerMove(board,row,col);/*computer move generated but nothing
			is returned since parameters are passed by reference so row and col are
			already set to values by the function*/
      board[row][col] = "O";
      positionsRemaining--;/*positions remaining reduced for future check for if
			another move can be taken or is the board full*/
      computerWon = currentPlayerWon(board, "O");/*checks if computer won*/
      userTurn = true;/*next move is user's turn*/
 }

	}

	//Display game result
	displayBoard(board);
	if (userWon) {
		cout << "Congratulations! You have won!" << endl;
	} else if (computerWon) {
		cout << "The computer has won. Try again." << endl;
	} else {
		cout << "Out of moves. Try again." << endl;
	}
	return 0;
}

void displayBoard(string b[][SIZE]) {
	cout << "Tic-tac-toe board:" << endl << endl;
	for (int i=0; i< SIZE; i++) {
		for (int j=0; j < SIZE; j++) {
			cout << b[i][j] << "\t";
		}
		cout << endl;
	}
	cout << endl;
}

bool userFirst() {
	//set seed for random number generation
	srand(time(NULL));

	//generate a random number
	//0 for computer
	//1 for user
	int num = rand()%2;
	if (num == 0) {
		return false;
	}
	return true;
}

//Return true if player/computer with symbol (X or O) has won
bool currentPlayerWon(string b[][SIZE], string symbol) {
	//Horizontal case
	//Loop through each row
	for (int i=0; i < SIZE; i++) {
		bool rowWinDetected = true;
		//Check all positions in row and see if they are the same symbol
		for (int j = 0; j < SIZE; j++) {
			if (b[i][j] != symbol) {
				rowWinDetected = false;
			}
		}
		if (rowWinDetected) {
			return true;
		}
	}

	//Vertical case
	//Loop through each column
	for (int i=0; i < SIZE; i++) {
		bool colWinDetected = true;
		//Check all positions in column and see if they are the same symbol
		for (int j = 0; j < SIZE; j++) {
			if (b[j][i] != symbol) {
				colWinDetected = false;
			}
		}
		if (colWinDetected) {
			return true;
		}
	}

	//Diagonal case #1
	bool diagonal1WinDetected = true;
	for (int i=0; i < SIZE; i++) {
		if (b[i][i] != symbol) {
			diagonal1WinDetected = false;
		}
	}
	if (diagonal1WinDetected) {
		return true;
	}

	//Diagonal case #2
	bool diagonal2WinDetected = true;
	for (int i=0; i < SIZE; i++) {
		if (b[(SIZE-1)-i][i] != symbol) {
			diagonal2WinDetected = false;
		}
	}
	if (diagonal2WinDetected) {
		return true;
	}

	//otherwise win not diagonal2WinDetected
	return false;

}
void generateComputerMove(string b[][SIZE],int &row,int &col)
{

	/*Rows checked to see if user is about to get three horizontally*/
	int i=0;
	for (int j=0;j<SIZE;j++)/*go through all rows*/
	{
		if (b[i][j]=="X"&&b[i+1][j]=="X"&&b[i+2][j]!="O")/*if user has any two positions filled in that row, put computer move in remaining position to block win*/
			{
				col=j;
				row=i+2;
				return;
			}
			else if(b[i][j]=="X"&&b[i+2][j]=="X"&&b[i+1][j]!="O")
			{
				col=j;
				row=i+1;
				return;
			}
			else if(b[i+1][j]=="X"&&b[i+2][j]=="X"&&b[i][j]!="O")
			{
				col=j;
				row=i;
				return;
			}
	}

	/*Columns checked to see if user is about to get three vertically*/
	int j=0;
	for (int i=0;i<SIZE;i++)/*go through all columns*/
	{
		if (b[i][j]=="X"&&b[i][j+1]=="X"&&b[i][j+2]!="O")/*if user has any two positions filled in that column, put computer move in remaining position to block win*/
		{
			col=j+2;
			row=i;
			return;
		}
		else if(b[i][j]=="X"&&b[i][j+2]=="X"&&b[i][j+1]!="O")
		{
			col=j+1;
			row=i;
			return;
		}
		else if(b[i][j+1]=="X"&&b[i][j+2]=="X"&&b[i][j]!="O")
		{
			col=j;
			row=i;
			return;
		}
	}

	/*diagonally checked to see if user is about to get three diagonally*/
	int k=0;
	if (b[k][k]=="X"&&b[k+1][k+1]=="X"&&b[k+2][k+2]!="O")/*if user has any two positions filled in diagonally(left to right), put computer move in remaining position to block win*/
	{
		col=k+2;
		row=k+2;
		return;
	}
	else if(b[k][k]=="X"&&b[k+2][k+2]=="X"&&b[k+1][k+1]!="O")
	{
		col=k+1;
		row=k+1;
		return;
	}
	else if(b[k+1][k+1]=="X"&&b[k+2][k+2]=="X"&&b[k][k]!="O")
	{
		col=k;
		row=k;
		return;
	}

	/*diagonally checked from other side to see if user is about to get three diagonally*/
	k=2;
	int t=0;
	if (b[k][t]=="X"&&b[k-1][t+1]=="X"&&b[k-2][t+2]!="O")/*if user has any two positions filled in diagonally(right to left), put computer move in remaining position to block win*/
	{
		col=t+2;
		row=k-2;
		return;
	}
	else if(b[k][t]=="X"&&b[k-2][t+2]=="X"&&b[k-1][t+1]!="O")
	{
		col=t+1;
		row=k-1;
		return;
	}
	else if(b[k-1][t+1]=="X"&&b[k-2][t+2]=="X"&&b[k][t]!="O")
	{
		col=t;
		row=k;
		return;
	}

	for (int i = 0; i < SIZE; i++)/*if user is not about to win, make computer move the first open position detected*/
	{
		for (int j = 0; j < SIZE; j++)
		{
			if (b[j][i]!="X"&&b[j][i]!="O")
			{
				col=i;
				row=j;
				return;
			}
		}
	}
}
