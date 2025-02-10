#include <stdlib.h>
#include <string.h>
#include <stdio.h>

struct special_struct {
    int var1;
    char *var2; 
};

void print_struct(struct special_struct *input_struct){
    printf("var1 : %d \n", input_struct->var1);
    printf("var2 : %s \n", input_struct->var2);
}

// FUNCTION to free the struct
// pass struct by reference
void free_struct(struct special_struct *input_struct){
    free(input_struct->var2);
    free(input_struct);
}

void print_options(){
    printf("print options loan and return");
}

int main(int argc, char **argv){
    // jz notes 
    // can make like a library(?) system that loan(malloc) and returns(free)
    
    int selection = 0;
    struct special_struct cart[8];


    // print options
    // get user input
    // do action
    // repeat until case 3
    while(selection != 10){

        print_options();

        scanf("%d", &selection);
        switch(selection){
            case 1:
                printf("1");
                break;
            case 2:
                printf("2");
            case 3:
                printf("exit");
                selection = 10;
            
        }
    }

    return 0;
}