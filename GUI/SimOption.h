#pragma once

#include <QObject>
#include <QString>

class SimOption : public QObject {
    Q_OBJECT

public:
    enum Name {
        NoScale = -1,
        ScaleAgility,
        ScaleStrength,
        ScaleHitChance,
        ScaleCritChance,
        ScaleMeleeAP,
        ScaleAxeSkill,
        ScaleDaggerSkill,
        ScaleMaceSkill,
        ScaleSwordSkill
    };

    Q_ENUMS(Name)
};
