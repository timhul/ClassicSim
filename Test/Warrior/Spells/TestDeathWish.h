#ifndef TESTDEATHWISH_H
#define TESTDEATHWISH_H

#include "TestSpellWarrior.h"

class DeathWish;

class TestDeathWish: public TestSpellWarrior {
public:
    TestDeathWish(EquipmentDb *equipment_db);

    void test_all();

    DeathWish* death_wish();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_dmg_mod_reduced_after_buff_expires();

    void given_death_wish_is_enabled();
    void given_death_wish_is_not_enabled();

    void when_death_wish_is_performed();

private:
};

#endif // TESTDEATHWISH_H
