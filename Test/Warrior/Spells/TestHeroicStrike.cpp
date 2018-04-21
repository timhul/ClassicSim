
#include "TestHeroicStrike.h"
#include "HeroicStrike.h"

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
}

void TestHeroicStrike::test_name_correct() {
    assert(warrior->get_heroic_strike()->get_name() == "Heroic Strike");
}

void TestHeroicStrike::test_has_no_cooldown() {
    assert(QString::number(warrior->get_heroic_strike()->get_cooldown(), 'f', 3) == "0.000");
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
    warrior->get_heroic_strike()->decrease_effect_via_talent();

    then_heroic_strike_costs(13);

    warrior->get_heroic_strike()->decrease_effect_via_talent();

    then_heroic_strike_costs(14);

    warrior->get_heroic_strike()->decrease_effect_via_talent();

    then_heroic_strike_costs(15);
}

void TestHeroicStrike::test_hit_dmg() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_heroic_strike_is_performed();

    then_damage_dealt_is(warrior->get_normalized_dmg(100, warrior->get_mh_wpn_speed()) + 157);
}

void TestHeroicStrike::test_crit_dmg_0_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_heroic_strike_is_performed();

    then_damage_dealt_is(round((warrior->get_normalized_dmg(100, warrior->get_mh_wpn_speed()) + 157) * 2));
}

void TestHeroicStrike::test_crit_dmg_1_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_heroic_strike_is_performed();

    then_damage_dealt_is(round((warrior->get_normalized_dmg(100, warrior->get_mh_wpn_speed()) + 157) * 2.1));
}

void TestHeroicStrike::test_crit_dmg_2_of_2_impale() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_heroic_strike_is_performed();

    then_damage_dealt_is(round((warrior->get_normalized_dmg(100, warrior->get_mh_wpn_speed()) + 157) * 2.2));
}

void TestHeroicStrike::given_0_of_3_improved_hs() {
    then_heroic_strike_costs(15);
}

void TestHeroicStrike::given_1_of_3_improved_hs() {
    warrior->get_heroic_strike()->increase_effect_via_talent();
}

void TestHeroicStrike::given_2_of_3_improved_hs() {
    warrior->get_heroic_strike()->increase_effect_via_talent();
    warrior->get_heroic_strike()->increase_effect_via_talent();
}

void TestHeroicStrike::given_3_of_3_improved_hs() {
    warrior->get_heroic_strike()->increase_effect_via_talent();
    warrior->get_heroic_strike()->increase_effect_via_talent();
    warrior->get_heroic_strike()->increase_effect_via_talent();
}

void TestHeroicStrike::when_heroic_strike_is_performed() {
    warrior->get_heroic_strike()->perform(100);
}

void TestHeroicStrike::then_heroic_strike_costs(const int rage) {
    assert(warrior->get_heroic_strike()->is_available(rage));
    assert(!warrior->get_heroic_strike()->is_available(rage - 1));
}
