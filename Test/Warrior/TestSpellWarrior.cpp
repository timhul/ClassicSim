
#include "TestSpellWarrior.h"

#include "Impale.h"
#include "Warrior.h"

void TestSpellWarrior::set_up() {
    set_up_general();
    warrior = new Warrior(race, engine, equipment, combat, faction);
    warrior->set_clvl(60);
    warrior->gain_rage(100);
    pchar = warrior;
}

void TestSpellWarrior::tear_down() {
    tear_down_general();
    delete warrior;
}

void TestSpellWarrior::given_0_of_2_impale() {
    assert(QString::number(warrior->get_ability_crit_dmg_mod(), 'f', 3) == "2.000");
}

void TestSpellWarrior::given_1_of_2_impale() {
    Impale impale(warrior, nullptr);
    impale.apply_rank_effect();
    assert(QString::number(warrior->get_ability_crit_dmg_mod(), 'f', 3) == "2.100");
}

void TestSpellWarrior::given_2_of_2_impale() {
    Impale impale(warrior, nullptr);
    impale.apply_rank_effect();
    impale.apply_rank_effect();
    assert(QString::number(warrior->get_ability_crit_dmg_mod(), 'f', 3) == "2.200");
}

void TestSpellWarrior::given_warrior_has_rage(const int rage) {
    warrior->lose_rage(warrior->get_curr_rage());
    warrior->gain_rage(rage);
    then_warrior_has_rage(rage);
}

void TestSpellWarrior::then_warrior_has_rage(const int rage) {
    assert(warrior->get_curr_rage() == rage);
}
