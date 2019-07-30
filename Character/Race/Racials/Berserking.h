#pragma once

#include "Spell.h"

class BerserkingBuff;

class Berserking: public Spell {
public:
    Berserking(Character* pchar, const ResourceType resource_type, const unsigned resource_cost);
    ~Berserking() override;

private:
    BerserkingBuff* buff;

    void spell_effect() override;
    void enable_spell_effect() override;
    void disable_spell_effect() override;
};
