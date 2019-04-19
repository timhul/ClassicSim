#include "ConditionBuff.h"

#include "Buff.h"
#include "Utils/Check.h"

ConditionBuff::ConditionBuff(Buff* buff, const int comparator, const double cmp_value) :
    Condition(comparator),
    buff(buff),
    cmp_value(cmp_value)
{}

bool ConditionBuff::condition_fulfilled() const {
    switch (comparator) {
    case Comparators::less:
    case Comparators::leq:
        return buff->time_left() < cmp_value;
    case Comparators::eq:
        return (buff->time_left() - cmp_value) < 0.000001;
    case Comparators::geq:
    case Comparators::greater:
        return buff->time_left() > cmp_value;
    case Comparators::false_val:
        return !buff->is_active();
    case Comparators::true_val:
        return buff->is_active();
    default:
        check(false, "ConditionBuff::condition_fulfilled reached end of switch");
        return false;
    }
}

QString ConditionBuff::condition_description() const {
    return QString("%1 buff remaining %2 %3 seconds").arg(buff->get_name()).arg(comparator_as_string()).arg(QString::number(cmp_value, 'f', 1));
}
