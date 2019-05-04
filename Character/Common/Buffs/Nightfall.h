#ifndef NIGHTFALL_H
#define NIGHTFALL_H

#include "Buff.h"

class Nightfall: public Buff {
public:
    Nightfall(Character* pchar);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // NIGHTFALL_H
