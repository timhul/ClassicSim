
#include "TestFlurryWarrior.h"
#include "Flurry.h"
#include "WarriorSpells.h"
#include "MainhandAttackWarrior.h"
#include "OffhandAttackWarrior.h"
#include "MainhandMeleeHit.h"
#include "OffhandMeleeHit.h"
#include "Bloodthirst.h"
#include "Whirlwind.h"
#include "HeroicStrike.h"
#include "Overpower.h"
#include "Spell.h"

TestFlurryWarrior::TestFlurryWarrior() :
    TestBuffWarrior("FlurryWarrior")
{}

void TestFlurryWarrior::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_15_second_duration();
    tear_down();

    set_up();
    test_has_3_charges();
    tear_down();

    set_up();
    test_attack_speed_increased_when_1_of_5_flurry_applied();
    tear_down();

    set_up();
    test_attack_speed_increased_when_2_of_5_flurry_applied();
    tear_down();

    set_up();
    test_attack_speed_increased_when_3_of_5_flurry_applied();
    tear_down();

    set_up();
    test_attack_speed_increased_when_4_of_5_flurry_applied();
    tear_down();

    set_up();
    test_attack_speed_increased_when_5_of_5_flurry_applied();
    tear_down();

    set_up();
    test_attack_speed_decreased_when_1_of_5_flurry_removed();
    tear_down();

    set_up();
    test_attack_speed_decreased_when_2_of_5_flurry_removed();
    tear_down();

    set_up();
    test_attack_speed_decreased_when_3_of_5_flurry_removed();
    tear_down();

    set_up();
    test_attack_speed_decreased_when_4_of_5_flurry_removed();
    tear_down();

    set_up();
    test_attack_speed_decreased_when_5_of_5_flurry_removed();
    tear_down();

    set_up();
    test_critical_mh_attack_applies_flurry();
    tear_down();

    set_up();
    test_critical_oh_attack_applies_flurry();
    tear_down();

    set_up();
    test_critical_bloodthirst_applies_flurry();
    tear_down();

    set_up();
    test_critical_whirlwind_applies_flurry();
    tear_down();

    set_up();
    test_critical_heroic_strike_applies_flurry();
    tear_down();

    set_up();
    test_critical_overpower_applies_flurry();
    tear_down();

    set_up();
    test_regular_hit_mh_attack_does_not_apply_flurry();
    tear_down();

    set_up();
    test_regular_hit_oh_attack_does_not_apply_flurry();
    tear_down();

    set_up();
    test_regular_hit_bloodthirst_does_not_apply_flurry();
    tear_down();

    set_up();
    test_regular_hit_whirlwind_does_not_apply_flurry();
    tear_down();

    set_up();
    test_regular_hit_heroic_strike_does_not_apply_flurry();
    tear_down();

    set_up();
    test_regular_hit_overpower_does_not_apply_flurry();
    tear_down();
}

void TestFlurryWarrior::test_name_correct() {
    assert(warrior->get_flurry()->get_name() == "Flurry");
}

void TestFlurryWarrior::test_has_15_second_duration() {
    given_flurry_enabled();

    when_flurry_is_applied();

    then_next_event_is("MainhandMeleeHit");
    then_next_event_is("OffhandMeleeHit");
    then_next_event_is("BuffRemoval", "15.000");
}

void TestFlurryWarrior::test_has_3_charges() {
    given_flurry_enabled();

    when_flurry_is_applied();

    then_number_of_charges_is(warrior->get_flurry(), 3);
}

void TestFlurryWarrior::test_attack_speed_increased_when_1_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_1_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();

    then_next_event_is("OffhandMeleeHit", "1.818");
    then_next_event_is("MainhandMeleeHit", "2.727");
}

void TestFlurryWarrior::test_attack_speed_increased_when_2_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_2_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();

    then_next_event_is("OffhandMeleeHit", "1.739");
    then_next_event_is("MainhandMeleeHit", "2.609");
}

void TestFlurryWarrior::test_attack_speed_increased_when_3_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_3_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();

    then_next_event_is("OffhandMeleeHit", "1.667");
    then_next_event_is("MainhandMeleeHit", "2.500");
}

void TestFlurryWarrior::test_attack_speed_increased_when_4_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_4_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();

    then_next_event_is("OffhandMeleeHit", "1.600");
    then_next_event_is("MainhandMeleeHit", "2.400");
}

void TestFlurryWarrior::test_attack_speed_increased_when_5_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_5_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();

    then_next_event_is("OffhandMeleeHit", "1.538");
    then_next_event_is("MainhandMeleeHit", "2.308");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_1_of_5_flurry_removed() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_1_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is("OffhandMeleeHit", "1.818");
    when_performing_oh_attack();
    then_next_event_is("MainhandMeleeHit", "2.727");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.727 = (2.727 - (1.818 * 2)) * 1.1
    then_next_event_is("OffhandMeleeHit", "3.727");
    then_next_event_is("MainhandMeleeHit", "5.727");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_2_of_5_flurry_removed() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_2_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is("OffhandMeleeHit", "1.739");
    when_performing_oh_attack();
    then_next_event_is("MainhandMeleeHit", "2.609");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.609 = (2.609 - (1.739 * 2)) * 1.15
    then_next_event_is("OffhandMeleeHit", "3.609");
    then_next_event_is("MainhandMeleeHit", "5.609");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_3_of_5_flurry_removed() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_3_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is("OffhandMeleeHit", "1.667");
    when_performing_oh_attack();
    then_next_event_is("MainhandMeleeHit", "2.500");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.5 = (2.500 - (1.667 * 2)) * 1.2
    then_next_event_is("OffhandMeleeHit", "3.500");
    then_next_event_is("MainhandMeleeHit", "5.500");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_4_of_5_flurry_removed() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_4_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is("OffhandMeleeHit", "1.600");
    when_performing_oh_attack();
    then_next_event_is("MainhandMeleeHit", "2.400");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.400 = (2.400 - (1.600 * 2)) * 1.25
    then_next_event_is("OffhandMeleeHit", "3.400");
    then_next_event_is("MainhandMeleeHit", "5.400");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_5_of_5_flurry_removed() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_5_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is("OffhandMeleeHit", "1.538");
    when_performing_oh_attack();
    then_next_event_is("MainhandMeleeHit", "2.308");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.308 = (2.308 - (1.538 * 2)) * 1.3
    then_next_event_is("OffhandMeleeHit", "3.308");
    then_next_event_is("MainhandMeleeHit", "5.308");
}

void TestFlurryWarrior::test_critical_mh_attack_applies_flurry() {
    given_a_guaranteed_white_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_mh_attack();

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_oh_attack_applies_flurry() {
    given_a_guaranteed_white_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_oh_attack();

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_bloodthirst_applies_flurry() {
    given_a_guaranteed_melee_ability_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_bloodthirst());

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_whirlwind_applies_flurry() {
    given_a_guaranteed_melee_ability_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_whirlwind());

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_heroic_strike_applies_flurry() {
    given_a_guaranteed_melee_ability_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_heroic_strike());

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_overpower_applies_flurry() {
    given_a_guaranteed_melee_ability_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_overpower());

    then_flurry_is_active();
}

void TestFlurryWarrior::test_regular_hit_mh_attack_does_not_apply_flurry() {
    given_a_guaranteed_white_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_mh_attack();

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_oh_attack_does_not_apply_flurry() {
    given_a_guaranteed_white_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_oh_attack();

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_bloodthirst_does_not_apply_flurry() {
    given_a_guaranteed_melee_ability_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_bloodthirst());

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_whirlwind_does_not_apply_flurry() {
    given_a_guaranteed_melee_ability_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_whirlwind());

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_heroic_strike_does_not_apply_flurry() {
    given_a_guaranteed_melee_ability_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_heroic_strike());

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_overpower_does_not_apply_flurry() {
    given_a_guaranteed_melee_ability_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_overpower());

    then_flurry_is_not_active();
}

void TestFlurryWarrior::given_flurry_enabled() {
    given_1_of_5_flurry();
    assert(warrior->get_flurry()->is_enabled());
}

void TestFlurryWarrior::given_flurry_not_enabled() {
    assert(warrior->get_flurry()->is_enabled() == false);
}

void TestFlurryWarrior::given_flurry_is_not_active() {
    when_flurry_is_removed();
}

void TestFlurryWarrior::when_flurry_is_applied() {
    assert(warrior->get_flurry()->is_active() == false);
    warrior->get_flurry()->apply_buff();
    assert(warrior->get_flurry()->is_active() == true);
}

void TestFlurryWarrior::when_flurry_is_removed() {
    while (warrior->get_flurry()->is_active()) {
        warrior->get_flurry()->use_charge();
    }
}

void TestFlurryWarrior::given_1_of_5_flurry() {
    warrior->get_flurry()->increase_rank();
}

void TestFlurryWarrior::given_2_of_5_flurry() {
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
}

void TestFlurryWarrior::given_3_of_5_flurry() {
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
}

void TestFlurryWarrior::given_4_of_5_flurry() {
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
}

void TestFlurryWarrior::given_5_of_5_flurry() {
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
    warrior->get_flurry()->increase_rank();
}

void TestFlurryWarrior::when_performing_mh_attack() {
    warrior->get_spells()->get_mh_attack()->perform();
}

void TestFlurryWarrior::when_performing_oh_attack() {
    warrior->get_spells()->get_oh_attack()->perform();
}

void TestFlurryWarrior::when_performing_attack(Spell* spell) {
    spell->perform();
}

void TestFlurryWarrior::then_flurry_is_active() {
    assert(warrior->get_flurry()->is_active());
}

void TestFlurryWarrior::then_flurry_is_not_active() {
    assert(!warrior->get_flurry()->is_active());
}
