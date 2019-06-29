#include "Fireball.h"

#include "CharacterSpells.h"
#include "ClassStatistics.h"
#include "CombatRoll.h"
#include "CooldownControl.h"
#include "FireballInstant.h"
#include "Mage.h"
#include "MageSpells.h"
#include "SimSettings.h"
#include "StatisticsResource.h"
#include "Utils/Check.h"

Fireball::Fireball(Mage* pchar, MageSpells* mage_spells, const int spell_rank) :
    SpellCastingTime("Fireball", "Assets/spell/Spell_fire_flamebolt.png", pchar, new CooldownControl(pchar, 0.0), RestrictedByGcd::Yes, ResourceType::Mana, 0, spell_rank),
    TalentRequirer(QVector<TalentRequirerInfo*>{
                   new TalentRequirerInfo("Improved Fireball", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Ignite", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Burning Soul", 2, DisabledAtZero::No),
                   new TalentRequirerInfo("Master of Elements", 5, DisabledAtZero::No),
                   new TalentRequirerInfo("Critical Mass", 3, DisabledAtZero::No)
                   }),
    mage_spells(mage_spells)
{
    switch (spell_rank) {
    case 1:
        base_damage_min = 14;
        base_damage_max = 23;
        base_dot_damage = 2;
        base_dot_duration = 4;
        base_resource_cost = 30;
        base_casting_time_ms = 1500;
        level_req = 1;
        break;
    case 2:
        base_damage_min = 31;
        base_damage_max = 46;
        base_dot_damage = 3;
        base_dot_duration = 6;
        base_resource_cost = 45;
        base_casting_time_ms = 2000;
        level_req = 6;
        break;
    case 3:
        base_damage_min = 53;
        base_damage_max = 74;
        base_dot_damage = 6;
        base_dot_duration = 6;
        base_resource_cost = 65;
        base_casting_time_ms = 2500;
        level_req = 12;
        break;
    case 4:
        base_damage_min = 84;
        base_damage_max = 117;
        base_dot_damage = 12;
        base_dot_duration = 8;
        base_resource_cost = 95;
        base_casting_time_ms = 3000;
        level_req = 18;
        break;
    case 5:
        base_damage_min = 139;
        base_damage_max = 188;
        base_dot_damage = 20;
        base_dot_duration = 8;
        base_resource_cost = 140;
        base_casting_time_ms = 3500;
        level_req = 24;
        break;
    case 6:
        base_damage_min = 199;
        base_damage_max = 266;
        base_dot_damage = 28;
        base_dot_duration = 8;
        base_resource_cost = 185;
        base_casting_time_ms = 3500;
        level_req = 30;
        break;
    case 7:
        base_damage_min = 255;
        base_damage_max = 366;
        base_dot_damage = 32;
        base_dot_duration = 8;
        base_resource_cost = 220;
        base_casting_time_ms = 3500;
        level_req = 36;
        break;
    case 8:
        base_damage_min = 318;
        base_damage_max = 415;
        base_dot_damage = 40;
        base_dot_duration = 8;
        base_resource_cost = 2600;
        base_casting_time_ms = 3500;
        level_req = 42;
        break;
    case 9:
        base_damage_min = 392;
        base_damage_max = 507;
        base_dot_damage = 52;
        base_dot_duration = 8;
        base_resource_cost = 305;
        base_casting_time_ms = 3500;
        level_req = 48;
        break;
    case 10:
        base_damage_min = 457;
        base_damage_max = 610;
        base_dot_damage = 60;
        base_dot_duration = 8;
        base_resource_cost = 350;
        base_casting_time_ms = 3500;
        level_req = 54;
        break;
    case 11:
        base_damage_min = 561;
        base_damage_max = 716;
        base_dot_damage = 72;
        base_dot_duration = 8;
        base_resource_cost = 95;
        base_casting_time_ms = 3500;
        level_req = 60;
        break;
    case 12:
        base_damage_min = 596;
        base_damage_max = 761;
        base_dot_damage = 76;
        base_dot_duration = 8;
        base_resource_cost = 410;
        base_casting_time_ms = 3500;
        level_req = 60;
        break;
    default:
        check(false, QString("%1 does not support rank %2").arg(name).arg(spell_rank).toStdString());
    }

    this->casting_time_ms = base_casting_time_ms;
    this->spell_dmg_coefficient = spell_coefficient_from_casting_time();
    this->resource_cost = base_resource_cost;

    QString empty_format_string = "";
    this->damage_spell = new FireballInstant(pchar, empty_format_string, base_damage_min, base_damage_max, base_dot_damage, base_dot_duration, spell_dmg_coefficient, spell_rank);
}

Fireball::~Fireball() {
    delete cooldown;
    delete damage_spell;
}

bool Fireball::is_rank_learned() const {
    if (spell_rank >= 1 && spell_rank <= 11)
        return pchar->get_clvl() >= level_req;

    if (spell_rank == 12)
        return static_cast<int>(pchar->get_sim_settings()->get_phase()) >= 4;

    check(false, QString("%1::is_rank_learned() failed for rank %2").arg(name).arg(spell_rank).toStdString());
    return false;
}

void Fireball::spell_effect() {
    pchar->get_spells()->stop_attack();
    cooldown->add_gcd_event();
    start_cast();
}

void Fireball::complete_cast_effect() {
    pchar->lose_mana(resource_cost);

    damage_spell->perform();

    if (damage_spell->magic_attack_result == MagicAttackResult::CRITICAL) {
        mage_spells->inflict_ignite(damage_spell->last_damage_dealt);
        gain_mana(base_resource_cost * master_of_elements_mana_return);
    }
}

void Fireball::prepare_set_of_combat_iterations() {
    damage_spell->prepare_set_of_combat_iterations();
    prepare_set_of_combat_iterations_spell_specific();
}

void Fireball::gain_mana(const double mana_gain) {
    const unsigned mana_gained = static_cast<unsigned>(std::round(mana_gain));
    const unsigned before = pchar->get_resource_level(ResourceType::Mana);

    pchar->gain_mana(mana_gained);

    const unsigned gain_after_cap = pchar->get_resource_level(ResourceType::Mana) - before;

    if (gain_after_cap > 0)
        statistics_resource->add_resource_gain(ResourceType::Mana, gain_after_cap);
}

void Fireball::prepare_set_of_combat_iterations_spell_specific() {
    this->statistics_resource = pchar->get_statistics()->get_resource_statistics(QString("Master of Elements (rank %1)").arg(spell_rank),
                                                                                 "Assets/spell/Spell_fire_masterofelements.png");
}

void Fireball::reset_effect() {
    damage_spell->reset();
}

void Fireball::increase_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Fireball")
        casting_time_ms = base_casting_time_ms - improved_fireball_ranks[curr];
    else if (talent_name == "Master of Elements")
        master_of_elements_mana_return = master_of_elements_ranks[curr];
    else if (talent_name == "Critical Mass")
        damage_spell->crit_bonus = critical_mass_ranks[curr];
}

void Fireball::decrease_talent_rank_effect(const QString& talent_name, const int curr) {
    if (talent_name == "Improved Fireball")
        casting_time_ms = base_casting_time_ms - improved_fireball_ranks[curr];
    else if (talent_name == "Master of Elements")
        master_of_elements_mana_return = master_of_elements_ranks[curr];
    else if (talent_name == "Critical Mass")
        damage_spell->crit_bonus = critical_mass_ranks[curr];
}
