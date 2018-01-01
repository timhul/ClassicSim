#ifndef BLOODTHIRST_H
#define BLOODTHIRST_H

#include "Spell.h"
#include "CooldownReady.h"

class Bloodthirst: public Spell {
public:
    Bloodthirst(Engine* engine, Character* pchar, CombatRoll* roll) :
        Spell("Bloodthirst", engine, pchar, roll, 6.0, 30) {}

    int spell_effect(const int) const override;
    void add_success_stats(std::string, const int) const;
protected:
private:
};

#endif // BLOODTHIRST_H
