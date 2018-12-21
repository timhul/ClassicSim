#include "TestRogue.h"

#include "Engine.h"
#include "Equipment.h"
#include "CombatRoll.h"
#include "Faction.h"
#include "InstantPoison.h"
#include "ItemNamespace.h"
#include "Orc.h"
#include "Rogue.h"
#include "Target.h"
#include "TestAdrenalineRush.h"
#include "TestBackstab.h"
#include "TestBladeFlurry.h"
#include "TestEnergy.h"
#include "TestEviscerate.h"
#include "TestRelentlessStrikes.h"
#include "TestSealFate.h"
#include "TestSinisterStrike.h"
#include "TestSliceAndDice.h"

#include "TestAssassination.h"
#include "TestCombat.h"

void TestRogue::test_all() {
    test_basic_properties();

    TestEnergy(equipment_db).test_all();

    TestAdrenalineRush(equipment_db).test_all();
    TestBackstab(equipment_db).test_all();
    TestBladeFlurry(equipment_db).test_all();
    TestEviscerate(equipment_db).test_all();
    TestSinisterStrike(equipment_db).test_all();
    TestSliceAndDice(equipment_db).test_all();

    TestRelentlessStrikes(equipment_db).test_all();
    TestSealFate(equipment_db).test_all();

    TestAssassination(equipment_db).test_all();
    TestCombat(equipment_db).test_all();
}

void TestRogue::test_basic_properties() {
    Race* race = new Orc();
    auto* rogue = new Rogue(race, equipment_db, nullptr);

    assert(rogue->get_name() == "Rogue");
    assert(rogue->get_race()->get_name() == "Orc");
    assert(rogue->get_highest_possible_armor_type() == ArmorTypes::LEATHER);
    assert(almost_equal(1.0, rogue->global_cooldown()));
    assert(almost_equal(2.0, rogue->get_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, rogue->get_spell_crit_dmg_mod()));

    rogue->get_mh_instant_poison()->enable();
    rogue->get_oh_instant_poison()->enable();

    delete race;
    delete rogue;
}
