#include "TestRevenge.h"

#include <cassert>

#include "Engine.h"
#include "Equipment.h"
#include "Event.h"
#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include "Queue.h"
#include "Revenge.h"
#include "Talent.h"

TestRevenge::TestRevenge(EquipmentDb* equipment_db) : TestSpellWarrior(equipment_db, "Revenge") {}

void TestRevenge::test_all() {
    run_mandatory_tests();

    set_up();
    test_hit_dmg();
    tear_down();

    set_up();
    test_hit_threat();
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

Revenge* TestRevenge::revenge() const {
    return static_cast<WarriorSpells*>(warrior->get_spells())->get_revenge();
}

void TestRevenge::test_name_correct() {
    assert(revenge()->get_name() == "Revenge");
}

void TestRevenge::test_spell_cooldown() {
    given_a_guaranteed_melee_ability_hit();
    assert(QString::number(revenge()->get_base_cooldown(), 'f', 3) == "5.000");
}

void TestRevenge::test_whether_spell_causes_global_cooldown() {
    revenge()->perform();

    then_next_event_is(EventType::PlayerAction, "1.500");
}

void TestRevenge::test_how_spell_observes_global_cooldown() {
    given_warrior_in_defensive_stance();
    given_warrior_has_rage(100);
    given_a_mainhand_weapon_with_2_speed();
    assert(revenge()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(revenge()->get_spell_status() == SpellStatus::OnGCD);
    assert(almost_equal(revenge()->get_cooldown_remaining(), 0));
}

void TestRevenge::test_is_ready_conditions() {
    given_warrior_in_battle_stance();
    given_warrior_has_rage(100);
    assert(revenge()->get_spell_status() == SpellStatus::InBattleStance);

    given_warrior_in_berserker_stance();
    given_warrior_has_rage(100);
    assert(revenge()->get_spell_status() == SpellStatus::InBerserkerStance);

    given_warrior_in_defensive_stance();
    given_warrior_has_rage(100);
    assert(revenge()->get_spell_status() == SpellStatus::Available);
}

void TestRevenge::test_resource_cost() {
    given_a_guaranteed_melee_ability_hit();
    given_warrior_has_rage(5);

    when_revenge_is_performed();

    then_warrior_has_rage(0);
}

void TestRevenge::test_stance_cooldown() {
    when_switching_to_defensive_stance();
    given_warrior_has_rage(100);
    assert(revenge()->get_spell_status() == SpellStatus::OnGCD);

    when_switching_to_berserker_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(revenge()->get_spell_status() == SpellStatus::OnGCD);

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(revenge()->get_spell_status() == SpellStatus::InBerserkerStance);

    when_switching_to_defensive_stance();
    given_warrior_has_rage(100);
    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(revenge()->get_spell_status() == SpellStatus::OnStanceCooldown);

    given_engine_priority_pushed_forward(1.1);
    when_revenge_is_performed();
    given_engine_priority_pushed_forward(1.4);
    assert(revenge()->get_spell_status() == SpellStatus::OnGCD);
    given_engine_priority_pushed_forward(1.4);
    assert(revenge()->get_spell_status() == SpellStatus::OnCooldown);
}

void TestRevenge::test_hit_dmg() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_2_speed();
    given_a_guaranteed_melee_ability_hit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_revenge_is_performed();

    // Flat 64-78 damage
    then_damage_dealt_is_in_range(64, 78);
}

void TestRevenge::test_crit_dmg_0_of_2_impale() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_2_speed();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_0_of_2_impale();

    when_revenge_is_performed();

    then_damage_dealt_is_in_range(128, 156);
}

void TestRevenge::test_hit_threat() {
    given_target_has_0_armor();
    given_in_melee_attack_mode();
    given_warrior_in_defensive_stance();
    given_1000_melee_ap();
    given_warrior_has_rage(100);
    given_a_guaranteed_melee_ability_hit();
    given_engine_priority_at(0.51);

    when_revenge_is_performed();

    // Base Range is 64-78. Defensive stance lowers by 10%
    then_damage_dealt_is_in_range(57, 71);

    // [Threat] = [Damage*.9+InnateThreat]*[1.3] = [483 - 502]
    then_threat_dealt_is_in_range(483, 502);
}

void TestRevenge::test_crit_dmg_1_of_2_impale() {
    given_target_has_0_armor();
    given_a_mainhand_weapon_with_2_speed();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_1_of_2_impale();

    when_revenge_is_performed();

    then_damage_dealt_is_in_range(134, 164);
}

void TestRevenge::test_crit_dmg_2_of_2_impale() {
    given_target_has_0_armor();
    given_a_twohand_weapon_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_crit();
    given_1000_melee_ap();
    given_no_previous_damage_dealt();
    given_2_of_2_impale();

    when_revenge_is_performed();

    then_damage_dealt_is_in_range(141, 172);
}

void TestRevenge::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_melee_ability_dodge();

    when_revenge_is_performed();

    then_overpower_is_active();
}

void TestRevenge::when_revenge_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    revenge()->perform();

    while (pchar->get_engine()->get_current_priority() < 1.5) {
        if (pchar->get_engine()->get_queue()->empty()) {
            qDebug() << "Attempted to run queued events until 1.5"
                     << "but ran out of events at" << pchar->get_engine()->get_current_priority();
            assert(false);
        }
        Event* event = pchar->get_engine()->get_queue()->get_next();
        pchar->get_engine()->set_current_priority(event);

        if (event->event_type == EventType::PlayerAction) {
            event->act();
            delete event;
            break;
        }

        delete event;
    }
}
