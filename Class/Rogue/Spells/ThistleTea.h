#pragma once

#include "Spell.h"

class StatisticsResource;
class Rogue;

class ThistleTea: public Spell {
public:
    ThistleTea(Rogue* rogue);
    ~ThistleTea() override;

private:
    StatisticsResource* statistics_resource {nullptr};

    void spell_effect() override;
    void prepare_set_of_combat_iterations_spell_specific() override;
};
