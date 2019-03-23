#include "TestMultiShot.h"

#include "Equipment.h"
#include "MultiShot.h"

TestMultiShot::TestMultiShot(EquipmentDb *equipment_db) :
    TestSpellHunter(equipment_db, "Multi-Shot")
{}

void TestMultiShot::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_mana_cost_1_of_5_efficiency();
    tear_down();

    set_up();
    test_mana_cost_2_of_5_efficiency();
    tear_down();

    set_up();
    test_mana_cost_3_of_5_efficiency();
    tear_down();

    set_up();
    test_mana_cost_4_of_5_efficiency();
    tear_down();

    set_up();
    test_mana_cost_5_of_5_efficiency();
    tear_down();
}

MultiShot* TestMultiShot::multi_shot() {
    auto* spells = dynamic_cast<HunterSpells*>(hunter->get_spells());
    return spells->get_multi_shot();
}

void TestMultiShot::test_name_correct() {
    assert(multi_shot()->get_name() == "Multi-Shot");
}

void TestMultiShot::test_spell_cooldown() {
    assert(almost_equal(10.0, multi_shot()->get_base_cooldown()));
}

void TestMultiShot::test_obeys_global_cooldown() {
    given_hunter_is_on_gcd();

    assert(!multi_shot()->is_available());
}

void TestMultiShot::test_resource_cost() {
    given_hunter_has_mana(230);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(229);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(230);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_is_ready_conditions() {
    // No conditions not tested in other mandatory tests.
}

void TestMultiShot::test_incurs_global_cooldown() {
    assert(hunter->action_ready());

    when_multi_shot_is_performed();

    assert(!hunter->action_ready());
}

void TestMultiShot::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_hit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();

    when_multi_shot_is_performed();

    // [Damage] = base_dmg + (normalized_wpn_speed * AP / 14) + flat_dmg_bonus
    // [300] = 100 + (2.8 * 1000 / 14) + 150
    then_damage_dealt_is(450);
}

void TestMultiShot::test_crit_dmg() {
    given_target_has_0_armor();
    given_a_ranged_weapon_with_100_min_max_dmg();
    given_a_guaranteed_ranged_white_crit();
    given_1000_ranged_ap();
    given_no_previous_damage_dealt();

    when_multi_shot_is_performed();

    // [Damage] = (base_dmg + (normalized_wpn_speed * AP / 14)) + flat_dmg_bonus) * crit_dmg_modifier
    // [900] = (100 + (2.8 * 1000 / 14) + 150) * 2.0
    then_damage_dealt_is(900);
}

void TestMultiShot::test_mana_cost_1_of_5_efficiency() {
    given_1_of_5_efficiency();
    given_hunter_has_mana(225);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(224);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(225);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_mana_cost_2_of_5_efficiency() {
    given_2_of_5_efficiency();
    given_hunter_has_mana(221);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(220);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(221);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_mana_cost_3_of_5_efficiency() {
    given_3_of_5_efficiency();
    given_hunter_has_mana(216);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(215);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(216);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_mana_cost_4_of_5_efficiency() {
    given_4_of_5_efficiency();
    given_hunter_has_mana(212);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(211);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(212);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::test_mana_cost_5_of_5_efficiency() {
    given_5_of_5_efficiency();
    given_hunter_has_mana(207);
    assert(multi_shot()->is_available());

    given_hunter_has_mana(206);
    assert(!multi_shot()->is_available());

    given_hunter_has_mana(207);

    when_multi_shot_is_performed();

    then_hunter_has_mana(0);
}

void TestMultiShot::when_multi_shot_is_performed() {
    if (pchar->get_equipment()->get_ranged() == nullptr)
        given_a_ranged_weapon_with_100_min_max_dmg();

    multi_shot()->perform();
}
