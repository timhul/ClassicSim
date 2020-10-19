#include "TestRotationFileReader.h"

#include "Buff.h"
#include "ConditionBuffDuration.h"
#include "ConditionResource.h"
#include "ConditionSpell.h"
#include "Human.h"
#include "Hunter.h"
#include "Orc.h"
#include "Paladin.h"
#include "RaidControl.h"
#include "Rotation.h"
#include "RotationExecutor.h"
#include "RotationFileReader.h"
#include "SimSettings.h"
#include "Utils/Check.h"
#include "Warrior.h"

TestRotationFileReader::TestRotationFileReader() : TestObject(nullptr) {}

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

    set_up_paladin();
    test_paladin_seal_of_the_crusader();
    tear_down();
}

TestRotationFileReader::~TestRotationFileReader() {
    for (const auto& rotation : rotations)
        delete rotation;
}

void TestRotationFileReader::test_values_after_initialization() {}

void TestRotationFileReader::test_warrior_dw_fury() {
    Rotation* rotation = get_rotation("DW Fury High Rage");

    QVector<QString> expected_all_executor_names = {"Bloodrage",
                                                    "Berserker Rage",
                                                    "Battle Shout",
                                                    "Heroic Strike",
                                                    "Manual Crowd Pummeler",
                                                    "Kiss of the Spider",
                                                    "Jom Gabbar",
                                                    "Badge of the Swarmguard",
                                                    "Slayer's Crest",
                                                    "Earthstrike",
                                                    "Zandalarian Hero Medallion",
                                                    "Diamond Flask",
                                                    "Cloudkeeper Legplates",
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
                                                    "Berserker Stance",};
    assert(rotation->all_executors.size() == expected_all_executor_names.size());
    verify_executor_names(rotation, rotation->all_executors, expected_all_executor_names);

    QVector<QString> expected_active_executor_names = {"Bloodrage",    "Berserker Rage", "Battle Shout",  "Heroic Strike",
                                                       "Recklessness", "Blood Fury",     "Execute",       "Whirlwind",
                                                       "Overpower",    "Hamstring",      "Battle Stance", "Berserker Stance"};
    rotation->link_spells(warrior);
    verify_executor_names(rotation, rotation->active_executors, expected_active_executor_names);

    QVector<QVector<Condition*>> condition_groups;
    ConditionResource* resource_condition;
    ConditionBuffDuration* buff_condition;
    ConditionVariableBuiltin* builtin_condition;

    //
    // Berserker Rage:
    //
    condition_groups = rotation->all_executors[1]->condition_groups;
    assert(condition_groups.size() == 1 && condition_groups[0].size() == 1);
    // resource "Rage" less 50
    resource_condition = static_cast<ConditionResource*>(condition_groups[0][0]);
    verify_resource_condition(resource_condition, 50.0, Comparator::Less, ResourceType::Rage);

    //
    // Battle Shout
    //
    condition_groups = rotation->all_executors[2]->condition_groups;
    assert(condition_groups.size() == 2);

    // Condition group 0
    assert(condition_groups[0].size() == 1);
    // buff "Battle Shout" less 3
    buff_condition = static_cast<ConditionBuffDuration*>(condition_groups[0][0]);
    verify_buff_condition(buff_condition, "Battle Shout", 3.0, Comparator::Less);

    // Condition group 1
    assert(condition_groups[1].size() == 3);
    // variable "time_remaining_execute" less 10
    builtin_condition = static_cast<ConditionVariableBuiltin*>(condition_groups[1][0]);
    verify_builtin_condition(builtin_condition, BuiltinVariables::TimeRemainingExecute, 10.0, Comparator::Less);
    // variable "time_remaining_execute" greater 0
    builtin_condition = static_cast<ConditionVariableBuiltin*>(condition_groups[1][1]);
    verify_builtin_condition(builtin_condition, BuiltinVariables::TimeRemainingExecute, 0.0, Comparator::Greater);
    // buff "Battle Shout" less 45
    buff_condition = static_cast<ConditionBuffDuration*>(condition_groups[1][2]);
    verify_buff_condition(buff_condition, "Battle Shout", 45.0, Comparator::Less);

    //
    // Heroic Strike
    //
    condition_groups = rotation->all_executors[3]->condition_groups;
    assert(condition_groups.size() == 1 && condition_groups[0].size() == 2);
    // "time_remaining_execute" greater 3
    builtin_condition = static_cast<ConditionVariableBuiltin*>(condition_groups[0][0]);
    verify_builtin_condition(builtin_condition, BuiltinVariables::TimeRemainingExecute, 3.0, Comparator::Greater);
    // resource "Rage" greater 50
    resource_condition = static_cast<ConditionResource*>(condition_groups[0][1]);
    verify_resource_condition(resource_condition, 50.0, Comparator::Greater, ResourceType::Rage);
}

void TestRotationFileReader::test_hunter_aimed_shot_multi_shot() {
    Rotation* rotation = get_rotation("Aimed/Multi-Shot");

    QVector<QString> expected_executor_names = {
        "Rapid Fire",         "Kiss of the Spider",
        "Jom Gabbar",         "Badge of the Swarmguard",
        "Slayer's Crest",     "Earthstrike",
        "Devilsaur Eye",      "Zandalarian Hero Medallion",
        "Blood Fury",         "Berserking",
        "Bestial Wrath",      "Aimed Shot",
        "Multi-Shot",         "Hunter's Mark",
        "Aspect of the Hawk", "Mana Potion",
        "Demonic Rune",       "Night Dragon's Breath",
    };
    assert(rotation->all_executors.size() == expected_executor_names.size());

    verify_executor_names(rotation, rotation->all_executors, expected_executor_names);
}

void TestRotationFileReader::test_paladin_seal_of_the_crusader() {
    Rotation* rotation = get_rotation("Seal of the Crusader");

    QVector<QString> expected_executor_names = {
        "Judgement",
        "Seal of the Crusader",
        "Consecration",
        "Manual Crowd Pummeler",
        "Scrolls of Blinding Light",
        "Kiss of the Spider",
        "Jom Gabbar",
        "Badge of the Swarmguard",
        "Slayer's Crest",
        "Earthstrike",
        "Zandalarian Hero Medallion",
        "Sanctified Orb",
        "Cloudkeeper Legplates",
        "Mana Potion",
        "Demonic Rune",
        "Night Dragon's Breath",
    };
    assert(rotation->all_executors.size() == expected_executor_names.size());
    verify_executor_names(rotation, rotation->all_executors, expected_executor_names);

    QVector<QString> expected_active_executor_names = {
        "Judgement", "Seal of the Crusader", "Mana Potion", "Demonic Rune", "Night Dragon's Breath",
    };
    rotation->link_spells(paladin);
    verify_executor_names(rotation, rotation->active_executors, expected_active_executor_names);
}

void TestRotationFileReader::verify_resource_condition(ConditionResource* condition,
                                                       const double cmp_value,
                                                       const Comparator comparator,
                                                       const ResourceType resource_type) {
    assert(condition != nullptr);
    assert(almost_equal(condition->cmp_value, cmp_value));
    assert(condition->comparator == comparator);
    assert(condition->resource_type == resource_type);
}

void TestRotationFileReader::verify_buff_condition(ConditionBuffDuration* condition,
                                                   const QString& name,
                                                   const double cmp_value,
                                                   const Comparator comparator) {
    assert(condition != nullptr);
    assert(condition->buff->name == name);
    assert(almost_equal(condition->cmp_value, cmp_value));
    assert(condition->comparator == comparator);
}

void TestRotationFileReader::verify_builtin_condition(ConditionVariableBuiltin* condition,
                                                      const BuiltinVariables builtin,
                                                      const double cmp_value,
                                                      const Comparator comparator) {
    assert(condition != nullptr);
    assert(condition->builtin == builtin);
    assert(almost_equal(condition->rhs_value, cmp_value));
    assert(condition->comparator == comparator);
}

void TestRotationFileReader::verify_executor_names(Rotation* rotation, QVector<RotationExecutor*>& executors, QVector<QString>& executor_names) {
    check((executors.size() == executor_names.size()), QString("Mismatched executor size for '%1' (expected %2, got %3)")
                                                           .arg(rotation->get_name())
                                                           .arg(executor_names.size())
                                                           .arg(executors.size())
                                                           .toStdString());

    for (int i = 0; i < executor_names.size(); ++i)
        check((executor_names[i] == executors[i]->get_spell_name()),
              QString("Unexpected executor, expected '%1' got '%2").arg(executor_names[i], executors[i]->get_spell_name()).toStdString());
}

Rotation* TestRotationFileReader::get_rotation(const QString& name) const {
    for (const auto& rotation : rotations) {
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
    this->raid_control = new RaidControl(sim_settings);
    this->warrior = new Warrior(race, equipment_db, sim_settings, raid_control);
}

void TestRotationFileReader::set_up_hunter() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->raid_control = new RaidControl(sim_settings);
    this->hunter = new Hunter(race, equipment_db, sim_settings, raid_control);
}

void TestRotationFileReader::set_up_paladin() {
    this->race = new Human();
    this->sim_settings = new SimSettings;
    this->raid_control = new RaidControl(sim_settings);
    this->paladin = new Paladin(race, equipment_db, sim_settings, raid_control);
}

void TestRotationFileReader::tear_down() {
    delete hunter;
    delete paladin;
    delete warrior;
    delete race;
    delete sim_settings;
    delete raid_control;

    hunter = nullptr;
    paladin = nullptr;
    warrior = nullptr;
}
