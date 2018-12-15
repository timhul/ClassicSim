#ifndef MAGICATTACKRESULT_H
#define MAGICATTACKRESULT_H

namespace MagicAttackResult {
    static const int MISS = 0;
    static const int CRITICAL = 1;
    static const int HIT = 2;
}

namespace MagicResistResult {
    static const int NO_RESIST = 0;
    static const int PARTIAL_RESIST_25 = 1;
    static const int PARTIAL_RESIST_50 = 2;
    static const int PARTIAL_RESIST_75 = 3;
    static const int FULL_RESIST = 4;
}

#endif // MAGICATTACKRESULT_H
