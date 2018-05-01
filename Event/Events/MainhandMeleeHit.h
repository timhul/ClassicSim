#ifndef MAINHANDMELEEHIT_H
#define MAINHANDMELEEHIT_H

#include "Event.h"

class Spells;

class MainhandMeleeHit: public Event {
public:
    MainhandMeleeHit(Spells*, const float, const int);

    virtual void act(void) override;
protected:
private:
    Spells* spells;
    int iteration;
};

#endif // MAINHANDMELEEHIT_H
