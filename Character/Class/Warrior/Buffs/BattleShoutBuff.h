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

protected:
private:
    friend class ImprovedBattleShout;
    friend class BoomingVoice;

    QVector<int> spell_ranks;
    QVector<double> ranks_booming_voice;
    QVector<double> ranks_imp_shout;
    int rank_spell;
    int base_duration;
    int base_attack_power;
    int modified_by_talents_attack_power;
    int rank_booming_voice;
    int rank_imp_shout;

    void increase_talent_rank_effect(const QString& talent_name) override;
    void decrease_talent_rank_effect(const QString& talent_name) override;
};

#endif // BATTLESHOUTBUFF_H
