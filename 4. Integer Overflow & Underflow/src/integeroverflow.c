#include <stdio.h>
#include <stdlib.h>


typedef struct {
    int health;
    int attack;
    int defense;
    char accuracy;

} Globin;




typedef struct {
 int health;
 int attack;
 int defense;
 int player_turn;
} Player;



void main(){
    // intialise player
    Player *player = (Player*)calloc(1,sizeof(Player));
    player->health = 11;
    player-> attack = 1;
    player->defense = 0;
    player->player_turn = 1;

    // initialise globin
    Globin *globin = (Globin*)calloc(1,sizeof(Globin));
    globin->health = 16;
    globin->attack = 5;
    globin->defense = 0;
    globin-> accuracy = 100;


    while (1){
        // things for the user to do
        printf("You are on a quest to find a path through the forest, you have met a globin and was given only 1 turn to defeat the globin:\n");
        printf("Globin stats: health: %d, attack: %d defense: %d accuracy:%d\n ", globin->health, globin->attack, globin->defense, globin-> accuracy);
        printf("Your stats: health: %d, attack: %d, defense: %d, player_turn_left: %d\n", player->health, player-> attack, player->defense, player->player_turn);
        printf("what action would you like to do?\n");
        printf("1. attack\n");
        printf("2. shield up\n");
        printf("3.skip a turn\n");
        printf("4. retreat\n");
        char health_input[100];
        int health = 0;
        char input[5];
        int action;
        fgets(input, sizeof(input),stdin);
        sscanf(input,"%d",&action);
        if (action > 4 ){
            printf("invalid value! Please input the value from the above options.\n");
            continue;
        }
        
        action = action & 0xF ;
        switch (action){
            case 1: // attack
                player->player_turn--;
                globin->health -= player-> attack;
                player->health -= globin->attack - player->defense;
                break;
            case 2: // shield up
                player->player_turn--;
                player->defense = 1;
                player->health -= globin->attack - player->defense;
                break;
            case 3: // skip a turn
                player->player_turn--;
                player->health -= globin->attack - player->defense;
                break;
            case 4: // retreat
                printf("quest failed!\n");
                exit(0);
            case 5: // change globins health
                printf("Welcome mod!\n");
                fgets(health_input, sizeof(health_input),stdin);
                sscanf(health_input,"%lu",&health); // here
                if (health < 5){
                    printf("health cannot be negative or health addition is too low!\n");
                    break;
                }
                globin->health = (15 + health) > 1 ? 15 + health:1 ;
                break;
            default:
                printf("invalid action!\n");
                break;
        }

        if (globin->health <= 0){
            printf("completed! flag{integeroverflow}\n");
            break;

        } else if (player->player_turn <= 0){
            printf("failed!\n");
            break;
        }
    }
}