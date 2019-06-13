#include "TestAttackTables.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "MagicAttackTable.h"
#include "Mechanics.h"
#include "MeleeSpecialTable.h"
#include "MeleeWhiteHitTable.h"
#include "Orc.h"
#include "Race.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "Target.h"
#include "Warrior.h"
#include "Weapon.h"

TestAttackTables::TestAttackTables(EquipmentDb *equipment_db):
    TestObject(equipment_db)
{}

void TestAttackTables::test_all() {
    qDebug() << "TestAttackTables";
    test_values_after_initialization();

    test_white_hit_table();
    test_white_hit_table_update();
    test_special_hit_table();
    test_magic_attack_table();
}

void TestAttackTables::test_values_after_initialization() {
}

void TestAttackTables::test_white_hit_table() {
    auto* random = new Random(0, 9999);
    auto* table = new MeleeWhiteHitTable(random, 300, 0, 0.0, 0.0, 0.0, 0.0);
    assert(table->get_outcome(0, 0.0) == PhysicalAttackResult::HIT);
    assert(table->get_outcome(9999, 0.0) == PhysicalAttackResult::HIT);
    delete table;

    table = new MeleeWhiteHitTable(random, 300, 1, 0.0001, 0.0001, 0.0001, 0.0001);
    assert(table->get_outcome(0, 0) == PhysicalAttackResult::MISS);
    assert(table->get_outcome(1, 0) == PhysicalAttackResult::DODGE);
    assert(table->get_outcome(2, 0) == PhysicalAttackResult::PARRY);
    assert(table->get_outcome(3, 0) == PhysicalAttackResult::GLANCING);
    assert(table->get_outcome(4, 0) == PhysicalAttackResult::BLOCK);
    assert(table->get_outcome(5, 1) == PhysicalAttackResult::CRITICAL);
    assert(table->get_outcome(6, 1) == PhysicalAttackResult::HIT);
    assert(table->get_outcome(9999, 0) == PhysicalAttackResult::HIT);
    delete random;
    delete table;
}

void TestAttackTables::test_white_hit_table_update() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* raid_control = new RaidControl(sim_settings);
    auto* pchar = new Warrior(race, equipment_db, sim_settings, raid_control);
    pchar->get_equipment()->set_mainhand(19103);
    pchar->get_equipment()->set_offhand(17075);
    assert(pchar->get_equipment()->get_mainhand()->get_name() == "Frostbite");
    assert(pchar->get_equipment()->get_offhand()->get_name() == "Vis'kag the Bloodletter");

    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_melee_white_table(300);

    assert(table->get_outcome(0, 1) == PhysicalAttackResult::MISS);
    assert(table->get_outcome(2799, 1) == PhysicalAttackResult::MISS);
    assert(table->get_outcome(2800, 1) == PhysicalAttackResult::DODGE);
    assert(table->get_outcome(3449, 1) == PhysicalAttackResult::DODGE);
    assert(table->get_outcome(3450, 1) == PhysicalAttackResult::GLANCING);
    assert(table->get_outcome(7449, 1) == PhysicalAttackResult::GLANCING);
    assert(table->get_outcome(7450, 1) == PhysicalAttackResult::CRITICAL);
    // Note: This will fail when changing base agility or agi needed per crit.
    assert(table->get_outcome(8134, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::CRITICAL);
    assert(table->get_outcome(8135, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::HIT);
    assert(table->get_outcome(8135, pchar->get_stats()->get_mh_crit_chance() + 1) == PhysicalAttackResult::CRITICAL);
    assert(table->get_outcome(8136, pchar->get_stats()->get_mh_crit_chance() + 1) == PhysicalAttackResult::HIT);

    pchar->get_stats()->decrease_melee_crit(pchar->get_stats()->get_mh_crit_chance());
    pchar->get_stats()->increase_melee_crit(9999);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::CRITICAL);

    delete pchar;
    delete raid_control;
    delete sim_settings;
    delete race;
}

void TestAttackTables::test_special_hit_table() {
    auto* random = new Random(0, 9999);
    auto* table = new MeleeSpecialTable(random, 300, 0, 0.0, 0.0, 0.0);
    assert(table->get_outcome(0, 0.0) == PhysicalAttackResult::HIT);
    delete table;

    table = new MeleeSpecialTable(random, 300, 1, 0.0001, 0.0001, 0.0001);
    assert(table->get_outcome(0, 10000) == PhysicalAttackResult::MISS);
    assert(table->get_outcome(1, 10000) == PhysicalAttackResult::DODGE);
    assert(table->get_outcome(2, 10000) == PhysicalAttackResult::PARRY);
    assert(table->get_outcome(3, 10000) == PhysicalAttackResult::BLOCK_CRITICAL);
    assert(table->get_outcome(4, 10000) == PhysicalAttackResult::CRITICAL);
    assert(table->get_outcome(9999, 10000) == PhysicalAttackResult::CRITICAL);
    delete table;
    delete random;
}

void TestAttackTables::test_magic_attack_table() {
    auto* random = new Random(0, 9999);
    auto* target = new Target(63);
    auto* mechanics = new Mechanics(target);
    auto* table = new MagicAttackTable(mechanics, random, 60, 0.0, target->get_resistance(MagicSchool::Frost));

    assert(table->get_hit_outcome(0, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(1699, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(1700, 0) == MagicAttackResult::HIT);
    assert(table->get_hit_outcome(9999, 0) == MagicAttackResult::HIT);

    target->set_lvl(62);
    table->update_miss_chance(60, 0);

    assert(table->get_hit_outcome(0, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(599, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(600, 0) == MagicAttackResult::HIT);
    assert(table->get_hit_outcome(9999, 0) == MagicAttackResult::HIT);

    target->set_lvl(61);
    table->update_miss_chance(60, 0);

    assert(table->get_hit_outcome(0, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(499, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(500, 0) == MagicAttackResult::HIT);
    assert(table->get_hit_outcome(9999, 0) == MagicAttackResult::HIT);

    target->set_lvl(60);
    table->update_miss_chance(60, 0);

    assert(table->get_hit_outcome(0, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(399, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(400, 0) == MagicAttackResult::HIT);
    assert(table->get_hit_outcome(9999, 0) == MagicAttackResult::HIT);

    target->set_lvl(59);
    table->update_miss_chance(60, 0);

    assert(table->get_hit_outcome(0, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(299, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(300, 0) == MagicAttackResult::HIT);
    assert(table->get_hit_outcome(9999, 0) == MagicAttackResult::HIT);

    target->set_lvl(58);
    table->update_miss_chance(60, 0);

    assert(table->get_hit_outcome(0, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(199, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(200, 0) == MagicAttackResult::HIT);
    assert(table->get_hit_outcome(9999, 0) == MagicAttackResult::HIT);

    target->set_lvl(57);
    table->update_miss_chance(60, 0);

    assert(table->get_hit_outcome(0, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(99, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(100, 0) == MagicAttackResult::HIT);
    assert(table->get_hit_outcome(9999, 0) == MagicAttackResult::HIT);

    target->set_lvl(56);
    table->update_miss_chance(60, 0);

    assert(table->get_hit_outcome(0, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(99, 0) == MagicAttackResult::MISS);
    assert(table->get_hit_outcome(100, 0) == MagicAttackResult::HIT);
    assert(table->get_hit_outcome(9999, 0) == MagicAttackResult::HIT);

    delete random;
    delete target;
    delete mechanics;
    delete table;
}
