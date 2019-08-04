#include "TestFerociousBite.h"

#include "Buff.h"
#include "CatForm.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "FerociousBite.h"
#include "Shred.h"

TestFerociousBite::TestFerociousBite(EquipmentDb* equipment_db) :
    TestSpellDruid(equipment_db, "Ferocious Bite")
{}

void TestFerociousBite::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg();
    tear_down();

    set_up();
    test_ferocious_bite_spends_combo_points();
    tear_down();

    set_up();
    test_hit_dmg_feral_aggression_5_of_5();
    tear_down();

    set_up();
    test_crit_dmg_feral_aggression_5_of_5();
    tear_down();
}

void TestFerociousBite::test_name_correct() {
    assert(ferocious_bite()->get_name() == "Ferocious Bite");
}

void TestFerociousBite::test_spell_cooldown() {
    assert(almost_equal(0.0, ferocious_bite()->get_base_cooldown()));
}

void TestFerociousBite::test_whether_spell_causes_global_cooldown() {
    given_druid_in_cat_form();
    given_druid_has_combo_points(1);
    given_engine_priority_at(0.51);
    assert(druid->action_ready());

    when_ferocious_bite_is_performed();

    assert(!druid->action_ready());
}

void TestFerociousBite::test_how_spell_observes_global_cooldown() {
    given_druid_in_cat_form();
    given_druid_has_combo_points(1);
    given_engine_priority_at(0.51);
    assert(druid->action_ready());

    when_shred_is_performed();

    assert(ferocious_bite()->get_spell_status() == SpellStatus::OnGCD);
}

void TestFerociousBite::test_resource_cost() {
    given_druid_in_cat_form();
    given_druid_has_combo_points(1);
    given_a_guaranteed_melee_ability_hit();
    assert(druid->get_resource_level(ResourceType::Energy) == 100);
    given_engine_priority_at(0.51);

    when_ferocious_bite_is_performed();

    then_druid_has_energy(0);
}

void TestFerociousBite::test_is_ready_conditions() {
    assert(ferocious_bite()->get_spell_status() == SpellStatus::InCasterForm);

    given_druid_in_cat_form();
    given_engine_priority_at(0.51);

    assert(ferocious_bite()->get_spell_status() == SpellStatus::InsufficientComboPoints);

    given_druid_has_combo_points(1);
    assert(ferocious_bite()->get_spell_status() == SpellStatus::Available);
}

void TestFerociousBite::test_hit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_cat_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);
    given_druid_has_combo_points(5);

    when_ferocious_bite_is_performed();

    // [Damage] = [min - max] + combo_points * melee_ap * 3% + energy_conversion_factor * (curr_energy - resource_cost)
    // [1113 - 1173] = [787 - 847] + 5 * 1000 * 0.03 + 2.7 * (100 - 35)
    then_damage_dealt_is_in_range(1113, 1173);
}

void TestFerociousBite::test_crit_dmg() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_cat_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();
    given_engine_priority_at(0.51);
    given_druid_has_combo_points(5);

    when_ferocious_bite_is_performed();

    // [Damage] = ([min - max] + combo_points * melee_ap * 3% + energy_conversion_factor * (curr_energy - resource_cost)) * crit_dmg_modifier
    // [2225 - 2345] = ([787 - 847] + 5 * 1000 * 0.03 + 2.7 * (100 - 35)) * 2.0
    then_damage_dealt_is_in_range(2225, 2345);
}

void TestFerociousBite::test_ferocious_bite_spends_combo_points() {
    given_druid_in_cat_form();
    given_druid_has_combo_points(5);
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);

    when_ferocious_bite_is_performed();

    assert(druid->get_combo_points() == 0);
}

void TestFerociousBite::test_hit_dmg_feral_aggression_5_of_5() {
    given_feral_talent_rank("Feral Aggression", 5);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_cat_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);
    given_druid_has_combo_points(5);

    when_ferocious_bite_is_performed();

    // [Damage] = ([min - max] + combo_points * melee_ap * 3% + energy_conversion_factor * (curr_energy - resource_cost)) * feral_aggression_mod
    // [1279 - 1348] = ([787 - 847] + 5 * 1000 * 0.03 + 2.7 * (100 - 35)) * 1.15
    then_damage_dealt_is_in_range(1279, 1348);
}

void TestFerociousBite::test_crit_dmg_feral_aggression_5_of_5() {
    given_feral_talent_rank("Feral Aggression", 5);
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_druid_in_cat_form();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();
    given_engine_priority_at(0.51);
    given_druid_has_combo_points(5);

    when_ferocious_bite_is_performed();

    // [Damage] = ([min - max] + combo_points * melee_ap * 3% + energy_conversion_factor * (curr_energy - resource_cost)) * feral_aggression_mod * crit_dmg_modifier
    // [2559 - 2697] = ([787 - 847] + 5 * 1000 * 0.03 + 2.7 * (100 - 35)) * 1.15 * 2.0
    then_damage_dealt_is_in_range(2559, 2697);
}

void TestFerociousBite::when_ferocious_bite_is_performed() {
    ferocious_bite()->perform();
}

void TestFerociousBite::when_shred_is_performed() {
    shred()->perform();
}

void TestFerociousBite::given_druid_in_cat_form() {
    cat_form()->perform();
}
