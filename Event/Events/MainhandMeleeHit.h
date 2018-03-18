#ifndef MAINHANDMELEEHIT_H
#define MAINHANDMELEEHIT_H

#include "Event.h"

class Character;

class MainhandMeleeHit: public Event {
public:
    MainhandMeleeHit(Character*, const float);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
};

#endif // MAINHANDMELEEHIT_H
