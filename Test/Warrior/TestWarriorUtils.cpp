
#include "TestWarriorUtils.h"
#include "Warrior.h"
#include "CharacterStats.h"
#include "Equipment.h"
#include "Weapon.h"

void TestWarriorUtils:: given_warrior_has_1h_axe_equipped_in_mainhand(Warrior* warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Zulian Hacker");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::AXE);
}

void TestWarriorUtils:: given_warrior_has_1h_mace_equipped_in_mainhand(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Anubisath Warhammer");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::MACE);
}

void TestWarriorUtils:: given_warrior_has_1h_sword_equipped_in_mainhand(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Skullforge Reaver");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::SWORD);
}

void TestWarriorUtils:: given_warrior_has_fist_weapon_equipped_in_mainhand(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Claw of the Black Drake");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::FIST);
}

void TestWarriorUtils:: given_warrior_has_dagger_equipped_in_mainhand(Warrior* warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Alcor's Sunrazor");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::DAGGER);
}

void TestWarriorUtils:: given_warrior_has_no_mainhand(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->clear_mainhand();
    assert(warrior->get_stats()->get_equipment()->get_mainhand() == nullptr);
}

void TestWarriorUtils:: given_warrior_has_1h_axe_equipped_in_offhand(Warrior* warrior) {
    warrior->get_stats()->get_equipment()->set_offhand("Zulian Hacker");
    assert(warrior->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::AXE);
}

void TestWarriorUtils:: given_warrior_has_1h_mace_equipped_in_offhand(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_offhand("Anubisath Warhammer");
    assert(warrior->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::MACE);
}

void TestWarriorUtils:: given_warrior_has_1h_sword_equipped_in_offhand(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_offhand("Skullforge Reaver");
    assert(warrior->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::SWORD);
}

void TestWarriorUtils:: given_warrior_has_fist_weapon_equipped_in_offhand(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_offhand("Arlokk's Grasp");
    assert(warrior->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::FIST);
}

void TestWarriorUtils:: given_warrior_has_dagger_equipped_in_offhand(Warrior* warrior) {
    warrior->get_stats()->get_equipment()->set_offhand("Alcor's Sunrazor");
    assert(warrior->get_stats()->get_equipment()->get_offhand()->get_weapon_type() == WeaponTypes::DAGGER);
}

void TestWarriorUtils:: given_warrior_has_no_offhand(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->clear_offhand();
    assert(warrior->get_stats()->get_equipment()->get_offhand() == nullptr);
}

void TestWarriorUtils:: given_warrior_has_2h_axe_equipped(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Arcanite Reaper");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_AXE);
}

void TestWarriorUtils:: given_warrior_has_2h_mace_equipped(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Earthshaker");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_MACE);
}

void TestWarriorUtils:: given_warrior_has_2h_sword_equipped(Warrior* warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Ashkandi, Greatsword of the Brotherhood");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::TWOHAND_SWORD);
}

void TestWarriorUtils:: given_warrior_has_polearm_equipped(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Barb of the Sand Reaver");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::POLEARM);
}

void TestWarriorUtils:: given_warrior_has_staff_equipped(Warrior *warrior) {
    warrior->get_stats()->get_equipment()->set_mainhand("Resurgence Rod");
    assert(warrior->get_stats()->get_equipment()->get_mainhand()->get_weapon_type() == WeaponTypes::STAFF);
}
