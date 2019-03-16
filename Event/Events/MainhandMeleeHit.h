#ifndef MAINHANDMELEEHIT_H
#define MAINHANDMELEEHIT_H

#include "Event.h"

class CharacterSpells;

class MainhandMeleeHit: public Event {
public:
    MainhandMeleeHit(CharacterSpells*, const double, const int);

    virtual void act(void) override;
protected:
private:
    CharacterSpells* spells;
    int iteration;
};

#endif // MAINHANDMELEEHIT_H
