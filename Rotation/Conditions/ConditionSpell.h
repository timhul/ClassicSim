#pragma once

#include "Condition.h"

class Spell;

class ConditionSpell : public Condition {
public:
    ConditionSpell(Spell* spell, const int comparator, const double cmp_value);

    bool condition_fulfilled() const override;
    QString condition_description() const override;

private:
    Spell* spell;
    const double cmp_value;
};
