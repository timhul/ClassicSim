#ifndef RESOURCEGAIN_H
#define RESOURCEGAIN_H

#include "Event.h"

class Character;
class Spell;

class ResourceGain: public Event {
public:
    ResourceGain(Character*, Spell*, const double);

    virtual void act(void) override;
protected:
private:
    Character* pchar;
    Spell* spell;
};

#endif // RESOURCEGAIN_H
