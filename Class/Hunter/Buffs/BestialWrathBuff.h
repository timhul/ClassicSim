#pragma once

#include "SelfBuff.h"

class Pet;

class BestialWrathBuff : public SelfBuff {
public:
    BestialWrathBuff(Character* pchar, const QString& pet_name);

private:
    void buff_effect_when_applied() override;
    void buff_effect_when_removed() override;
};
