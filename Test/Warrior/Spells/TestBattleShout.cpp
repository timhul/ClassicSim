#include "TestBattleShout.h"

#include "BattleShout.h"

TestBattleShout::TestBattleShout(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Battle Shout")
{}

void TestBattleShout::test_all() {
    run_mandatory_tests();
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
