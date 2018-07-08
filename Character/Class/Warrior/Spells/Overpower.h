#ifndef OVERPOWER_H
#define OVERPOWER_H

#include "Spell.h"

class Warrior;

class Overpower: public Spell {
public:
    Overpower(Engine* engine, Character* pchar, CombatRoll* roll);

    bool is_ready_spell_specific() const override;
    void spell_effect() override;

protected:
private:
    Warrior* pchar;
    QVector<float> talent_ranks;
};

#endif // OVERPOWER_H
