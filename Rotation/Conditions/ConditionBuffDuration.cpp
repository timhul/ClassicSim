#include "ConditionBuffDuration.h"

#include "Buff.h"
#include "Utils/Check.h"

ConditionBuffDuration::ConditionBuffDuration(Buff* buff, const Comparator comparator, const double cmp_value) :
    Condition(comparator),
    buff(buff),
    cmp_value(cmp_value)
{}

bool ConditionBuffDuration::condition_fulfilled() const {
    switch (comparator) {
    case Comparator::Less:
    case Comparator::Leq:
        return buff->time_left() < cmp_value;
    case Comparator::Eq:
        return (buff->time_left() - cmp_value) < 0.000001;
    case Comparator::Geq:
    case Comparator::Greater:
        return buff->time_left() > cmp_value;
    case Comparator::False:
        return !buff->is_active();
    case Comparator::True:
        return buff->is_active();
    }

    return false;
}

QString ConditionBuffDuration::condition_description() const {
    return QString("%1 buff remaining %2 %3 seconds").arg(buff->name).arg(comparator_as_string()).arg(QString::number(cmp_value, 'f', 1));
}
