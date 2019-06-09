#include "TestBattleShout.h"

#include "BattleShout.h"
#include "CharacterStats.h"
#include "Fury.h"
#include "SpellRankGroup.h"
#include "Warrior.h"

TestBattleShout::TestBattleShout(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Battle Shout")
{}

void TestBattleShout::test_all() {
    run_mandatory_tests();

    set_up();
    test_battle_shout_in_party();
    tear_down();

    set_up();
    test_battle_shout_in_separate_parties();
    tear_down();
}

BattleShout* TestBattleShout::battle_shout() {
    return dynamic_cast<BattleShout*>(get_max_rank_spell_by_name("Battle Shout"));
}

void TestBattleShout::test_name_correct() {
    assert(battle_shout()->get_name() == "Battle Shout");
}

void TestBattleShout::test_spell_cooldown() {
    assert(QString::number(battle_shout()->get_base_cooldown(), 'f', 3) == "0.000");
}

void TestBattleShout::test_stance_cooldown() {

}

void TestBattleShout::test_resource_cost() {
    given_warrior_has_rage(9);
    assert(battle_shout()->get_spell_status() == SpellStatus::InsufficientResources);

    given_warrior_has_rage(11);

    when_battle_shout_is_performed();

    then_warrior_has_rage(1);
}

void TestBattleShout::test_is_ready_conditions() {
    given_warrior_has_rage(10);
    assert(!warrior->on_global_cooldown());
    assert(!warrior->on_stance_cooldown());

    assert(battle_shout()->get_spell_status() == SpellStatus::Available);
}

void TestBattleShout::test_whether_spell_causes_global_cooldown() {
    assert(warrior->on_global_cooldown() == false);
    given_engine_priority_at(0.0);

    when_battle_shout_is_performed();

    assert(warrior->on_global_cooldown());
    given_engine_priority_at(1.49);
    assert(warrior->on_global_cooldown());
    given_engine_priority_at(1.51);
    assert(warrior->on_global_cooldown() == false);
}

void TestBattleShout::test_how_spell_observes_global_cooldown() {
    assert(battle_shout()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(battle_shout()->get_spell_status() == SpellStatus::OnGCD);
}

void TestBattleShout::when_battle_shout_is_performed() {
    battle_shout()->perform();
}

void TestBattleShout::given_improved_battle_shout_rank(Warrior* warrior, const unsigned num) {
    given_talent_rank(Fury(warrior).get_improved_battle_shout(), num);
}

void TestBattleShout::test_battle_shout_in_party() {
    auto* warr_1 = new Warrior(race, equipment_db, sim_settings, target, raid_control);
    auto* warr_2 = new Warrior(race, equipment_db, sim_settings, target, raid_control);

    given_improved_battle_shout_rank(warr_1, 5);
    given_improved_battle_shout_rank(warr_2, 5);

    const unsigned warr_1_melee_ap_before = warr_1->get_stats()->get_melee_ap();
    const unsigned warr_2_melee_ap_before = warr_2->get_stats()->get_melee_ap();

    warr_1->gain_rage(10);
    warr_1->get_spells()->get_spell_rank_group_by_name("Battle Shout")->get_max_available_spell_rank()->perform();

    // [melee_ap] = base_ap * improved_battle_shout
    // [290] = 232 * 1.25
    assert(warr_1->get_stats()->get_melee_ap() == warr_1_melee_ap_before + 290);
    assert(warr_2->get_stats()->get_melee_ap() == warr_2_melee_ap_before + 290);

    // Assert does not stack.
    warr_2->gain_rage(10);
    warr_2->get_spells()->get_spell_rank_group_by_name("Battle Shout")->get_max_available_spell_rank()->perform();

    assert(warr_1->get_stats()->get_melee_ap() == warr_1_melee_ap_before + 290);
    assert(warr_2->get_stats()->get_melee_ap() == warr_2_melee_ap_before + 290);

    delete warr_1;
    delete warr_2;
}

void TestBattleShout::test_battle_shout_in_separate_parties() {
    auto* warr_1 = new Warrior(race, equipment_db, sim_settings, target, raid_control, 0, 1);
    auto* warr_2 = new Warrior(race, equipment_db, sim_settings, target, raid_control, 1, 0);

    const unsigned warr_1_melee_ap_before = warr_1->get_stats()->get_melee_ap();
    const unsigned warr_2_melee_ap_before = warr_2->get_stats()->get_melee_ap();

    warr_1->gain_rage(10);
    warr_1->get_spells()->get_spell_rank_group_by_name("Battle Shout")->get_max_available_spell_rank()->perform();

    assert(warr_1->get_stats()->get_melee_ap() == warr_1_melee_ap_before + 232);
    assert(warr_2->get_stats()->get_melee_ap() == warr_2_melee_ap_before);

    warr_2->gain_rage(10);
    warr_2->get_spells()->get_spell_rank_group_by_name("Battle Shout")->get_max_available_spell_rank()->perform();

    assert(warr_1->get_stats()->get_melee_ap() == warr_1_melee_ap_before + 232);
    assert(warr_2->get_stats()->get_melee_ap() == warr_2_melee_ap_before + 232);

    delete warr_1;
    delete warr_2;
}
