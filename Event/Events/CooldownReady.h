#ifndef COOLDOWNREADY_H
#define COOLDOWNREADY_H

#include "Event.h"

class Spells;

class CooldownReady: public Event {
public:
    CooldownReady(Spells*, const float);

    virtual void act(void) override;
protected:
private:
    Spells* spells;
};


#endif // COOLDOWNREADY_H
