#ifndef MAINHANDMELEEHIT_H
#define MAINHANDMELEEHIT_H

#include "Event.h"

class CharacterSpells;

class MainhandMeleeHit: public Event {
public:
    MainhandMeleeHit(CharacterSpells*, const double timestamp, const int iteration);

    void act() override;

private:
    CharacterSpells* spells;
    int iteration;
};

#endif // MAINHANDMELEEHIT_H
