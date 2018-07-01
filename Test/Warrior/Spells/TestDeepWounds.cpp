
#include "TestDeepWounds.h"
#include "DeepWounds.h"
#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include "Bloodthirst.h"
#include "Whirlwind.h"
#include "HeroicStrike.h"
#include "Overpower.h"
#include "Queue.h"
#include "ClassStatistics.h"

TestDeepWounds::TestDeepWounds() :
    TestSpellWarrior("Deep Wounds")
{}

void TestDeepWounds::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_no_cooldown();
    tear_down();

    set_up();
    test_does_not_incur_global_cooldown_on_proc();
    tear_down();

    set_up();
    test_critical_mh_attack_applies_deep_wounds();
    tear_down();

    set_up();
    test_critical_oh_attack_applies_deep_wounds();
    tear_down();

    set_up();
    test_critical_bloodthirst_applies_deep_wounds();
    tear_down();

    set_up();
    test_critical_whirlwind_applies_deep_wounds();
    tear_down();

    set_up();
    test_critical_heroic_strike_applies_deep_wounds();
    tear_down();

    set_up();
    test_critical_overpower_applies_deep_wounds();
    tear_down();

    set_up();
    test_regular_hit_mh_attack_does_not_apply_deep_wounds();
    tear_down();

    set_up();
    test_regular_hit_oh_attack_does_not_apply_deep_wounds();
    tear_down();

    set_up();
    test_regular_hit_bloodthirst_does_not_apply_deep_wounds();
    tear_down();

    set_up();
    test_regular_hit_whirlwind_does_not_apply_deep_wounds();
    tear_down();

    set_up();
    test_regular_hit_heroic_strike_does_not_apply_deep_wounds();
    tear_down();

    set_up();
    test_regular_hit_overpower_does_not_apply_deep_wounds();
    tear_down();

    set_up();
    test_damage_of_1_of_3_deep_wounds();
    tear_down();

    set_up();
    test_damage_of_2_of_3_deep_wounds();
    tear_down();

    set_up();
    test_damage_of_3_of_3_deep_wounds();
    tear_down();

    set_up();
    test_damage_stacks_when_multiple_crits_occur();
    tear_down();
}

DeepWounds* TestDeepWounds::deep_wounds() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_deep_wounds();
}

void TestDeepWounds::test_name_correct() {
    assert(deep_wounds()->get_name() == "Deep Wounds");
}

void TestDeepWounds::test_has_no_cooldown() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_deep_wounds_enabled();

    when_mh_attack_is_performed();

    assert(warrior->action_ready());
}

void TestDeepWounds::test_does_not_incur_global_cooldown_on_proc() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_white_crit();
    given_1000_melee_ap();
    given_deep_wounds_enabled();

    when_mh_attack_is_performed();

    assert(deep_wounds()->is_ready());
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

void TestDeepWounds::test_critical_oh_attack_applies_deep_wounds() {
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
    given_a_guaranteed_melee_ability_crit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_heroic_strike());

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
    given_a_guaranteed_melee_ability_hit();
    given_deep_wounds_enabled();
    given_no_previous_deep_wounds_damage_dealt();

    when_attack_is_performed(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_heroic_strike());

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
    then_deep_wounds_damage_dealt_is(171);
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
    then_deep_wounds_damage_dealt_is(342);
    then_damage_is_dealt_over_12_seconds();
}

void TestDeepWounds::given_deep_wounds_enabled() {
    given_1_of_3_deep_wounds();
}

void TestDeepWounds::given_0_of_3_deep_wounds() {
    assert(!deep_wounds()->is_enabled());
}

void TestDeepWounds::given_1_of_3_deep_wounds() {
    deep_wounds()->increase_effect_via_talent();
}

void TestDeepWounds::given_2_of_3_deep_wounds() {
    deep_wounds()->increase_effect_via_talent();
    deep_wounds()->increase_effect_via_talent();
}

void TestDeepWounds::given_3_of_3_deep_wounds() {
    deep_wounds()->increase_effect_via_talent();
    deep_wounds()->increase_effect_via_talent();
    deep_wounds()->increase_effect_via_talent();
}

void TestDeepWounds::given_no_previous_deep_wounds_damage_dealt() {
    assert(pchar->get_statistics()->get_total_damage_for_spell("Deep Wounds") == 0);
}

void TestDeepWounds::when_mh_attack_is_performed() {
    warrior->get_spells()->get_mh_attack()->perform();
}

void TestDeepWounds::when_attack_is_performed(Spell* spell) {
    spell->perform();
}

void TestDeepWounds::then_deep_wounds_damage_dealt_is(const int damage_dealt) {
    while (!engine->get_queue()->empty()) {
        Event* event = engine->get_queue()->get_next();
        engine->set_current_priority(event);

        if (event->get_name() != "DotTick") {
            delete event;
            continue;
        }

        event->act();
        delete event;
    }

    assert(pchar->get_statistics()->get_total_damage_for_spell("Deep Wounds") == damage_dealt);
}

void TestDeepWounds::then_deep_wounds_is_applied() {
    while (!engine->get_queue()->empty()) {
        Event* event = engine->get_queue()->get_next();
        engine->set_current_priority(event);

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
    assert(QString::number(engine->get_current_priority(), 'f', 3) == "12.000");
}
