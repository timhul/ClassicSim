#pragma once

#include "Event.h"

class CharacterSpells;
class EnabledBuffs;

class EncounterStart: public Event {
public:
    EncounterStart(CharacterSpells* spells, EnabledBuffs* buffs);

    void act() override;

private:
    CharacterSpells* spells;
    EnabledBuffs* buffs;
};
