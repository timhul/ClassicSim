#pragma once

#include "MainhandAttack.h"

class StatisticsResource;
class Warrior;
class WarriorSpells;

class MainhandAttackWarrior: public MainhandAttack {
public:
    MainhandAttackWarrior(Warrior* pchar, WarriorSpells* spells);

private:
    Warrior* warr;
    WarriorSpells* spells;
    StatisticsResource* statistics_resource {nullptr};

    void calculate_damage() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void gain_rage(const double rage_gain);
};
