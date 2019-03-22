#include "TestConditionVariableBuiltin.h"

#include <cassert>

#include "AutoShot.h"
#include "CharacterSpells.h"
#include "ConditionVariableBuiltin.h"
#include "Engine.h"
#include "Equipment.h"
#include "Hunter.h"
#include "MainhandAttackWarrior.h"
#include "Orc.h"
#include "PlayerAction.h"
#include "Rogue.h"
#include "SimSettings.h"
#include "Warrior.h"
#include "Weapon.h"

TestConditionVariableBuiltin::TestConditionVariableBuiltin(EquipmentDb* equipment_db):
    TestObject(equipment_db),
    hunter(nullptr),
    rogue(nullptr),
    warrior(nullptr),
    race(nullptr),
    sim_settings(nullptr)
{}

void TestConditionVariableBuiltin::test_all() {
    test_values_after_initialization();

    set_up_rogue();
    test_combo_points_less();
    tear_down();

    set_up_rogue();
    test_combo_points_leq();
    tear_down();

    set_up_rogue();
    test_combo_points_equal();
    tear_down();

    set_up_rogue();
    test_combo_points_geq();
    tear_down();

    set_up_rogue();
    test_combo_points_greater();
    tear_down();

    set_up_hunter();
    test_auto_shot_timer_less();
    tear_down();

    set_up_hunter();
    test_auto_shot_timer_greater();
    tear_down();

    set_up_warrior();
    test_swing_timer_less();
    tear_down();

    set_up_warrior();
    test_swing_timer_greater();
    tear_down();
}

void TestConditionVariableBuiltin::test_values_after_initialization() {
}

void TestConditionVariableBuiltin::test_combo_points_less() {
    ConditionVariableBuiltin condition (rogue, BuiltinVariables::ComboPoints, Comparators::less, 3);

    assert(rogue->get_combo_points() == 0);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());
}

void TestConditionVariableBuiltin::test_combo_points_leq() {
    ConditionVariableBuiltin condition (rogue, BuiltinVariables::ComboPoints, Comparators::leq, 3);

    assert(rogue->get_combo_points() == 0);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());
}

void TestConditionVariableBuiltin::test_combo_points_equal() {
    ConditionVariableBuiltin condition (rogue, BuiltinVariables::ComboPoints, Comparators::eq, 3);

    assert(rogue->get_combo_points() == 0);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());
}

void TestConditionVariableBuiltin::test_combo_points_geq() {
    ConditionVariableBuiltin condition (rogue, BuiltinVariables::ComboPoints, Comparators::geq, 3);

    assert(rogue->get_combo_points() == 0);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());
}

void TestConditionVariableBuiltin::test_combo_points_greater() {
    ConditionVariableBuiltin condition(rogue, BuiltinVariables::ComboPoints, Comparators::greater, 3);

    assert(rogue->get_combo_points() == 0);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(!condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());

    rogue->gain_combo_points(1);
    assert(condition.condition_fulfilled());
}

void TestConditionVariableBuiltin::test_auto_shot_timer_less() {
    hunter->get_equipment()->set_ranged(17069);
    assert(hunter->get_equipment()->get_ranged()->get_name() == "Striker's Mark");
    AutoShot* auto_shot = hunter->get_spells()->get_auto_shot();
    auto_shot->prepare_set_of_combat_iterations();

    ConditionVariableBuiltin condition200ms(hunter, BuiltinVariables::AutoShotTimer, Comparators::less, 0.2);
    ConditionVariableBuiltin condition300ms(hunter, BuiltinVariables::AutoShotTimer, Comparators::less, 0.3);

    assert(auto_shot->is_available());
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    auto_shot->perform();
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.1);
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.19);
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.21);
    assert(!condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.29);
    assert(!condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.31);
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());
}

void TestConditionVariableBuiltin::test_auto_shot_timer_greater() {
    hunter->get_equipment()->set_ranged(17069);
    assert(hunter->get_equipment()->get_ranged()->get_name() == "Striker's Mark");
    AutoShot* auto_shot = hunter->get_spells()->get_auto_shot();
    auto_shot->prepare_set_of_combat_iterations();

    ConditionVariableBuiltin condition200ms(hunter, BuiltinVariables::AutoShotTimer, Comparators::greater, 0.2);
    ConditionVariableBuiltin condition300ms(hunter, BuiltinVariables::AutoShotTimer, Comparators::greater, 0.3);

    assert(auto_shot->is_available());
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    auto_shot->perform();
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.1);
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.19);
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.21);
    assert(condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.29);
    assert(condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(hunter->get_engine(), 0.31);
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());
}

void TestConditionVariableBuiltin::test_swing_timer_less() {
    warrior->get_equipment()->set_mainhand(19364);
    assert(warrior->get_equipment()->get_mainhand()->get_name() == "Ashkandi, Greatsword of the Brotherhood");
    MainhandAttack* mh_attack = warrior->get_spells()->get_mh_attack();
    mh_attack->prepare_set_of_combat_iterations();

    ConditionVariableBuiltin condition200ms(warrior, BuiltinVariables::SwingTimer, Comparators::less, 0.2);
    ConditionVariableBuiltin condition300ms(warrior, BuiltinVariables::SwingTimer, Comparators::less, 0.3);

    assert(mh_attack->is_available());
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    mh_attack->perform();
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.1);
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.19);
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.21);
    assert(!condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.29);
    assert(!condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.31);
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());
}

void TestConditionVariableBuiltin::test_swing_timer_greater() {
    warrior->get_equipment()->set_mainhand(19364);
    assert(warrior->get_equipment()->get_mainhand()->get_name() == "Ashkandi, Greatsword of the Brotherhood");
    MainhandAttack* mh_attack = warrior->get_spells()->get_mh_attack();
    mh_attack->prepare_set_of_combat_iterations();

    ConditionVariableBuiltin condition200ms(warrior, BuiltinVariables::SwingTimer, Comparators::greater, 0.2);
    ConditionVariableBuiltin condition300ms(warrior, BuiltinVariables::SwingTimer, Comparators::greater, 0.3);

    assert(mh_attack->is_available());
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    mh_attack->perform();
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.1);
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.19);
    assert(!condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.21);
    assert(condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.29);
    assert(condition200ms.condition_fulfilled());
    assert(!condition300ms.condition_fulfilled());

    set_event_priority(warrior->get_engine(), 0.31);
    assert(condition200ms.condition_fulfilled());
    assert(condition300ms.condition_fulfilled());
}

void TestConditionVariableBuiltin::set_up_rogue() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->rogue = new Rogue(race, equipment_db, sim_settings);
}

void TestConditionVariableBuiltin::set_up_hunter() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->hunter = new Hunter(race, equipment_db, sim_settings);
}

void TestConditionVariableBuiltin::set_up_warrior() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->warrior = new Warrior(race, equipment_db, sim_settings);
}

void TestConditionVariableBuiltin::tear_down() {
    delete rogue;
    delete hunter;
    delete warrior;
    delete race;
    delete sim_settings;

    rogue = nullptr;
    hunter = nullptr;
    warrior = nullptr;
}

void TestConditionVariableBuiltin::set_event_priority(Engine* engine, const double priority) {
    auto* event = new PlayerAction(nullptr, priority);
    engine->set_current_priority(event);
    delete event;

    assert(almost_equal(priority, engine->get_current_priority()));
}
