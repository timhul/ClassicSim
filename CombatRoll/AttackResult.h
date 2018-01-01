#ifndef ATTACKRESULT_H
#define ATTACKRESULT_H

#include <assert.h>

namespace Outcome {
    static const int MISS = 0;
    static const int DODGE = 1;
    static const int PARRY = 2;
    static const int GLANCING = 3;
    static const int BLOCK = 4;
    static const int BLOCK_CRITICAL = 5;
    static const int CRITICAL = 6;
    static const int HIT = 7;
}


class AttackResult {
public:
    AttackResult(const int _outcome): outcome(_outcome) {
        assert(_outcome >= Outcome::MISS);
        assert(_outcome <= Outcome::HIT);
    }

    bool is_critical(void) const;
    bool is_hit(void) const;
    bool is_glancing(void) const;
    bool is_miss(void) const;
    bool is_dodge(void) const;
    bool is_parry(void) const;
    bool is_resist(void) const;
    bool is_partial_resist(void) const;

protected:
private:
    const int outcome;
};

#endif // ATTACKRESULT_H
