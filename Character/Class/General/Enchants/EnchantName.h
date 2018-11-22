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
};

#endif // ENCHANTSTATICNAME_H
