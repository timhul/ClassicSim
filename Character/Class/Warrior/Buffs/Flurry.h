#ifndef FLURRY_H
#define FLURRY_H

#include "Buff.h"
#include <QVector>

class Flurry: public Buff {
public:
    Flurry(Character* pchar): Buff(pchar, "Flurry", 15.0, 3) {
        rank_talent = 0;
        rank_talents = {0, 10, 15, 20, 25, 30};
    }

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
    QVector<int> rank_talents;
};




#endif // FLURRY_H
