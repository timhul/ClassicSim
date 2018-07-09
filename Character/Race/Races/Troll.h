#ifndef TROLL_H
#define TROLL_H

#include "Race.h"

class Troll: public Race {
public:
    int get_race_int() const override;
    QString get_name() const override;
    int get_base_strength() const override;
    int get_base_agility() const override;
    int get_base_stamina() const override;
    int get_base_intellect() const override;
    int get_base_spirit() const override;
    float get_int_multiplier() const override;
    float get_spirit_multiplier() const override;

    int get_axe_bonus() const override;
    int get_sword_bonus() const override;
    int get_mace_bonus() const override;
    int get_bow_bonus() const override;
    int get_gun_bonus() const override;
    int get_thrown_bonus() const override;
protected:
private:
};

#endif // TROLL_H
