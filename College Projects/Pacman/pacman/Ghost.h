#pragma once


#include <iostream>
#include "gameObject.h"
#include <math.h>
class Ghost :public gameObject {
private:
	char lastChar;
	char mode;//BEST, GOOD or NOVICE
	void moveStupid(Board& board, char c, std::vector <std::pair<int, int>> inviVec);
	void moveHalfStupid(Board& board, char c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy);
	void moveProfessor(Board& board, char c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy);
public:
	Ghost(int x, int y, int prevX, int prevY, int initX, int initY, int mode);
	void setMode(const int _mode) { mode = _mode; }
	void setLastChar(const char _lastChar);
	const char getLastChar()const;
	virtual void move(Board& board, char& c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy);
	int findBestRoute(Board& board, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy);
	float getDistance(int x1, int y1, int x2, int y2);
};
