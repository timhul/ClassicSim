#ifndef RECKLESSNESS_H
#define RECKLESSNESS_H

#include "Spell.h"

class Recklessness: public Spell {
public:
    Recklessness(Character* pchar);

protected:
private:
    void spell_effect() override;
    SpellStatus is_ready_spell_specific() const override;
};

#endif // RECKLESSNESS_H
