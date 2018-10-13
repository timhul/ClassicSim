
#include "TestSpellWarrior.h"

#include "Impale.h"
#include "Spell.h"
#include "TacticalMastery.h"
#include "OverpowerBuff.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Whirlwind.h"
#include "SimSettings.h"
#include <QDebug>
#include <utility>

TestSpellWarrior::TestSpellWarrior(EquipmentDb *equipment_db, QString spell_under_test) :
    TestSpellDamage(equipment_db, std::move(spell_under_test)),
    warrior(nullptr),
    sim_settings(new SimSettings())
{}

void TestSpellWarrior::set_up() {
    set_up_general();
    warrior = new Warrior(race, equipment_db, sim_settings);
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
    assert(impale.increment_rank());
    assert(QString::number(warrior->get_ability_crit_dmg_mod(), 'f', 3) == "2.100");
}

void TestSpellWarrior::given_2_of_2_impale() {
    Impale impale(warrior, nullptr);
    assert(impale.increment_rank());
    assert(impale.increment_rank());
    assert(QString::number(warrior->get_ability_crit_dmg_mod(), 'f', 3) == "2.200");
}

void TestSpellWarrior::given_0_of_5_tactical_mastery() {
    assert(warrior->get_stance_remainder() == 0);
}

void TestSpellWarrior::given_1_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    assert(tactical_mastery.increment_rank());
    assert(warrior->get_stance_remainder() == 5);
}

void TestSpellWarrior::given_2_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(warrior->get_stance_remainder() == 10);
}

void TestSpellWarrior::given_3_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(warrior->get_stance_remainder() == 15);
}

void TestSpellWarrior::given_4_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(warrior->get_stance_remainder() == 20);
}

void TestSpellWarrior::given_5_of_5_tactical_mastery() {
    TacticalMastery tactical_mastery(warrior, nullptr);
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(tactical_mastery.increment_rank());
    assert(warrior->get_stance_remainder() == 25);
}

void TestSpellWarrior::given_warrior_in_battle_stance() {
    if (!warrior->in_battle_stance()) {
        warrior->switch_to_battle_stance();
        given_engine_priority_pushed_forward(warrior->stance_cooldown() + 1);
    }

    assert(!warrior->on_stance_cooldown());
    assert(warrior->in_battle_stance());
}

void TestSpellWarrior::given_warrior_in_berserker_stance() {
    if (!warrior->in_berserker_stance()) {
        warrior->switch_to_berserker_stance();
        given_engine_priority_pushed_forward(warrior->stance_cooldown() + 1);
    }

    assert(!warrior->on_stance_cooldown());
    assert(warrior->in_berserker_stance());
}

void TestSpellWarrior::given_warrior_in_defensive_stance() {
    if (!warrior->in_defensive_stance()) {
        warrior->switch_to_defensive_stance();
        given_engine_priority_pushed_forward(warrior->stance_cooldown() + 1);
    }

    assert(!warrior->on_stance_cooldown());
    assert(warrior->in_defensive_stance());
}

void TestSpellWarrior::given_warrior_is_on_gcd() {
    given_warrior_is_on_gcd(dynamic_cast<WarriorSpells*>(pchar->get_spells())->get_whirlwind());
}

void TestSpellWarrior::given_warrior_is_on_gcd(Spell *spell) {
    unsigned rage_before = warrior->get_curr_rage();
    warrior->gain_rage(100 - rage_before);

    spell->perform();

    int rage_delta = static_cast<int>(warrior->get_curr_rage()) - static_cast<int>(rage_before);

    if (rage_delta < 0)
        warrior->gain_rage(static_cast<unsigned>(rage_delta * -1));
    else
        warrior->lose_rage(static_cast<unsigned>(rage_delta));

    assert(warrior->on_global_cooldown());
}

void TestSpellWarrior::given_warrior_has_rage(const unsigned rage) {
    if (warrior->get_curr_rage() > 0)
        warrior->lose_rage(warrior->get_curr_rage());
    warrior->gain_rage(rage);
    then_warrior_has_rage(rage);
}

void TestSpellWarrior::when_switching_to_battle_stance() {
    warrior->switch_to_battle_stance();
}

void TestSpellWarrior::when_switching_to_berserker_stance() {
    warrior->switch_to_berserker_stance();
}

void TestSpellWarrior::when_switching_to_defensive_stance() {
    warrior->switch_to_defensive_stance();
}

void TestSpellWarrior::then_warrior_has_rage(const unsigned rage) {
    if (rage != warrior->get_curr_rage())
        qDebug() << spell_under_test << "expected" << rage << "rage but has" << warrior->get_curr_rage();
    assert(warrior->get_curr_rage() == rage);
}

void TestSpellWarrior::then_overpower_is_active() {
    assert(warrior->get_overpower_buff()->is_active());
}
