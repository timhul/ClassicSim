
#include "AttackResult.h"

#include <iostream>

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
        std::cout << "Outcome::CRITICAL";
        break;
    case Outcome::HIT:
        std::cout << "Outcome::HIT";
        break;
    case Outcome::GLANCING:
        std::cout << "Outcome::GLANCING";
        break;
    case Outcome::MISS:
        std::cout << "Outcome::MISS";
        break;
    case Outcome::DODGE:
        std::cout << "Outcome::DODGE";
        break;
    case Outcome::PARRY:
        std::cout << "Outcome::PARRY";
        break;
    default:
        assert(false);
    }
    std::cout << std::endl;
}
