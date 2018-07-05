#ifndef CONDITIONSPELL_H
#define CONDITIONSPELL_H

#include "Condition.h"

class Spell;

class ConditionSpell : public Condition {
public:
    ConditionSpell(Spell* spell, const int comparator, const float cmp_value);

    bool condition_fulfilled() const override;

private:
    Spell* spell;
    const int comparator;
    const float cmp_value;
};

#endif // CONDITIONSPELL_H
