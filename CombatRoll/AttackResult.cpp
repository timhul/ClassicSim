
#include "AttackResult.h"
#include <QDebug>

bool AttackResult::is_critical(void) const {
    return (this->outcome == Outcome::CRITICAL || this->outcome == Outcome::BLOCK_CRITICAL);
}

bool AttackResult::is_hit(void) const {
    return (this->outcome == Outcome::HIT);
}

bool AttackResult::is_glancing(void) const {
    return (this->outcome == Outcome::GLANCING);
}

bool AttackResult::is_miss(void) const {
    return (this->outcome == Outcome::MISS);
}

bool AttackResult::is_dodge(void) const {
    return (this->outcome == Outcome::DODGE);
}

bool AttackResult::is_parry(void) const {
    return (this->outcome == Outcome::PARRY);
}

bool AttackResult::is_partial_resist(void) const {
    return false;
}

bool AttackResult::is_resist(void) const {
    return false;
}

void AttackResult::dump() const {
    switch (this->outcome) {
    case Outcome::CRITICAL:
        qDebug() << "Outcome::CRITICAL";
        break;
    case Outcome::HIT:
        qDebug() << "Outcome::HIT";
        break;
    case Outcome::GLANCING:
        qDebug() << "Outcome::GLANCING";
        break;
    case Outcome::MISS:
        qDebug() << "Outcome::MISS";
        break;
    case Outcome::DODGE:
        qDebug() << "Outcome::DODGE";
        break;
    case Outcome::PARRY:
        qDebug() << "Outcome::PARRY";
        break;
    default:
        assert(false);
    }
}
