#pragma once

#include "Spell.h"

class Buff;
class Random;
class PeriodicDamageSpell;

class FireballInstant: public Spell {
public:
    FireballInstant(Character* pchar,
                    const QString& name,
                    const unsigned instant_min,
                    const unsigned instant_max,
                    const unsigned dmg_over_duration,
                    const int duration,
                    const unsigned resource_cost,
                    const unsigned casting_time,
                    const double spell_coefficient,
                    const double spell_coefficient_dot,
                    const int spell_rank);
    ~FireballInstant() override;

private:
    friend class Fireball;

    PeriodicDamageSpell* fireball_dot;
    Random* instant_dmg;
    const double spell_coefficient;
    unsigned crit_bonus {0};
    double last_damage_dealt;

    void spell_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    int magic_attack_result {MagicAttackResult::MISS};
};
