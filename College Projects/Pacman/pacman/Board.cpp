#include "Board.h"
using namespace std;

void Board::printBoard() const {	

	for (int i = 0; i < height; i++)
	{
		for (int j = 0; j <= length; j++) {
			if(this->matrixBoard[i][j]!='&'&&this->matrixBoard[i][j]!='0')
				cout << this->matrixBoard[i][j];
		}	
		cout << "\n";
	}
}





/* get and set current cells on board accorrding to x,y */

char Board::getcurrcell(int x, int y)const {
	return this->matrixBoard[x][y];
}

void Board::setcurrcell(int x, int y, char c) {
	this->matrixBoard[x][y] = c;
}

void Board::setBreadcrumbs(const int breadCrumbs)
{
	this->breadCrumbs = breadCrumbs;
}
int Board::getBreadcrumbs()const
{
	return this->breadCrumbs;
}

void Board::setLength(const int length)
{
	this->length = length;
}
void Board::setHeight(const int height)
{
	this->height = height;
}
int Board::getHeight()const
{
	return this->height;
}
int Board::getLength()const
{
	return this->length;
}
void Board::clearBoard()//a function that clears the board after each turn
{
	for (int i = 0; i <25; i++)
	{
		for (int j = 0; j <80; j++)
		{
			matrixBoard[i][j] = '0';
		}
	}
}