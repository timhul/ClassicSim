#pragma once

#include "TestSpellWarrior.h"

class TestOverpower: public TestSpellWarrior {
public:
    TestOverpower(EquipmentDb *equipment_db);

    void test_all();

private:
    Overpower* overpower() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg_0_of_2_impale();
    void test_crit_dmg_1_of_2_impale();
    void test_crit_dmg_2_of_2_impale();
    void test_overpower_hit_removes_buff();
    void test_overpower_crit_removes_buff();
    void test_overpower_miss_removes_buff();

    void given_no_overpower_buff();

    void when_overpower_is_performed();
    void when_overpower_buff_is_applied();

    void then_overpower_is_inactive();
};
