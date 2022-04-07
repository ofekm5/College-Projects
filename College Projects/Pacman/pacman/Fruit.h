#pragma once
#include "gameObject.h"
#include <stdlib.h>     
#include <time.h> 
class Fruit :public gameObject
{
private:
	int pointValue;
	char lastChar;
	bool invisible;
	int fruitMovement;
public:
	Fruit(int x, int y, int prevX, int prevY, int initX, int initY);
	int getPointValue() const;
	void setPointValue();
	virtual void move(Board& board, char& c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy);
	//a function that sets the fruit to be invisible
	void setInvisible(bool _invisible) { this->invisible = _invisible; }
	bool getInvisible() const{ return this->invisible; };
	char getlastChar() const{ return lastChar; }
	int getFruitMovement() const{ return fruitMovement; }
	void setfruitMovement(int _fruitMovement) {this->fruitMovement = _fruitMovement;}
};