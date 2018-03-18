#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "Event.h"

class Character;

class PlayerAction: public Event {
public:
    PlayerAction(Character*, const float);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
};

#endif // PLAYERACTION_H
