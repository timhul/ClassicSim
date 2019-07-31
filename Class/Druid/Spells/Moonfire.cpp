#include "Moonfire.h"

#include "Buff.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Druid.h"
#include "DruidSpells.h"
#include "NoEffectUniqueDebuff.h"
#include "Random.h"
#include "SimSettings.h"
#include "Utils/Check.h"

Moonfire::Moonfire(Druid* pchar, DruidSpells* druid_spells, const int spell_rank) :
    SpellPeriodic("Moonfire", "Assets/spell/Spell_nature_starfall.png", pchar, nullptr,
                  RestrictedByGcd::Yes, ResourceType::Mana, 3.0, 0, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Moonfire", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Vengeance", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Moonglow", 3, DisabledAtZero::No),
                   new TalentRequirerInfo("Moonfury", 5, DisabledAtZero::No),
                   }),
    druid_spells(druid_spells)
{
    switch (spell_rank) {
    case 1:
        base_resource_cost = 25;
        base_instant_damage_min = 9;
        base_instant_damage_max = 12;
        full_duration_damage = 12;
        duration = 9;
        level_req = 4;
        break;
    case 2:
        base_resource_cost = 50;
        base_instant_damage_min = 16;
        base_instant_damage_max = 21;
        full_duration_damage = 32;
        duration = 12;
        level_req = 10;
        break;
    case 3:
        base_resource_cost = 75;
        base_instant_damage_min = 30;
        base_instant_damage_max = 37;
        full_duration_damage = 52;
        duration = 12;
        level_req = 16;
        break;
    case 4:
        base_resource_cost = 105;
        base_instant_damage_min = 46;
        base_instant_damage_max = 55;
        full_duration_damage = 80;
        duration = 12;
        level_req = 22;
        break;
    case 5:
        base_resource_cost = 150;
        base_instant_damage_min = 69;
        base_instant_damage_max = 82;
        full_duration_damage = 124;
        duration = 12;
        level_req = 28;
        break;
    case 6:
        base_resource_cost = 190;
        base_instant_damage_min = 91;
        base_instant_damage_max = 108;
        full_duration_damage = 164;
        duration = 12;
        level_req = 34;
        break;
    case 7:
        base_resource_cost = 235;
        base_instant_damage_min = 116;
        base_instant_damage_max = 137;
        full_duration_damage = 212;
        duration = 12;
        level_req = 40;
        break;
    case 8:
        base_resource_cost = 280;
        base_instant_damage_min = 143;
        base_instant_damage_max = 168;
        full_duration_damage = 264;
        duration = 12;
        level_req = 46;
        break;
    case 9:
        base_resource_cost = 325;
        base_instant_damage_min = 171;
        base_instant_damage_max = 200;
        full_duration_damage = 320;
        duration = 12;
        level_req = 52;
        break;
    case 10:
        base_resource_cost = 375;
        base_instant_damage_min = 195;
        base_instant_damage_max = 228;
        full_duration_damage = 384;
        duration = 12;
        level_req = 58;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    this->instant_dmg = new Random(base_instant_damage_min, base_instant_damage_max);
    this->instant_spell_dmg_coefficient = SpellPeriodic::get_spell_coefficient_for_instant_portion_of_hybrid_spell(duration, 1.5);
    this->dot_spell_dmg_coefficient = SpellPeriodic::get_spell_coefficient_for_dot_portion_of_hybrid_spell(duration, 1.5);
    this->resource_cost = base_resource_cost;
    this->marker_buff = new NoEffectUniqueDebuff(pchar, Priority::Low, duration, QString("Moonfire (rank %1)").arg(spell_rank), icon, Hidden::No, 0);

    this->num_ticks = duration / tick_rate;
    this->reported_execution_time = 1.5 / num_ticks;
    this->reported_resource_cost = resource_cost / num_ticks;

    enabled = true;
    marker_buff->enable_buff();
}

Moonfire::~Moonfire() {
    delete cooldown;
    delete instant_dmg;
    delete marker_buff;
}

bool Moonfire::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 10)
        return pchar->get_clvl() >= level_req;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

int Moonfire::duration_for_spell_rank(const unsigned spell_rank) {
    if (spell_rank < 1 || spell_rank > 10)
        check(false, QString("Moonfire does not support rank %2").arg(spell_rank).toStdString());

    switch (spell_rank) {
    case 1:
        return 9;
    default:
        return 12;
    }
}

bool Moonfire::check_application_success() {
    pchar->lose_mana(static_cast<unsigned>(round(get_resource_cost())));
    cooldown->add_gcd_event();

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Arcane, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Arcane) + imp_moonfire_crit_bonus);
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Arcane);

    if (hit_roll == MagicAttackResult::MISS) {
        increment_miss();
        return false;
    }
    if (resist_roll == MagicResistResult::FULL_RESIST) {
        increment_full_resist();
        return false;
    }

    double damage_dealt = instant_dmg->get_roll() + pchar->get_stats()->get_spell_damage(MagicSchool::Arcane) * instant_spell_dmg_coefficient;
    damage_dealt *= get_partial_resist_dmg_modifier(resist_roll);
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect(MagicSchool::Arcane);
        const double spell_crit_dmg_mod = 1 + (pchar->get_stats()->get_spell_crit_dmg_mod() - 1) * vengeance_crit_damage_bonus;
        damage_dealt = round(damage_dealt * spell_crit_dmg_mod);
        add_crit_dmg(static_cast<int>(damage_dealt), get_resource_cost() / (duration / tick_rate), 0);
    }
    else {
        pchar->spell_hit_effect(MagicSchool::Arcane);
        damage_dealt = round(damage_dealt);
        add_hit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0);
    }

    return true;
}

void Moonfire::new_application_effect() {
    marker_buff->apply_buff();
}

void Moonfire::refresh_effect() {
    marker_buff->apply_buff();
}

void Moonfire::reset_effect() {
    tick_rest = 0.0;
}

void Moonfire::tick_effect() {
    const double spell_power_bonus = pchar->get_stats()->get_spell_damage(MagicSchool::Arcane) * dot_spell_dmg_coefficient;
    const double damage_dealt = (full_duration_damage + spell_power_bonus) * pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Arcane) / num_ticks + tick_rest;
    tick_rest += damage_dealt - round(damage_dealt);

    add_hit_dmg(static_cast<int>(round(damage_dealt)), reported_resource_cost, reported_execution_time);

    add_next_tick();
}

void Moonfire::set_base_damage_range() {
    const unsigned new_min_damage = static_cast<unsigned>(std::round(base_instant_damage_min * imp_moonfire_damage_bonus * moonfury_damage_bonus));
    const unsigned new_max_damage = static_cast<unsigned>(std::round(base_instant_damage_max * imp_moonfire_damage_bonus * moonfury_damage_bonus));
    instant_dmg->set_new_range(new_min_damage, new_max_damage);
}

void Moonfire::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Moonfire") {
        imp_moonfire_damage_bonus = improved_moonfire_ranks[curr].first;
        imp_moonfire_crit_bonus = improved_moonfire_ranks[curr].second;
        set_base_damage_range();
    }

    if (talent_name == "Vengeance")
        vengeance_crit_damage_bonus = vengeance_ranks[curr];

    if (talent_name == "Moonglow")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * moonglow_ranks[curr]));

    if (talent_name == "Moonfury") {
        moonfury_damage_bonus = moonfury_ranks[curr];
        set_base_damage_range();
    }
}

void Moonfire::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
