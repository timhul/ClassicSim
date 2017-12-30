#ifndef AUTOATTACK_H
#define AUTOATTACK_H

#include "Spell.h"

class AutoAttack: public Spell {
public:
    AutoAttack(Engine* engine, Character* pchar) :
        Spell("AutoAttack", engine, pchar, 0.0, 0) {}

protected:
private:
};

#endif // AUTOATTACK_H
