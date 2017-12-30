#ifndef COOLDOWNREADY_H
#define COOLDOWNREADY_H

#include "Event.h"
#include "Character.h"

class CooldownReady: public Event {
public:
    CooldownReady(Character*, const float);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
};


#endif // COOLDOWNREADY_H
