#ifndef ENCOUNTEREND_H
#define ENCOUNTEREND_H

#include "Event.h"

class EncounterEnd: public Event {
public:
    EncounterEnd();

    virtual void act(void) override;
protected:
private:
};

#endif // ENCOUNTEREND_H
