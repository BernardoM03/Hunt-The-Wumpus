#ifndef WUMPUS_H
#define WUMPUS_H 

#include "event.h"

//Wumpus Interface
class Wumpus : public Event {
protected:
	bool dead;
public:
	Wumpus();
	int action();
	void percept();

	void set_dead(bool death);
	bool get_dead();
};

#endif
