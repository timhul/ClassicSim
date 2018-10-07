#ifndef BERSERKERRAGE_H
#define BERSERKERRAGE_H

#include "Spell.h"

class Warrior;

class BerserkerRage: public Spell {
public:
    BerserkerRage(Engine* engine, Character* pchar, CombatRoll* roll);

protected:
private:
    Warrior* warr;
    QVector<int> talent_ranks;

    void spell_effect() override;
    bool is_ready_spell_specific() const override;
};

#endif // BERSERKERRAGE_H
