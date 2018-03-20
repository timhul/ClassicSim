#ifndef WARRIOR_H
#define WARRIOR_H

#include "Character.h"

class CombatRoll;
class Bloodthirst;
class MainhandAttack;
class OffhandAttack;
class Flurry;

class Warrior: public Character {
public:
    Warrior(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll);
    virtual ~Warrior();

    QString get_name() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    void rotation() override;
    void mh_auto_attack() override;
    void oh_auto_attack() override;
    float global_cooldown() const override;
    int get_curr_rage() const;
    void gain_rage(const int);
    void lose_rage(const int);
    int rage_gained_from_dd(const int) const;

    bool bt_available(void) const;

    int get_melee_ap() override;

    Flurry* get_flurry() const;

    void increase_hit(float) override;
    void increase_crit(float) override;
    void increase_ias(float) override;

    void decrease_hit(float) override;
    void decrease_crit(float) override;
    void decrease_ias(float) override;

protected:
private:
    int rage;
    CombatRoll* roll;
    Bloodthirst* bt;
    MainhandAttack* mh_attack;
    OffhandAttack* oh_attack;
    Flurry* flurry;

    void add_next_mh_attack(void) override;
    void add_next_oh_attack(void) override;
};

#endif // WARRIOR_H
