#include "Ghost.h"
#include "Board.h"

Ghost::Ghost(int x, int y, int prevX, int prevY, int initX, int initY, int mode) :gameObject(x, y, prevX, prevY, initX, initY)
{
    this->lastChar = '.';
    this->mode = mode;
}

void Ghost::setLastChar(const char _lastChar)
{
    this->lastChar = _lastChar;
}

const char Ghost::getLastChar()const
{
    return this->lastChar;
}

void Ghost::move(Board& board, char& c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy)
{
    /* recover former crumb */
    if (this->prevX != -1 && this->prevY != -1) {
        gotoxy(this->prevY, this->prevX);
    }
    else {/* if prev position was starting position */
        gotoxy(this->initY, this->initX);
    }
    std::cout << this->lastChar;

    /* Moving ghost */
    switch (this->mode)
    {
    case 'c':    // stupid (novice)
        this->moveStupid(board, c, inviVec);
        break;
    case 'b':    // half-stupid
        this->moveHalfStupid(board, c, inviVec, pacx, pacy);
        break;
    case 'a':    // "professor"
        this->moveProfessor(board, c, inviVec, pacx, pacy);
        break;
    }

    this->prevX = this->x;
    this->prevY = this->y;

    /* print the ghost and update the board */
    this->lastChar = board.getcurrcell(this->x, this->y);
    gotoxy(this->y, this->x);
    std::cout << "$";
}

void Ghost::moveStupid(Board& board, char c, std::vector <std::pair<int, int>> inviVec)
{
    //changing x.y randomly
    switch (c) {
    case 0:
        if (board.getcurrcell(this->x, this->y - 1) != '#' && !isInvisiblePath(inviVec, this->x, this->y - 1))//LEFT
            this->y--;
        else if (board.getcurrcell(this->x + 1, this->y) != '#' && !isInvisiblePath(inviVec, this->x + 1, this->y))//DOWN
            this->x++;
        break;
    case 1:
        if (board.getcurrcell(this->x - 1, this->y) != '#' && !isInvisiblePath(inviVec, this->x - 1, this->y))//UP
            this->x--;
        else if (board.getcurrcell(this->x, this->y + 1) != '#' && !isInvisiblePath(inviVec, this->x, this->y + 1))//RIGHT
            this->y++;
        break;
    case 2:
        if (board.getcurrcell(this->x + 1, this->y) != '#' && !isInvisiblePath(inviVec, this->x + 1, this->y))//DOWN
            this->x++;
        else if (board.getcurrcell(this->x, this->y + 1) != '#' && !isInvisiblePath(inviVec, this->x, this->y + 1))//RIGHT
            this->y++;
        break;
    case 3:
        if (board.getcurrcell(this->x, this->y + 1) != '#' && !isInvisiblePath(inviVec, this->x, this->y + 1))//RIGHT
            this->y++;
        else if (board.getcurrcell(this->x - 1, this->y) != '#' && !isInvisiblePath(inviVec, this->x - 1, this->y))//UP
            this->x--;
        break;
    }
}


void Ghost::moveHalfStupid(Board& board, char c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy)
{
    if (c != -1) {
        this->moveStupid(board, c, inviVec);
    }
    else {
        this->moveProfessor(board, c, inviVec, pacx, pacy);
    }
}


void Ghost::moveProfessor(Board& board, char c, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy) //deciding which move is best based on distance equation
{
    int bestroute = findBestRoute(board, inviVec, pacx, pacy);

    switch (bestroute) {
    case 0://left
        y--;
        break;
    case 1://right
        y++;
        break;
    case 2://up
        x--;
        break;
    case 3://down
        x++;
        break;
    }

}


int Ghost::findBestRoute(Board& board, std::vector <std::pair<int, int>> inviVec, int pacx, int pacy) {
    int minInd = -1, i, deltaX[4] = { 0,0,-1,1 }, deltaY[4] = { -1,1,0,0 };//deltas' indices: 0-left 1-right 2-down 3-up
    float distArr[4], minD = sqrt(pow(board.getHeight(), 2) + pow(board.getLength(), 2) * 1.0);//initializing minD with the largest distance on board


    for (i = 0; i < 4; i++)//calculating distances
        distArr[i] = getDistance(pacx, pacy, x + deltaX[i], y + deltaY[i]);

    for (i = 0; i < 4; i++) {
        if (minD > distArr[i] && board.getcurrcell(x + deltaX[i], y + deltaY[i]) != '#') {//if there is a possible valid move for the ghost that makes it closer to pacman
            minD = distArr[i];
            minInd = i;
        }
    }


    return minInd;
}


float Ghost::getDistance(int x1, int y1, int x2, int y2) {
    return sqrt(pow(x2 - x1, 2) + pow(y2 - y1, 2) * 1.0);
}
