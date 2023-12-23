#include "stalactites.h"

#include <iostream>

using namespace std;

//Stalactites Implementation

Stalactites::Stalactites() {
	//cout << "Stalactites()" << endl;
}

int Stalactites::action() {
	cout << "------------------------------------------------------" << endl;
	cout << "A large pillar of stone falls from the ceiling!" << endl;
	int num = rand() % 2;
	if (num == 0) {
		cout << "You dodge out of the way!" << endl;
		cout << "------------------------------------------------------" << endl;
		return 0;
	} else {
		cout << "The stalactite falls on top of you!" << endl;
		cout << "------------------------------------------------------" << endl;
		return 1;
	}

}

void Stalactites::percept() {
	cout << "You hear water dripping" << endl;
}
