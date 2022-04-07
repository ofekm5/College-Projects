#include "Pacman.h"
#include "Board.h"

//getters and setters
Pacman::Pacman(int x, int y, int prevX, int prevY, int initX, int initY, int _lives) :gameObject(x, y, prevX, prevY, initX, initY)
{
	this->lives = _lives;
}

void Pacman::setLives(const int lives)
{
	this->lives = lives;
}
const int Pacman::getLives()const
{
	return this->lives;
}
void Pacman::setPoints(const int _points)
{
	this->points = _points;
}
int Pacman::getPoints()const
{
	return this->points;
}



//a virtual function that moves the pacman
void Pacman::move(Board& board, char& c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy) {
	int height = board.getHeight(), length = board.getLength(), currInd;

	if (c == 'a' || c == 'A')/*moving left*/
	{
		if (board.getcurrcell(this->x, this->y - 1) != '#')
		{
			this->y--;
		}
	}
	else if (c == 'd' || c == 'D')/*moving right*/
	{
		if (board.getcurrcell(this->x, this->y + 1) != '#')
		{
			this->y++;
		}
	}
	else if (c == 'x' || c == 'X')/*moving down*/
	{
		if (board.getcurrcell(this->x + 1, this->y) != '#')
		{
			this->x++;
		}
	}
	else if (c == 'w' || c == 'W')/*moving up*/
	{
		if (board.getcurrcell(this->x - 1, this->y) != '#')
		{
			this->x--;
		}
	}

	gotoxy(prevY, prevX);
	std::cout << " ";
	board.setcurrcell(prevX, prevY, ' ');

	this->prevX = this->x;
	this->prevY = this->y;

	if (board.getcurrcell(this->x, this->y) == '.') {
		this->points++;
		board.setBreadcrumbs(board.getBreadcrumbs() - 1);//need to decrease number of breadcrumbs
	}
	if (isInvisiblePath(inviVec, x, y)) {
		findRespectedPath(board, inviVec, x, y);//change x and y to the next invisible cell
	}

	gotoxy(y, x);
	if (!isInvisiblePath(inviVec, x, y))
		std::cout << "@";
	else
		std::cout << " ";
}


void Pacman::findRespectedPath(Board& board, std::vector <std::pair<int, int>> inviVec, int& x, int& y) {
	bool rowOrColTunnel = true;//indicates the type of the tunnel
	int i;

	if (x == 0 || x == board.getHeight() - 1)
		rowOrColTunnel = true;
	else if (y == 0 || y == board.getLength()||y==board.getLength()-1)
		rowOrColTunnel = false;


	if (rowOrColTunnel) {//Row tunnel
		for (i = 0; i < inviVec.size(); i++) {
			if (y == inviVec[i].second && x != inviVec[i].first) {
				this->x = inviVec[i].first;
				this->y = inviVec[i].second;
				break;
			}
		}
	}
	else {//Col tunnel
		for (i = 0; i < inviVec.size(); i++) {
			if (x == inviVec[i].first && y != inviVec[i].second) {
				this->x = inviVec[i].first;
				this->y = inviVec[i].second;
				break;
			}
		}
	}
}