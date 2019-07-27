#pragma once

#include "TestTalentTree.h"

class TestFeralCombat: public TestTalentTree {
public:
    TestFeralCombat(EquipmentDb* equipment_db);

private:
    void set_up() override;
    void tear_down() override;

    void test_spending_talent_points() override;
    void test_clearing_tree_after_filling() override;
    void test_refilling_tree_after_switching_talent_setup() override;

    void spec_feral_combat();
};
