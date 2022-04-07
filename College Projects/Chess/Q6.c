#include "Q6.h"

int checkAndDisplayPathFromFile(char* file_name) {
    chessPosList pos_list;
    FILE* f;
    int status;
    bool fileExists = true;
    f = fopen(file_name, "rb");

    if (f == NULL) {
        status = -1;
        fileExists = false;
    }
    else {
        pos_list = unfoldData(f);//transforming the stream from file to a list

        if (!isValidRoute(&pos_list))
            status = 1;
        else {
            display(&pos_list);
            if (isRouteCoversAllBoard(&pos_list))
                status = 2;
            else
                status = 3;
        }

        freeList(&pos_list);
    }
    if (fileExists)
        fclose(f);
    return status;
}


chessPosList unfoldData(FILE* f) {
    int totalbytes;
    chessPosList lst;
    BYTE* receivedbytes;
    short n;

    makeEmptyList(&lst);

    fread(&n, sizeof(short), 1, f);//reading total squares

    //calculating how many bytes we will receive;

    if ((n * 6) % 8 == 0)
        totalbytes = ((n * 6) / 8);
    else
        totalbytes = ((n * 6) / 8) + 1;

    receivedbytes = (BYTE*)malloc(sizeof(BYTE) * totalbytes);//receivedbytes = array of encrypted bytes from stream

    //reading encoded bytes
    fread(receivedbytes, sizeof(BYTE), totalbytes, f);

    decode(receivedbytes, &lst, totalbytes, n);

    free(receivedbytes);
    return lst;
}


void decode(BYTE* receivedbytes, chessPosList* lst, int totalbytes, int n) {//decode the encrypted bytes to list of squares
    int i, totalnodes = n;

    for (i = 0;i < totalbytes;i += 3) {
        storeInList(receivedbytes + i, lst, &totalnodes);
    }

}


void storeInList(BYTE* receivedbytes, chessPosList* lst, int* totalnodes) {
    BYTE currvalue, mask;
    int currcell = 0, usefulbitsfromprev = 0;
    chessPos currpos;

    while (usefulbitsfromprev != -1 && (*totalnodes) != 0) {

        //filtering the received byte into the actual position in bits(3 msb=letter,3 next bits=number)
        if (usefulbitsfromprev == -2) {//there are 2 useless msb in byte
            currvalue = receivedbytes[currcell] << 2;
        }
        else if (usefulbitsfromprev != 0) {
            currvalue = receivedbytes[currcell] >> usefulbitsfromprev;
            mask = createOppMask(receivedbytes[currcell - 1], usefulbitsfromprev);
            currvalue |= mask;
        }
        else
            currvalue = receivedbytes[currcell];

        //transforming the indexes into chars
        if (((currvalue & 0xE0) >> 3) == 0)
            currpos[0] = 'A';//beacuse indexing method[A=0]
        else
            currpos[0] = ((currvalue & 0xE0) >> 5) + 'A';

        currpos[1] = ((currvalue & 0x1C) >> 2) + 1 + '0';

        insertDataToEndList(lst, currpos);
        (*totalnodes)--;


        //increasing accordingly as we move between bytes
        if (usefulbitsfromprev == 4) {
            usefulbitsfromprev = -2;
        }
        else if (usefulbitsfromprev == -2) {
            usefulbitsfromprev = -1;
            currcell++;

        }
        else {
            currcell++;
            usefulbitsfromprev += 2;
        }
    }


}


BYTE createOppMask(BYTE prvcell, int freebits) {//simillar mask creation like in Q5 but with opposite shifting, "taking" n lsb of prvcell
    BYTE mask = 0;
    int i;


    //isolating N lsb of the previous cell
    for (i = 0;i < freebits;i++) {
        mask |= 1 << i;
    }
    mask &= prvcell;

    mask = mask << (8 - freebits); //making N lsb of the prev cell as the N msb of curr cell

    return mask;
}


bool isValidRoute(chessPosList* pos_list) {
    chessPosCell* curr = pos_list->head;

    while (curr->next != NULL) {
        if (!isLinkValid(curr->position, curr->next->position))//if the conncetion between two squares is not valid
            return false;
        curr = curr->next;
    }

    return true;//if we covered all the route without finding a problem
}


bool isLinkValid(chessPos curr, chessPos nxt) {

    int currL = curr[0] - 'A', nxtL = nxt[0] - 'A', currR = curr[1] - '0' - 1, nxtR = nxt[1] - '0' - 1;

    //If the difference between squares is non of the valid options, return false
    if (!((nxtL - 1 == currL && nxtR + 2 == currR) || (nxtL - 2 == currL && nxtR + 1 == currR) || (nxtL - 1 == currL && nxtR - 2 == currR) || (nxtL + 1 == currL && nxtR - 2 == currR) || (nxtL + 2 == currL && nxtR - 1 == currR) || (nxtL + 2 == currL && nxtR + 1 == currR) || (nxtL + 1 == currL && nxtR + 2 == currR) || (nxtL - 2 == currL && nxtR - 1 == currR))) {
        return false;
    }
    return true;

}


bool isRouteCoversAllBoard(chessPosList* pos_list) {
    chessPosCell* curr = pos_list->head;
    int totalsquares = 0;

    //counting how many nodes are in list
    while (curr != NULL) {
        totalsquares++;
        curr = curr->next;
    }

    if (ROWS * COLS == totalsquares)//because we removed already squares that appear more than once
        return true;
    else
        return false;
}
