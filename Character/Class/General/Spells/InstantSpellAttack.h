#ifndef INSTANTSPELLATTACK_H
#define INSTANTSPELLATTACK_H

#include "Spell.h"
#include "MagicSchools.h"

class Random;

class InstantSpellAttack: public Spell {
public:
    InstantSpellAttack(Character* pchar, const QString& name, const QString &icon, const MagicSchool school, const unsigned min, const unsigned max);
    ~InstantSpellAttack() override;

protected:
private:
    const MagicSchool school;
    const unsigned min;
    const unsigned max;
    Random* random;

    void spell_effect() override;
};

#endif // INSTANTSPELLATTACK_H
