#include "Q4.h"

chessPosList* findKnightPathCoveringAllBoard(pathTree *path_tree){
    chessPosList* lst;
    int currlevel=1;
    bool wantedlevel = false;
    
    lst = (chessPosList*)malloc(sizeof(chessPosList));
    checkAllocation(lst);
    
    makeEmptyList(lst);
    
    findKnightPathCoveringAllBoardRec(path_tree->root,currlevel,&wantedlevel,lst);

    if(isEmptyList(lst)){
        free(lst);
        return NULL;
    }
    else
        return lst;
}


void findKnightPathCoveringAllBoardRec(treeNode* root, int currlevel, bool* wantedlevel, chessPosList* lst){
    treeNodeListCell* curr = root->next_possible_positions;
    
    if(root==NULL){
        return;
    }
    else if(currlevel==(ROWS*COLS)){//if went through the entire board
        *wantedlevel = true;
        insertDataToEndList(lst,root->position);
    }
    else{
        while(curr != NULL){
            findKnightPathCoveringAllBoardRec(curr->node,currlevel+1,wantedlevel,lst);
            if(*wantedlevel==true){//if we ended up in a complete path in further recursive calls
                insertDataToStartList(lst,root->position);
                break;//the break is needed for inserting only the correct node in the current level
            }
            curr = curr->next;
        }
    }
}



void insertDataToStartList(chessPosList* lst,chessPos position){
    chessPosCell* newHead,*formerHead;

    newHead = createNewListNode(position);

    if (isEmptyList(lst)){
        lst->head = newHead;
        lst->tail = newHead;
    }
    else{
        formerHead = lst->head;
        lst->head = newHead;
        lst->head->next = formerHead;
    }
}
