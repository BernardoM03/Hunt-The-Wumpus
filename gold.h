#ifndef GOLD_H
#define GOLD_H 

#include "event.h"

//Gold Interface

class Gold : public Event {
protected:
public:
	Gold();
	int action();
	void percept();
};

#endif
