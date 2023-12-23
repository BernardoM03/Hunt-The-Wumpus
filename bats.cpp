#include "bats.h"

#include <iostream>

using namespace std;

//Bats Implementation

Bats::Bats() {
	//cout << "Bats()" << endl;
}

int Bats::action() {
	cout << "------------------------------------------------------" << endl;
	cout << "You walk into a horde of bats." << endl;
	cout << "The encounter left you dizzy." << endl;
	cout << "------------------------------------------------------" << endl;
	return 5;
}

void Bats::percept() {
	cout << "You hear wings flapping." << endl;
}
