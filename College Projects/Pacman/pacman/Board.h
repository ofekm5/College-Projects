#pragma once

#include "gameObject.h"
#include "Pacman.h"//did a lot of errors without this include.
#include "Ghost.h"
#include "Fruit.h"
class Board {

private:
	int length ;
	int height ;
	char matrixBoard[25][80];
	int breadCrumbs;
public:
	
	void setcurrcell(int x, int y, char c);
	char getcurrcell(int x, int y)const;
	void printBoard()const;
	void setBreadcrumbs(const int _breadcrumbs);
	int getBreadcrumbs()const;
	void setLength(const int length);
	void setHeight(const int height);
	int getLength()const;
	int getHeight()const;
	void clearBoard();
};