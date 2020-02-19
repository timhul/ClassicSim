#include "TestTwoHandedWeaponSpecialization.h"

#include <cassert>

#include "CharacterStats.h"
#include "Equipment.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "TwoHandedWeaponSpecialization.h"
#include "Warrior.h"
#include "Weapon.h"

TestTwoHandedWeaponSpecialization::TestTwoHandedWeaponSpecialization(EquipmentDb* equipment_db) :
    TestSpell(equipment_db, "Two-hand Specialization"), warrior(nullptr), talent(nullptr) {}

void TestTwoHandedWeaponSpecialization::set_up() {
    race = new Orc();
    sim_settings = new SimSettings();
    raid_control = new RaidControl(sim_settings);
    warrior = new Warrior(race, equipment_db, sim_settings, raid_control);
    talent = new TwoHandedWeaponSpecialization(warrior, nullptr);
}

void TestTwoHandedWeaponSpecialization::tear_down() {
    delete warrior;
    delete race;
    delete sim_settings;
    delete raid_control;
}

void TestTwoHandedWeaponSpecialization::test_all() {
    set_up();
    test_basic_properties();
    tear_down();

    set_up();
    test_damage_modified_when_using_2handers();
    tear_down();

    set_up();
    test_damage_not_modified_when_not_using_2handers();
    tear_down();

    set_up();
    test_damage_added_per_rank();
    tear_down();
}

void TestTwoHandedWeaponSpecialization::test_basic_properties() {
    assert(talent->get_name() == "Two-Handed Weapon Specialization");
}

void TestTwoHandedWeaponSpecialization::test_damage_modified_when_using_2handers() {
    given_no_mainhand(warrior);
    given_no_offhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    assert(talent->increment_rank());

    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_2h_axe_equipped(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.01));
    given_no_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_2h_sword_equipped(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.01));
    given_no_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_2h_mace_equipped(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.01));
    given_no_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_polearm_equipped(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.01));
    given_no_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_staff_equipped(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.01));
    given_no_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));
}

void TestTwoHandedWeaponSpecialization::test_damage_not_modified_when_not_using_2handers() {
    assert(talent->increment_rank());
    given_2h_axe_equipped(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.01));

    given_1h_axe_equipped_in_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_1h_mace_equipped_in_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_1h_sword_equipped_in_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_dagger_equipped_in_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    given_fist_weapon_equipped_in_mainhand(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));
}

void TestTwoHandedWeaponSpecialization::test_damage_added_per_rank() {
    given_2h_axe_equipped(warrior);
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));

    assert(talent->increment_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.01));

    assert(talent->increment_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.02));

    assert(talent->increment_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.03));

    assert(talent->increment_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.04));

    assert(talent->increment_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.05));

    assert(talent->decrement_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.04));

    assert(talent->decrement_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.03));

    assert(talent->decrement_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.02));

    assert(talent->decrement_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.01));

    assert(talent->decrement_rank());
    assert(almost_equal(warrior->get_stats()->get_total_physical_damage_mod(), 1.0));
}
