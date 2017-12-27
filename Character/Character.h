#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"

class Character {
public:
    Character(Race* _race): race(_race) {}
    Race* get_race(void);
    virtual void rotation(void) const = 0;

    int get_strength();
    int get_agility();
    int get_stamina();
    int get_intellect();
    int get_spirit();

protected:
private:
    Race* race;
    int STR;
    int AGI;
    int STAM;
    int INT;
    int SPI;
    int melee_ap;
    int ranged_ap;
    float percent_hit;
    float percent_crit;
};

#endif // CHARACTER_H
