#include "ArcaneMissiles.h"

#include "Buff.h"
#include "Character.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "MageSpells.h"
#include "NoEffectUniqueDebuff.h"
#include "SimSettings.h"
#include "Utils/Check.h"

ArcaneMissiles::ArcaneMissiles(Character* pchar, MageSpells* spells, const int spell_rank) :
    SpellPeriodic("Arcane Missiles", "Assets/spell/Spell_nature_starfall.png", pchar,
                  new NoEffectUniqueDebuff(pchar, Priority::Low, 5),
                  RestrictedByGcd::Yes, ResourceType::Mana,
                  1.0, 0, spell_rank),
    CastingTimeRequirer(pchar, SuppressibleCast::No, 5000),
    mage_spells(spells)
{
    switch (spell_rank) {
    case 1:
        damage_per_missile = 24;
        resource_cost = 85;
        casting_time_ms = 3000;
        level_req = 8;
        break;
    case 2:
        damage_per_missile = 36;
        resource_cost = 140;
        casting_time_ms = 4000;
        level_req = 16;
        break;
    case 3:
        damage_per_missile = 56;
        resource_cost = 235;
        casting_time_ms = 5000;
        level_req = 24;
        break;
    case 4:
        damage_per_missile = 83;
        resource_cost = 320;
        casting_time_ms = 5000;
        level_req = 32;
        break;
    case 5:
        damage_per_missile = 115;
        resource_cost = 410;
        casting_time_ms = 5000;
        level_req = 40;
        break;
    case 6:
        damage_per_missile = 151;
        resource_cost = 500;
        casting_time_ms = 5000;
        level_req = 48;
        break;
    case 7:
        damage_per_missile = 192;
        resource_cost = 595;
        casting_time_ms = 5000;
        level_req = 56;
        break;
    case 8:
        damage_per_missile = 230;
        resource_cost = 655;
        casting_time_ms = 5000;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    enabled = true;
    marker_buff->enable_buff();
}

ArcaneMissiles::~ArcaneMissiles() {
    delete marker_buff;
}

bool ArcaneMissiles::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 7)
        return pchar->get_clvl() >= level_req;

    if (spell_rank == 8)
        return pchar->get_clvl() >= 60 && static_cast<int>(pchar->get_sim_settings()->get_phase()) >= 5;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void ArcaneMissiles::complete_cast_effect() {
    marker_buff->cancel_buff();
}

bool ArcaneMissiles::check_application_success() {
    cooldown->add_gcd_event();

    if (!mage_spells->clearcasting_active())
        pchar->lose_mana(static_cast<unsigned>(round(get_resource_cost())));

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Arcane, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane));
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Arcane);

    if (hit_roll == MagicAttackResult::MISS) {
        increment_miss();
        mage_spells->get_enigma_5p_buff()->apply_buff();
        return false;
    }
    if (resist_roll == MagicResistResult::FULL_RESIST) {
        increment_full_resist();
        mage_spells->get_enigma_5p_buff()->apply_buff();
        return false;
    }

    return true;
}

void ArcaneMissiles::new_application_effect() {
    start_cast();
}

void ArcaneMissiles::refresh_effect() {

}

void ArcaneMissiles::reset_effect() {

}

void ArcaneMissiles::tick_effect() {
    add_next_tick();

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Arcane, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane));
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Arcane);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    double damage_dealt = damage_per_missile + pchar->get_stats()->get_spell_damage(MagicSchool::Arcane) * 0.2;
    damage_dealt *= get_partial_resist_dmg_modifier(resist_roll);
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect(MagicSchool::Arcane);
        damage_dealt = round(damage_dealt * pchar->get_stats()->get_spell_crit_dmg_mod());
        add_spell_crit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0, resist_roll);
    }
    else {
        pchar->spell_hit_effect(MagicSchool::Arcane);
        damage_dealt = round(damage_dealt);
        add_spell_hit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0, resist_roll);
    }

    mage_spells->roll_clearcasting();
    mage_spells->roll_netherwind_focus();
}
