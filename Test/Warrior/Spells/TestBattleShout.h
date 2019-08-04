#pragma once

#include "TestSpellWarrior.h"

class BattleShout;

class TestBattleShout: public TestSpellWarrior {
public:
    TestBattleShout(EquipmentDb* equipment_db);

    void test_all();

private:
    BattleShout* battle_shout() const;

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_how_spell_observes_global_cooldown() override;
    void test_whether_spell_causes_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_battle_shout_in_party();
    void test_battle_shout_in_separate_parties();

    void when_battle_shout_is_performed();
    void given_improved_battle_shout_rank(Warrior* warrior, const unsigned num);
};
