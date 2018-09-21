#ifndef BATTLESTANCE_H
#define BATTLESTANCE_H

#include "Spell.h"

class Warrior;

class BattleStance: public Spell {
public:
    BattleStance(Engine* engine, Character* pchar, CombatRoll* roll);

    bool is_ready_spell_specific() const override;
    void spell_effect() override;
protected:
private:
    Warrior* warr;
};

#endif // BATTLESTANCE_H
