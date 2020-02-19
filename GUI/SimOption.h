#pragma once

#include <QObject>
#include <QString>

class SimOption : public QObject {
    Q_OBJECT

public:
    enum Name
    {
        NoScale = -1,
        ScaleAgility,
        ScaleStrength,
        ScaleHitChance,
        ScaleCritChance,
        ScaleMeleeAP,
        ScaleAxeSkill,
        ScaleDaggerSkill,
        ScaleMaceSkill,
        ScaleSwordSkill,
        ScaleIntellect,
        ScaleSpirit,
        ScaleMp5,
        ScaleSpellDamage,
        ScaleSpellCritChance,
        ScaleSpellHitChance,
        ScaleSpellPenetration,
    };

    Q_ENUM(Name)
};
