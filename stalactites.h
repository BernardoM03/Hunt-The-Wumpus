#ifndef STALACTITES_H
#define STALACTITES_H 

#include "event.h"

//Stalactites Interface

class Stalactites : public Event {
protected:
public:
	Stalactites();

	int action();
	void percept();
};

#endif
