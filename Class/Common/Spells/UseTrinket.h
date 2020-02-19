#pragma once

#include "Spell.h"

class Buff;
class Proc;

class UseTrinket : public Spell {
public:
    UseTrinket(Character* pchar, const QString& name, const QString& icon, const int cooldown, Buff* buff = nullptr, Proc* proc = nullptr);
    ~UseTrinket() override;

private:
    Buff* buff;
    Proc* proc;

    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};
