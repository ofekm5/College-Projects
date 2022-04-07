#ifndef Q6_h
#define Q6_h

#include "Q5.h"

bool isValidRoute(chessPosList* pos_list);
bool isLinkValid(chessPos curr, chessPos nxt);
bool isRouteCoversAllBoard(chessPosList* pos_list);
chessPosList unfoldData(FILE* f);
void decode(BYTE* receivedbytes, chessPosList* lst, int totalbytes, int n);
BYTE createOppMask(BYTE nxtcell, int freebits);
int checkAndDisplayPathFromFile(char* file_name);
void storeInList(BYTE* receivedbytes, chessPosList* lst, int* totalnodes);


#endif /* Q6_h */
