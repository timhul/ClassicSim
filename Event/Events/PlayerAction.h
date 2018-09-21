#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "Event.h"

class Rotation;

class PlayerAction: public Event {
public:
    PlayerAction(Rotation* rotation, const double);

    virtual void act(void) override;
protected:
private:
    Rotation* rotation;
};

#endif // PLAYERACTION_H
