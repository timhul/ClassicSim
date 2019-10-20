#include "Druid.h"

#include <cmath>

#include "Balance.h"
#include "BearForm.h"
#include "Buff.h"
#include "CatForm.h"
#include "CasterForm.h"
#include "CharacterStats.h"
#include "CharacterTalents.h"
#include "DruidEnchants.h"
#include "DruidSpells.h"
#include "EnabledBuffs.h"
#include "EnabledProcs.h"
#include "Energy.h"
#include "Engine.h"
#include "Equipment.h"
#include "FeralCombat.h"
#include "Mana.h"
#include "MoonkinForm.h"
#include "PlayerAction.h"
#include "Race.h"
#include "Rage.h"
#include "RaidControl.h"
#include "RestorationDruid.h"
#include "Utils/Check.h"
#include "Weapon.h"

Druid::Druid(Race* race, EquipmentDb* equipment_db, SimSettings *sim_settings, RaidControl* raid_control, const int party, const int member) :
    Character("Druid", "#FF7D0A", race, sim_settings, raid_control, party, member) {
    available_races.append("Night Elf");
    available_races.append("Tauren");
    available_enchants = new DruidEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    cstats->increase_agility(40);
    cstats->increase_strength(45);
    cstats->increase_stamina(50);
    cstats->increase_intellect(80);
    cstats->increase_spirit(90);

    this->druid_spells = new DruidSpells(this);
    this->spells = dynamic_cast<CharacterSpells*>(druid_spells);

    this->energy = new class Energy(this);
    this->rage = new class Rage();
    this->mana = new class Mana(this);
    mana->set_base_mana(1244);

    druid_spells->activate_racials();

    initialize_talents();
}

Druid::~Druid()
{
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete available_enchants;
    delete cstats;
    delete energy;
    delete rage;
    delete druid_spells;
}

unsigned Druid::get_strength_modifier() const {
    return 1;
}

unsigned Druid::get_agility_modifier() const {
    return 0;
}

unsigned Druid::get_stamina_modifier() const {
    return 0;
}

unsigned Druid::get_intellect_modifier() const {
    return 2;
}

unsigned Druid::get_spirit_modifier() const {
    return 2;
}

double Druid::get_mp5_from_spirit() const {
    return 15 + static_cast<double>(cstats->get_spirit()) / 5;
}

double Druid::get_agi_needed_for_one_percent_phys_crit() const {
    return 20;
}

double Druid::get_int_needed_for_one_percent_spell_crit() const {
    return 60.0;
}

unsigned Druid::get_melee_ap_per_strength() const {
    return 1;
}

unsigned Druid::get_melee_ap_per_agi() const {
    return 1;
}

unsigned Druid::get_ranged_ap_per_agi() const {
    return 0;
}

double Druid::global_cooldown() const {
    switch (current_form) {
    case DruidForm::Caster:
    case DruidForm::Bear:
    case DruidForm::Moonkin:
        return 1.5;
    case DruidForm::Cat:
        return 1.0;
    }

    check(false, "Reached end of Druid::global_cooldown() switch");
    return 1.5;
}

double Druid::form_cooldown() const {
    return 1.0;
}

void Druid::set_clvl(const unsigned clvl) {
    this->clvl = clvl;
    this->rage_conversion_value = 0.0091107836 * std::pow(clvl, 2) + 3.225598133 * clvl + 4.2652911;
}

void Druid::initialize_talents() {
    for (int i = 0; i < 3; ++i)
        talents->add_talent_tree(new Balance(this), new FeralCombat(this), new RestorationDruid(this));
}

unsigned Druid::get_resource_level(const ResourceType resource_type) const {
    switch (resource_type) {
    case ResourceType::Mana:
        return mana->current;
    case ResourceType::Rage:
        return rage->current;
    case ResourceType::Energy:
        return energy->current;
    default:
        return 0;
    }
}

unsigned Druid::get_max_resource_level(const ResourceType resource_type) const {
    switch (resource_type) {
    case ResourceType::Mana:
        return mana->max;
    case ResourceType::Rage:
        return rage->max;
    case ResourceType::Energy:
        return energy->max;
    default:
        return 0;
    }
}

void Druid::gain_mana(const unsigned value) {
    mana->gain_resource(value);
    add_player_reaction_event();
}

void Druid::lose_mana(const unsigned value) {
    mana->lose_resource(value);
}

void Druid::gain_rage(const unsigned value) {
    this->rage->gain_resource(value);
    add_player_reaction_event();
}

void Druid::lose_rage(const unsigned value) {
    this->rage->lose_resource(value);
}

void Druid::gain_energy(const unsigned value) {
    this->energy->gain_resource(value);
    add_player_reaction_event();
}

void Druid::lose_energy(const unsigned value) {
    this->energy->lose_resource(value);
}

void Druid::increase_base_mana(const unsigned value) {
    mana->base_mana += value;
}

void Druid::decrease_base_mana(const unsigned value) {
    mana->base_mana -= value;
}

void Druid::spell_critical_effect(MagicSchool) {
    druid_spells->get_natures_grace()->apply_buff();

    enabled_procs->run_proc_check(ProcInfo::Source::MagicSpell);
}

DruidForm Druid::get_current_form() const {
    return this->current_form;
}

bool Druid::on_form_cooldown() const {
    return engine->get_current_priority() < this->next_form_cd;
}

void Druid::cancel_form() {
    switch (this->current_form) {
    case DruidForm::Caster:
        break;
    case DruidForm::Bear:
        druid_spells->get_bear_form()->buff->cancel_buff();
        break;
    case DruidForm::Cat:
        druid_spells->get_cat_form()->buff->cancel_buff();
        break;
    case DruidForm::Moonkin:
        druid_spells->get_moonkin_form()->buff->cancel_buff();
        break;
    }

    current_form = DruidForm::Caster;
    druid_spells->get_caster_form()->buff->apply_buff();

    add_player_reaction_event();
}

void Druid::switch_to_form(const DruidForm new_form) {
    if (new_form == DruidForm::Caster)
        return cancel_form();

    if (on_form_cooldown())
        return;

    cancel_form();
    druid_spells->get_caster_form()->buff->cancel_buff();

    switch (new_form) {
    case DruidForm::Bear:
        druid_spells->get_bear_form()->buff->apply_buff();
        break;
    case DruidForm::Cat:
        druid_spells->get_cat_form()->buff->apply_buff();
        break;
    case DruidForm::Moonkin:
        druid_spells->get_moonkin_form()->buff->apply_buff();
        break;
    default:
        check(false, "Unhandled form in Druid::switch_to_form()");
    }

    this->current_form = new_form;
    this->next_form_cd = engine->get_current_priority() + form_cooldown();

    if ((engine->get_current_priority() + 0.5) > this->next_gcd) {
        this->next_gcd = engine->get_current_priority() + 0.5;
        engine->add_event(new PlayerAction(spells, next_gcd));
    }
}

unsigned Druid::rage_gained_from_dd(const unsigned damage_dealt) const {
    return static_cast<unsigned>(std::max(1, int(round(damage_dealt / rage_conversion_value * 7.5))));
}

unsigned Druid::get_combo_points() const {
    return this->combo_points;
}

void Druid::spend_combo_points() {
    combo_points = 0;
}

void Druid::gain_combo_points(const unsigned combo_points) {
    this->combo_points += combo_points;

    if (this->combo_points > 5)
        this->combo_points = 5;
}

void Druid::enter_stealth() {
    if (is_stealthed())
        return;

    spells->stop_attack();
    stealthed = true;
}

void Druid::exit_stealth() {
    stealthed = false;
}

bool Druid::is_stealthed() const {
    return this->stealthed;
}

int Druid::get_highest_possible_armor_type() const {
    return ArmorTypes::LEATHER;
}

QVector<int> Druid::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::MACE, WeaponTypes::POLEARM,
                             WeaponTypes::STAFF});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::CASTER_OFFHAND});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::IDOL});
    default:
        check(false, "Druid::get_weapon_proficiencies_for_slot reached end of switch");
        return QVector<int>();
    }
}

void Druid::reset_resource() {
    energy->reset_resource();
    rage->reset_resource();
    mana->reset_resource();
}

void Druid::reset_class_specific() {
    cancel_form();
    this->next_form_cd = 0.0;
    this->combo_points = 0;
    this->stealthed = false;
}
