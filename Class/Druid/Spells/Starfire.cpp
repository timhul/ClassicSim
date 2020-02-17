#include "Starfire.h"

#include <cmath>

#include "Buff.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "Random.h"
#include "SimSettings.h"
#include "Utils/Check.h"

Starfire::Starfire(Druid* pchar, DruidSpells* druid_spells, const int spell_rank) :
    Spell("Starfire", "Assets/spell/Spell_arcane_starfire.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, spell_rank),
    CastingTimeRequirer(pchar, SuppressibleCast::Yes, 3500),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Starfire", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Vengeance", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Moonglow", 3, DisabledAtZero::No),
                   new TalentRequirerInfo("Moonfury", 5, DisabledAtZero::No),
                   }),
    druid_spells(druid_spells),
    base_casting_time_ms(casting_time_ms)
{
    switch (spell_rank) {
    case 1:
        base_resource_cost = 95;
        base_damage_min = 94;
        base_damage_max = 115;
        level_req = 20;
        break;
    case 2:
        base_resource_cost = 135;
        base_damage_min = 146;
        base_damage_max = 177;
        level_req = 26;
        break;
    case 3:
        base_resource_cost = 180;
        base_damage_min = 212;
        base_damage_max = 253;
        level_req = 34;
        break;
    case 4:
        base_resource_cost = 230;
        base_damage_min = 293;
        base_damage_max = 348;
        level_req = 42;
        break;
    case 5:
        base_resource_cost = 275;
        base_damage_min = 378;
        base_damage_max = 445;
        level_req = 50;
        break;
    case 6:
        base_resource_cost = 315;
        base_damage_min = 450;
        base_damage_max = 531;
        level_req = 58;
        break;
    case 7:
        base_resource_cost = 340;
        base_damage_min = 495;
        base_damage_max = 584;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    this->instant_dmg = new Random(base_damage_min, base_damage_max);
    this->spell_dmg_coefficient = CastingTimeRequirer::spell_coefficient_from_casting_time(casting_time_ms, level_req);
    this->resource_cost = base_resource_cost;
}

Starfire::~Starfire() {
    delete cooldown;
    delete instant_dmg;
}

bool Starfire::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 6)
        return pchar->get_clvl() >= level_req;

    if (spell_rank == 7)
        return pchar->get_clvl() >= 60 && static_cast<int>(pchar->get_sim_settings()->get_phase()) >= 5;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void Starfire::spell_effect() {
    pchar->get_spells()->stop_attack();
    cooldown->add_gcd_event();
    start_cast();
}

void Starfire::complete_cast_effect() {
    if (!druid_spells->omen_of_clarity_active())
        pchar->lose_mana(static_cast<unsigned>(round(get_resource_cost())));
    druid_spells->get_natures_grace()->use_charge();

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Arcane, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane));
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Arcane);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    double damage_dealt = instant_dmg->get_roll() + pchar->get_stats()->get_spell_damage(MagicSchool::Arcane) * spell_dmg_coefficient;
    damage_dealt *= get_partial_resist_dmg_modifier(resist_roll);
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect(MagicSchool::Arcane);
        const double spell_crit_dmg_mod = 1 + (pchar->get_stats()->get_spell_crit_dmg_mod() - 1) * vengeance_crit_damage_bonus;
        damage_dealt = round(damage_dealt * spell_crit_dmg_mod);
        add_spell_crit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0, resist_roll);
    }
    else {
        pchar->spell_hit_effect(MagicSchool::Arcane);
        damage_dealt = round(damage_dealt);
        add_spell_hit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0, resist_roll);
    }
}

void Starfire::set_base_damage_range() {
    const unsigned new_min_damage = static_cast<unsigned>(std::round(base_damage_min * moonfury_damage_bonus));
    const unsigned new_max_damage = static_cast<unsigned>(std::round(base_damage_max * moonfury_damage_bonus));
    instant_dmg->set_new_range(new_min_damage, new_max_damage);
}

void Starfire::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Starfire")
        casting_time_ms = base_casting_time_ms - improved_starfire_ranks[curr];

    if (talent_name == "Vengeance")
        vengeance_crit_damage_bonus = vengeance_ranks[curr];

    if (talent_name == "Moonglow")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * moonglow_ranks[curr]));

    if (talent_name == "Moonfury") {
        moonfury_damage_bonus = moonfury_ranks[curr];
        set_base_damage_range();
    }
}

void Starfire::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
