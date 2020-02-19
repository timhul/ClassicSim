#pragma once

#include "Spell.h"

class Random;
class StatisticsResource;

class NightDragonsBreath : public Spell {
public:
    NightDragonsBreath(Character* pchar);
    ~NightDragonsBreath() override;

private:
    const unsigned min {394};
    const unsigned max {457};
    Random* random;
    StatisticsResource* statistics_resource {nullptr};

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};
