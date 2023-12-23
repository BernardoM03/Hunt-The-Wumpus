#include "game.h"
#include "gold.h"
#include "stalactites.h"
#include "bats.h"
#include "wumpus.h"

#include <time.h>
#include <iostream>

using namespace std;

//Game Implementation

Game::Game() {
	//Game constructor
	//Your code here:
}

Game::~Game(){
	//Game destructor
	//Your code here:
}

void Game::randomize(int &pos1, int &pos2) {
	do {
		pos1 = rand() % this->length;
		pos2 = rand() % this->width;
	} while (caveMatrix[pos1][pos2].get_hasEvent() || pos1 == adv_l && pos2 == adv_w);
}

void Game::play_game(int w, int l, bool d){

	this->debug_view = d;
	this->turn_counter = 0;
	Game::set_up(w, l);

	char input, arrow_input;

	while (Game::check_win() == false){
		this->turn_counter++;
		//display options
		if (this->debug_view == true){
			cout << endl;
			cout << "death: " << player_dead << endl;
			cout << "gold: " << gold_found << endl;
			cout << "dizzy: " << dizziness << endl;
			cout << "durability: " << armor_durability << endl;
			cout << "Start: " << adv_start_l << ", " << adv_start_w << endl;
			cout << "Current: " << adv_l << ", " << adv_w << endl;
			cout << "Wumpus: " << wump_l << ", " << wump_w << endl;
		}
		//print game board
		Game::display_game();
		//display percerts around player's location
		Game::check_percepts();
		//Player move...
		//1. get input
		input = Game::get_input();
		//2. move player
		Game::move(input);
		//The wumpus moves to a new location
		Game::wumpus_wander();
		//may or may not encounter events
		Game::check_encounter();
		//hidden event gets placed down
		Game::hidden_event_place();
	}
	return;
}

void Game::set_up(int l, int w){
	//set up the game
	this->length = l;
	this->width = w;
	this->num_arrows = 3;
	srand(time(NULL)); // seed time as random

	//resize 2D vector of room objects
	this->caveMatrix.resize(this->length);
	for (int i = 0; i < this->length; ++i){
		this->caveMatrix[i].resize(this->width);
	}
	//events
	//wumpus
	randomize(this->wump_l, this->wump_w);
	caveMatrix[this->wump_l][this->wump_w].set_encounter('w');
	//gold
	randomize(this->evt_l, this->evt_w);
	caveMatrix[this->evt_l][this->evt_w].set_encounter('g');
	//armor
	randomize(this->evt_l, this->evt_w);
	caveMatrix[this->evt_l][this->evt_w].set_encounter('a');
	//bats
	randomize(this->evt_l, this->evt_w);
	caveMatrix[this->evt_l][this->evt_w].set_encounter('b');
	randomize(this->evt_l, this->evt_w);
	caveMatrix[this->evt_l][this->evt_w].set_encounter('b');
	//stalactites
	randomize(this->evt_l, this->evt_w);
	caveMatrix[this->evt_l][this->evt_w].set_encounter('s');
	randomize(this->evt_l, this->evt_w);
	caveMatrix[this->evt_l][this->evt_w].set_encounter('s');	

	//adventurer
	randomize(this->adv_start_l, this->adv_start_w);
	this->adv_l = this->adv_start_l;
	this->adv_w = this->adv_start_w;

}

void Game::hidden_event_place(){
	if (turn_counter % 5 == 0) {
		randomize(this->evt_l, this->evt_w);
		caveMatrix[this->evt_l][this->evt_w].set_encounter('h');
	}
}

void Game::check_encounter(){

	if(caveMatrix[this->adv_l][this->adv_w].get_hasEvent()) {
		switch(caveMatrix[this->adv_l][this->adv_w].get_event()) {

			case 'w':
				this->player_dead = caveMatrix[this->adv_l][this->adv_w].get_encounter()->action();
				break;

			case 'g':
				this->gold_found = caveMatrix[this->adv_l][this->adv_w].get_encounter()->action();
				caveMatrix[this->adv_l][this->adv_w].set_encounter(' ');
					break;

			case 's':
				this->player_dead = caveMatrix[this->adv_l][this->adv_w].get_encounter()->action();
				caveMatrix[this->adv_l][this->adv_w].set_encounter(' ');
				break;

			case 'b':
				this->dizziness = caveMatrix[this->adv_l][this->adv_w].get_encounter()->action();
				caveMatrix[this->adv_l][this->adv_w].set_encounter(' ');
				break;

			case 'a':
				this->armor_durability = caveMatrix[this->adv_l][this->adv_w].get_encounter()->action();
				caveMatrix[this->adv_l][this->adv_w].set_encounter(' ');
				break;
		}
		if (armor_durability > 0 && player_dead == true) {
			cout << "The power of the Armor of Anti-Wumpness leaves you unscratched!" << endl;
			this->player_dead =  false;
			armor_durability--;
		}
	}
}

void Game::check_percepts(){
	cout << "------------------------------------------------------" << endl;
	cout << "PERCEPTS" << endl;
	if (this->adv_l - 1 >= 0){
		if(caveMatrix[this->adv_l - 1][this->adv_w].get_hasEvent()) {
			caveMatrix[this->adv_l - 1][this->adv_w].get_encounter()->percept();
		}
	}

	if (this->adv_l + 1 < this->length){
		if(caveMatrix[this->adv_l + 1][this->adv_w].get_hasEvent()) {
			caveMatrix[this->adv_l + 1][this->adv_w].get_encounter()->percept();
		}
	}

	if (adv_w - 1 >= 0){
		if(caveMatrix[this->adv_l][this->adv_w - 1].get_hasEvent()) {
			caveMatrix[this->adv_l][this->adv_w - 1].get_encounter()->percept();
		}
	}

	if (adv_w + 1 < this->width){
		if(caveMatrix[this->adv_l][this->adv_w + 1].get_hasEvent()) {
			caveMatrix[this->adv_l][this->adv_w + 1].get_encounter()->percept();
		}
	}
	cout << "------------------------------------------------------" << endl << endl;
}

//Note: you need to modify this function
void Game::display_game() const{
	cout << endl << endl;
	cout << "Arrows remaining: " << this->num_arrows << endl;

	for (int i = 0; i < this->length; ++i) {
		//cout << line << endl;
		for (int j = 0; j < this->width; ++j) {
			if (i != adv_l || j != adv_w){
				if (caveMatrix[i][j].get_hasEvent() == false || this->debug_view == false){
					cout << "[   ] ";
				}
				else {
					cout << "[ " <<caveMatrix[i][j].get_event() << " ] ";
				}
			}
			else {
				if (caveMatrix[i][j].get_hasEvent() == false || this->debug_view == false){
					cout << "[ * ] ";
				}
				else {
				cout << "[*" <<caveMatrix[i][j].get_event() << " ] ";
				}			
			}
		}
		cout << endl << endl;
	}
}

bool Game::check_win() const{
	
	if (this->player_dead == true){
		cout << endl << "--------------------------------------" << endl;
		cout << "You have died a gruesome death in the Wumpus's Cave..." << endl;
		cout << "--------------------------------------" << endl;
		return true;
	}

	if (this->gold_found == true && this->adv_l == this->adv_start_l && this->adv_w == this->adv_start_w) {
		cout << endl << "--------------------------------------" << endl;
		cout << "You have found the gold and escaped!" << endl;
		cout << "--------------------------------------" << endl;
		return true;
	}

	if (this->wumpus_dead == true) {
		cout << endl << "--------------------------------------" << endl;
		cout << "You have killed the Wumpus!" << endl;
		cout << "--------------------------------------" << endl;
		return true;
	}

	return false;
}

void Game::move_up(int &pos) {
	if (pos - 1 < 0){
		cout << "You hit the wall of the cave..." << endl;
	} 
	
	else if (caveMatrix[this->adv_l - 1][this->adv_w].get_event() == 'h'){
		cout << "You have hit a hidden wall..." << endl;
	}

	else {
		pos--;
	}
	return;

}

void Game::move_down(int &pos) {

	if (pos + 1 >= this->length){
		cout << "You hit the wall of the cave..." << endl;
	}
	
	else if (caveMatrix[this->adv_l + 1][this->adv_w].get_event() == 'h'){
		cout << "You have hit a hidden wall..." << endl;
	}

	else {
		pos++;
	}
	return;
}

void Game::move_left(int &pos) {

	if (pos - 1 < 0){
		cout << "You hit the wall of the cave..." << endl;
	}
	else if (caveMatrix[this->adv_l][this->adv_w - 1].get_event() == 'h'){
		cout << "You have hit a hidden wall..." << endl;
		cout << caveMatrix[this->adv_l][this->width - 1].get_event() << endl;
	}
	else {
		pos--;
	}
	return;

}

void Game::move_right(int &pos) {

	if (pos + 1 >= this->length){
		cout << "You hit the wall of the cave..." << endl;
	}

	else if (caveMatrix[this->adv_l][this->adv_w + 1].get_event() == 'h'){
		cout << "You have hit a hidden wall..." << endl;
	}

	else {
		pos++;
	}
	return;
}

void Game::wumpus_move(){

	int num = rand() % 4;

	if (num != 0) {
		caveMatrix[this->wump_l][this->wump_w].set_encounter(' ');
		randomize(this->wump_l, this->wump_w);
		caveMatrix[this->wump_l][this->wump_w].set_encounter('w');
		cout << "Thunderous footsteps echo through the cave..." << endl;
	}
	
	else {
		cout << "The arrow is followed only by silence..." << endl;
	}
	
	return;
}

void Game::wumpus_wander(){
	int num = rand() % 4;
	
	switch(num){

		case 0:
			if (wump_l - 1 >= 0) {
				if (!caveMatrix[wump_l - 1][wump_w].get_hasEvent()){
					caveMatrix[this->wump_l][this->wump_w].set_encounter(' ');
					wump_l--;
					caveMatrix[this->wump_l][this->wump_w].set_encounter('w');
				}
			}
			break;

		case 1:
			if (wump_w - 1 >= 0) {
				if (!caveMatrix[wump_l][wump_w - 1].get_hasEvent()){
					caveMatrix[this->wump_l][this->wump_w].set_encounter(' ');
					wump_w--;
					caveMatrix[this->wump_l][this->wump_w].set_encounter('w');
				}
			}
			break;

		case 2:
			if (wump_l + 1 < this->length) {
				if (!caveMatrix[wump_l + 1][wump_w].get_hasEvent()){
					caveMatrix[this->wump_l][this->wump_w].set_encounter(' ');
					wump_l++;
					caveMatrix[this->wump_l][this->wump_w].set_encounter('w');
				}
			}
			break;

		case 3:
			if (wump_w + 1 < this->width) {
				if (!caveMatrix[wump_l][wump_w + 1].get_hasEvent()){
					caveMatrix[this->wump_l][this->wump_w].set_encounter(' ');
					wump_w++;
					caveMatrix[this->wump_l][this->wump_w].set_encounter('w');
				}
			}
			break;
	}
}

void Game::fire_arrow(){
	// The player may fire arrow...
	int arrow_l = this->adv_l;
	int arrow_w = this->adv_w;
	this->num_arrows--;
	char dir = get_dir();

	switch(dir){
		case 'w':
			for (int i = 0; i < 3 && this->wumpus_dead == false; i++){
				Game::move_up(arrow_l);
				Game::check_wumpus_dead(arrow_l, arrow_w, i);
			}
			break;

		case 'a':
			for (int i = 0; i < 3 && this->wumpus_dead == false; i++){
				Game::move_left(arrow_w);
				Game::check_wumpus_dead(arrow_l, arrow_w, i);
			}
			break;

		case 's':
			for (int i = 0; i < 3 && this->wumpus_dead == false; i++){
				Game::move_down(arrow_l);
				Game::check_wumpus_dead(arrow_l, arrow_w, i);
			}
			break;

		case 'd':
			for (int i = 0; i < 3 && this->wumpus_dead == false; i++){
				Game::move_right(arrow_w);
				Game::check_wumpus_dead(arrow_l, arrow_w, i);
			}
			break;
	}
}

void Game::check_wumpus_dead(int arrow_l, int arrow_w, int arrow_range){

	if(caveMatrix[arrow_l][arrow_w].get_event() == 'w'){
		this->wumpus_dead = true;
	}

	if (caveMatrix[arrow_l][arrow_w].get_event() != 'w' && arrow_range == 2) {
		Game::wumpus_move();
	}
}

void Game::move(char c) {
	// Handle player's action: move or fire an arrow
	if (c == 'f'){
		Game::fire_arrow();
		return;
	}

	switch(c){
		case 'w':
			if (this->dizziness > 0) {
				Game::move_down(adv_l);
				this->dizziness--;
			} else {
				Game::move_up(adv_l);
			}
			break;

		case 'a':
			if (this->dizziness > 0) {
				Game::move_right(adv_w);
				this->dizziness--;
			} else {
				Game::move_left(adv_w);
			}
			break;

		case 's':
			if (this->dizziness > 0) {
				Game::move_up(adv_l);
				this->dizziness--;
			} else {
				Game::move_down(adv_l);
			}
			break;

		case 'd':
			if (this->dizziness > 0) {
				Game::move_left(adv_w);
				this->dizziness--;
			} else {
				Game::move_right(adv_w);
			}
			break;
	}
}

char Game::get_dir(){
	//get direction of arrow:
	char dir;
	
	cout << "------------------------------------------------------" << endl;
	cout << "Fire an arrow...." << endl;
	cout << "W-up" << endl;
	cout << "A-left" << endl;
	cout << "S-down" << endl;
	cout << "D-right" << endl;
	
	cout << "Enter direction: " << endl;
	dir = Game::error_check_arrow();
	cout << "------------------------------------------------------" << endl;
	return dir;
}

char Game::get_input(){
	//get action, move direction or firing an arrow
	char c;

	cout << "------------------------------------------------------" << endl;
	cout << "Player move..." << endl << endl;
	cout << "w-up" << endl;
	cout << "a-left" << endl;
	cout << "s-down" << endl;
	cout << "d-right" << endl;
	cout << "f-fire an arrow" << endl;

	cout << "Enter input: " << endl;
	c = Game::error_check_move();
	cout << "------------------------------------------------------" << endl;
	return c;
}

char Game::error_check_move(){
	char input;
	cin >> input;
	while (input != 'w' && input != 'a' && input != 's' && input != 'd' && input != 'f') {
		cout << "That was a wrong input. Please pick a correct direction!" << endl;
		cin.ignore(256, '\n');
		cin >> input;
	}
	return input;
}

char Game::error_check_arrow(){
	char input;
	cin >> input;
	while (input != 'w' && input != 'a' && input != 's' && input != 'd') {
		cout << "That was a wrong input. Please pick a correct direction!" << endl;
		cin.ignore(256, '\n');
		cin >> input;
	}
	return input;
}

int Game::set_length_width(){
	cout << "Min - 4" << endl << "Max - 50" << endl;
	int size;
	cin >> size;
	while (size < 4 || size > 50){
		cout << "The cave must be larger than 4 rooms and less than 50 rooms on each side" << endl;
		cin.ignore(256, '\n');
		cin >> size;
	}
	return size;
}

bool Game::set_debug() {
	cout << "Do you want to play in admin mode?" << endl;
	cout << "No - 0 " << endl << "Yes - 1" << endl;
	int debug;
	cin >> debug;
	while (debug != 0 && debug != 1 ){
		cout << "You must enter a '0' or a '1'" << endl;
		cin.ignore(256, '\n');
		cin >> debug;
	}
	return debug;
}