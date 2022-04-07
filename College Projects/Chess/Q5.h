#ifndef Q5_h
#define Q5_h

#include "Q4.h"
/* NOTE: chessboard's initial square is [1,1], but validKnightMovesarr starts in [0,0]  */

typedef unsigned char BYTE;

void saveListToBinFile(char *file_name, chessPosList *pos_list);
short getListSize(chessPosList *pos_list);
void encode(BYTE* bitsarr, short *listsize);
BYTE createMask(BYTE nxtcell, int freebits);
BYTE storeOnePos(chessPosCell *curr);
void reduceArr(BYTE** bitsarr, short *listsize);
void fileCheck(FILE* check);
void moveByteToEnd(BYTE* bitsarr, int ind, short *listsize);

/*
Bits structure:
   16Bit(short) = total pos in list
   each pos is represented by 3x3 bits:
       msb = row num minus one (row num is a letter)
       lsb = col num minus one
       the rest are zeroes
*/



#endif /* Q5_h */
