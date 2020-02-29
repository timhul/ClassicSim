#include "ShadowBolt.h"

#include <cmath>

#include "Buff.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "ImprovedShadowBolt.h"
#include "Random.h"
#include "SimSettings.h"
#include "Utils/Check.h"
#include "Warlock.h"
#include "WarlockSpells.h"

ShadowBolt::ShadowBolt(Warlock* warlock, WarlockSpells* warlock_spells, const int spell_rank_, ImprovedShadowBolt* imp_sb) :
    Spell("Shadow Bolt",
          "Assets/spell/Spell_shadow_shadowbolt.png",
          warlock,
          new CooldownControl(warlock, 0.0),
          RestrictedByGcd::Yes,
          ResourceType::Mana,
          0,
          spell_rank_),
    CastingTimeRequirer(pchar, SuppressibleCast::Yes, 3000),
    TalentRequirer(QVector<TalentRequirerInfo*> {
        new TalentRequirerInfo("Improved Shadow Bolt", 5, DisabledAtZero::No),
        new TalentRequirerInfo("Cataclysm", 5, DisabledAtZero::No),
        new TalentRequirerInfo("Bane", 5, DisabledAtZero::No),
        new TalentRequirerInfo("Devastation", 5, DisabledAtZero::No),
        new TalentRequirerInfo("Ruin", 1, DisabledAtZero::No),
    }),
    imp_sb(imp_sb),
    warlock_spells(warlock_spells) {
    switch (spell_rank) {
    case 1:
        base_damage_min = 13;
        base_damage_max = 18;
        base_resource_cost = 25;
        base_casting_time_ms = 1700;
        level_req = 1;
        break;
    case 2:
        base_damage_min = 26;
        base_damage_max = 32;
        base_resource_cost = 40;
        base_casting_time_ms = 2200;
        level_req = 6;
        break;
    case 3:
        base_damage_min = 52;
        base_damage_max = 61;
        base_resource_cost = 70;
        base_casting_time_ms = 2800;
        level_req = 12;
        break;
    case 4:
        base_damage_min = 92;
        base_damage_max = 104;
        base_resource_cost = 110;
        base_casting_time_ms = 3000;
        level_req = 20;
        break;
    case 5:
        base_damage_min = 150;
        base_damage_max = 170;
        base_resource_cost = 160;
        base_casting_time_ms = 3000;
        level_req = 28;
        break;
    case 6:
        base_damage_min = 213;
        base_damage_max = 240;
        base_resource_cost = 210;
        base_casting_time_ms = 3000;
        level_req = 36;
        break;
    case 7:
        base_damage_min = 292;
        base_damage_max = 327;
        base_resource_cost = 265;
        base_casting_time_ms = 3000;
        level_req = 44;
        break;
    case 8:
        base_damage_min = 373;
        base_damage_max = 415;
        base_resource_cost = 315;
        base_casting_time_ms = 3000;
        level_req = 52;
        break;
    case 9:
        base_damage_min = 455;
        base_damage_max = 507;
        base_resource_cost = 370;
        base_casting_time_ms = 3000;
        level_req = 60;
        break;
    case 10:
        base_damage_min = 482;
        base_damage_max = 538;
        base_resource_cost = 380;
        base_casting_time_ms = 3000;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    this->instant_dmg = new Random(base_damage_min, base_damage_max);
    this->casting_time_ms = base_casting_time_ms;
    this->spell_dmg_coefficient = CastingTimeRequirer::spell_coefficient_from_casting_time(casting_time_ms, level_req);
    this->resource_cost = base_resource_cost;
}

ShadowBolt::~ShadowBolt() {
    delete cooldown;
    delete instant_dmg;
}

bool ShadowBolt::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 9)
        return pchar->get_clvl() >= level_req;

    if (spell_rank == 10)
        return pchar->get_clvl() >= 60 && static_cast<int>(pchar->get_sim_settings()->get_phase()) >= 5;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void ShadowBolt::spell_effect() {
    pchar->get_spells()->stop_attack();
    cooldown->add_gcd_event();
    start_cast();
}

void ShadowBolt::complete_cast_effect() {
    pchar->lose_mana(resource_cost);

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Shadow,
                                                        pchar->get_stats()->get_spell_crit_chance(MagicSchool::Shadow) + devastation_bonus);
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Shadow);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    double damage_dealt = instant_dmg->get_roll() + pchar->get_stats()->get_spell_damage(MagicSchool::Shadow) * spell_dmg_coefficient;
    damage_dealt *= get_partial_resist_dmg_modifier(resist_roll);
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Shadow);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        if (apply_imp_sb)
            imp_sb->apply_buff();

        pchar->spell_critical_effect(MagicSchool::Shadow);
        const double spell_crit_dmg_mod = 1 + (pchar->get_stats()->get_spell_crit_dmg_mod() - 1) * ruin_crit_damage_bonus;
        damage_dealt = round(damage_dealt * spell_crit_dmg_mod);
        add_spell_crit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0, resist_roll);
    } else {
        pchar->spell_hit_effect(MagicSchool::Shadow);
        damage_dealt = round(damage_dealt);
        add_spell_hit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0, resist_roll);
    }
}

void ShadowBolt::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    // TODO: Improved Shadow Bolt rank is always applied with max value regardless of current rank.
    if (talent_name == "Improved Shadow Bolt")
        apply_imp_sb = true;

    if (talent_name == "Cataclysm")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * cataclysm_ranks[curr]));

    if (talent_name == "Bane")
        casting_time_ms = base_casting_time_ms - bane_ranks[curr];

    if (talent_name == "Devastation")
        devastation_bonus = devastation_ranks[curr];

    if (talent_name == "Ruin")
        ruin_crit_damage_bonus = 2.0;
}

void ShadowBolt::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    // TODO: Improved Shadow Bolt rank is always applied with max value regardless of current rank.
    if (talent_name == "Improved Shadow Bolt")
        apply_imp_sb = curr == 0 ? false : true;

    if (talent_name == "Cataclysm")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * cataclysm_ranks[curr]));

    if (talent_name == "Bane")
        casting_time_ms = base_casting_time_ms - bane_ranks[curr];

    if (talent_name == "Devastation")
        devastation_bonus = devastation_ranks[curr];

    if (talent_name == "Ruin")
        ruin_crit_damage_bonus = 1.0;
}
