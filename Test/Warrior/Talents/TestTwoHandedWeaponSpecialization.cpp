
#include "TestTwoHandedWeaponSpecialization.h"
#include "TwoHandedWeaponSpecialization.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Weapon.h"
#include "Orc.h"

TestTwoHandedWeaponSpecialization::TestTwoHandedWeaponSpecialization(EquipmentDb* equipment_db) :
    equipment_db(equipment_db),
    warrior(nullptr)
{}

void TestTwoHandedWeaponSpecialization::set_up() {
    race = new Orc();
    warrior = new Warrior(race, equipment_db);
    talent = new TwoHandedWeaponSpecialization(warrior, nullptr);
}

void TestTwoHandedWeaponSpecialization::tear_down() {
    delete warrior;
    delete race;
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
    given_warrior_has_no_mainhand();
    given_warrior_has_no_offhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    assert(talent->increment_rank());

    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_2h_axe_equipped();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.01) < 0.0001);
    given_warrior_has_no_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_2h_sword_equipped();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.01) < 0.0001);
    given_warrior_has_no_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_2h_mace_equipped();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.01) < 0.0001);
    given_warrior_has_no_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_polearm_equipped();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.01) < 0.0001);
    given_warrior_has_no_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_staff_equipped();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.01) < 0.0001);
    given_warrior_has_no_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);
}

void TestTwoHandedWeaponSpecialization::test_damage_not_modified_when_not_using_2handers() {
    assert(talent->increment_rank());
    given_warrior_has_2h_axe_equipped();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.01) < 0.0001);

    given_warrior_has_1h_axe_equipped_in_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_1h_mace_equipped_in_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_1h_sword_equipped_in_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_dagger_equipped_in_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    given_warrior_has_fist_weapon_equipped_in_mainhand();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);
}

void TestTwoHandedWeaponSpecialization::test_damage_added_per_rank() {
    given_warrior_has_2h_axe_equipped();
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);

    assert(talent->increment_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.01) < 0.0001);

    assert(talent->increment_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.02) < 0.0001);

    assert(talent->increment_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.03) < 0.0001);

    assert(talent->increment_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.04) < 0.0001);

    assert(talent->increment_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.05) < 0.0001);

    assert(talent->decrement_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.04) < 0.0001);

    assert(talent->decrement_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.03) < 0.0001);

    assert(talent->decrement_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.02) < 0.0001);

    assert(talent->decrement_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.01) < 0.0001);

    assert(talent->decrement_rank());
    assert(delta(warrior->get_stats()->get_total_phys_dmg_mod(), 1.0) < 0.0001);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_1h_axe_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Frostbite");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::AXE);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_1h_mace_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Spineshatter");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::MACE);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_1h_sword_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Skullforge Reaver");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::SWORD);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_fist_weapon_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Claw of the Black Drake");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::FIST);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_dagger_equipped_in_mainhand() {
    warrior->get_stats()->get_equipment()->set_mainhand("Alcor's Sunrazor");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::DAGGER);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_no_mainhand() {
    warrior->get_stats()->get_equipment()->clear_mainhand();
    assert(warrior->get_stats()->get_equipment()->get_mainhand() == nullptr);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_no_offhand() {
    warrior->get_stats()->get_equipment()->clear_offhand();
    assert(warrior->get_stats()->get_equipment()->get_offhand() == nullptr);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_2h_axe_equipped() {
    warrior->get_stats()->get_equipment()->set_mainhand("Arcanite Reaper");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_AXE);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_2h_mace_equipped() {
    warrior->get_stats()->get_equipment()->set_mainhand("Earthshaker");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_MACE);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_2h_sword_equipped() {
    warrior->get_stats()->get_equipment()->set_mainhand("Ashkandi, Greatsword of the Brotherhood");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_SWORD);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_polearm_equipped() {
    warrior->get_stats()->get_equipment()->set_mainhand("Barb of the Sand Reaver");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::POLEARM);
}

void TestTwoHandedWeaponSpecialization:: given_warrior_has_staff_equipped() {
    warrior->get_stats()->get_equipment()->set_mainhand("Resurgence Rod");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::STAFF);
}

double TestTwoHandedWeaponSpecialization::delta(double lhs, double rhs) {
    return (lhs - rhs) < 0 ?  (lhs - rhs) * - 1 : (lhs - rhs);
}


