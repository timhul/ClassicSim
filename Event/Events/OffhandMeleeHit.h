#pragma once

#include "Event.h"

class CharacterSpells;

class OffhandMeleeHit: public Event {
public:
    OffhandMeleeHit(CharacterSpells* spells, const double timestamp, const int iteration);

    void act() override;

private:
    CharacterSpells* spells;
    int iteration;
};
