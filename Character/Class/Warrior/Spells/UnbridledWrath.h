#ifndef UNBRIDLEDWRATH_H
#define UNBRIDLEDWRATH_H

#include "Spell.h"

class Warrior;

class UnbridledWrath: public Spell {
public:
    UnbridledWrath(Engine* engine, Character* pchar, CombatRoll* roll);
    ~UnbridledWrath();

    int spell_effect(const int) override;
    void increase_effect_via_talent() override;
    void decrease_effect_via_talent() override;

protected:
private:
    Warrior* pchar;
    Random* random;
    QVector<int> talent_ranks;
    int proc_range;
};

#endif // UNBRIDLEDWRATH_H
