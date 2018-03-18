
#include "OffhandAttack.h"
#include "Warrior.h"

OffhandAttack::OffhandAttack(Engine* engine, Character* pchar, CombatRoll* roll) :
    Spell("Offhand Attack", engine, pchar, roll, 10.0, 0)
{
    this->pchar = dynamic_cast<Warrior*>(pchar);
}

int OffhandAttack::spell_effect(const int) const {
    // TODO: Roll white hit table and damage in order to determine resource generation.
    // TODO: Check if Windfury is up, roll extra attacks.
    // TODO: Take offhand dual-wield penalty into account.
    // TODO: Take dual-wield specialization into account.
    engine->get_statistics()->increment("OH White Total Attempts");

    const int oh_wpn_skill = pchar->get_oh_wpn_skill();
    AttackResult* result = roll->get_melee_hit_result(oh_wpn_skill);

    if (result->is_miss()) {
        add_fail_stats("Miss");
        return 0;
    }
    // TODO: Apply Overpower
    if (result->is_dodge()) {
        add_fail_stats("Dodge");
        return 0;
    }
    if (result->is_parry()) {
        add_fail_stats("Parry");
        return 0;
    }

    // TODO: Remove hardcoded 5/5 Dual-wield specialization.
    int damage_dealt = std::max(1, int(round(pchar->get_oh_dmg() * 0.625)));

    // TODO: Apply Flurry
    if (result->is_critical()) {
        damage_dealt *= 2;
        const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
        add_success_stats("Critical", damage_dealt, rage_gained);
        return rage_gained;
    }
    if (result->is_glancing()) {
        damage_dealt *= roll->get_glancing_blow_dmg_penalty(oh_wpn_skill);
        const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
        add_success_stats("Glancing", damage_dealt, rage_gained);
        return rage_gained;
    }

    const int rage_gained = pchar->rage_gained_from_dd(damage_dealt);
    add_success_stats("Hit", damage_dealt, rage_gained);
    return rage_gained;
}
