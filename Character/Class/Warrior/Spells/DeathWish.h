#ifndef DEATHWISH_H
#define DEATHWISH_H

#include "Spell.h"

class Warrior;

class DeathWish: public Spell {
public:
    DeathWish(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;
protected:
private:
    Warrior* pchar;

};

#endif // DEATHWISH_H
