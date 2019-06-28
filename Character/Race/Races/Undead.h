#pragma once

#include "Race.h"

class Undead: public Race {
public:
    int get_race_int() const override;
    QString get_name() const override;
    unsigned get_base_strength() const override;
    unsigned get_base_agility() const override;
    unsigned get_base_stamina() const override;
    unsigned get_base_intellect() const override;
    unsigned get_base_spirit() const override;
    double get_int_multiplier() const override;
    double get_spirit_multiplier() const override;

    unsigned get_axe_bonus() const override;
    unsigned get_sword_bonus() const override;
    unsigned get_mace_bonus() const override;
    unsigned get_bow_bonus() const override;
    unsigned get_gun_bonus() const override;
    unsigned get_thrown_bonus() const override;
};
