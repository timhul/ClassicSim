#pragma once

#include "TestSpell.h"

class Character;

enum class ResourceType : int;

class TestSpellDamage : public TestSpell {
public:
    TestSpellDamage(EquipmentDb* equipment_db, QString spell_under_test);

    virtual ~TestSpellDamage();

    void run_mandatory_tests(const bool prepare_combat_iterations = true);
    virtual void run_class_specific_tests();

    virtual void set_up(const bool prepare_combat_iterations = true) = 0;
    virtual void tear_down() = 0;

    virtual void test_name_correct() = 0;
    virtual void test_how_spell_observes_global_cooldown() = 0;
    virtual void test_whether_spell_causes_global_cooldown() = 0;
    virtual void test_spell_cooldown() = 0;
    virtual void test_resource_cost() = 0;
    virtual void test_is_ready_conditions() = 0;

protected:
    void then_character_has_resource(Character* pchar, const ResourceType resource_type, const unsigned resource_level);

private:
    bool has_run_mandatory_tests;
};
