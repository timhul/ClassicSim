#ifndef OFFHANDMELEEHIT_H
#define OFFHANDMELEEHIT_H

#include "Event.h"
#include "Character.h"

class OffhandMeleeHit: public Event {
public:
    OffhandMeleeHit(Character*, const float);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
};

#endif // OFFHANDMELEEHIT_H
