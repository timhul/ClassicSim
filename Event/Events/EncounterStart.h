#ifndef ENCOUNTERSTART_H
#define ENCOUNTERSTART_H

#include "Event.h"

class Character;

class EncounterStart: public Event {
public:
    EncounterStart(Character* pchar);

    void act() override;

private:
    Character* pchar;
};

#endif // ENCOUNTERSTART_H
