#include "Frostbolt.h"

#include "Buff.h"
#include "CharacterSpells.h"
#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Mage.h"
#include "MageSpells.h"
#include "Proc.h"
#include "Random.h"
#include "SimSettings.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

Frostbolt::Frostbolt(Mage* pchar, MageSpells* mage_spells, Proc* winters_chill, const int spell_rank) :
    Spell("Frostbolt", "Assets/spell/Spell_frost_frostbolt02.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, spell_rank),
    CastingTimeRequirer(pchar, SuppressibleCast::Yes, 3000),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Frostbolt", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Ice Shards", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Frost Channeling", 3, DisabledAtZero::No),
                   new TalentRequirerInfo("Master of Elements", 5, DisabledAtZero::No),
                   }),
    mage_spells(mage_spells),
    winters_chill(winters_chill)
{
    switch (spell_rank) {
    case 1:
        base_damage_min = 18;
        base_damage_max = 20;
        base_resource_cost = 25;
        base_casting_time_ms = 1500;
        level_req = 4;
        break;
    case 2:
        base_damage_min = 31;
        base_damage_max = 35;
        base_resource_cost = 35;
        base_casting_time_ms = 1800;
        level_req = 8;
        break;
    case 3:
        base_damage_min = 51;
        base_damage_max = 57;
        base_resource_cost = 50;
        base_casting_time_ms = 2200;
        level_req = 14;
        break;
    case 4:
        base_damage_min = 74;
        base_damage_max = 82;
        base_resource_cost = 65;
        base_casting_time_ms = 2600;
        level_req = 20;
        break;
    case 5:
        base_damage_min = 126;
        base_damage_max = 138;
        base_resource_cost = 100;
        base_casting_time_ms = 3000;
        level_req = 26;
        break;
    case 6:
        base_damage_min = 174;
        base_damage_max = 190;
        base_resource_cost = 130;
        base_casting_time_ms = 3000;
        level_req = 32;
        break;
    case 7:
        base_damage_min = 227;
        base_damage_max = 247;
        base_resource_cost = 160;
        base_casting_time_ms = 3000;
        level_req = 38;
        break;
    case 8:
        base_damage_min = 292;
        base_damage_max = 316;
        base_resource_cost = 195;
        base_casting_time_ms = 3000;
        level_req = 44;
        break;
    case 9:
        base_damage_min = 353;
        base_damage_max = 383;
        base_resource_cost = 225;
        base_casting_time_ms = 3000;
        level_req = 50;
        break;
    case 10:
        base_damage_min = 429;
        base_damage_max = 463;
        base_resource_cost = 260;
        base_casting_time_ms = 3000;
        level_req = 56;
        break;
    case 11:
        base_damage_min = 515;
        base_damage_max = 555;
        base_resource_cost = 290;
        base_casting_time_ms = 3000;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    this->instant_dmg = new Random(base_damage_min, base_damage_max);
    this->casting_time_ms = base_casting_time_ms;
    this->spell_dmg_coefficient = 0.95 * CastingTimeRequirer::spell_coefficient_from_casting_time(casting_time_ms, level_req);
    this->resource_cost = base_resource_cost;
}

Frostbolt::~Frostbolt() {
    delete cooldown;
    delete instant_dmg;
}

bool Frostbolt::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 10)
        return pchar->get_clvl() >= level_req;

    if (spell_rank == 11)
        return pchar->get_clvl() >= 60 && static_cast<int>(pchar->get_sim_settings()->get_phase()) >= 4;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void Frostbolt::spell_effect() {
    pchar->get_spells()->stop_attack();
    cooldown->add_gcd_event();
    start_cast();
}

void Frostbolt::complete_cast_effect() {
    if (!mage_spells->clearcasting_active())
        pchar->lose_mana(static_cast<unsigned>(round(get_resource_cost())));

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Frost, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Frost));
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Frost);

    if (hit_roll == MagicAttackResult::MISS) {
        mage_spells->get_enigma_5p_buff()->apply_buff();
        return increment_miss();
    }
    if (resist_roll == MagicResistResult::FULL_RESIST) {
        mage_spells->get_enigma_5p_buff()->apply_buff();
        return increment_full_resist();
    }

    if (winters_chill->is_enabled() && winters_chill->check_proc_success())
        winters_chill->perform();

    double damage_dealt = instant_dmg->get_roll() + pchar->get_stats()->get_spell_damage(MagicSchool::Frost) * spell_dmg_coefficient;
    damage_dealt *= get_partial_resist_dmg_modifier(resist_roll);
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Frost);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect(MagicSchool::Frost);
        damage_dealt = round(damage_dealt * spell_crit_dmg_mod);
        gain_mana(base_resource_cost * master_of_elements_mana_return);
        add_crit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0);
    }
    else {
        pchar->spell_hit_effect(MagicSchool::Frost);
        damage_dealt = round(damage_dealt);
        add_hit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0);
    }

    mage_spells->roll_clearcasting();
    mage_spells->roll_netherwind_focus();
}

void Frostbolt::gain_mana(const double mana_gain) {
    const unsigned mana_gained = static_cast<unsigned>(std::round(mana_gain));
    const unsigned before = pchar->get_resource_level(ResourceType::Mana);

    pchar->gain_mana(mana_gained);

    const unsigned gain_after_cap = pchar->get_resource_level(ResourceType::Mana) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Mana, gain_after_cap);
}

void Frostbolt::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(QString("Master of Elements Frostbolt (rank %1)").arg(spell_rank),
                                                                                 "Assets/spell/Spell_fire_masterofelements.png");
    this->spell_crit_dmg_mod = (pchar->get_stats()->get_spell_crit_dmg_mod() - 1.0) * ice_shards_multiplier + 1.0;
}

void Frostbolt::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Frostbolt")
        casting_time_ms = base_casting_time_ms - improved_frostbolt_ranks[curr];
    else if (talent_name == "Ice Shards")
        ice_shards_multiplier = ice_shards_ranks[curr];
    else if (talent_name == "Frost Channeling")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * frost_channeling_ranks[curr]));
    else if (talent_name == "Master of Elements")
        master_of_elements_mana_return = master_of_elements_ranks[curr];
}

void Frostbolt::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Frostbolt")
        casting_time_ms = base_casting_time_ms - improved_frostbolt_ranks[curr];
    else if (talent_name == "Ice Shards")
        ice_shards_multiplier = ice_shards_ranks[curr];
    else if (talent_name == "Frost Channeling")
        resource_cost = static_cast<unsigned>(std::round(base_resource_cost * frost_channeling_ranks[curr]));
    else if (talent_name == "Master of Elements")
        master_of_elements_mana_return = master_of_elements_ranks[curr];
}
