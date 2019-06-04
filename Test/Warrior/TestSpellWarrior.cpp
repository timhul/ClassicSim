#include "TestSpellWarrior.h"

#include <QDebug>
#include <utility>

#include "Buff.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Impale.h"
#include "SimSettings.h"
#include "Spell.h"
#include "TacticalMastery.h"
#include "Warrior.h"
#include "WarriorSpells.h"
#include "Whirlwind.h"

TestSpellWarrior::TestSpellWarrior(EquipmentDb *equipment_db, QString spell_under_test) :
    TestSpellDamage(equipment_db, std::move(spell_under_test))
{}

void TestSpellWarrior::set_up(const bool prepare_combat_iterations) {
    set_up_general();
    warrior = new Warrior(race, equipment_db, sim_settings);
    spells = dynamic_cast<WarriorSpells*>(warrior->get_spells());
    warrior->set_clvl(60);
    warrior->gain_rage(100);
    pchar = warrior;

    if (prepare_combat_iterations)
        pchar->prepare_set_of_combat_iterations();
}

void TestSpellWarrior::tear_down() {
    tear_down_general();
    delete warrior;
}

void TestSpellWarrior::run_class_specific_tests() {
    set_up();
    test_stance_cooldown();
    tear_down();
}

void TestSpellWarrior::given_0_of_2_impale() {
    assert(QString::number(warrior->get_stats()->get_melee_ability_crit_dmg_mod(), 'f', 3) == "2.000");
}

void TestSpellWarrior::given_1_of_2_impale() {
    Impale impale(warrior, nullptr);
    assert(impale.increment_rank());
    assert(QString::number(warrior->get_stats()->get_melee_ability_crit_dmg_mod(), 'f', 3) == "2.100");
}

void TestSpellWarrior::given_2_of_2_impale() {
    Impale impale(warrior, nullptr);
    assert(impale.increment_rank());
    assert(impale.increment_rank());
    assert(QString::number(warrior->get_stats()->get_melee_ability_crit_dmg_mod(), 'f', 3) == "2.200");
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
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    given_warrior_is_on_gcd(dynamic_cast<WarriorSpells*>(pchar->get_spells())->get_whirlwind());
}

void TestSpellWarrior::given_warrior_is_on_gcd(Spell *spell) {
    unsigned rage_before = warrior->get_resource_level(ResourceType::Rage);
    warrior->gain_rage(100 - rage_before);

    spell->perform();

    int rage_delta = static_cast<int>(warrior->get_resource_level(ResourceType::Rage)) - static_cast<int>(rage_before);

    if (rage_delta < 0)
        warrior->gain_rage(static_cast<unsigned>(rage_delta * -1));
    else
        warrior->lose_rage(static_cast<unsigned>(rage_delta));

    assert(warrior->on_global_cooldown());
}

void TestSpellWarrior::given_warrior_has_rage(const unsigned rage) {
    if (warrior->get_resource_level(ResourceType::Rage) > 0)
        warrior->lose_rage(warrior->get_resource_level(ResourceType::Rage));
    warrior->gain_rage(rage);
    then_warrior_has_rage(rage);
}

void TestSpellWarrior::when_switching_to_battle_stance() {
    warrior->switch_to_battle_stance();
}

void TestSpellWarrior::when_switching_to_berserker_stance() {
    warrior->switch_to_berserker_stance();
}

void TestSpellWarrior::then_warrior_has_rage(const unsigned rage) {
    if (rage != warrior->get_resource_level(ResourceType::Rage))
        qDebug() << spell_under_test << "expected" << rage << "rage but has" << warrior->get_resource_level(ResourceType::Rage);
    assert(warrior->get_resource_level(ResourceType::Rage) == rage);
}

void TestSpellWarrior::then_overpower_is_active() {
    assert(spells->get_overpower_buff()->is_active());
}
