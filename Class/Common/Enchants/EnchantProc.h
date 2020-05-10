#pragma once

#include "Enchant.h"
#include "EnchantName.h"

class Character;
class Proc;

class EnchantProc : public Enchant {
public:
    EnchantProc(EnchantName::Name enchant, Character* pchar, EnchantInfo* enchant_info, const int slot);
    ~EnchantProc() override;

    void enable_proc();
    void disable_proc();
    bool proc_enabled() const;

private:
    Character* pchar;
    Proc* proc;
};
