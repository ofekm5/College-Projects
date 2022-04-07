#include "gameObject.h"
#include "Board.h"

void gotoxy(int x, int y)
{
	HANDLE hConsoleOutput;
	COORD dwCursorPosition;
	std::cout.flush();
	dwCursorPosition.X = x;
	dwCursorPosition.Y = y;
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, dwCursorPosition);
}



gameObject::gameObject(int x, int y, int prevX, int prevY, int initX, int initY) :x(x), y(y), prevX(prevX), prevY(prevY), initX(initX), initY(initY)
{

}

//getters and setters
const int gameObject::getX()const
{
	return this->x;
}

const int gameObject::getY()const
{
	return this->y;
}

void gameObject::setX(int x)
{
	this->x = x;
}

void gameObject::setY(int y)
{
	this->y = y;
}

void gameObject::setPrevX(const int _prevX)
{
	this->prevX = _prevX;
}

void gameObject::setPrevY(const int _prevY)
{
	this->prevY = _prevY;
}

const int gameObject::getPrevX()const
{
	return this->prevX;
}

const int gameObject::getPrevY()const
{
	return this->prevY;
}

const int gameObject::getInitX()const
{
	return this->initX;
}

const int gameObject::getInitY()const
{
	return this->initY;
}

void gameObject::setInitX(const int _initX)
{
	this->initX = _initX;
}

void gameObject::setInitY(const int _initY)
{
	this->initY = _initY;
}

//a function that checks if there is an invisible path
bool gameObject::isInvisiblePath(std::vector <std::pair<int, int>> inviVec, int x, int y) {
	for (int i = 0; i < inviVec.size(); i++) {
		if (inviVec[i].first==x && inviVec[i].second==y)
			return true;
	}
	return false;
}

void gameObject::respawn() {
	this->prevX = initX;
	this->prevY = initY;
	this->x = initX;
	this->y = initY;
}
gameObject::~gameObject() {}