#include "TestShaman.h"

#include "CharacterStats.h"
#include "ItemNamespace.h"
#include "Orc.h"
#include "Shaman.h"
#include "TestElemental.h"
#include "TestEnhancement.h"
#include "TestLightningBolt.h"
#include "TestRestorationShaman.h"
#include "TestStormstrike.h"

TestShaman::TestShaman(EquipmentDb* equipment_db):
    TestObject(equipment_db)
{}

void TestShaman::test_all() {
    test_values_after_initialization();

    TestElemental(equipment_db).test_all();
    TestEnhancement(equipment_db).test_all();
    TestRestorationShaman(equipment_db).test_all();

    TestStormstrike(equipment_db).test_all();
    TestLightningBolt(equipment_db).test_all();
}

void TestShaman::test_values_after_initialization() {
    Race* race = new Orc();
    auto* shaman = new Shaman(race, equipment_db, nullptr);

    assert(shaman->get_name() == "Shaman");
    assert(shaman->get_race()->get_name() == "Orc");
    assert(shaman->get_highest_possible_armor_type() == ArmorTypes::MAIL);
    assert(almost_equal(1.5, shaman->global_cooldown()));
    assert(almost_equal(2.0, shaman->get_stats()->get_melee_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, shaman->get_stats()->get_spell_crit_dmg_mod()));

    delete race;
    delete shaman;
}
