#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv){

    if (argc != 2){
        printf("Please have an input.\n");
        return 0;
    }
        
    
    char *buf;
    buf = (char *)malloc(sizeof(char) * 256);
    strcpy(buf, argv[1]);

    // jz : Theory is that, the user input may overflow the malloc-ed allocation.
    // What we can consider to do, is to then 
    // do a If Else Check, if the pointer + size + 2(?) == certain value, then pass

    
    return 0;
}