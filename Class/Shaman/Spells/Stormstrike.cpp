#include "Stormstrike.h"

#include "Buff.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Shaman.h"
#include "ShamanSpells.h"
#include "StormstrikeBuff.h"

Stormstrike::Stormstrike(Shaman* pchar, ShamanSpells* spells) :
    Spell("Stormstrike", "Assets/spell/Spell_holy_sealofmight.png", pchar, new CooldownControl(pchar, 12.0), RestrictedByGcd::Yes, ResourceType::Mana, 319),
    TalentRequirer(QVector<TalentRequirerInfo*>{new TalentRequirerInfo("Stormstrike", 1, DisabledAtZero::Yes)}),
    shaman(pchar),
    spells(spells),
    stormstrike_buff(new StormstrikeBuff(pchar))
{
    this->enabled = false;
}

Stormstrike::~Stormstrike() {
    if (stormstrike_buff->is_enabled())
        stormstrike_buff->disable_buff();

    delete stormstrike_buff;
    delete cooldown;
}

void Stormstrike::spell_effect() {
    const int result = roll->get_melee_ability_result(shaman->get_mh_wpn_skill(), pchar->get_stats()->get_mh_crit_chance());

    cooldown->add_spell_cd_event();
    cooldown->add_gcd_event();

    if (result == PhysicalAttackResult::MISS) {
        increment_miss();
        shaman->lose_mana(resource_cost);
        return;
    }
    if (result == PhysicalAttackResult::DODGE) {
        increment_dodge();
        shaman->lose_mana(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }
    if (result == PhysicalAttackResult::PARRY) {
        increment_parry();
        shaman->lose_mana(static_cast<unsigned>(round(resource_cost * 0.25)));
        return;
    }

    double damage_dealt = damage_after_modifiers(shaman->get_random_normalized_mh_dmg());

    if (result == PhysicalAttackResult::CRITICAL) {
        damage_dealt *= shaman->get_stats()->get_melee_ability_crit_dmg_mod();
        shaman->melee_mh_yellow_critical_effect();
        add_crit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }
    else if (result == PhysicalAttackResult::HIT) {
        shaman->melee_mh_yellow_hit_effect();
        add_hit_dmg(static_cast<int>(round(damage_dealt)), resource_cost, pchar->global_cooldown());
    }

    shaman->lose_mana(resource_cost);
    stormstrike_buff->apply_buff();
}

void Stormstrike::increase_talent_rank_effect(const QString&, const int) {
    stormstrike_buff->enable_buff();
}

void Stormstrike::decrease_talent_rank_effect(const QString&, const int) {
    stormstrike_buff->disable_buff();
}
