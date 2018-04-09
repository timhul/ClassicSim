#ifndef BERSERKERRAGE_H
#define BERSERKERRAGE_H

#include "Spell.h"

class Warrior;

class BerserkerRage: public Spell {
public:
    BerserkerRage(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;

protected:
private:
    Warrior* pchar;
    QVector<int> talent_ranks;
};

#endif // BERSERKERRAGE_H
