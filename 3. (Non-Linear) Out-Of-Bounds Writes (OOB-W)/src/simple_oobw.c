#include <stdlib.h>
#include <string.h>
#include <stdio.h>

int main(int argc, char **argv){

    if (argc != 3){
        printf("Program is expecting 2 input arguments.\n");
        printf("E.g. simple_oobw.exe 5 AAAAAAAA\n");
        return 0;
    }

    unsigned int ans = 11;
    unsigned int buf[32] = {0} ;
    unsigned int i = atoi(argv[1]);
    unsigned int j = atoi(argv[2]);

    buf[i] = j;

    printf("Value %s placed in buf[%s] \n", argv[2], argv[1]);

    if(ans == 1337){
        printf("Success!");
    }

    return 0;
}