#include "TestFlurryWarrior.h"

#include <cassert>

#include "Bloodthirst.h"
#include "Equipment.h"
#include "Flurry.h"
#include "Fury.h"
#include "HeroicStrike.h"
#include "MainhandAttackWarrior.h"
#include "MainhandMeleeHit.h"
#include "MortalStrike.h"
#include "OffhandAttackWarrior.h"
#include "OffhandMeleeHit.h"
#include "Overpower.h"
#include "Spell.h"
#include "SpellRankGroup.h"
#include "Talent.h"
#include "WarriorSpells.h"
#include "Whirlwind.h"

TestFlurryWarrior::TestFlurryWarrior(EquipmentDb* equipment_db) :
    TestBuffWarrior(equipment_db, "FlurryWarrior")
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
    test_critical_mortal_strike_applies_flurry();
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

    set_up();
    test_regular_hit_mortal_strike_does_not_apply_flurry();
    tear_down();
}

void TestFlurryWarrior::test_name_correct() {
    assert(spells->get_flurry()->name== "Flurry");
}

void TestFlurryWarrior::test_has_15_second_duration() {
    given_a_mainhand_and_offhand_equipped();
    given_flurry_enabled();

    when_flurry_is_applied();

    given_event_is_ignored(EventType::PlayerAction);
    then_next_event_is(EventType::MainhandMeleeHit);
    then_next_event_is(EventType::OffhandMeleeHit);
    then_next_event_is(EventType::BuffRemoval, "15.000");
}

void TestFlurryWarrior::test_has_3_charges() {
    given_flurry_enabled();

    when_flurry_is_applied();

    then_number_of_charges_is(spells->get_flurry(), 3);
}

void TestFlurryWarrior::test_attack_speed_increased_when_1_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_crit();
    given_1_of_5_flurry();

    warrior->get_spells()->start_attack();

    given_event_is_ignored(EventType::PlayerAction);
    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "1.818");
    then_next_event_is(EventType::MainhandMeleeHit, "2.727");
}

void TestFlurryWarrior::test_attack_speed_increased_when_2_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_crit();
    given_2_of_5_flurry();

    warrior->get_spells()->start_attack();

    given_event_is_ignored(EventType::PlayerAction);
    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "1.739");
    then_next_event_is(EventType::MainhandMeleeHit, "2.609");
}

void TestFlurryWarrior::test_attack_speed_increased_when_3_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_crit();
    given_3_of_5_flurry();

    warrior->get_spells()->start_attack();

    given_event_is_ignored(EventType::PlayerAction);
    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "1.667");
    then_next_event_is(EventType::MainhandMeleeHit, "2.500");
}

void TestFlurryWarrior::test_attack_speed_increased_when_4_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_crit();
    given_4_of_5_flurry();

    warrior->get_spells()->start_attack();

    given_event_is_ignored(EventType::PlayerAction);
    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "1.600");
    then_next_event_is(EventType::MainhandMeleeHit, "2.400");
}

void TestFlurryWarrior::test_attack_speed_increased_when_5_of_5_flurry_applied() {
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_crit();
    given_5_of_5_flurry();

    warrior->get_spells()->start_attack();

    given_event_is_ignored(EventType::PlayerAction);
    then_next_event_is(EventType::MainhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "0.000", RUN_EVENT);
    then_next_event_is(EventType::OffhandMeleeHit, "1.538");
    then_next_event_is(EventType::MainhandMeleeHit, "2.308");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_1_of_5_flurry_removed() {
    given_event_is_ignored(EventType::PlayerAction);
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_1_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is(EventType::OffhandMeleeHit, "1.818");
    when_performing_oh_attack();
    then_next_event_is(EventType::MainhandMeleeHit, "2.727");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.727 = (2.727 - (1.818 * 2)) * 1.1
    then_next_event_is(EventType::OffhandMeleeHit, "3.727");
    then_next_event_is(EventType::MainhandMeleeHit, "5.727");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_2_of_5_flurry_removed() {
    given_event_is_ignored(EventType::PlayerAction);
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_2_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is(EventType::OffhandMeleeHit, "1.739");
    when_performing_oh_attack();
    then_next_event_is(EventType::MainhandMeleeHit, "2.609");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.609 = (2.609 - (1.739 * 2)) * 1.15
    then_next_event_is(EventType::OffhandMeleeHit, "3.609");
    then_next_event_is(EventType::MainhandMeleeHit, "5.609");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_3_of_5_flurry_removed() {
    given_event_is_ignored(EventType::PlayerAction);
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_3_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is(EventType::OffhandMeleeHit, "1.667");
    when_performing_oh_attack();
    then_next_event_is(EventType::MainhandMeleeHit, "2.500");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.5 = (2.500 - (1.667 * 2)) * 1.2
    then_next_event_is(EventType::OffhandMeleeHit, "3.500");
    then_next_event_is(EventType::MainhandMeleeHit, "5.500");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_4_of_5_flurry_removed() {
    given_event_is_ignored(EventType::PlayerAction);
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_4_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is(EventType::OffhandMeleeHit, "1.600");
    when_performing_oh_attack();
    then_next_event_is(EventType::MainhandMeleeHit, "2.400");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.400 = (2.400 - (1.600 * 2)) * 1.25
    then_next_event_is(EventType::OffhandMeleeHit, "3.400");
    then_next_event_is(EventType::MainhandMeleeHit, "5.400");
}

void TestFlurryWarrior::test_attack_speed_decreased_when_5_of_5_flurry_removed() {
    given_event_is_ignored(EventType::PlayerAction);
    given_a_mainhand_weapon_with_3_speed();
    given_an_offhand_weapon_with_2_speed();
    given_a_guaranteed_white_hit();
    given_5_of_5_flurry();

    when_performing_mh_attack();
    when_performing_oh_attack();
    when_flurry_is_applied();
    then_next_event_is(EventType::OffhandMeleeHit, "1.538");
    when_performing_oh_attack();
    then_next_event_is(EventType::MainhandMeleeHit, "2.308");
    when_performing_mh_attack();
    when_flurry_is_removed();

    // updated swing = (curr_time - curr_expected_use) * haste_change
    // 3.308 = (2.308 - (1.538 * 2)) * 1.3
    then_next_event_is(EventType::OffhandMeleeHit, "3.308");
    then_next_event_is(EventType::MainhandMeleeHit, "5.308");
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

    when_performing_attack(static_cast<WarriorSpells*>(warrior->get_spells())->get_bloodthirst());

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_whirlwind_applies_flurry() {
    given_a_guaranteed_melee_ability_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(static_cast<WarriorSpells*>(warrior->get_spells())->get_whirlwind());

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_heroic_strike_applies_flurry() {
    given_a_mainhand_and_offhand_equipped();
    given_a_guaranteed_melee_ability_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    static_cast<HeroicStrike*>(warrior->get_spells()->get_spell_rank_group_by_name("Heroic Strike")->get_max_available_spell_rank())->calculate_damage();

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_overpower_applies_flurry() {
    given_a_guaranteed_melee_ability_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(static_cast<WarriorSpells*>(warrior->get_spells())->get_overpower());

    then_flurry_is_active();
}

void TestFlurryWarrior::test_critical_mortal_strike_applies_flurry() {
    given_a_guaranteed_melee_ability_crit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(static_cast<WarriorSpells*>(warrior->get_spells())->get_mortal_strike());

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

    when_performing_attack(static_cast<WarriorSpells*>(warrior->get_spells())->get_bloodthirst());

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_whirlwind_does_not_apply_flurry() {
    given_a_guaranteed_melee_ability_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(static_cast<WarriorSpells*>(warrior->get_spells())->get_whirlwind());

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_heroic_strike_does_not_apply_flurry() {
    given_a_mainhand_and_offhand_equipped();
    given_a_guaranteed_melee_ability_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    static_cast<HeroicStrike*>(warrior->get_spells()->get_spell_rank_group_by_name("Heroic Strike")->get_max_available_spell_rank())->calculate_damage();

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_overpower_does_not_apply_flurry() {
    given_a_guaranteed_melee_ability_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(static_cast<WarriorSpells*>(warrior->get_spells())->get_overpower());

    then_flurry_is_not_active();
}

void TestFlurryWarrior::test_regular_hit_mortal_strike_does_not_apply_flurry() {
    given_a_guaranteed_melee_ability_hit();
    given_flurry_enabled();
    given_flurry_is_not_active();

    when_performing_attack(static_cast<WarriorSpells*>(warrior->get_spells())->get_mortal_strike());

    then_flurry_is_not_active();
}

void TestFlurryWarrior::given_flurry_enabled() {
    given_1_of_5_flurry();
    assert(spells->get_flurry()->is_enabled());
}

void TestFlurryWarrior::given_flurry_is_not_active() {
    when_flurry_is_removed();
}

void TestFlurryWarrior::given_a_mainhand_and_offhand_equipped() {
    given_a_mainhand_weapon_with_100_min_max_dmg();
    given_an_offhand_weapon_with_100_min_max_dmg();
}

void TestFlurryWarrior::when_flurry_is_applied() {
    assert(spells->get_flurry()->is_active() == false);
    spells->get_flurry()->apply_buff();
    assert(spells->get_flurry()->is_active() == true);
}

void TestFlurryWarrior::when_flurry_is_removed() {
    while (spells->get_flurry()->is_active()) {
        spells->get_flurry()->use_charge();
    }
}

void TestFlurryWarrior::given_1_of_5_flurry() {
    const auto fury = Fury(warrior);
    given_talent_rank(fury, "Enrage", 5);
    given_talent_rank(fury, "Flurry", 1);

    warrior->prepare_set_of_combat_iterations();
}

void TestFlurryWarrior::given_2_of_5_flurry() {
    const auto fury = Fury(warrior);
    given_talent_rank(fury, "Enrage", 5);
    given_talent_rank(fury, "Flurry", 2);

    warrior->prepare_set_of_combat_iterations();
}

void TestFlurryWarrior::given_3_of_5_flurry() {
    const auto fury = Fury(warrior);
    given_talent_rank(fury, "Enrage", 5);
    given_talent_rank(fury, "Flurry", 3);

    warrior->prepare_set_of_combat_iterations();
}

void TestFlurryWarrior::given_4_of_5_flurry() {
    const auto fury = Fury(warrior);
    given_talent_rank(fury, "Enrage", 5);
    given_talent_rank(fury, "Flurry", 4);

    warrior->prepare_set_of_combat_iterations();
}

void TestFlurryWarrior::given_5_of_5_flurry() {
    const auto fury = Fury(warrior);
    given_talent_rank(fury, "Enrage", 5);
    given_talent_rank(fury, "Flurry", 5);

    warrior->prepare_set_of_combat_iterations();
}

void TestFlurryWarrior::when_performing_mh_attack() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    warrior->get_spells()->get_mh_attack()->perform();
}

void TestFlurryWarrior::when_performing_oh_attack() {
    if (pchar->get_equipment()->get_offhand() == nullptr)
        given_an_offhand_weapon_with_100_min_max_dmg();

    warrior->get_spells()->get_oh_attack()->perform();
}

void TestFlurryWarrior::when_performing_attack(Spell* spell) {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_weapon_with_100_min_max_dmg();

    spell->perform();
}

void TestFlurryWarrior::then_flurry_is_active() {
    assert(spells->get_flurry()->is_active());
}

void TestFlurryWarrior::then_flurry_is_not_active() {
    assert(!spells->get_flurry()->is_active());
}
