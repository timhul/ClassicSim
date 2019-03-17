#include "TestSpell.h"

#include <utility>

#include "Character.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "Engine.h"
#include "Equipment.h"
#include "EquipmentDb.h"
#include "Faction.h"
#include "Item.h"
#include "MainhandMeleeHit.h"
#include "MeleeSpecialTable.h"
#include "MeleeWhiteHitTable.h"
#include "Orc.h"
#include "RangedWhiteHitTable.h"
#include "SimSettings.h"
#include "Stats.h"
#include "Target.h"
#include "Weapon.h"

TestSpell::TestSpell(EquipmentDb* equipment_db, QString spell_under_test) :
    equipment_db(equipment_db),
    sim_settings(nullptr),
    pchar(nullptr),
    race(nullptr),
    spell_under_test(std::move(spell_under_test))
{}

void TestSpell::set_up_general() {
    race = new Orc();
    sim_settings = new SimSettings();
    ignored_events.clear();
}

void TestSpell::tear_down_general() {
    delete race;
    delete sim_settings;
    ignored_events.clear();
}

void TestSpell::given_no_previous_damage_dealt() {
    then_damage_dealt_is(0);
}

void TestSpell::given_a_guaranteed_white_hit() {
    set_melee_auto_table_for_hit(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_hit(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_white_glancing_blow() {
    set_melee_auto_table_for_glancing(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_glancing(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_white_crit() {
    set_melee_auto_table_for_crit(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_crit(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_white_miss() {
    set_melee_auto_table_for_miss(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_miss(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_white_dodge() {
    set_melee_auto_table_for_dodge(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_dodge(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_white_parry() {
    set_melee_auto_table_for_parry(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_parry(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_white_block() {
    set_melee_auto_table_for_block(pchar->get_mh_wpn_skill());
    set_melee_auto_table_for_block(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_melee_ability_crit() {
    set_melee_special_table_for_crit(pchar->get_mh_wpn_skill());
    set_melee_special_table_for_crit(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_melee_ability_hit() {
    set_melee_special_table_for_hit(pchar->get_mh_wpn_skill());
    set_melee_special_table_for_hit(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_melee_ability_miss() {
    set_melee_special_table_for_miss(pchar->get_mh_wpn_skill());
    set_melee_special_table_for_miss(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_melee_ability_dodge() {
    set_melee_special_table_for_dodge(pchar->get_mh_wpn_skill());
    set_melee_special_table_for_dodge(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_melee_ability_parry() {
    set_melee_special_table_for_parry(pchar->get_mh_wpn_skill());
    set_melee_special_table_for_parry(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_melee_ability_block() {
    set_melee_special_table_for_block(pchar->get_mh_wpn_skill());
    set_melee_special_table_for_block(pchar->get_oh_wpn_skill());
}

void TestSpell::given_a_guaranteed_ranged_white_hit() {
    set_ranged_auto_table_for_hit(pchar->get_ranged_wpn_skill());
}

void TestSpell::given_a_guaranteed_ranged_white_crit() {
    set_ranged_auto_table_for_crit(pchar->get_ranged_wpn_skill());
}

void TestSpell::given_a_guaranteed_ranged_white_miss() {
    set_ranged_auto_table_for_miss(pchar->get_ranged_wpn_skill());
}

void TestSpell::given_a_guaranteed_ranged_white_dodge() {
    set_ranged_auto_table_for_dodge(pchar->get_ranged_wpn_skill());
}

void TestSpell::given_a_guaranteed_ranged_white_block() {
    set_ranged_auto_table_for_block(pchar->get_ranged_wpn_skill());
}

void TestSpell::set_melee_special_table_for_hit(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());

    assert_melee_special_table_can_only_hit(wpn_skill);
}

void TestSpell::set_melee_special_table_for_crit(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());
    pchar->get_stats()->increase_crit(1.0);

    assert_melee_special_table_can_only_crit(wpn_skill);
}

void TestSpell::set_melee_special_table_for_miss(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);
    table->update_miss_chance(1.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);

    assert_melee_special_table_can_only_miss(wpn_skill);
}

void TestSpell::set_melee_special_table_for_dodge(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(1.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);

    assert_melee_special_table_can_only_dodge(wpn_skill);
}

void TestSpell::set_melee_special_table_for_parry(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(1.0);
    table->update_block_chance(0.0);

    assert_melee_special_table_can_only_parry(wpn_skill);
}

void TestSpell::set_melee_special_table_for_block(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(1.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());

    assert_melee_special_table_can_only_block(wpn_skill);
}

void TestSpell::set_melee_auto_table_for_hit(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(0.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());

    assert_melee_auto_table_can_only_hit(wpn_skill);
}

void TestSpell::set_melee_auto_table_for_crit(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(0.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());
    pchar->get_stats()->increase_crit(1.0);

    assert_melee_auto_table_can_only_crit(wpn_skill);
}

void TestSpell::set_melee_auto_table_for_glancing(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(1.0);

    assert_melee_auto_table_can_only_glance(wpn_skill);
}

void TestSpell::set_melee_auto_table_for_miss(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);
    table->update_miss_chance(1.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(0.0);

    assert_melee_auto_table_can_only_miss(wpn_skill);
}

void TestSpell::set_melee_auto_table_for_dodge(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(1.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(0.0);

    assert_melee_auto_table_can_only_dodge(wpn_skill);
}

void TestSpell::set_melee_auto_table_for_parry(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(1.0);
    table->update_block_chance(0.0);
    table->update_glancing_chance(0.0);

    assert_melee_auto_table_can_only_parry(wpn_skill);
}

void TestSpell::set_melee_auto_table_for_block(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_parry_chance(0.0);
    table->update_block_chance(1.0);
    table->update_glancing_chance(0.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());

    assert_melee_auto_table_can_only_block(wpn_skill);
}

void TestSpell::set_ranged_auto_table_for_hit(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_block_chance(0.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());

    assert_ranged_auto_table_can_only_hit(wpn_skill);
}

void TestSpell::set_ranged_auto_table_for_crit(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_block_chance(0.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());
    pchar->get_stats()->increase_crit(1.0);

    assert_ranged_auto_table_can_only_crit(wpn_skill);
}

void TestSpell::set_ranged_auto_table_for_miss(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);
    table->update_miss_chance(1.0);
    table->update_dodge_chance(0.0);
    table->update_block_chance(0.0);

    assert_ranged_auto_table_can_only_miss(wpn_skill);
}

void TestSpell::set_ranged_auto_table_for_dodge(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(1.0);
    table->update_block_chance(0.0);

    assert_ranged_auto_table_can_only_dodge(wpn_skill);
}

void TestSpell::set_ranged_auto_table_for_block(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);
    table->update_miss_chance(0.0);
    table->update_dodge_chance(0.0);
    table->update_block_chance(1.0);

    pchar->get_stats()->decrease_crit(pchar->get_stats()->get_mh_crit_chance());

    assert_ranged_auto_table_can_only_block(wpn_skill);
}

void TestSpell::assert_melee_special_table_can_only_hit(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::HIT);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::HIT);
}

void TestSpell::assert_melee_special_table_can_only_crit(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::CRITICAL);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::CRITICAL);
}

void TestSpell::assert_melee_special_table_can_only_miss(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::MISS);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::MISS);
}

void TestSpell::assert_melee_special_table_can_only_dodge(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::DODGE);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::DODGE);
}

void TestSpell::assert_melee_special_table_can_only_parry(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::PARRY);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::PARRY);
}

void TestSpell::assert_melee_special_table_can_only_block(const int wpn_skill) {
    MeleeSpecialTable* table = pchar->get_combat_roll()->get_melee_special_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::BLOCK);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::BLOCK);
}

void TestSpell::assert_melee_auto_table_can_only_hit(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::HIT);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::HIT);
}

void TestSpell::assert_melee_auto_table_can_only_glance(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::GLANCING);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::GLANCING);
}

void TestSpell::assert_melee_auto_table_can_only_crit(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::CRITICAL);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::CRITICAL);
}

void TestSpell::assert_melee_auto_table_can_only_miss(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::MISS);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::MISS);
}

void TestSpell::assert_melee_auto_table_can_only_dodge(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::DODGE);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::DODGE);
}

void TestSpell::assert_melee_auto_table_can_only_parry(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::PARRY);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::PARRY);
}

void TestSpell::assert_melee_auto_table_can_only_block(const int wpn_skill) {
    MeleeWhiteHitTable* table = pchar->get_combat_roll()->get_white_hit_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::BLOCK);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::BLOCK);
}

void TestSpell::assert_ranged_auto_table_can_only_hit(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::HIT);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::HIT);
}

void TestSpell::assert_ranged_auto_table_can_only_crit(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::CRITICAL);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::CRITICAL);
}

void TestSpell::assert_ranged_auto_table_can_only_miss(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::MISS);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::MISS);
}

void TestSpell::assert_ranged_auto_table_can_only_dodge(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::DODGE);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::DODGE);
}

void TestSpell::assert_ranged_auto_table_can_only_block(const int wpn_skill) {
    RangedWhiteHitTable* table = pchar->get_combat_roll()->get_ranged_white_table(wpn_skill);

    assert(table->get_outcome(0, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::BLOCK);
    assert(table->get_outcome(9999, pchar->get_stats()->get_mh_crit_chance()) == PhysicalAttackResult::BLOCK);
}

void TestSpell::create_100_dmg_1h() {
    if (equipment_db->get_melee_weapon(TestUtils::Test100Dmg) != nullptr)
        return;

    Weapon* wpn = new Weapon("Test 100 dmg", TestUtils::Test100Dmg, WeaponTypes::SWORD, WeaponSlots::ONEHAND, 100, 100, 2.6);
    equipment_db->add_melee_weapon(wpn);
}

void TestSpell::create_100_dmg_dagger() {
    if (equipment_db->get_melee_weapon(TestUtils::Test100DmgDagger) != nullptr)
        return;

    Weapon* wpn = new Weapon("Test 100 dmg Dagger", TestUtils::Test100DmgDagger, WeaponTypes::DAGGER, WeaponSlots::ONEHAND, 100, 100, 2.0);
    equipment_db->add_melee_weapon(wpn);
}

void TestSpell::create_100_dmg_2h() {
    if (equipment_db->get_melee_weapon(TestUtils::Test100Dmg2h) != nullptr)
        return;

    Weapon* wpn = new Weapon("Test 100 dmg 2h", TestUtils::Test100Dmg2h, WeaponTypes::TWOHAND_SWORD, WeaponSlots::TWOHAND, 100, 100, 3.5);
    equipment_db->add_melee_weapon(wpn);
}

void TestSpell::create_100_dmg_ranged() {
    if (equipment_db->get_ranged(TestUtils::Test100DmgRanged) != nullptr)
        return;

    QMap<QString, QString> info = {{"slot", "RANGED"}};
    Weapon* wpn = new Weapon("Test 100 dmg Ranged", TestUtils::Test100DmgRanged, WeaponTypes::BOW, WeaponSlots::RANGED, 100, 100, 2.6, info);
    equipment_db->add_ranged(wpn);
}

void TestSpell::create_3_speed_ranged() {
    if (equipment_db->get_ranged(TestUtils::Test3SpeedRanged) != nullptr)
        return;

    QMap<QString, QString> info = {{"slot", "RANGED"}};
    Weapon* wpn = new Weapon("Test 3 Speed Ranged", TestUtils::Test3SpeedRanged, WeaponTypes::BOW, WeaponSlots::RANGED, 100, 100, 3.0, info);
    equipment_db->add_ranged(wpn);
}

void TestSpell::create_2_speed_ranged() {
    if (equipment_db->get_ranged(TestUtils::Test2SpeedRanged) != nullptr)
        return;

    QMap<QString, QString> info = {{"slot", "RANGED"}};
    Weapon* wpn = new Weapon("Test 2 Speed Ranged", TestUtils::Test2SpeedRanged, WeaponTypes::BOW, WeaponSlots::RANGED, 100, 100, 2.0, info);
    equipment_db->add_ranged(wpn);
}

void TestSpell::create_3_speed() {
    if (equipment_db->get_melee_weapon(TestUtils::Test3Speed) != nullptr)
        return;

    Weapon* wpn = new Weapon("Test 3 Speed", TestUtils::Test3Speed, WeaponTypes::SWORD, WeaponSlots::ONEHAND, 100, 100, 3.0);
    equipment_db->add_melee_weapon(wpn);
}

void TestSpell::create_2_speed() {
    if (equipment_db->get_melee_weapon(TestUtils::Test2Speed) != nullptr)
        return;

    Weapon* wpn = new Weapon("Test 2 Speed", TestUtils::Test2Speed, WeaponTypes::SWORD, WeaponSlots::ONEHAND, 100, 100, 2.0);
    equipment_db->add_melee_weapon(wpn);
}

void TestSpell::create_axe() {
    if (equipment_db->get_melee_weapon(TestUtils::TestAxe) != nullptr)
        return;

    Weapon* wpn = new Weapon("Test Axe", TestUtils::TestAxe, WeaponTypes::AXE, WeaponSlots::ONEHAND, 100, 100, 2.0);
    equipment_db->add_melee_weapon(wpn);
}

void TestSpell::create_5_sword_skill_ring() {
    if (equipment_db->get_ring(TestUtils::Test5SwordSkill) != nullptr)
        return;

    QMap<QString, QString> info = {{"slot", "RING"}};
    QVector<QPair<QString, QString>> stats = {{"SWORD_SKILL", "5"}};

    Item* ring = new Item("Test +5 Sword Skill", TestUtils::Test5SwordSkill, info, stats);
    equipment_db->add_ring(ring);
}

void TestSpell::create_10_sword_skill_ring() {
    if (equipment_db->get_ring(TestUtils::Test10SwordSkill) != nullptr)
        return;

    QMap<QString, QString> info = {{"slot", "RING"}};
    QVector<QPair<QString, QString>> stats = {{"SWORD_SKILL", "10"}};

    Item* ring = new Item("Test +10 Sword Skill", TestUtils::Test10SwordSkill, info, stats);
    equipment_db->add_ring(ring);
}

void TestSpell::create_15_sword_skill_ring() {
    if (equipment_db->get_ring(TestUtils::Test15SwordSkill) != nullptr)
        return;

    QMap<QString, QString> info = {{"slot", "RING"}};
    QVector<QPair<QString, QString>> stats = {{"SWORD_SKILL", "15"}};

    Item* ring = new Item("Test +15 Sword Skill", TestUtils::Test15SwordSkill, info, stats);
    equipment_db->add_ring(ring);
}

void TestSpell::given_a_mainhand_weapon_with_100_min_max_dmg() {
    create_100_dmg_1h();

    pchar->get_equipment()->set_mainhand(TestUtils::Test100Dmg);
    assert(pchar->get_equipment()->get_mainhand()->get_min_dmg() == 100);
    assert(pchar->get_equipment()->get_mainhand()->get_max_dmg() == 100);
}

void TestSpell::given_a_mainhand_dagger_with_100_min_max_dmg() {
    create_100_dmg_dagger();

    pchar->get_equipment()->set_mainhand(TestUtils::Test100DmgDagger);
    assert(pchar->get_equipment()->get_mainhand()->get_min_dmg() == 100);
    assert(pchar->get_equipment()->get_mainhand()->get_max_dmg() == 100);
}

void TestSpell::given_a_mainhand_weapon_with_3_speed() {
    create_3_speed();

    pchar->get_equipment()->set_mainhand(TestUtils::Test3Speed);
    assert(almost_equal(3.0, pchar->get_equipment()->get_mainhand()->get_base_weapon_speed()));
}

void TestSpell::given_a_mainhand_weapon_with_2_speed() {
    create_2_speed();

    pchar->get_equipment()->set_mainhand(TestUtils::Test2Speed);
    assert(almost_equal(2.0, pchar->get_equipment()->get_mainhand()->get_base_weapon_speed()));
}

void TestSpell::given_a_twohand_weapon_with_100_min_max_dmg() {
    create_100_dmg_2h();

    pchar->get_equipment()->set_mainhand(TestUtils::Test100Dmg2h);
    assert(pchar->get_equipment()->get_mainhand()->get_min_dmg() == 100);
    assert(pchar->get_equipment()->get_mainhand()->get_max_dmg() == 100);
}

void TestSpell::given_a_ranged_weapon_with_100_min_max_dmg() {
    create_100_dmg_ranged();

    pchar->get_equipment()->set_ranged(TestUtils::Test100DmgRanged);
    assert(pchar->get_equipment()->get_ranged()->get_min_dmg() == 100);
    assert(pchar->get_equipment()->get_ranged()->get_max_dmg() == 100);
}

void TestSpell::given_a_ranged_weapon_with_3_speed() {
    create_3_speed_ranged();

    pchar->get_equipment()->set_ranged(TestUtils::Test3SpeedRanged);
    assert(almost_equal(3.0, pchar->get_equipment()->get_ranged()->get_base_weapon_speed()));
}

void TestSpell::given_a_ranged_weapon_with_2_speed() {
    create_2_speed_ranged();

    pchar->get_equipment()->set_ranged(TestUtils::Test2SpeedRanged);
    assert(almost_equal(2.0, pchar->get_equipment()->get_ranged()->get_base_weapon_speed()));
}

void TestSpell::given_300_weapon_skill_mh() {
    assert(pchar->get_mh_wpn_skill() == 300);
}

void TestSpell::given_305_weapon_skill_mh() {
    create_5_sword_skill_ring();

    pchar->get_equipment()->set_ring1(TestUtils::Test5SwordSkill);

    assert(pchar->get_equipment()->get_ring1() != nullptr);
    assert(pchar->get_mh_wpn_skill() == 305);
}

void TestSpell::given_310_weapon_skill_mh() {
    create_10_sword_skill_ring();

    pchar->get_equipment()->set_ring1(TestUtils::Test10SwordSkill);

    assert(pchar->get_equipment()->get_ring1() != nullptr);
    assert(pchar->get_mh_wpn_skill() == 310);
}

void TestSpell::given_315_weapon_skill_mh() {
    create_15_sword_skill_ring();

    pchar->get_equipment()->set_ring1(TestUtils::Test15SwordSkill);

    assert(pchar->get_equipment()->get_ring1() != nullptr);
    assert(pchar->get_mh_wpn_skill() == 315);
}

void TestSpell::given_300_weapon_skill_oh() {
    assert(pchar->get_oh_wpn_skill() == 300);
}

void TestSpell::given_305_weapon_skill_oh() {
    create_5_sword_skill_ring();
    qDebug() << "equipping";
    pchar->get_equipment()->set_ring1(TestUtils::Test5SwordSkill);

    assert(pchar->get_equipment()->get_ring1() != nullptr);
    assert(pchar->get_oh_wpn_skill() == 305);
}

void TestSpell::given_310_weapon_skill_oh() {
    create_10_sword_skill_ring();

    pchar->get_equipment()->set_ring1(TestUtils::Test10SwordSkill);

    assert(pchar->get_equipment()->get_ring1() != nullptr);
    assert(pchar->get_oh_wpn_skill() == 310);
}

void TestSpell::given_315_weapon_skill_oh() {
    create_15_sword_skill_ring();

    pchar->get_equipment()->set_ring1(TestUtils::Test15SwordSkill);

    assert(pchar->get_equipment()->get_ring1() != nullptr);
    assert(pchar->get_oh_wpn_skill() == 315);
}

void TestSpell::given_no_mainhand() {
    pchar->get_equipment()->clear_mainhand();
    assert(pchar->get_equipment()->get_mainhand() == nullptr);
}

void TestSpell::given_no_offhand() {
    pchar->get_equipment()->clear_offhand();
    assert(pchar->get_equipment()->get_offhand() == nullptr);
}

void TestSpell::given_an_offhand_weapon_with_100_min_max_dmg() {
    create_100_dmg_1h();

    pchar->get_equipment()->set_offhand(TestUtils::Test100Dmg);
    assert(pchar->get_equipment()->get_offhand()->get_min_dmg() == 100);
    assert(pchar->get_equipment()->get_offhand()->get_max_dmg() == 100);
}

void TestSpell::given_an_offhand_weapon_with_3_speed() {
    create_3_speed();

    pchar->get_equipment()->set_offhand(TestUtils::Test3Speed);
    assert(int(pchar->get_equipment()->get_offhand()->get_base_weapon_speed()) == 3);
}

void TestSpell::given_an_offhand_weapon_with_2_speed() {
    create_2_speed();

    pchar->get_equipment()->set_offhand(TestUtils::Test2Speed);
    assert(int(pchar->get_equipment()->get_offhand()->get_base_weapon_speed()) == 2);
}

void TestSpell::given_an_offhand_axe() {
    create_axe();

    pchar->get_equipment()->set_offhand(TestUtils::TestAxe);
    assert(int(pchar->get_equipment()->get_offhand()->get_weapon_type_string() == "Axe"));
}

void TestSpell::given_1000_melee_ap() {
    pchar->get_stats()->increase_melee_ap(1000 - pchar->get_stats()->get_melee_ap());
    assert(pchar->get_stats()->get_melee_ap() == 1000);
}

void TestSpell::given_1000_ranged_ap() {
    pchar->get_stats()->increase_ranged_ap(1000 - pchar->get_stats()->get_ranged_ap());
    assert(pchar->get_stats()->get_ranged_ap() == 1000);
}

void TestSpell::given_target_has_0_armor() {
    pchar->get_target()->set_armor(0);
    assert(pchar->get_target()->get_armor() == 0);
}

void TestSpell:: given_1h_axe_equipped_in_mainhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(19921);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Zulian Hacker");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::AXE);
}

void TestSpell:: given_1h_mace_equipped_in_mainhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(21837);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Anubisath Warhammer");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::MACE);
}

void TestSpell:: given_1h_sword_equipped_in_mainhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(13361);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Skullforge Reaver");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::SWORD);
}

void TestSpell:: given_fist_weapon_equipped_in_mainhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(19365);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Claw of the Black Drake");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::FIST);
}

void TestSpell:: given_dagger_equipped_in_mainhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(12783);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Heartseeker");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::DAGGER);
}

void TestSpell:: given_no_mainhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->clear_mainhand();
    assert(pchar->get_stats()->get_equipment()->get_mainhand() == nullptr);
}

void TestSpell:: given_1h_axe_equipped_in_offhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_offhand(19921);
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_name() == "Zulian Hacker");
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::AXE);
}

void TestSpell:: given_1h_mace_equipped_in_offhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_offhand(21837);
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_name() == "Anubisath Warhammer");
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::MACE);
}

void TestSpell:: given_1h_sword_equipped_in_offhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_offhand(13361);
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_name() == "Skullforge Reaver");
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::SWORD);
}

void TestSpell:: given_fist_weapon_equipped_in_offhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_offhand(19910);
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_name() == "Arlokk's Grasp");
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::FIST);
}

void TestSpell:: given_dagger_equipped_in_offhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_offhand(12783);
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_name() == "Heartseeker");
    assert(pchar->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::DAGGER);
}

void TestSpell:: given_no_offhand(Character* pchar) {
    pchar->get_stats()->get_equipment()->clear_offhand();
    assert(pchar->get_stats()->get_equipment()->get_offhand() == nullptr);
}

void TestSpell:: given_2h_axe_equipped(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(12784);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Arcanite Reaper");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_AXE);
}

void TestSpell:: given_2h_mace_equipped(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(17073);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Earthshaker");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_MACE);
}

void TestSpell:: given_2h_sword_equipped(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(19364);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Ashkandi, Greatsword of the Brotherhood");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_SWORD);
}

void TestSpell:: given_polearm_equipped(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(21635);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Barb of the Sand Reaver");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::POLEARM);
}

void TestSpell:: given_staff_equipped(Character* pchar) {
    pchar->get_stats()->get_equipment()->set_mainhand(17743);
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_name() == "Resurgence Rod");
    assert(pchar->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::STAFF);
}

void TestSpell::given_engine_priority_at(const double priority) {
    if (priority < pchar->get_engine()->get_current_priority())
        pchar->get_engine()->reset();

    auto* event = new MainhandMeleeHit(pchar->get_spells(), priority, 0);
    pchar->get_engine()->set_current_priority(event);
    delete event;
}

void TestSpell::given_engine_priority_pushed_forward(const double priority) {
    auto* event = new MainhandMeleeHit(pchar->get_spells(), priority + pchar->get_engine()->get_current_priority(), 0);
    pchar->get_engine()->set_current_priority(event);
    delete event;
}

void TestSpell::given_event_is_ignored(const QString& event) {
    ignored_events.insert(event);
}

void TestSpell::when_running_queued_events_until(const double priority) {
    while (pchar->get_engine()->get_current_priority() < priority) {
        if (pchar->get_engine()->get_queue()->empty()) {
            qDebug() << spell_under_test << "Attempted to run queued events until"
                     << QString::number(priority, 'f', 3)
                     << "but ran out of events at" << pchar->get_engine()->get_current_priority();
            assert(false);
        }
        Event* event = pchar->get_engine()->get_queue()->get_next();
        pchar->get_engine()->set_current_priority(event);

        event->act();

        delete event;
    }
}

void TestSpell::then_damage_dealt_is(const int damage) {
    if (damage != pchar->get_statistics()->get_total_damage_dealt())
        qDebug() << spell_under_test << "then_damage_dealt_is() assertion failed, expected"
                 << damage << "got" << pchar->get_statistics()->get_total_damage_dealt();
    assert(pchar->get_statistics()->get_total_damage_dealt() == damage);
}

void TestSpell::then_damage_dealt_is_in_range(const int min, const int max) {
    assert(min < max);
    const int damage_dealt = pchar->get_statistics()->get_total_damage_dealt();

    if (damage_dealt < min || damage_dealt > max)
        qDebug() << spell_under_test << "then_damage_dealt_is_in_range() assertion failed, expected range"
                 << min << "-" << max << "but got" << damage_dealt;
    assert(damage_dealt >= min && damage_dealt <= max);
}

void TestSpell::then_next_event_is(const QString &name) {
    Event* event = pchar->get_engine()->get_queue()->get_next();
    pchar->get_engine()->set_current_priority(event);

    if (event->get_name() != name)
        qDebug() << "Expected event" << name << "got" << event->get_name();
    assert(event->get_name() == name);

    delete event;
}

void TestSpell::then_next_event_is(const QString &name, const QString &priority, bool act_event) {
    if (pchar->get_engine()->get_queue()->empty()) {
        qDebug() << spell_under_test << "Queue empty! Expected to find" << name << priority;
        assert(false);
    }

    Event* event = nullptr;
    while (!pchar->get_engine()->get_queue()->empty()) {
        event = pchar->get_engine()->get_queue()->get_next();
        pchar->get_engine()->set_current_priority(event);

        if (!ignored_events.contains(event->get_name()))
            break;

        delete event;
    }

    if (event->get_name() != name) {
        qDebug() << spell_under_test << "Expected event" << name << priority << "but got" << event->get_name()
                 << "at priority" << QString::number(pchar->get_engine()->get_current_priority(), 'f', 3);
        assert(false);
    }

    if (QString::number(event->get_priority(), 'f', 3) != priority) {
        qDebug() << spell_under_test << "During event" << name << "expected" << priority
                 << "but got" << QString::number(pchar->get_engine()->get_current_priority(), 'f', 3);
        assert(false);
    }

    if (act_event)
        event->act();

    delete event;
}

void TestSpell::dump_queued_events() {
    Queue* queue = pchar->get_engine()->get_queue();
    while (!queue->empty()) {
        Event* event = queue->get_next();

        qDebug() << event->get_name() << ": " << event->get_priority();

        delete event;
    }
}
