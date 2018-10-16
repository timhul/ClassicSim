#ifndef ENCHANTSTATICNAME_H
#define ENCHANTSTATICNAME_H

#include <QObject>

class EnchantName : public QObject {
    Q_OBJECT

public:
    enum Name {
        Crusader = 0,
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
        EnchantChestGreaterStats
    };

    Q_ENUMS(Name)
};

#endif // ENCHANTSTATICNAME_H
