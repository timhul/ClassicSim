#pragma once

#include "Spell.h"

class Pet;

class PetAutoAttack: public Spell {
public:
    PetAutoAttack(Character* pchar, Pet *pet, const QString &icon);
    ~PetAutoAttack() override;

    double get_next_expected_use() const;
    void update_next_expected_use(const double);
    bool attack_is_valid(const int) const;
    int get_next_iteration();

    void complete_swing();

private:
    Pet* pet;
    double next_expected_use;
    int iteration;
    QVector<double> talent_ranks;

    void spell_effect() override;
    void reset_effect() override;

    void calculate_damage();

    void prepare_set_of_combat_iterations_spell_specific() override;
};
