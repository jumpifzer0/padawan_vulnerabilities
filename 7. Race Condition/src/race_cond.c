#include <stdio.h>
#include <windows.h>

#define SLEEPTIMEINPUT 1000
#define SLEEPTIMETASK 100
typedef struct {
    int remaining_amount;
    int amt_spent;
} Task;

// ask for input function
void InputFunction(int *taskend,Task **tasks,int *starting_tokens){
    char input[50];
    int intInput = 0;
    while(1){
        // check for the number of tasks that has been placed
        if (*taskend >= 10){
            printf("max order reached!\n");
            break;
        }
        if (*starting_tokens <= 0){
            printf("no more tokens! exiting...\n");
            break;
        }
        // ask for input
        printf("how many items would you like to buy?\n");
        fgets(input, sizeof(input), stdin);
        if (sscanf(input, "%d", &intInput) == 1) {
        // Successfully read an integer
            printf("You entered: %d\n", intInput);
            if (intInput <= 0){
                printf("items cannot have a negative number.\n");
            }
            if (intInput <= *starting_tokens ){
                // printf("taskkend %d\n",*taskend);
                Task *newTask = (Task *)malloc(sizeof(Task));
                newTask->amt_spent = intInput;
                tasks[(*taskend)++] = newTask;
                // printf("taskend %d\n",*taskend);
            }
            else {
                printf("invalid value! Current tokens left: %d\n",*starting_tokens);
            }
    } else {
            // Handle invalid input
            printf("Invalid input. Please enter a valid integer.\n");
    }       
    // sleep for a period of time
    Sleep(SLEEPTIMEINPUT);

    }

}

DWORD WINAPI ThreadFunction(LPVOID lpParam){
    int *taskend = ((int **)lpParam)[0];
    Task **tasks = ((Task ***)lpParam)[1];
    int *starting_tokens = ((int **)lpParam)[2];

    // Call InputFunction with the extracted parameters
    InputFunction(taskend, tasks, starting_tokens);
    return 0;  // Return the thread exit code
}

void main(){
    unsigned int taskstart = 0;
    unsigned int taskend = 0;
    Task *tasks[10];
    int starting_tokens = 100;
    int items_bought = 0;
    // create a thread to ask for input
    void *params[3] = {&taskend,&tasks,&starting_tokens};
    HANDLE userInputThread = CreateThread(
        NULL,
        0,
        ThreadFunction,
        params,
        0,
        NULL
    );
    
    // get items 
    while(1){
        while(taskstart  < taskend){
            // get a new task
            Task *curr_task = tasks[taskstart++];
            for (int i = 0; i < curr_task->amt_spent; i++){
                // simulate preparing task and subtract tokens
                starting_tokens = max(starting_tokens--,0);
                items_bought++;
                Sleep(SLEEPTIMETASK);
            }
            printf("bought %d items\n", curr_task->amt_spent);
        }
        if (taskstart >= 10){
            break;
        }else if (items_bought >= 500){
            break;
        }else if (taskstart  >= taskend) {
            DWORD dwExitCode = 0;
            GetExitCodeThread(userInputThread, &dwExitCode);

        if (dwExitCode != STILL_ACTIVE) {
            // If the thread has finished (not active), exit the loop
            printf("Input has terminated, exiting program.\n");
            break;
        }
        }
    }
    if (items_bought >= 500){
            printf("task complete successfully!\n");
    }
    printf("Total items bought: %d\n",items_bought);

    
}

// 100
// 89
// 78
// 67
// 56
// 45
// 34
// 23
// 12
// 1
