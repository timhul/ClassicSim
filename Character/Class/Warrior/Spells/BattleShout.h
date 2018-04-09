#ifndef BATTLESHOUT_H
#define BATTLESHOUT_H

#include "Spell.h"

class Warrior;

class BattleShout: public Spell {
public:
    BattleShout(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;

protected:
private:
    Warrior* pchar;
};

#endif // BATTLESHOUT_H
