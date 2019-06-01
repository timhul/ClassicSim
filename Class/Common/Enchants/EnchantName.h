#ifndef ENCHANTSTATICNAME_H
#define ENCHANTSTATICNAME_H

#include <QObject>

#include "Utils/Check.h"

class EnchantName : public QObject {
    Q_OBJECT

public:
    enum Name {
        NoEnchant = -1,
        Crusader,
        FieryWeapon,
        SuperiorStriking,
        EnchantWeaponAgility,
        EnchantWeaponStrength,
        IronCounterweight,
        Enchant2HWeaponAgility,
        Enchant2HWeaponSuperiorImpact,
        Biznicks247x128Accurascope,
        SniperScope,
        FalconsCall,
        InstantPoison,
        WindfuryTotem,
        EnchantBracerManaRegeneration,
        EnchantBracerMinorAgility,
        EnchantBracerSuperiorStrength,
        EnchantGlovesSuperiorAgility,
        EnchantGlovesGreaterStrength,
        EnchantGlovesMinorHaste,
        ArcanumOfRapidity,
        LesserArcanumOfVoracityAgility,
        LesserArcanumOfVoracityIntellect,
        LesserArcanumOfVoracitySpirit,
        LesserArcanumOfVoracityStamina,
        LesserArcanumOfVoracityStrength,
        DeathsEmbrace,
        EnchantCloakLesserAgility,
        ZandalarSignetOfMight,
        MightOfTheScourge,
        EnchantChestGreaterStats,
        EnchantBootsMinorSpeed,
        EnchantBootsGreaterAgility,
        ElementalSharpeningStone,
        ConsecratedSharpeningStone,
        DenseSharpeningStone,
        LesserManaOil,
        BrilliantManaOil,
        BrilliantWizardOil,
    };

    Q_ENUMS(Name)

    static QString get_name(Name enchant) {
        switch (enchant) {
        case EnchantName::NoEnchant:
            check(false, "Requested enchant name for EnchantName::NoEnchant");
            return "no enchant";
        case EnchantName::Crusader:
            return "Crusader";
        case EnchantName::FieryWeapon:
            return "Fiery Weapon";
        case EnchantName::WindfuryTotem:
            return "Windfury Totem";
        case EnchantName::InstantPoison:
            return "Instant Poison";
        case EnchantName::SuperiorStriking:
            return "Superior Striking";
        case EnchantName::EnchantWeaponAgility:
            return "Agility";
        case EnchantName::EnchantWeaponStrength:
            return "Strength";
        case EnchantName::EnchantBracerManaRegeneration:
            return "Mana Regeneration";
        case EnchantName::EnchantBracerMinorAgility:
            return "Minor Agility";
        case EnchantName::EnchantBracerSuperiorStrength:
            return "Superior Strength";
        case EnchantName::EnchantGlovesSuperiorAgility:
            return "Superior Agility";
        case EnchantName::EnchantGlovesGreaterStrength:
            return "Greater Strength";
        case EnchantName::EnchantGlovesMinorHaste:
            return "Minor Haste";
        case EnchantName::IronCounterweight:
            return "Iron Counterweight";
        case EnchantName::Enchant2HWeaponAgility:
            return "2H Weapon Agility";
        case EnchantName::Enchant2HWeaponSuperiorImpact:
            return "2H Weapon Superior Impact";
        case EnchantName::Biznicks247x128Accurascope:
            return "Biznicks 247x128 Accurascope";
        case EnchantName::SniperScope:
            return "Sniper Scope";
        case EnchantName::ArcanumOfRapidity:
            return "Arcanum of Rapidity";
        case EnchantName::LesserArcanumOfVoracityAgility:
        case EnchantName::LesserArcanumOfVoracityIntellect:
        case EnchantName::LesserArcanumOfVoracitySpirit:
        case EnchantName::LesserArcanumOfVoracityStamina:
        case EnchantName::LesserArcanumOfVoracityStrength:
            return "Lesser Arcanum of Voracity";
        case EnchantName::DeathsEmbrace:
            return "Death's Embrace";
        case EnchantName::FalconsCall:
            return "Falcon's Call";
        case EnchantName::EnchantCloakLesserAgility:
            return "Lesser Agility";
        case EnchantName::ZandalarSignetOfMight:
            return "Zandalar Signet of Might";
        case EnchantName::MightOfTheScourge:
            return "Might of the Scourge";
        case EnchantName::EnchantChestGreaterStats:
            return "Greater Stats";
        case EnchantName::EnchantBootsMinorSpeed:
            return "Minor Speed";
        case EnchantName:: EnchantBootsGreaterAgility:
            return "Greater Agility";
        case EnchantName:: ElementalSharpeningStone:
            return "Elemental Sharpening Stone";
        case EnchantName::ConsecratedSharpeningStone:
            return "Consecrated Sharpening Stone";
        case EnchantName::DenseSharpeningStone:
            return "Dense Sharpening Stone";
        case EnchantName::LesserManaOil:
            return "Lesser Mana Oil";
        case EnchantName::BrilliantManaOil:
            return "Brilliant Mana Oil";
        case EnchantName::BrilliantWizardOil:
            return "Brilliant Wizard Oil";
        }

        check(false, "EnchantName::get_name reached end of switch");
        return "";
    }

    static QString get_effect(Name enchant) {
        switch (enchant) {
        case EnchantName::NoEnchant:
            check(false, "Requested tooltip effect for EnchantName::NoEnchant");
            return "no enchant";
        case EnchantName::Crusader:
            return "Crusader";
        case EnchantName::FieryWeapon:
            return "Fiery Weapon";
        case EnchantName::WindfuryTotem:
            return "Windfury Totem";
        case EnchantName::InstantPoison:
            return "Instant Poison";
        case EnchantName::SuperiorStriking:
            return "+5 Damage";
        case EnchantName::EnchantWeaponAgility:
            return "+15 Agility";
        case EnchantName::EnchantWeaponStrength:
            return "+15 Strength";
        case EnchantName::EnchantBracerManaRegeneration:
            return "+4 mp5";
        case EnchantName::EnchantBracerMinorAgility:
            return "+1 Agility";
        case EnchantName::EnchantBracerSuperiorStrength:
            return "+9 Strength";
        case EnchantName::EnchantGlovesSuperiorAgility:
            return "+15 Agility";
        case EnchantName::EnchantGlovesGreaterStrength:
            return "+7 Strength";
        case EnchantName::EnchantGlovesMinorHaste:
            return "+1% Attack Speed";
        case EnchantName::IronCounterweight:
            return "+3% Attack Speed";
        case EnchantName::Enchant2HWeaponAgility:
            return "+25 Agility";
        case EnchantName::Enchant2HWeaponSuperiorImpact:
            return "+9 Damage";
        case EnchantName::Biznicks247x128Accurascope:
            return "+3% Ranged Hit";
        case EnchantName::SniperScope:
            return "+7 Damage";
        case EnchantName::ArcanumOfRapidity:
            return "+1% Haste";
        case EnchantName::LesserArcanumOfVoracityAgility:
            return "+8 Agility";
        case EnchantName::LesserArcanumOfVoracityIntellect:
            return "+8 Intellect";
        case EnchantName::LesserArcanumOfVoracitySpirit:
            return "+8 Spirit";
        case EnchantName::LesserArcanumOfVoracityStamina:
            return "+8 Stamina";
        case EnchantName::LesserArcanumOfVoracityStrength:
            return "+8 Strength";
        case EnchantName::DeathsEmbrace:
            return "+28 Attack and\n1% Dodge";
        case EnchantName::FalconsCall:
            return "+24 Ranged Attack Power\n10 Stamina, +1% Hit";
        case EnchantName::EnchantCloakLesserAgility:
            return "+3 Agility";
        case EnchantName::ZandalarSignetOfMight:
            return "+30 Attack Power";
        case EnchantName::MightOfTheScourge:
            return "+1% Crit and\n+26 Attack Power";
        case EnchantName::EnchantChestGreaterStats:
            return "+4 Attributes";
        case EnchantName::EnchantBootsMinorSpeed:
            return "Speed Increase";
        case EnchantName:: EnchantBootsGreaterAgility:
            return "+7 Agility";
        case EnchantName:: ElementalSharpeningStone:
            return "+2% Crit";
        case EnchantName::ConsecratedSharpeningStone:
            return "+100 AP\nvs Undead";
        case EnchantName::DenseSharpeningStone:
            return "+8 Damage";
        case EnchantName::LesserManaOil:
            return "+8 mp5";
        case EnchantName::BrilliantManaOil:
            return "+12mp5/+25 Heal";
        case EnchantName::BrilliantWizardOil:
            return "+36 SP\n+1% Spell Crit";
        }

        check(false, "EnchantName::get_effect reached end of switch");
        return "";
    }
};

#endif // ENCHANTSTATICNAME_H
