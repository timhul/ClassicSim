#include "TestMageTalentStatIncrease.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Fire.h"
#include "Talent.h"

TestMageTalentStatIncrease::TestMageTalentStatIncrease(EquipmentDb* equipment_db) :
    TestSpellMage(equipment_db, "MageTalentStatIncrease")
{}

void TestMageTalentStatIncrease::test_all() {
    run_mandatory_tests();

    set_up();
    test_fire_power();
    tear_down();
}

void TestMageTalentStatIncrease::test_fire_power() {
    auto tree = Fire(mage);
    Talent* talent = tree.get_talent_from_name("Fire Power");

    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->increment_rank();
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->increment_rank();
    assert(almost_equal(1.04, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->increment_rank();
    assert(almost_equal(1.06, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->increment_rank();
    assert(almost_equal(1.08, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->increment_rank();
    assert(almost_equal(1.10, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->decrement_rank();
    assert(almost_equal(1.08, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->decrement_rank();
    assert(almost_equal(1.06, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->decrement_rank();
    assert(almost_equal(1.04, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->decrement_rank();
    assert(almost_equal(1.02, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));

    talent->decrement_rank();
    assert(almost_equal(1.0, pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire)));
}

void TestMageTalentStatIncrease::test_name_correct() {
}

void TestMageTalentStatIncrease::test_spell_cooldown() {
}

void TestMageTalentStatIncrease::test_how_spell_observes_global_cooldown() {
}

void TestMageTalentStatIncrease::test_resource_cost() {
}

void TestMageTalentStatIncrease::test_is_ready_conditions() {
}

void TestMageTalentStatIncrease::test_whether_spell_causes_global_cooldown() {
}
