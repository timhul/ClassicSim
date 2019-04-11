#ifndef RAPIDFIRE_H
#define RAPIDFIRE_H

#include "Spell.h"

class RapidFireBuff;

class RapidFire: public Spell {
public:
    RapidFire(Character *pchar);
    ~RapidFire() override;

    RapidFireBuff* get_rapid_fire_buff() const;

private:
    RapidFireBuff* rapid_fire;

    void spell_effect() override;
};

#endif // RAPIDFIRE_H
