#pragma once

#include <QObject>
#include <QVector>

#include "Utils/Check.h"

class EnchantName : public QObject {
    Q_OBJECT

public:
    enum Name
    {
        NoEnchant = -1,
        ArcanumOfFocus,
        ArcanumOfRapidity,
        Biznicks247x128Accurascope,
        BrilliantManaOil,
        BrilliantWizardOil,
        ConsecratedSharpeningStone,
        Crusader,
        DeathsEmbrace,
        DenseSharpeningStone,
        DenseWeightstone,
        ElementalSharpeningStone,
        Enchant2HWeaponAgility,
        Enchant2HWeaponSuperiorImpact,
        EnchantBootsAgility,
        EnchantBootsGreaterAgility,
        EnchantBootsMinorSpeed,
        EnchantBootsSpirit,
        EnchantBracerGreaterIntellect,
        EnchantBracerGreaterStrength,
        EnchantBracerManaRegeneration,
        EnchantBracerMinorAgility,
        EnchantBracerSuperiorStrength,
        EnchantChestGreaterStats,
        EnchantChestMajorMana,
        EnchantChestStats,
        EnchantCloakLesserAgility,
        EnchantGlovesFirePower,
        EnchantGlovesFrostPower,
        EnchantGlovesShadowPower,
        EnchantGlovesGreaterAgility,
        EnchantGlovesGreaterStrength,
        EnchantGlovesMinorHaste,
        EnchantGlovesSuperiorAgility,
        EnchantWeaponAgility,
        EnchantWeaponSpellPower,
        EnchantWeaponStrength,
        FalconsCall,
        FieryWeapon,
        InstantPoison,
        IronCounterweight,
        LesserArcanumOfVoracityAgility,
        LesserArcanumOfVoracityIntellect,
        LesserArcanumOfVoracitySpirit,
        LesserArcanumOfVoracityStamina,
        LesserArcanumOfVoracityStrength,
        LesserManaOil,
        MightOfTheScourge,
        PowerOfTheScourge,
        PresenceOfSight,
        HoodooHex,
        ShadowOil,
        SniperScope,
        SolidWeightstone,
        SuperiorStriking,
        WindfuryTotem,
        ZandalarSignetOfMight,
        ZandalarSignetOfMojo,
    };

    Q_ENUM(Name)
};

class EnchantSpec {
public:
    EnchantSpec(const EnchantName::Name enum_name_, const QString& display_name_, const QString& unique_name_, const QString& effect_) :
        enum_name(enum_name_), display_name(display_name_), unique_name(unique_name_), effect(effect_) {}

    const EnchantName::Name enum_name;
    const QString display_name;
    const QString unique_name;
    const QString effect;
};

class EnchantInfo {
public:
    EnchantInfo();
    ~EnchantInfo();

    QString get_display_name(EnchantName::Name enum_val) const;
    QString get_unique_name(EnchantName::Name enum_val) const;
    QString get_effect(EnchantName::Name enum_val) const;
    EnchantName::Name get_enum_val(const QString& unique_name) const;

private:
    QVector<EnchantSpec*> enchant_specs;
};
