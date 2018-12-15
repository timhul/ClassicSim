#ifndef ENCHANTSTATICNAME_H
#define ENCHANTSTATICNAME_H

#include <QObject>

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
        InstantPoison,
        WindfuryTotem,
        EnchantBracerSuperiorStrength,
        EnchantGlovesSuperiorAgility,
        EnchantGlovesGreaterStrength,
        EnchantGlovesMinorHaste,
        ArcanumOfRapidity,
        LesserArcanumOfVoracity,
        EnchantCloakLesserAgility,
        ZandalarSignetOfMight,
        MightOfTheScourge,
        EnchantChestGreaterStats,
        EnchantBootsMinorSpeed,
        EnchantBootsGreaterAgility,
        ElementalSharpeningStone
    };

    Q_ENUMS(Name)

    static QString get_name(Name enchant) {
        switch (enchant) {
        case EnchantName::NoEnchant:
            assert(false);
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
        case EnchantName::EnchantBootsMinorSpeed:
            return "Minor Speed";
        case EnchantName:: EnchantBootsGreaterAgility:
            return "Greater Agility";
        case EnchantName:: ElementalSharpeningStone:
            return "Elemental Sharpening Stone";
        }

        assert(false);
        return "";
    }

    static QString get_effect(Name enchant) {
        switch (enchant) {
        case EnchantName::NoEnchant:
            assert(false);
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
        case EnchantName::EnchantBootsMinorSpeed:
            return "Speed Increase";
        case EnchantName:: EnchantBootsGreaterAgility:
            return "+7 Agility";
        case EnchantName:: ElementalSharpeningStone:
            return "+2% Crit";
        }

        assert(false);
        return "";
    }
};

#endif // ENCHANTSTATICNAME_H
