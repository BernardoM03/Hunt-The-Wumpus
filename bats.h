#ifndef BATS_H
#define BATS_H 

#include "event.h"

//Bats Interface

class Bats : public Event {
protected:
public:
	Bats();
	int action();
	void percept();
};

#endif
