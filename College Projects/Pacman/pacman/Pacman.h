#pragma once
#include <iostream>
#include "gameObject.h"
class Pacman :public gameObject {
private:
	int lives;
	int points = 0;
	//const int initX = 10, initY = 36; /*Initial position of pacman */
public:
	Pacman(int x, int y, int prevX, int prevY, int initX, int initY, int lives);
	void setLives(const int lives);
	const int getLives() const;
	virtual void move(Board& board, char& c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy);
	int getPoints()const;
	void setPoints(const int _points);
	void findRespectedPath(Board& board, std::vector <std::pair<int, int>> inviVec, int& x, int& y);
};