#pragma once

#include "TestSpell.h"

class EssenceOfTheRed;

class TestEssenceOfTheRed : public TestSpell {
public:
    TestEssenceOfTheRed(EquipmentDb* _equipment_db);

    void test_all();

private:
    Character* hunter {nullptr};
    Character* rogue {nullptr};
    Character* warrior {nullptr};

    EssenceOfTheRed* essence_of_the_red() const;

    void set_up_general();
    void set_up_hunter();
    void set_up_rogue();
    void set_up_warrior();
    void tear_down();

    void test_name_correct();
    void test_hunter_gains_mana_after_combat_start();
    void test_rogue_gains_energy_after_combat_start();
    void test_warrior_gains_rage_after_combat_start();
};
