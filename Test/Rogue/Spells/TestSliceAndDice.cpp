#include "SliceAndDice.h"

#include "Assassination.h"
#include "Backstab.h"
#include "Equipment.h"
#include "MainhandAttack.h"
#include "RogueSpells.h"
#include "Talent.h"
#include "TestSliceAndDice.h"
#include "WarriorSpells.h"

TestSliceAndDice::TestSliceAndDice(EquipmentDb *equipment_db) :
    TestSpellRogue(equipment_db, "Slice and Dice")
{}

void TestSliceAndDice::test_all() {
    run_mandatory_tests();

    set_up();
    test_combo_points();
    tear_down();

    set_up();
    test_stealth();
    tear_down();

    set_up();
    test_duration_and_attack_speed_with_1_combo_points();
    tear_down();

    set_up();
    test_duration_and_attack_speed_with_2_combo_points();
    tear_down();

    set_up();
    test_duration_and_attack_speed_with_3_combo_points();
    tear_down();

    set_up();
    test_duration_and_attack_speed_with_4_combo_points();
    tear_down();

    set_up();
    test_duration_and_attack_speed_with_5_combo_points();
    tear_down();

    set_up();
    test_duration_and_attack_speed_with_5_combo_points_and_1_of_3_imp_snd();
    tear_down();

    set_up();
    test_duration_and_attack_speed_with_5_combo_points_and_2_of_3_imp_snd();
    tear_down();

    set_up();
    test_duration_and_attack_speed_with_5_combo_points_and_3_of_3_imp_snd();
    tear_down();
}

SliceAndDice *TestSliceAndDice::slice_and_dice() {
    return dynamic_cast<RogueSpells*>(rogue->get_spells())->get_slice_and_dice();
}

void TestSliceAndDice::test_name_correct() {
    assert(slice_and_dice()->get_name() == "Slice and Dice");
}

void TestSliceAndDice::test_spell_cooldown() {
    assert(QString::number(slice_and_dice()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestSliceAndDice::test_incurs_global_cooldown() {
    given_rogue_has_combo_points(1);

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("PlayerAction", QString::number(rogue->global_cooldown(), 'f', 3));
}

void TestSliceAndDice::test_obeys_global_cooldown() {
    given_dagger_equipped_in_mainhand(rogue);
    given_rogue_has_combo_points(1);

    given_rogue_has_energy(100);
    assert(slice_and_dice()->is_available());

    given_rogue_is_on_gcd();

    given_rogue_has_energy(100);
    assert(!slice_and_dice()->is_available());
}

void TestSliceAndDice::test_is_ready_conditions() {
    given_rogue_has_combo_points(0);
    assert(!slice_and_dice()->is_available());

    given_rogue_has_combo_points(1);
    assert(slice_and_dice()->is_available());

    given_rogue_has_combo_points(2);
    assert(slice_and_dice()->is_available());

    given_rogue_has_combo_points(3);
    assert(slice_and_dice()->is_available());

    given_rogue_has_combo_points(4);
    assert(slice_and_dice()->is_available());

    given_rogue_has_combo_points(5);
    assert(slice_and_dice()->is_available());
}

void TestSliceAndDice::test_resource_cost() {
    given_dagger_equipped_in_mainhand(rogue);
    given_a_guaranteed_melee_ability_hit();

    given_rogue_has_combo_points(1);
    given_rogue_has_energy(25);
    when_slice_and_dice_is_performed();
    then_rogue_has_energy(0);

    given_engine_priority_at(1.01);

    given_rogue_has_combo_points(1);
    given_rogue_has_energy(35);
    when_slice_and_dice_is_performed();
    then_rogue_has_energy(10);
}

void TestSliceAndDice::test_combo_points() {
    given_a_mainhand_dagger_with_100_min_max_dmg();
    given_a_guaranteed_melee_ability_hit();

    given_rogue_has_combo_points(1);
    when_slice_and_dice_is_performed();
    then_rogue_has_combo_points(0);

    given_engine_priority_pushed_forward(1.01);
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(2);
    when_slice_and_dice_is_performed();
    then_rogue_has_combo_points(0);

    given_engine_priority_pushed_forward(1.01);
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(3);
    when_slice_and_dice_is_performed();
    then_rogue_has_combo_points(0);

    given_engine_priority_pushed_forward(1.01);
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(4);
    when_slice_and_dice_is_performed();
    then_rogue_has_combo_points(0);

    given_engine_priority_pushed_forward(1.01);
    given_rogue_has_energy(100);
    given_rogue_has_combo_points(5);
    when_slice_and_dice_is_performed();
    then_rogue_has_combo_points(0);
}

void TestSliceAndDice::test_stealth() {
    given_rogue_has_combo_points(1);
    given_rogue_not_in_stealth();
    assert(slice_and_dice()->is_available());
    given_rogue_in_stealth();
    assert(slice_and_dice()->is_available());

    when_slice_and_dice_is_performed();

    assert(!rogue->is_stealthed());
}

void TestSliceAndDice::test_duration_and_attack_speed_with_1_combo_points() {
    given_a_mainhand_weapon_with_2_speed();
    given_rogue_has_combo_points(1);
    rogue->start_attack();

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "1.000");
    then_next_event_is("MainhandMeleeHit", "1.538");
    then_next_event_is("ResourceGain", "2.000");
    then_next_event_is("BuffRemoval", "9.000");
}

void TestSliceAndDice::test_duration_and_attack_speed_with_2_combo_points() {
    given_a_mainhand_weapon_with_2_speed();
    given_rogue_has_combo_points(2);
    rogue->start_attack();

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "1.000");
    then_next_event_is("MainhandMeleeHit", "1.538");
    then_next_event_is("ResourceGain", "2.000");
    then_next_event_is("BuffRemoval", "12.000");
}

void TestSliceAndDice::test_duration_and_attack_speed_with_3_combo_points() {
    given_a_mainhand_weapon_with_2_speed();
    given_rogue_has_combo_points(3);
    rogue->start_attack();

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "1.000");
    then_next_event_is("MainhandMeleeHit", "1.538");
    then_next_event_is("ResourceGain", "2.000");
    then_next_event_is("BuffRemoval", "15.000");
}

void TestSliceAndDice::test_duration_and_attack_speed_with_4_combo_points() {
    given_a_mainhand_weapon_with_2_speed();
    given_rogue_has_combo_points(4);
    rogue->start_attack();

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "1.000");
    then_next_event_is("MainhandMeleeHit", "1.538");
    then_next_event_is("ResourceGain", "2.000");
    then_next_event_is("BuffRemoval", "18.000");
}

void TestSliceAndDice::test_duration_and_attack_speed_with_5_combo_points() {
    given_a_mainhand_weapon_with_2_speed();
    given_rogue_has_combo_points(5);
    rogue->start_attack();

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "1.000");
    then_next_event_is("MainhandMeleeHit", "1.538");
    then_next_event_is("ResourceGain", "2.000");
    then_next_event_is("BuffRemoval", "21.000");
}

void TestSliceAndDice::test_duration_and_attack_speed_with_5_combo_points_and_1_of_3_imp_snd() {
    given_1_of_3_imp_snd();
    given_a_mainhand_weapon_with_2_speed();
    given_rogue_has_combo_points(5);
    rogue->start_attack();

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "1.000");
    then_next_event_is("MainhandMeleeHit", "1.538");
    then_next_event_is("ResourceGain", "2.000");
    then_next_event_is("BuffRemoval", "24.000");
}

void TestSliceAndDice::test_duration_and_attack_speed_with_5_combo_points_and_2_of_3_imp_snd() {
    given_2_of_3_imp_snd();
    given_a_mainhand_weapon_with_2_speed();
    given_rogue_has_combo_points(5);
    rogue->start_attack();

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "1.000");
    then_next_event_is("MainhandMeleeHit", "1.538");
    then_next_event_is("ResourceGain", "2.000");
    then_next_event_is("BuffRemoval", "27.000");
}

void TestSliceAndDice::test_duration_and_attack_speed_with_5_combo_points_and_3_of_3_imp_snd() {
    given_3_of_3_imp_snd();
    given_a_mainhand_weapon_with_2_speed();
    given_rogue_has_combo_points(5);
    rogue->start_attack();

    when_slice_and_dice_is_performed();

    then_next_event_is("MainhandMeleeHit", "0.000");
    then_next_event_is("MainhandMeleeHit", "0.000", RUN_EVENT);
    then_next_event_is("PlayerAction", "1.000");
    then_next_event_is("MainhandMeleeHit", "1.538");
    then_next_event_is("ResourceGain", "2.000");
    then_next_event_is("BuffRemoval", "30.000");
}

void TestSliceAndDice::given_1_of_3_imp_snd() {
    Talent* talent = Assassination(rogue).get_improved_slice_and_dice();

    assert(talent->increment_rank());

    delete talent;
}

void TestSliceAndDice::given_2_of_3_imp_snd() {
    Talent* talent = Assassination(rogue).get_improved_slice_and_dice();

    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSliceAndDice::given_3_of_3_imp_snd() {
    Talent* talent = Assassination(rogue).get_improved_slice_and_dice();

    assert(talent->increment_rank());
    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;
}

void TestSliceAndDice::when_slice_and_dice_is_performed() {
    if (pchar->get_equipment()->get_mainhand() == nullptr)
        given_a_mainhand_dagger_with_100_min_max_dmg();

    slice_and_dice()->perform();
}
