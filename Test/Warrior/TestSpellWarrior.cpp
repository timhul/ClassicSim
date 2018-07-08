
#include "TestSpellWarrior.h"

#include "Impale.h"
#include "TacticalMastery.h"
#include "OverpowerBuff.h"
#include "Warrior.h"
#include <QDebug>

TestSpellWarrior::TestSpellWarrior(QString spell_under_test) :
    TestSpell(spell_under_test)
{}

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

void TestSpellWarrior::given_0_of_5_tactical_mastery() {
    assert(warrior->get_stance_remainder() == 0);
}

void TestSpellWarrior::given_1_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    tactical_mastery.apply_rank_effect();
    assert(warrior->get_stance_remainder() == 5);
}

void TestSpellWarrior::given_2_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    assert(warrior->get_stance_remainder() == 10);
}

void TestSpellWarrior::given_3_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    assert(warrior->get_stance_remainder() == 15);
}

void TestSpellWarrior::given_4_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    assert(warrior->get_stance_remainder() == 20);
}

void TestSpellWarrior::given_5_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    tactical_mastery.apply_rank_effect();
    assert(warrior->get_stance_remainder() == 25);
}

void TestSpellWarrior::given_warrior_has_rage(const int rage) {
    warrior->lose_rage(warrior->get_curr_rage());
    warrior->gain_rage(rage);
    then_warrior_has_rage(rage);
}

void TestSpellWarrior::then_warrior_has_rage(const int rage) {
    if (rage != warrior->get_curr_rage())
        qDebug() << spell_under_test << "expected" << rage << "rage but has" << warrior->get_curr_rage();
    assert(warrior->get_curr_rage() == rage);
}

void TestSpellWarrior::then_overpower_is_active() {
    assert(warrior->get_overpower_buff()->is_active());
}
