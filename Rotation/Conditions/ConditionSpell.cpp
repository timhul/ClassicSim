#include "ConditionSpell.h"

#include "Spell.h"
#include "Utils/Check.h"

ConditionSpell::ConditionSpell(Spell *spell, const int comparator, const double cmp_value) :
    Condition(comparator),
    spell(spell),
    cmp_value(cmp_value)
{}

bool ConditionSpell::condition_fulfilled() const {
    double cooldown = spell->get_cooldown_remaining();

    switch (comparator) {
    case Comparators::less:
    case Comparators::leq:
        return cooldown < cmp_value;
    case Comparators::eq:
        return (cooldown - cmp_value) < 0.000001;
    case Comparators::geq:
    case Comparators::greater:
        return cooldown > cmp_value;
    default:
        check(false, "ConditionSpell::condition_fulfilled reached end of switch");
        return false;
    }
}

QString ConditionSpell::condition_description() const {
    return QString("%1 cooldown %2 %3 seconds").arg(spell->get_name()).arg(comparator_as_string()).arg(QString::number(cmp_value, 'f', 1));
}
