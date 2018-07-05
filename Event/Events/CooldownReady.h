#ifndef COOLDOWNREADY_H
#define COOLDOWNREADY_H

#include "Event.h"

class Rotation;

class CooldownReady: public Event {
public:
    CooldownReady(Rotation* rotation, const float);

    virtual void act(void) override;
protected:
private:
    Rotation* rotation;
};


#endif // COOLDOWNREADY_H
