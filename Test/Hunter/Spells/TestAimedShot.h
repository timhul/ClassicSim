#ifndef TESTAIMEDSHOT_H
#define TESTAIMEDSHOT_H

#include "TestSpellHunter.h"

class AimedShot;
class MultiShot;

class TestAimedShot: public TestSpellHunter {
public:
    TestAimedShot(EquipmentDb *equipment_db);

    void test_all();

private:
    AimedShot* aimed_shot();
    MultiShot* multi_shot();

    void test_name_correct() override;
    void test_spell_cooldown() override;
    void test_incurs_global_cooldown() override;
    void test_obeys_global_cooldown() override;
    void test_resource_cost() override;
    void test_is_ready_conditions() override;

    void test_hit_dmg();
    void test_crit_dmg();
    void test_aimed_shot_adds_player_action_event_on_completion();
    void test_aimed_shot_cast_in_progress_blocks_other_spells();

    void given_aimed_shot_is_enabled();
    void when_aimed_shot_is_performed();
};

#endif // TESTAIMEDSHOT_H
