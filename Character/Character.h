#ifndef CHARACTER_H
#define CHARACTER_H

#include <QString>

class Race;
class Engine;
class Equipment;

class Character {
public:
    Character(Race*, Engine*, Equipment*);

    Race* get_race(void);
    virtual QString get_name() const = 0;

    virtual void rotation(void) = 0;
    virtual void mh_auto_attack(const int) = 0;
    virtual void oh_auto_attack(const int) = 0;

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

    int get_mh_wpn_skill();
    int get_oh_wpn_skill();
    int get_ranged_wpn_skill();

    virtual int get_melee_ap();

    virtual void increase_hit(float);
    virtual void increase_crit(float);
    virtual void increase_attack_speed(float);

    virtual void decrease_hit(float);
    virtual void decrease_crit(float);
    virtual void decrease_attack_speed(float);

    float get_mh_wpn_speed();
    float get_oh_wpn_speed();

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
    float percent_attack_speed;
    int clvl;
    bool melee_attacking;
    float last_action;

    virtual void add_next_mh_attack(void);
    virtual void add_next_oh_attack(void);
private:
};

#endif // CHARACTER_H
