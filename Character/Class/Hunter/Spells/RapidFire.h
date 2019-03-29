#ifndef RAPIDFIRE_H
#define RAPIDFIRE_H

#include "Spell.h"

class Buff;
class RapidFireBuff;

class RapidFire: public Spell {
public:
    RapidFire(Character *pchar);
    ~RapidFire() override;

private:
    RapidFireBuff* rapid_fire;

    void spell_effect() override;
};

#endif // RAPIDFIRE_H
