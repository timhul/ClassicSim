#ifndef OFFHANDMELEEHIT_H
#define OFFHANDMELEEHIT_H

#include "Event.h"

class Spells;

class OffhandMeleeHit: public Event {
public:
    OffhandMeleeHit(Spells*, const double, const int);

    virtual void act(void) override;
protected:
private:
    Spells* spells;
    int iteration;
};

#endif // OFFHANDMELEEHIT_H
