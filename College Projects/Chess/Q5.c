#include "Q5.h"


void saveListToBinFile(char *file_name, chessPosList *pos_list){
    int i;
    short listsize;
    FILE *f1 = fopen(file_name, "wb");
    fileCheck(f1);
    BYTE* bitsarr;
    chessPosCell *curr=pos_list->head;
    
    
    //getting size of list and writing it in file
    listsize = getListSize(pos_list);
    fwrite(&listsize, sizeof(short), 1, f1);
    
    //allocating array of bytes
    bitsarr = (BYTE*)calloc(listsize, sizeof(BYTE));
    checkAllocation(bitsarr);
    
    //storing in each cell the according pos in the 6 msb
    for(i=0;i<listsize;i++){
        bitsarr[i] = storeOnePos(curr);
        curr = curr->next;
    }
    
    encode(bitsarr,&listsize);
    
    //writing to file each cell of bytes
    fwrite(bitsarr, sizeof(BYTE), listsize, f1);
    
    
    fclose(f1);
}


short getListSize(chessPosList *pos_list){
    chessPosCell *curr=pos_list->head;
    short listsize=0;
    
    while(curr!=NULL){
        listsize++;
        curr = curr->next;
    }
    
    return listsize;
}


BYTE storeOnePos(chessPosCell *curr){//converting and storing current position in 6 msb of returned byte
    BYTE msbmask,lsbmask,res;
    
    //extracting index from position
    if(curr->position[0] == 'A'){
        msbmask = 0;
    }
    else
        msbmask = (curr->position[0] - 'A')<<5;//shifting the msb in order to use OR operator accordingly
    
    lsbmask = (curr->position[1] -'0' - 1)<<2;//extracting index from positions
    
    res = msbmask | lsbmask;
     
    
    return res;
}


void encode(BYTE* bitsarr, short *listsize){//storing bits from next cell in current's unused bits
    int i=0,unusedbits, unusedbytes;
    BYTE mask;
    int freebits=2;
    short numofbytes=(*listsize);
    
    unusedbits = (*listsize)*2;//each cell has 2 unused bits
       
    unusedbytes = unusedbits/8;
    numofbytes-=unusedbytes;
    
    
    //for(i=0;i<(*listsize)-1;i++){
    while(i<numofbytes){
        mask = createMask(bitsarr[i+1], freebits);//creating a mask of N(num of freebits) msb from next cell
        bitsarr[i] |= mask;//adding relevent bits to current cell to occupy unused space
        
        bitsarr[i+1] = bitsarr[i+1]<<freebits;//shifting next cell because we "moved" its N msb to previous cell
        if(freebits==6){
            i++;
            moveByteToEnd(bitsarr,i,listsize);
            freebits = 2;
            //bitsarr[i] = bitsarr[i];
            
        }
        else{
            freebits+=2;
            i++;
        }
    }
    if(numofbytes!=(*listsize)){
        bitsarr = realloc(bitsarr, sizeof(BYTE)*numofbytes);
    }
    //reduceArr(&bitsarr, listsize);//getting rid of uncessary cells
}


void reduceArr(BYTE** bitsarr, short *listsize){ //making sure that 
    int unusedbits, unusedbytes;
    
    unusedbits = (*listsize)*2;//each cell has 2 unused bits
    
    unusedbytes = unusedbits/8;
    (*listsize)-=unusedbytes;
    
    if(unusedbytes!=0){
        *bitsarr = realloc(*bitsarr, sizeof(BYTE)*(*listsize));
    }
}


void moveByteToEnd(BYTE* bitsarr, int ind, short *listsize){
    int i;
    BYTE temp;
    
    for(i=ind;i<(*listsize)-1;i++){
        temp = bitsarr[i+1];
        bitsarr[i+1] = bitsarr[i];
        bitsarr[i] = temp;
    }
    
}


BYTE createMask(BYTE nxtcell, int freebits){
    BYTE mask=0;
    int i,y;
    
    if(freebits==0)
        return 0;
    
    //isolating N msb of the next cell
    for(i=0,y=7;i<freebits;i++,y--){
        mask |= 1 << y;
    }
    mask &= nxtcell;
    
    mask = mask >> (8-freebits); //making N msb of the next cell as the N lsb of curr cell
    
    return mask;
}


void fileCheck(FILE* check){
    if (check == NULL)
    {
        printf("file failure");
        exit(1);
    }
}
