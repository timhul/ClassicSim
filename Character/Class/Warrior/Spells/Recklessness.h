#ifndef RECKLESSNESS_H
#define RECKLESSNESS_H

#include "Spell.h"

class Recklessness: public Spell {
public:
    Recklessness(Engine* engine, Character* pchar, CombatRoll* roll) :
        Spell("Recklessness", engine, pchar, roll, true, 1800.0, 0) {}

    void spell_effect() override;
protected:
private:
    bool is_ready_spell_specific() const override;
};

#endif // RECKLESSNESS_H
