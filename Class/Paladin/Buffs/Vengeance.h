#ifndef VENGEANCE_H
#define VENGEANCE_H

#include "SelfBuff.h"
#include "TalentRequirer.h"

#include <QVector>

class Paladin;

class Vengeance: public SelfBuff, public TalentRequirer {
public:
    Vengeance(Paladin* pchar);
    ~Vengeance() override = default;

private:
    Paladin* paladin;

    int dmg_bonus {0};
    QVector<int> dmg_bonuses;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // VENGEANCE_H
