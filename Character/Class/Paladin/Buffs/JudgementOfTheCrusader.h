#ifndef JUDGEMENTOFTHECRUSADER_H
#define JUDGEMENTOFTHECRUSADER_H

#include "Buff.h"
#include "TalentRequirer.h"

#include <QVector>

class Paladin;

class JudgementOfTheCrusader: public Buff, public TalentRequirer {
public:
    JudgementOfTheCrusader(Paladin* pchar);

private:
    Paladin* paladin;

    unsigned holy_damage_bonus;
    const unsigned holy_damage_base {140};
    const QVector<double> improved_sotc_ranks {1.0, 1.05, 1.10, 1.15};

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // JUDGEMENTOFTHECRUSADER_H
