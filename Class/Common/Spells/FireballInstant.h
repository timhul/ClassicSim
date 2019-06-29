#pragma once

#include "Spell.h"

class Buff;
class Random;

class FireballInstant: public Spell {
public:
    FireballInstant(Character* pchar,
                    const QString& name,
                    const unsigned instant_min,
                    const unsigned instant_max,
                    const unsigned dmg_over_duration,
                    const int duration,
                    const double spell_coefficient = 0.0,
                    const int spell_rank = 1);
    ~FireballInstant() override;

private:
    friend class Fireball;

    Buff* fireball_dot;
    Random* instant_dmg;
    double damage_remaining {0};
    const double period_tick {2.0};
    const unsigned max_ticks;
    const double base_dmg_per_tick;
    unsigned num_ticks_left {0};
    const double spell_coefficient;
    unsigned crit_bonus {0};

    void spell_effect() override;
    void reset_effect() override;
    void perform_periodic() override;
    void apply_fireball_dot();

    int magic_attack_result {MagicAttackResult::MISS};
};
