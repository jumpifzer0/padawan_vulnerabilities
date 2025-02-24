#include <stdio.h>

unsigned int i = 0;

void vulnfn(){
    char input[100];
    fflush(stdout);
    i++;
    if (i >= 3){
        printf("flag{linearstackbufferoverflow!}");
        fflush(stdout);
        return;
    }
    
    gets(input);
    printf("received input!\n");
    fflush(stdout);
    return;
}



void main(){
    vulnfn();

}