#ifndef PLAYERACTION_H
#define PLAYERACTION_H

#include "Event.h"
#include "Class.h"

class PlayerAction: public Event {
public:
    PlayerAction(Class*, const float);

    virtual void act(void) override;
protected:
private:
    Class* pclass;
};

#endif // PLAYERACTION_H
