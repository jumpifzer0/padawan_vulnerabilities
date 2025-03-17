#include <iostream>

#include "eevee.h"

using namespace std;


// function to keep printing options
void print_main_options(){
    cout << 
R"(***********************
(1) Show Eevee Info
(2) Select Other Evolutions
(3) Battle
(4) Exit
***********************)" << endl;

    cout << "Please provide a selection : ";
}


void print_eevee_info(eevee * selectedeevee){
    cout << "[*] Here are the stats for the eevee that you have selected." << endl;
    cout << "HP  : " << selectedeevee->hp << endl;
    cout << "ATK : " << selectedeevee->atk << endl;
    cout << "DEF : " << selectedeevee->def << endl;
}


void print_eeveelutions(){
    cout << "[1] Flareon" << endl;
    cout << "[2] Jolteon" << endl;
    cout << "[3] Vaporeon" << endl;
    cout << "[4] Glaceon" << endl;
    cout << "[5] Leafeon" << endl;
    cout << "[6] Espeon" << endl;
    cout << "[7] Sylveon" << endl;
    cout << "Please provide a selection : ";
}


// function to select the eevee based on the eeveelution selected
eevee * returnEeveelution(int selection){

    eevee * selectedEevee;

    switch(selection){
        case 1:
            selectedEevee = new Flareon();
            cout << "Flareon Selected" << endl;
            break;
        case 2:
            selectedEevee = new Jolteon();
            cout << "Jolteon Selected" << endl;
            break;
        case 3:
            selectedEevee = new Vaporeon();
            cout << "Vaporeon Selected" << endl;
            break;
        case 4:
            selectedEevee = new Glaceon();
            cout << "Glaceon Selected" << endl;
            break;
        case 5:
            selectedEevee = new Leafeon();
            cout << "Leafeon Selected" << endl;
            break;
        case 6:
            selectedEevee = new Espeon();
            cout << "Espeon Selected" << endl;
            break;
        case 7:
            selectedEevee = new Umbreon();
            cout << "Sylveon Selected" << endl;
            break;
    }
    return selectedEevee;
}


int battle(int eevee_atk){
    enemy * opponentmon = new enemy();

    if(eevee_atk >= opponentmon->hp){
        cout << "[*] Success!" << endl;
        return 1;
    }
    else{
        cout << "[-] Your pokemon has fainted. Try again." << endl;
        return 0;
    }

}


int main(){

    int game_ongoing = 1;

    // will be in the heap.
    eevee * currentEevee = new eevee();

    int eevee_selection = 0;

    while(game_ongoing){

        int user_option = 0;
        int success_condition = 0;

        print_main_options();
        cin >> user_option;

        switch(user_option){
            case 1:
                print_eevee_info(currentEevee);
                break;
            case 2:
                print_eeveelutions();
                cin >> eevee_selection;
                currentEevee = returnEeveelution(eevee_selection);
                break;
            case 3:
                if (eevee_selection == 0){
                    currentEevee->tackle();
                    success_condition = battle(currentEevee->atk);
                }
                else if (eevee_selection == 1){
                    Flareon *flareon = static_cast<Flareon*>(currentEevee);
                    flareon->flamethrower();
                    success_condition = battle(flareon->atk);
                }
                else if (eevee_selection == 2){
                    Jolteon *jolteon = static_cast<Jolteon*>(currentEevee);
                    jolteon->thunderbolt();
                    success_condition = battle(jolteon->atk);
                }
                else if (eevee_selection == 3){
                    Vaporeon *vaporeon = static_cast<Vaporeon*>(currentEevee);
                    vaporeon->hydro_pump();
                    success_condition = battle(vaporeon->atk);
                }
                else if (eevee_selection == 4){
                    Glaceon *glaceon = static_cast<Glaceon*>(currentEevee);
                    glaceon->blizzard();
                    success_condition = battle(glaceon->atk);
                }
                else if (eevee_selection == 5){
                    Leafeon *leafeon = static_cast<Leafeon*>(currentEevee);
                    leafeon->solar_blade();
                    success_condition = battle(leafeon->atk);
                }
                else if (eevee_selection == 6){
                    Espeon *espeon = static_cast<Espeon*>(currentEevee);
                    espeon->future_sight();
                    success_condition = battle(espeon->atk);
                }
                else if (eevee_selection == 7){
                    Sylveon *sylveon = static_cast<Sylveon*>(currentEevee);
                    sylveon->alluring_voice();
                    success_condition = battle(sylveon->atk);
                }
                break;
            case 4:
                cout << "[*] Exiting the game.";
                game_ongoing = 0;
                break;
            default:
                cout << "[*] Please Provide a proper selection" << endl;
        }

        if(success_condition){
            game_ongoing = 0;
        }

    }

    return 0;
}
