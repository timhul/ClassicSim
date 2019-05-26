#include "CharacterStats.h"

#include "Buff.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "Race.h"
#include "Stats.h"
#include "Target.h"
#include "Utils/Check.h"
#include "Weapon.h"

CharacterStats::CharacterStats(Character* pchar, EquipmentDb *equipment_db) :
    pchar(pchar),
    equipment(new Equipment(equipment_db, pchar)),
    axe_skill_bonus(0),
    dagger_skill_bonus(0),
    mace_skill_bonus(0),
    sword_skill_bonus(0),
    melee_ability_crit_dmg_mod(2.0),
    ranged_ability_crit_dmg_mod(2.0),
    spell_crit_dmg_mod(1.5),
    melee_attack_speed_mod(1.0),
    ranged_attack_speed_mod(1.0),
    total_phys_dmg_mod(1.0),
    physical_damage_taken_mod(1.0),
    spell_damage_taken_mod(1.0),
    total_ap_mod(1.0),
    agility_mod(1.0),
    intellect_mod(1.0),
    spirit_mod(1.0),
    stamina_mod(1.0),
    strength_mod(1.0)
{
    this->base_stats = new Stats();

    increase_strength(pchar->get_strength_modifier());
    increase_agility(pchar->get_agility_modifier());
    increase_stamina(pchar->get_stamina_modifier());
    increase_intellect(pchar->get_intellect_modifier());
    increase_spirit(pchar->get_spirit_modifier());

    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::AXE, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_AXE, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::DAGGER, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::POLEARM, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::BOW, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::CROSSBOW, 0.0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::GUN, 0.0);

    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::AXE, 0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::DAGGER, 0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::FIST, 0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::MACE, 0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::SWORD, 0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_AXE, 0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_MACE, 0);
    this->damage_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_SWORD, 0);

    this->damage_bonuses_per_monster_type.insert(Target::CreatureType::Beast, 0);
    this->damage_bonuses_per_monster_type.insert(Target::CreatureType::Demon, 0);
    this->damage_bonuses_per_monster_type.insert(Target::CreatureType::Dragonkin, 0);
    this->damage_bonuses_per_monster_type.insert(Target::CreatureType::Elemental, 0);
    this->damage_bonuses_per_monster_type.insert(Target::CreatureType::Giant, 0);
    this->damage_bonuses_per_monster_type.insert(Target::CreatureType::Humanoid, 0);
    this->damage_bonuses_per_monster_type.insert(Target::CreatureType::Mechanical, 0);
    this->damage_bonuses_per_monster_type.insert(Target::CreatureType::Undead, 0);

    this->crit_dmg_bonuses_per_monster_type.insert(Target::CreatureType::Beast, 0);
    this->crit_dmg_bonuses_per_monster_type.insert(Target::CreatureType::Demon, 0);
    this->crit_dmg_bonuses_per_monster_type.insert(Target::CreatureType::Dragonkin, 0);
    this->crit_dmg_bonuses_per_monster_type.insert(Target::CreatureType::Elemental, 0);
    this->crit_dmg_bonuses_per_monster_type.insert(Target::CreatureType::Giant, 0);
    this->crit_dmg_bonuses_per_monster_type.insert(Target::CreatureType::Humanoid, 0);
    this->crit_dmg_bonuses_per_monster_type.insert(Target::CreatureType::Mechanical, 0);
    this->crit_dmg_bonuses_per_monster_type.insert(Target::CreatureType::Undead, 0);

    this->spell_school_damage_changes.insert(MagicSchool::Arcane, {});
    this->spell_school_damage_changes.insert(MagicSchool::Fire, {});
    this->spell_school_damage_changes.insert(MagicSchool::Frost, {});
    this->spell_school_damage_changes.insert(MagicSchool::Holy, {});
    this->spell_school_damage_changes.insert(MagicSchool::Nature, {});
    this->spell_school_damage_changes.insert(MagicSchool::Physical, {});
    this->spell_school_damage_changes.insert(MagicSchool::Shadow, {});

    this->spell_school_damage_modifiers.insert(MagicSchool::Arcane, 1.0);
    this->spell_school_damage_modifiers.insert(MagicSchool::Fire, 1.0);
    this->spell_school_damage_modifiers.insert(MagicSchool::Frost, 1.0);
    this->spell_school_damage_modifiers.insert(MagicSchool::Holy, 1.0);
    this->spell_school_damage_modifiers.insert(MagicSchool::Nature, 1.0);
    this->spell_school_damage_modifiers.insert(MagicSchool::Physical, 1.0);
    this->spell_school_damage_modifiers.insert(MagicSchool::Shadow, 1.0);

    this->magic_school_buffs_with_charges.insert(MagicSchool::Arcane, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Fire, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Frost, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Holy, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Nature, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Physical, {});
    this->magic_school_buffs_with_charges.insert(MagicSchool::Shadow, {});
}

CharacterStats::~CharacterStats() {
    delete base_stats;
    delete equipment;
}

Equipment* CharacterStats::get_equipment() const {
    return this->equipment;
}

Stats* CharacterStats::get_stats() const {
    return this->base_stats;
}

unsigned CharacterStats::get_strength() const {
    return static_cast<unsigned>(round(strength_mod *
                                       (base_stats->get_strength() +
                                        equipment->get_stats()->get_strength() +
                                        pchar->get_race()->get_base_strength())));
}

unsigned CharacterStats::get_agility() const {
    return static_cast<unsigned>(round(agility_mod *
                                       (base_stats->get_agility() +
                                        equipment->get_stats()->get_agility() +
                                        pchar->get_race()->get_base_agility())));
}

unsigned CharacterStats::get_stamina() const {
    return static_cast<unsigned>(round(stamina_mod *
                                       (base_stats->get_stamina() +
                                        equipment->get_stats()->get_stamina() +
                                        pchar->get_race()->get_base_stamina())));
}

unsigned CharacterStats::get_intellect() const {
    return static_cast<unsigned>(round(intellect_mod *
                                       (base_stats->get_intellect() +
                                        equipment->get_stats()->get_intellect() +
                                        pchar->get_race()->get_base_intellect())));
}

unsigned CharacterStats::get_spirit() const {
    return static_cast<unsigned>(round(spirit_mod *
                                       (base_stats->get_spirit() +
                                        equipment->get_stats()->get_spirit() +
                                        pchar->get_race()->get_base_spirit())));
}

unsigned CharacterStats::get_melee_hit_chance() const {
    return base_stats->get_melee_hit_chance() + equipment->get_stats()->get_melee_hit_chance();
}

unsigned CharacterStats::get_mh_crit_chance() const {
    const unsigned equip_effect = base_stats->get_melee_crit_chance() + equipment->get_stats()->get_melee_crit_chance();
    const unsigned crit_from_agi = static_cast<unsigned>(round(static_cast<double>(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit() * 100));

    double crit_from_wpn_type = 0.0;
    if (equipment->get_mainhand() != nullptr)
        crit_from_wpn_type = crit_bonuses_per_weapon_type[equipment->get_mainhand()->get_weapon_type()];

    return equip_effect + crit_from_agi + static_cast<unsigned>(crit_from_wpn_type * 10000);
}

unsigned CharacterStats::get_oh_crit_chance() const {
    double crit_from_wpn_type = 0.0;
    if (equipment->get_offhand() != nullptr)
        crit_from_wpn_type = crit_bonuses_per_weapon_type[equipment->get_offhand()->get_weapon_type()];
    else
        return 0;

    const unsigned equip_effect = base_stats->get_melee_crit_chance() + equipment->get_stats()->get_melee_crit_chance();
    const unsigned crit_from_agi = static_cast<unsigned>(round(static_cast<double>(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit() * 100));

    return equip_effect + crit_from_agi + static_cast<unsigned>(crit_from_wpn_type * 10000);
}

unsigned CharacterStats::get_ranged_hit_chance() const {
    return base_stats->get_ranged_hit_chance() + equipment->get_stats()->get_ranged_hit_chance();
}

unsigned CharacterStats::get_ranged_crit_chance() const {
    const unsigned equip_effect = base_stats->get_ranged_crit_chance() + equipment->get_stats()->get_ranged_crit_chance();
    const unsigned crit_from_agi = static_cast<unsigned>(round(static_cast<double>(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit() * 100));

    double crit_from_wpn_type = 0.0;
    if (equipment->get_mainhand() != nullptr)
        crit_from_wpn_type = crit_bonuses_per_weapon_type[equipment->get_mainhand()->get_weapon_type()];

    return equip_effect + crit_from_agi + static_cast<unsigned>(crit_from_wpn_type * 10000);
}

void CharacterStats::increase_wpn_skill(const int weapon_type, const int increase) {
    switch (weapon_type) {
    case WeaponTypes::AXE:
        axe_skill_bonus += increase;
        break;
    case WeaponTypes::DAGGER:
        dagger_skill_bonus += increase;
        break;
    case WeaponTypes::MACE:
        mace_skill_bonus += increase;
        break;
    case WeaponTypes::SWORD:
        sword_skill_bonus += increase;
        break;
    }
}

void CharacterStats::decrease_wpn_skill(const int weapon_type, const int decrease) {
    switch (weapon_type) {
    case WeaponTypes::AXE:
        check((axe_skill_bonus >= decrease), "Underflow decrease");
        axe_skill_bonus -= decrease;
        break;
    case WeaponTypes::DAGGER:
        check((dagger_skill_bonus >= decrease), "Underflow decrease");
        dagger_skill_bonus -= decrease;
        break;
    case WeaponTypes::MACE:
        check((mace_skill_bonus >= decrease), "Underflow decrease");
        mace_skill_bonus -= decrease;
        break;
    case WeaponTypes::SWORD:
        check((sword_skill_bonus >= decrease), "Underflow decrease");
        sword_skill_bonus -= decrease;
        break;
    }
}

int CharacterStats::get_mh_wpn_skill() const {
    return get_wpn_skill(equipment->get_mainhand());
}

int CharacterStats::get_oh_wpn_skill() const {
    return get_wpn_skill(equipment->get_offhand());
}

int CharacterStats::get_ranged_wpn_skill() const {
    return get_wpn_skill(equipment->get_ranged());
}

int CharacterStats::get_wpn_skill(Weapon* weapon) const {
    if (weapon == nullptr)
        return pchar->get_clvl() * 5;

    int skill_bonus = 0;
    switch (weapon->get_weapon_type()) {
    case WeaponTypes::AXE:
    case WeaponTypes::TWOHAND_AXE:
        skill_bonus += pchar->get_race()->get_axe_bonus() + equipment->get_stats()->get_axe_skill() + axe_skill_bonus;
        break;
    case WeaponTypes::DAGGER:
        skill_bonus += equipment->get_stats()->get_dagger_skill() + dagger_skill_bonus;
        break;
    case WeaponTypes::SWORD:
    case WeaponTypes::TWOHAND_SWORD:
        skill_bonus += pchar->get_race()->get_sword_bonus() + equipment->get_stats()->get_sword_skill() + sword_skill_bonus;
        break;
    case WeaponTypes::MACE:
    case WeaponTypes::TWOHAND_MACE:
        skill_bonus += pchar->get_race()->get_mace_bonus() + equipment->get_stats()->get_mace_skill() + mace_skill_bonus;
        break;
    case WeaponTypes::BOW:
        skill_bonus += pchar->get_race()->get_bow_bonus() + equipment->get_stats()->get_bow_skill();
        break;
    case WeaponTypes::CROSSBOW:
        skill_bonus += equipment->get_stats()->get_crossbow_skill();
        break;
    case WeaponTypes::GUN:
        skill_bonus += pchar->get_race()->get_gun_bonus() + equipment->get_stats()->get_gun_skill();
        break;
    }
    return pchar->get_clvl() * 5 + skill_bonus;
}

void CharacterStats::increase_stat(const ItemStats stat_type, const unsigned value) {
    switch (stat_type) {
    case ItemStats::Agility:
        return increase_agility(value);
     case ItemStats::Intellect:
        return increase_intellect(value);
     case ItemStats::Spirit:
        return increase_spirit(value);
    case ItemStats::Stamina:
        return increase_stamina(value);
    case ItemStats::Strength:
        return increase_strength(value);
    case ItemStats::ManaPer5:
        return increase_mp5(value);
    case ItemStats::SpellDamage:
        return increase_base_spell_damage(value);
    case ItemStats::SpellCrit:
        return increase_spell_crit(value);
    case ItemStats::SpellHit:
        return increase_spell_hit(value);
    case ItemStats::Armor:
    case ItemStats::Defense:
    case ItemStats::DodgeChance:
    case ItemStats::ParryChance:
    case ItemStats::ResistanceArcane:
    case ItemStats::ResistanceFire:
    case ItemStats::ResistanceFrost:
    case ItemStats::ResistanceHoly:
    case ItemStats::ResistanceNature:
    case ItemStats::ResistanceShadow:
    case ItemStats::ResistanceAll:
    case ItemStats::SkillAxe:
    case ItemStats::SkillDagger:
    case ItemStats::SkillMace:
    case ItemStats::SkillSword:
    case ItemStats::SkillBow:
    case ItemStats::SkillCrossbow:
    case ItemStats::SkillGun:
        return;
    case ItemStats::HitChance:
        increase_ranged_hit(value);
        return increase_melee_hit(value);
    case ItemStats::CritChance:
        increase_ranged_crit(value);
        return increase_melee_crit(value);
    case ItemStats::AttackSpeedPercent:
        pchar->increase_ranged_attack_speed(value);
        return pchar->increase_melee_attack_speed(value);
    case ItemStats::MeleeAttackSpeedPercent:
        return pchar->increase_melee_attack_speed(value);
    case ItemStats::RangedAttackSpeedPercent:
        return pchar->increase_ranged_attack_speed(value);
    case ItemStats::AttackPower:
        increase_melee_ap(value);
        return increase_ranged_ap(value);
    case ItemStats::APVersusBeast:
    case ItemStats::APVersusDemon:
    case ItemStats::APVersusDragonkin:
    case ItemStats::APVersusElemental:
    case ItemStats::APVersusGiant:
    case ItemStats::APVersusHumanoid:
    case ItemStats::APVersusMechanical:
    case ItemStats::APVersusUndead:
    case ItemStats::MeleeAttackPower:
    case ItemStats::RangedAttackPower:
        return increase_ap_vs_type(get_type_for_stat(stat_type), value);
    }
}

void CharacterStats::decrease_stat(const ItemStats stat_type, const unsigned value) {
    switch (stat_type) {
    case ItemStats::Agility:
        return decrease_agility(value);
     case ItemStats::Intellect:
        return decrease_intellect(value);
     case ItemStats::Spirit:
        return decrease_spirit(value);
    case ItemStats::Stamina:
        return decrease_stamina(value);
    case ItemStats::Strength:
        return decrease_strength(value);
    case ItemStats::ManaPer5:
        return decrease_mp5(value);
    case ItemStats::SpellDamage:
        return decrease_base_spell_damage(value);
    case ItemStats::SpellCrit:
        return decrease_spell_crit(value);
    case ItemStats::SpellHit:
        return decrease_spell_hit(value);
    case ItemStats::Armor:
    case ItemStats::Defense:
    case ItemStats::DodgeChance:
    case ItemStats::ParryChance:
    case ItemStats::ResistanceArcane:
    case ItemStats::ResistanceFire:
    case ItemStats::ResistanceFrost:
    case ItemStats::ResistanceHoly:
    case ItemStats::ResistanceNature:
    case ItemStats::ResistanceShadow:
    case ItemStats::ResistanceAll:
    case ItemStats::SkillAxe:
    case ItemStats::SkillDagger:
    case ItemStats::SkillMace:
    case ItemStats::SkillSword:
    case ItemStats::SkillBow:
    case ItemStats::SkillCrossbow:
    case ItemStats::SkillGun:
        return;
    case ItemStats::HitChance:
        decrease_ranged_hit(value);
        return decrease_melee_hit(value);
    case ItemStats::CritChance:
        decrease_ranged_crit(value);
        return decrease_melee_crit(value);
    case ItemStats::AttackSpeedPercent:
        pchar->decrease_ranged_attack_speed(value);
        return pchar->decrease_melee_attack_speed(value);
    case ItemStats::MeleeAttackSpeedPercent:
        return pchar->decrease_melee_attack_speed(value);
    case ItemStats::RangedAttackSpeedPercent:
        return pchar->decrease_ranged_attack_speed(value);
    case ItemStats::AttackPower:
        decrease_melee_ap(value);
        return decrease_ranged_ap(value);
    case ItemStats::APVersusBeast:
    case ItemStats::APVersusDemon:
    case ItemStats::APVersusDragonkin:
    case ItemStats::APVersusElemental:
    case ItemStats::APVersusGiant:
    case ItemStats::APVersusHumanoid:
    case ItemStats::APVersusMechanical:
    case ItemStats::APVersusUndead:
    case ItemStats::MeleeAttackPower:
    case ItemStats::RangedAttackPower:
        return decrease_ap_vs_type(get_type_for_stat(stat_type), value);
    }
}

void CharacterStats::increase_melee_attack_speed(const unsigned increase) {
    add_multiplicative_effect(melee_attack_speed_buffs, static_cast<int>(increase), melee_attack_speed_mod);
}

void CharacterStats::decrease_melee_attack_speed(const unsigned decrease) {
    remove_multiplicative_effect(melee_attack_speed_buffs, static_cast<int>(decrease), melee_attack_speed_mod);
}

void CharacterStats::increase_ranged_attack_speed(const unsigned increase) {
    add_multiplicative_effect(ranged_attack_speed_buffs, static_cast<int>(increase), ranged_attack_speed_mod);
}

void CharacterStats::decrease_ranged_attack_speed(const unsigned decrease) {
    remove_multiplicative_effect(ranged_attack_speed_buffs, static_cast<int>(decrease), ranged_attack_speed_mod);
}

void CharacterStats::increase_strength(const unsigned increase) {
    base_stats->increase_strength(increase);
}

void CharacterStats::decrease_strength(const unsigned decrease) {
    base_stats->decrease_strength(decrease);
}

void CharacterStats::increase_agility(const unsigned increase) {
    base_stats->increase_agility(increase);
}

void CharacterStats::decrease_agility(const unsigned decrease) {
    base_stats->decrease_agility(decrease);
}

void CharacterStats::increase_stamina(const unsigned increase) {
    base_stats->increase_stamina(increase);
}

void CharacterStats::decrease_stamina(const unsigned decrease) {
    base_stats->decrease_stamina(decrease);
}

void CharacterStats::increase_intellect(const unsigned increase) {
    base_stats->increase_intellect(increase);
}

void CharacterStats::decrease_intellect(const unsigned decrease) {
    base_stats->decrease_intellect(decrease);
}

void CharacterStats::increase_spirit(const unsigned increase) {
    base_stats->increase_spirit(increase);
}

void CharacterStats::decrease_spirit(const unsigned decrease) {
    base_stats->decrease_spirit(decrease);
}

unsigned CharacterStats::get_melee_ap() const {
    unsigned stat_melee_ap = equipment->get_stats()->get_base_melee_ap() + base_stats->get_base_melee_ap();
    unsigned attributes_ap = get_strength() * pchar->get_melee_ap_per_strength() + get_agility() * pchar->get_melee_ap_per_agi();
    unsigned target_ap_eq = equipment->get_stats()->get_melee_ap_against_type(pchar->get_target()->get_creature_type());
    unsigned target_ap_base = base_stats->get_melee_ap_against_type(pchar->get_target()->get_creature_type());
    return static_cast<unsigned>(round(total_ap_mod * (stat_melee_ap + attributes_ap + target_ap_eq + target_ap_base)));
}

void CharacterStats::increase_melee_ap(const unsigned increase) {
    base_stats->increase_base_melee_ap(increase);
}

void CharacterStats::decrease_melee_ap(const unsigned decrease) {
    base_stats->decrease_base_melee_ap(decrease);
}

unsigned CharacterStats::get_ranged_ap() const {
    unsigned stat_ranged_ap = equipment->get_stats()->get_base_ranged_ap() + base_stats->get_base_ranged_ap();
    unsigned attributes_ap = get_agility() * pchar->get_ranged_ap_per_agi();
    unsigned target_ap_eq = equipment->get_stats()->get_ranged_ap_against_type(pchar->get_target()->get_creature_type());
    unsigned target_ap_base = base_stats->get_ranged_ap_against_type(pchar->get_target()->get_creature_type());
    return static_cast<unsigned>(round(total_ap_mod * (stat_ranged_ap + attributes_ap + target_ap_eq + target_ap_base)));
}

void CharacterStats::increase_ranged_ap(const unsigned increase) {
    base_stats->increase_base_ranged_ap(increase);
}

void CharacterStats::decrease_ranged_ap(const unsigned decrease) {
    base_stats->decrease_base_ranged_ap(decrease);
}

void CharacterStats::increase_ap_vs_type(const Target::CreatureType target_type, const unsigned value) {
    base_stats->increase_melee_ap_against_type(target_type, value);
    base_stats->increase_ranged_ap_against_type(target_type, value);
}

void CharacterStats::decrease_ap_vs_type(const Target::CreatureType target_type, const unsigned value) {
    base_stats->decrease_melee_ap_against_type(target_type, value);
    base_stats->decrease_ranged_ap_against_type(target_type, value);
}

void CharacterStats::increase_dmg_vs_type(const Target::CreatureType target_type, const double value) {
    damage_bonuses_per_monster_type[target_type] += value;
}

void CharacterStats::decrease_dmg_vs_type(const Target::CreatureType target_type, const double value) {
    damage_bonuses_per_monster_type[target_type] -= value;
}

void CharacterStats::increase_crit_dmg_vs_type(const Target::CreatureType target_type, const unsigned value) {
    crit_dmg_bonuses_per_monster_type[target_type] += static_cast<double>(value) / 100;
}

void CharacterStats::decrease_crit_dmg_vs_type(const Target::CreatureType target_type, const unsigned value) {
    crit_dmg_bonuses_per_monster_type[target_type] -= static_cast<double>(value) / 100;
}

double CharacterStats::get_total_phys_dmg_mod() const {
    double dmg_bonus_from_wpn_type = 1.0;

    Weapon* weapon = nullptr;
    switch (pchar->get_spells()->get_attack_mode()) {
    case MeleeAttack:
        weapon = equipment->get_mainhand();
        break;
    case RangedAttack:
        weapon = equipment->get_ranged();
        break;
    case MagicAttack:
        break;
    }

    if (weapon != nullptr)
        dmg_bonus_from_wpn_type += double(damage_bonuses_per_weapon_type[weapon->get_weapon_type()]) / 100;

    double dmg_bonus_from_monster_type = 1.0 + damage_bonuses_per_monster_type[pchar->get_target()->get_creature_type()];

    return total_phys_dmg_mod * dmg_bonus_from_wpn_type * dmg_bonus_from_monster_type;
}

double CharacterStats::get_melee_attack_speed_mod() const {
    return melee_attack_speed_mod;
}

double CharacterStats::get_ranged_attack_speed_mod() const {
    return ranged_attack_speed_mod;
}

double CharacterStats::get_physical_damage_taken_mod() const {
    return physical_damage_taken_mod;
}

double CharacterStats::get_spell_damage_taken_mod() const {
    return spell_damage_taken_mod;
}

void CharacterStats::increase_melee_hit(const unsigned increase) {
    base_stats->increase_melee_hit(increase);
    pchar->get_combat_roll()->update_melee_miss_chance();
}

void CharacterStats::decrease_melee_hit(const unsigned decrease) {
    base_stats->decrease_melee_hit(decrease);
    pchar->get_combat_roll()->update_melee_miss_chance();
}

void CharacterStats::increase_melee_crit(const unsigned increase) {
    base_stats->increase_melee_crit(increase);
}

void CharacterStats::decrease_melee_crit(const unsigned decrease) {
    base_stats->decrease_melee_crit(decrease);
}

void CharacterStats::increase_ranged_hit(const unsigned increase) {
    base_stats->increase_ranged_hit(increase);
    pchar->get_combat_roll()->update_ranged_miss_chance();
}

void CharacterStats::decrease_ranged_hit(const unsigned decrease) {
    base_stats->decrease_ranged_hit(decrease);
    pchar->get_combat_roll()->update_ranged_miss_chance();
}

void CharacterStats::increase_ranged_crit(const unsigned increase) {
    base_stats->increase_ranged_crit(increase);
}

void CharacterStats::decrease_ranged_crit(const unsigned decrease) {
    base_stats->decrease_ranged_crit(decrease);
}

void CharacterStats::increase_crit_for_weapon_type(const int weapon_type, const double increase) {
    crit_bonuses_per_weapon_type[weapon_type] += increase;
}

void CharacterStats::decrease_crit_for_weapon_type(const int weapon_type, const double decrease) {
    crit_bonuses_per_weapon_type[weapon_type] -= decrease;
}

void CharacterStats::increase_total_phys_dmg_for_weapon_type(const int weapon_type, const int increase) {
    damage_bonuses_per_weapon_type[weapon_type] += increase;
}

void CharacterStats::decrease_total_phys_dmg_for_weapon_type(const int weapon_type, const int decrease) {
    damage_bonuses_per_weapon_type[weapon_type] -= decrease;
}

unsigned CharacterStats::get_spell_hit_chance() const {
    return base_stats->get_spell_hit_chance() + equipment->get_stats()->get_spell_hit_chance();
}

void CharacterStats::increase_spell_hit(const unsigned increase) {
    base_stats->increase_spell_hit(increase);
    pchar->get_combat_roll()->update_spell_miss_chance(get_spell_hit_chance());
}

void CharacterStats::decrease_spell_hit(const unsigned decrease) {
    base_stats->decrease_spell_hit(decrease);
    pchar->get_combat_roll()->update_spell_miss_chance(get_spell_hit_chance());
}

unsigned CharacterStats::get_spell_crit_chance() const {
    const unsigned equip_effect = base_stats->get_spell_crit_chance()  + equipment->get_stats()->get_spell_crit_chance();
    const auto crit_from_int = static_cast<unsigned>(round(static_cast<double>(get_intellect()) / pchar->get_int_needed_for_one_percent_spell_crit() * 100));

    return equip_effect + crit_from_int;
}

void CharacterStats::increase_spell_crit(const unsigned increase) {
    base_stats->increase_spell_crit(increase);
}

void CharacterStats::decrease_spell_crit(const unsigned decrease) {
    base_stats->decrease_spell_crit(decrease);
}

double CharacterStats::get_melee_ability_crit_dmg_mod() const {
    return melee_ability_crit_dmg_mod + crit_dmg_bonuses_per_monster_type[pchar->get_target()->get_creature_type()];
}

void CharacterStats::increase_melee_ability_crit_dmg_mod(double increase) {
    melee_ability_crit_dmg_mod += increase;
}

void CharacterStats::decrease_melee_ability_crit_dmg_mod(double decrease) {
    melee_ability_crit_dmg_mod -= decrease;
}

double CharacterStats::get_ranged_ability_crit_dmg_mod() const {
    return ranged_ability_crit_dmg_mod + crit_dmg_bonuses_per_monster_type[pchar->get_target()->get_creature_type()];
}

void CharacterStats::increase_ranged_ability_crit_dmg_mod(double increase) {
    ranged_ability_crit_dmg_mod += increase;
}

void CharacterStats::decrease_ranged_ability_crit_dmg_mod(double decrease) {
    ranged_ability_crit_dmg_mod -= decrease;
}

double CharacterStats::get_spell_crit_dmg_mod() const {
    return spell_crit_dmg_mod  + crit_dmg_bonuses_per_monster_type[pchar->get_target()->get_creature_type()];
}

void CharacterStats::increase_spell_crit_dmg_mod(double increase) {
    spell_crit_dmg_mod += increase;
}

void CharacterStats::decrease_spell_crit_dmg_mod(double decrease) {
    spell_crit_dmg_mod -= decrease;
}

void CharacterStats::increase_total_phys_dmg_mod(const int increase) {
    add_multiplicative_effect(phys_dmg_buffs, increase, total_phys_dmg_mod);
}

void CharacterStats::decrease_total_phys_dmg_mod(const int decrease) {
    remove_multiplicative_effect(phys_dmg_buffs, decrease, total_phys_dmg_mod);
}

void CharacterStats::add_phys_damage_taken_mod(const int mod) {
    add_multiplicative_effect(phys_damage_taken_changes, mod, physical_damage_taken_mod);
}

void CharacterStats::remove_phys_damage_taken_mod(const int mod) {
    remove_multiplicative_effect(phys_damage_taken_changes, mod, physical_damage_taken_mod);
}

void CharacterStats::add_spell_damage_taken_mod(const int mod) {
    add_multiplicative_effect(spell_damage_taken_changes, mod, spell_damage_taken_mod);
}

void CharacterStats::remove_spell_damage_taken_mod(const int mod) {
    remove_multiplicative_effect(spell_damage_taken_changes, mod, spell_damage_taken_mod);
}

void CharacterStats::add_total_stat_mod(const int mod) {
    add_agility_mod(mod);
    add_intellect_mod(mod);
    add_spirit_mod(mod);
    add_stamina_mod(mod);
    add_strength_mod(mod);
}

void CharacterStats::remove_total_stat_mod(const int mod) {
    remove_agility_mod(mod);
    remove_intellect_mod(mod);
    remove_spirit_mod(mod);
    remove_stamina_mod(mod);
    remove_strength_mod(mod);
}

void CharacterStats::add_ap_multiplier(const int mod) {
    add_multiplicative_effect(ap_total_multipliers, mod, total_ap_mod);
}

void CharacterStats::remove_ap_multiplier(const int mod) {
    remove_multiplicative_effect(ap_total_multipliers, mod, total_ap_mod);
}

void CharacterStats::add_agility_mod(const int mod) {
    add_multiplicative_effect(agility_mod_changes, mod, agility_mod);
}

void CharacterStats::remove_agility_mod(const int mod) {
    remove_multiplicative_effect(agility_mod_changes, mod, agility_mod);
}

void CharacterStats::add_intellect_mod(const int mod) {
    add_multiplicative_effect(intellect_mod_changes, mod, intellect_mod);
}

void CharacterStats::remove_intellect_mod(const int mod) {
    remove_multiplicative_effect(intellect_mod_changes, mod, intellect_mod);
}

void CharacterStats::add_spirit_mod(const int mod) {
    add_multiplicative_effect(spirit_mod_changes, mod, spirit_mod);
}

void CharacterStats::remove_spirit_mod(const int mod) {
    remove_multiplicative_effect(spirit_mod_changes, mod, spirit_mod);
}

void CharacterStats::add_stamina_mod(const int mod) {
    add_multiplicative_effect(stamina_mod_changes, mod, stamina_mod);
}

void CharacterStats::remove_stamina_mod(const int mod) {
    remove_multiplicative_effect(stamina_mod_changes, mod, stamina_mod);
}

void CharacterStats::add_strength_mod(const int mod) {
    add_multiplicative_effect(strength_mod_changes, mod, strength_mod);
}

void CharacterStats::remove_strength_mod(const int mod) {
    remove_multiplicative_effect(strength_mod_changes, mod, strength_mod);
}

double CharacterStats::get_mh_wpn_speed() {
    return pchar->has_mainhand() ? equipment->get_mainhand()->get_base_weapon_speed() / melee_attack_speed_mod :
                                   2.0 / melee_attack_speed_mod;
}

double CharacterStats::get_oh_wpn_speed() {
    return pchar->has_offhand() ? equipment->get_offhand()->get_base_weapon_speed() / melee_attack_speed_mod :
                                  300;
}

double CharacterStats::get_ranged_wpn_speed() {
    return pchar->has_ranged() ? equipment->get_ranged()->get_base_weapon_speed() / ranged_attack_speed_mod :
                                 300;
}

void CharacterStats::increase_dodge(const double dodge) {
    base_stats->increase_dodge(dodge);
}

void CharacterStats::decrease_dodge(const double dodge) {
    base_stats->decrease_dodge(dodge);
}

unsigned CharacterStats::get_mp5() const {
    return base_stats->get_mp5() + equipment->get_stats()->get_mp5();
}

void CharacterStats::increase_mp5(const unsigned increase) {
    base_stats->increase_mp5(increase);
}

void CharacterStats::decrease_mp5(const unsigned decrease) {
    base_stats->decrease_mp5(decrease);
}

unsigned CharacterStats::get_spell_damage(const MagicSchool school) const {
    return base_stats->get_spell_damage(school) + equipment->get_stats()->get_spell_damage(school);
}

void CharacterStats::increase_base_spell_damage(const unsigned increase) {
    base_stats->increase_base_spell_damage(increase);
}

void CharacterStats::decrease_base_spell_damage(const unsigned decrease) {
    base_stats->decrease_base_spell_damage(decrease);
}

void CharacterStats::increase_spell_damage_vs_school(const unsigned increase, const MagicSchool school) {
    base_stats->increase_spell_damage_vs_school(increase, school);
}

void CharacterStats::decrease_spell_damage_vs_school(const unsigned decrease, const MagicSchool school) {
    base_stats->decrease_spell_damage_vs_school(decrease, school);
}

double CharacterStats::get_spell_dmg_mod(const MagicSchool school) const {
    const double mod = spell_school_damage_modifiers[school];

    for (auto & buff : magic_school_buffs_with_charges[school])
        buff->use_charge();

    return mod;
}

void CharacterStats::increase_spell_dmg_mod(const int increase, const MagicSchool school, Buff* buff_with_charges) {
    add_multiplicative_effect(spell_school_damage_changes[school], increase, spell_school_damage_modifiers[school]);

    if (buff_with_charges != nullptr)
        magic_school_buffs_with_charges[school].append(buff_with_charges);
}

void CharacterStats::decrease_spell_dmg_mod(const int decrease, const MagicSchool school, Buff* buff_to_remove) {
    remove_multiplicative_effect(spell_school_damage_changes[school], decrease, spell_school_damage_modifiers[school]);

    if (buff_to_remove != nullptr) {
        for (int i = 0; i < magic_school_buffs_with_charges[school].size(); ++i) {
            Buff* buff = magic_school_buffs_with_charges[school][i];
            if (buff->get_instance_id() == buff_to_remove->get_instance_id()) {
                magic_school_buffs_with_charges[school].removeAt(i);
                return;
            }
        }

        check(false, QString("CharacterStats::decrease_spell_dmg_mod failed to remove buff %1").arg(buff_to_remove->get_name()).toStdString());
    }
}

void CharacterStats::add_multiplicative_effect(QVector<int>& effects, int add_value, double &modifier) {
    effects.append(add_value);

    recalculate_multiplicative_effects(effects, modifier);
}

void CharacterStats::remove_multiplicative_effect(QVector<int>& effects, int remove_value, double &modifier) {
    check(effects.removeOne(remove_value), "Failed to remove multiplicative effect");

    recalculate_multiplicative_effects(effects, modifier);
}

void CharacterStats::recalculate_multiplicative_effects(QVector<int>& effects, double& modifier) {
    modifier = 1.0;
    for (int effect : effects) {
        double coefficient = 1.0 + double(effect) / 100;
        modifier = modifier * coefficient;
    }

    check((modifier > 0), "Modifier negative");
}

Target::CreatureType CharacterStats::get_type_for_stat(const ItemStats stats) {
    switch (stats) {
    case ItemStats::APVersusBeast:
        return Target::CreatureType::Beast;
    case ItemStats::APVersusDemon:
        return Target::CreatureType::Demon;
    case ItemStats::APVersusDragonkin:
        return Target::CreatureType::Dragonkin;
    case ItemStats::APVersusElemental:
        return Target::CreatureType::Elemental;
    case ItemStats::APVersusGiant:
        return Target::CreatureType::Giant;
    case ItemStats::APVersusHumanoid:
        return Target::CreatureType::Humanoid;
    case ItemStats::APVersusMechanical:
        return Target::CreatureType::Mechanical;
    case ItemStats::APVersusUndead:
        return Target::CreatureType::Undead;
    default:
        check(false, "CharacterStats::get_type_for_stat reached end of switch");
        return Target::CreatureType::Beast;
    }
}
