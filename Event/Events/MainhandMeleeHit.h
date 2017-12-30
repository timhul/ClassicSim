#ifndef MAINHANDMELEEHIT_H
#define MAINHANDMELEEHIT_H

#include "Event.h"
#include "Character.h"

class MainhandMeleeHit: public Event {
public:
    MainhandMeleeHit(Character*, const float);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
};

#endif // MAINHANDMELEEHIT_H
