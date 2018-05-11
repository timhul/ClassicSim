#ifndef DEATHWISHBUFF_H
#define DEATHWISHBUFF_H

#include "Buff.h"
#include <QVector>

class DeathWishBuff: public Buff {
public:
    DeathWishBuff(Character* pchar): Buff(pchar, "Death Wish", 30, 0) {
        rank_talent = 0;
        rank_talents = {0, 20};
    }

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
    QVector<int> rank_talents;
};

#endif // DEATHWISHBUFF_H
