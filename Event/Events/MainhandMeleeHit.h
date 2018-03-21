#ifndef MAINHANDMELEEHIT_H
#define MAINHANDMELEEHIT_H

#include "Event.h"

class Character;

class MainhandMeleeHit: public Event {
public:
    MainhandMeleeHit(Character*, const float, const int);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
    int iteration;
};

#endif // MAINHANDMELEEHIT_H
