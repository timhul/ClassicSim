#ifndef EXECUTE_H
#define EXECUTE_H

#include "Spell.h"

class Warrior;

class Execute: public Spell {
public:
    Execute(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;
protected:
private:
    Warrior* pchar;
    QVector<int> spell_ranks;
    QVector<int> talent_ranks;
};

#endif // EXECUTE_H
