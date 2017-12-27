#ifndef MELEEHIT_H
#define MELEEHIT_H

#include "Event.h"
#include "Character.h"

class MeleeHit: public Event {
public:
    MeleeHit(Character*);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
};

#endif // MELEEHIT_H
