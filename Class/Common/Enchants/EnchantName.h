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
