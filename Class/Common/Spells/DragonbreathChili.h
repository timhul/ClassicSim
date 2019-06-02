#pragma once

#include "Proc.h"

class Random;
class StatisticsSpell;

class DragonbreathChili: public Proc {
public:
    DragonbreathChili(Character* pchar);
    ~DragonbreathChili() override;

private:
    Random* damage_roll;

    const double spell_dmg_coefficient {1.0};

    void proc_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};
