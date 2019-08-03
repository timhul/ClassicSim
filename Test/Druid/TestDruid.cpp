#include "TestDruid.h"

#include "CharacterStats.h"
#include "Druid.h"
#include "Equipment.h"
#include "Item.h"
#include "ItemNamespace.h"
#include "NightElf.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "TestBalance.h"
#include "TestCatForm.h"
#include "TestFeralCombat.h"
#include "TestMoonfire.h"
#include "TestMoonkinForm.h"
#include "TestRestorationDruid.h"
#include "TestShred.h"
#include "TestStarfire.h"
#include "TestWrath.h"

TestDruid::TestDruid(EquipmentDb* equipment_db):
    TestObject(equipment_db)
{}

void TestDruid::test_all() {
    test_values_after_initialization();

    TestBalance(equipment_db).test_all();
    TestFeralCombat(equipment_db).test_all();
    TestRestorationDruid(equipment_db).test_all();

    TestWrath(equipment_db).test_all();
    TestMoonfire(equipment_db).test_all();
    TestStarfire(equipment_db).test_all();
    TestMoonkinForm(equipment_db).test_all();
    TestCatForm(equipment_db).test_all();
    TestShred(equipment_db).test_all();
}

void TestDruid::test_values_after_initialization() {
    Race* race = new NightElf();
    auto sim_settings = new SimSettings();
    auto raid_control = new RaidControl(sim_settings);
    auto druid = new Druid(race, equipment_db, sim_settings, raid_control);

    assert(druid->class_name == "Druid");
    assert(druid->get_race()->get_name() == "Night Elf");
    assert(druid->get_highest_possible_armor_type() == ArmorTypes::LEATHER);
    assert(almost_equal(1.5, druid->global_cooldown()));
    assert(almost_equal(2.0, druid->get_stats()->get_melee_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, druid->get_stats()->get_spell_crit_dmg_mod()));

    delete race;
    delete druid;
    delete sim_settings;
    delete raid_control;
}
