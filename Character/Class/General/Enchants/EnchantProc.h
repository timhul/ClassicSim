#ifndef ENCHANTPROC_H
#define ENCHANTPROC_H

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

#endif // ENCHANTPROC_H
