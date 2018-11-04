#ifndef SIMOPTION_H
#define SIMOPTION_H

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
        ScaleWeaponSkill
    };

    Q_ENUMS(Name)
};

#endif // SIMOPTION_H
