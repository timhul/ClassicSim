#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "Event.h"

class Character;

class PlayerAction: public Event {
public:
    PlayerAction(Character* pchar, const double);

    virtual void act(void) override;

private:
    Character* pchar;
};

#endif // PLAYERACTION_H
