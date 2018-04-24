
#include "TestExecute.h"
#include "Execute.h"
#include "Impale.h"

#include "Warrior.h"
#include "Target.h"
#include "Orc.h"

#include "Engine.h"
#include "Queue.h"
#include "Equipment.h"
#include "Target.h"
#include "CombatRoll.h"
#include "PlayerAction.h"
#include "MeleeSpecialTable.h"

#include <QDebug>

void TestExecute::test_all() {
    set_up();
    test_name_correct();
    tear_down();

    set_up();
    test_has_no_cooldown();
    tear_down();

    set_up();
    test_incurs_global_cooldown_on_use();
    tear_down();

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
}

void TestExecute::test_name_correct() {
    assert(warrior->get_execute()->get_name() == "Execute");
}

void TestExecute::test_has_no_cooldown() {
    assert(QString::number(warrior->get_execute()->get_cooldown(), 'f', 3) == "0.000");
}

void TestExecute::test_incurs_global_cooldown_on_use() {
    Queue* queue = engine->get_queue();
    assert(queue->empty());

    when_execute_is_performed_with_rage(100);

    assert(!queue->empty());
    assert(!warrior->action_ready());
    Event* event = queue->get_next();
    assert(event->get_name() == "CooldownReady");
    assert(QString::number(event->get_priority(), 'f', 3) == QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestExecute::test_1_of_2_improved_execute_reduces_rage_cost() {
    assert(warrior->get_execute()->is_available(15));
    assert(!warrior->get_execute()->is_available(14));

    warrior->get_execute()->increase_effect_via_talent();

    assert(warrior->get_execute()->is_available(13));
    assert(!warrior->get_execute()->is_available(12));
}

void TestExecute::test_2_of_2_improved_execute_reduces_rage_cost() {
    assert(warrior->get_execute()->is_available(15));
    assert(!warrior->get_execute()->is_available(14));

    warrior->get_execute()->increase_effect_via_talent();
    warrior->get_execute()->increase_effect_via_talent();

    assert(warrior->get_execute()->is_available(10));
    assert(!warrior->get_execute()->is_available(9));
}

void TestExecute::test_removing_points_in_improved_execute_increases_rage_cost() {
    assert(warrior->get_execute()->is_available(15));
    assert(!warrior->get_execute()->is_available(14));

    warrior->get_execute()->increase_effect_via_talent();
    warrior->get_execute()->increase_effect_via_talent();

    assert(warrior->get_execute()->is_available(10));
    assert(!warrior->get_execute()->is_available(9));

    warrior->get_execute()->decrease_effect_via_talent();

    assert(warrior->get_execute()->is_available(13));
    assert(!warrior->get_execute()->is_available(12));

    warrior->get_execute()->decrease_effect_via_talent();

    assert(warrior->get_execute()->is_available(15));
    assert(!warrior->get_execute()->is_available(14));
}

void TestExecute::test_min_crit_dmg_0_of_2_imp_execute_0_of_2_impale() {
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
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_0_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [3938] = (600 + 15 * (100 - 15)) * 2.1
    // TODO: 3937.5 is erroneously rounded to 3937 instead of 3938. Consider using ceil.
    then_damage_dealt_is(3937);
}

void TestExecute::test_min_crit_dmg_1_of_2_imp_execute_1_of_2_impale() {
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
    given_a_guaranteed_melee_ability_crit();
    given_1_of_2_impale();
    given_1_of_2_improved_execute();
    given_no_previous_damage_dealt();

    when_execute_is_performed_with_rage(100);

    // [Damage] = (600 + 15 * (rage - rage_cost)) * crit_dmg_modifier
    // [4001] = (600 + 15 * (100 - 13)) * 2.1
    // TODO: 4000.5 is erroneously rounded to 4000 instead of 4000. Consider using ceil.
    then_damage_dealt_is(4000);
}

void TestExecute::test_min_crit_dmg_2_of_2_imp_execute_1_of_2_impale() {
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
    assert(warrior->get_execute()->is_available(15));
    assert(!warrior->get_execute()->is_available(14));
}

void TestExecute::given_1_of_2_improved_execute() {
    warrior->get_execute()->increase_effect_via_talent();

    assert(warrior->get_execute()->is_available(13));
    assert(!warrior->get_execute()->is_available(12));
}

void TestExecute::given_2_of_2_improved_execute() {
    warrior->get_execute()->increase_effect_via_talent();
    warrior->get_execute()->increase_effect_via_talent();

    assert(warrior->get_execute()->is_available(10));
    assert(!warrior->get_execute()->is_available(9));
}

void TestExecute::when_execute_is_performed_with_rage(const int rage) {
    warrior->get_execute()->perform(rage);
}
