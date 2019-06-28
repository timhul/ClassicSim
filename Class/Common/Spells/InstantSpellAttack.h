#pragma once

#include "Spell.h"
#include "MagicSchools.h"

class Random;

class InstantSpellAttack: public Spell {
public:
    InstantSpellAttack(Character* pchar, const QString& name, const QString &icon, const MagicSchool school, const unsigned min, const unsigned max, const double coefficient = 0.56);
    ~InstantSpellAttack() override;

private:
    const MagicSchool school;
    const unsigned min;
    const unsigned max;
    const double coefficient;
    Random* random;

    void spell_effect() override;
};
