
#include "Character.h"
#include "CharacterStats.h"
#include "EnchantStatic.h"

EnchantStatic::EnchantStatic(EnchantName::Name enchant_name, Character *pchar) :
    Enchant(get_name_from_enum(enchant_name), get_effect_from_enum(enchant_name)),
    enchant_name(enchant_name),
    pchar(pchar)
{
    switch (enchant_name) {
    case EnchantName::EnchantBracerSuperiorStrength:
        pchar->get_stats()->increase_strength(9);
        break;
    case EnchantName::EnchantGlovesGreaterStrength:
        pchar->get_stats()->increase_strength(7);
        break;
    case EnchantName::EnchantGlovesMinorHaste:
        pchar->get_stats()->increase_haste(1); // This is wrong, it should not be a multiplicative effect
        break;
    case EnchantName::IronCounterweight:
        pchar->get_stats()->increase_haste(3); // This is wrong, it should not be a multiplicative effect
        break;
    case EnchantName::Enchant2HWeaponAgility:
        pchar->get_stats()->increase_agility(25);
        break;
    case EnchantName::ArcanumOfRapidity:
        pchar->get_stats()->increase_haste(1); // MIGHT be wrong, investigate if it should be a multiplicative effect
        break;
    case EnchantName::LesserArcanumOfVoracity:
        pchar->get_stats()->increase_strength(8);
        break;
    case EnchantName::EnchantCloakLesserAgility:
        pchar->get_stats()->increase_agility(3);
        break;
    case EnchantName::ZandalarSignetOfMight:
        pchar->get_stats()->increase_melee_ap(30);
        // TODO: should increase ranged ap
        break;
    case EnchantName::MightOfTheScourge:
        pchar->get_stats()->increase_melee_ap(26);
        pchar->get_stats()->increase_crit(0.01);
        break;
    case EnchantName::EnchantChestGreaterStats:
        pchar->get_stats()->increase_agility(4);
        pchar->get_stats()->increase_intellect(4);
        pchar->get_stats()->increase_spirit(4);
        pchar->get_stats()->increase_stamina(4);
        pchar->get_stats()->increase_strength(4);
        break;
    default:
        assert(false);
        break;
    }
}

EnchantStatic::~EnchantStatic() {
    switch (enchant_name) {
    case EnchantName::EnchantBracerSuperiorStrength:
        pchar->get_stats()->decrease_strength(9);
        break;
    case EnchantName::EnchantGlovesGreaterStrength:
        pchar->get_stats()->decrease_strength(7);
        break;
    case EnchantName::EnchantGlovesMinorHaste:
        pchar->get_stats()->decrease_haste(1); // This is wrong, it should not be a multiplicative effect
        break;
    case EnchantName::IronCounterweight:
        pchar->get_stats()->decrease_haste(3); // This is wrong, it should not be a multiplicative effect
        break;
    case EnchantName::Enchant2HWeaponAgility:
        pchar->get_stats()->decrease_agility(25);
        break;
    case EnchantName::ArcanumOfRapidity:
        pchar->get_stats()->decrease_haste(1); // MIGHT be wrong, investigate if it should be a multiplicative effect
        break;
    case EnchantName::LesserArcanumOfVoracity:
        pchar->get_stats()->decrease_strength(8);
        break;
    case EnchantName::EnchantCloakLesserAgility:
        pchar->get_stats()->decrease_agility(3);
        break;
    case EnchantName::ZandalarSignetOfMight:
        pchar->get_stats()->decrease_melee_ap(30);
        // TODO: should decrease ranged ap
        break;
    case EnchantName::MightOfTheScourge:
        pchar->get_stats()->decrease_melee_ap(26);
        pchar->get_stats()->decrease_crit(0.01);
        break;
    case EnchantName::EnchantChestGreaterStats:
        pchar->get_stats()->decrease_agility(4);
        pchar->get_stats()->decrease_intellect(4);
        pchar->get_stats()->decrease_spirit(4);
        pchar->get_stats()->decrease_stamina(4);
        pchar->get_stats()->decrease_strength(4);
        break;
    default:
        assert(false);
        break;
    }
}

QString get_name_from_enum(EnchantName::Name enchant_name) {
    switch (enchant_name) {
    case EnchantName::EnchantBracerSuperiorStrength:
        return "Superior Strength";
    case EnchantName::EnchantGlovesGreaterStrength:
        return "Greater Strength";
    case EnchantName::EnchantGlovesMinorHaste:
        return "Minor Haste";
    case EnchantName::IronCounterweight:
        return "Iron Counterweight";
    case EnchantName::Enchant2HWeaponAgility:
        return "2H Weapon Agility";
    case EnchantName::ArcanumOfRapidity:
        return "Arcanum of Rapidity";
    case EnchantName::LesserArcanumOfVoracity:
        return "Lesser Arcanum of Voracity";
    case EnchantName::EnchantCloakLesserAgility:
        return "Lesser Agility";
    case EnchantName::ZandalarSignetOfMight:
        return "Zandalar Signet of Might";
    case EnchantName::MightOfTheScourge:
        return "Might of the Scourge";
    case EnchantName::EnchantChestGreaterStats:
        return "Greater Stats";
    default:
        assert(false);
        return "<Missing static enchant name>";
    }
}

QString get_effect_from_enum(EnchantName::Name enchant_name) {
    switch (enchant_name) {
    case EnchantName::EnchantBracerSuperiorStrength:
        return "+9 Strength";
    case EnchantName::EnchantGlovesGreaterStrength:
        return "+7 Strength";
    case EnchantName::EnchantGlovesMinorHaste:
        return "+1% Attack Speed";
    case EnchantName::IronCounterweight:
        return "+3% Attack Speed";
    case EnchantName::Enchant2HWeaponAgility:
        return "+25 Agility";
    case EnchantName::ArcanumOfRapidity:
        return "+1% Haste";
    case EnchantName::LesserArcanumOfVoracity:
        return "+8 Strength";
    case EnchantName::EnchantCloakLesserAgility:
        return "+3 Agility";
    case EnchantName::ZandalarSignetOfMight:
        return "+30 Attack Power";
    case EnchantName::MightOfTheScourge:
        return "+1% Crit and\n+26 Attack Power";
    case EnchantName::EnchantChestGreaterStats:
        return "+4 Attributes";
    default:
        assert(false);
        return "<Missing static enchant name>";
    }
}
