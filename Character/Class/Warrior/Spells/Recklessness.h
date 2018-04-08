#ifndef RECKLESSNESS_H
#define RECKLESSNESS_H

#include "Spell.h"

class Recklessness: public Spell {
public:
    Recklessness(Engine* engine, Character* pchar, CombatRoll* roll) :
        Spell("Recklessness", engine, pchar, roll, 1800.0, 0) {}

    int spell_effect(const int) override;
protected:
private:
};

#endif // RECKLESSNESS_H
