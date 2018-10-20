#ifndef NATUREDAMAGEATTACK_H
#define NATUREDAMAGEATTACK_H

#include "Spell.h"

class Random;

class NatureDamageAttack: public Spell {
public:
    NatureDamageAttack(Character* pchar, const QString& name, const unsigned min, const unsigned max);
    ~NatureDamageAttack() override;

protected:
private:
    const unsigned min;
    const unsigned max;
    Random* random;

    void spell_effect() override;
};

#endif // NATUREDAMAGEATTACK_H
