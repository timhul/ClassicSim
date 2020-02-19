#include "ConditionResource.h"

#include "Character.h"
#include "Utils/Check.h"
#include "Utils/CompareDouble.h"

ConditionResource::ConditionResource(Character* pchar, const Comparator comparator_, const ResourceType resource_type, const double cmp_value) :
    Condition(comparator_), pchar(pchar), resource_type(resource_type), cmp_value(cmp_value) {}

bool ConditionResource::condition_fulfilled() const {
    const unsigned resource = pchar->get_resource_level(resource_type);

    switch (comparator) {
    case Comparator::Less:
        return resource < cmp_value;
    case Comparator::Leq:
        return resource < cmp_value || almost_equal(resource, cmp_value);
    case Comparator::Eq:
        return almost_equal(resource, cmp_value);
    case Comparator::Geq:
        return resource > cmp_value || almost_equal(resource, cmp_value);
    case Comparator::Greater:
        return resource > cmp_value;
    default:
        check(false, "ConditionResource::condition_fulfilled reached end of switch");
        return false;
    }
}

QString ConditionResource::condition_description() const {
    return QString("%1 %2 %3").arg(name_for_resource()).arg(comparator_as_string()).arg(QString::number(cmp_value, 'f', 0));
}

QString ConditionResource::name_for_resource() const {
    switch (resource_type) {
    case ResourceType::Energy:
        return "Energy";
    case ResourceType::Focus:
        return "Focus";
    case ResourceType::Mana:
        return "Mana";
    case ResourceType::Rage:
        return "Rage";
    }

    return "<unknown resource";
}
