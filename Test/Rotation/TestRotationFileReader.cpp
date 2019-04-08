#include "TestRotationFileReader.h"

#include "Buff.h"
#include "ConditionBuff.h"
#include "ConditionResource.h"
#include "ConditionSpell.h"
#include "Hunter.h"
#include "Orc.h"
#include "Rotation.h"
#include "RotationExecutor.h"
#include "RotationFileReader.h"
#include "SimSettings.h"
#include "Utils/Check.h"
#include "Warrior.h"

TestRotationFileReader::TestRotationFileReader() :
    TestObject(nullptr),
    race(nullptr),
    sim_settings(nullptr),
    hunter(nullptr),
    warrior(nullptr)
{}

void TestRotationFileReader::test_all() {
    qDebug() << "TestRotationFileReader";
    RotationFileReader::add_rotations(rotations);

    test_values_after_initialization();

    set_up_warrior();
    test_warrior_dw_fury();
    tear_down();

    set_up_hunter();
    test_hunter_aimed_shot_multi_shot();
    tear_down();
}

TestRotationFileReader::~TestRotationFileReader() {
    for (auto * rotation: rotations)
        delete rotation;
}

void TestRotationFileReader::test_values_after_initialization() {
    assert(rotations.size() == 8);
}

void TestRotationFileReader::test_warrior_dw_fury() {
    Rotation* rotation = get_rotation("DW Fury High Rage");

    QVector<QString> expected_executor_names = {
        "Berserker Rage",
        "Battle Shout",
        "Heroic Strike",
        "Kiss of the Spider",
        "Jom Gabbar",
        "Badge of the Swarmguard",
        "Slayer's Crest",
        "Earthstrike",
        "Zandalarian Hero Medallion",
        "Diamond Flask",
        "Death Wish",
        "Recklessness",
        "Blood Fury",
        "Berserking",
        "Execute",
        "Bloodthirst",
        "Whirlwind",
        "Overpower",
        "Hamstring",
        "Battle Stance",
        "Berserker Stance"
    };
    assert(rotation->executors.size() == expected_executor_names.size());

    verify_executor_names(rotation, expected_executor_names);

    rotation->link_spells(warrior);

    QVector<QVector<Condition*>> condition_groups;
    ConditionResource* resource_condition;
    ConditionBuff* buff_condition;
    ConditionVariableBuiltin* builtin_condition;

    //
    // Berserker Rage:
    //
    condition_groups = rotation->executors[0]->condition_groups;
    assert(condition_groups.size() == 1 && condition_groups[0].size() == 1);
    // resource "Rage" less 50
    resource_condition = dynamic_cast<ConditionResource*>(condition_groups[0][0]);
    verify_resource_condition(resource_condition, 50.0, Comparators::less, ResourceType::Rage);

    //
    // Battle Shout
    //
    condition_groups = rotation->executors[1]->condition_groups;
    assert(condition_groups.size() == 2);

    // Condition group 0
    assert(condition_groups[0].size() == 1);
    // buff "Battle Shout" less 3
    buff_condition = dynamic_cast<ConditionBuff*>(condition_groups[0][0]);
    verify_buff_condition(buff_condition, "Battle Shout", 3.0, Comparators::less);

    // Condition group 1
    assert(condition_groups[1].size() == 3);
    // variable "time_remaining_execute" less 10
    builtin_condition = dynamic_cast<ConditionVariableBuiltin*>(condition_groups[1][0]);
    verify_builtin_condition(builtin_condition, BuiltinVariables::TimeRemainingExecute, 10.0, Comparators::less);
    // variable "time_remaining_execute" greater 0
    builtin_condition = dynamic_cast<ConditionVariableBuiltin*>(condition_groups[1][1]);
    verify_builtin_condition(builtin_condition, BuiltinVariables::TimeRemainingExecute, 0.0, Comparators::greater);
    // buff "Battle Shout" less 45
    buff_condition = dynamic_cast<ConditionBuff*>(condition_groups[1][2]);
    verify_buff_condition(buff_condition, "Battle Shout", 45.0, Comparators::less);

    //
    // Heroic Strike
    //
    condition_groups = rotation->executors[2]->condition_groups;
    assert(condition_groups.size() == 1 && condition_groups[0].size() == 2);
    // "time_remaining_execute" greater 3
    builtin_condition = dynamic_cast<ConditionVariableBuiltin*>(condition_groups[0][0]);
    verify_builtin_condition(builtin_condition, BuiltinVariables::TimeRemainingExecute, 3.0, Comparators::greater);
    // resource "Rage" greater 50
    resource_condition = dynamic_cast<ConditionResource*>(condition_groups[0][1]);
    verify_resource_condition(resource_condition, 50.0, Comparators::greater, ResourceType::Rage);
}

void TestRotationFileReader::test_hunter_aimed_shot_multi_shot() {
    Rotation* rotation = get_rotation("Aimed/Multi-Shot");

    QVector<QString> expected_executor_names = {
        "Rapid Fire",
        "Kiss of the Spider",
        "Jom Gabbar",
        "Badge of the Swarmguard",
        "Slayer's Crest",
        "Earthstrike",
        "Devilsaur Eye",
        "Zandalarian Hero Medallion",
        "Blood Fury",
        "Berserking",
        "Bestial Wrath",
        "Aimed Shot",
        "Multi-Shot",
        "Hunter's Mark",
        "Aspect of the Hawk"
    };
    assert(rotation->executors.size() == expected_executor_names.size());

    verify_executor_names(rotation, expected_executor_names);
}

void TestRotationFileReader::verify_resource_condition(ConditionResource* condition, const double cmp_value,
                                                       const int comparator, const ResourceType resource_type) {
    assert(condition != nullptr);
    assert(almost_equal(condition->cmp_value, cmp_value));
    assert(condition->comparator == comparator);
    assert(condition->resource_type == resource_type);
}

void TestRotationFileReader::verify_buff_condition(ConditionBuff* condition, const QString& name,
                                                   const double cmp_value, const int comparator) {
    assert(condition != nullptr);
    assert(condition->buff->get_name() == name);
    assert(almost_equal(condition->cmp_value, cmp_value));
    assert(condition->comparator == comparator);
}

void TestRotationFileReader::verify_builtin_condition(ConditionVariableBuiltin* condition, const BuiltinVariables builtin,
                                                      const double cmp_value, const int comparator) {
    assert(condition != nullptr);
    assert(condition->builtin == builtin);
    assert(almost_equal(condition->rhs_value, cmp_value));
    assert(condition->comparator == comparator);
}

void TestRotationFileReader::verify_executor_names(Rotation* rotation, QVector<QString>& executor_names) {
    check((rotation->executors.size() == executor_names.size()),
          QString("Mismatched executor size for '%1'").arg(rotation->get_name()).toStdString());

    for (int i = 0; i < executor_names.size(); ++i)
        check((executor_names[i] == rotation->executors[i]->get_spell_name()),
              QString("Unexpected executor, expected '%1' got '%2").arg(executor_names[i], rotation->executors[i]->get_spell_name()).toStdString());
}

Rotation* TestRotationFileReader::get_rotation(const QString& name) const {
    for (auto * rotation: rotations) {
        if (rotation->get_name() == name)
            return rotation;
    }

    qDebug() << "Failed to find" << name;
    assert(false);
    return nullptr;
}

void TestRotationFileReader::set_up_warrior() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->warrior = new Warrior(race, equipment_db, sim_settings);
}

void TestRotationFileReader::set_up_hunter() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->hunter = new Hunter(race, equipment_db, sim_settings);
}

void TestRotationFileReader::tear_down() {
    delete hunter;
    delete warrior;
    delete race;
    delete sim_settings;

    hunter = nullptr;
    warrior = nullptr;
}
