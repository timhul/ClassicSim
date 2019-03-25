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
    test_surefooted();
    tear_down();

    set_up();
    test_killer_instinct();
    tear_down();

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

void TestHunterTalentStatIncrease::test_surefooted() {
    Talent* talent = Survival(hunter).get_surefooted();
    unsigned melee_hit_initial = pchar->get_stats()->get_melee_hit_chance();
    unsigned ranged_hit_initial = pchar->get_stats()->get_ranged_hit_chance();

    assert(talent->increment_rank());
    assert(melee_hit_initial + 1 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 1 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->increment_rank());
    assert(melee_hit_initial + 2 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 2 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->increment_rank());
    assert(melee_hit_initial + 3 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 3 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->decrement_rank());
    assert(melee_hit_initial + 2 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 2 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->decrement_rank());
    assert(melee_hit_initial + 1 == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial + 1 == pchar->get_stats()->get_ranged_hit_chance());

    assert(talent->decrement_rank());
    assert(melee_hit_initial == pchar->get_stats()->get_melee_hit_chance());
    assert(ranged_hit_initial == pchar->get_stats()->get_ranged_hit_chance());

    delete talent;
}

void TestHunterTalentStatIncrease::test_killer_instinct() {
    Talent* talent = Survival(hunter).get_killer_instinct();
    unsigned melee_crit_initial = pchar->get_stats()->get_mh_crit_chance();
    unsigned ranged_crit_initial = pchar->get_stats()->get_ranged_crit_chance();

    assert(talent->increment_rank());
    assert(melee_crit_initial + 100 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 100 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->increment_rank());
    assert(melee_crit_initial + 200 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 200 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->increment_rank());
    assert(melee_crit_initial + 300 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 300 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->decrement_rank());
    assert(melee_crit_initial + 200 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 200 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->decrement_rank());
    assert(melee_crit_initial + 100 == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial + 100 == pchar->get_stats()->get_ranged_crit_chance());

    assert(talent->decrement_rank());
    assert(melee_crit_initial == pchar->get_stats()->get_mh_crit_chance());
    assert(ranged_crit_initial == pchar->get_stats()->get_ranged_crit_chance());

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
