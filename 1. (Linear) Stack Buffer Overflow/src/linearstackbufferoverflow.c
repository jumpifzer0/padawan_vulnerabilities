#include <stdio.h>



void vulnfn(char a, char b, char c, char d){
    // ask for the attributes over here
    char input[100];
    gets(input);
    // if it is the correct attributes then is good
    if (a != 0 && b != 0 && c!= 0 && b!= 0){
        printf("flag{linearstackbufferoverflow!}");
    }
    // else 
    return;
}




void main(){
    // call a function

    char a = 0;
    char b = 0;
    char c = 0;
    char d = 0;
    vulnfn(a,b,c,d);

}