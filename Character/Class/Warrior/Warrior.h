#ifndef WARRIOR_H
#define WARRIOR_H

#include "Class.h"
#include "PlayerAction.h"
#include "Bloodthirst.h"
#include "MainhandAttack.h"

class Warrior: public Class {
public:
    Warrior(Race* race, Engine* engine, Equipment* _eq) : Class(race, engine, _eq) {
        // Constants added as a hack, these are the gains from 1-60.
        // This essentially forces a clvl of 60 for stats to be accurate for warrior.
        this->STR += get_strength_modifier() + 97;
        this->AGI += get_agility_modifier() + 60;
        this->STAM += get_stamina_modifier() + 88;
        this->INT += get_intellect_modifier() + 10;
        this->SPI += get_spirit_modifier() + 25;
        this->rage = 0;
        this->bt = new Bloodthirst(engine, dynamic_cast<Character*>(this));
    }

    ~Warrior() {
        delete bt;
    }

    std::string get_name() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    void rotation() override;
    void auto_attack() override;
    float global_cooldown() const override;
    int get_curr_rage() const;

    bool bt_available(void) const;

    void add_next_action_event(void);

protected:
private:
    int rage;
    Bloodthirst* bt;
};

#endif // WARRIOR_H
