#include <stdio.h>

unsigned int i = 0;

// void vulnfn(char a, char b, char c, char d){
//     // ask for the attributes over here
//     printf("reached here!\n");
//     printf("%d,%d,%d,%d\n",a,b,c,d);
//     fflush(stdout);
//     // if it is the correct attributes then is good
//     if (a != 0 && b != 0 && c!= 0 && b!= 0){
//         printf("flag{linearstackbufferoverflow!}");
//         fflush(stdout);
//         return;
//     }
//     // else 
//     char input[100];
//     gets(input);
//     printf("received input!\n");
//     fflush(stdout);
//     return;
// }

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
    // call a function

    // char a = 0;
    // char b = 0;
    // char c = 0;
    // char d = 0;
    // vulnfn(a,b,c,d);
    vulnfn();

}