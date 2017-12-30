#ifndef PALADIN_H
#define PALADIN_H

#include "Class.h"

class Paladin: public Class {
public:
    Paladin(Race* race, Engine* engine) : Class(race, engine) {
        this->STR += get_strength_modifier();
        this->AGI += get_agility_modifier();
        this->STAM += get_stamina_modifier();
        this->INT += get_intellect_modifier();
        this->SPI += get_spirit_modifier();
    }

    std::string get_name() const override;
    int get_strength_modifier() const override;
    int get_agility_modifier() const override;
    int get_stamina_modifier() const override;
    int get_intellect_modifier() const override;
    int get_spirit_modifier() const override;
    void rotation() override;
    float global_cooldown() const override;

protected:
private:
};

#endif // PALADIN_H
