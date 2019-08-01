#include "Wrath.h"

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

Wrath::Wrath(Druid* pchar, DruidSpells* druid_spells, const int spell_rank) :
    Spell("Wrath", "Assets/items/Spell_nature_abolishmagic.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, spell_rank),
    CastingTimeRequirer(pchar, SuppressibleCast::Yes, 2000),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Wrath", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Vengeance", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Moonglow", 3, DisabledAtZero::No),
                   new TalentRequirerInfo("Moonfury", 5, DisabledAtZero::No),
                   }),
    druid_spells(druid_spells)
{
    switch (spell_rank) {
    case 1:
    case 2:
    case 3:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
        break;
    case 4:
        base_damage_min = 63;
        base_damage_max = 74;
        base_resource_cost = 70;
        base_casting_time_ms = 2000;
        level_req = 22;
        break;
    case 5:
        base_damage_min = 101;
        base_damage_max = 116;
        base_resource_cost = 100;
        base_casting_time_ms = 2000;
        level_req = 30;
        break;
    case 6:
        base_damage_min = 139;
        base_damage_max = 158;
        base_resource_cost = 125;
        base_casting_time_ms = 2000;
        level_req = 38;
        break;
    case 7:
        base_damage_min = 188;
        base_damage_max = 211;
        base_resource_cost = 155;
        base_casting_time_ms = 2000;
        level_req = 46;
        break;
    case 8:
        base_damage_min = 236;
        base_damage_max = 265;
        base_resource_cost = 180;
        base_casting_time_ms = 2000;
        level_req = 54;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    this->instant_dmg = new Random(base_damage_min, base_damage_max);
    this->casting_time_ms = base_casting_time_ms;
    this->spell_dmg_coefficient = CastingTimeRequirer::spell_coefficient_from_casting_time(casting_time_ms, level_req);
    this->resource_cost = base_resource_cost;
}

Wrath::~Wrath() {
    delete cooldown;
    delete instant_dmg;
}

bool Wrath::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 8)
        return pchar->get_clvl() >= level_req;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void Wrath::spell_effect() {
    pchar->get_spells()->stop_attack();
    cooldown->add_gcd_event();
    start_cast();
}

void Wrath::complete_cast_effect() {
    pchar->lose_mana(static_cast<unsigned>(round(get_resource_cost())));
    druid_spells->get_natures_grace()->use_charge();

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Nature, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Nature));
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Nature);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    double damage_dealt = instant_dmg->get_roll() + pchar->get_stats()->get_spell_damage(MagicSchool::Nature) * spell_dmg_coefficient;
    damage_dealt *= get_partial_resist_dmg_modifier(resist_roll);
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Nature);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect(MagicSchool::Nature);
        const double spell_crit_dmg_mod = 1 + (pchar->get_stats()->get_spell_crit_dmg_mod() - 1) * vengeance_crit_damage_bonus;
        damage_dealt = round(damage_dealt * spell_crit_dmg_mod);
        add_crit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0);
    }
    else {
        pchar->spell_hit_effect(MagicSchool::Nature);
        damage_dealt = round(damage_dealt);
        add_hit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0);
    }
}

void Wrath::set_base_damage_range() {
    const unsigned new_min_damage = static_cast<unsigned>(std::round(base_damage_min * moonfury_damage_bonus));
    const unsigned new_max_damage = static_cast<unsigned>(std::round(base_damage_max * moonfury_damage_bonus));
    instant_dmg->set_new_range(new_min_damage, new_max_damage);
}

void Wrath::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Wrath")
        casting_time_ms = base_casting_time_ms - improved_wrath_ranks[curr];

    if (talent_name == "Vengeance")
        vengeance_crit_damage_bonus = vengeance_ranks[curr];

    if (talent_name == "Moonglow")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * moonglow_ranks[curr]));

    if (talent_name == "Moonfury") {
        moonfury_damage_bonus = moonfury_ranks[curr];
        set_base_damage_range();
    }
}

void Wrath::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    increase_talent_rank_effect(talent_name, curr);
}
