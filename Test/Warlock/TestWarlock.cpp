#include "TestWarlock.h"

#include "CharacterStats.h"
#include "Equipment.h"
#include "Item.h"
#include "ItemNamespace.h"
#include "Orc.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "TestAffliction.h"
#include "TestDemonology.h"
#include "TestDestruction.h"
#include "Warlock.h"

TestWarlock::TestWarlock(EquipmentDb* equipment_db_) : TestObject(equipment_db_) {}

void TestWarlock::test_all() {
    test_values_after_initialization();

    TestAffliction(equipment_db).test_all();
    TestDemonology(equipment_db).test_all();
    TestDestruction(equipment_db).test_all();
}

void TestWarlock::test_values_after_initialization() {
    Race* race = new Orc();
    auto sim_settings = new SimSettings();
    auto raid_control = new RaidControl(sim_settings);
    auto warlock = new Warlock(race, equipment_db, sim_settings, raid_control);

    assert(warlock->class_name == "Warlock");
    assert(warlock->get_race()->get_name() == "Orc");
    assert(warlock->get_highest_possible_armor_type() == ArmorTypes::CLOTH);
    assert(almost_equal(1.5, warlock->global_cooldown()));
    assert(almost_equal(2.0, warlock->get_stats()->get_melee_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, warlock->get_stats()->get_spell_crit_dmg_mod()));

    delete race;
    delete warlock;
    delete sim_settings;
    delete raid_control;
}
