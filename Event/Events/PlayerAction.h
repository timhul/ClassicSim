#pragma once

#include "Event.h"

class CharacterSpells;

class PlayerAction : public Event {
public:
    PlayerAction(CharacterSpells* spells, const double timestamp);

    void act() override;

private:
    CharacterSpells* spells;
};
