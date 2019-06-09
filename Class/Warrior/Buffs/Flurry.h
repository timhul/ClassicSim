#ifndef FLURRY_H
#define FLURRY_H

#include "SelfBuff.h"
#include "TalentRequirer.h"

#include <QVector>

class Flurry: public SelfBuff, public TalentRequirer {
public:
    Flurry(Character* pchar);

private:
    QVector<unsigned> rank_talents;
    unsigned attack_speed_increase;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // FLURRY_H
