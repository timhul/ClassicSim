#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"
#include "Stats.h"

class Character {
public:
    Character(Race* _race, Stats* _stats): race(_race), stats(_stats) {}
    Race* get_race(void);
    virtual void rotation(void) const = 0;

protected:
private:
    Race* race;
    Stats* stats;
};

#endif // CHARACTER_H
