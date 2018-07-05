
#include "ConditionSpell.h"
#include "Spell.h"

ConditionSpell::ConditionSpell(Spell *spell, const int comparator, const float cmp_value) :
    spell(spell),
    comparator(comparator),
    cmp_value(cmp_value)
{}

bool ConditionSpell::condition_fulfilled() const {
    float cooldown = spell->get_cooldown_remaining();

    switch (comparator) {
    case Comparators::less:
    case Comparators::leq:
        return cooldown < cmp_value;
    case Comparators::eq:
        return (cooldown - cmp_value) < 0.000001;
    case Comparators::geq:
    case Comparators::greater:
        return cooldown > cmp_value;
    }

    assert(false);
    return false;
}
