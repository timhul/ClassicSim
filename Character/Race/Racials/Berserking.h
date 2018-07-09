#ifndef BERSERKING_H
#define BERSERKING_H

#include "Spell.h"

class Character;

class Berserking: public Spell {
public:
    Berserking(Engine* engine, Character* pchar, CombatRoll* roll);

    bool is_ready_spell_specific() const override;
    void spell_effect() override;

protected:
private:
};

#endif // BERSERKING_H
