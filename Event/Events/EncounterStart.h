#ifndef ENCOUNTERSTART_H
#define ENCOUNTERSTART_H

#include "Event.h"

class EncounterStart: public Event {
public:
    EncounterStart();

    virtual void act(void) override;
protected:
private:
};

#endif // ENCOUNTERSTART_H
