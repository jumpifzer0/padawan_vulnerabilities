#include <iostream>
#include <windows.h>
#include <string>
#include <vector>

#include "eevee.h"

using namespace std;

//------------------------------------
// constructor for eevee
eevee::eevee() {
    hp = 55;
    atk = 55;
    def = 55;
};

void eevee::tackle(){
    cout << "Eevee uses tackle." << endl;
}
//------------------------------------

enemy::enemy(){
    hp = 200;
    atk = 300;
    def = 0;
}


//------------------------------------
// constructor for flareon
Flareon::Flareon() : eevee() {
    hp = 65;
    atk = 130;
    def = 60; 
}

void Flareon::flamethrower(){
    cout << "Flareon uses flamethrower." << endl;
}
//------------------------------------

//------------------------------------
// constructor for jolteon
Jolteon::Jolteon() : eevee(){
    hp = 65;
    atk = 65;
    def = 60;
}

void Jolteon::thunderbolt(){
    cout << "Jolteon uses thunderbolt." << endl;
}
//------------------------------------

//------------------------------------
// constructor for vaporeon
Vaporeon::Vaporeon() : eevee(){
    hp = 130;
    atk = 65;
    def = 60;
}

void Vaporeon::hydro_pump(){
    cout << "Vaporeon uses hydro pump." << endl;
}
//------------------------------------

//------------------------------------
// constructor for glaceon
Glaceon::Glaceon() : eevee(){
    hp = 65;
    atk = 60;
    def = 110;
}

void Glaceon::blizzard(){
    cout << "Glaceon uses blizzard." << endl;
}
//------------------------------------

//------------------------------------
// constructor for leafeon
Leafeon::Leafeon() : eevee(){
    hp = 65;
    atk = 110;
    def = 130;
}

void Leafeon::solar_blade(){
    cout << "Leafeon use solar blade" << endl;
}
//------------------------------------

//------------------------------------
// constructor for espeon
Espeon::Espeon() : eevee(){
    hp = 65;
    atk = 65;
    def = 60;
}

void Espeon::future_sight(){
    cout << "Espeon uses future sight." << endl;
}
//------------------------------------

//------------------------------------
// constructor for umbreon
Umbreon::Umbreon() : eevee(){
    hp = 95;
    atk = 200;
    def = 110;
}

void Umbreon::dark_pulse(){
    cout << "Umbreon uses dark pulse" << endl;
}
//------------------------------------

//------------------------------------
// constructor for sylveon
Sylveon::Sylveon() : eevee(){
    hp = 95;
    atk = 65;
    def = 65;
}

void Sylveon::alluring_voice(){
    cout << "Sylveon uses alluring voice" << endl;
}
//------------------------------------



