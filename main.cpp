#include <iostream>
#include <cstdlib>
#include <ctime>
#include "game.h"

using namespace std;


int main()
{
	//set the random seed
	srand(time(NULL));
	
	Game g;

	//get two inputs: size of the cave(wid and len)
	
	cout << "------------------------------------------------------" << endl;
	cout << "Please input a length size for the cave" << endl;
	int len = g.set_length_width();
	cout << "Please input a width size for the cave" << endl;
	int wid = g.set_length_width();

	//get the 3rd input --> debug mode or not

	bool debug = g.set_debug();
	cout << "------------------------------------------------------" << endl;

	//Play game
	g.play_game(wid, len, debug);


	return 0;
}
