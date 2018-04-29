#ifndef BLOODRAGE_H
#define BLOODRAGE_H

#include "Spell.h"

class Warrior;

class Bloodrage: public Spell {
public:
    Bloodrage(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;
    void periodic_effect() override;

protected:
private:
    Warrior* pchar;
    QVector<int> talent_ranks;
    int periodic_rage_base;
    int periodic_rage_current;
};

#endif // BLOODRAGE_H
