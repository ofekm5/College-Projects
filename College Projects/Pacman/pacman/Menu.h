#pragma once
#include <iostream>
using namespace std;

class Menu
{
private:
	char choice='0';
	char level;
public:
	void presentMenu() const;
	void presentInstructionsAndKeys() const;
	void initMenu();
	char getChoice() { return this->choice; }
	char setLevel();
};
