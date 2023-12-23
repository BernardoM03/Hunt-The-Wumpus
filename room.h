#ifndef ROOM_H
#define ROOM_H 

#include "event.h"
#include "wumpus.h"
#include "stalactites.h"
#include "bats.h"
#include "gold.h"
#include "armor.h"
#include "hidden.h"


using namespace std;

class Room {
private: 
	Event *encounter;
    bool hasEvent;
    char event;
public:
	Room();
    ~Room();
    //setters
    void set_encounter(char event);
    //getters
    Event* get_encounter() const;
    bool get_hasEvent() const;
    char get_event() const;
};

#endif
