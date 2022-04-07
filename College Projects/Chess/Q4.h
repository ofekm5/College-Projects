#ifndef Q4_h
#define Q4_h

#include "Q3.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree *path_tree);
chessPosList* convertTreeToList(pathTree tr);
void convertTreeToListRec(treeNode* root,chessPosList* lst);
void findKnightPathCoveringAllBoardRec(treeNode* root,int currlevel, bool* wantedlevel, chessPosList* lst);
void insertDataToStartList(chessPosList* lst,chessPos position);


#endif /* Q4_h */
