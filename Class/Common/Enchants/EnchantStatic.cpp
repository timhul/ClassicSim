#include "EnchantStatic.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Utils/Check.h"

EnchantStatic::EnchantStatic(EnchantName::Name enchant_name, Character* pchar, EnchantInfo* enchant_info, int enchant_slot) :
    Enchant(enchant_name, enchant_info), enchant_name(enchant_name), pchar(pchar), enchant_slot(enchant_slot) {
    switch (enchant_name) {
    case EnchantName::Name::SuperiorStriking:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->get_stats()->increase_mh_weapon_damage_bonus(5);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->get_stats()->increase_oh_weapon_damage_bonus(5);
        else
            check(false, "Unhandled case in switch");
        break;
    case EnchantName::Name::EnchantWeaponAgility:
        pchar->get_stats()->increase_agility(15);
        break;
    case EnchantName::Name::EnchantWeaponStrength:
        pchar->get_stats()->increase_strength(15);
        break;
    case EnchantName::Name::EnchantWeaponSpellPower:
        pchar->get_stats()->increase_base_spell_damage(30);
        break;
    case EnchantName::Name::EnchantBracerGreaterIntellect:
        pchar->get_stats()->increase_intellect(7);
        break;
    case EnchantName::Name::EnchantBracerManaRegeneration:
        pchar->get_stats()->increase_mp5(4);
        break;
    case EnchantName::Name::EnchantBracerMinorAgility:
        pchar->get_stats()->increase_agility(1);
        break;
    case EnchantName::Name::EnchantBracerGreaterStrength:
        pchar->get_stats()->increase_strength(7);
        break;
    case EnchantName::Name::EnchantBracerSuperiorStrength:
        pchar->get_stats()->increase_strength(9);
        break;
    case EnchantName::Name::EnchantGlovesSuperiorAgility:
        pchar->get_stats()->increase_agility(15);
        break;
    case EnchantName::Name::EnchantGlovesGreaterAgility:
        pchar->get_stats()->increase_agility(7);
        break;
    case EnchantName::Name::EnchantGlovesGreaterStrength:
        pchar->get_stats()->increase_strength(7);
        break;
    case EnchantName::Name::EnchantGlovesMinorHaste:
        pchar->get_stats()->increase_melee_attack_speed(1);
        break;
    case EnchantName::Name::EnchantGlovesFirePower:
        pchar->get_stats()->increase_spell_damage_vs_school(20, MagicSchool::Fire);
        break;
    case EnchantName::Name::EnchantGlovesFrostPower:
        pchar->get_stats()->increase_spell_damage_vs_school(20, MagicSchool::Frost);
        break;
    case EnchantName::Name::EnchantGlovesShadowPower:
        pchar->get_stats()->increase_spell_damage_vs_school(20, MagicSchool::Shadow);
        break;
    case EnchantName::Name::IronCounterweight:
        pchar->get_stats()->increase_melee_attack_speed(3);
        break;
    case EnchantName::Name::Enchant2HWeaponAgility:
        pchar->get_stats()->increase_agility(25);
        break;
    case EnchantName::Name::Enchant2HWeaponSuperiorImpact:
        pchar->get_stats()->increase_mh_weapon_damage_bonus(9);
        break;
    case EnchantName::Name::Biznicks247x128Accurascope:
        pchar->get_stats()->increase_ranged_hit(300);
        break;
    case EnchantName::Name::SniperScope:
        pchar->get_stats()->increase_ranged_weapon_damage_bonus(7);
        break;
    case EnchantName::Name::ArcanumOfFocus:
        pchar->get_stats()->increase_base_spell_damage(8);
        break;
    case EnchantName::Name::ArcanumOfRapidity:
        pchar->get_stats()->increase_melee_attack_speed(1);
        break;
    case EnchantName::Name::LesserArcanumOfVoracityAgility:
        pchar->get_stats()->increase_agility(8);
        break;
    case EnchantName::Name::LesserArcanumOfVoracityIntellect:
        pchar->get_stats()->increase_intellect(8);
        break;
    case EnchantName::Name::LesserArcanumOfVoracitySpirit:
        pchar->get_stats()->increase_spirit(8);
        break;
    case EnchantName::Name::LesserArcanumOfVoracityStamina:
        pchar->get_stats()->increase_stamina(8);
        break;
    case EnchantName::Name::LesserArcanumOfVoracityStrength:
        pchar->get_stats()->increase_strength(8);
        break;
    case EnchantName::Name::DeathsEmbrace:
        pchar->get_stats()->increase_melee_ap(28);
        pchar->get_stats()->increase_ranged_ap(28);
        pchar->get_stats()->increase_dodge(0.01);
        break;
    case EnchantName::Name::FalconsCall:
        pchar->get_stats()->increase_ranged_ap(24);
        pchar->get_stats()->increase_stamina(10);
        pchar->get_stats()->increase_melee_hit(100);
        pchar->get_stats()->increase_ranged_hit(100);
        break;
    case EnchantName::Name::PresenceOfSight:
        pchar->get_stats()->increase_base_spell_damage(18);
        pchar->get_stats()->increase_spell_hit(100);
        break;
    case EnchantName::Name::HoodooHex:
        pchar->get_stats()->increase_base_spell_damage(18);
        pchar->get_stats()->increase_stamina(10);
        break;
    case EnchantName::Name::EnchantCloakLesserAgility:
        pchar->get_stats()->increase_agility(3);
        break;
    case EnchantName::Name::ZandalarSignetOfMight:
        pchar->get_stats()->increase_melee_ap(30);
        pchar->get_stats()->increase_ranged_ap(30);
        break;
    case EnchantName::Name::ZandalarSignetOfMojo:
        pchar->get_stats()->increase_base_spell_damage(18);
        break;
    case EnchantName::Name::MightOfTheScourge:
        pchar->get_stats()->increase_melee_ap(26);
        pchar->get_stats()->increase_ranged_ap(26);
        pchar->get_stats()->increase_melee_aura_crit(100);
        break;
    case EnchantName::Name::PowerOfTheScourge:
        pchar->get_stats()->increase_spell_crit(100);
        pchar->get_stats()->increase_base_spell_damage(15);
        break;
    case EnchantName::Name::EnchantChestStats:
        pchar->get_stats()->increase_agility(3);
        pchar->get_stats()->increase_intellect(3);
        pchar->get_stats()->increase_spirit(3);
        pchar->get_stats()->increase_stamina(3);
        pchar->get_stats()->increase_strength(3);
        break;
    case EnchantName::Name::EnchantChestGreaterStats:
        pchar->get_stats()->increase_agility(4);
        pchar->get_stats()->increase_intellect(4);
        pchar->get_stats()->increase_spirit(4);
        pchar->get_stats()->increase_stamina(4);
        pchar->get_stats()->increase_strength(4);
        break;
    case EnchantName::Name::EnchantChestMajorMana:
        pchar->increase_base_mana(100);
        break;
    case EnchantName::Name::EnchantBootsMinorSpeed:
        break;
    case EnchantName::Name::EnchantBootsAgility:
        pchar->get_stats()->increase_agility(5);
        break;
    case EnchantName::Name::EnchantBootsGreaterAgility:
        pchar->get_stats()->increase_agility(7);
        break;
    case EnchantName::Name::EnchantBootsSpirit:
        pchar->get_stats()->increase_spirit(5);
        break;
    case EnchantName::Name::ElementalSharpeningStone:
        pchar->get_stats()->increase_melee_aura_crit(200);
        break;
    case EnchantName::Name::ConsecratedSharpeningStone:
        pchar->get_stats()->increase_ap_vs_type(Target::CreatureType::Undead, 100);
        break;
    case EnchantName::Name::DenseSharpeningStone:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->get_stats()->increase_mh_weapon_damage_bonus(8);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->get_stats()->increase_oh_weapon_damage_bonus(8);
        else
            check(false, "Unhandled case in switch");
        break;
    case EnchantName::Name::SolidWeightstone:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->get_stats()->increase_mh_weapon_damage_bonus(6);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->get_stats()->increase_oh_weapon_damage_bonus(6);
        else
            check(false, "Unhandled case in switch");
        break;
    case EnchantName::Name::DenseWeightstone:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->get_stats()->increase_mh_weapon_damage_bonus(8);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->get_stats()->increase_oh_weapon_damage_bonus(8);
        else
            check(false, "Unhandled case in switch");
        break;
    case EnchantName::Name::LesserManaOil:
        pchar->get_stats()->increase_mp5(8);
        break;
    case EnchantName::Name::BrilliantManaOil:
        pchar->get_stats()->increase_mp5(12);
        break;
    case EnchantName::Name::BrilliantWizardOil:
        pchar->get_stats()->increase_base_spell_damage(36);
        pchar->get_stats()->increase_spell_crit(100);
        break;
    default:
        check(false, "EnchantStatic constructor reached end of switch");
        break;
    }
}

EnchantStatic::~EnchantStatic() {
    switch (enchant_name) {
    case EnchantName::Name::SuperiorStriking:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->get_stats()->decrease_mh_weapon_damage_bonus(5);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->get_stats()->decrease_oh_weapon_damage_bonus(5);
        break;
    case EnchantName::Name::EnchantWeaponAgility:
        pchar->get_stats()->decrease_agility(15);
        break;
    case EnchantName::Name::EnchantWeaponStrength:
        pchar->get_stats()->decrease_strength(15);
        break;
    case EnchantName::Name::EnchantWeaponSpellPower:
        pchar->get_stats()->decrease_base_spell_damage(30);
        break;
    case EnchantName::Name::EnchantBracerGreaterIntellect:
        pchar->get_stats()->decrease_intellect(7);
        break;
    case EnchantName::Name::EnchantBracerManaRegeneration:
        pchar->get_stats()->decrease_mp5(4);
        break;
    case EnchantName::Name::EnchantBracerMinorAgility:
        pchar->get_stats()->decrease_agility(1);
        break;
    case EnchantName::Name::EnchantBracerGreaterStrength:
        pchar->get_stats()->decrease_strength(7);
        break;
    case EnchantName::Name::EnchantBracerSuperiorStrength:
        pchar->get_stats()->decrease_strength(9);
        break;
    case EnchantName::Name::EnchantGlovesSuperiorAgility:
        pchar->get_stats()->decrease_agility(15);
        break;
    case EnchantName::Name::EnchantGlovesGreaterAgility:
        pchar->get_stats()->decrease_agility(7);
        break;
    case EnchantName::Name::EnchantGlovesGreaterStrength:
        pchar->get_stats()->decrease_strength(7);
        break;
    case EnchantName::Name::EnchantGlovesMinorHaste:
        pchar->get_stats()->decrease_melee_attack_speed(1);
        break;
    case EnchantName::Name::EnchantGlovesFirePower:
        pchar->get_stats()->decrease_spell_damage_vs_school(20, MagicSchool::Fire);
        break;
    case EnchantName::Name::EnchantGlovesFrostPower:
        pchar->get_stats()->decrease_spell_damage_vs_school(20, MagicSchool::Frost);
        break;
    case EnchantName::Name::EnchantGlovesShadowPower:
        pchar->get_stats()->decrease_spell_damage_vs_school(20, MagicSchool::Shadow);
        break;
    case EnchantName::Name::IronCounterweight:
        pchar->get_stats()->decrease_melee_attack_speed(3);
        break;
    case EnchantName::Name::Enchant2HWeaponAgility:
        pchar->get_stats()->decrease_agility(25);
        break;
    case EnchantName::Name::Enchant2HWeaponSuperiorImpact:
        pchar->get_stats()->decrease_mh_weapon_damage_bonus(9);
        break;
    case EnchantName::Name::Biznicks247x128Accurascope:
        pchar->get_stats()->decrease_ranged_hit(300);
        break;
    case EnchantName::Name::SniperScope:
        pchar->get_stats()->decrease_ranged_weapon_damage_bonus(7);
        break;
    case EnchantName::Name::ArcanumOfFocus:
        pchar->get_stats()->decrease_base_spell_damage(8);
        break;
    case EnchantName::Name::ArcanumOfRapidity:
        pchar->get_stats()->decrease_melee_attack_speed(1);
        break;
    case EnchantName::Name::LesserArcanumOfVoracityAgility:
        pchar->get_stats()->decrease_agility(8);
        break;
    case EnchantName::Name::LesserArcanumOfVoracityIntellect:
        pchar->get_stats()->decrease_intellect(8);
        break;
    case EnchantName::Name::LesserArcanumOfVoracitySpirit:
        pchar->get_stats()->decrease_spirit(8);
        break;
    case EnchantName::Name::LesserArcanumOfVoracityStamina:
        pchar->get_stats()->decrease_stamina(8);
        break;
    case EnchantName::Name::LesserArcanumOfVoracityStrength:
        pchar->get_stats()->decrease_strength(8);
        break;
    case EnchantName::Name::DeathsEmbrace:
        pchar->get_stats()->decrease_melee_ap(28);
        pchar->get_stats()->decrease_ranged_ap(28);
        pchar->get_stats()->decrease_dodge(0.01);
        break;
    case EnchantName::Name::FalconsCall:
        pchar->get_stats()->decrease_ranged_ap(24);
        pchar->get_stats()->decrease_stamina(10);
        pchar->get_stats()->decrease_melee_hit(100);
        pchar->get_stats()->decrease_ranged_hit(100);
        break;
    case EnchantName::Name::PresenceOfSight:
        pchar->get_stats()->decrease_base_spell_damage(18);
        pchar->get_stats()->decrease_spell_hit(100);
        break;
    case EnchantName::Name::HoodooHex:
        pchar->get_stats()->decrease_base_spell_damage(18);
        pchar->get_stats()->decrease_stamina(10);
        break;
    case EnchantName::Name::EnchantCloakLesserAgility:
        pchar->get_stats()->decrease_agility(3);
        break;
    case EnchantName::Name::ZandalarSignetOfMight:
        pchar->get_stats()->decrease_melee_ap(30);
        pchar->get_stats()->decrease_ranged_ap(30);
        break;
    case EnchantName::Name::ZandalarSignetOfMojo:
        pchar->get_stats()->decrease_base_spell_damage(18);
        break;
    case EnchantName::Name::MightOfTheScourge:
        pchar->get_stats()->decrease_melee_ap(26);
        pchar->get_stats()->decrease_ranged_ap(26);
        pchar->get_stats()->decrease_melee_aura_crit(100);
        break;
    case EnchantName::Name::PowerOfTheScourge:
        pchar->get_stats()->decrease_spell_crit(100);
        pchar->get_stats()->decrease_base_spell_damage(15);
        break;
    case EnchantName::Name::EnchantChestStats:
        pchar->get_stats()->decrease_agility(3);
        pchar->get_stats()->decrease_intellect(3);
        pchar->get_stats()->decrease_spirit(3);
        pchar->get_stats()->decrease_stamina(3);
        pchar->get_stats()->decrease_strength(3);
        break;
    case EnchantName::Name::EnchantChestGreaterStats:
        pchar->get_stats()->decrease_agility(4);
        pchar->get_stats()->decrease_intellect(4);
        pchar->get_stats()->decrease_spirit(4);
        pchar->get_stats()->decrease_stamina(4);
        pchar->get_stats()->decrease_strength(4);
        break;
    case EnchantName::Name::EnchantChestMajorMana:
        pchar->decrease_base_mana(100);
        break;
    case EnchantName::Name::EnchantBootsMinorSpeed:
        break;
    case EnchantName::Name::EnchantBootsAgility:
        pchar->get_stats()->decrease_agility(5);
        break;
    case EnchantName::Name::EnchantBootsGreaterAgility:
        pchar->get_stats()->decrease_agility(7);
        break;
    case EnchantName::Name::EnchantBootsSpirit:
        pchar->get_stats()->decrease_spirit(5);
        break;
    case EnchantName::Name::ElementalSharpeningStone:
        pchar->get_stats()->decrease_melee_aura_crit(200);
        break;
    case EnchantName::Name::ConsecratedSharpeningStone:
        pchar->get_stats()->decrease_ap_vs_type(Target::CreatureType::Undead, 100);
        break;
    case EnchantName::Name::DenseSharpeningStone:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->get_stats()->decrease_mh_weapon_damage_bonus(8);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->get_stats()->decrease_oh_weapon_damage_bonus(8);
        break;
    case EnchantName::Name::SolidWeightstone:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->get_stats()->decrease_mh_weapon_damage_bonus(6);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->get_stats()->decrease_oh_weapon_damage_bonus(6);
        break;
    case EnchantName::Name::DenseWeightstone:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->get_stats()->decrease_mh_weapon_damage_bonus(8);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->get_stats()->decrease_oh_weapon_damage_bonus(8);
        break;
    case EnchantName::Name::LesserManaOil:
        pchar->get_stats()->decrease_mp5(8);
        break;
    case EnchantName::Name::BrilliantManaOil:
        pchar->get_stats()->decrease_mp5(12);
        break;
    case EnchantName::Name::BrilliantWizardOil:
        pchar->get_stats()->decrease_base_spell_damage(36);
        pchar->get_stats()->decrease_spell_crit(100);
        break;
    default:
        break;
    }
}
