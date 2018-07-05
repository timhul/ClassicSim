
#include "ConditionResource.h"
#include "Character.h"

ConditionResource::ConditionResource(Character* pchar, const int comparator, const float cmp_value) :
    pchar(pchar),
    comparator(comparator),
    cmp_value(cmp_value)
{}

bool ConditionResource::condition_fulfilled() const {
    const int resources = pchar->get_resource_level();

    switch (comparator) {
    case Comparators::less:
    case Comparators::leq:
        return resources < cmp_value;
    case Comparators::eq:
        return (resources - cmp_value) < 0.000001;
    case Comparators::geq:
    case Comparators::greater:
        return resources > cmp_value;
    }

    assert(false);
    return false;
}
