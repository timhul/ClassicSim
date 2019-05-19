#include "Hamstring.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Utils/Check.h"
#include "Warrior.h"
#include "WarriorSpells.h"

Hamstring::Hamstring(Warrior* pchar, WarriorSpells* spells) :
    Spell("Hamstring", "Assets/ability/Ability_shockwave.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Rage, 10),
    ItemModificationRequirer({16484, 16548, 22868, 23286}),
    warr(pchar),
    spells(spells)
{}

Hamstring::~Hamstring() {
    delete cooldown;
}

void Hamstring::spell_effect() {
    const int result = roll->get_melee_ability_result(warr->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    cooldown->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        warr->lose_rage(resource_cost);
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        spells->get_overpower_buff()->apply_buff();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        warr->lose_rage(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double damage_dealt = damage_after_modifiers(45);

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= warr->get_stats()->get_melee_ability_crit_dmg_mod();
        warr->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == PhysicalAttackResult::HIT) {
        warr->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    warr->lose_rage(resource_cost);
}

void Hamstring::activate_item_effect(const int item_id) {
    switch (item_id) {
    case 16484:
    case 16548:
    case 22868:
    case 23286:
        resource_cost -= 3;
        break;
    default:
        check(false, "Hamstring::activate_item_effect reached end of switch");
    }
}

void Hamstring::deactivate_item_effect(const int item_id) {
    switch (item_id) {
    case 16484:
    case 16548:
    case 22868:
    case 23286:
        resource_cost += 3;
        break;
    default:
        check(false, "Hamstring::deactivate_item_effect reached end of switch");
    }
}
