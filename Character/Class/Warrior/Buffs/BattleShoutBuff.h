#ifndef BATTLESHOUTBUFF_H
#define BATTLESHOUTBUFF_H

#include "Buff.h"
#include <QVector>

class BattleShoutBuff: public Buff {
public:
    BattleShoutBuff(Character* pchar): Buff(pchar, "Battle Shout", 120, 0) {
        spell_ranks = {15, 35, 55, 85, 130, 185, 232};
        // TODO: Remove hardcoded rank 7 Battle Shout.
        rank_spell = 6;
        base_ap = spell_ranks[rank_spell];

        rank_booming_voice = 0;
        rank_imp_shout = 0;

        base_duration = duration;

        ranks_booming_voice = {1.0, 1.1, 1.2, 1.3, 1.4, 1.5};
        ranks_imp_shout = {1.0, 1.05, 1.10, 1.15, 1.20, 1.25};
    }

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

    void increase_effect_via_booming_voice();
    void decrease_effect_via_booming_voice();

    void increase_effect_via_imp_shout();
    void decrease_effect_via_imp_shout();

protected:
private:
    QVector<int> spell_ranks;
    QVector<double> ranks_booming_voice;
    QVector<double> ranks_imp_shout;
    int rank_spell;
    int base_duration;
    int base_ap;
    int rank_booming_voice;
    int rank_imp_shout;
};

#endif // BATTLESHOUTBUFF_H
