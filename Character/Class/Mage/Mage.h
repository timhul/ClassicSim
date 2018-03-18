#ifndef MAGE_H
#define MAGE_H

#include "Character.h"
#include "CombatRoll.h"

class Mage: public Character {
public:
    Mage(Race* race, Engine* engine, Equipment* _eq, CombatRoll* _roll) :
        Character(race, engine, _eq) {
        this->STR += get_strength_modifier();
        this->AGI += get_agility_modifier();
        this->STAM += get_stamina_modifier();
        this->INT += get_intellect_modifier();
        this->SPI += get_spirit_modifier();
        this->roll = _roll;
    }

    virtual ~Mage() {}

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

    int get_melee_ap() override;

protected:
private:
    CombatRoll* roll;
};

#endif // MAGE_H
