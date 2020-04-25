#pragma once

#include "MainhandAttack.h"

class StatisticsResource;
class Druid;
class Proc;

class MainhandAttackDruid : public MainhandAttack {
public:
    MainhandAttackDruid(Druid* pchar, Proc* primal_fury);

private:
    Druid* druid;
    StatisticsResource* statistics_resource {nullptr};
    Proc* primal_fury;

    void calculate_damage() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void gain_rage(const double rage_gain);

    unsigned get_weapon_skill() const;
};
