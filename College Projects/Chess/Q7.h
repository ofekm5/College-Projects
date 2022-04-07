#ifndef Q7_H
#define Q7_H

#include "Q1.h"
#include "Q2.h"
#include "Q3.h"
#include "Q4.h"
#include "Q5.h"
#include "Q6.h"

//a function that checks if the choice of the user is valid
bool checkChoice(int choice);

//a function that checks if the position is valid
bool checkValidPos(chessPos position);

//a function that gets a position from the user and returns the position
chessPos* choice1(void);

//a function that gets a file name from the user(without .bin) and creates the file name for question 5
char* choice4(void);

//a function that gets a file name from the user and executes question 6
void choice5(void);

//a function that creates  a file name from the user
char* createFileName(void);

void menu(void);


#endif /* Q7_h */


