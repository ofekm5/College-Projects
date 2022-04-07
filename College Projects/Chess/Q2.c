#include "Q2.h"

chessBoardCell** initBoard()/*a function that creates a chess board*/
{
    chessBoardCell** cb;
    int i, j;
    /*8 rows for chess board*/
    cb = (chessBoardCell**)malloc(sizeof(chessBoardCell*) * ROWS);
    checkAllocation(cb);
    for (i = 0;i < ROWS;i++)
    {
        /*each row has 8 columns*/
        cb[i] = (chessBoardCell*)malloc(sizeof(chessBoardCell) * COLS);
        checkAllocation(cb[i]);
        for (j = 0;j < COLS;j++)
        {
            //converting the ints to chars
            cb[i][j].val[0] = i + 'A';
            cb[i][j].val[1] = j + 1 + '0';

            cb[i][j].pos[0] =  cb[i][j].pos[1]= ' '; //space is needed for printing unchosen cells from list
        }

    }
    return cb;
}

void printChessBoard(chessBoardCell** cb)
{
    int i, j;
    printf("\n");
    printf("  ");
    for (i = 0;i < COLS;i++)
        printf("%4d ", i + 1);
    printf("\n   _");
    for (i = 0;i < COLS;i++)
        printf("_____");
    printf("\n");
    for (i = 0; i < ROWS; i++)
    {
        printf("%2c |", cb[i][0].val[0]);
        for (j = 0; j < COLS; j++)
        {
            printf("%c%c  |", cb[i][j].pos[0], cb[i][j].pos[1]);

        }
        printf("\n");
    }
    printf("   _");
    for (i = 0;i < COLS;i++)
        printf("_____");
}


void display(chessPosList* lst)/*a function that gets list lst,deletes all duplicates, and displays a chess board with the remaining data(not yet) */
{

    chessBoardCell** cb;
    chessPosList tmp;
    int N = 1, i, j;
    bool visited[ROWS][COLS];
    makeEmptyList(&tmp);

    /*we create a boolean matrix in the size of a chess board(8x8).each cell says if we visited already*/
    for (i = 0;i < ROWS;i++)
    {
        for (j = 0;j < COLS;j++)
        {
            visited[i][j] = false;
        }
    }
    cb = initBoard();

    chessPosCell* curr = lst->head;
    while (curr != NULL)
    {
        i = curr->position[0] - 'A';

        j = curr->position[1] - 1 - '0';

        /*if we havent visited, insert to the temp list, update N and update the chess board.*/
        if (visited[i][j] == false)
        {
            visited[i][j] = true;
            insertDataToEndList(&tmp, curr->position);
            if(N<10){
                cb[i][j].pos[1] = N + '0';
                cb[i][j].pos[0] = ' ';
            }
            else{
                cb[i][j].pos[0] = N/10 + '0';
                cb[i][j].pos[1] = N%10 + '0';
            }

            N++;
        }

        curr = curr->next;
    }

    //freeing the old list and replacing it with the new one
    freeList(lst);
    *lst = tmp;


    printChessBoard(cb);
    freeBoard(cb);
}


void makeEmptyList(chessPosList* lst)
{
    lst->head = NULL;
    lst->tail = NULL;
}


bool isEmptyList(chessPosList* lst)
{
    if (lst->head == NULL)
        return true;
    return false;
}


void insertDataToEndList(chessPosList* lst, chessPos data)
{
    chessPosCell* newTail;

    newTail = createNewListNode(data);

    insertNodeToEndList(lst, newTail);

    newTail->next = NULL;

}


chessPosCell* createNewListNode(chessPos data)
{
    chessPosCell* res;

    res = (chessPosCell*)malloc(sizeof(chessPosCell));

    checkAllocation(res);

    res->position[0] = data[0];
    res->position[1] = data[1];

    return res;

}


void insertNodeToEndList(chessPosList* lst, chessPosCell* node)
{
    if (isEmptyList(lst))
    {
        lst->head = node;
        lst->tail = node;
    }
    else
    {
        lst->tail->next = node;
        lst->tail = node;
    }
}



void freeList(chessPosList* lst)
{
    /*each time we free the previous and than one more time in the end for the final cell*/
    chessPosCell* curr = lst->head, * prev = lst->head;
    curr = curr->next;

    while (curr != NULL)
    {
        free(prev);

        prev = curr;

        curr = curr->next;
    }

    free(prev);
}


void freeBoard(chessBoardCell** cb)
{
    int i;
    for (i = 0;i < ROWS;i++)
    {
        free(cb[i]);
    }
    free(cb);
}

