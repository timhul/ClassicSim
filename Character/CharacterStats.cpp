#include "CharacterStats.h"

#include "Buff.h"
#include "Character.h"
#include "CharacterSpells.h"
#include "CombatRoll.h"
#include "Equipment.h"
#include "Mechanics.h"
#include "Race.h"
#include "Stats.h"
#include "Target.h"
#include "Utils/Check.h"
#include "Weapon.h"

CharacterStats::CharacterStats(Character* pchar, EquipmentDb* equipment_db) : pchar(pchar), equipment(new Equipment(equipment_db, pchar)) {
    this->aura_effects = new Stats();
    this->base_stats = new Stats();

    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::AXE, 0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::TWOHAND_AXE, 0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::DAGGER, 0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::POLEARM, 0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::BOW, 0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::CROSSBOW, 0);
    this->crit_bonuses_per_weapon_type.insert(WeaponTypes::GUN, 0);

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

    this->magic_school_damage_changes.insert(MagicSchool::Arcane, {});
    this->magic_school_damage_changes.insert(MagicSchool::Fire, {});
    this->magic_school_damage_changes.insert(MagicSchool::Frost, {});
    this->magic_school_damage_changes.insert(MagicSchool::Holy, {});
    this->magic_school_damage_changes.insert(MagicSchool::Nature, {});
    this->magic_school_damage_changes.insert(MagicSchool::Physical, {});
    this->magic_school_damage_changes.insert(MagicSchool::Shadow, {});

    this->magic_school_damage_modifiers.insert(MagicSchool::Arcane, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Fire, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Frost, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Holy, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Nature, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Physical, 1.0);
    this->magic_school_damage_modifiers.insert(MagicSchool::Shadow, 1.0);

    this->magic_damage_bonuses_per_monster_type.insert(Target::CreatureType::Beast, {});
    this->magic_damage_bonuses_per_monster_type.insert(Target::CreatureType::Demon, {});
    this->magic_damage_bonuses_per_monster_type.insert(Target::CreatureType::Dragonkin, {});
    this->magic_damage_bonuses_per_monster_type.insert(Target::CreatureType::Elemental, {});
    this->magic_damage_bonuses_per_monster_type.insert(Target::CreatureType::Giant, {});
    this->magic_damage_bonuses_per_monster_type.insert(Target::CreatureType::Humanoid, {});
    this->magic_damage_bonuses_per_monster_type.insert(Target::CreatureType::Mechanical, {});
    this->magic_damage_bonuses_per_monster_type.insert(Target::CreatureType::Undead, {});

    this->magic_damage_mods_per_monster_type.insert(Target::CreatureType::Beast, 1.0);
    this->magic_damage_mods_per_monster_type.insert(Target::CreatureType::Demon, 1.0);
    this->magic_damage_mods_per_monster_type.insert(Target::CreatureType::Dragonkin, 1.0);
    this->magic_damage_mods_per_monster_type.insert(Target::CreatureType::Elemental, 1.0);
    this->magic_damage_mods_per_monster_type.insert(Target::CreatureType::Giant, 1.0);
    this->magic_damage_mods_per_monster_type.insert(Target::CreatureType::Humanoid, 1.0);
    this->magic_damage_mods_per_monster_type.insert(Target::CreatureType::Mechanical, 1.0);
    this->magic_damage_mods_per_monster_type.insert(Target::CreatureType::Undead, 1.0);
}

CharacterStats::~CharacterStats() {
    delete aura_effects;
    delete base_stats;
    delete equipment;
}

Equipment* CharacterStats::get_equipment() const {
    return this->equipment;
}

unsigned CharacterStats::get_armor() const {
    return static_cast<unsigned>(armor_mod * (base_stats->get_armor() + equipment->get_stats()->get_armor()) + get_agility() * 2);
}

unsigned CharacterStats::get_block_value() const {
    return static_cast<unsigned>(base_stats->get_block_value() + equipment->get_stats()->get_block_value());
}

unsigned CharacterStats::get_strength() const {
    return static_cast<unsigned>(
        round(strength_mod * (base_stats->get_strength() + equipment->get_stats()->get_strength() + pchar->get_race()->get_base_strength())));
}

unsigned CharacterStats::get_agility() const {
    return static_cast<unsigned>(
        round(agility_mod * (base_stats->get_agility() + equipment->get_stats()->get_agility() + pchar->get_race()->get_base_agility())));
}

unsigned CharacterStats::get_stamina() const {
    return static_cast<unsigned>(
        round(stamina_mod * (base_stats->get_stamina() + equipment->get_stats()->get_stamina() + pchar->get_race()->get_base_stamina())));
}

unsigned CharacterStats::get_intellect() const {
    return static_cast<unsigned>(
        round(intellect_mod * (base_stats->get_intellect() + equipment->get_stats()->get_intellect() + pchar->get_race()->get_base_intellect())));
}

unsigned CharacterStats::get_spirit() const {
    return static_cast<unsigned>(
        round(spirit_mod * (base_stats->get_spirit() + equipment->get_stats()->get_spirit() + pchar->get_race()->get_base_spirit())));
}

unsigned CharacterStats::get_melee_hit_chance() const {
    return base_stats->get_melee_hit_chance() + equipment->get_stats()->get_melee_hit_chance();
}

unsigned CharacterStats::get_mh_crit_chance() const {
    const unsigned crit_from_agi = static_cast<unsigned>(
        round(static_cast<double>(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit() * 100));
    const unsigned equip_effect = aura_effects->get_melee_crit_chance() + equipment->get_stats()->get_melee_crit_chance();

    unsigned crit_from_wpn_type = 0;
    if (equipment->get_mainhand() != nullptr)
        crit_from_wpn_type = crit_bonuses_per_weapon_type[equipment->get_mainhand()->get_weapon_type()];

    const unsigned aura_crit = pchar->get_combat_roll()->mechanics->get_suppressed_aura_crit_chance(pchar->get_clvl(),
                                                                                                    equip_effect + crit_from_wpn_type);
    const unsigned crit_chance = crit_from_agi + aura_crit + base_stats->get_melee_crit_chance();

    return crit_penalty > crit_chance ? 0 : crit_chance - crit_penalty;
}

unsigned CharacterStats::get_oh_crit_chance() const {
    if (equipment->get_offhand() == nullptr)
        return 0;

    const unsigned crit_from_agi = static_cast<unsigned>(
        round(static_cast<double>(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit() * 100));
    const unsigned equip_effect = aura_effects->get_melee_crit_chance() + equipment->get_stats()->get_melee_crit_chance();

    unsigned crit_from_wpn_type = 0;
    if (equipment->get_mainhand() != nullptr)
        crit_from_wpn_type = crit_bonuses_per_weapon_type[equipment->get_offhand()->get_weapon_type()];

    const unsigned aura_crit = pchar->get_combat_roll()->mechanics->get_suppressed_aura_crit_chance(pchar->get_clvl(),
                                                                                                    equip_effect + crit_from_wpn_type);
    const unsigned crit_chance = crit_from_agi + aura_crit + base_stats->get_melee_crit_chance();

    return crit_penalty > crit_chance ? 0 : crit_chance - crit_penalty;
}

unsigned CharacterStats::get_ranged_hit_chance() const {
    return base_stats->get_ranged_hit_chance() + equipment->get_stats()->get_ranged_hit_chance();
}

unsigned CharacterStats::get_ranged_crit_chance() const {
    const unsigned equip_effect = base_stats->get_ranged_crit_chance() + equipment->get_stats()->get_ranged_crit_chance();
    const unsigned crit_from_agi = static_cast<unsigned>(
        round(static_cast<double>(get_agility()) / pchar->get_agi_needed_for_one_percent_phys_crit() * 100));

    unsigned crit_from_wpn_type = 0;
    if (equipment->get_mainhand() != nullptr)
        crit_from_wpn_type = crit_bonuses_per_weapon_type[equipment->get_mainhand()->get_weapon_type()];

    const unsigned aura_crit = pchar->get_combat_roll()->mechanics->get_suppressed_aura_crit_chance(pchar->get_clvl(),
                                                                                                    equip_effect + crit_from_wpn_type);
    const unsigned crit_chance = crit_from_agi + aura_crit;

    return crit_penalty > crit_chance ? 0 : crit_chance - crit_penalty;
}

void CharacterStats::increase_wpn_skill(const int weapon_type, const unsigned value) {
    switch (weapon_type) {
    case WeaponTypes::AXE:
        base_stats->increase_axe_skill(value);
        break;
    case WeaponTypes::DAGGER:
        base_stats->increase_dagger_skill(value);
        break;
    case WeaponTypes::FIST:
        base_stats->increase_fist_skill(value);
        break;
    case WeaponTypes::MACE:
        base_stats->increase_mace_skill(value);
        break;
    case WeaponTypes::SWORD:
        base_stats->increase_sword_skill(value);
        break;
    case WeaponTypes::TWOHAND_AXE:
        base_stats->increase_twohand_axe_skill(value);
        break;
    case WeaponTypes::TWOHAND_MACE:
        base_stats->increase_twohand_mace_skill(value);
        break;
    case WeaponTypes::TWOHAND_SWORD:
        base_stats->increase_twohand_sword_skill(value);
        break;
    case WeaponTypes::BOW:
        base_stats->increase_bow_skill(value);
        break;
    case WeaponTypes::CROSSBOW:
        base_stats->increase_crossbow_skill(value);
        break;
    case WeaponTypes::GUN:
        base_stats->increase_gun_skill(value);
        break;
    default:
        check(false, QString("CharacterStats::increase_wpn_skill has no effect for weapon type %1").arg(weapon_type).toStdString());
    }
}

void CharacterStats::decrease_wpn_skill(const int weapon_type, const unsigned value) {
    switch (weapon_type) {
    case WeaponTypes::AXE:
        base_stats->decrease_axe_skill(value);
        break;
    case WeaponTypes::DAGGER:
        base_stats->decrease_dagger_skill(value);
        break;
    case WeaponTypes::FIST:
        base_stats->decrease_fist_skill(value);
        break;
    case WeaponTypes::MACE:
        base_stats->decrease_mace_skill(value);
        break;
    case WeaponTypes::SWORD:
        base_stats->decrease_sword_skill(value);
        break;
    case WeaponTypes::TWOHAND_AXE:
        base_stats->decrease_twohand_axe_skill(value);
        break;
    case WeaponTypes::TWOHAND_MACE:
        base_stats->decrease_twohand_mace_skill(value);
        break;
    case WeaponTypes::TWOHAND_SWORD:
        base_stats->decrease_twohand_sword_skill(value);
        break;
    case WeaponTypes::BOW:
        base_stats->decrease_bow_skill(value);
        break;
    case WeaponTypes::CROSSBOW:
        base_stats->decrease_crossbow_skill(value);
        break;
    case WeaponTypes::GUN:
        base_stats->decrease_gun_skill(value);
        break;
    default:
        check(false, QString("CharacterStats::decrease_wpn_skill has no effect for weapon type %1").arg(weapon_type).toStdString());
    }
}

unsigned CharacterStats::get_mh_wpn_skill() const {
    return get_wpn_skill(equipment->get_mainhand());
}

unsigned CharacterStats::get_oh_wpn_skill() const {
    return get_wpn_skill(equipment->get_offhand());
}

unsigned CharacterStats::get_ranged_wpn_skill() const {
    return get_wpn_skill(equipment->get_ranged());
}

unsigned CharacterStats::get_wpn_skill(Weapon* weapon) const {
    const unsigned level_based_skill = pchar->get_clvl() * 5;
    if (weapon == nullptr)
        return level_based_skill;

    unsigned skill_bonus = 0;
    switch (weapon->get_weapon_type()) {
    case WeaponTypes::AXE:
        skill_bonus += pchar->get_race()->get_axe_bonus() + equipment->get_stats()->get_axe_skill() + base_stats->get_axe_skill();
        break;
    case WeaponTypes::TWOHAND_AXE:
        skill_bonus += pchar->get_race()->get_axe_bonus() + equipment->get_stats()->get_twohand_axe_skill() + base_stats->get_twohand_axe_skill();
        break;
    case WeaponTypes::DAGGER:
        skill_bonus += equipment->get_stats()->get_dagger_skill() + base_stats->get_dagger_skill();
        break;
    case WeaponTypes::FIST:
        skill_bonus += equipment->get_stats()->get_fist_skill() + base_stats->get_fist_skill();
        break;
    case WeaponTypes::SWORD:
        skill_bonus += pchar->get_race()->get_sword_bonus() + equipment->get_stats()->get_sword_skill() + base_stats->get_sword_skill();
        break;
    case WeaponTypes::TWOHAND_SWORD:
        skill_bonus += pchar->get_race()->get_sword_bonus() + equipment->get_stats()->get_twohand_sword_skill()
                       + base_stats->get_twohand_sword_skill();
        break;
    case WeaponTypes::MACE:
        skill_bonus += pchar->get_race()->get_mace_bonus() + equipment->get_stats()->get_mace_skill() + base_stats->get_mace_skill();
        break;
    case WeaponTypes::TWOHAND_MACE:
        skill_bonus += pchar->get_race()->get_mace_bonus() + equipment->get_stats()->get_twohand_mace_skill() + base_stats->get_twohand_mace_skill();
        break;
    case WeaponTypes::BOW:
        skill_bonus += pchar->get_race()->get_bow_bonus() + equipment->get_stats()->get_bow_skill() + base_stats->get_bow_skill();
        break;
    case WeaponTypes::CROSSBOW:
        skill_bonus += equipment->get_stats()->get_crossbow_skill() + base_stats->get_crossbow_skill();
        break;
    case WeaponTypes::GUN:
        skill_bonus += pchar->get_race()->get_gun_bonus() + equipment->get_stats()->get_gun_skill() + base_stats->get_gun_skill();
        break;
    }

    return level_based_skill + skill_bonus;
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
    case ItemStats::HealthPer5:
        return increase_hp5(value);
    case ItemStats::ManaSkillReduction:
        return increase_mana_skill_reduction(value);
    case ItemStats::SpellDamage:
        return increase_base_spell_damage(value);
    case ItemStats::SpellDamageArcane:
        return increase_spell_damage_vs_school(value, MagicSchool::Arcane);
    case ItemStats::SpellDamageFire:
        return increase_spell_damage_vs_school(value, MagicSchool::Fire);
    case ItemStats::SpellDamageFrost:
        return increase_spell_damage_vs_school(value, MagicSchool::Frost);
    case ItemStats::SpellDamageHoly:
        return increase_spell_damage_vs_school(value, MagicSchool::Holy);
    case ItemStats::SpellDamageNature:
        return increase_spell_damage_vs_school(value, MagicSchool::Nature);
    case ItemStats::SpellDamageShadow:
        return increase_spell_damage_vs_school(value, MagicSchool::Shadow);
    case ItemStats::SpellDamageVersusBeast:
    case ItemStats::SpellDamageVersusDemon:
    case ItemStats::SpellDamageVersusDragonkin:
    case ItemStats::SpellDamageVersusElemental:
    case ItemStats::SpellDamageVersusGiant:
    case ItemStats::SpellDamageVersusHumanoid:
    case ItemStats::SpellDamageVersusMechanical:
    case ItemStats::SpellDamageVersusUndead:
        return increase_spell_damage_vs_type(get_type_for_stat(stat_type), value);
    case ItemStats::SpellCrit:
        return increase_spell_crit(value);
    case ItemStats::SpellHit:
        return increase_spell_hit(value);
    case ItemStats::SpellPenetration:
        increase_spell_penetration(MagicSchool::Arcane, value);
        increase_spell_penetration(MagicSchool::Fire, value);
        increase_spell_penetration(MagicSchool::Frost, value);
        increase_spell_penetration(MagicSchool::Holy, value);
        increase_spell_penetration(MagicSchool::Nature, value);
        increase_spell_penetration(MagicSchool::Shadow, value);
        return;
    case ItemStats::BlockValue:
        return increase_block_value(value);
    case ItemStats::Armor:
        return increase_armor(value);
    case ItemStats::Defense:
    case ItemStats::DodgeChance:
    case ItemStats::ParryChance:
    case ItemStats::BlockChance:
    case ItemStats::ResistanceArcane:
    case ItemStats::ResistanceFire:
    case ItemStats::ResistanceFrost:
    case ItemStats::ResistanceHoly:
    case ItemStats::ResistanceNature:
    case ItemStats::ResistanceShadow:
    case ItemStats::ResistanceAll:
    case ItemStats::SkillAxe:
        return increase_wpn_skill(WeaponTypes::AXE, value);
    case ItemStats::SkillDagger:
        return increase_wpn_skill(WeaponTypes::DAGGER, value);
    case ItemStats::SkillFist:
        return increase_wpn_skill(WeaponTypes::FIST, value);
    case ItemStats::SkillMace:
        return increase_wpn_skill(WeaponTypes::MACE, value);
    case ItemStats::SkillSword:
        return increase_wpn_skill(WeaponTypes::SWORD, value);
    case ItemStats::Skill2hAxe:
        return increase_wpn_skill(WeaponTypes::TWOHAND_AXE, value);
    case ItemStats::Skill2hMace:
        return increase_wpn_skill(WeaponTypes::TWOHAND_MACE, value);
    case ItemStats::Skill2hSword:
        return increase_wpn_skill(WeaponTypes::TWOHAND_SWORD, value);
    case ItemStats::SkillBow:
        return increase_wpn_skill(WeaponTypes::BOW, value);
    case ItemStats::SkillCrossbow:
        return increase_wpn_skill(WeaponTypes::CROSSBOW, value);
    case ItemStats::SkillGun:
        return increase_wpn_skill(WeaponTypes::GUN, value);
    case ItemStats::HitChance:
        increase_ranged_hit(value);
        return increase_melee_hit(value);
    case ItemStats::CritChance:
        increase_ranged_crit(value);
        return increase_melee_aura_crit(value);
    case ItemStats::AttackSpeedPercent:
        pchar->increase_ranged_attack_speed(value);
        return pchar->increase_melee_attack_speed(value);
    case ItemStats::MeleeAttackSpeedPercent:
        return pchar->increase_melee_attack_speed(value);
    case ItemStats::RangedAttackSpeedPercent:
        return pchar->increase_ranged_attack_speed(value);
    case ItemStats::CastingSpeedPercent:
        return pchar->get_stats()->increase_casting_speed_mod(value);
    case ItemStats::AttackPower:
        increase_melee_ap(value);
        return increase_ranged_ap(value);
    case ItemStats::FeralAttackPower:
        return increase_feral_ap(value);
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
    case ItemStats::FlatWeaponDamage:
        increase_mh_weapon_damage_bonus(value);
        return increase_oh_weapon_damage_bonus(value);
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
    case ItemStats::HealthPer5:
        return decrease_hp5(value);
    case ItemStats::ManaSkillReduction:
        return decrease_mana_skill_reduction(value);
    case ItemStats::SpellDamage:
        return decrease_base_spell_damage(value);
    case ItemStats::SpellDamageArcane:
        return decrease_spell_damage_vs_school(value, MagicSchool::Arcane);
    case ItemStats::SpellDamageFire:
        return decrease_spell_damage_vs_school(value, MagicSchool::Fire);
    case ItemStats::SpellDamageFrost:
        return decrease_spell_damage_vs_school(value, MagicSchool::Frost);
    case ItemStats::SpellDamageHoly:
        return decrease_spell_damage_vs_school(value, MagicSchool::Holy);
    case ItemStats::SpellDamageNature:
        return decrease_spell_damage_vs_school(value, MagicSchool::Nature);
    case ItemStats::SpellDamageShadow:
        return decrease_spell_damage_vs_school(value, MagicSchool::Shadow);
    case ItemStats::SpellDamageVersusBeast:
    case ItemStats::SpellDamageVersusDemon:
    case ItemStats::SpellDamageVersusDragonkin:
    case ItemStats::SpellDamageVersusElemental:
    case ItemStats::SpellDamageVersusGiant:
    case ItemStats::SpellDamageVersusHumanoid:
    case ItemStats::SpellDamageVersusMechanical:
    case ItemStats::SpellDamageVersusUndead:
        return decrease_spell_damage_vs_type(get_type_for_stat(stat_type), value);
    case ItemStats::SpellCrit:
        return decrease_spell_crit(value);
    case ItemStats::SpellHit:
        return decrease_spell_hit(value);
    case ItemStats::SpellPenetration:
        decrease_spell_penetration(MagicSchool::Arcane, value);
        decrease_spell_penetration(MagicSchool::Fire, value);
        decrease_spell_penetration(MagicSchool::Frost, value);
        decrease_spell_penetration(MagicSchool::Holy, value);
        decrease_spell_penetration(MagicSchool::Nature, value);
        decrease_spell_penetration(MagicSchool::Shadow, value);
        return;
    case ItemStats::BlockValue:
        return decrease_block_value(value);
    case ItemStats::Armor:
        return decrease_armor(value);
    case ItemStats::BlockChance:
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
        return decrease_wpn_skill(WeaponTypes::AXE, value);
    case ItemStats::SkillDagger:
        return decrease_wpn_skill(WeaponTypes::DAGGER, value);
    case ItemStats::SkillFist:
        return decrease_wpn_skill(WeaponTypes::FIST, value);
    case ItemStats::SkillMace:
        return decrease_wpn_skill(WeaponTypes::MACE, value);
    case ItemStats::SkillSword:
        return decrease_wpn_skill(WeaponTypes::SWORD, value);
    case ItemStats::Skill2hAxe:
        return decrease_wpn_skill(WeaponTypes::TWOHAND_AXE, value);
    case ItemStats::Skill2hMace:
        return decrease_wpn_skill(WeaponTypes::TWOHAND_MACE, value);
    case ItemStats::Skill2hSword:
        return decrease_wpn_skill(WeaponTypes::TWOHAND_SWORD, value);
    case ItemStats::SkillBow:
        return decrease_wpn_skill(WeaponTypes::BOW, value);
    case ItemStats::SkillCrossbow:
        return decrease_wpn_skill(WeaponTypes::CROSSBOW, value);
    case ItemStats::SkillGun:
        return decrease_wpn_skill(WeaponTypes::GUN, value);
    case ItemStats::HitChance:
        decrease_ranged_hit(value);
        return decrease_melee_hit(value);
    case ItemStats::CritChance:
        decrease_ranged_crit(value);
        return decrease_melee_aura_crit(value);
    case ItemStats::AttackSpeedPercent:
        pchar->decrease_ranged_attack_speed(value);
        return pchar->decrease_melee_attack_speed(value);
    case ItemStats::MeleeAttackSpeedPercent:
        return pchar->decrease_melee_attack_speed(value);
    case ItemStats::RangedAttackSpeedPercent:
        return pchar->decrease_ranged_attack_speed(value);
    case ItemStats::CastingSpeedPercent:
        return pchar->get_stats()->decrease_casting_speed_mod(value);
    case ItemStats::AttackPower:
        decrease_melee_ap(value);
        return decrease_ranged_ap(value);
    case ItemStats::FeralAttackPower:
        return decrease_feral_ap(value);
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
    case ItemStats::FlatWeaponDamage:
        decrease_mh_weapon_damage_bonus(value);
        return decrease_oh_weapon_damage_bonus(value);
    }
}

void CharacterStats::increase_melee_attack_speed(const unsigned value) {
    add_multiplicative_effect(melee_attack_speed_buffs, static_cast<int>(value), melee_attack_speed_mod);
}

void CharacterStats::decrease_melee_attack_speed(const unsigned value) {
    remove_multiplicative_effect(melee_attack_speed_buffs, static_cast<int>(value), melee_attack_speed_mod);
}

void CharacterStats::increase_ranged_attack_speed(const unsigned value) {
    add_multiplicative_effect(ranged_attack_speed_buffs, static_cast<int>(value), ranged_attack_speed_mod);
}

void CharacterStats::decrease_ranged_attack_speed(const unsigned value) {
    remove_multiplicative_effect(ranged_attack_speed_buffs, static_cast<int>(value), ranged_attack_speed_mod);
}

double CharacterStats::get_casting_speed_mod() const {
    return casting_speed_mod;
}

void CharacterStats::increase_casting_speed_mod(const unsigned value) {
    add_multiplicative_effect(casting_speed_buffs, static_cast<int>(value), casting_speed_mod);
}

void CharacterStats::decrease_casting_speed_mod(const unsigned value) {
    remove_multiplicative_effect(casting_speed_buffs, static_cast<int>(value), casting_speed_mod);
}

bool CharacterStats::casting_time_suppressed() const {
    if (casting_time_suppression_buffs.empty())
        return false;

    casting_time_suppression_buffs.last()->use_charge();

    return true;
}

void CharacterStats::suppress_casting_time(Buff* buff) {
    for (const auto& stored_buff : casting_time_suppression_buffs)
        check((buff->get_instance_id() != stored_buff->get_instance_id()), "Tried to add the same cast time suppression buff multiple times");

    casting_time_suppression_buffs.append(buff);
}

void CharacterStats::return_casting_time(Buff* buff) {
    for (int i = 0; i < casting_time_suppression_buffs.size(); ++i) {
        if (buff->get_instance_id() == casting_time_suppression_buffs[i]->get_instance_id())
            return casting_time_suppression_buffs.removeAt(i);
    }

    check(false, QString("Failed to remove %1").arg(buff->name).toStdString());
}

unsigned CharacterStats::get_casting_speed_flat_reduction() const {
    return this->casting_speed_flat_reduction;
}

void CharacterStats::increase_casting_speed_flat_reduction(const unsigned value) {
    casting_speed_flat_reduction += value;
}

void CharacterStats::decrease_casting_speed_flat_reduction(const unsigned value) {
    check((casting_speed_flat_reduction >= value), "Underflow reduction of flat casting speed");
    casting_speed_flat_reduction -= value;
}

void CharacterStats::increase_block_value(const unsigned value) {
    base_stats->increase_block_value(value);
}

void CharacterStats::decrease_block_value(const unsigned value) {
    base_stats->decrease_block_value(value);
}

void CharacterStats::increase_strength(const unsigned value) {
    base_stats->increase_strength(value);
}

void CharacterStats::decrease_strength(const unsigned value) {
    base_stats->decrease_strength(value);
}

void CharacterStats::increase_armor(const unsigned value) {
    base_stats->increase_armor(value);
}

void CharacterStats::decrease_armor(const unsigned value) {
    base_stats->decrease_armor(value);
}

void CharacterStats::increase_agility(const unsigned value) {
    base_stats->increase_agility(value);
}

void CharacterStats::decrease_agility(const unsigned value) {
    base_stats->decrease_agility(value);
}

void CharacterStats::increase_stamina(const unsigned value) {
    base_stats->increase_stamina(value);
}

void CharacterStats::decrease_stamina(const unsigned value) {
    base_stats->decrease_stamina(value);
}

void CharacterStats::increase_intellect(const unsigned value) {
    base_stats->increase_intellect(value);
}

void CharacterStats::decrease_intellect(const unsigned value) {
    base_stats->decrease_intellect(value);
}

void CharacterStats::increase_spirit(const unsigned value) {
    base_stats->increase_spirit(value);
}

void CharacterStats::decrease_spirit(const unsigned value) {
    base_stats->decrease_spirit(value);
}

unsigned CharacterStats::get_melee_ap() const {
    unsigned stat_melee_ap = equipment->get_stats()->get_base_melee_ap() + base_stats->get_base_melee_ap();
    unsigned attributes_ap = get_strength() * pchar->get_melee_ap_per_strength() + get_agility() * pchar->get_melee_ap_per_agi();
    unsigned target_ap_eq = equipment->get_stats()->get_melee_ap_against_type(pchar->get_target()->get_creature_type());
    unsigned target_ap_base = base_stats->get_melee_ap_against_type(pchar->get_target()->get_creature_type());
    unsigned stat_feral_ap = 0;
    if (equipment->druid_is_in_feral_form()) {
        stat_feral_ap = equipment->get_stats()->get_base_feral_ap();
    }
    return static_cast<unsigned>(round(total_ap_mod * (stat_melee_ap + attributes_ap + target_ap_eq + target_ap_base + stat_feral_ap)));
}

void CharacterStats::increase_melee_ap(const unsigned value) {
    base_stats->increase_base_melee_ap(value);
}

void CharacterStats::decrease_melee_ap(const unsigned value) {
    base_stats->decrease_base_melee_ap(value);
}

void CharacterStats::increase_feral_ap(const unsigned value) {
    base_stats->increase_base_feral_ap(value);
}

void CharacterStats::decrease_feral_ap(const unsigned value) {
    base_stats->decrease_base_feral_ap(value);
}

unsigned CharacterStats::get_ranged_ap() const {
    unsigned stat_ranged_ap = equipment->get_stats()->get_base_ranged_ap() + base_stats->get_base_ranged_ap();
    unsigned attributes_ap = get_agility() * pchar->get_ranged_ap_per_agi();
    unsigned target_ap_eq = equipment->get_stats()->get_ranged_ap_against_type(pchar->get_target()->get_creature_type());
    unsigned target_ap_base = base_stats->get_ranged_ap_against_type(pchar->get_target()->get_creature_type());
    unsigned target_debuff_ap = pchar->get_target()->get_stats()->get_base_ranged_ap();
    return static_cast<unsigned>(round(total_ap_mod * (stat_ranged_ap + attributes_ap + target_ap_eq + target_ap_base + target_debuff_ap)));
}

void CharacterStats::increase_ranged_ap(const unsigned value) {
    base_stats->increase_base_ranged_ap(value);
}

void CharacterStats::decrease_ranged_ap(const unsigned value) {
    base_stats->decrease_base_ranged_ap(value);
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

void CharacterStats::increase_spell_damage_vs_type(const Target::CreatureType target_type, const unsigned value) {
    base_stats->increase_spell_damage_against_type(target_type, value);
}

void CharacterStats::decrease_spell_damage_vs_type(const Target::CreatureType target_type, const unsigned value) {
    base_stats->decrease_spell_damage_against_type(target_type, value);
}

void CharacterStats::increase_magic_damage_mod_vs_type(const Target::CreatureType target_type, const int value) {
    add_multiplicative_effect(magic_damage_bonuses_per_monster_type[target_type], value, magic_damage_mods_per_monster_type[target_type]);
}

void CharacterStats::decrease_magic_damage_mod_vs_type(const Target::CreatureType target_type, const int value) {
    remove_multiplicative_effect(magic_damage_bonuses_per_monster_type[target_type], value, magic_damage_mods_per_monster_type[target_type]);
}

double CharacterStats::get_total_physical_damage_mod() const {
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

double CharacterStats::get_total_threat_mod() const {
    return total_threat_mod;
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

void CharacterStats::increase_melee_hit(const unsigned value) {
    base_stats->increase_melee_hit(value);
    pchar->get_combat_roll()->update_melee_yellow_miss_chance();
    pchar->get_combat_roll()->update_melee_white_miss_chance();
}

void CharacterStats::decrease_melee_hit(const unsigned value) {
    base_stats->decrease_melee_hit(value);
    pchar->get_combat_roll()->update_melee_yellow_miss_chance();
    pchar->get_combat_roll()->update_melee_white_miss_chance();
}

void CharacterStats::increase_melee_aura_crit(const unsigned value) {
    aura_effects->increase_melee_aura_crit(value);
}

void CharacterStats::decrease_melee_aura_crit(const unsigned value) {
    aura_effects->decrease_melee_aura_crit(value);
}

void CharacterStats::increase_melee_base_crit(const unsigned value) {
    base_stats->increase_melee_aura_crit(value);
}

void CharacterStats::decrease_melee_base_crit(const unsigned value) {
    base_stats->decrease_melee_aura_crit(value);
}

void CharacterStats::increase_ranged_hit(const unsigned value) {
    base_stats->increase_ranged_hit(value);
    pchar->get_combat_roll()->update_ranged_miss_chance();
}

void CharacterStats::decrease_ranged_hit(const unsigned value) {
    base_stats->decrease_ranged_hit(value);
    pchar->get_combat_roll()->update_ranged_miss_chance();
}

void CharacterStats::increase_ranged_crit(const unsigned value) {
    base_stats->increase_ranged_crit(value);
}

void CharacterStats::decrease_ranged_crit(const unsigned value) {
    base_stats->decrease_ranged_crit(value);
}

void CharacterStats::increase_crit_for_weapon_type(const int weapon_type, const unsigned value) {
    crit_bonuses_per_weapon_type[weapon_type] += value;
}

void CharacterStats::decrease_crit_for_weapon_type(const int weapon_type, const unsigned value) {
    crit_bonuses_per_weapon_type[weapon_type] -= value;
}

void CharacterStats::increase_total_phys_dmg_for_weapon_type(const int weapon_type, const int value) {
    damage_bonuses_per_weapon_type[weapon_type] += value;
}

void CharacterStats::decrease_total_phys_dmg_for_weapon_type(const int weapon_type, const int value) {
    damage_bonuses_per_weapon_type[weapon_type] -= value;
}

unsigned CharacterStats::get_spell_hit_chance(const MagicSchool school) const {
    return base_stats->get_spell_hit_chance(school) + equipment->get_stats()->get_spell_hit_chance(school);
}

void CharacterStats::increase_spell_hit(const unsigned value) {
    base_stats->increase_spell_hit(value);
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Arcane, get_spell_hit_chance(MagicSchool::Arcane));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Fire, get_spell_hit_chance(MagicSchool::Fire));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Frost, get_spell_hit_chance(MagicSchool::Frost));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Holy, get_spell_hit_chance(MagicSchool::Holy));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Nature, get_spell_hit_chance(MagicSchool::Nature));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Shadow, get_spell_hit_chance(MagicSchool::Shadow));
}

void CharacterStats::decrease_spell_hit(const unsigned value) {
    base_stats->decrease_spell_hit(value);
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Arcane, get_spell_hit_chance(MagicSchool::Arcane));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Fire, get_spell_hit_chance(MagicSchool::Fire));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Frost, get_spell_hit_chance(MagicSchool::Frost));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Holy, get_spell_hit_chance(MagicSchool::Holy));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Nature, get_spell_hit_chance(MagicSchool::Nature));
    pchar->get_combat_roll()->update_spell_miss_chance(MagicSchool::Shadow, get_spell_hit_chance(MagicSchool::Shadow));
}

void CharacterStats::increase_spell_hit(const MagicSchool school, const unsigned value) {
    base_stats->increase_spell_hit(school, value);
    pchar->get_combat_roll()->update_spell_miss_chance(school, get_spell_hit_chance(school));
}

void CharacterStats::decrease_spell_hit(const MagicSchool school, const unsigned value) {
    base_stats->decrease_spell_hit(school, value);
    pchar->get_combat_roll()->update_spell_miss_chance(school, get_spell_hit_chance(school));
}

unsigned CharacterStats::get_spell_crit_chance(MagicSchool school) const {
    const unsigned equip_effect = base_stats->get_spell_crit_chance(school) + equipment->get_stats()->get_spell_crit_chance(school);
    const unsigned crit_from_target = pchar->get_target()->get_stats()->get_spell_crit_chance(school);
    const auto crit_from_int = static_cast<unsigned>(
        round(static_cast<double>(get_intellect()) / pchar->get_int_needed_for_one_percent_spell_crit() * 100));

    const unsigned crit_chance = crit_from_int + equip_effect + crit_from_target;

    return crit_penalty > crit_chance ? 0 : crit_chance - crit_penalty;
}

void CharacterStats::increase_spell_crit(const unsigned value) {
    base_stats->increase_spell_crit(value);
}

void CharacterStats::decrease_spell_crit(const unsigned value) {
    base_stats->decrease_spell_crit(value);
}

void CharacterStats::increase_spell_crit(const MagicSchool school, const unsigned value) {
    base_stats->increase_spell_crit(school, value);
}

void CharacterStats::decrease_spell_crit(const MagicSchool school, const unsigned value) {
    base_stats->decrease_spell_crit(school, value);
}

double CharacterStats::get_melee_ability_crit_dmg_mod() const {
    return melee_ability_crit_dmg_mod + crit_dmg_bonuses_per_monster_type[pchar->get_target()->get_creature_type()];
}

void CharacterStats::increase_melee_ability_crit_dmg_mod(const double value) {
    melee_ability_crit_dmg_mod += value;
}

void CharacterStats::decrease_melee_ability_crit_dmg_mod(const double value) {
    melee_ability_crit_dmg_mod -= value;
}

double CharacterStats::get_ranged_ability_crit_dmg_mod() const {
    return ranged_ability_crit_dmg_mod + crit_dmg_bonuses_per_monster_type[pchar->get_target()->get_creature_type()];
}

double CharacterStats::get_spell_crit_dmg_mod() const {
    return spell_crit_dmg_mod + crit_dmg_bonuses_per_monster_type[pchar->get_target()->get_creature_type()];
}

void CharacterStats::increase_spell_crit_dmg_mod(const double value) {
    spell_crit_dmg_mod += value;
}

void CharacterStats::decrease_spell_crit_dmg_mod(const double value) {
    spell_crit_dmg_mod -= value;
}

void CharacterStats::increase_total_phys_dmg_mod(const int increase) {
    add_multiplicative_effect(phys_dmg_buffs, increase, total_phys_dmg_mod);
}

void CharacterStats::decrease_total_phys_dmg_mod(const int decrease) {
    remove_multiplicative_effect(phys_dmg_buffs, decrease, total_phys_dmg_mod);
}

void CharacterStats::increase_total_threat_mod(const int increase) {
    add_multiplicative_effect(threat_buffs, increase, total_threat_mod);
}

void CharacterStats::decrease_total_threat_mod(const int decrease) {
    remove_multiplicative_effect(threat_buffs, decrease, total_threat_mod);
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

void CharacterStats::add_armor_mod(const int mod) {
    add_multiplicative_effect(armor_mod_changes, mod, armor_mod);
}

void CharacterStats::remove_armor_mod(const int mod) {
    remove_multiplicative_effect(armor_mod_changes, mod, armor_mod);
}

double CharacterStats::get_mh_wpn_speed() {
    return pchar->has_mainhand() ? equipment->get_mainhand()->get_base_weapon_speed() / melee_attack_speed_mod : 2.0 / melee_attack_speed_mod;
}

double CharacterStats::get_oh_wpn_speed() {
    return pchar->has_offhand() ? equipment->get_offhand()->get_base_weapon_speed() / melee_attack_speed_mod : 300;
}

double CharacterStats::get_ranged_wpn_speed() {
    return pchar->has_ranged() ? equipment->get_ranged()->get_base_weapon_speed() / ranged_attack_speed_mod : 300;
}

void CharacterStats::increase_dodge(const double value) {
    base_stats->increase_dodge(value);
}

void CharacterStats::decrease_dodge(const double value) {
    base_stats->decrease_dodge(value);
}

unsigned CharacterStats::get_mp5() const {
    return base_stats->get_mp5() + equipment->get_stats()->get_mp5();
}

void CharacterStats::increase_mp5(const unsigned value) {
    base_stats->increase_mp5(value);
}

void CharacterStats::decrease_mp5(const unsigned value) {
    base_stats->decrease_mp5(value);
}

unsigned CharacterStats::get_hp5() const {
    return base_stats->get_hp5() + equipment->get_stats()->get_hp5();
}

void CharacterStats::increase_hp5(const unsigned value) {
    base_stats->increase_hp5(value);
}

void CharacterStats::decrease_hp5(const unsigned value) {
    base_stats->decrease_hp5(value);
}

unsigned CharacterStats::get_spell_damage(const MagicSchool school, const ConsumeCharge consume_charge) const {
    const unsigned spell_damage_base = base_stats->get_spell_damage(school);
    const unsigned spell_damage_base_target = base_stats->get_spell_damage_against_type(pchar->get_target()->get_creature_type());
    const unsigned spell_damage_eq = equipment->get_stats()->get_spell_damage(school);
    const unsigned spell_damage_eq_target = equipment->get_stats()->get_spell_damage_against_type(pchar->get_target()->get_creature_type());
    const unsigned target_debuff_bonus = pchar->get_target()->get_spell_damage(school, consume_charge);

    return spell_damage_base + spell_damage_base_target + spell_damage_eq + spell_damage_eq_target + target_debuff_bonus;
}

void CharacterStats::increase_base_spell_damage(const unsigned value) {
    base_stats->increase_base_spell_damage(value);
}

void CharacterStats::decrease_base_spell_damage(const unsigned value) {
    base_stats->decrease_base_spell_damage(value);
}

void CharacterStats::increase_spell_damage_vs_school(const unsigned value, const MagicSchool school) {
    base_stats->increase_spell_damage_vs_school(value, school);
}

void CharacterStats::decrease_spell_damage_vs_school(const unsigned value, const MagicSchool school) {
    base_stats->decrease_spell_damage_vs_school(value, school);
}

unsigned CharacterStats::get_target_resistance(const MagicSchool school) const {
    const int delta = pchar->get_target()->get_resistance(school) - static_cast<int>(get_spell_penetration(school));

    return delta < 0 ? 0 : static_cast<unsigned>(delta);
}

unsigned CharacterStats::get_spell_penetration(const MagicSchool school) const {
    return equipment->get_stats()->get_spell_penetration(school) + base_stats->get_spell_penetration(school);
}

void CharacterStats::increase_spell_penetration(const MagicSchool school, const unsigned increase) {
    base_stats->increase_spell_penetration(school, increase);
    pchar->get_combat_roll()->update_target_resistance(school, get_target_resistance(school));
}

void CharacterStats::decrease_spell_penetration(const MagicSchool school, const unsigned decrease) {
    base_stats->decrease_spell_penetration(school, decrease);
    pchar->get_combat_roll()->update_target_resistance(school, get_target_resistance(school));
}

double CharacterStats::get_magic_school_damage_mod(const MagicSchool school, const ConsumeCharge consume_charge) const {
    return magic_school_damage_modifiers[school] * pchar->get_target()->get_magic_school_damage_mod(school, consume_charge)
           * magic_damage_mods_per_monster_type[pchar->get_target()->get_creature_type()];
}

void CharacterStats::increase_magic_school_damage_mod(const unsigned increase) {
    increase_magic_school_damage_mod(increase, MagicSchool::Arcane);
    increase_magic_school_damage_mod(increase, MagicSchool::Fire);
    increase_magic_school_damage_mod(increase, MagicSchool::Frost);
    increase_magic_school_damage_mod(increase, MagicSchool::Holy);
    increase_magic_school_damage_mod(increase, MagicSchool::Nature);
    increase_magic_school_damage_mod(increase, MagicSchool::Shadow);
}

void CharacterStats::decrease_magic_school_damage_mod(const unsigned decrease) {
    decrease_magic_school_damage_mod(decrease, MagicSchool::Arcane);
    decrease_magic_school_damage_mod(decrease, MagicSchool::Fire);
    decrease_magic_school_damage_mod(decrease, MagicSchool::Frost);
    decrease_magic_school_damage_mod(decrease, MagicSchool::Holy);
    decrease_magic_school_damage_mod(decrease, MagicSchool::Nature);
    decrease_magic_school_damage_mod(decrease, MagicSchool::Shadow);
}

void CharacterStats::increase_magic_school_damage_mod(const unsigned increase, const MagicSchool school) {
    add_multiplicative_effect(magic_school_damage_changes[school], static_cast<int>(increase), magic_school_damage_modifiers[school]);
}

void CharacterStats::decrease_magic_school_damage_mod(const unsigned decrease, const MagicSchool school) {
    remove_multiplicative_effect(magic_school_damage_changes[school], static_cast<int>(decrease), magic_school_damage_modifiers[school]);
}

unsigned CharacterStats::get_mh_weapon_damage_bonus() const {
    return mh_weapon_dmg_bonus + equipment->get_stats()->get_flat_weapon_damage();
}

void CharacterStats::increase_mh_weapon_damage_bonus(const unsigned value) {
    this->mh_weapon_dmg_bonus += value;
}

void CharacterStats::decrease_mh_weapon_damage_bonus(const unsigned value) {
    check((mh_weapon_dmg_bonus >= value), "Underflow decrease mh weapon damage bonus");
    this->mh_weapon_dmg_bonus -= value;
}

unsigned CharacterStats::get_oh_weapon_damage_bonus() const {
    return oh_weapon_dmg_bonus + equipment->get_stats()->get_flat_weapon_damage();
}

void CharacterStats::increase_oh_weapon_damage_bonus(const unsigned value) {
    this->oh_weapon_dmg_bonus += value;
}

void CharacterStats::decrease_oh_weapon_damage_bonus(const unsigned value) {
    check((oh_weapon_dmg_bonus >= value), "Underflow decrease oh weapon damage bonus");
    this->oh_weapon_dmg_bonus -= value;
}

unsigned CharacterStats::get_ranged_weapon_damage_bonus() const {
    return ranged_weapon_dmg_bonus;
}

void CharacterStats::increase_ranged_weapon_damage_bonus(const unsigned value) {
    this->ranged_weapon_dmg_bonus += value;
}

void CharacterStats::decrease_ranged_weapon_damage_bonus(const unsigned value) {
    check((ranged_weapon_dmg_bonus >= value), "Underflow decrease ranged weapon damage bonus");
    this->ranged_weapon_dmg_bonus -= value;
}

unsigned CharacterStats::get_flat_physical_damage_bonus() const {
    return physical_flat_dmg_bonus;
}

void CharacterStats::increase_flat_physical_damage_bonus(const unsigned value) {
    physical_flat_dmg_bonus += value;
}

void CharacterStats::decrease_flat_physical_damage_bonus(const unsigned value) {
    check((physical_flat_dmg_bonus >= value), "Underflow decrease flat physical damage bonus");
    physical_flat_dmg_bonus -= value;
}

unsigned CharacterStats::get_mana_skill_reduction() const {
    return mana_skill_reduction;
}

void CharacterStats::increase_mana_skill_reduction(const unsigned value) {
    mana_skill_reduction += value;
}

void CharacterStats::decrease_mana_skill_reduction(const unsigned value) {
    check((mana_skill_reduction >= value), "Underflow decrease mana skill reduction");
    mana_skill_reduction -= value;
}

void CharacterStats::increase_crit_penalty(const unsigned value) {
    crit_penalty += value;
}

void CharacterStats::add_multiplicative_effect(QVector<int>& effects, const int add_value, double& modifier) {
    effects.append(add_value);

    recalculate_multiplicative_effects(effects, modifier);
}

void CharacterStats::remove_multiplicative_effect(QVector<int>& effects, const int remove_value, double& modifier) {
    check(effects.removeOne(remove_value), "Failed to remove multiplicative effect");

    recalculate_multiplicative_effects(effects, modifier);
}

void CharacterStats::recalculate_multiplicative_effects(const QVector<int>& effects, double& modifier) {
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
    case ItemStats::SpellDamageVersusBeast:
        return Target::CreatureType::Beast;
    case ItemStats::APVersusDemon:
    case ItemStats::SpellDamageVersusDemon:
        return Target::CreatureType::Demon;
    case ItemStats::APVersusDragonkin:
    case ItemStats::SpellDamageVersusDragonkin:
        return Target::CreatureType::Dragonkin;
    case ItemStats::APVersusElemental:
    case ItemStats::SpellDamageVersusElemental:
        return Target::CreatureType::Elemental;
    case ItemStats::APVersusGiant:
    case ItemStats::SpellDamageVersusGiant:
        return Target::CreatureType::Giant;
    case ItemStats::APVersusHumanoid:
    case ItemStats::SpellDamageVersusHumanoid:
        return Target::CreatureType::Humanoid;
    case ItemStats::APVersusMechanical:
    case ItemStats::SpellDamageVersusMechanical:
        return Target::CreatureType::Mechanical;
    case ItemStats::APVersusUndead:
    case ItemStats::SpellDamageVersusUndead:
        return Target::CreatureType::Undead;
    default:
        check(false, "CharacterStats::get_type_for_stat reached end of switch");
        return Target::CreatureType::Beast;
    }
}
