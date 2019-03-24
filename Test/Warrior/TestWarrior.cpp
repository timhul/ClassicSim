#include "TestWarrior.h"

#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Engine.h"
#include "Equipment.h"
#include "Faction.h"
#include "ItemNamespace.h"
#include "Orc.h"
#include "Target.h"
#include "TestArms.h"
#include "TestBerserkerStance.h"
#include "TestBloodrage.h"
#include "TestBloodthirst.h"
#include "TestDeathWish.h"
#include "TestDeepWounds.h"
#include "TestExecute.h"
#include "TestFlurryWarrior.h"
#include "TestFury.h"
#include "TestHeroicStrike.h"
#include "TestMainhandAttackWarrior.h"
#include "TestMortalStrike.h"
#include "TestOffhandAttackWarrior.h"
#include "TestOverpower.h"
#include "TestRecklessness.h"
#include "TestRend.h"
#include "TestSlam.h"
#include "TestSwordSpecialization.h"
#include "TestTwoHandedWeaponSpecialization.h"
#include "TestUnbridledWrath.h"
#include "TestWhirlwind.h"
#include "Warrior.h"

TestWarrior::TestWarrior(EquipmentDb* equipment_db):
    TestObject(equipment_db)
{}

void TestWarrior::test_all() {
    test_values_after_initialization();

    TestExecute(equipment_db).test_all();
    TestHeroicStrike(equipment_db).test_all();
    TestBloodthirst(equipment_db).test_all();
    TestMainhandAttackWarrior(equipment_db).test_all();
    TestOffhandAttackWarrior(equipment_db).test_all();
    TestWhirlwind(equipment_db).test_all();
    TestOverpower(equipment_db).test_all();
    TestFlurryWarrior(equipment_db).test_all();
    TestDeepWounds(equipment_db).test_all();
    TestBloodrage(equipment_db).test_all();
    TestRecklessness(equipment_db).test_all();
    TestBerserkerStance(equipment_db).test_all();
    TestDeathWish(equipment_db).test_all();
    TestMortalStrike(equipment_db).test_all();
    TestSlam(equipment_db).test_all();
    TestRend(equipment_db).test_all();

    TestUnbridledWrath(equipment_db).test_all();
    TestSwordSpecialization(equipment_db).test_all();

    TestTwoHandedWeaponSpecialization(equipment_db).test_all();

    TestArms(equipment_db).test_all();
    TestFury(equipment_db).test_all();
}

void TestWarrior::test_values_after_initialization() {
    Race* race = new Orc();
    auto* warr = new Warrior(race, equipment_db, nullptr);

    assert(warr->get_name() == "Warrior");
    assert(warr->get_race()->get_name() == "Orc");
    assert(warr->get_highest_possible_armor_type() == ArmorTypes::PLATE);
    assert(almost_equal(1.5, warr->global_cooldown()));
    assert(almost_equal(1.0, warr->stance_cooldown()));
    assert(almost_equal(2.0, warr->get_stats()->get_melee_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, warr->get_stats()->get_spell_crit_dmg_mod()));

    delete race;
    delete warr;
}
