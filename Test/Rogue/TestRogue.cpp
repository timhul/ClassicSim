#include "TestBackstab.h"
#include "TestRogue.h"
#include "TestEnergy.h"
#include "TestEviscerate.h"
#include "TestSliceAndDice.h"

#include "Rogue.h"
#include "Orc.h"

#include "Engine.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "Faction.h"
#include "ItemNamespace.h"

void TestRogue::test_all() {
    test_basic_properties();

    TestEnergy(equipment_db).test_all();
    TestBackstab(equipment_db).test_all();
    TestEviscerate(equipment_db).test_all();
    TestSliceAndDice(equipment_db).test_all();
}

void TestRogue::test_basic_properties() {
    Race* race = new Orc();
    auto* rogue = new Rogue(race, equipment_db, nullptr);

    assert(rogue->get_name() == "Rogue");
    assert(rogue->get_race()->get_name() == "Orc");
    assert(rogue->get_highest_possible_armor_type() == ArmorTypes::LEATHER);
    assert(delta(1.0, rogue->global_cooldown()) < 0.0001);
    assert(delta(2.0, rogue->get_ability_crit_dmg_mod()) < 0.0001);
    assert(delta(1.5, rogue->get_spell_crit_dmg_mod()) < 0.0001);

    delete race;
    delete rogue;
}
