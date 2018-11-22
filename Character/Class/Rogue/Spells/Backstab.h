#ifndef BACKSTAB_H
#define BACKSTAB_H

#include "Spell.h"

class Rogue;

class Backstab: public Spell {
public:
    Backstab(Character* pchar);

protected:
private:
    Rogue* rogue;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;
};

#endif // BACKSTAB_H
