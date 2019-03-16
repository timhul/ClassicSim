#ifndef OFFHANDMELEEHIT_H
#define OFFHANDMELEEHIT_H

#include "Event.h"

class CharacterSpells;

class OffhandMeleeHit: public Event {
public:
    OffhandMeleeHit(CharacterSpells*, const double, const int);

    virtual void act(void) override;
protected:
private:
    CharacterSpells* spells;
    int iteration;
};

#endif // OFFHANDMELEEHIT_H
