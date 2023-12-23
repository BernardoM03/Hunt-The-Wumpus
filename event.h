#ifndef EVENT_H
#define EVENT_H 

using namespace std;
#include <iostream>

//Event Interface
//Note: this must be an abstract class!

class Event
{
protected:
public:
	Event();

	virtual int action() = 0;
	virtual void percept() = 0;
	virtual ~Event();
};
#endif
