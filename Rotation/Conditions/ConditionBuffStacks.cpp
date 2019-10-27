#include "ConditionBuffStacks.h"

#include "Buff.h"
#include "Utils/Check.h"

ConditionBuffStacks::ConditionBuffStacks(Buff* buff, const Comparator comparator, const int cmp_value) :
    Condition(comparator),
    buff(buff),
    cmp_value(cmp_value)
{}

bool ConditionBuffStacks::condition_fulfilled() const {
    switch (comparator) {
    case Comparator::Less:
        return buff->get_stacks() < cmp_value;
    case Comparator::Leq:
        return buff->get_stacks() <= cmp_value;
    case Comparator::Eq:
        return buff->get_stacks() == cmp_value;
    case Comparator::Geq:
        return buff->get_stacks() >= cmp_value;
    case Comparator::Greater:
        return buff->get_stacks() > cmp_value;
    case Comparator::False:
        return buff->get_stacks() == 0;
    case Comparator::True:
        return buff->get_stacks() > 0;
    }

    return false;
}

QString ConditionBuffStacks::condition_description() const {
    return QString("%1 buff stacks %2 %3").arg(buff->name).arg(comparator_as_string()).arg(cmp_value);
}
