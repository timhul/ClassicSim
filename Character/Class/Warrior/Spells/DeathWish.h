#ifndef DEATHWISH_H
#define DEATHWISH_H

#include "Spell.h"

class Warrior;

class DeathWish: public Spell {
public:
    DeathWish(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    Warrior* warr;

    void spell_effect() override;
    void enable_spell_effect() override;
    void disable_spell_effect() override;
};

#endif // DEATHWISH_H
