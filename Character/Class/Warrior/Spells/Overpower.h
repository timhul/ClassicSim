#ifndef OVERPOWER_H
#define OVERPOWER_H

#include "Spell.h"

class Warrior;

class Overpower: public Spell {
public:
    Overpower(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;
protected:
private:
    Warrior* pchar;
    QVector<float> talent_ranks;
};

#endif // OVERPOWER_H
