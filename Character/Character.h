#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"

class Character {
public:
    Character(Race* _race): race(_race) {}
    Race* get_race(void);
    virtual void rotation(void) const = 0;

protected:
private:
    Race* race;
};

#endif // CHARACTER_H
