#include "armor.h"

#include <iostream>

using namespace std;

Armor::Armor() {
    //cout << "Gold()" << endl;
}

int Armor::action() {
    cout << "------------------------------------------------------" << endl;
    cout << "You have found the Legendary Armor of Anti-Wumpness" << endl;
    cout << "You equip the armor and embrace the strength" << endl;
    cout << "------------------------------------------------------" << endl;
    return 2;
}

void Armor::percept() {
    cout << "You feel an immense power." << endl;
}