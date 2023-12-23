#include "wumpus.h"

#include <iostream>

using namespace std;

//Wumpus Implementation

Wumpus::Wumpus() : dead(false) {
	//cout << "Wumpus()" << endl;
}

int Wumpus::action() {
	cout << "------------------------------------------------------" << endl;
	cout << "You unsuspectingly walk before the maw of the Wumpus." << endl;
	cout << "------------------------------------------------------" << endl;
	return 1;
}

void Wumpus::percept() {
	cout << "You smell a terrible stench" << endl;
}

void Wumpus::set_dead(bool death) {
	dead = death;
}

bool Wumpus::get_dead() {
	return dead;
}
