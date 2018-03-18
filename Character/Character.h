#ifndef CHARACTER_H
#define CHARACTER_H

#include <string>

class Race;
class Engine;
class Equipment;

class Character {
public:
    Character(Race*, Engine*, Equipment*);

    Race* get_race(void);
    virtual std::string get_name() const = 0;

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

    int get_mh_wpn_skill();
    int get_oh_wpn_skill();
    int get_ranged_wpn_skill();

    virtual int get_melee_ap();

    void increase_hit(float);
    void increase_crit(float);
    void increase_ias(float);

    void decrease_hit(float);
    void decrease_crit(float);
    void decrease_ias(float);

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
    float percent_ias;
    int clvl;
    bool melee_attacking;
    float last_action;

    virtual void start_mh_attack(void);
    virtual void start_oh_attack(void);
private:
};

#endif // CHARACTER_H
