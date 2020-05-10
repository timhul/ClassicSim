#pragma once

#include "Spell.h"

class Buff;
class Mage;

class MageArmor : public Spell{
public:
    MageArmor(Mage* pchar);
    ~MageArmor() override;

private:
    Buff* buff;

    void spell_effect() override;
};
