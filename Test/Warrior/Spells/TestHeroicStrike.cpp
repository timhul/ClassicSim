#include "TestHeroicStrike.h"

#include <cassert>

#include "Arms.h"
#include "Buff.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "Fury.h"
#include "HeroicStrike.h"
#include "Talent.h"
#include "WarriorSpells.h"

TestHeroicStrike::TestHeroicStrike(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Heroic Strike")
{}

void TestHeroicStrike::test_all() {
    run_mandatory_tests();

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

    set_up();
    test_miss_chance_while_dual_wielding();
    tear_down();

    set_up();
    test_flurry_charges_not_consumed();
    tear_down();
}

void TestHeroicStrike::test_name_correct() {
    assert(heroic_strike()->get_name() == "Heroic Strike");
}

void TestHeroicStrike::test_spell_cooldown() {
    assert(QString::number(heroic_strike()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestHeroicStrike::test_whether_spell_causes_global_cooldown() {
    assert(warrior->action_ready());

    when_heroic_strike_is_performed();

    assert(warrior->action_ready());
}

void TestHeroicStrike::test_how_spell_observes_global_cooldown() {
    given_warrior_has_rage(100);
    assert(heroic_strike()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(heroic_strike()->get_spell_status() == SpellStatus::Available);
}

void TestHeroicStrike::test_resource_cost() {
    then_heroic_strike_costs(15);
}

void TestHeroicStrike::test_is_ready_conditions() {
    given_warrior_in_battle_stance();
    given_warrior_has_rage(100);
    assert(heroic_strike()->get_spell_status() == SpellStatus::Available);

    given_warrior_in_berserker_stance();
    given_warrior_has_rage(100);
    assert(heroic_strike()->get_spell_status() == SpellStatus::Available);

    given_warrior_in_defensive_stance();
    given_warrior_has_rage(100);
    assert(heroic_strike()->get_spell_status() == SpellStatus::Available);
}

void TestHeroicStrike::test_stance_cooldown() {
    when_switching_to_berserker_stance();

    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);

    assert(heroic_strike()->get_spell_status() == SpellStatus::Available);
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
    const auto arms = Arms(warrior);
    Talent* improved_heroic_strike = arms.get_talent_from_name("Improved Heroic Strike");

    assert(improved_heroic_strike->increment_rank());
    assert(improved_heroic_strike->increment_rank());
    assert(improved_heroic_strike->increment_rank());

    assert(improved_heroic_strike->decrement_rank());
    then_heroic_strike_costs(13);

    assert(improved_heroic_strike->decrement_rank());
    then_heroic_strike_costs(14);

    assert(improved_heroic_strike->decrement_rank());
    then_heroic_strike_costs(15);
}

void TestHeroicStrike::test_hit_dmg() {
    given_target_has_0_armor();
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
    given_target_has_0_armor();
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
    given_target_has_0_armor();
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
    given_target_has_0_armor();
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

void TestHeroicStrike::test_miss_chance_while_dual_wielding() {
    given_1h_axe_equipped_in_mainhand(warrior);
    given_1h_axe_equipped_in_offhand(warrior);
    given_warrior_has_rage(100);
    assert(almost_equal(0.2448, pchar->get_combat_roll()->get_white_miss_chance(pchar->get_oh_wpn_skill())));
    assert(warrior->is_dual_wielding() == true);

    heroic_strike()->perform();
    assert(warrior->is_dual_wielding() == false);
    assert(almost_equal(0.056, pchar->get_combat_roll()->get_white_miss_chance(pchar->get_oh_wpn_skill())));

    when_heroic_strike_is_performed();
    assert(warrior->is_dual_wielding() == true);
    assert(almost_equal(0.2448, pchar->get_combat_roll()->get_white_miss_chance(pchar->get_oh_wpn_skill())));
}

void TestHeroicStrike::test_flurry_charges_not_consumed() {
    given_1h_axe_equipped_in_mainhand(warrior);
    given_a_guaranteed_melee_ability_hit();
    given_5_of_5_flurry();
    given_warrior_has_rage(100);
    flurry()->apply_buff();
    assert(flurry()->get_charges() == 3);

    when_heroic_strike_is_performed();

    assert(flurry()->get_charges() == 3);
}

void TestHeroicStrike::given_1_of_3_improved_hs() {
    given_arms_talent_with_rank("Improved Heroic Strike", 1);
}

void TestHeroicStrike::given_2_of_3_improved_hs() {
    given_arms_talent_with_rank("Improved Heroic Strike", 2);
}

void TestHeroicStrike::given_3_of_3_improved_hs() {
    given_arms_talent_with_rank("Improved Heroic Strike", 3);
}

void TestHeroicStrike::given_5_of_5_flurry() {
    const auto fury = Fury(warrior);
    given_talent_rank(fury, "Enrage", 5);
    given_talent_rank(fury, "Flurry", 5);

    warrior->prepare_set_of_combat_iterations();
}

void TestHeroicStrike::when_heroic_strike_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    heroic_strike()->calculate_damage();
}

void TestHeroicStrike::then_heroic_strike_costs(const unsigned rage) {
    warrior->lose_rage(warrior->get_resource_level(ResourceType::Rage));
    warrior->gain_rage(rage);
    assert(heroic_strike()->get_spell_status() == SpellStatus::Available);

    warrior->lose_rage(warrior->get_resource_level(ResourceType::Rage));
    warrior->gain_rage(rage - 1);
    assert(heroic_strike()->get_spell_status() == SpellStatus::InsufficientResources);
}

Buff* TestHeroicStrike::flurry() const {
    return static_cast<WarriorSpells*>(warrior->get_spells())->get_flurry();
}
