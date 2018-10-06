#ifndef BLOODRAGE_H
#define BLOODRAGE_H

#include "Spell.h"

class Warrior;

class Bloodrage: public Spell {
public:
    Bloodrage(Engine* engine, Character* pchar, CombatRoll* roll);

    void spell_effect() override;
    void periodic_effect() override;

protected:
private:
    Warrior* warr;
    QVector<int> talent_ranks;
    int periodic_rage_base;
    int periodic_rage_current;

    bool is_ready_spell_specific() const override;
};

#endif // BLOODRAGE_H
