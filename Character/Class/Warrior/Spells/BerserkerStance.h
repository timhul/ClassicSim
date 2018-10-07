#ifndef BERSERKERSTANCE_H
#define BERSERKERSTANCE_H

#include "Spell.h"

class Warrior;

class BerserkerStance: public Spell {
public:
    BerserkerStance(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    Warrior* warr;

    bool is_ready_spell_specific() const override;
    void spell_effect() override;
};

#endif // BERSERKERSTANCE_H
