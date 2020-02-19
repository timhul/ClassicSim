#include "TestConsecration.h"

#include <cassert>

#include "CharacterStats.h"
#include "Consecration.h"
#include "Equipment.h"
#include "Event.h"
#include "HolyPaladin.h"
#include "Paladin.h"
#include "PaladinSpells.h"
#include "Retribution.h"
#include "SanctityAura.h"
#include "Talent.h"

TestConsecration::TestConsecration(EquipmentDb* equipment_db) : TestSpellPaladin(equipment_db, "Consecration") {}

void TestConsecration::test_all() {
    run_mandatory_tests(false);

    set_up(false);
    test_damage();
    tear_down();

    set_up(false);
    test_damage_sanctity_aura();
    tear_down();
}

Consecration* TestConsecration::consecration() const {
    return static_cast<Consecration*>(get_max_rank_spell_by_name("Consecration"));
}

void TestConsecration::test_name_correct() {
    assert(consecration()->get_name() == "Consecration");
}

void TestConsecration::test_spell_cooldown() {
    assert(almost_equal(consecration()->get_base_cooldown(), 8.0));
}

void TestConsecration::test_how_spell_observes_global_cooldown() {
    given_consecration_is_enabled();
    assert(consecration()->get_spell_status() == SpellStatus::Available);

    given_paladin_is_on_gcd();

    assert(consecration()->get_spell_status() == SpellStatus::OnGCD);
}

void TestConsecration::test_whether_spell_causes_global_cooldown() {
    given_consecration_is_enabled();
    assert(paladin->action_ready());

    when_consecration_is_performed();

    assert(!paladin->action_ready());
}

void TestConsecration::test_resource_cost() {
    given_consecration_is_enabled();

    given_paladin_has_mana(564);
    assert(consecration()->get_spell_status() == SpellStatus::InsufficientResources);

    given_paladin_has_mana(565);
    assert(consecration()->get_spell_status() == SpellStatus::Available);

    given_paladin_has_mana(566);
    when_consecration_is_performed();
    then_paladin_has_mana(1);
}

void TestConsecration::test_is_ready_conditions() {
    assert(consecration()->get_spell_status() == SpellStatus::NotEnabled);

    given_consecration_is_enabled();

    assert(consecration()->get_spell_status() == SpellStatus::Available);
}

void TestConsecration::test_damage() {
    given_event_is_ignored(EventType::BuffRemoval);
    given_event_is_ignored(EventType::PlayerAction);
    given_consecration_is_enabled();
    given_character_has_spell_damage(100, MagicSchool::Holy);
    given_a_guaranteed_magic_hit(MagicSchool::Holy);

    when_consecration_is_performed();
    // Duplicate is resource tick
    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "2.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "4.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "4.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "6.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "6.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "8.000", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "8.000", RUN_EVENT);

    // [Damage] = base_dmg + holy_spell_dmg * spell_coefficient
    // [417] = 384 + 100 * 0.33
    then_damage_dealt_is(417);
}

void TestConsecration::test_damage_sanctity_aura() {
    given_event_is_ignored(EventType::BuffRemoval);
    given_event_is_ignored(EventType::PlayerAction);
    given_character_has_spell_damage(100, MagicSchool::Holy);
    given_a_guaranteed_magic_hit(MagicSchool::Holy);
    given_retribution_talent_rank("Sanctity Aura", 1);
    given_consecration_is_enabled();

    get_max_rank_spell_by_name("Sanctity Aura")->perform();
    given_engine_priority_pushed_forward(1.5);

    when_consecration_is_performed();

    // Duplicate is resource tick
    then_next_event_is(EventType::DotTick, "3.500", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "3.500", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "5.500", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "5.500", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "7.500", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "7.500", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "9.500", RUN_EVENT);
    then_next_event_is(EventType::DotTick, "9.500", RUN_EVENT);

    // [Damage] = (base_dmg + holy_spell_dmg * spell_coefficient) * holy_dmg_mod
    // [458] = (384 + 100 * 0.33) * 1.1
    then_damage_dealt_is(458);
}

void TestConsecration::given_consecration_is_enabled() {
    given_holy_talent_rank("Consecration", 1);
    assert(consecration()->is_enabled());
    paladin->prepare_set_of_combat_iterations();
}

void TestConsecration::when_consecration_is_performed() {
    consecration()->perform();
}
