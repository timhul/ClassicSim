#ifndef BATTLESHOUT_H
#define BATTLESHOUT_H

#include "Spell.h"

class Warrior;

class BattleShout: public Spell {
public:
    BattleShout(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;

protected:
private:
    Warrior* warr;
};

#endif // BATTLESHOUT_H
