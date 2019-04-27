#include "TestPaladin.h"

#include "CharacterStats.h"
#include "Human.h"
#include "ItemNamespace.h"
#include "Paladin.h"
#include "TestHolyPaladin.h"
#include "TestJudgement.h"
#include "TestMainhandAttackPaladin.h"
#include "TestProtectionPaladin.h"
#include "TestRetribution.h"
#include "TestSealOfTheCrusader.h"

TestPaladin::TestPaladin(EquipmentDb* equipment_db):
    TestObject(equipment_db)
{}

void TestPaladin::test_all() {
    test_values_after_initialization();

    TestHolyPaladin(equipment_db).test_all();
    TestProtectionPaladin(equipment_db).test_all();
    TestRetribution(equipment_db).test_all();

    TestMainhandAttackPaladin(equipment_db).test_all();
    TestSealOfTheCrusader(equipment_db).test_all();
    TestJudgement(equipment_db).test_all();
}

void TestPaladin::test_values_after_initialization() {
    Race* race = new Human();
    auto* paladin = new Paladin(race, equipment_db, nullptr);

    assert(paladin->get_name() == "Paladin");
    assert(paladin->get_race()->get_name() == "Human");
    assert(paladin->get_highest_possible_armor_type() == ArmorTypes::PLATE);
    assert(almost_equal(1.5, paladin->global_cooldown()));
    assert(almost_equal(2.0, paladin->get_stats()->get_melee_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, paladin->get_stats()->get_spell_crit_dmg_mod()));

    delete race;
    delete paladin;
}
