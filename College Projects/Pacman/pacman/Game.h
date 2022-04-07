#pragma once

#include "Board.h"
#include "gameObject.h"
#include <windows.h>
#include <conio.h>
#include <fstream>
#include "Menu.h"
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>

class Game {

private:

	int gameOver = 0, currLevel;//0-Game isn't over, 1-Game lost, 2-Game won
	const int ESC = 27;
	Board board;
	gameObject* objarr[6]; /* first cell is pacman's, second is fruit's and te rest are saved for ghosts */
	void updateStats();
	int legendX, legendY;
	int totalboardfiles = 0;
	vector <string> screen_files;//storing all .screen files names
	vector <pair<int, int>> inviVec;//vector of all the invisible paths

public:
	Game();

	void startGame();/*a method that presents the menu,
					 and if the user chooses to play the method initializes everything and starts the game*/

	void gamePlaying(int totalGhost, bool& playerWon, char ghostLevel);/*the game loop. runs until the game is over*/

	void pause();

	void checkObjects(int totalGhost);/* returns true if the game is over */

	void waitingforResponse() const;

	void readBoardFromFile(vector<string> screen_files, int& totalGhost, int& currfile, char mode, int lives);

	int findIndexOfName(vector <string> screen_files, string filename);

	void getScreenNames();

	void killEmAll(int& lives);

	void initGameObjVec();

};
