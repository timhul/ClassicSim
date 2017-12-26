#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "Event.h"
#include "Class.h"

class PlayerAction: public Event {
public:
    PlayerAction(const Class*);

    virtual void act(void) override;
protected:
private:
    const Class* pclass;
};

#endif // PLAYERACTION_H
