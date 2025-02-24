#include <stdio.h>
#include <stdlib.h>
#include <stdio.h>

unsigned int i = 0;
void function0(){
    printf("flag{otherintegerissue}\n");
    i++;
    if (i!= 3){
        exit(0);
    };
    return;
}

void function1(){
    i++;
    if (i!= 2){
        exit(0);
    };

    return;
}

void function2(){
    i++;
    if (i!= 1){
        exit(0);
 
    }
    return;
}

void main(){
    char input[5];
    unsigned char value; 
    void (*ptr)();
    
    unsigned int counter = 0;
    ptr = (void (*)())(char *)main;
    while(counter++ < 3){
        printf("Please input a value\n");
        fgets(input,sizeof(input),stdin);
        sscanf(input,"%d",&value);
        if (value < 0x8){break;}
        ptr =  (void (*)())((char *)ptr + (char) (value&0xFC)); 
        printf("main address:%X  new address:%X   offset value calculated:%d\n",main, ptr, value&0xFC);
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

