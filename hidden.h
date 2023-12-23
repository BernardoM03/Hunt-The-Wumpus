#ifndef HIDDEN_H
#define HIDDEN_H

#include "event.h"

class Hidden : public Event{
protected:
public:
    Hidden();
    int action();
    void percept();
};

#endif
