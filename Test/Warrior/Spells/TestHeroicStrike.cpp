
#include "TestHeroicStrike.h"
#include "HeroicStrike.h"

TestHeroicStrike::TestHeroicStrike() :
    TestSpellWarrior("Heroic Strike")
{}

void TestHeroicStrike::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_no_cooldown();
    tear_down();

    set_up();
    test_does_not_incur_global_cooldown_on_use();
    tear_down();

    set_up();
    test_1_of_3_improved_hs_reduces_rage_cost();
    tear_down();

    set_up();
    test_2_of_3_improved_hs_reduces_rage_cost();
    tear_down();

    set_up();
    test_3_of_3_improved_hs_reduces_rage_cost();
    tear_down();

    set_up();
    test_removing_points_in_improved_hs_increases_rage_cost();
    tear_down();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_crit_dmg_0_of_2_impale();
    tear_down();

    set_up();
    test_crit_dmg_1_of_2_impale();
    tear_down();

    set_up();
    test_crit_dmg_2_of_2_impale();
    tear_down();

    set_up();
    test_dodge_applies_overpower_buff();
    tear_down();
}

HeroicStrike* TestHeroicStrike::heroic_strike() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_heroic_strike();
}

void TestHeroicStrike::test_name_correct() {
    assert(heroic_strike()->get_name() == "Heroic Strike");
}

void TestHeroicStrike::test_has_no_cooldown() {
    assert(QString::number(heroic_strike()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestHeroicStrike::test_does_not_incur_global_cooldown_on_use() {
    assert(warrior->action_ready());

    when_heroic_strike_is_performed();

    assert(warrior->action_ready());
}

void TestHeroicStrike::test_1_of_3_improved_hs_reduces_rage_cost() {
    given_1_of_3_improved_hs();

    then_heroic_strike_costs(14);
}

void TestHeroicStrike::test_2_of_3_improved_hs_reduces_rage_cost() {
    given_2_of_3_improved_hs();

    then_heroic_strike_costs(13);
}

void TestHeroicStrike::test_3_of_3_improved_hs_reduces_rage_cost() {
    given_3_of_3_improved_hs();

    then_heroic_strike_costs(12);
}

void TestHeroicStrike::test_removing_points_in_improved_hs_increases_rage_cost() {
    given_3_of_3_improved_hs();
    heroic_strike()->decrease_effect_via_talent();

    then_heroic_strike_costs(13);

    heroic_strike()->decrease_effect_via_talent();

    then_heroic_strike_costs(14);

    heroic_strike()->decrease_effect_via_talent();

    then_heroic_strike_costs(15);
}

void TestHeroicStrike::test_hit_dmg() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_hit();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_heroic_strike_is_performed();

    // [Damage] = base_dmg + (wpn_speed * AP / 14) + hs_flat_dmg
    // [443] = 100 + (2.6 * 1000 / 14) + 157
    then_damage_dealt_is(443);
}

void TestHeroicStrike::test_crit_dmg_0_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_heroic_strike_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14) + hs_flat_dmg) * crit_dmg_modifier
    // [885] = (100 + (2.6 * 1000 / 14) + 157) * 2
    then_damage_dealt_is(885);
}
void TestHeroicStrike::test_crit_dmg_1_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_heroic_strike_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14) + hs_flat_dmg) * crit_dmg_modifier
    // [930] = (100 + (2.6 * 1000 / 14) + 157) * 2.1
    then_damage_dealt_is(930);
}

void TestHeroicStrike::test_crit_dmg_2_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_1000_melee_ap();
    given_a_guaranteed_melee_ability_crit();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_heroic_strike_is_performed();

    // [Damage] = (base_dmg + (wpn_speed * AP / 14) + hs_flat_dmg) * crit_dmg_modifier
    // [974] = (100 + (2.6 * 1000 / 14) + 157) * 2.2
    then_damage_dealt_is(974);
}

void TestHeroicStrike::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_melee_ability_dodge();

    when_heroic_strike_is_performed();

    then_overpower_is_active();
}

void TestHeroicStrike::given_0_of_3_improved_hs() {
    then_heroic_strike_costs(15);
}

void TestHeroicStrike::given_1_of_3_improved_hs() {
    heroic_strike()->increase_effect_via_talent();
}

void TestHeroicStrike::given_2_of_3_improved_hs() {
    heroic_strike()->increase_effect_via_talent();
    heroic_strike()->increase_effect_via_talent();
}

void TestHeroicStrike::given_3_of_3_improved_hs() {
    heroic_strike()->increase_effect_via_talent();
    heroic_strike()->increase_effect_via_talent();
    heroic_strike()->increase_effect_via_talent();
}

void TestHeroicStrike::when_heroic_strike_is_performed() {
    heroic_strike()->calculate_damage();
}

void TestHeroicStrike::then_heroic_strike_costs(const int rage) {
    warrior->lose_rage(warrior->get_curr_rage());
    warrior->gain_rage(rage);
    assert(heroic_strike()->is_available());

    warrior->lose_rage(warrior->get_curr_rage());
    warrior->gain_rage(rage - 1);
    assert(!heroic_strike()->is_available());
}
