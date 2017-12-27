#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"

class Character {
public:
    Character(Race*);
    Race* get_race(void);
    virtual void rotation(void) const = 0;

    virtual int get_strength_modifier() const = 0;
    virtual int get_agility_modifier() const = 0;
    virtual int get_stamina_modifier() const = 0;
    virtual int get_intellect_modifier() const = 0;
    virtual int get_spirit_modifier() const = 0;
    int get_strength();
    int get_agility();
    int get_stamina();
    int get_intellect();
    int get_spirit();
    int get_clvl(void) const;
    void set_clvl(const int&);

protected:
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
    int clvl;
private:
};

#endif // CHARACTER_H
