#ifndef ENCOUNTEREND_H
#define ENCOUNTEREND_H

#include "Event.h"
#include "Engine.h"

class Character;

class EncounterEnd: public Event {
public:
    EncounterEnd(Engine*, Character* pchar);

    virtual void act(void) override;
protected:
private:
    Engine* engine;
    Character* pchar;
};

#endif // ENCOUNTEREND_H
