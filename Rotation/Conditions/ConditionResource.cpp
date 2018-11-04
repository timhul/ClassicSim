
#include "ConditionResource.h"
#include "Character.h"

ConditionResource::ConditionResource(Character* pchar, const int comparator, const Resource resource_type, const double cmp_value) :
    pchar(pchar),
    comparator(comparator),
    resource_type(resource_type),
    cmp_value(cmp_value)
{}

bool ConditionResource::condition_fulfilled() const {
    const unsigned resource = pchar->get_resource_level(resource_type);

    switch (comparator) {
    case Comparators::less:
    case Comparators::leq:
        return resource < cmp_value;
    case Comparators::eq:
        return (resource - cmp_value) < 0.000001;
    case Comparators::geq:
    case Comparators::greater:
        return resource > cmp_value;
    }

    assert(false);
    return false;
}
