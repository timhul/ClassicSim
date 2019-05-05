#ifndef MAINHANDATTACKWARRIOR_H
#define MAINHANDATTACKWARRIOR_H

#include "Spell.h"
#include "MainhandAttack.h"

class StatisticsResource;
class Warrior;

class MainhandAttackWarrior: public MainhandAttack {
public:
    MainhandAttackWarrior(Character *pchar);

    void extra_attack() override;

private:
    Warrior* warr;
    StatisticsResource* statistics_resource {nullptr};

    void spell_effect() override;
    int calculate_damage() override;
    void prepare_set_of_combat_iterations_spell_specific() override;

    void gain_rage(const double rage_gain);
};

#endif // MAINHANDATTACKWARRIOR_H
