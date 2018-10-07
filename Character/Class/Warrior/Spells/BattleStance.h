#ifndef BATTLESTANCE_H
#define BATTLESTANCE_H

#include "Spell.h"

class Warrior;

class BattleStance: public Spell {
public:
    BattleStance(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;
};

#endif // BATTLESTANCE_H
