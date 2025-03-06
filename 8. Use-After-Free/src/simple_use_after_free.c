#include <stdlib.h>
#include <string.h>
#include <stdio.h>


struct special_struct {
    int var1;
    char *var2; 
};


void print_struct(struct special_struct *input_struct){
    printf("[Book Info] \n");
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
    printf("===============\n");
    printf("[Options] \n"
           " [1] Show Loaned Book \n"
           " [2] Loan Book \n"
           " [3] Return Book \n"
           " [4] Give Feed Back \n"
           " [5] Exit \n"
    );
    printf("===============\n");
}

// jz notes 
// possible case to cause use-after-free
// loan book -> return book -> give feed back -> print book

// can consider, if want to make it easily exploitable, change one of the variables to a address pointer. Then user can exploit using address.
int main(int argc, char **argv){
        
    int selection = 0;
    struct special_struct* loanedBook;

    while(selection != 10){

        print_options();
        printf("Please input the value that you would like to do\n");
        scanf("%d", &selection);

        // This is needed to clear the buffer, so that \n is removed for fgets to work.
        // flushes stdin
        while(getchar() != '\n');

        switch(selection){
            case 1:
                print_struct(loanedBook);
                break;
            case 2:
                loanedBook = malloc(sizeof(struct special_struct));
                loanedBook->var2 = malloc(256);

                printf("What is var1 : ");
                scanf("%d", &loanedBook->var1);

                // This is needed to clear the buffer, so that fgets can work.
                while(getchar() != '\n');

                printf("What is var2 : ");
                fgets(loanedBook->var2, 256, stdin);

                printf("Book Loaned \n");
                break;
            case 3:
                free_struct(loanedBook);
                break;
            case 4:
                char *feedback = malloc(256);
                printf("Please Provide your feedback below \n");
                fgets(feedback, 256, stdin);
                break;
            case 5:
                printf("Exit");
                selection = 10;
            
        }
    }

    return 0;
}