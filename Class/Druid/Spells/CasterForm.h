#pragma once

#include "Spell.h"

class Buff;
class Druid;

class CasterForm : public Spell {
public:
    CasterForm(Druid* druid);
    ~CasterForm() override;

private:
    friend class Druid;

    Druid* druid;
    Buff* buff;

    SpellStatus is_ready_spell_specific() const override;
    void spell_effect() override;
};
