#include "TestCharacterStats.h"

#include "CharacterStats.h"
#include "Orc.h"
#include "Warrior.h"

TestCharacterStats::TestCharacterStats() :
    TestObject(nullptr),
    pchar(nullptr),
    cstats(nullptr),
    race(nullptr)
{}

void TestCharacterStats::set_up() {
    race = new Orc();
    pchar = new Warrior(race, equipment_db, nullptr);
    cstats = pchar->get_stats();
}

void TestCharacterStats::tear_down() {
    delete pchar;
    delete race;
}

void TestCharacterStats::test_all() {
    set_up();
    test_values_after_initialization();
    tear_down();

    set_up();
    test_attack_speed_multipliers_stacks_multiplicatively();
    tear_down();

    set_up();
    test_physical_damage_multipliers_stacks_multiplicatively();
    tear_down();

    set_up();
    test_physical_damage_taken_multipliers_stacks_multiplicatively();
    tear_down();

    set_up();
    test_spell_damage_taken_multipliers_stacks_multiplicatively();
    tear_down();

    set_up();
    test_damage_bonuses_vs_creature_type();
    tear_down();

    set_up();
    test_ap_bonuses_vs_creature_type();
    tear_down();

    set_up();
    test_ap_multipliers();
    tear_down();
}

void TestCharacterStats::test_values_after_initialization() {
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.0));
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.0));
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 1.0));
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 1.0));
}

void TestCharacterStats::test_attack_speed_multipliers_stacks_multiplicatively() {
    cstats->increase_melee_attack_speed(10);
    // 1.1 = 1.0 * 1.1
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.10));

    cstats->increase_melee_attack_speed(20);
    // 1.32 = 1.0 * 1.1 * 1.2
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.32));

    cstats->increase_melee_attack_speed(50);
    // 1.98 = 1.0 * 1.1 * 1.2 * 1.5
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.98));

    cstats->increase_melee_attack_speed(100);
    // 3.96 = 1.0 * 1.1 * 1.2 * 1.5 * 2
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 3.96));

    cstats->decrease_melee_attack_speed(20);
    // 3.30 = 1.0 * 1.1 * 1.5 * 2
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 3.30));

    cstats->decrease_melee_attack_speed(10);
    // 3.00 = 1.0 * 1.5 * 2
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 3.00));

    cstats->decrease_melee_attack_speed(100);
    // 1.50 = 1.0 * 1.5
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.50));

    cstats->decrease_melee_attack_speed(50);
    // 1.00 = 1.0
    assert(almost_equal(cstats->get_melee_attack_speed_mod(), 1.00));
}

void TestCharacterStats::test_physical_damage_multipliers_stacks_multiplicatively() {
    cstats->increase_total_phys_dmg_mod(10);
    // 1.2 = 1.0 * 1.2
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.10));

    cstats->increase_total_phys_dmg_mod(20);
    // 1.32 = 1.0 * 1.1 * 1.2
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.32));

    cstats->increase_total_phys_dmg_mod(50);
    // 1.98 = 1.0 * 1.1 * 1.2 * 1.5
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.98));

    cstats->increase_total_phys_dmg_mod(100);
    // 3.96 = 1.0 * 1.1 * 1.2 * 1.5 * 2
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 3.96));

    cstats->decrease_total_phys_dmg_mod(20);
    // 3.30 = 1.0 * 1.1 * 1.5 * 2
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 3.30));

    cstats->decrease_total_phys_dmg_mod(10);
    // 3.00 = 1.0 * 1.5 * 2
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 3.00));

    cstats->decrease_total_phys_dmg_mod(100);
    // 1.50 = 1.0 * 1.5
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.50));

    cstats->decrease_total_phys_dmg_mod(50);
    // 1.00 = 1.0
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.00));
}

void TestCharacterStats::test_physical_damage_taken_multipliers_stacks_multiplicatively() {
    cstats->add_phys_damage_taken_mod(-10);
    // 0.90 = 1.0 * 0.9
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.90));

    cstats->add_phys_damage_taken_mod(-20);
    // 0.72 = 1.0 * 0.9 * 0.8
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.72));

    cstats->add_phys_damage_taken_mod(-50);
    // 0.36 = 1.0 * 0.9 * 0.8 * 0.5
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.36));

    cstats->remove_phys_damage_taken_mod(-20);
    // 0.45 = 1.0 * 0.9 * 0.5
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.45));

    cstats->remove_phys_damage_taken_mod(-10);
    // 0.5 = 1.0 * 0.5
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 0.50));

    cstats->remove_phys_damage_taken_mod(-50);
    // 1.00 = 1.0
    assert(almost_equal(cstats->get_physical_damage_taken_mod(), 1.00));
}

void TestCharacterStats::test_spell_damage_taken_multipliers_stacks_multiplicatively() {
    cstats->add_spell_damage_taken_mod(-10);
    // 0.90 = 1.0 * 0.9
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.90));

    cstats->add_spell_damage_taken_mod(-20);
    // 0.72 = 1.0 * 0.9 * 0.8
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.72));

    cstats->add_spell_damage_taken_mod(-50);
    // 0.36 = 1.0 * 0.9 * 0.8 * 0.5
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.36));

    cstats->remove_spell_damage_taken_mod(-20);
    // 0.45 = 1.0 * 0.9 * 0.5
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.45));

    cstats->remove_spell_damage_taken_mod(-10);
    // 0.5 = 1.0 * 0.5
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 0.50));

    cstats->remove_spell_damage_taken_mod(-50);
    // 1.00 = 1.0
    assert(almost_equal(cstats->get_spell_damage_taken_mod(), 1.00));
}

void TestCharacterStats::test_damage_bonuses_vs_creature_type() {
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.0));
    assert(pchar->get_target()->get_creature_type() == Target::CreatureType::Beast);

    cstats->increase_dmg_vs_type(Target::CreatureType::Beast, 0.01);
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.01));

    cstats->increase_dmg_vs_type(Target::CreatureType::Beast, 0.1);
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.11));

    cstats->decrease_dmg_vs_type(Target::CreatureType::Beast, 0.05);
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.06));

    cstats->decrease_dmg_vs_type(Target::CreatureType::Beast, 0.06);
    assert(almost_equal(cstats->get_total_phys_dmg_mod(), 1.0));
}

void TestCharacterStats::test_ap_bonuses_vs_creature_type() {
    const unsigned base_melee_ap = cstats->get_melee_ap();
    const unsigned base_ranged_ap = cstats->get_ranged_ap();
    assert(pchar->get_target()->get_creature_type() == Target::CreatureType::Beast);

    cstats->increase_ap_vs_type(Target::CreatureType::Beast, 100);
    assert(base_melee_ap + 100 == cstats->get_melee_ap());
    assert(base_ranged_ap + 100 == cstats->get_ranged_ap());

    cstats->decrease_ap_vs_type(Target::CreatureType::Beast, 100);
    assert(base_melee_ap == cstats->get_melee_ap());
    assert(base_ranged_ap == cstats->get_ranged_ap());
}

void TestCharacterStats::test_ap_multipliers() {
    const unsigned base_melee_ap = cstats->get_melee_ap();
    const unsigned base_ranged_ap = cstats->get_ranged_ap();

    cstats->add_ap_multiplier(100);
    assert(cstats->get_melee_ap() == base_melee_ap * 2);
    assert(cstats->get_ranged_ap() == base_ranged_ap * 2);

    cstats->remove_ap_multiplier(100);
    assert(cstats->get_melee_ap() == base_melee_ap);
    assert(cstats->get_ranged_ap() == base_ranged_ap);
}
