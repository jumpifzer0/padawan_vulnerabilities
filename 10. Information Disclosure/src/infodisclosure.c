#include <stdio.h>
#include <windows.h>
#include <wincrypt.h>



int submit(char *buffer, int *data){
    int temp,temp2;
    int score = 1;
    for (int i = 0; i < 4; i++){
        temp = ((unsigned char)buffer[i*4+3] << 24) | ((unsigned char)buffer[i*4 + 2] << 16) | ((unsigned char)buffer[i*4 + 1] << 8) | (unsigned char)buffer[i*4 + 0];
        
        printf("these are the temp values %d,%d,%d",temp,temp2,data[i]);
        if (temp != data[i]){
            // return 0;
            score = 0;
        }
    }
    return score;

}







void main(){


    setbuf(stdout, NULL); // TODO: check doc
    setbuf(stdin, NULL); // TODO: check doc
    setbuf(stderr, NULL); // TODO: check doc



    HCRYPTPROV hProv;
    BYTE buffer[16]; // Example: generate 16 random bytes

    // Acquire a cryptographic provider context
    if (!CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT)) {
        printf("Error acquiring context: %lx\n", GetLastError());
        fflush(stdout);
        return;
    }

    // Generate secure random numbers
    if (!CryptGenRandom(hProv, sizeof(buffer), buffer)) {
        printf("Error generating random numbers: %lx\n", GetLastError());
        fflush(stdout);
        return;
    }

    int data[4] = {0,1,2,3}; // todo guess the 4 numbers 


    char option;
    int input_value;
    char input[100];
    int pos = 0;
    while (1){
        // menu, modify number see number
        
        printf("what would you like to do?\n");
        printf("1. View and modify number\n");
        printf("2. Submit number\n");
        fflush(stdout);
        if (fgets(input, sizeof(input), stdin) != NULL) {
            option = input[0];
        } else {
            // Error reading the input
            printf("Error reading input.\n");
            fflush(stdout);
        }
        switch (option){
            case '1':
              
                printf("what value would you like to view and modify?\n");
                fflush(stdout);
                // get integer here
                if (fgets(input, sizeof(input), stdin) != NULL) {
                    // Use sscanf to parse the integer from the input string
                    if (sscanf(input, "%d", &input_value) == 1) {
                        // Successfully parsed the integer
                        printf("You entered: %d\n", input_value);
                        fflush(stdout);
                    } else {
                        // Failed to parse the integer (input was not valid)
                        printf("Invalid input. Please enter a valid integer.\n");
                        fflush(stdout);
                        break;
                    }
                } else {
                    // Error reading the input
                    printf("Error reading input.\n");
                    fflush(stdout);
                    break;
                }
                printf("This is the value you are looking for: %d\n",*(data+input_value));
                fflush(stdout);
                if (input_value  >= 0 && input_value < 4){
                    // ask for input to modify
                    pos = input_value;
                    printf("what is the value you would like to input:\n");
                    fflush(stdout);
                    // if input is value then change
                     if (fgets(input, sizeof(input), stdin) != NULL) {
                    // Use sscanf to parse the integer from the input string
                        if (sscanf(input, "%d", &input_value) == 1) {
                            // Successfully parsed the integer
                            printf("You entered: %d\n", input_value);
                            fflush(stdout);
                            data[pos] = input_value;
                        } else {
                            // Failed to parse the integer (input was not valid)
                            printf("Invalid input. Please enter a valid integer.\n");
                            fflush(stdout);
                        }
                    } else {
                        // Error reading the input
                        printf("Error reading input.\n");
                        fflush(stdout);
                    }
                } else {
                    printf("you cannot change these values\n");
                    fflush(stdout);
                }
              fflush(stdout);
             
            break;
            case '2':
            printf("Here are your values: 1. %d 2. %d 3. %d 4. %d\n",data[0],data[1],data[2],data[3]);
            if (submit(buffer,data) == 1){
                printf("challenge solved!\n");
                
            } else{
                printf("incorrect values!\n");
            }
            exit(0);
            break;
            default:
                printf("invalid value\n");

        }
    }
}