#include "IncomingDamageEvent.h"

#include "Character.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "Engine.h"
#include "MainhandAttack.h"
#include "Mechanics.h"
#include "PhysicalAttackResult.h"

IncomingDamageEvent::IncomingDamageEvent(Character* character, Engine* engine, const int timestamp) :
    Event(EventType::IncomingDamage, static_cast<double>(timestamp)), character(character), roll(new CombatRoll(character)), engine(engine) {}

void IncomingDamageEvent::act() {
    engine->add_event(new IncomingDamageEvent(character, engine, engine->get_current_priority() + 1.5));

    auto result = roll->get_melee_hit_result(300, 500);

    if (result == PhysicalAttackResult::MISS)
        return;

    if (result == PhysicalAttackResult::DODGE)
        // impl revenge
        return;

    if (result == PhysicalAttackResult::PARRY) {
        character->get_spells()->get_mh_attack()->update_next_expected_use_for_parry();
        character->get_spells()->get_mh_attack()->add_next_mh_attack();
        // impl revenge
        return;
    }

    if (result == PhysicalAttackResult::BLOCK || result == PhysicalAttackResult::BLOCK_CRITICAL)
        // imply revenge
        return;

    auto armor = character->get_stats()->get_armor();
    auto reduction = Mechanics::get_reduction_from_armor(armor, 63);
    double damage_dealt = 2200 * (1 - reduction);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt = round(damage_dealt * 2);
    }

    // NYI
    /* if (result == PhysicalAttackResult::CRUSHING) { */
    /*   damage_dealt = round(damage_dealt * 1.5); */
    /* } */

    character->gain_rage(damage_dealt / 90);
}
