#pragma once

#include "Spell.h"

class Buff;
class Proc;

class UseItem : public Spell {
public:
    UseItem(Character* pchar, const QString& name, const QString& icon, const int cooldown, Buff* buff = nullptr, Proc* proc = nullptr);
    ~UseItem() override;

private:
    Buff* buff;
    Proc* proc;

    void spell_effect() override;
};
