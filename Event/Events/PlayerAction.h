#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "Event.h"

class Spells;

class PlayerAction: public Event {
public:
    PlayerAction(Spells*, const float);

    virtual void act(void) override;
protected:
private:
    Spells* spells;
};

#endif // PLAYERACTION_H
