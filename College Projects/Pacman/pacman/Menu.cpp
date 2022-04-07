#include "Menu.h"

//a function that creates the menu with all it's options
void Menu::presentMenu() const {
	cout << "Enter your choice:" << endl;
	cout << "(1): Start a new game." << endl;
	cout << "(2): Start a new game from file." << endl;
	cout << "(8): View instructions." << endl;
	cout << "(9): Exit." << endl;
}


void Menu::presentInstructionsAndKeys() const {
	system("CLS");
	cout << "Guide Pacman around the maze and eat all the little white dots whilst avoiding those nasty ghosts." << endl;
	cout << "KEYS:\nLEFT-A\nRIGHT-D\nDOWN-X\nUP-W\nSTAY-S" << endl;
}

//a function that handles the user input in the menu
void Menu::initMenu() {
	bool validChoice = false;
	while (!validChoice)/*9=exit*/
	{
		this->presentMenu();
		cin >> this->choice;
		if (this->choice != '1' && this->choice != '2' && this->choice != '8'&&this->choice!='9') {
			cout << "\nWrong choice. Enter again." << endl;
			continue;
		}
		else if (this->choice == '8') {
			presentInstructionsAndKeys();
			continue;
		}
		else if (choice == '1' || choice == '9' || choice == '2') {
			validChoice = true;
		}

	}
}

//a function that asks the user an input(ghost level)and returns the answer
char Menu::setLevel()
{
	cout << "choose level:\na. BEST\nb. GOOD\nc. NOVICE" << endl;
	cin >> this->level;
	while (this->level != 'a' && this->level != 'b' && this->level != 'c')
	{
		cout << "incorrect input. enter again" << endl;
		cin >> this->level;
	}
	return this->level;
}

