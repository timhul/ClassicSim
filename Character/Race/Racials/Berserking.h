#ifndef BERSERKING_H
#define BERSERKING_H

#include "Spell.h"

class Warrior;

class Berserking: public Spell {
public:
    Berserking(Engine* engine, Character* pchar, CombatRoll* roll);

    bool is_ready_spell_specific() const override;
    void spell_effect() override;

protected:
private:
    Warrior* pchar;

};

#endif // BERSERKING_H
