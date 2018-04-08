#ifndef FLURRY_H
#define FLURRY_H

#include "Buff.h"
#include <QVector>

class Flurry: public Buff {
public:
    Flurry(Character* pchar): Buff(pchar, "Flurry", 15.0, 3) {
        rank = 0;
        ranks = {10, 15, 20, 25, 30};
    }

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;

protected:
private:
    QVector<int> ranks;
};




#endif // FLURRY_H
