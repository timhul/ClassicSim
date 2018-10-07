#ifndef DEEPWOUNDS_H
#define DEEPWOUNDS_H

#include "Spell.h"
#include <QVector>

class Warrior;

class DeepWounds: public Spell {
public:
    DeepWounds(Engine* engine, Character* pchar, CombatRoll* roll);

    void apply_debuff();

protected:
private:
    Warrior* warr;
    double previous_tick_rest;
    QVector<int> stacks;
    QVector<double> ranks;

    void spell_effect() override;
    void reset_effect() override;
};

#endif // DEEPWOUNDS_H
