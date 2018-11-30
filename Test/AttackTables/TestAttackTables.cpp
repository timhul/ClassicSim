#include <cassert>

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "Orc.h"
#include "MeleeSpecialTable.h"
#include "Race.h"
#include "SimSettings.h"
#include "TestAttackTables.h"
#include "Warrior.h"
#include "WhiteHitTable.h"

void TestAttackTables::test_all() {
    test_basic_properties();

    test_white_hit_table();
    test_white_hit_table_update();
    test_special_hit_table();
}

void TestAttackTables::test_basic_properties() {
}

void TestAttackTables::test_white_hit_table() {
    auto* random = new Random(0, 9999);
    auto* table = new WhiteHitTable(random, 300, 0.0, 0.0, 0.0, 0.0, 0.0);
    assert(table->get_outcome(0, 0.0) == AttackResult::HIT);
    assert(table->get_outcome(9999, 0.0) == AttackResult::HIT);
    delete table;

    table = new WhiteHitTable(random, 300, 0.0001, 0.0001, 0.0001, 0.0001, 0.0001);
    assert(table->get_outcome(0, 0.0) == AttackResult::MISS);
    assert(table->get_outcome(1, 0.0) == AttackResult::DODGE);
    assert(table->get_outcome(2, 0.0) == AttackResult::PARRY);
    assert(table->get_outcome(3, 0.0) == AttackResult::GLANCING);
    assert(table->get_outcome(4, 0.0) == AttackResult::BLOCK);
    assert(table->get_outcome(5, 0.0001) == AttackResult::CRITICAL);
    assert(table->get_outcome(6, 0.0001) == AttackResult::HIT);
    assert(table->get_outcome(9999, 0.0) == AttackResult::HIT);
    assert(table->get_outcome(6, 1.0) == AttackResult::CRITICAL);
    delete random;
    delete table;
}

void TestAttackTables::test_white_hit_table_update() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* pchar = new Warrior(race, equipment_db, sim_settings);
    pchar->get_equipment()->set_mainhand("Frostbite");
    pchar->get_equipment()->set_offhand("Vis'kag the Bloodletter");

    WhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(300);

    assert(table->get_outcome(0, 0.0001) == AttackResult::MISS);
    assert(table->get_outcome(2799, 0.0001) == AttackResult::MISS);
    assert(table->get_outcome(2800, 0.0001) == AttackResult::DODGE);
    assert(table->get_outcome(3299, 0.0001) == AttackResult::DODGE);
    assert(table->get_outcome(3300, 0.0001) == AttackResult::GLANCING);
    assert(table->get_outcome(7299, 0.0001) == AttackResult::GLANCING);
    assert(table->get_outcome(7300, 0.0001) == AttackResult::CRITICAL);
    // Note: This will fail when changing base agility or agi needed per crit.
    assert(table->get_outcome(7984, pchar->get_stats()->get_mh_crit_chance()) == AttackResult::CRITICAL);
    assert(table->get_outcome(7985, pchar->get_stats()->get_mh_crit_chance()) == AttackResult::HIT);

    pchar->get_stats()->increase_crit(0.0001);
    assert(table->get_outcome(7985, pchar->get_stats()->get_mh_crit_chance()) == AttackResult::CRITICAL);
    assert(table->get_outcome(7986, pchar->get_stats()->get_mh_crit_chance()) == AttackResult::HIT);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());
    pchar->get_stats()->increase_crit(0.9999);
    assert(table->get_outcome(7986, pchar->get_stats()->get_mh_crit_chance()) == AttackResult::CRITICAL);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == AttackResult::CRITICAL);

    delete sim_settings;
    delete race;
    delete pchar;
}

void TestAttackTables::test_special_hit_table() {
    auto* random = new Random(0, 9999);
    auto* table = new MeleeSpecialTable(random, 300, 0.0, 0.0, 0.0, 0.0);
    assert(table->get_outcome(0, 0.0) == AttackResult::HIT);
    delete table;

    table = new MeleeSpecialTable(random, 300, 0.0001, 0.0001, 0.0001, 0.0001);
    assert(table->get_outcome(0, 1.0) == AttackResult::MISS);
    assert(table->get_outcome(1, 1.0) == AttackResult::DODGE);
    assert(table->get_outcome(2, 1.0) == AttackResult::PARRY);
    assert(table->get_outcome(3, 1.0) == AttackResult::BLOCK_CRITICAL);
    assert(table->get_outcome(4, 1.0) == AttackResult::CRITICAL);
    assert(table->get_outcome(9999, 1.0) == AttackResult::CRITICAL);
    delete table;
    delete random;
}
