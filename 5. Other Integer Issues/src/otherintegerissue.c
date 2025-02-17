#include <stdio.h>
#include <stdlib.h>
// the address is 32bit

#include <stdio.h>

unsigned int i = 0;
void function0(){
    // add some padding so that it will cause integer overflow
    printf("flag{otherintegerissue}\n");
    i++;
    if (i!= 3){
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
    };
    return;
}

void function1(){
    i++;
    if (i!= 2){
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
    };

    return;
}

void function2(){
    i++;
    if (i!= 1){
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
        exit(0);
    }
    return;
}

void main(){
    
    // get the user input
    char input[5];
    unsigned char value; // todo: try to see if it works with unsigned int
    void (*ptr)();
    
    unsigned int counter = 0;
    ptr = (void (*)())(char *)main;
    while(counter++ < 3){
        // add the fuc
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d",&value);
        if (value < 0x8){break;}
        ptr =  (void (*)())((char *)ptr + (char) (value&0xFC)); // signed char
        printf("%X  %X   %d\n",main, ptr, value&0xFC);
        ptr();
    }
    if (value < 0x8){
        printf("value is too small!");
    }
}

void function3(){

}

void funciton4(){

}

// 1460
// 1498
// 14c4
// 14f0