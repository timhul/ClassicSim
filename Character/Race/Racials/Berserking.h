#ifndef BERSERKING_H
#define BERSERKING_H

#include "Spell.h"

class Character;

class Berserking: public Spell {
public:
    Berserking(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;

protected:

    void enable_spell_effect() override;
    void disable_spell_effect() override;

private:
};

#endif // BERSERKING_H
