#include "TestPaladin.h"

#include "CharacterStats.h"
#include "Human.h"
#include "ItemNamespace.h"
#include "Paladin.h"
#include "RaidControl.h"
#include "SimSettings.h"
#include "TestConsecration.h"
#include "TestHolyPaladin.h"
#include "TestJudgement.h"
#include "TestMainhandAttackPaladin.h"
#include "TestPaladinTalentStatIncrease.h"
#include "TestProtectionPaladin.h"
#include "TestRetribution.h"
#include "TestSealOfCommand.h"
#include "TestSealOfTheCrusader.h"

TestPaladin::TestPaladin(EquipmentDb* equipment_db):
    TestObject(equipment_db)
{}

void TestPaladin::test_all() {
    test_values_after_initialization();

    TestHolyPaladin(equipment_db).test_all();
    TestProtectionPaladin(equipment_db).test_all();
    TestRetribution(equipment_db).test_all();

    TestConsecration(equipment_db).test_all();
    TestJudgement(equipment_db).test_all();
    TestMainhandAttackPaladin(equipment_db).test_all();
    TestPaladinTalentStatIncrease(equipment_db).test_all();
    TestSealOfCommand(equipment_db).test_all();
    TestSealOfTheCrusader(equipment_db).test_all();
}

void TestPaladin::test_values_after_initialization() {
    Race* race = new Human();
    auto* sim_settings = new SimSettings();
    auto* raid_control = new RaidControl(sim_settings);
    auto* paladin = new Paladin(race, equipment_db, sim_settings, raid_control);

    assert(paladin->class_name == "Paladin");
    assert(paladin->get_race()->get_name() == "Human");
    assert(paladin->get_highest_possible_armor_type() == ArmorTypes::PLATE);
    assert(almost_equal(1.5, paladin->global_cooldown()));
    assert(almost_equal(2.0, paladin->get_stats()->get_melee_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, paladin->get_stats()->get_spell_crit_dmg_mod()));

    delete race;
    delete paladin;
    delete sim_settings;
    delete raid_control;
}
