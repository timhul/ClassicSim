#ifndef ENCOUNTERSTART_H
#define ENCOUNTERSTART_H

#include "Event.h"

class CharacterSpells;

class EncounterStart: public Event {
public:
    EncounterStart(CharacterSpells* spells);

    void act() override;

private:
    CharacterSpells* spells;
};

#endif // ENCOUNTERSTART_H
