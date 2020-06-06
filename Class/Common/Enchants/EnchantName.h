#pragma once

#include <QObject>

#include "Utils/Check.h"

class EnchantName : public QObject {
    Q_OBJECT

public:
    enum Name
    {
        NoEnchant = -1,
        Crusader,
        FieryWeapon,
        SuperiorStriking,
        EnchantWeaponAgility,
        EnchantWeaponStrength,
        EnchantWeaponSpellPower,
        IronCounterweight,
        Enchant2HWeaponAgility,
        Enchant2HWeaponSuperiorImpact,
        Biznicks247x128Accurascope,
        SniperScope,
        FalconsCall,
        InstantPoison,
        WindfuryTotem,
        EnchantBracerGreaterIntellect,
        EnchantBracerManaRegeneration,
        EnchantBracerMinorAgility,
        EnchantBracerGreaterStrength,
        EnchantBracerSuperiorStrength,
        EnchantGlovesSuperiorAgility,
        EnchantGlovesGreaterAgility,
        EnchantGlovesGreaterStrength,
        EnchantGlovesMinorHaste,
        EnchantGlovesFirePower,
        EnchantGlovesFrostPower,
        ArcanumOfFocus,
        ArcanumOfRapidity,
        LesserArcanumOfVoracityAgility,
        LesserArcanumOfVoracityIntellect,
        LesserArcanumOfVoracitySpirit,
        LesserArcanumOfVoracityStamina,
        LesserArcanumOfVoracityStrength,
        DeathsEmbrace,
        PresenceOfSight,
        EnchantCloakLesserAgility,
        ZandalarSignetOfMight,
        ZandalarSignetOfMojo,
        MightOfTheScourge,
        EnchantChestStats,
        EnchantChestGreaterStats,
        EnchantBootsMinorSpeed,
        EnchantBootsGreaterAgility,
        EnchantBootsAgility,
        EnchantBootsSpirit,
        ElementalSharpeningStone,
        ConsecratedSharpeningStone,
        DenseSharpeningStone,
        LesserManaOil,
        BrilliantManaOil,
        BrilliantWizardOil,
        ShadowOil,
        SolidWeightstone,
        DenseWeightstone,
    };

    Q_ENUM(Name)

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
        case EnchantName::EnchantWeaponSpellPower:
            return "Spell Power";
        case EnchantName::EnchantBracerGreaterIntellect:
            return "Greater Intellect";
        case EnchantName::EnchantBracerManaRegeneration:
            return "Mana Regeneration";
        case EnchantName::EnchantBracerMinorAgility:
            return "Minor Agility";
        case EnchantName::EnchantBracerGreaterStrength:
            return "Greater Strength";
        case EnchantName::EnchantBracerSuperiorStrength:
            return "Superior Strength";
        case EnchantName::EnchantGlovesSuperiorAgility:
            return "Superior Agility";
        case EnchantName::EnchantGlovesGreaterAgility:
            return "Greater Agility";
        case EnchantName::EnchantGlovesGreaterStrength:
            return "Greater Strength";
        case EnchantName::EnchantGlovesMinorHaste:
            return "Minor Haste";
        case EnchantName::EnchantGlovesFirePower:
            return "Fire Power";
        case EnchantName::EnchantGlovesFrostPower:
            return "Frost Power";
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
        case EnchantName::ArcanumOfFocus:
            return "Arcanum of Focus";
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
        case EnchantName::PresenceOfSight:
            return "Presence of Sight";
        case EnchantName::EnchantCloakLesserAgility:
            return "Lesser Agility";
        case EnchantName::ZandalarSignetOfMight:
            return "Zandalar Signet of Might";
        case EnchantName::ZandalarSignetOfMojo:
            return "Zandalar Signet of Mojo";
        case EnchantName::MightOfTheScourge:
            return "Might of the Scourge";
        case EnchantName::EnchantChestStats:
            return "Stats";
        case EnchantName::EnchantChestGreaterStats:
            return "Greater Stats";
        case EnchantName::EnchantBootsMinorSpeed:
            return "Minor Speed";
        case EnchantName::EnchantBootsAgility:
            return "Agility";
        case EnchantName::EnchantBootsGreaterAgility:
            return "Greater Agility";
        case EnchantName::EnchantBootsSpirit:
            return "Spirit";
        case EnchantName::ElementalSharpeningStone:
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
        case EnchantName::ShadowOil:
            return "Shadow Oil";
        case EnchantName::SolidWeightstone:
            return "Solid Weightstone";
        case EnchantName::DenseWeightstone:
            return "Dense Weightstone";
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
        case EnchantName::EnchantWeaponSpellPower:
            return "+30 Spell Damage/Healing";
        case EnchantName::EnchantBracerGreaterIntellect:
            return "+7 Intellect";
        case EnchantName::EnchantBracerManaRegeneration:
            return "+4 mp5";
        case EnchantName::EnchantBracerMinorAgility:
            return "+1 Agility";
        case EnchantName::EnchantBracerGreaterStrength:
            return "+7 Strength";
        case EnchantName::EnchantBracerSuperiorStrength:
            return "+9 Strength";
        case EnchantName::EnchantGlovesSuperiorAgility:
            return "+15 Agility";
        case EnchantName::EnchantGlovesGreaterAgility:
            return "+7 Agility";
        case EnchantName::EnchantGlovesGreaterStrength:
            return "+7 Strength";
        case EnchantName::EnchantGlovesMinorHaste:
            return "+1% Attack Speed";
        case EnchantName::EnchantGlovesFirePower:
            return "+20 Fire Damage";
        case EnchantName::EnchantGlovesFrostPower:
            return "+20 Frost Damage";
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
        case EnchantName::ArcanumOfFocus:
            return "+8 Spell Damage/Healing";
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
        case EnchantName::PresenceOfSight:
            return "+18 Spell Damage/Healing\n+1% Spell Hit";
        case EnchantName::FalconsCall:
            return "+24 Ranged Attack Power\n10 Stamina, +1% Hit";
        case EnchantName::EnchantCloakLesserAgility:
            return "+3 Agility";
        case EnchantName::ZandalarSignetOfMight:
            return "+30 Attack Power";
        case EnchantName::ZandalarSignetOfMojo:
            return "+18 Spell Damage/Healing";
        case EnchantName::MightOfTheScourge:
            return "+1% Crit and\n+26 Attack Power";
        case EnchantName::EnchantChestStats:
            return "+3 Attributes";
        case EnchantName::EnchantChestGreaterStats:
            return "+4 Attributes";
        case EnchantName::EnchantBootsMinorSpeed:
            return "Speed Increase";
        case EnchantName::EnchantBootsAgility:
            return "+5 Agility";
        case EnchantName::EnchantBootsGreaterAgility:
            return "+7 Agility";
        case EnchantName::EnchantBootsSpirit:
            return "+5 Spirit";
        case EnchantName::ElementalSharpeningStone:
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
        case EnchantName::ShadowOil:
            return "15% R3 Shadow Bolt";
        case EnchantName::SolidWeightstone:
            return "+6 Damage";
        case EnchantName::DenseWeightstone:
            return "+8 Damage";
        }

        check(false, "EnchantName::get_effect reached end of switch");
        return "";
    }
};
