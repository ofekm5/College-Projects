#include "Q3.h"

pathTree findAllPossibleKnightPaths(chessPos* startingPosition){
    chessPosArray*** validKnightMovesarr;
    validKnightMovesarr = validKnightMoves();
    bool chessPosVisited[8][8]={false}; /* 2D boolean array to mark visited squares */
    pathTree res;
        
    res.root = findAllPossibleKnightPathsRec(*startingPosition,chessPosVisited,validKnightMovesarr);
        
    freeKnightMovesArr(validKnightMovesarr);
    return res;
}


treeNode* findAllPossibleKnightPathsRec(chessPos startingPosition,bool visited[][8],chessPosArray*** validKnightMovesarr){
    chessPos *availchildren;
    treeNodeListCell* curr=NULL;
    chessPosArray* validMoves;
    treeNode* res;
    int i,numoffreesquares;
    
    if(strcmp(startingPosition,"")==0){/* If we ended up in an empty square */
        return NULL;
    }
    else{
        visited[startingPosition[0] - 'A'][startingPosition[1] - '0'-1] = true; //mark the cell of current square as visited
        
        validMoves = validKnightMovesarr[startingPosition[0] - 'A'][startingPosition[1] - '0'-1];//filtering current position's possible moves
        
        numoffreesquares = getNumofFreesquares(validMoves,startingPosition,visited,&availchildren);//calculating how many free squares are available
        
        //creating a single tree node
        res = createNewTreeNode(startingPosition);

        if(numoffreesquares!=0){
            curr = res->next_possible_positions;
            for(i=0;i<numoffreesquares;i++){
                curr->node = findAllPossibleKnightPathsRec(availchildren[i],visited,validKnightMovesarr);//recursing through all the children
                if(i!=numoffreesquares-1){//avoid create unecessary list for the last child
                    curr->next = (treeNodeListCell*)calloc(1,sizeof(treeNodeListCell));
                    checkAllocation(curr->next);
                }
                curr = curr->next;
            }
        }
        else{//if current square does not have any squares to go to, insert an empty list of children
            free(res->next_possible_positions);
            res->next_possible_positions=NULL;
        }
        visited[startingPosition[0] - 'A'][startingPosition[1] - '0'-1] = false;//mark the cell of current square as not visited because current recursive call finished
    }

    return res;
}


treeNode* createNewTreeNode(chessPos position){
    treeNode* node = (treeNode*)malloc(sizeof(treeNode));
    checkAllocation(node);
    
    node->position[0] = position[0];
    node->position[1] = position[1];
    node->next_possible_positions = (treeNodeListCell*)calloc(1,sizeof(treeNodeListCell));//we are using calloc in order to avoid unexpected behavior
    checkAllocation(node->next_possible_positions);
    
    return node;
}


int getNumofFreesquares(chessPosArray* validMoves, chessPos startingPosition, bool visited[][8],chessPos **availchildren){
    chessPos* tmp=NULL;
    int freesquares=0,i,k,j,writeind=0;
    
    //calculating the num of free squares
    for(i=0;i<validMoves->size;i++){
        //square to array index conversions
        k = validMoves->positions[i][0] - 'A';
        j = validMoves->positions[i][1]- '0' - 1;
        if(visited[k][j]==false){
            freesquares++;
        }
    }
    
    //if there are some free squares, insert them in tmp
    if(freesquares!=0){
        tmp=(chessPos*)malloc(freesquares*sizeof(chessPos));
        checkAllocation(tmp);
        for(i=0;i<validMoves->size;i++){
            //square-to-array index conversions
            k=validMoves->positions[i][0] - 'A';
            j=validMoves->positions[i][1]- '0' - 1;
            if(visited[k][j]==false){
                tmp[writeind][0] = validMoves->positions[i][0];
                tmp[writeind][1] = validMoves->positions[i][1];
                writeind++;
            }
        }
    }
    
    *availchildren=tmp;
    return freesquares;
}


void freeTree(pathTree tr){
    freeTreeRec(tr.root);
}


void freeTreeRec(treeNode* root){
    treeNodeListCell* curr;
    
    //if the root is a leaf, free it. else,free its children in a recursive way and then free the list's pointer and the root
    if(root->next_possible_positions==NULL)
        free(root);
    else{
        curr = root->next_possible_positions;
        while(curr != NULL){
            freeTreeRec(curr->node);
            curr = curr->next;
        }
        free(root->next_possible_positions);
        free(root);
    }
}
