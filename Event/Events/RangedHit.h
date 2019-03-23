#ifndef RANGEDHIT_H
#define RANGEDHIT_H

#include "Event.h"

class CharacterSpells;

class RangedHit: public Event {
public:
    RangedHit(CharacterSpells*, const double timestamp, const int iteration);

    void act() override;

private:
    CharacterSpells* spells;
    int iteration;
};

#endif // RANGEDHIT_H
