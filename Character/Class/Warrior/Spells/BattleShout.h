#ifndef BATTLESHOUT_H
#define BATTLESHOUT_H

#include "Spell.h"

class Warrior;
class WarriorSpells;

class BattleShout: public Spell {
public:
    BattleShout(Warrior* pchar, WarriorSpells* spells);

private:
    Warrior* warr;
    WarriorSpells* spells;

    void spell_effect() override;
};

#endif // BATTLESHOUT_H
