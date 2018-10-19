#ifndef SHADOWBOLTATTACK_H
#define SHADOWBOLTATTACK_H

#include "Spell.h"

class Random;

class ShadowBoltAttack: public Spell {
public:
    ShadowBoltAttack(Character* pchar, const QString& name, const unsigned min, const unsigned max);
    ~ShadowBoltAttack() override;

protected:
private:
    const unsigned min;
    const unsigned max;
    Random* random;

    void spell_effect() override;
};

#endif // SHADOWBOLTATTACK_H
