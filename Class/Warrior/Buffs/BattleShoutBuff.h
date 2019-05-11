#ifndef BATTLESHOUTBUFF_H
#define BATTLESHOUTBUFF_H

#include "Buff.h"
#include "TalentRequirer.h"

#include <QVector>

class BattleShoutBuff: public Buff, public TalentRequirer {
public:
    BattleShoutBuff(Character* pchar);

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

private:
    QVector<unsigned> spell_ranks;
    QVector<double> ranks_booming_voice;
    QVector<double> ranks_imp_shout;
    int rank_spell;
    int base_duration;
    unsigned base_attack_power;
    unsigned modified_by_talents_attack_power;

    void increase_talent_rank_effect(const QString& talent_name, const int curr) override;
    void decrease_talent_rank_effect(const QString& talent_name, const int curr) override;
};

#endif // BATTLESHOUTBUFF_H
