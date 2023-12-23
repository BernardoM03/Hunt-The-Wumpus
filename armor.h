#ifndef ARMOR_H
#define ARMOR_H

#include "event.h"

class Armor : public Event {
protected:
public:
    Armor();
    int action();
    void percept();
};

#endif 