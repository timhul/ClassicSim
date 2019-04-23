#include "TestDeathWish.h"

#include "CharacterStats.h"
#include "DeathWish.h"
#include "DeathWishBuff.h"
#include "Fury.h"
#include "Talent.h"

TestDeathWish::TestDeathWish(EquipmentDb *equipment_db) :
    TestSpellWarrior(equipment_db, "Death Wish")
{}

void TestDeathWish::test_all() {
    run_mandatory_tests(false);

    set_up(false);
    test_dmg_mod_reduced_after_buff_expires();
    tear_down();
}

DeathWish* TestDeathWish::death_wish() {
    return dynamic_cast<WarriorSpells*>(warrior->get_spells())->get_death_wish();
}

void TestDeathWish::test_name_correct() {
    assert(death_wish()->get_name() == "Death Wish");
}

void TestDeathWish::test_spell_cooldown() {
    given_death_wish_is_enabled();
    assert(QString::number(death_wish()->get_base_cooldown(), 'f', 3) == "180.000");

    when_death_wish_is_performed();

    then_next_event_is("PlayerAction", "1.500");
    then_next_event_is("BuffRemoval", "30.000");
    then_next_event_is("PlayerAction", "180.000");
}

void TestDeathWish::test_obeys_global_cooldown() {
    given_death_wish_is_enabled();
    given_warrior_has_rage(100);
    assert(death_wish()->get_spell_status() == SpellStatus::Available);

    given_warrior_is_on_gcd();

    assert(death_wish()->get_spell_status() == SpellStatus::OnGCD);
}

void TestDeathWish::test_incurs_global_cooldown() {
    given_death_wish_is_enabled();

    when_death_wish_is_performed();

    then_next_event_is("PlayerAction", QString::number(warrior->global_cooldown(), 'f', 3));
}

void TestDeathWish::test_resource_cost() {
    given_death_wish_is_enabled();
    given_warrior_has_rage(100);

    when_death_wish_is_performed();

    then_warrior_has_rage(90);
}

void TestDeathWish::test_is_ready_conditions() {
    given_death_wish_is_not_enabled();
    given_warrior_has_rage(0);
    assert(warrior->action_ready());
    assert(death_wish()->get_spell_status() == SpellStatus::NotEnabled);

    given_warrior_has_rage(100);
    assert(death_wish()->get_spell_status() == SpellStatus::NotEnabled);

    given_death_wish_is_enabled();
    assert(death_wish()->get_spell_status() == SpellStatus::Available);
}

void TestDeathWish::test_stance_cooldown() {
    given_death_wish_is_enabled();
    given_warrior_in_berserker_stance();
    given_warrior_has_rage(100);
    assert(death_wish()->get_spell_status() == SpellStatus::Available);

    given_warrior_in_battle_stance();
    when_switching_to_berserker_stance();
    given_warrior_has_rage(100);
    assert(warrior->on_stance_cooldown() == true);
    assert(death_wish()->get_spell_status() == SpellStatus::OnGCD);

    given_engine_priority_pushed_forward(0.99);
    assert(warrior->on_stance_cooldown() == true);
    assert(death_wish()->get_spell_status() == SpellStatus::OnStanceCooldown);

    given_engine_priority_pushed_forward(0.02);
    assert(warrior->on_stance_cooldown() == false);
    assert(death_wish()->get_spell_status() == SpellStatus::Available);
}

void TestDeathWish::test_dmg_mod_reduced_after_buff_expires() {
    given_death_wish_is_enabled();
    given_warrior_has_rage(100);

    when_death_wish_is_performed();
    assert(QString::number(pchar->get_stats()->get_total_phys_dmg_mod(), 'f', 3) == "1.200");

    when_running_queued_events_until(30.01);
    assert(QString::number(pchar->get_stats()->get_total_phys_dmg_mod(), 'f', 3) == "1.000");
}

void TestDeathWish::given_death_wish_is_enabled() {
    Talent* talent = Fury(warrior).get_death_wish();

    assert(talent->increment_rank());

    delete talent;

    assert(death_wish()->is_enabled());
    pchar->prepare_set_of_combat_iterations();
}

void TestDeathWish::given_death_wish_is_not_enabled() {
    assert(!death_wish()->is_enabled());
}

void TestDeathWish::when_death_wish_is_performed() {
    death_wish()->perform();
}
