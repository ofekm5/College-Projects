#include "Q7.h"


void menu()
{
    char* fileName = NULL;
    bool exit = false, pathTreeCreated = false, listCreated = false;
    chessPosList* lst = NULL;
    chessPos* position = NULL;
    int choice;
    pathTree tree;
    while (!exit) {
        printf("1. Enter a knight's starting position\n\n2. Create all possible knight paths\n\n");
        printf("3. Find a knight path covering all board\n\n4. Save knight path covering all board to file\n\n");
        printf("5. Load and display path from file\n\n6. Exit\n");
        scanf("%d", &choice);
        getchar();
        if (!checkChoice(choice))
            printf("Wrong choice. Enter again\n\n");
        switch (choice)
        {
        case 6://exit(first we check if there is a position,list or tree created.if so,than we free each)
            if (position != NULL)
                free(position);
            if (pathTreeCreated) {
                pathTreeCreated = false;
                freeTree(tree);
            }
            if (listCreated) {
                listCreated = false;
                if (lst != NULL)
                    freeList(lst);
            }
            exit = true;
            printf("Goodbye!\n");
            break;

        case 1://getting a position(first we check if there is a position,list or tree created.if so,than we free each)
            if (pathTreeCreated) {
                pathTreeCreated = false;
                freeTree(tree);
            }
            if (listCreated) {
                listCreated = false;
                if (lst != NULL)
                    freeList(lst);
            }

            position = choice1();
            break;

        case 2://creating path tree of all possible positions.if position isn't entered-user needs to enter position first.
            if (position == NULL) {

                printf("You haven't entered a position yet.\n\n");
              
                break;
            }
            else {

                tree = findAllPossibleKnightPaths(position);
                pathTreeCreated = true;
                printf("path of all possible positions created\n\n");
            }

            break;

        case 3:/*creating a path tree covering all the board.if position isn't entered-user needs to enter position first.
            if path tree wasn't created yet,we create the path tree according to the position*/
            if (position == NULL) {

                printf("You haven't entered a position yet.\n\n");
              
                break;
            }
            else {
                if (pathTreeCreated == false) {
                    tree = findAllPossibleKnightPaths(position);
                    pathTreeCreated = true;
                }

                lst = findKnightPathCoveringAllBoard(&tree);
                listCreated = true;
                if (lst == NULL || isEmptyList(lst)) {
                    printf("Path tree covering all board not found\n\n");
                }
                else {
                    printf("Path tree covering all board created\n\n");
                }
            }
            break;
        case 4://writing list of position to file
            if (position == NULL) {
                printf("You haven't entered a position yet.\n\n");
               
                break;
            }
            else {
                //if path tree covering all board exists we create the file.if not-we let the user know
                if (!listCreated && !pathTreeCreated) {
                    tree = findAllPossibleKnightPaths(position);
                    lst = findKnightPathCoveringAllBoard(&tree);
                    pathTreeCreated = true;
                    listCreated = true;
                }
                else if (pathTreeCreated) {
                    lst = findKnightPathCoveringAllBoard(&tree);
                    listCreated = true;
                }
                if (lst != NULL && !isEmptyList(lst)) {
                    fileName = choice4();
                    saveListToBinFile(fileName, lst);
                    printf("List saved to file succesfully.\n\n");
                }
                else {
                    printf("Path tree covering all board not found\n\n");
                }

            }
            break;
        case 5://reading a file name and doing question 6
            choice5();
            break;
        }
    }
}


bool checkChoice(int choice) {
    if (!(choice >= 1 && choice <= 6))
        return false;
    return true;
}

bool checkValidPos(chessPos position) {
    if (!(position[0] >= 'A' && position[0] <= 'H'))
        return false;
    if (!(position[1] >= '1' && position[1] <= '8'))
        return false;
    return true;
}

chessPos* choice1() {

    char left, right;
    chessPos* position;
    position = (chessPos*)malloc(sizeof(chessPos));
    checkAllocation(position);
    //enter position on board
    printf("Please enter a position:\n");
    scanf("%c%c", &left, &right);
    getchar();
    (*position)[0] = left;
    (*position)[1] = right;
    while (!(checkValidPos(*position))) {
        printf("Not a valid position. Enter again.\n");
        scanf("%c%c", &left, &right);
        getchar();
        (*position)[0] = left;
        (*position)[1] = right;
    }
    return position;
}

char* choice4()
{
   
    char* fileName = createFileName();
    
    return fileName;
}


void choice5() {
    int status;
    char* fileName;
    fileName = createFileName();

    status = checkAndDisplayPathFromFile(fileName);

    if (status == -1)
        printf("File doesn't exist\n\n");
    else if (status == 1)
        printf("Knight's path is not legal\n\n");
    else if (status == 3)
        printf("\n\nPath is not covering all the board\n\n");
    else
        printf("\n\nPath covering all the board\n\n");

}

char* createFileName() {
    printf("\nPlease enter file name(ending with .bin).\n");
    int logSize = 0, physSize = 1;
    char c;
    char* fileName = (char*)malloc(physSize * sizeof(char));
    checkAllocation(fileName);
    c = getchar();
    while (c != '\n')
    {
        if (logSize == physSize)
        {
            physSize *= 2;
            fileName = (char*)realloc(fileName, physSize * sizeof(char));
            checkAllocation(fileName);
        }
        fileName[logSize++] = c;
        c = getchar();
    }
    fileName = (char*)realloc(fileName, (logSize + 1) * sizeof(char));
    checkAllocation(fileName);
    fileName[logSize] = '\0';


    return fileName;
}



