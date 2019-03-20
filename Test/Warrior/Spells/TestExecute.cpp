#include "TestExecute.h"

#include "CombatRoll.h"
#include "Engine.h"
#include "Equipment.h"
#include "Execute.h"
#include "Fury.h"
#include "Impale.h"
#include "MeleeSpecialTable.h"
#include "Orc.h"
#include "Queue.h"
#include "Target.h"

TestExecute::TestExecute(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Execute")
{}

void TestExecute::test_all() {
    run_mandatory_tests();

    set_up();
    test_1_of_2_improved_execute_reduces_rage_cost();
    tear_down();

    set_up();
    test_2_of_2_improved_execute_reduces_rage_cost();
    tear_down();

    set_up();
    test_removing_points_in_improved_execute_increases_rage_cost();
    tear_down();

    set_up();
    test_min_crit_dmg_0_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_0_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_1_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_1_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_2_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_2_of_2_imp_execute_0_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_0_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_0_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_1_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_1_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_2_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_2_of_2_imp_execute_1_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_0_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_0_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_1_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_1_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_min_crit_dmg_2_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_max_crit_dmg_2_of_2_imp_execute_2_of_2_impale();
    tear_down();

    set_up();
    test_dodge_applies_overpower_buff();
    tear_down();
}

Execute* TestExecute::execute() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_execute();
}

void TestExecute::test_name_correct() {
    assert(execute()->get_name() == "Execute");
}

void TestExecute::test_spell_cooldown() {
    assert(QString::number(execute()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestExecute::test_incurs_global_cooldown() {
    when_execute_is_performed_with_rage(100);

    then_next_event_is("PlayerAction", QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestExecute::test_obeys_global_cooldown() {
    given_target_in_execute_range();
    given_warrior_has_rage(100);
    assert(execute()->is_available());

    given_warrior_is_on_gcd();

    assert(!execute()->is_available());
}

void TestExecute::test_resource_cost() {
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_hit();
    assert(execute_available_with_rage(15));
    assert(!execute_available_with_rage(14));

    when_execute_is_performed_with_rage(15);

    then_warrior_has_rage(0);
}

void TestExecute::test_is_ready_conditions() {
    given_warrior_in_battle_stance();
    given_target_not_in_execute_range();
    given_warrior_has_rage(0);

    assert(warrior->action_ready());
    assert(!execute()->is_available());

    given_target_in_execute_range();
    assert(!execute()->is_available());

    given_target_not_in_execute_range();
    given_warrior_has_rage(100);
    assert(!execute()->is_available());

    given_target_in_execute_range();
    given_warrior_in_defensive_stance();
    given_warrior_has_rage(100);
    assert(!execute()->is_available());

    given_warrior_in_berserker_stance();
    given_warrior_has_rage(100);
    assert(execute()->is_available());

    given_warrior_in_battle_stance();
    given_warrior_has_rage(100);
    assert(execute()->is_available());
}

void TestExecute::test_stance_cooldown() {
    given_warrior_in_battle_stance();
    given_target_in_execute_range();
    given_warrior_has_rage(100);
    assert(execute()->is_available());

    when_switching_to_berserker_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(!execute()->is_available());

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(!execute()->is_available());

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(execute()->is_available());
}

void TestExecute::test_1_of_2_improved_execute_reduces_rage_cost() {
    given_target_in_execute_range();
    assert(execute_available_with_rage(15));
    assert(!execute_available_with_rage(14));

    given_1_of_2_improved_execute();

    assert(execute_available_with_rage(13));
    assert(!execute_available_with_rage(12));
}

void TestExecute::test_2_of_2_improved_execute_reduces_rage_cost() {
    given_target_in_execute_range();
    assert(execute_available_with_rage(15));
    assert(!execute_available_with_rage(14));

    given_2_of_2_improved_execute();

    assert(execute_available_with_rage(10));
    assert(!execute_available_with_rage(9));
}

void TestExecute::test_removing_points_in_improved_execute_increases_rage_cost() {
    Talent* improved_execute = Fury(warrior).get_improved_execute();
    given_target_in_execute_range();
    assert(execute_available_with_rage(15));
    assert(!execute_available_with_rage(14));

    assert(improved_execute->increment_rank());
    assert(improved_execute->increment_rank());

    assert(execute_available_with_rage(10));
    assert(!execute_available_with_rage(9));

    assert(improved_execute->decrement_rank());

    assert(execute_available_with_rage(13));
    assert(!execute_available_with_rage(12));

    assert(improved_execute->decrement_rank());

    assert(execute_available_with_rage(15));
    assert(!execute_available_with_rage(14));

    delete improved_execute;
}

void TestExecute::test_min_crit_dmg_0_of_2_imp_execute_0_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(15);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1200] = (600 + 15 * (15 - 15)) * 2.0
    then_damage_dealt_is(1200);
}

void TestExecute::test_max_crit_dmg_0_of_2_imp_execute_0_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3750] = (600 + 15 * (100 - 15)) * 2.0
    then_damage_dealt_is(3750);
}

void TestExecute::test_min_crit_dmg_1_of_2_imp_execute_0_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(13);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1200] = (600 + 15 * (13 - 13)) * 2.0
    then_damage_dealt_is(1200);
}

void TestExecute::test_max_crit_dmg_1_of_2_imp_execute_0_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3810] = (600 + 15 * (100 - 13)) * 2.0
    then_damage_dealt_is(3810);
}

void TestExecute::test_min_crit_dmg_2_of_2_imp_execute_0_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(10);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1200] = (600 + 15 * (10 - 10)) * 2.0
    then_damage_dealt_is(1200);
}

void TestExecute::test_max_crit_dmg_2_of_2_imp_execute_0_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_0_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3900] = (600 + 15 * (100 - 10)) * 2.0
    then_damage_dealt_is(3900);
}

void TestExecute::test_min_crit_dmg_0_of_2_imp_execute_1_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(15);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1260] = (600 + 15 * (15 - 15)) * 2.1
    then_damage_dealt_is(1260);
}

void TestExecute::test_max_crit_dmg_0_of_2_imp_execute_1_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3938] = (600 + 15 * (100 - 15)) * 2.1
    then_damage_dealt_is(3938);
}

void TestExecute::test_min_crit_dmg_1_of_2_imp_execute_1_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(13);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1260] = (600 + 15 * (13 - 13)) * 2.1
    then_damage_dealt_is(1260);
}

void TestExecute::test_max_crit_dmg_1_of_2_imp_execute_1_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4001] = (600 + 15 * (100 - 13)) * 2.1
    then_damage_dealt_is(4001);
}

void TestExecute::test_min_crit_dmg_2_of_2_imp_execute_1_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(10);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1260] = (600 + 15 * (10 - 10)) * 2.1
    then_damage_dealt_is(1260);
}

void TestExecute::test_max_crit_dmg_2_of_2_imp_execute_1_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4095] = (600 + 15 * (100 - 10)) * 2.1
    then_damage_dealt_is(4095);
}

void TestExecute::test_min_crit_dmg_0_of_2_imp_execute_2_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(15);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1320] = (600 + 15 * (15 - 15)) * 2.2
    then_damage_dealt_is(1320);
}

void TestExecute::test_max_crit_dmg_0_of_2_imp_execute_2_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4125] = (600 + 15 * (100 - 15)) * 2.2
    then_damage_dealt_is(4125);
}

void TestExecute::test_min_crit_dmg_1_of_2_imp_execute_2_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(13);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1320] = (600 + 15 * (13 - 13)) * 2.2
    then_damage_dealt_is(1320);
}

void TestExecute::test_max_crit_dmg_1_of_2_imp_execute_2_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4191] = (600 + 15 * (100 - 13)) * 2.2
    then_damage_dealt_is(4191);
}

void TestExecute::test_min_crit_dmg_2_of_2_imp_execute_2_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(10);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [1320] = (600 + 15 * (10 - 10)) * 2.2
    then_damage_dealt_is(1320);
}

void TestExecute::test_max_crit_dmg_2_of_2_imp_execute_2_of_2_impale() {
    given_target_has_0_armor();
    given_target_in_execute_range();
    given_a_guaranteed_melee_ability_crit();
    given_2_of_2_impale();
    given_2_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4290] = (600 + 15 * (100 - 10)) * 2.2
    then_damage_dealt_is(4290);
}

void TestExecute::given_0_of_2_improved_execute() {
    assert(execute_available_with_rage(15));
    assert(!execute_available_with_rage(14));
}

void TestExecute::given_1_of_2_improved_execute() {
    Talent* talent = Fury(warrior).get_improved_execute();

    assert(talent->increment_rank());

    delete talent;

    assert(execute_available_with_rage(13));
    assert(!execute_available_with_rage(12));
}

void TestExecute::given_2_of_2_improved_execute() {
    Talent* talent = Fury(warrior).get_improved_execute();

    assert(talent->increment_rank());
    assert(talent->increment_rank());

    delete talent;

    assert(execute_available_with_rage(10));
    assert(!execute_available_with_rage(9));
}

void TestExecute::test_dodge_applies_overpower_buff() {
    given_a_guaranteed_melee_ability_dodge();

    when_execute_is_performed_with_rage(100);

    then_overpower_is_active();
}

void TestExecute::given_target_in_execute_range() {
    given_engine_priority_at(280);
}

void TestExecute::given_target_not_in_execute_range() {
    given_engine_priority_at(0.0);
}

void TestExecute::when_execute_is_performed_with_rage(const unsigned rage) {
    warrior->lose_rage(warrior->get_resource_level(ResourceType::Rage));
    warrior->gain_rage(rage);
    execute()->perform();
}

bool TestExecute::execute_available_with_rage(const unsigned rage) {
    warrior->lose_rage(warrior->get_resource_level(ResourceType::Rage));
    warrior->gain_rage(rage);
    return execute()->is_available();
}
