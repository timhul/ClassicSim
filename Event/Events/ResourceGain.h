#ifndef RESOURCEGAIN_H
#define RESOURCEGAIN_H

#include "Event.h"

class Character;
class Spell;

class ResourceGain: public Event {
public:
    ResourceGain(Character* pchar, Spell* spell, const double timestamp);

    void act(void) override;

private:
    Character* pchar;
    Spell* spell;
};

#endif // RESOURCEGAIN_H
