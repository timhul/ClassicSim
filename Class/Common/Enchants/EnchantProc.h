#pragma once

#include "Enchant.h"
#include "EnchantName.h"

class Character;
class Proc;

class EnchantProc : public Enchant {
public:
    EnchantProc(EnchantName::Name enchant, Character* pchar, const int slot);
    ~EnchantProc() override;

private:
    Character* pchar;
    Proc* proc;
};
