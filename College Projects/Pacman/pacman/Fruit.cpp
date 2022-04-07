#include "Fruit.h"
#include "Board.h"
Fruit::Fruit(int x, int y, int prevX, int prevY, int initX, int initY):gameObject(x,y,prevX,prevY,initX,initY)
{
	this->lastChar = '.';
	invisible = false;

	/* initialize random seed: */
	srand(time(NULL));

	/* generate secret number between 5 and 9: */
	this->pointValue = rand() % 3 + 5;

	this->fruitMovement = 0;
}
//getters and setters
int Fruit::getPointValue()const
{
	return this->pointValue;
}
void Fruit::setPointValue()
{
	this->pointValue = rand() % 3 + 5;
}

//a virtual function that moves the fruit
void Fruit::move(Board& board, char& c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy)
{
	/* recover former crumb */
	if (this->prevX != -1 && this->prevY != -1) {
		gotoxy(this->prevY, this->prevX);
	}
	else {/* if prev position was starting position */
		gotoxy(this->initY, this->initX);
	}
	std::cout << this->lastChar;

	switch (c) {
	case 0:
		if (board.getcurrcell(this->x, this->y - 1) != '#' && !isInvisiblePath(inviVec, this->x, this->y - 1))//LEFT
			this->y--;
		else if (board.getcurrcell(this->x + 1, this->y) != '#' && !isInvisiblePath(inviVec, this->x + 1, this->y))//DOWN
			this->x++;
		else
			c = 1;
		break;
	case 1:
		if (board.getcurrcell(this->x - 1, this->y) != '#' && !isInvisiblePath(inviVec, this->x - 1, this->y))//UP
			this->x--;
		else if (board.getcurrcell(this->x, this->y + 1) != '#' && !isInvisiblePath(inviVec, this->x, this->y + 1))//RIGHT
			this->y++;
		else
			c = 2;
		break;
	case 2:
		if (board.getcurrcell(this->x + 1, this->y) != '#' && !isInvisiblePath(inviVec, this->x + 1, this->y))//DOWN
			this->x++;
		else if (board.getcurrcell(this->x, this->y + 1) != '#' && !isInvisiblePath(inviVec, this->x, this->y + 1))//RIGHT
			this->y++;
		else
			c = 3;
		break;
	case 3:
		if (board.getcurrcell(this->x, this->y + 1) != '#' && !isInvisiblePath(inviVec, this->x, this->y + 1))//RIGHT
			this->y++;
		else if (board.getcurrcell(this->x - 1, this->y) != '#' && !isInvisiblePath(inviVec, this->x - 1, this->y))//UP
			this->x--;
		else
			c = 0;
		break;
	}

	this->prevX = this->x;
	this->prevY = this->y;

	/* print the fruit and update the board */
	this->lastChar = board.getcurrcell(this->x, this->y);
	gotoxy(this->y, this->x);
	std::cout << this->pointValue;
}
