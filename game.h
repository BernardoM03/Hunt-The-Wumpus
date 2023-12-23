#ifndef GAME_H
#define GAME_H 

#include <vector>
#include <iostream> 
#include "room.h"

using namespace std;

//Game interface 
class Game
{
private:	
	//declare a 2D vector of Room objects:

	//other member variables:
	int length; 			//length of the board
	int width;  			//width of the board
	int num_arrows; 		//keep track of number of errors remaining
	bool debug_view;		//debug mode or not
	//position trackers
	int adv_start_l;
	int adv_start_w;
	int adv_l;
	int adv_w;
	int evt_l;
	int evt_w;
	int wump_l;
	int wump_w; 

	bool wumpus_dead; // check_wun (win)
	bool gold_found; //check_win (win)
	bool player_dead; //check_win (loss)
	int dizziness; //bat dizziness counter
	int armor_durability; // armor durability coumnter
	int turn_counter; // keeps track of the turns

	vector<vector<Room>> caveMatrix;

public:
	//suggested functions:
	Game();
	~Game();
	
	void play_game(int, int, bool);

	void set_up(int l, int w);

	void display_game() const;

	void check_percepts();
	void check_encounter();

	bool check_win() const;
	void wumpus_move();
	void fire_arrow();

	void move_up(int &pos);
	void move_down(int &pos);
	void move_left(int &pos);
	void move_right(int &pos);
	void move(char);
	void wumpus_wander();

	void randomize(int &pos1, int &pos2);
	void check_wumpus_dead(int arrow_l, int arrow_w, int arrow_range);

	char get_dir();
	char get_input();

	char error_check_move();
	char error_check_arrow();

	int set_length_width();
	bool set_debug();

	void hidden_event_place();
};
#endif
