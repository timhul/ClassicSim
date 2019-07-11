#include "Scorch.h"

#include "CharacterStats.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "Mage.h"
#include "MageSpells.h"
#include "Random.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

Scorch::Scorch(Mage* pchar, MageSpells* mage_spells, const int spell_rank) :
    SpellCastingTime("Scorch", "Assets/spell/Spell_fire_soulburn.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Scorch", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Incinerate", 2, DisabledAtZero::No),
                   new TalentRequirerInfo("Burning Soul", 2, DisabledAtZero::No),
                   new TalentRequirerInfo("Master of Elements", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Critical Mass", 3, DisabledAtZero::No),
                   }),
    mage_spells(mage_spells)
{
    casting_time_ms = 1500;

    switch (spell_rank) {
    case 1:
        base_damage_min = 53;
        base_damage_max = 65;
        base_resource_cost = 50;
        level_req = 22;
        break;
    case 2:
        base_damage_min = 77;
        base_damage_max = 93;
        base_resource_cost = 65;
        level_req = 28;
        break;
    case 3:
        base_damage_min = 100;
        base_damage_max = 120;
        base_resource_cost = 80;
        level_req = 34;
        break;
    case 4:
        base_damage_min = 133;
        base_damage_max = 159;
        base_resource_cost = 100;
        level_req = 40;
        break;
    case 5:
        base_damage_min = 162;
        base_damage_max = 192;
        base_resource_cost = 115;
        level_req = 46;
        break;
    case 6:
        base_damage_min = 200;
        base_damage_max = 239;
        base_resource_cost = 135;
        level_req = 52;
        break;
    case 7:
        base_damage_min = 233;
        base_damage_max = 275;
        base_resource_cost = 150;
        level_req = 58;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    this->spell_dmg_coefficient = spell_coefficient_from_casting_time();
    this->resource_cost = base_resource_cost;
    this->instant_dmg = new Random(base_damage_min, base_damage_max);
}

Scorch::~Scorch() {
    delete cooldown;
    delete instant_dmg;
}

bool Scorch::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 7)
        return pchar->get_clvl() >= level_req;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void Scorch::spell_effect() {
    pchar->get_spells()->stop_attack();
    cooldown->add_gcd_event();
    start_cast();
}

void Scorch::complete_cast_effect() {
    if (!mage_spells->clearcasting_active())
        pchar->lose_mana(get_resource_cost());

    const int hit_roll = roll->get_spell_ability_result(MagicSchool::Fire, pchar->get_stats()->get_spell_crit_chance(MagicSchool::Fire) + incinerate + imp_critical_mass);
    const int resist_roll = roll->get_spell_resist_result(MagicSchool::Fire);

    if (hit_roll == MagicAttackResult::MISS)
        return increment_miss();
    if (resist_roll == MagicResistResult::FULL_RESIST)
        return increment_full_resist();

    double damage_dealt = instant_dmg->get_roll() + static_cast<unsigned>(round(pchar->get_stats()->get_spell_damage(MagicSchool::Fire) * spell_dmg_coefficient));
    damage_dealt *= get_partial_resist_dmg_modifier(resist_roll);
    damage_dealt *= pchar->get_stats()->get_magic_school_damage_mod(MagicSchool::Fire);

    if (hit_roll == MagicAttackResult::CRITICAL) {
        pchar->spell_critical_effect(MagicSchool::Fire);
        damage_dealt = round(damage_dealt * pchar->get_stats()->get_spell_crit_dmg_mod());
        mage_spells->inflict_ignite(damage_dealt);
        gain_mana(base_resource_cost * master_of_elements_mana_return);
        add_crit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0);
    }
    else {
        pchar->spell_hit_effect(MagicSchool::Fire);
        damage_dealt = round(damage_dealt);
        add_hit_dmg(static_cast<int>(damage_dealt), get_resource_cost(), 0);
    }

    mage_spells->roll_clearcasting();
}

void Scorch::gain_mana(const double mana_gain) {
    const unsigned mana_gained = static_cast<unsigned>(std::round(mana_gain));
    const unsigned before = pchar->get_resource_level(ResourceType::Mana);

    pchar->gain_mana(mana_gained);

    const unsigned gain_after_cap = pchar->get_resource_level(ResourceType::Mana) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Mana, gain_after_cap);
}

void Scorch::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(QString("Master of Elements Scorch (rank %1)").arg(spell_rank),
                                                                                 "Assets/spell/Spell_fire_masterofelements.png");
}

void Scorch::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Scorch")
        incinerate = incinerate_ranks[curr];
    else if (talent_name == "Master of Elements")
        master_of_elements_mana_return = master_of_elements_ranks[curr];
    else if (talent_name == "Critical Mass")
        imp_critical_mass = critical_mass_ranks[curr];
}

void Scorch::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Scorch")
        incinerate = incinerate_ranks[curr];
    else if (talent_name == "Master of Elements")
        master_of_elements_mana_return = master_of_elements_ranks[curr];
    else if (talent_name == "Critical Mass")
        imp_critical_mass = critical_mass_ranks[curr];
}
