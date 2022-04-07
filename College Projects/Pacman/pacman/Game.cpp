
#define _CRT_SECURE_NO_WARNINGS
#include "Game.h"

Game::Game()
{

	for (int i = 0; i < 6; i++) {
		objarr[i] = nullptr;
	}
	this->legendX = 0;
	this->legendY = 0;
	this->currLevel = 0;
}

void Game::getScreenNames()//retrieving screen files' names
{
	int pointAppears = 0;
	string path = ".";

	for (const auto& file : filesystem::directory_iterator(path)) {
		string pathstr = file.path().string();
		int i = pathstr.size() - 1, typeInd = 0;
		char* fileType = new char[20];
		strcpy(fileType, "e");

		while (pathstr[i] != '.') {//checking each file's postfix
			fileType[typeInd++] = pathstr[i];
			i--;
		}
		fileType[typeInd] = '\0';
		if (strcmp(fileType, "neercs") == 0)//written backwards because fileType initiallized backwards
			this->screen_files.push_back(file.path().string());
		if (fileType != nullptr)
			delete[] fileType;
	}
}


void Game::startGame() {
	int totalGhost = 0, fileInd = -1, i = 0;
	bool finishedBoards = false, playerWon;
	Menu m;
	char choice = 0, ghostLevel;
	string filename, fullFileName;
	int lives = 3;
	Pacman* temp = dynamic_cast<Pacman*>(objarr[0]);

	getScreenNames();

	do {
		m.initMenu();
		lives = 3;
		choice = m.getChoice();

		if (choice == '1')
		{
			currLevel = 0;
			totalGhost = 0;

			system("CLS");
			ghostLevel = m.setLevel(); //getting ghost difficulty
			system("CLS");
			do {
				totalGhost = 0;
				system("CLS");
				gameOver = 0;
				inviVec.clear();

				readBoardFromFile(screen_files, totalGhost, currLevel, ghostLevel, lives);

				gamePlaying(totalGhost, playerWon, ghostLevel);
				killEmAll(lives);
				if (gameOver == 1)
					break;
				currLevel++;
			} while (currLevel < screen_files.size());

			if (currLevel == screen_files.size())
			{
				cout << "you won" << endl;
			}
			currLevel = 1;//initialized for further use
		}
		else if (choice == '2')
		{
			currLevel = 2; //making current board as the last board in queue
			totalGhost = 0;
			gameOver = 0;
			system("CLS");
			ghostLevel = m.setLevel();
			do {
				fullFileName = ".\\";
				cout << "Enter specific file name" << endl;
				cin >> filename;
				fullFileName.append(filename);//Adding file prefix 
				fileInd = findIndexOfName(screen_files, fullFileName);
				if (fileInd == -1)
					cout << "There is no file with this name. Try again." << endl;
			} while (fileInd == -1);
			system("CLS");
			inviVec.clear();
			readBoardFromFile(screen_files, totalGhost, fileInd, ghostLevel, 3);
			gamePlaying(totalGhost, playerWon, ghostLevel);
			killEmAll(lives);
			if (board.getBreadcrumbs() == 0)
			{
				cout << "you won" << endl;
			}
			board.clearBoard();
		}
	} while (choice != '9');
	system("CLS");
	cout << "GOODBYE:)" << endl;
}

void Game::initGameObjVec()
{
	for (int i = 0; i < 6; i++)
	{
		objarr[i] = nullptr;
	}
}

void Game::readBoardFromFile(vector<string> screen_files, int& totalGhost, int& currfile, char mode, int lives)//translating the board in the file and storing it in local data objects
{
	int logicHeight = 0, logicWidth = 0, numberBreadcrumbs = 0, x = 0, y = 0;
	ifstream myFile(screen_files[currfile]);
	char currentChar;
	bool isfruitinserted = false;
	if (myFile.fail())
	{
		cout << "Error opening file!" << endl;
		exit(1);
	}

	while (!myFile.eof())
	{
		currentChar = myFile.get();

		if (currentChar == '#')			// walls
		{
			if (logicHeight == 0)//the first line determine the length of the board
				logicWidth++;
			this->board.setcurrcell(x, y, currentChar);
			y++;
		}
		else if (currentChar == '\n')
		{
			logicHeight++;
			x++;
			y = 0;
		}
		else if (currentChar == '$')	// ghost
		{
			objarr[2 + totalGhost] = new Ghost(x, y, -1, -1, x, y, mode);
			this->board.setcurrcell(x, y, '.');//the ghost is hovering over crumbs
			y++;
			totalGhost++;
		}
		else if (currentChar == '@')	//	pacman
		{
			objarr[0] = new Pacman(x, y, x, y, x, y, lives);
			this->board.setcurrcell(x, y, currentChar);
			y++;
		}
		else if (currentChar == '%')	// empty - no breadcrumb
		{
			y++;
		}
		else if (currentChar == ' ')	// breadcrumb
		{
			numberBreadcrumbs++;
			this->board.setcurrcell(x, y, '.');
			y++;
		}
		else if (currentChar == '&')	// legend place
		{
			/* initializing legend */
			this->legendX = x;
			this->legendY = y;
		}


	}

	board.setBreadcrumbs(numberBreadcrumbs);
	myFile.close();
	this->board.setLength(logicWidth);
	this->board.setHeight(logicHeight);
	for (int x = 0; x <= logicHeight; x++) {
		for (int y = 0; y <= logicWidth; y++) {
			if (!isfruitinserted)//inserting the fruit
			{
				if ((board.getcurrcell(x, y) == ' ' || board.getcurrcell(x, y) == '.') && (!((board.getcurrcell(x, y - 1) == '#' && board.getcurrcell(x, y + 1) == '#') || (board.getcurrcell(x + 1, y) == '#' && board.getcurrcell(x - 1, y) == '#'))))
				{
					objarr[1] = new Fruit(x, y, -1, -1, x, y);
					isfruitinserted = true;
				}
			}
			if (((y == 0 || y == logicWidth || y == logicWidth - 1) && ((board.getcurrcell(x, y) == ' ') || (board.getcurrcell(x, y) == '.') && board.getcurrcell(x - 1, y) == '#' && board.getcurrcell(x + 1, y) == '#')) ||
				((x == 0 || x == logicHeight - 1) && ((board.getcurrcell(x, y) == ' ') || (board.getcurrcell(x, y) == '.') && board.getcurrcell(x, y + 1) == '#' && board.getcurrcell(x, y - 1) == '#'))
				)//if curr cell is invisible path
			{
				inviVec.push_back(std::make_pair(x, y));
			}
		}
	}
	this->board.printBoard();
}


int Game::findIndexOfName(vector <string> screen_files, string filename) {
	for (int i = 0; i < screen_files.size(); i++) {
		if (screen_files[i] == filename)
			return i;
	}
	return -1;
}


void Game::gamePlaying(int totalGhost, bool& playerWon, char ghostLevel) {
	int i, d = 0, rep = 0, fruitRep = 0, fruitMove = 0, pacx, pacy;
	char c = 0, lastvalidchar = 0, ghostDir, fruitDisappear = 0;
	bool ghostMove = true;
	int fruitIter = 0, dointShowIter = 0;
	Fruit* localFruit = dynamic_cast<Fruit*>(objarr[1]);
	/*waiting for a valid key to be hit in the first time*/
	do {
		if (_kbhit())
			c = _getch();
	} while (c != 'a' && c != 'A' && c != 'd' && c != 'D' && c != 'w' && c != 'W' && c != 'x' && c != 'X' && c != 's' && c != 'S');

	while (gameOver == 0) {
		if (c != ESC) {
			updateStats();/* Presenting the score and lives on the screen */
			/*a valid key was pressed. updating the pacman moves*/
			if (c == 'a' || c == 'A' || c == 'd' || c == 'D' || c == 'w' || c == 'W' || c == 'x' || c == 'X' || c == 's' || c == 'S')
			{
				lastvalidchar = c;
				objarr[0]->move(this->board, c, inviVec);
			}
			else/*not a valid key pressed. moving according to the last valid move*/
			{
				objarr[0]->move(this->board, lastvalidchar, inviVec);
			}

			checkObjects(totalGhost);
			if (gameOver != 0)
				break;
			Sleep(100);
			if (_kbhit())
				c = _getch();

			if (ghostMove)/* moving the ghosts alternately(so that the speed will be half of pacman's speed)*/
			{
				if (ghostLevel == 'c') {//novice
					if (rep == 20) {
						rep = 0;
						if (d == 3)
							d = 0;
						else
							d++;
					}
					rep++;
				}
				else if (ghostLevel == 'b') {//half stupid
					if (rep < 20) {
						d = -1;
					}
					else if (rep >= 20 && rep <= 25) {
						if (d == 3 || d == -1)
							d = 0;
						else
							d++;

						if (rep == 25)
							rep = 0;
					}
					rep++;
				}
				else if (ghostLevel == 'a') {
					d = -1;
				}

				pacx = objarr[0]->getX();
				pacy = objarr[0]->getY();
				for (i = 0; i < totalGhost; i++) {
					if (d != -1) {
						ghostDir = (char)(d + i) % 4; //using different direction for each ghost
					}
					else
						ghostDir = (char)(d); //if current mode is professor

					objarr[2 + i]->move(board, ghostDir, inviVec, pacx, pacy);
				}
				ghostMove = false;
				checkObjects(totalGhost);
				if (gameOver != 0)
					break;
			}
			else
			{
				ghostMove = true;
			}

			if (fruitDisappear < 50) {//moving fruit, simillar to novice level in ghosts
				fruitMove++;
				if (fruitMove == 1) {
					if (fruitRep == 20) {//changing direction
						fruitRep = 0;
						if (localFruit->getFruitMovement() == 3)
							localFruit->setfruitMovement(0);
						else
							localFruit->setfruitMovement(localFruit->getFruitMovement() + 1);
					}
					fruitRep++;
					char temp = (char)localFruit->getFruitMovement();
					objarr[1]->move(this->board, temp, inviVec);
					fruitDisappear++;
					checkObjects(totalGhost);
					if (gameOver != 0)
						break;
				}
				else if (fruitMove == 4)
					fruitMove = 0;
			}
			else if (fruitDisappear == 50) {//fruit disappear
				fruitDisappear++;
				localFruit->setInvisible(true);
				gotoxy(localFruit->getY(), localFruit->getX());
				cout << localFruit->getlastChar();
			}
			else if (fruitDisappear < 100)//counting until fruit reappear
				fruitDisappear++;
			else {//fruit reappear
				localFruit->setInvisible(false);
				gotoxy(localFruit->getY(), localFruit->getX());
				cout << localFruit->getPointValue();
				fruitDisappear = 0;
			}
		}
		else {/* ESC was pressed. saving the last move of pacman */
			pause();
			c = lastvalidchar;
		}
	}
}


void Game::updateStats() {
	Pacman* temp = dynamic_cast<Pacman*>(objarr[0]);
	gotoxy(this->legendY, this->legendX);
	cout << "Lives: " << temp->getLives() << endl;
	gotoxy(this->legendY, this->legendX + 1);
	cout << "Points: " << temp->getPoints() << endl;
}


void Game::waitingforResponse()const
{
	char ch = -1;
	while (ch == -1)
	{
		system("PAUSE");
		ch = getchar();
	}
}


void Game::checkObjects(int totalGhost) {/* checking whether pac/ghost ate the fruit or if ghost ate pac */
	int pacx = this->objarr[0]->getX(), pacy = this->objarr[0]->getY(), fX = this->objarr[1]->getX(), fY = this->objarr[1]->getY();
	bool pacmanEaten = false;
	Pacman* localPac = dynamic_cast<Pacman*>(objarr[0]);
	Fruit* localFruit = dynamic_cast<Fruit*>(objarr[1]);

	this->gameOver = 0;

	for (int i = 2; i <= 5; i++) {
		int gX = -1, gY = -1;//Initiallize x.y of ghost with non existing x.y 
		if (objarr[i] != nullptr) {
			gX = this->objarr[i]->getX();
			gY = this->objarr[i]->getY();
		}

		if (pacx == gX && pacy == gY) {//If the ghost ate pacman
			localPac->setLives(localPac->getLives() - 1);
			if (localPac->getLives() != 0) { /* If the game is not over, respawn */
				objarr[0]->respawn();
				gotoxy(gY, gX);
				cout << "@";
			}
			else
			{
				this->gameOver = 1;
				system("CLS");
				cout << "You Lost!" << endl;
				waitingforResponse();
				board.clearBoard();
			}
			break;
		}

		if (gX == fX && gY == fY) {//If the ghost ate the fruit
			localFruit->setPointValue();
			localFruit->setfruitMovement(rand() % 3 + 1);//changing initial direction of fruit
			objarr[1]->respawn();
		}
	}


	if (pacmanEaten == false) {
		if (pacx == fX && pacy == fY && localFruit->getInvisible() == false) {//If pacman ate the fruit
			localPac->setPoints(localPac->getPoints() + localFruit->getPointValue());
			localFruit->setPointValue();
			localFruit->setfruitMovement(rand() % 3 + 1); //changing initial direction of fruit
			objarr[1]->respawn();

		}
		else if (board.getBreadcrumbs() == 0) { /* win. numberOfBreadCrumbs = total breadcrumbs in board*/
			system("CLS");
			this->gameOver = 2;
			if (currLevel < screen_files.size() - 1)
				waitingforResponse();
		}
	}
}


void Game::pause()
{
	char c = 0;
	gotoxy(this->board.getLength() + 1, 0);
	cout << "GAME PAUSED" << endl;

	do {/*running until ESC was pressed again*/
		if (_kbhit())
			c = _getch();
	} while (c != ESC);

	gotoxy(this->board.getLength() + 1, 0);
	cout << "           " << endl;
}

void Game::killEmAll(int& lives)//destorying every pawn in the game which be later revived as a new one
{
	Pacman* temp = dynamic_cast<Pacman*>(objarr[0]);

	lives = temp->getLives();
	for (int i = 0; i < 6; i++)
	{
		if (objarr[i])
			delete objarr[i];
		objarr[i] = nullptr;
	}
}
