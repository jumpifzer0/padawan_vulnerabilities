#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv){

    if (argc != 3){
        printf("Program is expecting 2 input arguments.\n");
        printf("E.g. simple_oobw.exe 5 AAAAAAAA\n");
        return 0;
    }
    
    unsigned int buf[32];
    unsigned int i = atoi(argv[1]);
    unsigned int j = atoi(argv[2]);

    buf[i] = j;

    printf("Value %s placed in buf[%s]", argv[2], argv[1]);

    // jz notes
    // One thing that can be considered would be to add a success function
    // concept is for the oobw to be that the user can
    //  1) Use the buf index ACID to control where in the stack does the user want to write to
    //  2) Use the buf content at the index to be 
    //      a) function value (since no ASLR), to call the success function
    //      b) another value in the stack, hence when over writing it can directly overwrite that value. 

    // Can also consider doing it in the heap instead

    return 0;
}