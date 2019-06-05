#ifndef ENCOUNTEREND_H
#define ENCOUNTEREND_H

#include "Event.h"

class Character;
class Engine;

class EncounterEnd: public Event {
public:
    EncounterEnd(Engine*, int combat_length);

    void act() override;

private:
    Engine* engine;
    Character* pchar;
};

#endif // ENCOUNTEREND_H
