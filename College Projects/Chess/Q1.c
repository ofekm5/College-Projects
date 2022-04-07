#include "Q1.h"

chessPosArray*** validKnightMoves() {
    chessPosArray*** arr;
    int i, y;

    //allocating a ROWS cell array
    arr = (chessPosArray***)malloc(sizeof(chessPosArray**) * ROWS);
    checkAllocation(arr);

    //allocating a ROWS cell array inside every cell to create 2D array
    for (i = 0;i < ROWS;i++) {
        arr[i] = (chessPosArray**)malloc(sizeof(chessPosArray*) * COLS);
        checkAllocation(arr[i]);
    }


    for (i = 0;i < ROWS;i++) {
        for (y = 0;y < COLS;y++) {
            arr[i][y] = calculateKnightArr(i + 1, y + 1);/* y+1 because intial array value is zero */
        }
    }


    return arr;
}


chessPosArray* calculateKnightArr(int x, int y) {/* returns an array of possible knight moves */
    chessPosArray* knightMoves;
    int logsize = 0;

    /* initializing*/
    knightMoves = (chessPosArray*)malloc(sizeof(chessPosArray));
    checkAllocation(knightMoves);
    knightMoves->positions = (chessPos*)malloc(8 * sizeof(chessPos));/* 8-max possible moves */
    checkAllocation(knightMoves->positions);
    knightMoves->size = 0;

    /* checking validity of every possible cell. if valid, meaning inside the board, insert it in knightMoves->positions */
    if (isPosValid(x-1,y+2)) {
        insertAndConvert(knightMoves->positions, &logsize, x-1,y+2);
    }
    if (isPosValid(x-2,y+1)){
        insertAndConvert(knightMoves->positions, &logsize, x-2,y+1);
    }
    if (isPosValid(x-1,y-2)) {
        insertAndConvert(knightMoves->positions, &logsize, x-1,y-2);
    }
    if (isPosValid(x+1,y-2)) {
        insertAndConvert(knightMoves->positions, &logsize, x+1,y-2);
    }
    if (isPosValid(x+2,y-1)) {
        insertAndConvert(knightMoves->positions, &logsize, x+2,y-1);
    }
    if (isPosValid(x+2,y+1)) {
        insertAndConvert(knightMoves->positions, &logsize, x+2,y+1);
    }
    if (isPosValid(x+1,y+2)) {
        insertAndConvert(knightMoves->positions, &logsize, x+1,y+2);
    }
    if (isPosValid(x-2,y-1)) {
        insertAndConvert(knightMoves->positions, &logsize, x-2,y-1);
    }

    if (logsize != 8) {/* if a shrink is needed */
        knightMoves->positions = (chessPos*)realloc(knightMoves->positions, logsize*sizeof(chessPos));
        checkAllocation(knightMoves->positions);
    }

    knightMoves->size = logsize;

    return knightMoves;
}


bool isPosValid(int x, int y) { /* checks if current cell is located on board */
    if (x >= 1 && x <= ROWS && y >= 1 && y <= COLS)
        return true;
    else
        return false;
}


void insertAndConvert(chessPos arr[], int* logsize, int x, int y) {/* converts the cell to valid chess cell and stores it */

    arr[*logsize][0] = x - 1 + 'A'; /* minus one in order to normalize zero to A */
    arr[*logsize][1] = y + '0';

    (*logsize)++;//increasing for further use
}


void freeKnightMovesArr(chessPosArray*** arr) {
    int i, y;

    for (i = 0;i < ROWS;i++) {
        for (y = 0;y < COLS;y++) {
            free(arr[i][y]->positions);
            free(arr[i][y]);
        }
        free(arr[i]);
    }
    free(arr);
}


void checkAllocation(void* ptr)
{
    if (ptr == NULL)
    {
        printf("allocation failed");
        exit(1);
    }
}
