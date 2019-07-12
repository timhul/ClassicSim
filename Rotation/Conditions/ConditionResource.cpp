#include "ConditionResource.h"

#include "Character.h"
#include "Utils/Check.h"

ConditionResource::ConditionResource(Character* pchar, const Comparator comparator, const ResourceType resource_type, const double cmp_value) :
    Condition(comparator),
    pchar(pchar),
    resource_type(resource_type),
    cmp_value(cmp_value)
{}

bool ConditionResource::condition_fulfilled() const {
    const unsigned resource = pchar->get_resource_level(resource_type);

    switch (comparator) {
    case Comparator::Less:
    case Comparator::Leq:
        return resource < cmp_value;
    case Comparator::Eq:
        return (resource - cmp_value) < 0.000001;
    case Comparator::Geq:
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
