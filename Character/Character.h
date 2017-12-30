#ifndef CHARACTER_H
#define CHARACTER_H

#include "Race.h"
#include "Engine.h"
#include "Equipment.h"

class Character {
public:
    Character(Race*, Engine*, Equipment*);
    Race* get_race(void);
    virtual void rotation(void) = 0;
    virtual void mh_auto_attack(void) = 0;
    virtual void oh_auto_attack(void) = 0;

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
    Engine* get_engine(void) const;
    Equipment* get_equipment(void) const;
    bool is_dual_wielding(void);
    bool is_melee_attacking(void) const;
    void start_attack(void);
    void stop_attack(void);
    bool action_ready(void) const;
    virtual float global_cooldown() const;

    int get_mh_dmg();
    int get_oh_dmg();

    virtual int get_melee_ap();

    int rage_gained_from_dd(const int) const;

protected:
    Race* race;
    Engine* engine;
    Equipment* equipment;
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
    bool melee_attacking;
    float last_action;

    virtual void start_mh_attack(void);
    virtual void start_oh_attack(void);
private:
};

#endif // CHARACTER_H
