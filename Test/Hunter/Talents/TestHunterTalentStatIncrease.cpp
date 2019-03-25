#include "TestHunterTalentStatIncrease.h"

#include "CharacterStats.h"
#include "Survival.h"
#include "Talent.h"

TestHunterTalentStatIncrease::TestHunterTalentStatIncrease(EquipmentDb* equipment_db) :
    TestSpellHunter(equipment_db, "Mana")
{}

void TestHunterTalentStatIncrease::test_all() {
    run_mandatory_tests();

    set_up();
    test_lightning_reflexes();
    tear_down();
}

void TestHunterTalentStatIncrease::test_lightning_reflexes() {
    Talent* talent = Survival(hunter).get_lightning_reflexes();
    given_character_has_agility(100);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_agility() == 103);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_agility() == 106);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_agility() == 109);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_agility() == 112);

    assert(talent->increment_rank());
    assert(pchar->get_stats()->get_agility() == 115);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_agility() == 112);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_agility() == 109);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_agility() == 106);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_agility() == 103);

    assert(talent->decrement_rank());
    assert(pchar->get_stats()->get_agility() == 100);

    delete talent;
}

void TestHunterTalentStatIncrease::test_name_correct() {
}

void TestHunterTalentStatIncrease::test_spell_cooldown() {
}

void TestHunterTalentStatIncrease::test_obeys_global_cooldown() {
}

void TestHunterTalentStatIncrease::test_resource_cost() {
}

void TestHunterTalentStatIncrease::test_is_ready_conditions() {
}

void TestHunterTalentStatIncrease::test_incurs_global_cooldown() {
}
