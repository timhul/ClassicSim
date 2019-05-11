#ifndef BESTIALWRATHBUFF_H
#define BESTIALWRATHBUFF_H

#include "Buff.h"

class Pet;

class BestialWrathBuff: public Buff {
public:
    BestialWrathBuff(Character* pchar, const QString& pet_name);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};

#endif // BESTIALWRATHBUFF_H
