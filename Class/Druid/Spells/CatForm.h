#pragma once

#include "Spell.h"

class Buff;
class Druid;

class CatForm: public Spell {
public:
    CatForm(Character* pchar);
    ~CatForm() override;

private:
    friend class Druid;

    Druid* druid;

    Buff* buff;

    SpellStatus is_ready_spell_specific() const override;
    void spell_effect() override;
};
