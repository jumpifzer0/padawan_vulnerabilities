#include <stdlib.h>
#include <string.h>
#include <stdio.h>


void func1(int input_val){
    int i = input_val;
    printf("This is the i = %d \n", i);
}


int func2(int input_val){
    int j;
    if(j == 123456789){
        return 1;
    }    
    else{
        return 0;
    }
}


int main(int argc, char **argv){

    if (argc != 2){
        printf("Program is expecting 1 input argument.\n");
        printf("E.g. simple_uda.exe AAAA\n");
        return 0;
    }
    
    unsigned int user_input = atoi(argv[1]);

    func1(user_input);

    int outcome = func2(user_input);

    if(outcome)
        printf("Success\n");

    return 0;
}

// jz notes 
// can consider adding other red herrings if want to make more comprehensive