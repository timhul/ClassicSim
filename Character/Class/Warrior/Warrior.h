#ifndef WARRIOR_H
#define WARRIOR_H

#include "Class.h"
#include "PlayerAction.h"
#include "Bloodthirst.h"
#include "MainhandAttack.h"
#include "OffhandAttack.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"
#include "CombatRoll.h"

class Warrior: public Class {
public:
    Warrior(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll) :
        Class(race, engine, _eq) {
        // Constants added as a hack, these are the gains from 1-60.
        // This essentially forces a clvl of 60 for stats to be accurate for warrior.
        this->STR += get_strength_modifier() + 97;
        this->AGI += get_agility_modifier() + 60;
        this->STAM += get_stamina_modifier() + 88;
        this->INT += get_intellect_modifier() + 10;
        this->SPI += get_spirit_modifier() + 25;
        this->rage = 0;
        this->roll = _roll;
        this->bt = new Bloodthirst(engine, dynamic_cast<Character*>(this), roll);
        this->mh_attack = new MainhandAttack(engine, dynamic_cast<Character*>(this), roll);
        this->oh_attack = new OffhandAttack(engine, dynamic_cast<Character*>(this), roll);
    }

    ~Warrior() {
        delete bt;
        delete mh_attack;
        delete oh_attack;
    }

    std::string get_name() const override;
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

protected:
private:
    int rage;
    CombatRoll* roll;
    Bloodthirst* bt;
    MainhandAttack* mh_attack;
    OffhandAttack* oh_attack;

    void start_mh_attack(void) override;
    void start_oh_attack(void) override;
};

#endif // WARRIOR_H
