#ifndef DEEPWOUNDS_H
#define DEEPWOUNDS_H

#include "Spell.h"
#include <QVector>

class Warrior;

class DeepWounds: public Spell {
public:
    DeepWounds(Engine* engine, Character* pchar, CombatRoll* roll);

    int spell_effect(const int) override;
    void apply_debuff();
protected:
private:
    Warrior* pchar;
    QVector<int> stacks;
};

#endif // DEEPWOUNDS_H
