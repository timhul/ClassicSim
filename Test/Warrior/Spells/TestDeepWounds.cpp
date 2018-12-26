#include "TestDeepWounds.h"

#include "Bloodthirst.h"
#include "ClassStatistics.h"
#include "DeepWounds.h"
#include "DeepWoundsTalent.h"
#include "Engine.h"
#include "Equipment.h"
#include "HeroicStrike.h"
#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include "Overpower.h"
#include "Queue.h"
#include "Whirlwind.h"

TestDeepWounds::TestDeepWounds(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Deep Wounds")
{}

void TestDeepWounds::test_all() {
    const bool prepare_combat_iterations = false;
    run_mandatory_tests(prepare_combat_iterations);

    set_up(prepare_combat_iterations);
    test_critical_mh_attack_applies_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_critical_oh_attack_applies_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_critical_bloodthirst_applies_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_critical_whirlwind_applies_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_critical_heroic_strike_applies_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_critical_overpower_applies_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_regular_hit_mh_attack_does_not_apply_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_regular_hit_oh_attack_does_not_apply_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_regular_hit_bloodthirst_does_not_apply_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_regular_hit_whirlwind_does_not_apply_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_regular_hit_heroic_strike_does_not_apply_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_regular_hit_overpower_does_not_apply_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_damage_of_1_of_3_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_damage_of_2_of_3_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_damage_of_3_of_3_deep_wounds();
    tear_down();

    set_up(prepare_combat_iterations);
    test_damage_stacks_when_multiple_crits_occur();
    tear_down();
}

DeepWounds* TestDeepWounds::deep_wounds() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_deep_wounds();
}

void TestDeepWounds::test_name_correct() {
    assert(deep_wounds()->get_name() == "Deep Wounds");
}

void TestDeepWounds::test_spell_cooldown() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_deep_wounds_enabled();

    when_mh_attack_is_performed();

    assert(warrior->action_ready());
}

void TestDeepWounds::test_incurs_global_cooldown() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_deep_wounds_enabled();

    when_mh_attack_is_performed();

    assert(deep_wounds()->is_ready());
}

void TestDeepWounds::test_obeys_global_cooldown() {
    given_deep_wounds_enabled();
    assert(deep_wounds()->is_available());

    given_warrior_is_on_gcd();

    assert(deep_wounds()->is_available());
}

void TestDeepWounds::test_resource_cost() {
    given_deep_wounds_enabled();
    given_warrior_has_rage(0);
    assert(deep_wounds()->is_available());
}

void TestDeepWounds::test_critical_mh_attack_applies_deep_wounds() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_mh_attack_is_performed();

    then_deep_wounds_is_applied();
}

void TestDeepWounds::test_is_ready_conditions() {
    // No conditions not tested in other mandatory tests.
}

void TestDeepWounds::test_stance_cooldown() {
    given_deep_wounds_enabled();
    when_switching_to_berserker_stance();

    assert(warrior->on_stance_cooldown() == true);

    assert(deep_wounds()->is_available());
}

void TestDeepWounds::test_critical_oh_attack_applies_deep_wounds() {
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(warrior->get_spells()->get_oh_attack());

    then_deep_wounds_is_applied();
}

void TestDeepWounds::test_critical_bloodthirst_applies_deep_wounds() {
    given_a_guaranteed_melee_ability_crit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_bloodthirst());

    then_deep_wounds_is_applied();
}

void TestDeepWounds::test_critical_whirlwind_applies_deep_wounds() {
    given_a_guaranteed_melee_ability_crit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_whirlwind());

    then_deep_wounds_is_applied();
}

void TestDeepWounds::test_critical_heroic_strike_applies_deep_wounds() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_heroic_strike()->calculate_damage();

    then_deep_wounds_is_applied();
}

void TestDeepWounds::test_critical_overpower_applies_deep_wounds() {
    given_a_guaranteed_melee_ability_crit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_overpower());

    then_deep_wounds_is_applied();
}

void TestDeepWounds::test_regular_hit_mh_attack_does_not_apply_deep_wounds() {
    given_a_guaranteed_white_hit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_mh_attack_is_performed();

    then_deep_wounds_is_not_applied();
}

void TestDeepWounds::test_regular_hit_oh_attack_does_not_apply_deep_wounds() {
    given_an_offhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_hit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(warrior->get_spells()->get_oh_attack());

    then_deep_wounds_is_not_applied();
}

void TestDeepWounds::test_regular_hit_bloodthirst_does_not_apply_deep_wounds() {
    given_a_guaranteed_melee_ability_hit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_bloodthirst());

    then_deep_wounds_is_not_applied();
}

void TestDeepWounds::test_regular_hit_whirlwind_does_not_apply_deep_wounds() {
    given_a_guaranteed_melee_ability_hit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_whirlwind());

    then_deep_wounds_is_not_applied();
}

void TestDeepWounds::test_regular_hit_heroic_strike_does_not_apply_deep_wounds() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_heroic_strike()->calculate_damage();

    then_deep_wounds_is_not_applied();
}

void TestDeepWounds::test_regular_hit_overpower_does_not_apply_deep_wounds() {
    given_a_guaranteed_melee_ability_hit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_overpower());

    then_deep_wounds_is_not_applied();
}

void TestDeepWounds::test_damage_of_1_of_3_deep_wounds() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_1_of_3_deep_wounds();
    given_no_previous_deep_wounds_damage_dealt();

    when_mh_attack_is_performed();

    // total_deep_wounds_damage = (avg_mh_wpn_dmg + (mh_wpn_speed * melee_ap / 14)) * deep_wounds_percent
    // [57] = (100 + (2.6 * 1000 / 14)) * 0.2
    then_deep_wounds_damage_dealt_is(57);
    then_damage_is_dealt_over_12_seconds();
}

void TestDeepWounds::test_damage_of_2_of_3_deep_wounds() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_2_of_3_deep_wounds();
    given_no_previous_deep_wounds_damage_dealt();

    when_mh_attack_is_performed();

    // total_deep_wounds_damage = (avg_mh_wpn_dmg + (mh_wpn_speed * melee_ap / 14)) * deep_wounds_percent
    // [114] = (100 + (2.6 * 1000 / 14)) * 0.4
    then_deep_wounds_damage_dealt_is(114);
    then_damage_is_dealt_over_12_seconds();
}

void TestDeepWounds::test_damage_of_3_of_3_deep_wounds() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_3_of_3_deep_wounds();
    given_no_previous_deep_wounds_damage_dealt();

    when_mh_attack_is_performed();

    // total_deep_wounds_damage = (avg_mh_wpn_dmg + (mh_wpn_speed * melee_ap / 14)) * deep_wounds_percent
    // [171] = (100 + (2.6 * 1000 / 14)) * 0.6
    // TODO: Rounding causes slight deep wounds increase in damage, asserting 172 instead of 171.
    then_deep_wounds_damage_dealt_is(172);
    then_damage_is_dealt_over_12_seconds();
}

void TestDeepWounds::test_damage_stacks_when_multiple_crits_occur() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_3_of_3_deep_wounds();
    given_no_previous_deep_wounds_damage_dealt();

    when_mh_attack_is_performed();
    when_mh_attack_is_performed();

    // total_deep_wounds_damage = (avg_mh_wpn_dmg + (mh_wpn_speed * melee_ap / 14)) * deep_wounds_percent
    // [342] = [((100 + (2.6 * 1000 / 14)) * 0.6)] + [((100 + (2.6 * 1000 / 14)) * 0.6)]
    // TODO: Rounding causes slight deep wounds increase in damage, asserting 343 instead of 342.
    then_deep_wounds_damage_dealt_is(343);
    then_damage_is_dealt_over_12_seconds();
}

void TestDeepWounds::given_deep_wounds_enabled() {
    given_1_of_3_deep_wounds();
}

void TestDeepWounds::given_1_of_3_deep_wounds() {
    assert(DeepWoundsTalent(pchar, nullptr).increment_rank());
    pchar->prepare_set_of_combat_iterations();
}

void TestDeepWounds::given_2_of_3_deep_wounds() {
    assert(DeepWoundsTalent(pchar, nullptr).increment_rank());
    assert(DeepWoundsTalent(pchar, nullptr).increment_rank());
    pchar->prepare_set_of_combat_iterations();
}

void TestDeepWounds::given_3_of_3_deep_wounds() {
    assert(DeepWoundsTalent(pchar, nullptr).increment_rank());
    assert(DeepWoundsTalent(pchar, nullptr).increment_rank());
    assert(DeepWoundsTalent(pchar, nullptr).increment_rank());
    pchar->prepare_set_of_combat_iterations();
}

void TestDeepWounds::given_no_previous_deep_wounds_damage_dealt() {
    assert(pchar->get_statistics()->get_total_damage_for_spell("Deep Wounds") == 0);
}

void TestDeepWounds::when_mh_attack_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    warrior->get_spells()->get_mh_attack()->perform();
}

void TestDeepWounds::when_attack_is_performed(Spell* spell) {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    spell->perform();
}

void TestDeepWounds::then_deep_wounds_damage_dealt_is(const int damage_dealt) {
    while (!pchar->get_engine()->get_queue()->empty()) {
        Event* event = pchar->get_engine()->get_queue()->get_next();
        pchar->get_engine()->set_current_priority(event);

        if (event->get_name() != "DotTick") {
            delete event;
            continue;
        }

        event->act();
        delete event;
    }

    if (pchar->get_statistics()->get_total_damage_for_spell("Deep Wounds") != damage_dealt)
        qDebug() << "Deep Wounds: expected" << damage_dealt << "got" << pchar->get_statistics()->get_total_damage_for_spell("Deep Wounds");
    assert(pchar->get_statistics()->get_total_damage_for_spell("Deep Wounds") == damage_dealt);
}

void TestDeepWounds::then_deep_wounds_is_applied() {
    while (!pchar->get_engine()->get_queue()->empty()) {
        Event* event = pchar->get_engine()->get_queue()->get_next();
        pchar->get_engine()->set_current_priority(event);

        if (event->get_name() != "DotTick") {
            delete event;
            continue;
        }

        event->act();
        delete event;
    }

    assert(pchar->get_statistics()->get_total_damage_for_spell("Deep Wounds") > 0);
}

void TestDeepWounds::then_deep_wounds_is_not_applied() {
    then_deep_wounds_damage_dealt_is(0);
}

void TestDeepWounds::then_damage_is_dealt_over_12_seconds() {
    assert(QString::number(pchar->get_engine()->get_current_priority(), 'f', 3) == "12.000");
}
