#include "TestHunter.h"

#include "CharacterStats.h"
#include "Equipment.h"
#include "Hunter.h"
#include "ItemNamespace.h"
#include "Orc.h"
#include "Quiver.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "TestAimedShot.h"
#include "TestAutoShot.h"
#include "TestBeastMastery.h"
#include "TestHunterTalentStatIncrease.h"
#include "TestMarksmanship.h"
#include "TestMultiShot.h"
#include "TestSurvival.h"
#include "Weapon.h"

TestHunter::TestHunter(EquipmentDb* equipment_db):
    TestObject(equipment_db)
{}

void TestHunter::test_all() {
    test_values_after_initialization();

    TestAimedShot(equipment_db).test_all();
    TestAutoShot(equipment_db).test_all();
    TestMultiShot(equipment_db).test_all();
    TestHunterTalentStatIncrease(equipment_db).test_all();

    TestBeastMastery(equipment_db).test_all();
    TestMarksmanship(equipment_db).test_all();
    TestSurvival(equipment_db).test_all();
}

void TestHunter::test_values_after_initialization() {
    Race* race = new Orc();
    auto sim_settings = new SimSettings();
    auto raid_control = new RaidControl(sim_settings);
    auto hunter = new Hunter(race, equipment_db, sim_settings, raid_control);

    assert(hunter->class_name == "Hunter");
    assert(hunter->get_race()->get_name() == "Orc");
    assert(hunter->get_highest_possible_armor_type() == ArmorTypes::MAIL);
    assert(almost_equal(1.5, hunter->global_cooldown()));
    assert(almost_equal(2.0, hunter->get_stats()->get_melee_ability_crit_dmg_mod()));
    assert(almost_equal(2.0, hunter->get_stats()->get_ranged_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, hunter->get_stats()->get_spell_crit_dmg_mod()));

    // Test quiver bonus applies
    hunter->get_equipment()->set_ranged(19361);
    Weapon* wpn = hunter->get_equipment()->get_ranged();
    assert(wpn->name == "Ashjre'thul, Crossbow of Smiting");
    assert(almost_equal(3.4, hunter->get_stats()->get_ranged_wpn_speed()));
    hunter->get_equipment()->set_quiver(18714);
    assert(hunter->get_equipment()->get_quiver()->name == "Ancient Sinew Wrapped Lamina");
    assert(almost_equal(2.95652, hunter->get_stats()->get_ranged_wpn_speed()));

    delete race;
    delete hunter;
    delete raid_control;
    delete sim_settings;
}
