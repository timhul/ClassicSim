
#include "TestWarrior.h"

#include "Warrior.h"
#include "Orc.h"

#include "Engine.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "Faction.h"
#include "ItemNamespace.h"
#include "TestExecute.h"
#include "TestHeroicStrike.h"
#include "TestBloodthirst.h"
#include "TestMainhandAttackWarrior.h"
#include "TestOffhandAttackWarrior.h"
#include "TestWhirlwind.h"
#include "TestOverpower.h"
#include "TestFlurryWarrior.h"
#include "TestDeepWounds.h"
#include "TestBloodrage.h"
#include "TestRecklessness.h"
#include "TestBerserkerStance.h"
#include "TestDeathWish.h"
#include "TestMortalStrike.h"
#include "TestSlam.h"
#include "TestRend.h"

#include "TestSwordSpecialization.h"
#include "TestUnbridledWrath.h"

#include "TestTwoHandedWeaponSpecialization.h"

#include "TestArms.h"
#include "TestFury.h"

void TestWarrior::test_all() {
    test_basic_properties();

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

void TestWarrior::test_basic_properties() {
    Race* race = new Orc();
    auto* warr = new Warrior(race, equipment_db, nullptr);

    assert(warr->get_name() == "Warrior");
    assert(warr->get_race()->get_name() == "Orc");
    assert(warr->get_highest_possible_armor_type() == ArmorTypes::PLATE);
    assert(almost_equal(1.5, warr->global_cooldown()));
    assert(almost_equal(1.0, warr->stance_cooldown()));
    assert(almost_equal(2.0, warr->get_ability_crit_dmg_mod()));
    assert(almost_equal(1.5, warr->get_spell_crit_dmg_mod()));

    delete race;
    delete warr;
}
