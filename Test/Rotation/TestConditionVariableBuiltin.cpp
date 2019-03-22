#include "TestConditionVariableBuiltin.h"

#include <cassert>

#include "ConditionVariableBuiltin.h"
#include "Orc.h"
#include "Rogue.h"
#include "SimSettings.h"

TestConditionVariableBuiltin::TestConditionVariableBuiltin():
    TestObject(nullptr)
{}

void TestConditionVariableBuiltin::test_all() {
    test_values_after_initialization();

    test_combo_points_less();
    test_combo_points_leq();
    test_combo_points_equal();
    test_combo_points_geq();
    test_combo_points_greater();
}

void TestConditionVariableBuiltin::test_values_after_initialization() {
}

void TestConditionVariableBuiltin::test_combo_points_less() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* rogue = new Rogue(race, equipment_db, sim_settings);
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

    delete rogue;
    delete sim_settings;
    delete race;
}

void TestConditionVariableBuiltin::test_combo_points_leq() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* rogue = new Rogue(race, equipment_db, sim_settings);
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

    delete rogue;
    delete sim_settings;
    delete race;
}

void TestConditionVariableBuiltin::test_combo_points_equal() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* rogue = new Rogue(race, equipment_db, sim_settings);
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

    delete rogue;
    delete sim_settings;
    delete race;
}

void TestConditionVariableBuiltin::test_combo_points_geq() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* rogue = new Rogue(race, equipment_db, sim_settings);
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

    delete rogue;
    delete sim_settings;
    delete race;
}

void TestConditionVariableBuiltin::test_combo_points_greater() {
    Race* race = new Orc();
    auto* sim_settings = new SimSettings();
    auto* rogue = new Rogue(race, equipment_db, sim_settings);
    ConditionVariableBuiltin condition (rogue, BuiltinVariables::ComboPoints, Comparators::greater, 3);

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

    delete rogue;
    delete sim_settings;
    delete race;
}
