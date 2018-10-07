#ifndef BATTLESHOUT_H
#define BATTLESHOUT_H

#include "Spell.h"

class Warrior;

class BattleShout: public Spell {
public:
    BattleShout(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
};

#endif // BATTLESHOUT_H
