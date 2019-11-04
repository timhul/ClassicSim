#pragma once

#include "TestObject.h"

class Character;
class ConditionResource;
class Engine;
class EquipmentDb;
class Hunter;
class Race;
class RaidControl;
class Rogue;
class SimSettings;
class Warrior;

enum class ResourceType: int;

class TestConditionResource : TestObject {
public:
    TestConditionResource(EquipmentDb* equipment_db);
    void test_all() override;

private:
    void test_values_after_initialization() override;

    void test_resource_less(Character* pchar, const ResourceType resource_type);
    void test_resource_leq(Character* pchar, const ResourceType resource_type);
    void test_resource_eq(Character* pchar, const ResourceType resource_type);
    void test_resource_geq(Character* pchar, const ResourceType resource_type);
    void test_resource_greater(Character* pchar, const ResourceType resource_type);

    Hunter* hunter {nullptr};
    Rogue* rogue {nullptr};
    Warrior* warrior {nullptr};
    Race* race {nullptr};
    SimSettings* sim_settings {nullptr};
    RaidControl* raid_control {nullptr};

    void set_up_rogue();
    void set_up_hunter();
    void set_up_warrior();

    void tear_down();

    void given_character_has_resource(Character* pchar, const ResourceType resource_type, const unsigned resource_level);
};
