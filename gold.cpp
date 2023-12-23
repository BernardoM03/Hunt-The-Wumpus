#include "gold.h"

#include <iostream>

using namespace std;

//Gold Implementation

Gold::Gold() {
	//cout << "Gold()" << endl;
}

int Gold::action() {
	cout << "------------------------------------------------------" << endl;
	cout << "You have found the Gold!" << endl;
	cout << "You place it within your backpack." << endl;
	cout << "------------------------------------------------------" << endl;
	return true;
}

void Gold::percept() {
	cout << "You see a glimmer nearby." << endl;
}