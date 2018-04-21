
#include "TestSpellWarrior.h"

#include "Impale.h"
#include "Warrior.h"

void TestSpellWarrior::set_up() {
    set_up_general();
    warrior = new Warrior(race, engine, equipment, combat);
    warrior->set_clvl(60);
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
