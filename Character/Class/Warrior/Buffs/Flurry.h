#ifndef FLURRY_H
#define FLURRY_H

#include "Buff.h"
#include <QVector>

class Flurry: public Buff {
public:
    Flurry(Character* pchar);

protected:
private:
    QVector<int> rank_talents;

    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};




#endif // FLURRY_H
