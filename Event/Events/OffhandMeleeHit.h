#ifndef OFFHANDMELEEHIT_H
#define OFFHANDMELEEHIT_H

#include "Event.h"

class CharacterSpells;

class OffhandMeleeHit: public Event {
public:
    OffhandMeleeHit(CharacterSpells*, const double timestamp, const int iteration);

    void act(void) override;

private:
    CharacterSpells* spells;
    int iteration;
};

#endif // OFFHANDMELEEHIT_H
