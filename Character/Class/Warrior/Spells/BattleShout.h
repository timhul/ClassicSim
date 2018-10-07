#ifndef BATTLESHOUT_H
#define BATTLESHOUT_H

#include "Spell.h"

class Warrior;

class BattleShout: public Spell {
public:
    BattleShout(Character* pchar);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
};

#endif // BATTLESHOUT_H
