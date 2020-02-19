#pragma once

#include "TestSpellPaladin.h"

class MainhandAttackPaladin;
class Consecration;

class TestConsecration : public TestSpellPaladin {
public:
    TestConsecration(EquipmentDb* equipment_db);

    void test_all();

private:
    Consecration* consecration() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_damage();
    void test_damage_sanctity_aura();

    void given_consecration_is_enabled();
    void when_consecration_is_performed();
};
