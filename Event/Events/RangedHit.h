#pragma once

#include "Event.h"

class CharacterSpells;

class RangedHit : public Event {
public:
    RangedHit(CharacterSpells* spells, const double timestamp, const int iteration);

    void act() override;

private:
    CharacterSpells* spells;
    int iteration;
};
