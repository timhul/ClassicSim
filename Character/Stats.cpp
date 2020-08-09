#include "Stats.h"

#include <cmath>

#include "Utils/Check.h"

Stats::Stats() {
    this->melee_ap_against_creature[Target::CreatureType::Beast] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Demon] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Dragonkin] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Elemental] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Giant] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Humanoid] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Mechanical] = 0;
    this->melee_ap_against_creature[Target::CreatureType::Undead] = 0;

    this->ranged_ap_against_creature[Target::CreatureType::Beast] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Demon] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Dragonkin] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Elemental] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Giant] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Humanoid] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Mechanical] = 0;
    this->ranged_ap_against_creature[Target::CreatureType::Undead] = 0;

    this->spell_damage_against_creature[Target::CreatureType::Beast] = 0;
    this->spell_damage_against_creature[Target::CreatureType::Demon] = 0;
    this->spell_damage_against_creature[Target::CreatureType::Dragonkin] = 0;
    this->spell_damage_against_creature[Target::CreatureType::Elemental] = 0;
    this->spell_damage_against_creature[Target::CreatureType::Giant] = 0;
    this->spell_damage_against_creature[Target::CreatureType::Humanoid] = 0;
    this->spell_damage_against_creature[Target::CreatureType::Mechanical] = 0;
    this->spell_damage_against_creature[Target::CreatureType::Undead] = 0;

    this->magic_school_damage_bonus[MagicSchool::Arcane] = 0;
    this->magic_school_damage_bonus[MagicSchool::Fire] = 0;
    this->magic_school_damage_bonus[MagicSchool::Frost] = 0;
    this->magic_school_damage_bonus[MagicSchool::Holy] = 0;
    this->magic_school_damage_bonus[MagicSchool::Nature] = 0;
    this->magic_school_damage_bonus[MagicSchool::Physical] = 0;
    this->magic_school_damage_bonus[MagicSchool::Shadow] = 0;
}

void Stats::add(const QString& key, const QString& value) {
    if (key == "STRENGTH") {
        this->increase_strength(value.toUInt());
        this->base_tooltip.append(QString("+%1 Strength").arg(value));
    } else if (key == "AGILITY") {
        this->increase_agility(value.toUInt());
        this->base_tooltip.append(QString("+%1 Agility").arg(value));
    } else if (key == "STAMINA") {
        this->increase_stamina(value.toUInt());
        this->base_tooltip.append(QString("+%1 Stamina").arg(value));
    } else if (key == "INTELLECT") {
        this->increase_intellect(value.toUInt());
        this->base_tooltip.append(QString("+%1 Intellect").arg(value));
    } else if (key == "SPIRIT") {
        this->increase_spirit(value.toUInt());
        this->base_tooltip.append(QString("+%1 Spirit").arg(value));
    } else if (key == "CRIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        const unsigned attack_table_value = display_value * 100;
        this->increase_melee_aura_crit(attack_table_value);
        this->increase_ranged_crit(attack_table_value);
        this->equip_effects_tooltip.append(QString("Equip: Improves your chance to get a critical strike by %1%.").arg(display_value));
    } else if (key == "HIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        const unsigned attack_table_value = display_value * 100;
        this->increase_melee_hit(attack_table_value);
        this->increase_ranged_hit(attack_table_value);
        this->equip_effects_tooltip.append(QString("Equip: Improves your chance to hit by %1%.").arg(display_value));
    } else if (key == "ATTACK_POWER") {
        this->increase_base_melee_ap(value.toUInt());
        this->increase_base_ranged_ap(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: +%1 Attack Power.").arg(value));
    } else if (key == "FERAL_ATTACK_POWER") {
        this->increase_base_feral_ap(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: +%1 Attack Power in Cat, Bear, and Dire Bear forms only.").arg(value));
    } else if (key == "RANGED_ATTACK_POWER") {
        this->increase_base_ranged_ap(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: +%1 Ranged Attack Power.").arg(value));
    } else if (key == "ATTACK_POWER_BEAST") {
        this->increase_melee_ap_against_type(Target::CreatureType::Beast, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: +%1 Attack Power when fighting Beasts.").arg(value));
    } else if (key == "ATTACK_POWER_DEMON") {
        this->increase_melee_ap_against_type(Target::CreatureType::Demon, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: +%1 Attack Power when fighting Demons.").arg(value));
    } else if (key == "ATTACK_POWER_DRAGONKIN") {
        this->increase_melee_ap_against_type(Target::CreatureType::Dragonkin, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: +%1 Attack Power when fighting Dragonkin.").arg(value));
    } else if (key == "ATTACK_POWER_UNDEAD") {
        this->increase_melee_ap_against_type(Target::CreatureType::Undead, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: +%1 Attack Power when fighting Undead.").arg(value));
    } else if (key == "WEAPON_DAMAGE") {
        this->increase_flat_weapon_damage(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: +%1 Weapon Damage.").arg(value));
    } else if (key == "AXE_SKILL") {
        this->increase_axe_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Axes +%1.").arg(value));
    } else if (key == "DAGGER_SKILL") {
        this->increase_dagger_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Daggers +%1.").arg(value));
    } else if (key == "MACE_SKILL") {
        this->increase_mace_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Swords +%1.").arg(value));
    } else if (key == "SWORD_SKILL") {
        this->increase_sword_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Sword +%1.").arg(value));
    } else if (key == "TWOHAND_AXE_SKILL") {
        this->increase_twohand_axe_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Two-handed Axes +%1.").arg(value));
    } else if (key == "TWOHAND_MACE_SKILL") {
        this->increase_twohand_mace_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Two-handed Maces +%1.").arg(value));
    } else if (key == "TWOHAND_SWORD_SKILL") {
        this->increase_twohand_sword_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Two-handed Swords +%1.").arg(value));
    } else if (key == "BOW_SKILL") {
        this->increase_bow_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Bows +%1.").arg(value));
    } else if (key == "CROSSBOW_SKILL") {
        this->increase_crossbow_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Crossbows +%1.").arg(value));
    } else if (key == "GUN_SKILL") {
        this->increase_gun_skill(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Guns +%1.").arg(value));
    } else if (key == "MANA_PER_5") {
        this->increase_mp5(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Restores %1 mana per 5 sec.").arg(value));
    } else if (key == "HEALTH_PER_5") {
        this->increase_hp5(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Restores %1 health per 5 sec.").arg(value));
    } else if (key == "SPELL_DAMAGE") {
        this->increase_base_spell_damage(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increases damage and healing done by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_ARCANE") {
        this->increase_spell_damage_vs_school(value.toUInt(), MagicSchool::Arcane);
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done by Arcane spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_FIRE") {
        this->increase_spell_damage_vs_school(value.toUInt(), MagicSchool::Fire);
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done by Fire spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_FROST") {
        this->increase_spell_damage_vs_school(value.toUInt(), MagicSchool::Frost);
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done by Frost spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_HOLY") {
        this->increase_spell_damage_vs_school(value.toUInt(), MagicSchool::Holy);
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done by Holy spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_NATURE") {
        this->increase_spell_damage_vs_school(value.toUInt(), MagicSchool::Nature);
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done by Nature spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_SHADOW") {
        this->increase_spell_damage_vs_school(value.toUInt(), MagicSchool::Shadow);
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done by Shadow spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_BEAST") {
        this->increase_spell_damage_against_type(Target::CreatureType::Beast, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done to Beasts by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_DEMON") {
        this->increase_spell_damage_against_type(Target::CreatureType::Demon, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done to Demons by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_DRAGONKIN") {
        this->increase_spell_damage_against_type(Target::CreatureType::Dragonkin, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done to Dragonkin by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_ELEMENTAL") {
        this->increase_spell_damage_against_type(Target::CreatureType::Elemental, value.toUInt());
        this->equip_effects_tooltip.append(
            QString("Equip: Increases damage done to Elementals by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_GIANT") {
        this->increase_spell_damage_against_type(Target::CreatureType::Giant, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done to Giants by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_HUMANOID") {
        this->increase_spell_damage_against_type(Target::CreatureType::Humanoid, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done to Humanoids by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_MECHANICAL") {
        this->increase_spell_damage_against_type(Target::CreatureType::Mechanical, value.toUInt());
        this->equip_effects_tooltip.append(
            QString("Equip: Increases damage done to Mechanicals by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_DAMAGE_UNDEAD") {
        this->increase_spell_damage_against_type(Target::CreatureType::Undead, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increases damage done to Undead by magical spells and effects by up to %1.").arg(value));
    } else if (key == "SPELL_CRIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        const unsigned attack_table_value = display_value * 100;
        this->increase_spell_crit(attack_table_value);
        this->equip_effects_tooltip.append(QString("Equip: Improves your chance to get a critical strike with spells by %1%.").arg(display_value));
    } else if (key == "SPELL_HIT_CHANCE") {
        const unsigned display_value = static_cast<unsigned>(round(value.toDouble() * 100));
        const unsigned attack_table_value = display_value * 100;
        this->increase_spell_hit(attack_table_value);
        this->equip_effects_tooltip.append(QString("Equip: Improves your chance to hit with spells by %1%.").arg(display_value));
    } else if (key == "SPELL_PENETRATION") {
        this->increase_spell_penetration(MagicSchool::Arcane, value.toUInt());
        this->increase_spell_penetration(MagicSchool::Fire, value.toUInt());
        this->increase_spell_penetration(MagicSchool::Frost, value.toUInt());
        this->increase_spell_penetration(MagicSchool::Holy, value.toUInt());
        this->increase_spell_penetration(MagicSchool::Nature, value.toUInt());
        this->increase_spell_penetration(MagicSchool::Shadow, value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Decreases the magical resistances of your spell targets by %1.").arg(value));
    } else if (key == "ARMOR") {
        this->increase_armor(value.toInt());
        this->base_tooltip.append(QString("%1 Armor").arg(value));
    } else if (key == "DEFENSE") {
        this->increase_defense(value.toInt());
        this->equip_effects_tooltip.append(QString("Equip: Increased Defense +%1.").arg(value));
    } else if (key == "BLOCK_VALUE") {
      this->increase_block_value(value.toInt());
      this->equip_effects_tooltip.append(QString("Equip: Increased Block Value +%1.").arg(value));
    } else if (key == "DODGE_CHANCE") {
        this->increase_dodge(value.toDouble());
        this->equip_effects_tooltip.append(QString("Equip: Increases your chance to dodge an attack by %1%.").arg(value));
    } else if (key == "PARRY_CHANCE") {
        this->increase_parry(value.toDouble());
        this->equip_effects_tooltip.append(QString("Equip: Increases your chance to parry an attack by %1%.").arg(value));
    } else if (key == "ALL_RESISTANCE") {
        this->increase_arcane_resistance(value.toInt());
        this->increase_fire_resistance(value.toInt());
        this->increase_frost_resistance(value.toInt());
        this->increase_holy_resistance(value.toInt());
        this->increase_nature_resistance(value.toInt());
        this->increase_shadow_resistance(value.toInt());
        this->equip_effects_tooltip.append(QString("+%1 All Resistances.").arg(value));
    } else if (key == "ARCANE_RESISTANCE") {
        this->increase_arcane_resistance(value.toInt());
        this->base_tooltip.append(QString("+%1 Arcane Resistance").arg(value));
    } else if (key == "FIRE_RESISTANCE") {
        this->increase_fire_resistance(value.toInt());
        this->base_tooltip.append(QString("+%1 Fire Resistance").arg(value));
    } else if (key == "FROST_RESISTANCE") {
        this->increase_frost_resistance(value.toInt());
        this->base_tooltip.append(QString("+%1 Frost Resistance").arg(value));
    } else if (key == "HOLY_RESISTANCE") {
        this->increase_holy_resistance(value.toInt());
        this->base_tooltip.append(QString("+%1 Holy Resistance").arg(value));
    } else if (key == "NATURE_RESISTANCE") {
        this->increase_nature_resistance(value.toInt());
        this->base_tooltip.append(QString("+%1 Nature Resistance").arg(value));
    } else if (key == "SHADOW_RESISTANCE") {
        this->increase_shadow_resistance(value.toInt());
        this->base_tooltip.append(QString("+%1 Shadow Resistance").arg(value));
    } else if (key == "RANGED_ATTACK_SPEED") {
        this->increase_ranged_attack_speed(value.toUInt());
        this->equip_effects_tooltip.append(QString("Equip: Increases ranged attack speed by %1%.").arg(value));
    }
}

void Stats::add(const Stats* rhs) {
    increase_strength(rhs->get_strength());
    increase_agility(rhs->get_agility());
    increase_stamina(rhs->get_stamina());
    increase_intellect(rhs->get_intellect());
    increase_spirit(rhs->get_spirit());

    increase_block_value(rhs->get_block_value());
    increase_armor(rhs->get_armor());

    increase_axe_skill(rhs->get_axe_skill());
    increase_dagger_skill(rhs->get_dagger_skill());
    increase_fist_skill(rhs->get_fist_skill());
    increase_mace_skill(rhs->get_mace_skill());
    increase_sword_skill(rhs->get_sword_skill());
    increase_twohand_axe_skill(rhs->get_twohand_axe_skill());
    increase_twohand_mace_skill(rhs->get_twohand_mace_skill());
    increase_twohand_sword_skill(rhs->get_twohand_sword_skill());
    increase_bow_skill(rhs->get_bow_skill());
    increase_crossbow_skill(rhs->get_crossbow_skill());
    increase_gun_skill(rhs->get_gun_skill());

    increase_melee_hit(rhs->get_melee_hit_chance());
    increase_melee_aura_crit(rhs->get_melee_crit_chance());
    increase_ranged_hit(rhs->get_ranged_hit_chance());
    increase_ranged_crit(rhs->get_ranged_crit_chance());
    increase_ranged_attack_speed(rhs->get_ranged_attack_speed_percent());

    increase_spell_hit(MagicSchool::Arcane, rhs->get_spell_hit_chance(MagicSchool::Arcane));
    increase_spell_hit(MagicSchool::Fire, rhs->get_spell_hit_chance(MagicSchool::Fire));
    increase_spell_hit(MagicSchool::Frost, rhs->get_spell_hit_chance(MagicSchool::Frost));
    increase_spell_hit(MagicSchool::Holy, rhs->get_spell_hit_chance(MagicSchool::Holy));
    increase_spell_hit(MagicSchool::Nature, rhs->get_spell_hit_chance(MagicSchool::Nature));
    increase_spell_hit(MagicSchool::Shadow, rhs->get_spell_hit_chance(MagicSchool::Shadow));

    increase_spell_crit(MagicSchool::Arcane, rhs->get_spell_crit_chance(MagicSchool::Arcane));
    increase_spell_crit(MagicSchool::Fire, rhs->get_spell_crit_chance(MagicSchool::Fire));
    increase_spell_crit(MagicSchool::Frost, rhs->get_spell_crit_chance(MagicSchool::Frost));
    increase_spell_crit(MagicSchool::Holy, rhs->get_spell_crit_chance(MagicSchool::Holy));
    increase_spell_crit(MagicSchool::Nature, rhs->get_spell_crit_chance(MagicSchool::Nature));
    increase_spell_crit(MagicSchool::Shadow, rhs->get_spell_crit_chance(MagicSchool::Shadow));

    increase_spell_penetration(MagicSchool::Arcane, rhs->get_spell_penetration(MagicSchool::Arcane));
    increase_spell_penetration(MagicSchool::Fire, rhs->get_spell_penetration(MagicSchool::Fire));
    increase_spell_penetration(MagicSchool::Frost, rhs->get_spell_penetration(MagicSchool::Frost));
    increase_spell_penetration(MagicSchool::Holy, rhs->get_spell_penetration(MagicSchool::Holy));
    increase_spell_penetration(MagicSchool::Nature, rhs->get_spell_penetration(MagicSchool::Nature));
    increase_spell_penetration(MagicSchool::Shadow, rhs->get_spell_penetration(MagicSchool::Shadow));

    increase_base_melee_ap(rhs->get_base_melee_ap());
    increase_base_feral_ap(rhs->get_base_feral_ap());
    increase_base_ranged_ap(rhs->get_base_ranged_ap());

    increase_melee_ap_against_type(Target::CreatureType::Beast, rhs->get_melee_ap_against_type(Target::CreatureType::Beast));
    increase_melee_ap_against_type(Target::CreatureType::Demon, rhs->get_melee_ap_against_type(Target::CreatureType::Demon));
    increase_melee_ap_against_type(Target::CreatureType::Dragonkin, rhs->get_melee_ap_against_type(Target::CreatureType::Dragonkin));
    increase_melee_ap_against_type(Target::CreatureType::Elemental, rhs->get_melee_ap_against_type(Target::CreatureType::Elemental));
    increase_melee_ap_against_type(Target::CreatureType::Giant, rhs->get_melee_ap_against_type(Target::CreatureType::Giant));
    increase_melee_ap_against_type(Target::CreatureType::Humanoid, rhs->get_melee_ap_against_type(Target::CreatureType::Humanoid));
    increase_melee_ap_against_type(Target::CreatureType::Mechanical, rhs->get_melee_ap_against_type(Target::CreatureType::Mechanical));
    increase_melee_ap_against_type(Target::CreatureType::Undead, rhs->get_melee_ap_against_type(Target::CreatureType::Undead));

    increase_ranged_ap_against_type(Target::CreatureType::Beast, rhs->get_ranged_ap_against_type(Target::CreatureType::Beast));
    increase_ranged_ap_against_type(Target::CreatureType::Demon, rhs->get_ranged_ap_against_type(Target::CreatureType::Demon));
    increase_ranged_ap_against_type(Target::CreatureType::Dragonkin, rhs->get_ranged_ap_against_type(Target::CreatureType::Dragonkin));
    increase_ranged_ap_against_type(Target::CreatureType::Elemental, rhs->get_ranged_ap_against_type(Target::CreatureType::Elemental));
    increase_ranged_ap_against_type(Target::CreatureType::Giant, rhs->get_ranged_ap_against_type(Target::CreatureType::Giant));
    increase_ranged_ap_against_type(Target::CreatureType::Humanoid, rhs->get_ranged_ap_against_type(Target::CreatureType::Humanoid));
    increase_ranged_ap_against_type(Target::CreatureType::Mechanical, rhs->get_ranged_ap_against_type(Target::CreatureType::Mechanical));
    increase_ranged_ap_against_type(Target::CreatureType::Undead, rhs->get_ranged_ap_against_type(Target::CreatureType::Undead));

    increase_spell_damage_against_type(Target::CreatureType::Beast, rhs->get_spell_damage_against_type(Target::CreatureType::Beast));
    increase_spell_damage_against_type(Target::CreatureType::Demon, rhs->get_spell_damage_against_type(Target::CreatureType::Demon));
    increase_spell_damage_against_type(Target::CreatureType::Dragonkin, rhs->get_spell_damage_against_type(Target::CreatureType::Dragonkin));
    increase_spell_damage_against_type(Target::CreatureType::Elemental, rhs->get_spell_damage_against_type(Target::CreatureType::Elemental));
    increase_spell_damage_against_type(Target::CreatureType::Giant, rhs->get_spell_damage_against_type(Target::CreatureType::Giant));
    increase_spell_damage_against_type(Target::CreatureType::Humanoid, rhs->get_spell_damage_against_type(Target::CreatureType::Humanoid));
    increase_spell_damage_against_type(Target::CreatureType::Mechanical, rhs->get_spell_damage_against_type(Target::CreatureType::Mechanical));
    increase_spell_damage_against_type(Target::CreatureType::Undead, rhs->get_spell_damage_against_type(Target::CreatureType::Undead));

    increase_flat_weapon_damage(rhs->get_flat_weapon_damage());

    increase_mp5(rhs->get_mp5());
    increase_hp5(rhs->get_hp5());
    increase_base_spell_damage(rhs->get_base_spell_damage());

    increase_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Arcane], MagicSchool::Arcane);
    increase_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Fire], MagicSchool::Fire);
    increase_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Frost], MagicSchool::Frost);
    increase_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Holy], MagicSchool::Holy);
    increase_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Nature], MagicSchool::Nature);
    increase_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Physical], MagicSchool::Physical);
    increase_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Shadow], MagicSchool::Shadow);
}

void Stats::remove(const Stats* rhs) {
    decrease_strength(rhs->get_strength());
    decrease_agility(rhs->get_agility());
    decrease_stamina(rhs->get_stamina());
    decrease_intellect(rhs->get_intellect());
    decrease_spirit(rhs->get_spirit());

    decrease_block_value(rhs->get_block_value());
    decrease_armor(rhs->get_armor());

    decrease_axe_skill(rhs->get_axe_skill());
    decrease_dagger_skill(rhs->get_dagger_skill());
    decrease_fist_skill(rhs->get_fist_skill());
    decrease_mace_skill(rhs->get_mace_skill());
    decrease_sword_skill(rhs->get_sword_skill());
    decrease_twohand_axe_skill(rhs->get_twohand_axe_skill());
    decrease_twohand_mace_skill(rhs->get_twohand_mace_skill());
    decrease_twohand_sword_skill(rhs->get_twohand_sword_skill());
    decrease_bow_skill(rhs->get_bow_skill());
    decrease_crossbow_skill(rhs->get_crossbow_skill());
    decrease_gun_skill(rhs->get_gun_skill());

    decrease_melee_hit(rhs->get_melee_hit_chance());
    decrease_melee_aura_crit(rhs->get_melee_crit_chance());
    decrease_ranged_hit(rhs->get_ranged_hit_chance());
    decrease_ranged_crit(rhs->get_ranged_crit_chance());
    decrease_ranged_attack_speed(rhs->get_ranged_attack_speed_percent());

    decrease_spell_hit(MagicSchool::Arcane, rhs->get_spell_hit_chance(MagicSchool::Arcane));
    decrease_spell_hit(MagicSchool::Fire, rhs->get_spell_hit_chance(MagicSchool::Fire));
    decrease_spell_hit(MagicSchool::Frost, rhs->get_spell_hit_chance(MagicSchool::Frost));
    decrease_spell_hit(MagicSchool::Holy, rhs->get_spell_hit_chance(MagicSchool::Holy));
    decrease_spell_hit(MagicSchool::Nature, rhs->get_spell_hit_chance(MagicSchool::Nature));
    decrease_spell_hit(MagicSchool::Shadow, rhs->get_spell_hit_chance(MagicSchool::Shadow));

    decrease_spell_crit(MagicSchool::Arcane, rhs->get_spell_crit_chance(MagicSchool::Arcane));
    decrease_spell_crit(MagicSchool::Fire, rhs->get_spell_crit_chance(MagicSchool::Fire));
    decrease_spell_crit(MagicSchool::Frost, rhs->get_spell_crit_chance(MagicSchool::Frost));
    decrease_spell_crit(MagicSchool::Holy, rhs->get_spell_crit_chance(MagicSchool::Holy));
    decrease_spell_crit(MagicSchool::Nature, rhs->get_spell_crit_chance(MagicSchool::Nature));
    decrease_spell_crit(MagicSchool::Shadow, rhs->get_spell_crit_chance(MagicSchool::Shadow));

    decrease_spell_penetration(MagicSchool::Arcane, rhs->get_spell_penetration(MagicSchool::Arcane));
    decrease_spell_penetration(MagicSchool::Fire, rhs->get_spell_penetration(MagicSchool::Fire));
    decrease_spell_penetration(MagicSchool::Frost, rhs->get_spell_penetration(MagicSchool::Frost));
    decrease_spell_penetration(MagicSchool::Holy, rhs->get_spell_penetration(MagicSchool::Holy));
    decrease_spell_penetration(MagicSchool::Nature, rhs->get_spell_penetration(MagicSchool::Nature));
    decrease_spell_penetration(MagicSchool::Shadow, rhs->get_spell_penetration(MagicSchool::Shadow));

    decrease_base_melee_ap(rhs->get_base_melee_ap());
    decrease_base_feral_ap(rhs->get_base_feral_ap());
    decrease_base_ranged_ap(rhs->get_base_ranged_ap());

    decrease_melee_ap_against_type(Target::CreatureType::Beast, rhs->get_melee_ap_against_type(Target::CreatureType::Beast));
    decrease_melee_ap_against_type(Target::CreatureType::Demon, rhs->get_melee_ap_against_type(Target::CreatureType::Demon));
    decrease_melee_ap_against_type(Target::CreatureType::Dragonkin, rhs->get_melee_ap_against_type(Target::CreatureType::Dragonkin));
    decrease_melee_ap_against_type(Target::CreatureType::Elemental, rhs->get_melee_ap_against_type(Target::CreatureType::Elemental));
    decrease_melee_ap_against_type(Target::CreatureType::Giant, rhs->get_melee_ap_against_type(Target::CreatureType::Giant));
    decrease_melee_ap_against_type(Target::CreatureType::Humanoid, rhs->get_melee_ap_against_type(Target::CreatureType::Humanoid));
    decrease_melee_ap_against_type(Target::CreatureType::Mechanical, rhs->get_melee_ap_against_type(Target::CreatureType::Mechanical));
    decrease_melee_ap_against_type(Target::CreatureType::Undead, rhs->get_melee_ap_against_type(Target::CreatureType::Undead));

    decrease_ranged_ap_against_type(Target::CreatureType::Beast, rhs->get_ranged_ap_against_type(Target::CreatureType::Beast));
    decrease_ranged_ap_against_type(Target::CreatureType::Demon, rhs->get_ranged_ap_against_type(Target::CreatureType::Demon));
    decrease_ranged_ap_against_type(Target::CreatureType::Dragonkin, rhs->get_ranged_ap_against_type(Target::CreatureType::Dragonkin));
    decrease_ranged_ap_against_type(Target::CreatureType::Elemental, rhs->get_ranged_ap_against_type(Target::CreatureType::Elemental));
    decrease_ranged_ap_against_type(Target::CreatureType::Giant, rhs->get_ranged_ap_against_type(Target::CreatureType::Giant));
    decrease_ranged_ap_against_type(Target::CreatureType::Humanoid, rhs->get_ranged_ap_against_type(Target::CreatureType::Humanoid));
    decrease_ranged_ap_against_type(Target::CreatureType::Mechanical, rhs->get_ranged_ap_against_type(Target::CreatureType::Mechanical));
    decrease_ranged_ap_against_type(Target::CreatureType::Undead, rhs->get_ranged_ap_against_type(Target::CreatureType::Undead));

    decrease_spell_damage_against_type(Target::CreatureType::Beast, rhs->get_spell_damage_against_type(Target::CreatureType::Beast));
    decrease_spell_damage_against_type(Target::CreatureType::Demon, rhs->get_spell_damage_against_type(Target::CreatureType::Demon));
    decrease_spell_damage_against_type(Target::CreatureType::Dragonkin, rhs->get_spell_damage_against_type(Target::CreatureType::Dragonkin));
    decrease_spell_damage_against_type(Target::CreatureType::Elemental, rhs->get_spell_damage_against_type(Target::CreatureType::Elemental));
    decrease_spell_damage_against_type(Target::CreatureType::Giant, rhs->get_spell_damage_against_type(Target::CreatureType::Giant));
    decrease_spell_damage_against_type(Target::CreatureType::Humanoid, rhs->get_spell_damage_against_type(Target::CreatureType::Humanoid));
    decrease_spell_damage_against_type(Target::CreatureType::Mechanical, rhs->get_spell_damage_against_type(Target::CreatureType::Mechanical));
    decrease_spell_damage_against_type(Target::CreatureType::Undead, rhs->get_spell_damage_against_type(Target::CreatureType::Undead));

    decrease_flat_weapon_damage(rhs->get_flat_weapon_damage());

    decrease_mp5(rhs->get_mp5());
    decrease_hp5(rhs->get_hp5());
    decrease_base_spell_damage(rhs->get_base_spell_damage());

    decrease_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Arcane], MagicSchool::Arcane);
    decrease_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Fire], MagicSchool::Fire);
    decrease_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Frost], MagicSchool::Frost);
    decrease_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Holy], MagicSchool::Holy);
    decrease_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Nature], MagicSchool::Nature);
    decrease_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Physical], MagicSchool::Physical);
    decrease_spell_damage_vs_school(rhs->magic_school_damage_bonus[MagicSchool::Shadow], MagicSchool::Shadow);
}

int Stats::get_armor() const {
    return armor;
}

unsigned Stats::get_strength() const {
    return strength;
}

unsigned Stats::get_agility() const {
    return agility;
}

unsigned Stats::get_stamina() const {
    return stamina;
}

unsigned Stats::get_intellect() const {
    return intellect;
}

unsigned Stats::get_spirit() const {
    return spirit;
}

unsigned Stats::get_block_value() const {
    return block_value;
}

void Stats::increase_strength(const unsigned increase) {
    strength += increase;
}

void Stats::decrease_strength(const unsigned decrease) {
    strength -= decrease;
}

void Stats::increase_agility(const unsigned increase) {
    agility += increase;
}

void Stats::decrease_agility(const unsigned decrease) {
    agility -= decrease;
}

void Stats::increase_stamina(const unsigned increase) {
    stamina += increase;
}

void Stats::decrease_stamina(const unsigned decrease) {
    stamina -= decrease;
}

void Stats::increase_intellect(const unsigned increase) {
    intellect += increase;
}

void Stats::decrease_intellect(const unsigned decrease) {
    intellect -= decrease;
}

void Stats::increase_spirit(const unsigned increase) {
    spirit += increase;
}

void Stats::decrease_spirit(const unsigned decrease) {
    spirit -= decrease;
}

void Stats::increase_armor(const int increase) {
    armor += increase;
}

void Stats::decrease_armor(const int decrease) {
    armor -= decrease;
}

void Stats::increase_block_value(const int increase) {
    block_value += increase;
}

void Stats::decrease_block_value(const int decrease) {
    block_value -= decrease;
}

void Stats::increase_defense(const int increase) {
    defense += increase;
}

void Stats::decrease_defense(const int decrease) {
    defense -= decrease;
}

void Stats::increase_dodge(const double increase) {
    dodge_chance += increase;
}

void Stats::decrease_dodge(const double decrease) {
    dodge_chance -= decrease;
}

void Stats::increase_parry(const double increase) {
    parry_chance += increase;
}

void Stats::decrease_parry(const double decrease) {
    parry_chance -= decrease;
}

void Stats::increase_arcane_resistance(const int increase) {
    arcane_res += increase;
}

void Stats::decrease_arcane_resistance(const int decrease) {
    arcane_res -= decrease;
}

void Stats::increase_fire_resistance(const int increase) {
    fire_res += increase;
}

void Stats::decrease_fire_resistance(const int decrease) {
    fire_res -= decrease;
}

void Stats::increase_frost_resistance(const int increase) {
    frost_res += increase;
}

void Stats::decrease_frost_resistance(const int decrease) {
    frost_res -= decrease;
}

void Stats::increase_holy_resistance(const int increase) {
    holy_res += increase;
}

void Stats::decrease_holy_resistance(const int decrease) {
    holy_res -= decrease;
}

void Stats::increase_nature_resistance(const int increase) {
    nature_res += increase;
}

void Stats::decrease_nature_resistance(const int decrease) {
    nature_res -= decrease;
}

void Stats::increase_shadow_resistance(const int increase) {
    shadow_res += increase;
}

void Stats::decrease_shadow_resistance(const int decrease) {
    shadow_res -= decrease;
}

unsigned Stats::get_axe_skill() const {
    return axe_skill;
}

void Stats::increase_axe_skill(const unsigned value) {
    axe_skill += value;
}
void Stats::decrease_axe_skill(const unsigned value) {
    axe_skill -= value;
}

unsigned Stats::get_dagger_skill() const {
    return dagger_skill;
}

void Stats::increase_dagger_skill(const unsigned value) {
    dagger_skill += value;
}

void Stats::decrease_dagger_skill(const unsigned value) {
    dagger_skill -= value;
}

unsigned Stats::get_fist_skill() const {
    return fist_skill;
}

void Stats::increase_fist_skill(const unsigned value) {
    fist_skill += value;
}

void Stats::decrease_fist_skill(const unsigned value) {
    fist_skill -= value;
}

unsigned Stats::get_mace_skill() const {
    return mace_skill;
}

void Stats::increase_mace_skill(const unsigned value) {
    mace_skill += value;
}

void Stats::decrease_mace_skill(const unsigned value) {
    mace_skill -= value;
}

unsigned Stats::get_sword_skill() const {
    return sword_skill;
}

void Stats::increase_sword_skill(const unsigned value) {
    sword_skill += value;
}

void Stats::decrease_sword_skill(const unsigned value) {
    sword_skill -= value;
}

unsigned Stats::get_twohand_axe_skill() const {
    return twohand_axe_skill;
}

void Stats::increase_twohand_axe_skill(const unsigned value) {
    twohand_axe_skill += value;
}
void Stats::decrease_twohand_axe_skill(const unsigned value) {
    twohand_axe_skill -= value;
}

unsigned Stats::get_twohand_mace_skill() const {
    return twohand_mace_skill;
}

void Stats::increase_twohand_mace_skill(const unsigned value) {
    twohand_mace_skill += value;
}

void Stats::decrease_twohand_mace_skill(const unsigned value) {
    twohand_mace_skill -= value;
}

unsigned Stats::get_twohand_sword_skill() const {
    return twohand_sword_skill;
}

void Stats::increase_twohand_sword_skill(const unsigned value) {
    twohand_sword_skill += value;
}

void Stats::decrease_twohand_sword_skill(const unsigned value) {
    twohand_sword_skill -= value;
}

unsigned Stats::get_bow_skill() const {
    return bow_skill;
}

void Stats::increase_bow_skill(const unsigned value) {
    bow_skill += value;
}

void Stats::decrease_bow_skill(const unsigned value) {
    bow_skill -= value;
}

unsigned Stats::get_crossbow_skill() const {
    return crossbow_skill;
}

void Stats::increase_crossbow_skill(const unsigned value) {
    crossbow_skill += value;
}

void Stats::decrease_crossbow_skill(const unsigned value) {
    crossbow_skill -= value;
}

unsigned Stats::get_gun_skill() const {
    return gun_skill;
}

void Stats::increase_gun_skill(const unsigned value) {
    gun_skill += value;
}

void Stats::decrease_gun_skill(const unsigned value) {
    gun_skill -= value;
}

unsigned Stats::get_base_melee_ap() const {
    return melee_ap;
}

void Stats::increase_base_melee_ap(const unsigned increase) {
    melee_ap += increase;
}

void Stats::decrease_base_melee_ap(const unsigned decrease) {
    check((melee_ap >= decrease), "Underflow base melee ap decrease");
    melee_ap -= decrease;
}

unsigned Stats::get_base_feral_ap() const {
    return feral_ap;
}

void Stats::increase_base_feral_ap(const unsigned increase) {
    feral_ap += increase;
}

void Stats::decrease_base_feral_ap(const unsigned decrease) {
    check((feral_ap >= decrease), "Underflow base feral ap decrease");
    feral_ap -= decrease;
}

unsigned Stats::get_base_ranged_ap() const {
    return ranged_ap;
}

void Stats::increase_base_ranged_ap(const unsigned increase) {
    ranged_ap += increase;
}

void Stats::decrease_base_ranged_ap(const unsigned decrease) {
    check((ranged_ap >= decrease), "Underflow base ranged ap decrease");
    ranged_ap -= decrease;
}

unsigned Stats::get_melee_hit_chance() const {
    return melee_hit;
}

unsigned Stats::get_ranged_hit_chance() const {
    return ranged_hit;
}

unsigned Stats::get_melee_crit_chance() const {
    return melee_crit;
}

unsigned Stats::get_ranged_crit_chance() const {
    return ranged_crit;
}

unsigned Stats::get_spell_hit_chance(const MagicSchool school) const {
    return spell_hit + magic_school_hit_bonus[school];
}

unsigned Stats::get_spell_crit_chance(MagicSchool school) const {
    return spell_crit + magic_school_crit_bonus[school];
}

void Stats::increase_melee_aura_crit(const unsigned value) {
    melee_crit += value;
}

void Stats::decrease_melee_aura_crit(const unsigned value) {
    check((melee_crit >= value), "Underflow melee crit decrease");
    melee_crit -= value;
}

void Stats::increase_melee_hit(const unsigned value) {
    melee_hit += value;
}

void Stats::decrease_melee_hit(const unsigned value) {
    check((melee_hit >= value), "Underflow melee hit decrease");
    melee_hit -= value;
}

void Stats::increase_ranged_hit(const unsigned value) {
    ranged_hit += value;
}

void Stats::decrease_ranged_hit(const unsigned value) {
    check((ranged_hit >= value), "Underflow ranged hit decrease");
    ranged_hit -= value;
}

void Stats::increase_ranged_crit(const unsigned value) {
    ranged_crit += value;
}

void Stats::decrease_ranged_crit(const unsigned value) {
    check((ranged_crit >= value), "Underflow ranged crit decrease");
    ranged_crit -= value;
}

unsigned Stats::get_ranged_attack_speed_percent() const {
    return ranged_attack_speed;
}

void Stats::increase_ranged_attack_speed(const unsigned value) {
    check((ranged_attack_speed == 0 || value == 0), "Cannot increase non-zero ranged attack speed");
    ranged_attack_speed += value;
}

void Stats::decrease_ranged_attack_speed(const unsigned value) {
    check((ranged_attack_speed >= value), "Underflow decrease ranged attack speed");
    ranged_attack_speed -= value;
}

void Stats::increase_spell_hit(const unsigned value) {
    spell_hit += value;
}

void Stats::decrease_spell_hit(const unsigned value) {
    spell_hit -= value;
}

void Stats::increase_spell_hit(const MagicSchool school, const unsigned value) {
    magic_school_hit_bonus[school] += value;
}

void Stats::decrease_spell_hit(const MagicSchool school, const unsigned value) {
    check((magic_school_hit_bonus[school] >= value), "Underflow spell school hit decrease");

    magic_school_hit_bonus[school] -= value;
}

void Stats::increase_spell_crit(const unsigned value) {
    spell_crit += value;
}

void Stats::decrease_spell_crit(const unsigned value) {
    check((spell_crit >= value), "Underflow spell_crit decrease");
    spell_crit -= value;
}

void Stats::increase_spell_crit(const MagicSchool school, const unsigned value) {
    magic_school_crit_bonus[school] += value;
}

void Stats::decrease_spell_crit(const MagicSchool school, const unsigned value) {
    check((magic_school_crit_bonus[school] >= value), "Underflow spell school crit decrease");

    magic_school_crit_bonus[school] -= value;
}

void Stats::increase_melee_ap_against_type(const Target::CreatureType type, const unsigned increase) {
    melee_ap_against_creature[type] += increase;
}

void Stats::decrease_melee_ap_against_type(const Target::CreatureType type, const unsigned decrease) {
    melee_ap_against_creature[type] -= decrease;
}

unsigned Stats::get_melee_ap_against_type(const Target::CreatureType type) const {
    return melee_ap_against_creature[type];
}

void Stats::increase_ranged_ap_against_type(const Target::CreatureType type, const unsigned increase) {
    ranged_ap_against_creature[type] += increase;
}

void Stats::decrease_ranged_ap_against_type(const Target::CreatureType type, const unsigned decrease) {
    ranged_ap_against_creature[type] -= decrease;
}

unsigned Stats::get_ranged_ap_against_type(const Target::CreatureType type) const {
    return ranged_ap_against_creature[type];
}

void Stats::increase_spell_damage_against_type(const Target::CreatureType type, const unsigned increase) {
    spell_damage_against_creature[type] += increase;
}

void Stats::decrease_spell_damage_against_type(const Target::CreatureType type, const unsigned decrease) {
    check((spell_damage_against_creature[type] >= decrease), "Underflow decrease spell damage against type");
    spell_damage_against_creature[type] -= decrease;
}

unsigned Stats::get_spell_damage_against_type(const Target::CreatureType type) const {
    return spell_damage_against_creature[type];
}

unsigned Stats::get_flat_weapon_damage() const {
    return flat_weapon_damage;
}

void Stats::increase_flat_weapon_damage(const unsigned value) {
    flat_weapon_damage += value;
}

void Stats::decrease_flat_weapon_damage(const unsigned value) {
    check((value <= flat_weapon_damage), "Underflow decrease flat_weapon_damage");
    flat_weapon_damage -= value;
}

unsigned Stats::get_mp5() const {
    return mp5;
}

void Stats::increase_mp5(const unsigned increase) {
    mp5 += increase;
}

void Stats::decrease_mp5(const unsigned decrease) {
    check((decrease <= mp5), "Underflow decrease mp5");
    mp5 -= decrease;
}

unsigned Stats::get_hp5() const {
    return hp5;
}

void Stats::increase_hp5(const unsigned increase) {
    hp5 += increase;
}

void Stats::decrease_hp5(const unsigned decrease) {
    check((decrease <= hp5), "Underflow decrease hp5");
    hp5 -= decrease;
}

unsigned Stats::get_base_spell_damage() const {
    return spell_damage;
}

void Stats::increase_base_spell_damage(const unsigned increase) {
    spell_damage += increase;
}

void Stats::decrease_base_spell_damage(const unsigned decrease) {
    check((decrease <= spell_damage), "Underflow decrease spell_damage");
    spell_damage -= decrease;
}

unsigned Stats::get_spell_damage(const MagicSchool school) const {
    return get_base_spell_damage() + magic_school_damage_bonus[school];
}

void Stats::increase_spell_damage_vs_school(const unsigned increase, const MagicSchool school) {
    magic_school_damage_bonus[school] += increase;
}

void Stats::decrease_spell_damage_vs_school(const unsigned decrease, const MagicSchool school) {
    check((decrease <= magic_school_damage_bonus[school]), "Underflow Stats::decrease_spell_damage_vs_school()");
    magic_school_damage_bonus[school] -= decrease;
}

unsigned Stats::get_spell_penetration(const MagicSchool school) const {
    return magic_school_spell_penetration_bonus[school];
}

void Stats::increase_spell_penetration(const MagicSchool school, const unsigned increase) {
    magic_school_spell_penetration_bonus[school] += increase;
}

void Stats::decrease_spell_penetration(const MagicSchool school, const unsigned decrease) {
    check((decrease <= magic_school_spell_penetration_bonus[school]), "Underflow decrease spell penetration bonus");
    magic_school_spell_penetration_bonus[school] -= decrease;
}

QStringList Stats::get_equip_effects_tooltip() const {
    return this->equip_effects_tooltip;
}

QStringList Stats::get_base_tooltip() const {
    return this->base_tooltip;
}
