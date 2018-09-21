#ifndef CONDITIONRESOURCE_H
#define CONDITIONRESOURCE_H

#include "Condition.h"

class Character;

class ConditionResource : public Condition {
public:
    ConditionResource(Character* pchar, const int comparator, const double cmp_value);

    bool condition_fulfilled() const override;

private:
    const Character* pchar;
    const int comparator;
    const double cmp_value;
};

#endif // CONDITIONRESOURCE_H
