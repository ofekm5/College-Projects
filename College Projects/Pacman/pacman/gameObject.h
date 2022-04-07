#pragma once
#include <iostream>
#include <windows.h>
#include <conio.h>
#include <vector>
class Board;

void gotoxy(int x, int y);

class gameObject
{
protected:
	int x;
	int y;
	int prevX;
	int prevY;
	int initX;
	int initY;
public:
	gameObject(int x, int y, int prevX, int prevY, int initX, int initY);
	void setX(const int x);
	void setY(const int y);
	const int getX() const;
	const int getY() const;
	const int getInitX()const;
	const int getInitY()const;
	const int getPrevX() const;
	void setPrevX(const int x);
	const int getPrevY() const;
	void setPrevY(const int y);
	void setInitX(const int _initX);
	void setInitY(const int _initY);
	virtual void move(Board& board, char& c, std::vector <std::pair<int, int>> inviVec,int pacx=-1, int pacy=-1) = 0;
	bool isInvisiblePath(std::vector <std::pair<int, int>> inviVec, int x, int y);
	void respawn();
	virtual ~gameObject();
};
