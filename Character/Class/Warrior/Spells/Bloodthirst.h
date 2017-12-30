#ifndef BLOODTHIRST_H
#define BLOODTHIRST_H

#include "Spell.h"
#include "CooldownReady.h"

class Bloodthirst: public Spell {
public:
    Bloodthirst(Engine* engine, Character* pchar) :
        Spell("Bloodthirst", engine, pchar, 6.0, 30) {}

    int spell_effect(const int) const override;
protected:
private:
};

#endif // BLOODTHIRST_H
