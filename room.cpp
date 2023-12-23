#include "room.h"

using namespace std;

//Room Implementation

Room::Room() : event(0), encounter(nullptr), hasEvent(false) {
    //cout << "Room()" << endl;
}

Room::~Room() {
    delete encounter;
    encounter = nullptr;
}

Event* Room::get_encounter() const{
    return encounter;
}

void Room::set_encounter(char event){
    this->event = event;
    hasEvent = true;
    if (event == 'w'){
        encounter = new Wumpus;
    } 
    else if (event == 'g'){
        encounter = new Gold;
    }
    else if (event == 's'){
        encounter = new Stalactites;
    }
    else if (event == 'b') {
        encounter = new Bats;
    } 
    else if (event == 'a') {
        encounter = new Armor;
    }
    else if (event == 'h') {
        encounter = new Hidden;
    }
    else {
        delete encounter;
        encounter = nullptr;
    }
}

bool Room::get_hasEvent() const {
    if (encounter != nullptr){
       return true;
    } else {
        return false;
    }
}

char Room::get_event() const {
    return event;
}
