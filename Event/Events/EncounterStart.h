#ifndef ENCOUNTERSTART_H
#define ENCOUNTERSTART_H

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

#endif // ENCOUNTERSTART_H
