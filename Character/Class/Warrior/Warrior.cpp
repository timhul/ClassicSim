#include "Warrior.h"

#include <QDebug>

#include "Arms.h"
#include "CharacterStats.h"
#include "CombatRoll.h"
#include "EnabledProcs.h"
#include "EnabledBuffs.h"
#include "Equipment.h"
#include "Fury.h"
#include "MainhandAttackWarrior.h"
#include "MainhandMeleeHit.h"
#include "OffhandAttackWarrior.h"
#include "OffhandMeleeHit.h"
#include "Protection.h"
#include "Race.h"
#include "Rage.h"
#include "Stats.h"
#include "Talents.h"
#include "WarriorEnchants.h"
#include "WarriorSpells.h"
#include "Weapon.h"

#include "Flurry.h"
#include "SwordSpecialization.h"
#include "UnbridledWrath.h"

#include "BattleStanceBuff.h"
#include "BerserkerStanceBuff.h"
#include "DefensiveStanceBuff.h"
#include "HeroicStrikeBuff.h"
#include "DeathWishBuff.h"
#include "BattleShoutBuff.h"
#include "OverpowerBuff.h"
#include "RecklessnessBuff.h"

Warrior::Warrior(Race* race, EquipmentDb* equipment_db, SimSettings* sim_settings) :
    Character(race, sim_settings) {
    available_races.append("Dwarf");
    available_races.append("Gnome");
    available_races.append("Human");
    available_races.append("Night Elf");
    available_races.append("Orc");
    available_races.append("Tauren");
    available_races.append("Troll");
    available_races.append("Undead");
    this->available_enchants = new WarriorEnchants(this);

    set_clvl(60);
    this->cstats = new CharacterStats(this, equipment_db);

    // CSIM-67: Investigate whether base stats below are the same for all melee classes.
    // Character sheet implies 3% base crit.
    // Crit without gear and no crit from base agil = 3 - (clvl * 5 - wpn-skill) * 0.04
    this->cstats->increase_crit(0.03);
    // Character sheet implies -17 base melee ap at 1: 26 STR -> 35 Melee AP = -17 base melee ap.
    // Character sheet implies 160 base melee ap at 60: 123 STR -> 406 Melee AP = 160 base melee ap.
    this->cstats->get_stats()->increase_base_melee_ap(160);

    // CSIM-68: Constants added as a hack for now, these are the gains from 1-60.
    // This essentially forces a clvl of 60 for stats to be accurate for warrior.
    cstats->increase_strength(97);
    cstats->increase_agility(60);
    cstats->increase_stamina(88);
    cstats->increase_intellect(10);
    cstats->increase_spirit(25);

    this->rage = new class Rage();
    this->resource = this->rage;
    this->stance = WarriorStances::Battle;
    this->stance_rage_remainder = 0;
    this->next_stance_cd = 0.0;

    this->warr_spells = new WarriorSpells(this);
    this->spells = dynamic_cast<Spells*>(warr_spells);

    this->flurry = new Flurry(this);
    this->battle_shout_buff = new BattleShoutBuff(this);
    this->battle_stance_buff = new BattleStanceBuff(this);
    this->berserker_stance_buff = new BerserkerStanceBuff(this);
    this->defensive_stance_buff = new DefensiveStanceBuff(this);
    this->heroic_strike_buff = new HeroicStrikeBuff(this);
    this->death_wish_buff = new DeathWishBuff(this);
    this->overpower_buff = new OverpowerBuff(this);
    this->recklessness_buff = new RecklessnessBuff(this);
    battle_shout_buff->enable_buff();
    battle_stance_buff->enable_buff();
    berserker_stance_buff->enable_buff();
    defensive_stance_buff->enable_buff();
    heroic_strike_buff->enable_buff();
    overpower_buff->enable_buff();
    recklessness_buff->enable_buff();

    this->sword_spec = new SwordSpecialization(this);
    this->unbridled_wrath = new UnbridledWrath(this);

    initialize_talents();

    spells->activate_racials();
}

Warrior::~Warrior() {
    cstats->get_equipment()->unequip_all();
    enabled_buffs->clear_all();
    enabled_procs->clear_all();

    delete available_enchants;
    delete cstats;
    delete warr_spells;
    // TODO: Create a WarriorProcs class.
    delete unbridled_wrath;
    delete sword_spec;
    // TODO: Create a WarriorBuffs class.
    delete battle_shout_buff;
    delete battle_stance_buff;
    delete berserker_stance_buff;
    delete defensive_stance_buff;
    delete death_wish_buff;
    delete flurry;
    delete heroic_strike_buff;
    delete overpower_buff;
    delete recklessness_buff;
    delete rage;
}

QString Warrior::get_name() const {
    return "Warrior";
}

QString Warrior::get_class_color() const {
    return "#C79C6E";
}

int Warrior::get_strength_modifier() const {
    return 3;
}

int Warrior::get_agility_modifier() const {
    return 0;
}

int Warrior::get_stamina_modifier() const {
    return 2;
}

int Warrior::get_intellect_modifier() const {
    return 0;
}

int Warrior::get_spirit_modifier() const {
    return 0;
}

double Warrior::get_agi_needed_for_one_percent_phys_crit() const {
    return 20;
}

double Warrior::get_int_needed_for_one_percent_spell_crit() const {
    return std::numeric_limits<double>::max();
}

int Warrior::get_ap_per_strength() const {
    return 2;
}

int Warrior::get_ap_per_agi() const {
    return 0;
}

void Warrior::gain_rage(const unsigned gained_rage) {
    this->rage->gain_resource(gained_rage);
}

void Warrior::lose_rage(const unsigned lost_rage) {
    this->rage->lose_resource(lost_rage);
}

unsigned Warrior::rage_gained_from_dd(const unsigned damage_dealt) const {
    // TODO: Check if you are guaranteed 1 rage on swing even with very low damage.
    return static_cast<unsigned>(std::max(1, int(round(damage_dealt / rage_conversion_value * 7.5))));
}

void Warrior::set_clvl(const int clvl) {
    this->clvl = clvl;
    this->rage_conversion_value = 0.0091107836 * std::pow(clvl, 2) + 3.225598133 * clvl + 4.2652911;
}

Flurry* Warrior::get_flurry() const {
    return this->flurry;
}

BattleStanceBuff* Warrior::get_battle_stance_buff() const {
    return this->battle_stance_buff;
}

BerserkerStanceBuff* Warrior::get_berserker_stance_buff() const {
    return this->berserker_stance_buff;
}

DefensiveStanceBuff* Warrior::get_defensive_stance_buff() const {
    return this->defensive_stance_buff;
}

HeroicStrikeBuff* Warrior::get_hs_buff() const {
    return this->heroic_strike_buff;
}

SwordSpecialization* Warrior::get_sword_spec() const {
    return this->sword_spec;
}

UnbridledWrath* Warrior::get_unbridled_wrath() const {
    return this->unbridled_wrath;
}

DeathWishBuff* Warrior::get_death_wish_buff() const {
    return this->death_wish_buff;
}

OverpowerBuff* Warrior::get_overpower_buff() const {
    return this->overpower_buff;
}

BattleShoutBuff* Warrior::get_battle_shout_buff() const {
    return this->battle_shout_buff;
}

RecklessnessBuff* Warrior::get_recklessness_buff() const {
    return this->recklessness_buff;
}

int Warrior::get_highest_possible_armor_type() const {
    return ArmorTypes::PLATE;
}

QVector<int> Warrior::get_weapon_proficiencies_for_slot(const int slot) const {
    switch (slot) {
    case EquipmentSlot::MAINHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::MACE, WeaponTypes::SWORD, WeaponTypes::POLEARM,
                             WeaponTypes::STAFF, WeaponTypes::TWOHAND_AXE,
                             WeaponTypes::TWOHAND_MACE, WeaponTypes::TWOHAND_SWORD});
    case EquipmentSlot::OFFHAND:
        return QVector<int>({WeaponTypes::AXE, WeaponTypes::DAGGER, WeaponTypes::FIST,
                             WeaponTypes::MACE, WeaponTypes::SWORD, WeaponTypes::CASTER_OFFHAND,
                             WeaponTypes::SHIELD});
    case EquipmentSlot::RANGED:
        return QVector<int>({WeaponTypes::BOW, WeaponTypes::CROSSBOW, WeaponTypes::GUN,
                             WeaponTypes::THROWN});
    default:
        assert(false);
        return QVector<int>();
    }
}

double Warrior::global_cooldown() const {
    return 1.5;
}

double Warrior::stance_cooldown() const {
    return 1.0;
}

unsigned Warrior::get_resource_level(const ResourceType) const {
    return this->rage->current;
}

void Warrior::increase_stance_rage_remainder() {
    this->stance_rage_remainder += 5;
    assert(stance_rage_remainder <= 25);
}

void Warrior::decrease_stance_rage_remainder() {
    assert(stance_rage_remainder >= 5);
    this->stance_rage_remainder -= 5;
}

unsigned Warrior::get_stance_remainder() const {
    return this->stance_rage_remainder;
}

bool Warrior::on_stance_cooldown() const {
    return engine->get_current_priority() < this->next_stance_cd;
}

void Warrior::new_stance_effect() {
    switch (this->stance) {
    case WarriorStances::Berserker:
        berserker_stance_buff->apply_buff();
        break;
    case WarriorStances::Defensive:
        defensive_stance_buff->apply_buff();
        break;
    }

    if (this->rage->current > stance_rage_remainder)
        this->rage->current = stance_rage_remainder;

    if ((engine->get_current_priority() + 0.5) > this->next_gcd) {
        this->next_gcd = engine->get_current_priority() + 0.5;
        auto* new_event = new CooldownReady(this->get_rotation(), next_gcd);
        engine->add_event(new_event);
    }

    this->next_stance_cd = engine->get_current_priority() + stance_cooldown();
}

void Warrior::switch_to_battle_stance() {
    switch (this->stance) {
    case WarriorStances::Berserker:
        berserker_stance_buff->cancel_buff();
        break;
    case WarriorStances::Defensive:
        defensive_stance_buff->cancel_buff();
        break;
    }

    this->stance = WarriorStances::Battle;
    new_stance_effect();
}

void Warrior::switch_to_berserker_stance() {
    switch (this->stance) {
    case WarriorStances::Defensive:
        defensive_stance_buff->cancel_buff();
        break;
    }

    this->stance = WarriorStances::Berserker;
    new_stance_effect();
}

void Warrior::switch_to_defensive_stance() {
    switch (this->stance) {
    case WarriorStances::Berserker:
        berserker_stance_buff->cancel_buff();
        break;
    }

    this->stance = WarriorStances::Defensive;
    new_stance_effect();
}

bool Warrior::in_battle_stance() const {
    return this->stance == WarriorStances::Battle;
}

bool Warrior::in_berserker_stance() const {
    return this->stance == WarriorStances::Berserker;
}

bool Warrior::in_defensive_stance() const {
    return this->stance == WarriorStances::Defensive;
}

void Warrior::melee_mh_white_hit_effect(const bool run_procs) {
    if (run_procs) {
        flurry->use_charge();
        run_mh_white_specific_proc_effects();
    }
}

void Warrior::melee_mh_yellow_hit_effect(const bool run_procs) {
    if (run_procs)
        run_mh_yellow_specific_proc_effects();
}

void Warrior::melee_mh_white_critical_effect(const bool run_procs) {
    flurry->apply_buff();
    warr_spells->apply_deep_wounds();

    if (run_procs)
        run_mh_white_specific_proc_effects();
}

void Warrior::melee_mh_yellow_critical_effect(const bool run_procs) {
    flurry->apply_buff();
    warr_spells->apply_deep_wounds();

    if (run_procs)
        run_mh_yellow_specific_proc_effects();
}

void Warrior::melee_oh_white_hit_effect(const bool run_procs) {
    if (run_procs) {
        flurry->use_charge();
        run_oh_white_specific_proc_effects();
    }
}

void Warrior::melee_oh_yellow_hit_effect(const bool run_procs) {
    if (run_procs)
        run_oh_yellow_specific_proc_effects();
}

void Warrior::melee_oh_white_critical_effect(const bool run_procs) {
    flurry->apply_buff();
    warr_spells->apply_deep_wounds();

    if (run_procs)
        run_oh_white_specific_proc_effects();
}

void Warrior::melee_oh_yellow_critical_effect(const bool run_procs) {
    flurry->apply_buff();
    warr_spells->apply_deep_wounds();

    if (run_procs)
        run_oh_yellow_specific_proc_effects();
}

void Warrior::initialize_talents() {
    for (int i = 0; i < 3; ++i) {
        talents->add_talent_tree(new Arms(this), new Fury(this), new Protection(this));
    }
}

void Warrior::reset_class_specific() {
    // TODO: Consider adding pre-run actions for stance
    switch_to_battle_stance();
    this->next_stance_cd = 0.0 - stance_cooldown();
}
