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
        WindfuryTotem,
        EnchantBracerSuperiorStrength,
        EnchantGlovesGreaterStrength,
        EnchantGlovesMinorHaste,
        IronCounterweight,
        Enchant2HWeaponAgility,
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
