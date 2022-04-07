#ifndef Q2_h
#define Q2_h

#include "Q1.h"


typedef struct _chessPosCell{

    chessPos position;

    struct _chessPosCell* next;

}chessPosCell;

typedef struct _chessPosList {

    chessPosCell* head;

    chessPosCell* tail;
}chessPosList;

typedef struct boardArea {

    chessPos val;
    char pos[2];

}chessBoardCell;

chessPosArray*** validKnightMoves(void);
chessPosArray* calculateKnightArr(int x, int y);
bool isPosValid(int x, int y);
void insertAndConvert(chessPos* knightMoves, int* logsize, int x, int y);
void checkAllocation(void* check);
void freeKnightMovesArr(chessPosArray*** arr);
void display(chessPosList* lst);
void deleteAllOccurances(chessPosCell* pos);
void makeEmptyList(chessPosList* lst);
bool isEmptyList(chessPosList* lst);
void insertDataToEndList(chessPosList* lst, chessPos data);
chessPosCell* createNewListNode(chessPos data);
void insertNodeToEndList(chessPosList* lst, chessPosCell* node);
void freeList(chessPosList* lst);
void printChessBoard(chessBoardCell** cb);
chessBoardCell** initBoard(void);
void freeBoard(chessBoardCell** cb);





#endif /* Q2_h */
