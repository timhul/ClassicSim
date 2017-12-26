#ifndef ENCOUNTEREND_H
#define ENCOUNTEREND_H

#include "Event.h"
#include "Engine.h"

class EncounterEnd: public Event {
public:
    EncounterEnd(Engine*);

    virtual void act(void) override;
protected:
private:
    Engine* engine;
};

#endif // ENCOUNTEREND_H
