#pragma once

#include "MainhandAttack.h"

class StatisticsResource;
class Druid;

class MainhandAttackDruid: public MainhandAttack {
public:
    MainhandAttackDruid(Druid* pchar);

private:
    Druid* druid;
    StatisticsResource* statistics_resource {nullptr};

    void calculate_damage() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void gain_rage(const double rage_gain);

    unsigned get_weapon_skill() const;
};
