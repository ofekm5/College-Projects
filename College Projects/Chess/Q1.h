#ifndef Q1_h
#define Q1_h
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


typedef char chessPos[2];

typedef struct _chessPosArray {
    unsigned int size;
    chessPos* positions;
}chessPosArray;


/* We changed the size from 8 to 4 in order to test ex.3 */
#define ROWS 5
#define COLS 5
chessPosArray*** validKnightMoves(void);
chessPosArray* calculateKnightArr(int x, int y);
bool isPosValid(int x, int y);
void insertAndConvert(chessPos* knightMoves, int* logsize, int x, int y);
void checkAllocation(void* check);
void freeKnightMovesArr(chessPosArray*** arr);
void checkAllocation(void* check);

#endif
