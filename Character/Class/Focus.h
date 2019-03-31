#ifndef FOCUS_H
#define FOCUS_H

#include "Energy.h"

class Character;
class FocusTick;

class Focus: public Energy {
public:
    Focus(Character*);

    friend class Cat;

private:
};

#endif // FOCUS_H
