#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"
#include "Engine.h"

class Character {
public:
    Character(Race*, Engine*);
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
    float get_hit_chance(void) const;
    float get_crit_chance(void) const;
    int get_clvl(void) const;
    void set_clvl(const int&);
    Engine* get_engine(void) const { return this->engine; }
    virtual bool is_dual_wielding(void) { return false; }

protected:
    Race* race;
    Engine* engine;
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
