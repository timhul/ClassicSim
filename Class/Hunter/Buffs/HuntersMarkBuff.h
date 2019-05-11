#ifndef HUNTERSMARKBUFF_H
#define HUNTERSMARKBUFF_H

#include "Buff.h"
#include "TalentRequirer.h"

#include <QVector>

class HuntersMarkBuff: public Buff, public TalentRequirer {
public:
    HuntersMarkBuff(Character* pchar);

private:
    QVector<double> imp_hunters_mark_ranks;
    unsigned hunters_mark_bonus;
    const unsigned base_ranged_ap_bonus;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // HUNTERSMARKBUFF_H
