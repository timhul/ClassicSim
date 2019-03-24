#include "EnchantStatic.h"

#include "Character.h"
#include "CharacterStats.h"
#include "Utils/Check.h"

EnchantStatic::EnchantStatic(EnchantName::Name enchant_name, Character *pchar, int enchant_slot) :
    Enchant(enchant_name),
    enchant_name(enchant_name),
    pchar(pchar),
    enchant_slot(enchant_slot)
{
    switch (enchant_name) {
    case EnchantName::SuperiorStriking:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->increase_mh_flat_damage_bonus(5);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->increase_oh_flat_damage_bonus(5);
        else
            check(false, "Unhandled case in switch");
        break;
    case EnchantName::EnchantWeaponAgility:
        pchar->get_stats()->increase_agility(15);
        break;
    case EnchantName::EnchantWeaponStrength:
        pchar->get_stats()->increase_strength(15);
        break;
    case EnchantName::EnchantBracerMinorAgility:
        pchar->get_stats()->increase_agility(1);
        break;
    case EnchantName::EnchantBracerSuperiorStrength:
        pchar->get_stats()->increase_strength(9);
        break;
    case EnchantName::EnchantGlovesSuperiorAgility:
        pchar->get_stats()->increase_agility(15);
        break;
    case EnchantName::EnchantGlovesGreaterStrength:
        pchar->get_stats()->increase_strength(7);
        break;
    case EnchantName::EnchantGlovesMinorHaste:
        pchar->get_stats()->increase_melee_attack_speed(1);
        break;
    case EnchantName::IronCounterweight:
        pchar->get_stats()->increase_melee_attack_speed(3);
        break;
    case EnchantName::Enchant2HWeaponAgility:
        pchar->get_stats()->increase_agility(25);
        break;
    case EnchantName::Enchant2HWeaponSuperiorImpact:
        pchar->increase_mh_flat_damage_bonus(9);
        break;
    case EnchantName::ArcanumOfRapidity:
        pchar->get_stats()->increase_melee_attack_speed(1);
        break;
    case EnchantName::LesserArcanumOfVoracityAgility:
        pchar->get_stats()->increase_agility(8);
        break;
    case EnchantName::LesserArcanumOfVoracityIntellect:
        pchar->get_stats()->increase_intellect(8);
        break;
    case EnchantName::LesserArcanumOfVoracitySpirit:
        pchar->get_stats()->increase_spirit(8);
        break;
    case EnchantName::LesserArcanumOfVoracityStamina:
        pchar->get_stats()->increase_stamina(8);
        break;
    case EnchantName::LesserArcanumOfVoracityStrength:
        pchar->get_stats()->increase_strength(8);
        break;
    case EnchantName::DeathsEmbrace:
        pchar->get_stats()->increase_melee_ap(28);
        pchar->get_stats()->increase_ranged_ap(28);
        pchar->get_stats()->increase_dodge(0.01);
        break;
    case EnchantName::FalconsCall:
        pchar->get_stats()->increase_ranged_ap(24);
        pchar->get_stats()->increase_stamina(10);
        pchar->get_stats()->increase_melee_hit(1);
        pchar->get_stats()->increase_ranged_hit(1);
        break;
    case EnchantName::EnchantCloakLesserAgility:
        pchar->get_stats()->increase_agility(3);
        break;
    case EnchantName::ZandalarSignetOfMight:
        pchar->get_stats()->increase_melee_ap(30);
        pchar->get_stats()->increase_ranged_ap(30);
        break;
    case EnchantName::MightOfTheScourge:
        pchar->get_stats()->increase_melee_ap(26);
        pchar->get_stats()->increase_ranged_ap(26);
        pchar->get_stats()->increase_crit(0.01);
        break;
    case EnchantName::EnchantChestGreaterStats:
        pchar->get_stats()->increase_agility(4);
        pchar->get_stats()->increase_intellect(4);
        pchar->get_stats()->increase_spirit(4);
        pchar->get_stats()->increase_stamina(4);
        pchar->get_stats()->increase_strength(4);
        break;
    case EnchantName::EnchantBootsMinorSpeed:
        break;
    case EnchantName:: EnchantBootsGreaterAgility:
        pchar->get_stats()->increase_agility(7);
        break;
    case EnchantName:: ElementalSharpeningStone:
        pchar->get_stats()->increase_crit(0.02);
        break;
    case EnchantName::ConsecratedSharpeningStone:
        pchar->get_stats()->increase_ap_vs_type(Target::CreatureType::Undead, 100);
        break;
    case EnchantName::DenseSharpeningStone:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->increase_mh_flat_damage_bonus(8);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->increase_oh_flat_damage_bonus(8);
        else
            check(false, "Unhandled case in switch");
        break;
    default:
        check(false, "Reached end of switch");
        break;
    }
}

EnchantStatic::~EnchantStatic() {
    switch (enchant_name) {
    case EnchantName::SuperiorStriking:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->decrease_mh_flat_damage_bonus(5);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->decrease_oh_flat_damage_bonus(5);
        break;
    case EnchantName::EnchantWeaponAgility:
        pchar->get_stats()->decrease_agility(15);
        break;
    case EnchantName::EnchantWeaponStrength:
        pchar->get_stats()->decrease_strength(15);
        break;
    case EnchantName::EnchantBracerMinorAgility:
        pchar->get_stats()->decrease_agility(1);
        break;
    case EnchantName::EnchantBracerSuperiorStrength:
        pchar->get_stats()->decrease_strength(9);
        break;
    case EnchantName::EnchantGlovesSuperiorAgility:
        pchar->get_stats()->decrease_agility(15);
        break;
    case EnchantName::EnchantGlovesGreaterStrength:
        pchar->get_stats()->decrease_strength(7);
        break;
    case EnchantName::EnchantGlovesMinorHaste:
        pchar->get_stats()->decrease_melee_attack_speed(1);
        break;
    case EnchantName::IronCounterweight:
        pchar->get_stats()->decrease_melee_attack_speed(3);
        break;
    case EnchantName::Enchant2HWeaponAgility:
        pchar->get_stats()->decrease_agility(25);
        break;
    case EnchantName::Enchant2HWeaponSuperiorImpact:
        pchar->decrease_mh_flat_damage_bonus(9);
        break;
    case EnchantName::ArcanumOfRapidity:
        pchar->get_stats()->decrease_melee_attack_speed(1);
        break;
    case EnchantName::LesserArcanumOfVoracityAgility:
        pchar->get_stats()->decrease_agility(8);
        break;
    case EnchantName::LesserArcanumOfVoracityIntellect:
        pchar->get_stats()->decrease_intellect(8);
        break;
    case EnchantName::LesserArcanumOfVoracitySpirit:
        pchar->get_stats()->decrease_spirit(8);
        break;
    case EnchantName::LesserArcanumOfVoracityStamina:
        pchar->get_stats()->decrease_stamina(8);
        break;
    case EnchantName::LesserArcanumOfVoracityStrength:
        pchar->get_stats()->decrease_strength(8);
        break;
    case EnchantName::DeathsEmbrace:
        pchar->get_stats()->decrease_melee_ap(28);
        pchar->get_stats()->decrease_ranged_ap(28);
        pchar->get_stats()->decrease_dodge(0.01);
        break;
    case EnchantName::FalconsCall:
        pchar->get_stats()->decrease_ranged_ap(24);
        pchar->get_stats()->decrease_stamina(10);
        pchar->get_stats()->decrease_melee_hit(1);
        pchar->get_stats()->decrease_ranged_hit(1);
        break;
    case EnchantName::EnchantCloakLesserAgility:
        pchar->get_stats()->decrease_agility(3);
        break;
    case EnchantName::ZandalarSignetOfMight:
        pchar->get_stats()->decrease_melee_ap(30);
        pchar->get_stats()->decrease_ranged_ap(30);
        break;
    case EnchantName::MightOfTheScourge:
        pchar->get_stats()->decrease_melee_ap(26);
        pchar->get_stats()->decrease_ranged_ap(26);
        pchar->get_stats()->decrease_crit(0.01);
        break;
    case EnchantName::EnchantChestGreaterStats:
        pchar->get_stats()->decrease_agility(4);
        pchar->get_stats()->decrease_intellect(4);
        pchar->get_stats()->decrease_spirit(4);
        pchar->get_stats()->decrease_stamina(4);
        pchar->get_stats()->decrease_strength(4);
        break;
    case EnchantName::EnchantBootsMinorSpeed:
        break;
    case EnchantName:: EnchantBootsGreaterAgility:
        pchar->get_stats()->decrease_agility(7);
        break;
    case EnchantName:: ElementalSharpeningStone:
        pchar->get_stats()->decrease_crit(0.02);
        break;
    case EnchantName::ConsecratedSharpeningStone:
        pchar->get_stats()->decrease_ap_vs_type(Target::CreatureType::Undead, 100);
        break;
    case EnchantName::DenseSharpeningStone:
        if (enchant_slot == EnchantSlot::MAINHAND)
            pchar->decrease_mh_flat_damage_bonus(8);
        else if (enchant_slot == EnchantSlot::OFFHAND)
            pchar->decrease_oh_flat_damage_bonus(8);
        break;
    default:
        break;
    }
}
