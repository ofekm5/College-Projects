#ifndef Q3_h
#define Q3_h

#include "Q1.h"
#include "Q2.h"


typedef struct _treeNode treeNode;
typedef struct _treeNodeListCell treeNodeListCell;

typedef struct _treeNode{
    chessPos position;
    treeNodeListCell* next_possible_positions;
}treeNode;


typedef struct _treeNodeListCell {
    treeNode* node;
    struct _treeNodeListCell* next;
}treeNodeListCell;


typedef struct _pathTree {
    treeNode* root;
}pathTree;


pathTree findAllPossibleKnightPaths(chessPos* startingPosition);
void createNewTree(treeNode* root,chessPos* startingPosition, chessPosArray*** possiblemoves);
treeNode* createNewTreeNode(chessPos position);
treeNodeListCell* createtreenodelistcell(chessPosArray *cellpossiblemoves);
void createNewTreeRec(treeNode* root,chessPos* startingPosition, chessPosArray*** knightpossiblemoves);
treeNode* findAllPossibleKnightPathsRec(chessPos startingPosition,bool visited[][8],chessPosArray*** validKnightMovesarr);
int getNumofFreesquares(chessPosArray* validMoves, chessPos startingPosition, bool visited[][8],chessPos **availchildren);
void freeTree(pathTree tr);
void freeTreeRec(treeNode* root);
int findHowmanychildren(treeNode* root);

#endif /* Q3_h */
