#ifndef CONDITIONRESOURCE_H
#define CONDITIONRESOURCE_H

#include "Condition.h"

#include "Resource.h"

class Character;

class ConditionResource : public Condition {
public:
    ConditionResource(Character* pchar, const int comparator, const ResourceType resource_type, const double cmp_value);

    bool condition_fulfilled() const override;
    QString condition_description() const override;

    const Character* pchar;
    const ResourceType resource_type;
    const double cmp_value;

private:
    QString name_for_resource() const;
};

#endif // CONDITIONRESOURCE_H
