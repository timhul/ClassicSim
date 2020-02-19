#include "TestConditionResource.h"

#include "CharacterSpells.h"
#include "ConditionResource.h"
#include "Hunter.h"
#include "Orc.h"
#include "RaidControl.h"
#include "Rogue.h"
#include "SimSettings.h"
#include "Warrior.h"

TestConditionResource::TestConditionResource(EquipmentDb* equipment_db_) : TestObject(equipment_db_) {}

void TestConditionResource::test_all() {
    qDebug() << "TestConditionResource";
    test_values_after_initialization();

    set_up_warrior();
    test_resource_less(warrior, ResourceType::Rage);
    tear_down();

    set_up_rogue();
    test_resource_less(rogue, ResourceType::Energy);
    tear_down();

    set_up_hunter();
    test_resource_less(hunter, ResourceType::Mana);
    tear_down();

    set_up_warrior();
    test_resource_leq(warrior, ResourceType::Rage);
    tear_down();

    set_up_rogue();
    test_resource_leq(rogue, ResourceType::Energy);
    tear_down();

    set_up_hunter();
    test_resource_leq(hunter, ResourceType::Mana);
    tear_down();

    set_up_warrior();
    test_resource_eq(warrior, ResourceType::Rage);
    tear_down();

    set_up_rogue();
    test_resource_eq(rogue, ResourceType::Energy);
    tear_down();

    set_up_hunter();
    test_resource_eq(hunter, ResourceType::Mana);
    tear_down();

    set_up_warrior();
    test_resource_geq(warrior, ResourceType::Rage);
    tear_down();

    set_up_rogue();
    test_resource_geq(rogue, ResourceType::Energy);
    tear_down();

    set_up_hunter();
    test_resource_geq(hunter, ResourceType::Mana);
    tear_down();

    set_up_warrior();
    test_resource_greater(warrior, ResourceType::Rage);
    tear_down();

    set_up_rogue();
    test_resource_greater(rogue, ResourceType::Energy);
    tear_down();

    set_up_hunter();
    test_resource_greater(hunter, ResourceType::Mana);
    tear_down();
}

void TestConditionResource::test_values_after_initialization() {}

void TestConditionResource::test_resource_less(Character* pchar, const ResourceType resource_type) {
    ConditionResource condition(pchar, Comparator::Less, resource_type, 50);

    given_character_has_resource(pchar, resource_type, 0);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 49);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 50);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 51);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 100);
    assert(condition.condition_fulfilled() == false);
}

void TestConditionResource::test_resource_leq(Character* pchar, const ResourceType resource_type) {
    ConditionResource condition(pchar, Comparator::Leq, resource_type, 50);

    given_character_has_resource(pchar, resource_type, 0);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 49);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 50);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 51);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 100);
    assert(condition.condition_fulfilled() == false);
}

void TestConditionResource::test_resource_eq(Character* pchar, const ResourceType resource_type) {
    ConditionResource condition(pchar, Comparator::Eq, resource_type, 50);

    given_character_has_resource(pchar, resource_type, 0);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 49);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 50);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 51);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 100);
    assert(condition.condition_fulfilled() == false);
}

void TestConditionResource::test_resource_geq(Character* pchar, const ResourceType resource_type) {
    ConditionResource condition(pchar, Comparator::Geq, resource_type, 50);

    given_character_has_resource(pchar, resource_type, 0);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 49);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 50);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 51);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 100);
    assert(condition.condition_fulfilled() == true);
}

void TestConditionResource::test_resource_greater(Character* pchar, const ResourceType resource_type) {
    ConditionResource condition(pchar, Comparator::Greater, resource_type, 50);

    given_character_has_resource(pchar, resource_type, 0);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 49);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 50);
    assert(condition.condition_fulfilled() == false);

    given_character_has_resource(pchar, resource_type, 51);
    assert(condition.condition_fulfilled() == true);

    given_character_has_resource(pchar, resource_type, 100);
    assert(condition.condition_fulfilled() == true);
}

void TestConditionResource::set_up_rogue() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->raid_control = new RaidControl(sim_settings);
    this->rogue = new Rogue(race, equipment_db, sim_settings, raid_control);
}

void TestConditionResource::set_up_hunter() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->raid_control = new RaidControl(sim_settings);
    this->hunter = new Hunter(race, equipment_db, sim_settings, raid_control);
}

void TestConditionResource::set_up_warrior() {
    this->race = new Orc();
    this->sim_settings = new SimSettings();
    this->raid_control = new RaidControl(sim_settings);
    this->warrior = new Warrior(race, equipment_db, sim_settings, raid_control);
}

void TestConditionResource::tear_down() {
    delete rogue;
    delete hunter;
    delete warrior;
    delete race;
    delete sim_settings;
    delete raid_control;

    rogue = nullptr;
    hunter = nullptr;
    warrior = nullptr;
}

void TestConditionResource::given_character_has_resource(Character* pchar, const ResourceType resource_type, const unsigned resource_level) {
    const unsigned curr_level = pchar->get_resource_level(resource_type);

    if (curr_level < resource_level)
        pchar->gain_resource(resource_type, resource_level - curr_level);
    else if (curr_level > resource_level)
        pchar->lose_resource(resource_type, curr_level - resource_level);

    assert(pchar->get_resource_level(resource_type) == resource_level);
}
