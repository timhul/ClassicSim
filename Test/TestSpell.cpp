
#include "TestSpell.h"

#include "Orc.h"
#include "CombatRoll.h"
#include "MeleeSpecialTable.h"
#include "Engine.h"
#include "Equipment.h"
#include "Target.h"
#include "Character.h"

void TestSpell::set_up_general() {
    // not thread safe
    engine = new Engine();
    equipment = new Equipment();
    target = new Target(63);
    combat = new CombatRoll(target);
    race = new Orc();
}

void TestSpell::tear_down_general() {
    // not thread safe
    delete engine;
    delete equipment;
    delete combat;
    delete target;
    delete race;
}

void TestSpell::given_no_previous_damage_dealt() {
    then_damage_dealt_is(0);
}

void TestSpell::given_a_guaranteed_melee_ability_crit() {
    MeleeSpecialTable* table = combat->get_melee_special_table(pchar->get_mh_wpn_skill());
    table->set_miss_range(0);
    table->set_dodge_range(0);
    table->set_parry_range(0);
    table->set_block_range(0);
    table->update_crit_chance(1.0);

    assert(table->get_outcome(0, 0.0) == Outcome::CRITICAL);
    assert(table->get_outcome(9999, 0.0) == Outcome::CRITICAL);
}

void TestSpell::then_damage_dealt_is(const int damage) {
    assert(engine->get_statistics()->get_total_damage() == damage);
}
