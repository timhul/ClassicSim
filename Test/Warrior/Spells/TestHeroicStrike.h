#ifndef TESTHEROICSTRIKE_H
#define TESTHEROICSTRIKE_H

#include "TestSpellWarrior.h"

class HeroicStrike;

class TestHeroicStrike: public TestSpellWarrior {
public:
    TestHeroicStrike(EquipmentDb *equipment_db);

    void test_all();

private:
    HeroicStrike* heroic_strike();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_stance_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_1_of_3_improved_hs_reduces_rage_cost();
    void test_2_of_3_improved_hs_reduces_rage_cost();
    void test_3_of_3_improved_hs_reduces_rage_cost();
    void test_removing_points_in_improved_hs_increases_rage_cost();
    void test_hit_dmg();
    void test_crit_dmg_0_of_2_impale();
    void test_crit_dmg_1_of_2_impale();
    void test_crit_dmg_2_of_2_impale();
    void test_dodge_applies_overpower_buff();

    void given_0_of_3_improved_hs();
    void given_1_of_3_improved_hs();
    void given_2_of_3_improved_hs();
    void given_3_of_3_improved_hs();
    void given_user_has_activated_heroic_strike();
    void given_user_has_not_activate_heroic_strike();

    void when_heroic_strike_is_performed();

    void then_heroic_strike_costs(const unsigned rage);
};

#endif // TESTHEROICSTRIKE_H
