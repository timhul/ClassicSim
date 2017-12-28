#ifndef WARRIOR_H
#define WARRIOR_H

#include "Class.h"

class Warrior: public Class {
public:
    Warrior(Race* race, Engine* engine) : Class(race, engine) {
        // Constants added as a hack, these are the gains from 1-60.
        // This essentially forces a clvl of 60 for stats to be accurate for warrior.
        this->STR += get_strength_modifier() + 97;
        this->AGI += get_agility_modifier() + 60;
        this->STAM += get_stamina_modifier() + 88;
        this->INT += get_intellect_modifier() + 10;
        this->SPI += get_spirit_modifier() + 25;
    }

    std::string get_name() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    void rotation() const override;
    float global_cooldown() const override;

    bool is_dual_wielding(void) override;

protected:
private:
};

#endif // WARRIOR_H
