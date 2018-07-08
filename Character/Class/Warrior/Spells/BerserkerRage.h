#ifndef BERSERKERRAGE_H
#define BERSERKERRAGE_H

#include "Spell.h"

class Warrior;

class BerserkerRage: public Spell {
public:
    BerserkerRage(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;
    bool is_ready_spell_specific() const override;

protected:
private:
    Warrior* pchar;
    QVector<int> talent_ranks;
};

#endif // BERSERKERRAGE_H
