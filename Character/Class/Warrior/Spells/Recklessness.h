#ifndef RECKLESSNESS_H
#define RECKLESSNESS_H

#include "Spell.h"
#include "CooldownReady.h"

class Recklessness: public Spell {
public:
    Recklessness(Engine* engine, Character* pchar) :
        Spell("Recklessness", engine, pchar, 1800.0, 0) {}

    int spell_effect(const int) const override;
protected:
private:
};

#endif // RECKLESSNESS_H
