#pragma once

#include "Spell.h"

class Buff;
class Druid;

class BearForm: public Spell {
public:
    BearForm(Character* pchar);
    ~BearForm() override;

private:
    friend class Druid;

    Druid* druid;

    Buff* buff;

    SpellStatus is_ready_spell_specific() const override;
    void spell_effect() override;
};
