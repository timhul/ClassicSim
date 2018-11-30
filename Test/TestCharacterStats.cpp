#include "TestCharacterStats.h"

#include "CharacterStats.h"
#include "Orc.h"
#include "Warrior.h"

TestCharacterStats::TestCharacterStats() :
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
    test_basic_properties();
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
}

void TestCharacterStats::test_basic_properties() {
    assert(delta(cstats->get_total_phys_dmg_mod(), 1.0) < 0.0001);
    assert(delta(cstats->get_attack_speed_mod(), 1.0) < 0.0001);
    assert(delta(cstats->get_physical_damage_taken_mod(), 1.0) < 0.0001);
    assert(delta(cstats->get_spell_damage_taken_mod(), 1.0) < 0.0001);
}

void TestCharacterStats::test_attack_speed_multipliers_stacks_multiplicatively() {
    cstats->increase_haste(10);
    // 1.1 = 1.0 * 1.1
    assert(delta(cstats->get_attack_speed_mod(), 1.10) < 0.0001);

    cstats->increase_haste(20);
    // 1.32 = 1.0 * 1.1 * 1.2
    assert(delta(cstats->get_attack_speed_mod(), 1.32) < 0.0001);

    cstats->increase_haste(50);
    // 1.98 = 1.0 * 1.1 * 1.2 * 1.5
    assert(delta(cstats->get_attack_speed_mod(), 1.98) < 0.0001);

    cstats->increase_haste(100);
    // 3.96 = 1.0 * 1.1 * 1.2 * 1.5 * 2
    assert(delta(cstats->get_attack_speed_mod(), 3.96) < 0.0001);

    cstats->decrease_haste(20);
    // 3.30 = 1.0 * 1.1 * 1.5 * 2
    assert(delta(cstats->get_attack_speed_mod(), 3.30) < 0.0001);

    cstats->decrease_haste(10);
    // 3.00 = 1.0 * 1.5 * 2
    assert(delta(cstats->get_attack_speed_mod(), 3.00) < 0.0001);

    cstats->decrease_haste(100);
    // 1.50 = 1.0 * 1.5
    assert(delta(cstats->get_attack_speed_mod(), 1.50) < 0.0001);

    cstats->decrease_haste(50);
    // 1.00 = 1.0
    assert(delta(cstats->get_attack_speed_mod(), 1.00) < 0.0001);
}

void TestCharacterStats::test_physical_damage_multipliers_stacks_multiplicatively() {
    cstats->increase_total_phys_dmg_mod(10);
    // 1.2 = 1.0 * 1.2
    assert(delta(cstats->get_total_phys_dmg_mod(), 1.10) < 0.0001);

    cstats->increase_total_phys_dmg_mod(20);
    // 1.32 = 1.0 * 1.1 * 1.2
    assert(delta(cstats->get_total_phys_dmg_mod(), 1.32) < 0.0001);

    cstats->increase_total_phys_dmg_mod(50);
    // 1.98 = 1.0 * 1.1 * 1.2 * 1.5
    assert(delta(cstats->get_total_phys_dmg_mod(), 1.98) < 0.0001);

    cstats->increase_total_phys_dmg_mod(100);
    // 3.96 = 1.0 * 1.1 * 1.2 * 1.5 * 2
    assert(delta(cstats->get_total_phys_dmg_mod(), 3.96) < 0.0001);

    cstats->decrease_total_phys_dmg_mod(20);
    // 3.30 = 1.0 * 1.1 * 1.5 * 2
    assert(delta(cstats->get_total_phys_dmg_mod(), 3.30) < 0.0001);

    cstats->decrease_total_phys_dmg_mod(10);
    // 3.00 = 1.0 * 1.5 * 2
    assert(delta(cstats->get_total_phys_dmg_mod(), 3.00) < 0.0001);

    cstats->decrease_total_phys_dmg_mod(100);
    // 1.50 = 1.0 * 1.5
    assert(delta(cstats->get_total_phys_dmg_mod(), 1.50) < 0.0001);

    cstats->decrease_total_phys_dmg_mod(50);
    // 1.00 = 1.0
    assert(delta(cstats->get_total_phys_dmg_mod(), 1.00) < 0.0001);
}

void TestCharacterStats::test_physical_damage_taken_multipliers_stacks_multiplicatively() {
    cstats->add_phys_damage_taken_mod(-10);
    // 0.90 = 1.0 * 0.9
    assert(delta(cstats->get_physical_damage_taken_mod(), 0.90) < 0.0001);

    cstats->add_phys_damage_taken_mod(-20);
    // 0.72 = 1.0 * 0.9 * 0.8
    assert(delta(cstats->get_physical_damage_taken_mod(), 0.72) < 0.0001);

    cstats->add_phys_damage_taken_mod(-50);
    // 0.36 = 1.0 * 0.9 * 0.8 * 0.5
    assert(delta(cstats->get_physical_damage_taken_mod(), 0.36) < 0.0001);

    cstats->remove_phys_damage_taken_mod(-20);
    // 0.45 = 1.0 * 0.9 * 0.5
    assert(delta(cstats->get_physical_damage_taken_mod(), 0.45) < 0.0001);

    cstats->remove_phys_damage_taken_mod(-10);
    // 0.5 = 1.0 * 0.5
    assert(delta(cstats->get_physical_damage_taken_mod(), 0.50) < 0.0001);

    cstats->remove_phys_damage_taken_mod(-50);
    // 1.00 = 1.0
    assert(delta(cstats->get_physical_damage_taken_mod(), 1.00) < 0.0001);
}

void TestCharacterStats::test_spell_damage_taken_multipliers_stacks_multiplicatively() {
    cstats->add_spell_damage_taken_mod(-10);
    // 0.90 = 1.0 * 0.9
    assert(delta(cstats->get_spell_damage_taken_mod(), 0.90) < 0.0001);

    cstats->add_spell_damage_taken_mod(-20);
    // 0.72 = 1.0 * 0.9 * 0.8
    assert(delta(cstats->get_spell_damage_taken_mod(), 0.72) < 0.0001);

    cstats->add_spell_damage_taken_mod(-50);
    // 0.36 = 1.0 * 0.9 * 0.8 * 0.5
    assert(delta(cstats->get_spell_damage_taken_mod(), 0.36) < 0.0001);

    cstats->remove_spell_damage_taken_mod(-20);
    // 0.45 = 1.0 * 0.9 * 0.5
    assert(delta(cstats->get_spell_damage_taken_mod(), 0.45) < 0.0001);

    cstats->remove_spell_damage_taken_mod(-10);
    // 0.5 = 1.0 * 0.5
    assert(delta(cstats->get_spell_damage_taken_mod(), 0.50) < 0.0001);

    cstats->remove_spell_damage_taken_mod(-50);
    // 1.00 = 1.0
    assert(delta(cstats->get_spell_damage_taken_mod(), 1.00) < 0.0001);
}
