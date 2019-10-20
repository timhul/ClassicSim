#include "TestBloodFury.h"

#include <cassert>

#include "BloodFury.h"
#include "CharacterStats.h"

TestBloodFury::TestBloodFury(EquipmentDb* equipment_db) :
    TestSpellWarrior(equipment_db, "Blood Fury")
{}

void TestBloodFury::test_all() {
    run_mandatory_tests();

    set_up();
    test_melee_ap_bonus();
    tear_down();

    set_up();
    test_does_not_yield_ranged_ap();
    tear_down();
}

BloodFury* TestBloodFury::blood_fury() const {
    return dynamic_cast<BloodFury*>(get_max_rank_spell_by_name("Blood Fury"));
}

void TestBloodFury::test_name_correct() {
    assert(blood_fury()->get_name() == "Blood Fury");
}

void TestBloodFury::test_spell_cooldown() {
    assert(almost_equal(blood_fury()->get_base_cooldown(), 120.0));
}

void TestBloodFury::test_stance_cooldown() {

}

void TestBloodFury::test_how_spell_observes_global_cooldown() {

}

void TestBloodFury::test_whether_spell_causes_global_cooldown() {

}

void TestBloodFury::test_resource_cost() {
    given_warrior_has_rage(0);

    assert(blood_fury()->get_spell_status() == SpellStatus::Available);
}

void TestBloodFury::test_is_ready_conditions() {

}

void TestBloodFury::test_melee_ap_bonus() {
    given_character_has_strength(1000);
    assert(pchar->get_stats()->get_melee_ap() == 2160);

    blood_fury()->perform();

    // [MeleeAp] = (base_melee_ap + str * ap_from_str) * 0.25
    // [540] = (160 + 1000 * 2) * 0.25
    assert(pchar->get_stats()->get_melee_ap() == 2160 + 540);
}

void TestBloodFury::test_does_not_yield_ranged_ap() {
    const unsigned ranged_ap_before = pchar->get_stats()->get_ranged_ap();

    blood_fury()->perform();

    assert(ranged_ap_before == pchar->get_stats()->get_ranged_ap());
}
